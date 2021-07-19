#include <string>
#include <vector>
#include <iostream>
#include <exception>

using namespace std;

template<typename T>
class Deque {
 public:
    bool   Empty() const { return _front.empty() && _back.empty(); }
    size_t Size()  const { return _front.size() + _back.size(); }

    const T& operator[] (size_t i) const { return AtImpl(i); }
    T&       operator[] (size_t i)       { return AtImpl(i); }

    const T& At(size_t i) const {
        CheckIndex(i);
        return AtImpl(i);
    }

    T& At(size_t i) {
        CheckIndex(i);
        return AtImpl(i);
    }

    const T& Front() const { return (_front.empty() ? _back.front() : _front.back()); }
    T&       Front()       { return (_front.empty() ? _back.front() : _front.back()); }

    const T& Back() const { return (_back.empty() ? _front.front() : _back.back()); }
    T&       Back()       { return (_back.empty() ? _front.front() : _back.back()); }

    void PushFront(const T& elem) { _front.push_back(elem); }
    void PushBack(const T& elem)  { _back.push_back(elem); }

    //  Deque: |_____/_____|
    //         \     /\    /
    // reversed _front _back
 private:
    void CheckIndex(size_t i) const {
        if (i >= Size())
        throw out_of_range("Index is out of range");
    }

    const T& AtImpl(size_t i) const {
        return (i < _front.size() ? _front[_front.size() - i - 1] : _back[i - _front.size()]);
    }

    T& AtImpl(size_t i) {
        return (i < _front.size() ? _front[_front.size() - i - 1] : _back[i - _front.size()]);
    }

 protected:
    vector<T> _front;
    vector<T> _back;
};
