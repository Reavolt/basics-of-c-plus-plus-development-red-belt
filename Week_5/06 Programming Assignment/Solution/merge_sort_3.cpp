#include "test_runner.h"
#include <algorithm>
#include <vector>

//----------------------------------------------------------------------------------------------------
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (std::distance(range_begin, range_end) < 2)
    {
        return;
    }
    else
    {
        std::vector<typename RandomIt::value_type> elements
        (std::make_move_iterator(range_begin), std::make_move_iterator(range_end));

        auto itr_part_1 = elements.begin() + elements.size() / 3;
        auto itr_part_2 = itr_part_1 + elements.size() / 3;

        MergeSort(elements.begin(), itr_part_1);
        MergeSort(itr_part_1, itr_part_2);
        MergeSort(itr_part_2, elements.end());

        std::vector<typename RandomIt::value_type> temp;

        std::merge(std::make_move_iterator(elements.begin()), std::make_move_iterator(itr_part_1),
        std::make_move_iterator(itr_part_1), std::make_move_iterator(itr_part_2), std::move(std::back_inserter(temp)));
        std::merge(std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()),
        std::make_move_iterator(itr_part_2), std::make_move_iterator(elements.end()), range_begin);
    }
}
//----------------------------------------------------------------------------------------------------
void TestIntVector()
{
    std::vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestIntVector, "TestIntVector");
    return 0;
}
//----------------------------------------------------------------------------------------------------