#include <iostream>

#include "ubjsonStorage/Storage.h"
#include "ubjsonStorage/logger/log.h"
#include "ubjsonStorage/dataTypes/stdSupport.h"

int main()
{
    ubjsonStorage::Storage s;

    std::string testString {"This is the first string for tests"};
    std::string testString2 {"This is the second string for tests"};

    ubjsonStorage::TimeStamp time = std::time(nullptr);
    ubjsonStorage::TimeStamp time2 = time + 1;

    s.save(time, testString);
    s.save(time2, testString2);

    auto resultString = s.load<std::string>(time).value_or("Something went wrong");
    auto resultString2 = s.load<std::string>(time2).value_or("Something went wrong");

    LOG(testString);
    LOG(resultString);

    LOG(testString2);
    LOG(resultString2);

    return 0;
}
