
#include "ConfigReader.h"

#include <nlohmann/json.hpp>

#include "../logger/log.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace storage
{

constexpr auto CFG_PATH = "ioconfig.cfg";

ConfigReader::ConfigReader()
{
    if (!read()) {
        LOG("Could not read cfg");
    }
}

ConfigReader::~ConfigReader() = default;

bool ConfigReader::read()
{
    std::ifstream f(CFG_PATH);
    std::string cfgContents;
    if(f) {
        std::ostringstream ss;
        ss << f.rdbuf();
        cfgContents = ss.str();

        return parseCfgContents(cfgContents);;
    }
    else {
        LOG("Could not find cfg file");
    }

    return false;
}

bool ConfigReader::parseCfgContents(std::string_view data)
{
    using json = nlohmann::json;

    json contents = json::parse(data);

    if (contents.count("max_file_size"))
        m_maxFileSize = contents["max_file_size"];

    if (contents.count("storage_path"))
        m_storagePath = contents["storage_path"];

    cfgLoaded = checkCfgCompleteness();

    return cfgLoaded;
}

bool ConfigReader::checkCfgCompleteness()
{
    return m_maxFileSize
        && !m_storagePath.empty()
        ;
}

} // namespace
