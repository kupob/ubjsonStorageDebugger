
#pragma once

#include <cinttypes>
#include <string_view>
#include <string>

namespace storage
{

class ConfigReader
{
public:
    ConfigReader();
    ~ConfigReader();

public:
    inline bool isCfgLoaded() const { return cfgLoaded; }

    inline int64_t getMaxFileSize() const noexcept { return m_maxFileSize; }
    inline std::string getStoragePath() const noexcept { return m_storagePath; }

private:
    bool read();

    bool parseCfgContents(std::string_view data);
    bool checkCfgCompleteness();

private:
    bool cfgLoaded = false;

    int64_t m_maxFileSize { 0 };
    std::string m_storagePath {};
};

}
