#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

//-------------------------------------------------------------------------------------------------
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) 
{
    auto res = std::find_if(first, last, pred);
    
    if (res == last) 
    {
        return res;
    }

    for (auto it = res; it != last; it = std::find_if(std::next(it), last, pred))
    {
        if (it != last && *res < *it) 
        {
            res = it;
        }
    }
    return res;
}
//-------------------------------------------------------------------------------------------------
void TestUniqueMax()
{
    auto IsEven = [](int x) 
    {
        return x % 2 == 0;
    };

    const std::list<int> hill{ 2, 4, 8, 9, 6, 4, 2 };
    auto max_iterator = hill.begin();
    std::advance(max_iterator, 2);

    std::vector<int> numbers(10);
    std::iota(numbers.begin(), numbers.end(), 1);

    /*
      Мы не используем AssertEqual, потому что для итераторов
      отсутствует перегрузка оператора вывода в поток ostream.
      Разыменование здесь также недопустимо, так как оно может повлечь
      неопределенное поведение, если функция max_element_if, к примеру,
      вернула итератор, указывающий на конец контейнера.
    */

    Assert(max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
    "Expect the last element");

    Assert(max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
    "Expect the maximal even number");
}
//-------------------------------------------------------------------------------------------------
void TestSeveralMax() 
{
    struct IsCapitalized 
    {
        bool operator()(const std::string& s)
        {
            return !s.empty() && std::isupper(s.front());
        }
    };

    const std::forward_list<std::string> text
    { "One", "two", "Three", 
      "One", "Two", "Three", 
      "one", "Two", "three" 
    };
    auto max_iterator = text.begin();
    std::advance(max_iterator, 4);

    Assert(max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
    "Expect thr first \"Two\"");
}
//-------------------------------------------------------------------------------------------------
void TestNoMax() 
{
    const std::vector<int> empty;
    const std::string str = "Non-empty string";

    auto AlwaysTrue = [](int) 
    {
        return true;
    };
    Assert(max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
    "Expect end for empty container");

    auto AlwaysFalse = [](char)
    {
        return false;
    };
    Assert(max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(), 
    "Expect end for AlwaysFalse predicate");
}
//-------------------------------------------------------------------------------------------------
int main() 
{
    TestRunner tr;
    tr.RunTest(TestUniqueMax, "TestUniqueMax");
    tr.RunTest(TestSeveralMax, "TestSeveralMax");
    tr.RunTest(TestNoMax, "TestNoMax");
    return 0;
}
//-------------------------------------------------------------------------------------------------