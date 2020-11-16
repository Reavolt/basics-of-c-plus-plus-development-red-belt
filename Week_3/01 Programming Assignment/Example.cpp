#include "test_runner.h"

#include <algorithm>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  queue<T*> free;
  set<T*> allocated;
};

template <typename T>
T* ObjectPool<T>::Allocate() {
  if (free.empty()) {
    free.push(new T);
  }
  auto ret = free.front();
  free.pop();
  allocated.insert(ret);
  return ret;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
  if (free.empty()) {
    return nullptr;
  }
  return Allocate();
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
  if (allocated.find(object) == allocated.end()) {
    throw invalid_argument("");
  }
  allocated.erase(object);
  free.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
  for (auto x : allocated) {
    delete x;
  }
  while (!free.empty()) {
    auto x = free.front();
    free.pop();
    delete x;
  }
}