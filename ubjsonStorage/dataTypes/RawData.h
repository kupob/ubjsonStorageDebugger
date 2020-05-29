#pragma once

#include <optional>
#include <string>

#include "../UbjsonCpp/include/value.hpp"

namespace storage
{

typedef ubjson::Value RawData;

template<typename T>
std::optional<T> fromRawData(const RawData &data);

template<typename T>
RawData toRawData(const T &data);

}
