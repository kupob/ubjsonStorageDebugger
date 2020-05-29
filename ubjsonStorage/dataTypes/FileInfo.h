
#pragma once

#include <string>

#include "TimeStamp.h"

namespace storage
{

struct FileInfo
{
    std::string fileName;
    TimeStamp time = 0;

    int32_t dataCount = 0;
};

}
