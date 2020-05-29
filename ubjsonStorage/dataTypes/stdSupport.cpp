
#include "stdSupport.h"

#include <string>

namespace storage
{

template<>
RawData toRawData(const std::string &data)
{
    return data;
}

template<>
std::optional<std::string> fromRawData(const RawData &data)
{
    return data.asString();
}

}
