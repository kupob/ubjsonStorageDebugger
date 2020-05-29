#pragma once

#include <string>

#include "RawData.h"

namespace storage
{

template<>
RawData toRawData(const std::string& data);

template<>
std::optional<std::string> fromRawData (const RawData& data);

}
