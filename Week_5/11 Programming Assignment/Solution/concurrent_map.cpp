#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <future>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <cmath>

//----------------------------------------------------------------------------------------------------
template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(std::is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access
    {
        Access(const K& key, std::pair<std::mutex, std::map<K, V>>& bucket_content) :
                guard(bucket_content.first), ref_to_value(bucket_content.second[key])
        {
        }
        std::lock_guard<std::mutex> guard;
        V& ref_to_value;
    };
    explicit ConcurrentMap(size_t bucket_count);

    Access operator[](const K& key);

    std::map<K, V> BuildOrdinaryMap();
private:
    std::vector<std::pair<std::mutex, std::map<K,V>>> data;
};
//----------------------------------------------------------------------------------------------------
template <typename K, typename V>
ConcurrentMap<K,V>::ConcurrentMap(size_t bucket_count) : data(bucket_count)
{

}
//----------------------------------------------------------------------------------------------------
template <typename K, typename V>
typename ConcurrentMap<K,V>::Access ConcurrentMap<K,V>::operator[](const K& key)
{
    auto& bucket = data[(key < 0 ? -key : key) % data.size()];
    return {key, bucket};
}
//----------------------------------------------------------------------------------------------------
template <typename K, typename V>
std::map<K, V> ConcurrentMap<K,V>::BuildOrdinaryMap()
{
    std::map<K, V> temp;
    for (auto& [mtx, mapping] : data)
    {
        std::lock_guard<std::mutex> lck_guard{mtx};
        temp.insert(begin(mapping), end(mapping));
    }
    return temp;
}
//----------------------------------------------------------------------------------------------------
void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count, int key_count)
{
    auto kernel = [&cm, key_count](int seed)
    {
        std::vector<int> updates(key_count);
        std::iota(std::begin(updates), std::end(updates), -key_count / 2);
        std::shuffle(std::begin(updates), std::end(updates), std::default_random_engine(seed));

        for (int i = 0; i < 2; ++i)
        {
            for (auto key : updates)
            {
                cm[key].ref_to_value++;
            }
        }
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i)
    {
        futures.push_back(std::async(kernel, i));
    }
}
//----------------------------------------------------------------------------------------------------
void TestConcurrentUpdate()
{
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto& [k, v] : result)
    {
        ASSERT_EQUAL(v, 6);
    }
}
//----------------------------------------------------------------------------------------------------
void TestReadAndWrite()
{
    ConcurrentMap<size_t, std::string> cm(5);

    auto updater = [&cm]
    {
        for (size_t i = 0; i < 50000; ++i)
        {
            cm[i].ref_to_value += 'a';
        }
    };

    auto reader = [&cm]
    {
        std::vector<std::string> result(50000);
        for (size_t i = 0; i < result.size(); ++i)
        {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = std::async(updater);
    auto r1 = std::async(reader);
    auto u2 = std::async(updater);
    auto r2 = std::async(reader);

    u1.get();
    u2.get();

    for (auto f : {&r1, &r2})
    {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const std::string& s)
        {
            return s.empty() || s == "a" || s == "aa";
        }));
    }
}
//----------------------------------------------------------------------------------------------------
void TestSpeedup()
{
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestConcurrentUpdate, "TestConcurrentUpdate");
    tr.RunTest(TestReadAndWrite, "TestReadAndWrite");
    tr.RunTest(TestSpeedup, "TestSpeedup");
    return 0;
}
//----------------------------------------------------------------------------------------------------