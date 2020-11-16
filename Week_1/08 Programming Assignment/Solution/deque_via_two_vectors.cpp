//#include "test_runner.h"

#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

//-------------------------------------------------------------------------------------------------
template <typename T>
class Deque
{
public:
    Deque() = default;

    void PushFront(const T& value)
    {
        front.push_back(value);
    }

    void PushBack(const T& value)
    {
        back.push_back(value);
    }

    bool Empty() const
    {
        return (front.empty() && back.empty());
    }

    size_t Size() const
    {
        return (front.size() + back.size());
    }

    const T& Front() const
    {
        if (front.empty())
        {
            return back.front();
        }
        return front.back();
    }    
    
    T& Front()
    {
        if (front.empty())
        {
            return const_cast<T&>(std::as_const(back).front());
        }
        return const_cast<T&>(std::as_const(front).back());
    }

    const T& Back() const
    {
        if (back.empty())
        {
            return front.front();
        }
        return back.back();
    }   
    
    T& Back()
    {
        if (back.empty())
        {
            return const_cast<T&>(std::as_const(front).front());
        }
        return const_cast<T&>(std::as_const(back).back());
    }

    const T& At(const size_t index) const
    {
        if (index >= Size())
        {
            throw std::out_of_range("out_of_range");
        }
        
        if (index < front.size()) 
        {
            return front[(front.size() - 1) - index];
        }
        return back[index - front.size()];
    }
    
    T& At(const size_t index) 
    {
        if (index >= Size())
        {
            throw std::out_of_range("out_of_range");
        }
        
        if (index < front.size()) 
        {
            return const_cast<T&>(std::as_const(front)[(front.size() - 1) - index]);
        }
        return const_cast<T&>(std::as_const(back)[index - front.size()]);
    }

    const T& operator[](size_t index) const
    {
        if (index < front.size())
        {
            return front[(front.size() - 1) - index];
        }
        return back[index - front.size()];
    }

    T& operator[](size_t index)
    {
        if (index < front.size()) 
        {
            return const_cast<T&>(std::as_const(front)[(front.size() - 1) - index]);
        }
        return const_cast<T&>(std::as_const(back)[index - front.size()]);
    }
private:
    std::vector<T> front;
    std::vector<T> back;
};
//-------------------------------------------------------------------------------------------------
//void TestDeque()
//{
//    //tests At()
//    {
//        Deque<int> test;
//        try
//        {
//            test.PushFront(1);
//            ASSERT_EQUAL(test.At(0), 1);
//        }
//        catch (const std::out_of_range & err)
//        {
//            std::cerr << err.what() << std::endl;
//        }
//        test.PushFront(2);
//        ASSERT_EQUAL(test.At(0), 2);
//        ASSERT_EQUAL(test.At(1), 1);
//        test.PushBack(3);
//        ASSERT_EQUAL(test.At(2), 3);
//    }
//    //tests operator[]
//    {
//        Deque<int> test;
//        try
//        {
//            test.PushFront(1);
//            ASSERT_EQUAL(test[0], 1);
//        }
//        catch (const std::out_of_range & err)
//        {
//            std::cerr << err.what() << std::endl;
//        }
//        test.PushFront(2);
//        ASSERT_EQUAL(test[0], 2);
//        ASSERT_EQUAL(test[1], 1);
//        test.PushBack(3);
//        ASSERT_EQUAL(test[2], 3);
//    }    
//    
//    //tests Back() and Front()
//    {
//        Deque<int> test;
//        try
//        {
//            test.PushFront(1);
//            ASSERT_EQUAL(test.Back(), 1);
//            ASSERT_EQUAL(test.Front(), 1);
//        }
//        catch (const std::out_of_range & err)
//        {
//            std::cerr << err.what() << std::endl;
//        }
//        test.PushFront(2);
//        ASSERT_EQUAL(test.Back(), 1);
//        ASSERT_EQUAL(test.Front(), 2);
//        test.PushBack(3);
//        ASSERT_EQUAL(test.Back(), 3);
//        ASSERT_EQUAL(test.Front(), 2);
//        test.PushBack(4);
//        ASSERT_EQUAL(test.Back(), 4);
//        ASSERT_EQUAL(test.Front(), 2);
//    }
//
//    //tests const
//    {
//        Deque<int> test;
//        try
//        {
//            test.PushFront(1);
//            test[0] = 1;
//            ASSERT_EQUAL(test[0], 1);
//            ASSERT_EQUAL(test.Front(), 1);
//        }
//        catch (const std::out_of_range & err)
//        {
//            std::cerr << err.what() << std::endl;
//        }
//        test.PushFront(2);
//        ASSERT_EQUAL(test.Back(), 1);
//        ASSERT_EQUAL(test.Front(), 2);
//        test.PushBack(3);
//        ASSERT_EQUAL(test.Back(), 3);
//        ASSERT_EQUAL(test.Front(), 2);
//        test.PushBack(4);
//        ASSERT_EQUAL(test.Back(), 4);
//        ASSERT_EQUAL(test.Front(), 2);
//    }
//}
//-------------------------------------------------------------------------------------------------
int main()
{
    //TestRunner tr;
    //RUN_TEST(tr, TestDeque);
    return 0;
}
//-------------------------------------------------------------------------------------------------