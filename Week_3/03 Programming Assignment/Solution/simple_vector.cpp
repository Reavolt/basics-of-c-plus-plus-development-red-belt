#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

//----------------------------------------------------------------------------------------------------
void TestConstruction()
{
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u, "");
    ASSERT_EQUAL(empty.Capacity(), 0u, "");
    ASSERT(empty.begin() == empty.end(), "");

    SimpleVector<std::string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u, "");
    ASSERT(five_strings.Size() <= five_strings.Capacity(), "");
    for (auto& item : five_strings)
    {
        ASSERT(item.empty(), "");
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello", "");
}
//----------------------------------------------------------------------------------------------------
void TestPushBack()
{
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i)
    {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity(), "");
    }
    std::sort(std::begin(v), std::end(v));

    const std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQUAL(v.Size(), expected.size(), "1");
    ASSERT(equal(std::begin(v), std::end(v), begin(expected)), "");
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestConstruction, "TestConstruction");
    tr.RunTest(TestPushBack, "TestPushBack");
    return 0;
}
//----------------------------------------------------------------------------------------------------