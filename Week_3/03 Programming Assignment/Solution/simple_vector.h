#pragma once

#include <cstdlib>
#include <algorithm>

//----------------------------------------------------------------------------------------------------
template <typename T>
class SimpleVector
{
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);
private:
    T* elements{};
    size_t size{};
    size_t capacity{};
};
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : elements(new T[size]{}), size(size), capacity(size)
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>::~SimpleVector()
{
    delete[] elements;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
T& SimpleVector<T>::operator[](size_t index)
{
    return elements[index];
}
//----------------------------------------------------------------------------------------------------
template <typename T>
T* SimpleVector<T>::begin()
{
    return elements;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
T* SimpleVector<T>::end()
{
    return elements + size;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t SimpleVector<T>::Size() const
{
    return size;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
size_t SimpleVector<T>::Capacity() const
{
    return capacity;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void SimpleVector<T>::PushBack(const T& value)
{
    if(Capacity() == 0)
    {
        T* temp = new T[++capacity]{value};
        ++size;
        elements = temp;
    }
    else
    {
        if (Size() == Capacity())
        {
            T *temp = new T[2 * capacity]{};
            capacity *= 2;

            for (size_t i = 0; i <= size; i++)
            {
                temp[i] = elements[i];
            }
            delete[] elements;
            elements = temp;
        }
        elements[size++] = value;
    }
}
//----------------------------------------------------------------------------------------------------