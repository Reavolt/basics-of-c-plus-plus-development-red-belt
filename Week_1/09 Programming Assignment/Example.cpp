#include <vector>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

//Решение проблемы с тестом TestLooping
//Функция TestLooping в заготовке решения выглядит так

void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

//Давайте заглянем внутрь файла test_runner.h и посмотрим, во что раскроется макрос ASSERT_EQUAL:

void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os << x << ' ';
    }
    os << '\n';
  }

  // ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
  // раскроется в код ниже:
  {
    ostringstream os;
    os << os.str() << " != " << "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n" << ", " 
       << "[здесь будет имя вашего файла]" << ":" << 45;
    AssertEqual(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n", os.str())   ;
  }
}

//Теперь становится понятно, почему TestLooping может вести себя неадекватно: переменная os, объявленная в теле 
//макроса, перекрывает переменную os из функции TestLooping. Решить эту проблему несложно — надо в теле макроса 
//выбрать такое имя переменной, которое с малой вероятностью будет использоваться в пользовательском коде:

#define ASSERT_EQUAL(x, y) {                          \
  ostringstream __assert_equal_private_os;            \
  __assert_equal_private_os                           \
    << #x << " != " << #y << ", "                     \
    << __FILE__ << ":" << __LINE__;                   \
  AssertEqual(x, y, __assert_equal_private_os.str()); \
}