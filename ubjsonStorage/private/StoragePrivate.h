
#pragma once

#include "../dataTypes/TimeStamp.h"
#include "../dataTypes/FileInfo.h"
#include "../dataTypes/RawData.h"

namespace storage
{

class Storage;
class ConfigReader;

class StoragePrivate
{
public:
    StoragePrivate();
    ~StoragePrivate();

private:
    void save(TimeStamp time, const RawData& data);
    std::optional<RawData> m_load(TimeStamp time);
    void insert(TimeStamp time, const RawData& data);

    void beginInsert(TimeStamp time);
    void endInsert();

    void checkStorageDir();
    void analyzeStorage();
    void initNewStorageFile(TimeStamp time, std::string_view fileName);

    std::string findFile(TimeStamp time);
    std::string generateFileName(TimeStamp time);

    std::string timeToString(TimeStamp time);
    TimeStamp timeFromString(const std::string& data);

private:
    std::unique_ptr<ConfigReader> m_config;
    std::map<TimeStamp, FileInfo> m_storageFiles;

    RawData m_obj;
    std::string m_fileName;
    TimeStamp m_fileTimeStamp;

private:
    friend class Storage;
};

}
