#include "test_runner.h"

#include <iostream>
#include <utility>
#include <vector>

//-------------------------------------------------------------------------------------------------
template <typename T>
class Table
{
public:
    Table(const size_t rows, const size_t cols)
    {
        Resize(rows, cols);
    }

    void Resize(const size_t rows, const size_t columns)
    {
        data.resize(rows);

        for (auto& itr : data)
        {
            itr.resize(columns);
        }
    }

    std::pair<size_t, size_t> Size() const
    {
        return std::make_pair(data.size(), (data.empty() ? 0 : data.at(0).size()));
    }

    std::vector<T>& operator[](const size_t value)
    {
        return data.at(value);
    }

    const std::vector<T>& operator[](const size_t value) const
    {
        return data.at(value);
    }
private:
    std::vector<std::vector<T>> data;
};
//-------------------------------------------------------------------------------------------------
void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}
//-------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
//-------------------------------------------------------------------------------------------------