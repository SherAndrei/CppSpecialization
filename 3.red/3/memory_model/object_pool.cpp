#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

#include "test_runner.h"

using namespace std;

template <class T>
class ObjectPool {
 public:
    T* Allocate() {
        T* result;
        if (!freed.empty()) {
            result = *(malloced.insert(freed.front()).first);
            freed.pop_front();
        } else {
            result = *(malloced.insert(new T).first);
        }
        return result;
    }

    T* TryAllocate() {
        if (freed.empty())
            return nullptr;
        return Allocate();
    }

    void Deallocate(T* object) {
        const auto it = malloced.find(object);
        if (it == malloced.end())
            throw invalid_argument("");
        freed.push_back(object);
        malloced.erase(it);
    }

    ~ObjectPool() {
        for (auto p : malloced)
            delete p;
        while (!freed.empty()) {
            delete freed.back();
            freed.pop_back();
        }
    }

 private:
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
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
