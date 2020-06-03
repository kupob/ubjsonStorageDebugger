
#include "Tests.h"

#include <chrono>

#include "ubjsonStorage/stdSupport.h"

storage::TimeStamp Tests::getTime()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}

Tests::Tests()
    : m_storage(new storage::Storage())
{

}

Tests::~Tests()
{

}

void Tests::run()
{
//    test1();
//    test2();
//    test3();

    testType <bool>          (true);
    testType <int8_t>        (127);
    testType <uint8_t>       (255);
    testType <int16_t>       (32666);
    testType <uint16_t>      (64777);
    testType <int>           (1234567890);
    testType <unsigned int>  (4242424242);
    testType <int64_t>       (8'800'555'35'35);
    testType <uint64_t>      (8'800'999'99'99);
    testType <float>         (123.456);
    testType <double>        (8'800.555'35'35);
    testType <std::string>   ("The quick brown fox jumps over the lazy dog");
}

///< Store two strings separately and load it back
void Tests::test1()
{
    std::string testString {"This is the first string for tests"};
    std::string testString2 {"This is the second string for tests"};

    storage::TimeStamp time = getTime();
    storage::TimeStamp time2 = time + 1;

    m_storage->save(time, testString);
    m_storage->save(time2, testString2);

    auto resultString = m_storage->load<std::string>(time).value_or("Something went wrong");
    auto resultString2 = m_storage->load<std::string>(time2).value_or("Something went wrong");

    if (testString == resultString &&
        testString2 == resultString2) {
        LOGERROR ("Test 1 passed");
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
    storage::TimeStamp time = getTime();

    m_storage->beginInsert(time);

    for (int i = 0; i <= 2000; ++i) {
        std::string testString {"This is very big big big big big big big big big big big big big big big big big string for tests number " + std::to_string(i)};
        m_storage->insert(time + i, testString);
    }

    m_storage->endInsert();
}

struct test3struct {
    std::string stringValue;
    int intValue;
    double doubleValue;
    bool boolValue;

    bool operator==(const test3struct& other) const {
        return stringValue == other.stringValue
            && intValue == other.intValue
            && doubleValue == other.doubleValue
            && boolValue == other.boolValue;
    }
};

namespace storage
{

template<>
std::optional<test3struct> deserialize(const RawData &data)
{
    return test3struct { data[0], data[1], data[2], data[3] };
}

template<>
RawData serialize(const test3struct &data)
{
    return { {data.stringValue}, {data.intValue}, {data.doubleValue}, {data.boolValue} };
}

} // namespace storage

void Tests::test3() ///< Store custom struct
{
    storage::TimeStamp time = getTime();
    test3struct s {"This is string for tests", 6666666, 1234567.1234567, true};

    m_storage->save(time, s);

    auto result = m_storage->load<test3struct>(time);

    if (result.has_value() && result.value() == s) {
        LOGERROR ("Test 3 passed");
    }
    else {
        LOGERROR ("Test 3 not passed");
        LOGERROR("source:");
        LOGERROR(s.stringValue << " " << s.intValue << " " << s.doubleValue << " " << s.boolValue);
        LOGERROR("result:");
        LOGERROR(result->stringValue << " " << result->intValue << " " << result->doubleValue << " " << result->boolValue);
    }
}
