#include "test_runner.h"
#include "profile.h"
#include <array>
#include <iostream>
#include <iterator>
#include <utility>
#include <random>

using namespace std;

// TAirport should be enum with sequential items and last item TAirport::Last_
template <typename TAirport>
class AirportCounter {
public:
  AirportCounter() {
    data.fill(0);
  }

  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end)
      : AirportCounter()
  {
    for (; begin != end; ++begin) {
      Insert(*begin);
    }
  }

  size_t Get(TAirport airport) const {
    return data[static_cast<size_t>(airport)];
  }

  void Insert(TAirport airport) {
    ++GetRef(airport);
  }

  void EraseOne(TAirport airport) {
    --GetRef(airport);
  }

  void EraseAll(TAirport airport) {
    GetRef(airport) = 0;
  }

  static const size_t SIZE = static_cast<size_t>(TAirport::Last_);
  using Item = pair<TAirport, size_t>;
  using Items = array<Item, SIZE>;

  // any iterable can be returned, but std::array is enough for now
  Items GetItems() const {
    Items items;
    for (size_t airport_idx = 0; airport_idx < SIZE; ++airport_idx) {
      items[airport_idx] = {static_cast<TAirport>(airport_idx), data[airport_idx]};
    }
    return items;
  }

private:
  array<size_t, SIZE> data;

  size_t& GetRef(TAirport airport) {
    return data[static_cast<size_t>(airport)];
  }
};