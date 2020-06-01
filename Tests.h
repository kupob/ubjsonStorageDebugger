
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

private:
    std::unique_ptr<storage::Storage> m_storage;
};

