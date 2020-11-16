#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

//#include "test_runner.h"

//----------------------------------------------------------------------------------------------------
class ReadingManager
{
public:
    ReadingManager() :
    people(MAX_USER_COUNT_ + 1, -1),
    pages(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count)
    {
        for (int i = people[user_id] + 1; i <= page_count; i++)
        {
            ++pages[i];
        }
        people[user_id] = page_count;
    }

    double Cheer(int user_id) const
    {
        if (people[user_id] == -1)
        {
            return 0;
        }

        if (pages[0] == 1)
        {
            return 1;
        }
        return static_cast<double>(pages[0] - pages[people[user_id]]) / static_cast<double>(pages[0] - 1);
    }
private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    std::vector<int> people;
    std::vector<int> pages;
};
//----------------------------------------------------------------------------------------------------
//void TestReadPage()
//{
//    {
//        ReadingManager manager;
//        ASSERT_EQUAL(manager.Cheer(1), 0.0, "add user_1");
//        manager.Read(1, 1);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "add user_1");
//    }
//    {
//        ReadingManager manager;
//        ASSERT_EQUAL(manager.Cheer(1), 0.0, "add user but cheer not existed_1");
//        manager.Read(1, 1);
//        ASSERT_EQUAL(manager.Cheer(2), 0.0, "add user but cheer not existed_2");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(1, 1);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "read twice_1");
//        manager.Read(1, 2);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "read twice_2");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(1, 1);
//        manager.Read(2, 2);
//        manager.Read(3, 3);
//        ASSERT_EQUAL(manager.Cheer(2), 0.5, "better than third_1");
//        manager.Read(4, 4);
//        ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0, "better than third_2");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(1, 1);
//        manager.Read(2, 2);
//        manager.Read(3, 3);
//        ASSERT_EQUAL(manager.Cheer(2), 0.5, "better than 2 third_1");
//        manager.Read(4, 4);
//        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0, "better than 2 third_2");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(1, 0);
//        manager.Read(2, 0);
//        manager.Read(3, 1);
//        manager.Read(4, 2);
//        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0, "read zero_1");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(1, 5);
//        manager.Read(2, 5);
//        manager.Read(3, 5);
//        manager.Read(4, 5);
//        ASSERT_EQUAL(manager.Cheer(3), 0.0, "all read the same_1");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(4, 5);
//        manager.Read(3, 4);
//        manager.Read(2, 3);
//        manager.Read(1, 2);
//        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0, "reverse order_1");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(4, 5);
//        manager.Read(3, 4);
//        manager.Read(4, 6);
//        manager.Read(3, 5);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0, "two users read two times_1");
//        ASSERT_EQUAL(manager.Cheer(3), 0.0, "two users read two times_2");
//        manager.Read(10, 2);
//        ASSERT_EQUAL(manager.Cheer(3), 0.5, "two users read two times_3");
//        ASSERT_EQUAL(manager.Cheer(4), 1.0, "two users read two times_4");
//    }
//    {
//        ReadingManager manager;
//        manager.Read(4, 5);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0, "only one user_1");
//        manager.Read(4, 6);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0, "only one user_2");
//        manager.Read(4, 100);
//        ASSERT_EQUAL(manager.Cheer(4), 1.0, "only one user_3");
//        ASSERT_EQUAL(manager.Cheer(3), 0.0, "only one user_4");
//        ASSERT_EQUAL(manager.Cheer(5), 0.0, "only one user_5");
//    }
//    {// ten users
//        ReadingManager manager;
//        manager.Read(1, 1);
//        manager.Read(2, 2);
//        manager.Read(3, 3);
//        manager.Read(4, 4);
//        manager.Read(5, 5);
//        manager.Read(6, 6);
//        manager.Read(7, 7);
//        manager.Read(8, 8);
//        manager.Read(9, 9);
//        manager.Read(100, 10);
//        manager.Read(111, 11);
//
//        ASSERT_EQUAL(manager.Cheer(1), 0.0, "ten users_1");
//        ASSERT_EQUAL(manager.Cheer(2), 0.1, "ten users_2");
//        ASSERT_EQUAL(manager.Cheer(3), 0.2, "ten users_3");
//        ASSERT_EQUAL(manager.Cheer(4), 0.3, "ten users_4");
//        ASSERT_EQUAL(manager.Cheer(5), 0.4, "ten users_5");
//        ASSERT_EQUAL(manager.Cheer(6), 0.5, "ten users_6");
//        ASSERT_EQUAL(manager.Cheer(7), 0.6, "ten users_7");
//        ASSERT_EQUAL(manager.Cheer(8), 0.7, "ten users_8");
//        ASSERT_EQUAL(manager.Cheer(9), 0.8, "ten users_9");
//        ASSERT_EQUAL(manager.Cheer(100), 0.9, "ten users_10");
//        ASSERT_EQUAL(manager.Cheer(111), 1.0, "ten users_11");
//        ASSERT_EQUAL(manager.Cheer(12), 0.0, "ten users_12");
//    }
//    {
//        ReadingManager manager;
//
//        ASSERT_EQUAL(manager.Cheer(1), 0.0, "cheer twice_1");
//        ASSERT_EQUAL(manager.Cheer(1), 0.0, "cheer twice_2");
//        manager.Read(1, 1);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "cheer twice_3");
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "cheer twice_4");
//
//        ASSERT_EQUAL(manager.Cheer(2), 0, "cheer twice_5");
//    }
//    {
//        const int MAX_USER_COUNT = 100'000;
//        ReadingManager manager;
//        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0, "max ID_1");
//        manager.Read(MAX_USER_COUNT, 1);
//        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0, "max ID_2");
//    }
//    {
//        ReadingManager manager;
//        ASSERT_EQUAL(manager.Cheer(1), 0.0, "max page_1");
//        manager.Read(1, 1000);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "max page_2");
//    }
//    {
//        const int MAX_USER_COUNT = 100'000;
//        ReadingManager manager;
//        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0, "max ID and max page_1");
//        manager.Read(MAX_USER_COUNT, 1000);
//        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0, "max ID and max page_2");
//    }
//    {
//        ReadingManager manager;
//        ASSERT_EQUAL(manager.Cheer(0), 0.0, "zero ID_1");
//        manager.Read(0, 1000);
//        ASSERT_EQUAL(manager.Cheer(0), 1.0, "zero ID_2");
//    }
//    {// from coursera (https://www.coursera.org/learn/c-plus-plus-red/programming/e72ST/eliektronnaia-knigha/discussions/threads/hLK3cT0AEemHtRKqiMW_lA)
//        ReadingManager manager;
//        manager.Read(1, 1);
//        manager.Read(1, 3);
//        manager.Read(2, 2);
//        ASSERT_EQUAL(manager.Cheer(1), 1.0, "from coursera_1");
//        ASSERT_EQUAL(manager.Cheer(2), 0.0, "from coursera_2");
//    }
//}
//----------------------------------------------------------------------------------------------------
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

//    TestRunner tr;
//    tr.RunTest(TestReadPage, "TestReadPage");

    ReadingManager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        std::string query_type;
        std::cin >> query_type;

        int user_id;
        std::cin >> user_id;

        if (query_type == "READ")
        {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else
        if (query_type == "CHEER")
        {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------