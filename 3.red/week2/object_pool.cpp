#include "test_runner.h"
//#include "../../Utilities/Allocations.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
 public:
    T* Allocate()
    {
        T* result;
        if (!freed.empty())
        {
            result = *(malloced.insert(freed.front()).first);
            freed.pop_front();
        } else {
            //T* ptrT = new T;
            result = *(malloced.insert(new T).first);
            //all.insert(ptrT);
        }
        return result;
    }
    T* TryAllocate()
    {
        if (!freed.empty())
        {
            T* result = *(malloced.insert(freed.front()).first);;
            freed.pop_front();
            return result;
        }
        
        return nullptr;
    }

    void Deallocate(T* object)
    {
        const auto it = malloced.find(object);
        if (it != malloced.end())
        {
            freed.push_back(*it);
            malloced.erase(it);
        }
        else throw invalid_argument("");
    }

    ~ObjectPool()
    {
        while (!malloced.empty())
        {
            delete *(malloced.begin());
            malloced.erase(malloced.begin());
        }
        while (!freed.empty())
        {
            delete freed.back();
            freed.pop_back();
        }
    }

 private:
    //set<T*>   all;
    set<T*> malloced;
    deque<T*> freed;
};


void TestObjectPool() {

    ObjectPool<string> pool;

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

int main() {
    TestRunner tr;
    //PrintMemoryUsage();
    RUN_TEST(tr, TestObjectPool);
    //PrintMemoryUsage();
    return 0;
}


/*
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
*/
