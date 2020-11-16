#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
void Swap(T* first, T* second) {
  auto tmp = *first;
  *first = *second;
  *second = tmp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
  sort(begin(pointers), end(pointers), [](T* lhs, T* rhs) {
    return *lhs < *rhs;
  });
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
  auto source_begin = source;
  auto source_end = source + count;
  auto dest_begin = destination;
  auto dest_end = destination + count;
  if (dest_begin >= source_end || dest_end <= source_begin) {
    reverse_copy(source_begin, source_end, dest_begin);
  } else if (dest_begin > source_begin) {
    /* Случай, когда целевая область лежит правее исходной
     * |   |   |   |d_6|d_5|d_4|d_3|d_2|d_1|
     * |s_1|s_2|s_3|s_4|s_5|s_6|   |   |   |
     * */
    for (size_t i = 0; source_begin + i < dest_begin; ++i) {
      *(dest_end - i - 1) = *(source_begin + i);
    }
    reverse(dest_begin, source_end);
  } else {
    /* Случай, когда целевая область лежит левее исходной
     * |d_6|d_5|d_4|d_3|d_2|d_1|   |   |   |
     * |   |   |   |s_1|s_2|s_3|s_4|s_5|s_6|
     * */
    for (size_t i = 0; source_end - i - 1 >= dest_end; ++i) {
      *(dest_begin + i) = *(source_end - i - 1);
    }
    reverse(source_begin, dest_end);
  }
}

// Шаблонная функция ReversedCopy — альтернативное решение:

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
  auto source_begin = source;
  auto source_end = source + count;
  auto dest_begin = destination;

  for (size_t i = 0; i < count; i++) {
    T* source_curr = source_end - i - 1;
    T* dest_curr = dest_begin + i;

    // Не пересекающаяся часть диапазонов — смело "копируем" элемент на
    // требуемую позицию
    if (dest_curr < source_begin || dest_curr >= source_end) {
      *dest_curr = *source_curr;
    // Пересекающаяся часть диапазонов — разворачиваем её до/относительно центра
    } else if (dest_curr < source_curr) {
      Swap(source_curr, dest_curr);
    }
  }
}