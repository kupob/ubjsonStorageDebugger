
#pragma once

#include <memory>
#include <iostream>

#include "ubjsonStorage/Storage.h"
#include "ubjsonStorage/logger/log.h"

namespace {
#define MAKE_TEMPLATE_NAME(T) std::string getTypeName(const T& value) { return #T; }

MAKE_TEMPLATE_NAME(bool);
MAKE_TEMPLATE_NAME(int8_t);
MAKE_TEMPLATE_NAME(uint8_t);
MAKE_TEMPLATE_NAME(int16_t);
MAKE_TEMPLATE_NAME(uint16_t);
MAKE_TEMPLATE_NAME(int);
MAKE_TEMPLATE_NAME(unsigned int);
MAKE_TEMPLATE_NAME(int64_t);
MAKE_TEMPLATE_NAME(uint64_t);
MAKE_TEMPLATE_NAME(float);
MAKE_TEMPLATE_NAME(double);
MAKE_TEMPLATE_NAME(std::string);
}

namespace storage
{
class Storage;
}

class Tests
{
public:
    Tests();
    ~Tests();

    void run();

private:
    void test1(); ///< Store two strings separately and load it back
    void test2(); ///< Store many big items
    void test3(); ///< Store custom struct

    storage::TimeStamp getTime();

    template<typename T>
    void testType(const T& value) noexcept {
        storage::TimeStamp time = getTime();

        m_storage->save(time, value);

        std::optional<T> result = m_storage->load<T>(time);

        if (result.has_value() && result.value() == value) {
            LOGERROR ("Test " << getTypeName(value) << " passed");
        }
        else {
            LOGERROR ("Test " << getTypeName(value) << " not passed");
            LOGERROR("source: " << value);
            if (result.has_value())
                LOGERROR("result: " << result.value());
            else
                LOGERROR("result: " << "got nothing");
        }
    }

private:
    std::unique_ptr<storage::Storage> m_storage;
};

