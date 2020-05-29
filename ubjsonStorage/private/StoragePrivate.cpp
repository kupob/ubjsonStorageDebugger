
#include "StoragePrivate.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "../configReader/ConfigReader.h"
#include "../logger/log.h"

#include "../UbjsonCpp/include/stream_writer.hpp"
#include "../UbjsonCpp/include/stream_reader.hpp"

namespace storage
{

namespace fs = std::filesystem;

constexpr auto FILE_TYPE = ".dat";

StoragePrivate::StoragePrivate()
    : m_config(std::make_unique<ConfigReader>())
{
    if (m_config->isCfgLoaded()) {
        LOG(m_config->getMaxFileSize());
        LOG(m_config->getStoragePath());

        checkStorageDir();
        analyzeStorage();
    }
}

StoragePrivate::~StoragePrivate() = default;

void StoragePrivate::save(TimeStamp time, const RawData& data)
{
    beginInsert(time);

    insert(time, data);

    endInsert();
}

std::optional<RawData> StoragePrivate::m_load(TimeStamp time)
{
    auto fileName = findFile(time);
    auto file = std::filesystem::path (fileName);
    if (!fs::exists(fileName))
        return {};

    auto fileTimeStamp = timeFromString(file.stem());
    auto diff = time - fileTimeStamp;

    std::ifstream input;
    input.open(findFile(time), std::ios::binary);

    ubjson::StreamReader<decltype(input)> reader(input);
    RawData obj = reader.getNextValue();

    auto it = obj.find(std::to_string(diff));
    if (it != obj.end())
        return *it;

    return {};
}

void StoragePrivate::insert(TimeStamp time, const RawData& data)
{
    auto diff = time - m_fileTimeStamp;
    m_obj[std::to_string(diff)] = data;
}

void StoragePrivate::beginInsert(TimeStamp time)
{
    m_fileName = findFile(time);
    bool fileExists = fs::exists(m_fileName);

    auto file = std::filesystem::path (m_fileName);
    m_fileTimeStamp = fs::exists(m_fileName) ? timeFromString(file.stem()) : time;

    if (fileExists) {
        std::ifstream input;
        input.open(findFile(time), std::ios::binary);

        ubjson::StreamReader<decltype(input)> reader(input);
        m_obj = reader.getNextValue();
    }
    else {
        initNewStorageFile(time, m_fileName);
    }
}

void StoragePrivate::endInsert()
{
    std::ofstream output;
    output.open(m_fileName, std::ios::binary);

    ubjson::StreamWriter<std::ostream> writer(output);
    auto result = writer.writeValue(m_obj);

    output.close();

    if(result.second)
        std::cout << "Successfully wrote: " << result.first << " bytes" << std::endl;
}

void StoragePrivate::checkStorageDir()
{
    if (!fs::exists(m_config->getStoragePath()))
        fs::create_directories(m_config->getStoragePath());
}

void StoragePrivate::analyzeStorage()
{
    m_storageFiles.clear();

    for(auto& entry: fs::directory_iterator(m_config->getStoragePath())) {
        auto file = fs::path(entry.path());
        if (file.extension() == FILE_TYPE) {
            auto fileTime = timeFromString(file.stem());
            m_storageFiles[fileTime] = {entry.path(), fileTime, 0 /* TODO */};
        }
    }
}

void StoragePrivate::initNewStorageFile(TimeStamp time, std::string_view fileName)
{
    m_storageFiles[time] = {fileName.data(), time, 1};
}

std::string StoragePrivate::findFile(TimeStamp time)
{
    if (m_storageFiles.empty()) {
        return generateFileName(time);
    }

    auto it = m_storageFiles.lower_bound(time);
    if (it == m_storageFiles.begin()) {
        return generateFileName(time);
    }

    return (--it)->second.fileName;
}

std::string StoragePrivate::generateFileName(TimeStamp time)
{
    return m_config->getStoragePath() + "/" + timeToString(time) + FILE_TYPE;
}

std::string StoragePrivate::timeToString(TimeStamp time)
{
    std::stringstream ss;
    ss << time;
    return ss.str();
}

TimeStamp StoragePrivate::timeFromString(const std::string& data)
{
    std::istringstream stream( data );
    TimeStamp result;
    stream >> result;
    return result;
}


}
