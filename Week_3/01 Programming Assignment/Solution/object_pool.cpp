#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <memory>

#include "test_runner.h"

//----------------------------------------------------------------------------------------------------
template <typename T>
class ObjectPool
{
public:
    T* Allocate()
    {
        if (!released_objects.empty())
        {
            auto ro_ptr = released_objects.front();
            allocated_objects.insert(ro_ptr);
            released_objects.pop_front();
            return ro_ptr;
        }
        T* t_ptr = new T;
        allocated_objects.insert(t_ptr);
        return t_ptr;
    }

    T* TryAllocate()
    {
        if (released_objects.empty())
        {
            return nullptr;
        }
        return Allocate();
    }

    void Deallocate(T* object)
    {
        if (allocated_objects.find(object) == allocated_objects.end())
        {
            throw std::invalid_argument("");
        }
        released_objects.push_back(*allocated_objects.find(object));
        allocated_objects.erase(object);
    }

    ~ObjectPool()
    {
        std::for_each(allocated_objects.begin(), allocated_objects.end(), std::default_delete<T>());
        std::for_each(released_objects.begin(), released_objects.end(), std::default_delete<T>());
    }
private:
    std::set<T*> allocated_objects;
    std::deque<T*> released_objects;
};
//----------------------------------------------------------------------------------------------------
void TestObjectPool()
{
    ObjectPool<std::string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}
//----------------------------------------------------------------------------------------------------
int main()
{
    TestRunner tr;
    tr.RunTest(TestObjectPool, "TestObjectPool");
    return 0;
}
//----------------------------------------------------------------------------------------------------