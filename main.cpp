#include <iostream>
#include <chrono>

#include "ubjsonStorage/Storage.h"
#include "ubjsonStorage/logger/log.h"
#include "ubjsonStorage/dataTypes/stdSupport.h"

bool test1(storage::Storage& s) ///< Store two strings separately and load it back
{
    std::string testString {"This is the first string for tests"};
    std::string testString2 {"This is the second string for tests"};

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    storage::TimeStamp time = now_ms.time_since_epoch().count();
    storage::TimeStamp time2 = time + 1;

    s.save(time, testString);
    s.save(time2, testString2);

    auto resultString = s.load<std::string>(time).value_or("Something went wrong");
    auto resultString2 = s.load<std::string>(time2).value_or("Something went wrong");

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

int main()
{
    storage::Storage s;

    test1(s);

    return 0;
}
