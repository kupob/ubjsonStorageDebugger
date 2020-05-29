#include "Storage.h"

#include "private/StoragePrivate.h"

namespace storage
{

Storage::Storage()
    : pImpl(std::make_unique<StoragePrivate>())
{

}

Storage::~Storage() = default;

void Storage::m_save(TimeStamp time, const RawData& data)
{
    pImpl->save(time, data);
}

std::optional<RawData> Storage::m_load(TimeStamp time)
{
    return pImpl->m_load(time);
}

void Storage::beginInsert(TimeStamp time)
{
    pImpl->beginInsert(time);
}

void Storage::endInsert()
{
    pImpl->endInsert();
}

void Storage::m_insert(TimeStamp time, const RawData& data)
{
    pImpl->insert(time, data);
}

}
