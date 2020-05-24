#include <iostream>

#include "ebmlio/Storage.h"
#include "ebmlio/logger/log.h"
#include "ebmlio/dataTypes/stdSupport.h"

int main()
{
    ebmlio::Storage s;

    std::string testString {"This is the string for tests"};
    ebmlio::TimeStamp time = std::time(nullptr);

    s.save(time, testString);
    auto resultString = s.load<std::string>(time).value_or("");

    LOG(testString);
    LOG(resultString);

    return 0;
}
