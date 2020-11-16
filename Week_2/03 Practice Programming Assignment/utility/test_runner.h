#pragma once

#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

//-------------------------------------------------------------------------------------------------
class TestRunner
{
public:
    template <typename test_func>
    void RunTest(test_func func, const std::string& test_name);
    
    TestRunner() = default;
    ~TestRunner();
private:
    int fail_count = 0;
};
//-------------------------------------------------------------------------------------------------
template <typename test_func>
void TestRunner::RunTest(test_func func, const std::string& test_name)
{
    try
    {
        func();
        std::cerr << "PASSED: " << test_name << std::endl;
    }
    catch (const std::runtime_error & e)
    {
        ++fail_count;
        std::cerr << "FAIL: " << test_name << e.what() << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------
template <typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
std::ostream& operator << (std::ostream& os, const std::map<Key, Value>& map)
{
    os << "{";
    bool first = true;
    for (const auto& kv : map)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
void Assert(bool b, const std::string& hint);
//-------------------------------------------------------------------------------------------------
template<typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << " Assertion failed: " << std::endl;
        os << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}
//-------------------------------------------------------------------------------------------------
#endif // _TEST_RUNNER_H_