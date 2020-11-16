#include "parse.h"

//----------------------------------------------------------------------------------------------------
std::string_view Strip(std::string_view s)
{
    while (!s.empty() && std::isspace(s.front()))
    {
        s.remove_prefix(1);
    }
    while (!s.empty() && std::isspace(s.back()))
    {
        s.remove_suffix(1);
    }
    return s;
}
//----------------------------------------------------------------------------------------------------
std::vector<std::string_view> SplitBy(std::string_view s, char sep)
{
    std::vector<std::string_view> result;
    while (!s.empty())
    {
        size_t pos = s.find(sep);
        result.push_back(s.substr(0, pos));
        s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
    }
    return result;
}
//----------------------------------------------------------------------------------------------------