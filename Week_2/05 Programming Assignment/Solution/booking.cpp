#include <iostream>
#include <cstdint>
#include <map>
#include <queue>

//----------------------------------------------------------------------------------------------------
struct booking
{
    int64_t time;
    int client_id;
    int room_count;
};
//----------------------------------------------------------------------------------------------------
class hotel_info
{
public:
    void book(const booking& booking)
    {
        booking_history.push(booking);
        room_count += booking.room_count;
        ++client_booking_counts[booking.client_id];
    }

    int clients(const int64_t& current_time)
    {
        remove_old_books(current_time);
        return client_booking_counts.size();
    }

    int rooms(const int64_t& current_time)
    {
        remove_old_books(current_time);
        return room_count;
    }
private:
    static const int SECONDS_IN_DAYS = 86400;

    std::queue<booking> booking_history;
    int room_count = 0;
    std::map<int, int> client_booking_counts;

    void pop_booking()
    {
        const booking& booking = booking_history.front();
        room_count -= booking.room_count;
        const auto client_stat_it = client_booking_counts.find(booking.client_id);

        if (--client_stat_it->second == 0)
        {
            client_booking_counts.erase(client_stat_it);
        }
        booking_history.pop();
    }

    void remove_old_books(const int64_t& current_time)
    {
        while (!booking_history.empty() && booking_history.front().time <= current_time - SECONDS_IN_DAYS)
        {
            pop_booking();
        }
    }
};
//----------------------------------------------------------------------------------------------------
class booking_manager
{
public:
    void book(const int64_t& time, const std::string& hotel_name, int client_id, short int room_count)
    {
        current_time = time;
        hotels[hotel_name].book({time, client_id, room_count});
    }

    int clients(const std::string& hotel_name)
    {
        return hotels[hotel_name].clients(current_time);
    }

    int rooms(const std::string& hotel_name)
    {
        return hotels[hotel_name].rooms(current_time);
    }
private:
    int64_t current_time = 0;
    std::map<std::string, hotel_info> hotels;
};
//----------------------------------------------------------------------------------------------------
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    booking_manager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        std::string query_type;
        std::cin >> query_type;

        if (query_type == "BOOK")
        {
            int64_t time = 0;
            std::cin >> time;

            std::string hotel_name;
            std::cin >> hotel_name;

            int client_id = 0;
            std::cin >> client_id;

            short int room_count = 0;
            std::cin >> room_count;

            manager.book(time, hotel_name, client_id, room_count);
        }
        else
        if (query_type == "CLIENTS")
        {
            std::string hotel_name;
            std::cin >> hotel_name;

            std::cout << manager.clients(hotel_name) << "\n";
        }
        else
        if (query_type == "ROOMS")
        {
            std::string hotel_name;
            std::cin >> hotel_name;

            std::cout << manager.rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------