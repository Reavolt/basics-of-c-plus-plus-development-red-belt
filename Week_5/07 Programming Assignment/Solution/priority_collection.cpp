#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

//----------------------------------------------------------------------------------------------------
template <typename T>
class PriorityCollection
{
public:
    using Id = size_t;

    Id Add(T object);
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin);

    bool IsValid(Id id) const;
    const T& Get(Id id) const;
    void Promote(Id id);
    std::pair<const T&, int> GetMax() const;
    std::pair<T, int> PopMax();
private:
    int id = 0;
    std::set<std::pair<int, Id>> sorted_objects;
    std::vector<std::pair<T, int>> objects;
};
//----------------------------------------------------------------------------------------------------
template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object)
{
    sorted_objects.emplace(0, id);
    objects.emplace_back(std::move(object), 0);
    return Id(id++);
}
//----------------------------------------------------------------------------------------------------
template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
{
    while (range_begin != range_end) *ids_begin++ = Add(std::move(*range_begin++));
}
//----------------------------------------------------------------------------------------------------
template <typename T>
bool PriorityCollection<T>::IsValid(Id id) const
{
    return objects[id].second >= 0;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
const T& PriorityCollection<T>::Get(Id id) const
{
    return objects[id].first;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void PriorityCollection<T>::Promote(Id id)
{
    auto new_priority = objects[id].second++;
    auto old_priority = new_priority++;
    sorted_objects.erase({old_priority, id});
    sorted_objects.insert({new_priority, id});
}
//----------------------------------------------------------------------------------------------------
template <typename T>
std::pair<const T&, int> PriorityCollection<T>::GetMax() const
{
    return objects[std::prev(std::end(sorted_objects))->second];
}
//----------------------------------------------------------------------------------------------------
template <typename T>
std::pair<T, int> PriorityCollection<T>::PopMax()
{
    auto id = std::prev(std::end(sorted_objects))->second;
    auto result = std::move(objects[id]);
    sorted_objects.erase({result.second, id});
    objects[id] = {T(), -1};
    return result;
}
//----------------------------------------------------------------------------------------------------
class StringNonCopyable : public std::string
{
public:
    using std::string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};
//----------------------------------------------------------------------------------------------------
void TestNoCopy()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
    {
        strings.Promote(red_id);
    }

    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }

    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }

    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestNoCopy, "TestNoCopy");
    return 0;
}
//----------------------------------------------------------------------------------------------------