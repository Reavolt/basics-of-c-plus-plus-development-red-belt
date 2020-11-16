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
    SimpleVector(const SimpleVector& sv);
    SimpleVector(SimpleVector&& sv);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);
    void PushBack(T&& value);

    SimpleVector& operator=(const SimpleVector& rhs);
    SimpleVector& operator=(SimpleVector&& rhs) noexcept;
private:
    size_t size{};
    size_t capacity{};
    T* elements{};
};
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>::SimpleVector(size_t size) : size(size), capacity(size * 2), elements(new T[capacity]{})
{

}
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector& sv) : size(sv.size), capacity(sv.capacity), elements(new T[sv.capacity]{})
{
    std::copy(sv.begin(), sv.end(), begin());
}
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector&& sv) : size(sv.size), capacity(sv.capacity), elements(sv.elements)
{
    sv.size = 0;
    sv.capacity = 0;
    sv.elements = nullptr;
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
const T* SimpleVector<T>::begin() const
{
    return elements;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
const T* SimpleVector<T>::end() const
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
    if (size == capacity)
    {
        auto tmp = new T[(capacity += 1) *= 2];

        for (size_t i = 0; i < size; ++i)
        {
            tmp[i] = elements[i];
        }
        delete[] elements;
        elements = tmp;
    }
    elements[++size - 1] = value;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
void SimpleVector<T>::PushBack(T&& value)
{
    if (size == capacity)
    {
        auto tmp = new T[(capacity += 1) *= 2];

        for (size_t i = 0; i < size; ++i)
        {
            tmp[i] = std::move(elements[i]);
        }
        delete[] elements;
        elements = std::move(tmp);
    }
    elements[++size - 1] = std::move(value);
}
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector<T>& rhs)
{
    if (this == &rhs) return *this;

    if (rhs.size <= capacity)
    {
        std::copy(rhs.begin(), rhs.end(), begin());
        size = rhs.size;
    }
    else
    {
        SimpleVector<T> tmp(rhs);
        std::swap(tmp.elements, elements);
        std::swap(tmp.size, size);
        std::swap(tmp.capacity, capacity);
    }
    return *this;
}
//----------------------------------------------------------------------------------------------------
template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(SimpleVector<T>&& rhs) noexcept
{
    std::swap(rhs.elements, elements);
    std::swap(rhs.size, size);
    std::swap(rhs.capacity, capacity);
}
//----------------------------------------------------------------------------------------------------