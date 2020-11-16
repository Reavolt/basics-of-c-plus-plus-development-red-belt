#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Table {
 private:
  vector<vector<T>> data;

 public:
  Table(size_t rows, size_t columns) {
    Resize(rows, columns);
  }

  const vector<T>& operator [] (size_t idx) const {
    return data[idx];
  }

  vector<T>& operator [] (size_t idx) {
    return data[idx];
  }

  void Resize(size_t rows, size_t columns) {
    data.resize(rows);
    for (auto& item : data) {
      item.resize(columns);
    }
  }

  pair<size_t, size_t> Size() const {
    return {data.size(), (data.empty() ? 0 : data[0].size())};
  }

};