
#include "Tests.h"

#include <iostream>
#include <chrono>

#include "ubjsonStorage/Storage.h"
#include "ubjsonStorage/logger/log.h"
#include "ubjsonStorage/stdSupport.h"

Tests::Tests()
    : m_storage(new storage::Storage())
{

}

Tests::~Tests()
{

}

void Tests::run()
{
    test1();
    test2();
}

///< Store two strings separately and load it back
void Tests::test1()
{
    std::string testString {"This is the first string for tests"};
    std::string testString2 {"This is the second string for tests"};

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    storage::TimeStamp time = now_ms.time_since_epoch().count();
    storage::TimeStamp time2 = time + 1;

    m_storage->save(time, testString);
    m_storage->save(time2, testString2);

    auto resultString = m_storage->load<std::string>(time).value_or("Something went wrong");
    auto resultString2 = m_storage->load<std::string>(time2).value_or("Something went wrong");

    if (testString == resultString &&
        testString2 == resultString2) {
        LOG ("Test 1 passed");
    }
    else {
        LOGERROR("Test 1 not passed");
        LOGERROR ("src: " + testString + " result: " + resultString);
        LOGERROR ("src: " + testString2 + " result: " + resultString2);
    }
}

///< Store many big items
void Tests::test2()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    storage::TimeStamp time = now_ms.time_since_epoch().count();


    m_storage->beginInsert(time);

    for (int i = 0; i <= 2000; ++i) {
        std::string testString {"This is very big big big big big big big big big big big big big big big big big string for tests number " + std::to_string(i)};
        m_storage->save(time + i, testString);
    }

    m_storage->endInsert();
}

