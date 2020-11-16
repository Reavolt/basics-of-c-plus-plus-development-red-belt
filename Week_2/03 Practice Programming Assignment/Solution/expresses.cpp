#include "test_runner.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

//-------------------------------------------------------------------------------------------------
class RouteManager
{
public:
  void AddRoute(int start, int finish)
  {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }

  int FindNearestFinish(int start, int finish) const
  {
        int result = abs(start - finish);

        if (reachable_lists_.count(start) < 1)
        {
            return result;
        }

        const std::set<int>& reachable_stations = reachable_lists_.at(start);
        const auto finish_pos = reachable_stations.lower_bound(finish);
        if (finish_pos != end(reachable_stations))
        {
          result = std::min(result, abs(finish - *finish_pos));
        }
        if (finish_pos != begin(reachable_stations))
        {
          result = std::min(result, abs(finish - *prev(finish_pos)));
        }
        return result;
  }
private:
    std::map<int, std::set<int>> reachable_lists_;
};
//-------------------------------------------------------------------------------------------------
int main()
{
    RouteManager routes;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        std::string query_type;
        std::cin >> query_type;

        int start, finish;
        std::cin >> start >> finish;

        if (query_type == "ADD")
        {
            routes.AddRoute(start, finish);
        }
        else
        if (query_type == "GO")
        {
            std::cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------