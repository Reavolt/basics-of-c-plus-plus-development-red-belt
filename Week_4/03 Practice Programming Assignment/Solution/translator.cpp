#include "test_runner.h"

#include <string>
#include <map>
#include <deque>
#include <string_view>

//----------------------------------------------------------------------------------------------------
class Translator
{
public:
    void Add(std::string_view source, std::string_view target);
    std::string_view TranslateForward(std::string_view source) const;
    std::string_view TranslateBackward(std::string_view target) const;
private:
    std::string_view GetClonedView(std::string_view s);
    static std::string_view Translate(const std::map<std::string_view, std::string_view>& dict, std::string_view s);

    std::map<std::string_view, std::string_view> forward_dict;
    std::map<std::string_view, std::string_view> backward_dict;
    std::deque<std::string> data;
};
//----------------------------------------------------------------------------------------------------
void Translator::Add(std::string_view source, std::string_view target)
{
    const std::string_view source_view = GetClonedView(source);
    const std::string_view target_view = GetClonedView(target);
    forward_dict[source_view] = target_view;
    backward_dict[target_view] = source_view;
}
//----------------------------------------------------------------------------------------------------
std::string_view Translator::TranslateForward(std::string_view source) const
{
    return Translate(forward_dict, source);
}
//----------------------------------------------------------------------------------------------------
std::string_view Translator::TranslateBackward(std::string_view target) const
{
    return Translate(backward_dict, target);
}
//----------------------------------------------------------------------------------------------------
std::string_view Translator::GetClonedView(std::string_view s)
{
    for (const auto* map_ptr : {&forward_dict, &backward_dict})
    {
        if (const auto it = map_ptr->find(s); it != map_ptr->end())
        {
            return it->first;
        }
    }
    return data.emplace_back(s);
}
//----------------------------------------------------------------------------------------------------
std::string_view Translator::Translate(const std::map<std::string_view, std::string_view>& dict, std::string_view s)
{
    if (const auto it = dict.find(s); it != dict.end())
    {
        return it->second;
    }
    else
    {
        return {};
    }
}
//----------------------------------------------------------------------------------------------------
void TestSimple()
{
    Translator translator;
    translator.Add(std::string("okno"), std::string("window"));
    translator.Add(std::string("stol"), std::string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestSimple, "TestSimple");
    return 0;
}
//----------------------------------------------------------------------------------------------------