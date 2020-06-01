
#pragma once

#include <memory>

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
    void test4(); ///< Store double

private:
    std::unique_ptr<storage::Storage> m_storage;
};

