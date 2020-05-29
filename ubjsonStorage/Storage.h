#pragma once

#include "dataTypes/TimeStamp.h"
#include "dataTypes/RawData.h"

#include <optional>
#include <string>
#include <string_view>
#include <experimental/propagate_const>

namespace storage
{

class StoragePrivate;

class Storage {
    std::experimental::propagate_const<std::unique_ptr<StoragePrivate>> pImpl;

public:
    Storage();
    ~Storage();

    ///< Single save
    template<typename T>
    void save(TimeStamp time, const T& data) {
        m_save(time, toRawData<T>(data));
    }

    ///< Single load
    template<typename T>
    std::optional<T> load(TimeStamp time) {
        auto optRaw = m_load(time);
        return optRaw.has_value() ? fromRawData<T>(optRaw.value()) : std::optional<T>();
    }

    ///< Better for multiple saves but you should embrace it with beginInsert() and endInsert()
    template<typename T>
    void insert(TimeStamp time, const T& data) {
        m_insert(time, toRawData<T>(data));
    }

    ///< For multiple saves
    void beginInsert(TimeStamp time);
    void endInsert();

private:
    void m_save(TimeStamp time, const RawData& data);
    std::optional<RawData> m_load(TimeStamp time);

    void m_insert(TimeStamp time, const RawData& data);
};

}

