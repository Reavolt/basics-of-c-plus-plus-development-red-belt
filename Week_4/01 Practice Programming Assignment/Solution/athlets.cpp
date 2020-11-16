#include <iostream>
#include <list>
#include <vector>

//----------------------------------------------------------------------------------------------------
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int SPORTSMEN_COUNT = 100'000;

    int pair_count = 0;
    std::cin >> pair_count;

    std::list<int> queue;
    std::vector<std::list<int>::iterator> positions(SPORTSMEN_COUNT, std::end(queue));

    int newSportsman, nextSportsman;
    for (int i = 0; i < pair_count; ++i)
    {
        std::cin >> newSportsman >> nextSportsman;
        positions[newSportsman] = queue.insert(positions[nextSportsman], newSportsman);
    }

    for (int x : queue)
    {
        std::cout << x << '\n';
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------