#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

//----------------------------------------------------------------------------------------------------
template <typename TAirport>
class AirportCounter
{
public:
    static const size_t SIZE = static_cast<size_t>(TAirport::Last_);
    using Item = std::pair<TAirport, size_t>;
    using Items = std::array<Item, SIZE>;
public:
    AirportCounter();
    template <typename TIterator>
    AirportCounter(TIterator begin, TIterator end);

    size_t Get(TAirport airport) const;
    void Insert(TAirport airport);

    void EraseOne(TAirport airport);
    void EraseAll(TAirport airport);

    Items GetItems() const;
private:
    std::array<size_t, SIZE> airports;
};
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
AirportCounter<TAirport>::AirportCounter()
{
    airports.fill(0);
}
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
template <typename TIterator>
AirportCounter<TAirport>::AirportCounter(TIterator begin, TIterator end)
{
    airports.fill(0);
    while(begin != end)
    {
        Insert(*begin);
        begin++;
    }
}
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
size_t AirportCounter<TAirport>::Get(TAirport airport) const
{
    return airports[static_cast<size_t>(airport)];
}
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
void AirportCounter<TAirport>::Insert(TAirport airport)
{
    ++airports[static_cast<size_t>(airport)];
}
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
void AirportCounter<TAirport>::EraseOne(TAirport airport)
{
    --airports[static_cast<size_t>(airport)];
}
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
void AirportCounter<TAirport>::EraseAll(TAirport airport)
{
    airports[static_cast<size_t>(airport)] = 0;
}
//----------------------------------------------------------------------------------------------------
template <typename TAirport>
typename AirportCounter<TAirport>::Items AirportCounter<TAirport>::GetItems() const
{
    Items items;
    for (size_t i = 0; i < airports.size(); ++i)
    {
        items[i] = {static_cast<TAirport>(i), airports[i]};
    }
    return items;
}
//----------------------------------------------------------------------------------------------------
void TestMoscow()
{
    enum class MoscowAirport
    {
        VKO,
        SVO,
        DME,
        ZIA,
        Last_
    };

    const std::vector<MoscowAirport> airports =
    {
            MoscowAirport::SVO,
            MoscowAirport::VKO,
            MoscowAirport::ZIA,
            MoscowAirport::SVO,
    };
    AirportCounter<MoscowAirport> airport_counter(begin(airports), end(airports));

    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 1);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 2);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::DME), 0);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::ZIA), 1);

    using Item = AirportCounter<MoscowAirport>::Item;
    std::vector<Item> items;
    for (const auto& item : airport_counter.GetItems())
    {
        items.push_back(item);
    }
    ASSERT_EQUAL(items.size(), 4);

    #define ASSERT_EQUAL_ITEM(idx, expected_enum, expected_count) \
    do                                                          \
    { \
        ASSERT_EQUAL(static_cast<size_t>(items[idx].first), static_cast<size_t>(MoscowAirport::expected_enum)); \
        ASSERT_EQUAL(items[idx].second, expected_count); \
    }                                                         \
    while (false)

    ASSERT_EQUAL_ITEM(0, VKO, 1);
    ASSERT_EQUAL_ITEM(1, SVO, 2);
    ASSERT_EQUAL_ITEM(2, DME, 0);
    ASSERT_EQUAL_ITEM(3, ZIA, 1);

    airport_counter.Insert(MoscowAirport::VKO);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 2);

    airport_counter.EraseOne(MoscowAirport::SVO);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::SVO), 1);

    airport_counter.EraseAll(MoscowAirport::VKO);
    ASSERT_EQUAL(airport_counter.Get(MoscowAirport::VKO), 0);
}
//----------------------------------------------------------------------------------------------------
enum class SmallCountryAirports
{
    Airport_1,
    Airport_2,
    Airport_3,
    Airport_4,
    Airport_5,
    Airport_6,
    Airport_7,
    Airport_8,
    Airport_9,
    Airport_10,
    Airport_11,
    Airport_12,
    Airport_13,
    Airport_14,
    Airport_15,
    Last_
};
//----------------------------------------------------------------------------------------------------
void TestManyConstructions()
{
    std::default_random_engine rnd(20180623);
    std::uniform_int_distribution<size_t> gen_airport(0,
        static_cast<size_t>(SmallCountryAirports::Last_) - 1);

    std::array<SmallCountryAirports, 2> airports;
    for (auto& x : airports)
    {
        x = static_cast<SmallCountryAirports>(gen_airport(rnd));
    }

    uint64_t total = 0;
    for (int step = 0; step < 100'000'000; ++step)
    {
        AirportCounter<SmallCountryAirports> counter(begin(airports), end(airports));
        total += counter.Get(SmallCountryAirports::Airport_1);
    }
    ASSERT(total < 1000);
}
//----------------------------------------------------------------------------------------------------
enum class SmallTownAirports
{
    Airport_1,
    Airport_2,
    Last_
};
//----------------------------------------------------------------------------------------------------
void TestManyGetItems()
{
    std::default_random_engine rnd(20180701);
    std::uniform_int_distribution<size_t> gen_airport(0,
        static_cast<size_t>(SmallTownAirports::Last_) - 1);

    std::array<SmallTownAirports, 2> airports;
    for (auto& x : airports)
    {
        x = static_cast<SmallTownAirports>(gen_airport(rnd));
    }

    uint64_t total = 0;
    for (int step = 0; step < 100'000'000; ++step)
    {
        AirportCounter<SmallTownAirports> counter(begin(airports), end(airports));
        total += counter.Get(SmallTownAirports::Airport_1);

        for (const auto [airport, count] : counter.GetItems())
        {
            total += count;
        }
    }
    // Assert to use variable total so that compiler doesn't optimize it out
    ASSERT(total > 0);
}
//----------------------------------------------------------------------------------------------------
void TestMostPopularAirport()
{
    std::default_random_engine rnd(20180624);
    std::uniform_int_distribution<size_t> gen_airport(0,
        static_cast<size_t>(SmallCountryAirports::Last_) - 1);

    std::array<std::pair<SmallCountryAirports, SmallCountryAirports>, 1000> dayly_flight_report;
    for (auto& x : dayly_flight_report)
    {
        x =
        {
            static_cast<SmallCountryAirports>(gen_airport(rnd)),
            static_cast<SmallCountryAirports>(gen_airport(rnd))
        };
    }

    const int days_to_explore = 365 * 500;

    std::vector<SmallCountryAirports> most_popular(days_to_explore);

    for (int day = 0; day < days_to_explore; ++day)
    {
        AirportCounter<SmallCountryAirports> counter;
        for (const auto& [source, dest] : dayly_flight_report)
        {
            counter.Insert(source);
            counter.Insert(dest);
        }

        const auto items = counter.GetItems();
        most_popular[day] = max_element(std::begin(items), std::end(items), [](auto lhs, auto rhs)
        {
            return lhs.second < rhs.second;
        })->first;
    }

    ASSERT(all_of(begin(most_popular), end(most_popular), [&](SmallCountryAirports a)
    {
        return a == most_popular.front();
    }));
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;

    LOG_DURATION("Total tests duration");
    tr.RunTest(TestMoscow, "TestMoscow");
    tr.RunTest(TestManyConstructions, "TestManyConstructions");
    tr.RunTest(TestManyGetItems, "TestManyGetItems");
    tr.RunTest(TestMostPopularAirport, "TestMostPopularAirport");
    return 0;
}
//----------------------------------------------------------------------------------------------------