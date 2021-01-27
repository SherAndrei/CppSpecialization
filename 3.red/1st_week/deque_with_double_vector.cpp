#include <string>
#include <vector>
#include <iostream>
#include <exception>

using namespace std;

#define CONST_TO_NON_CONST(my_class, member_func) \
    const_cast<T&>(static_cast<const my_class&>(*this)member_func)

template<typename T>
class Deque {
 public:
    Deque() = default;
    bool   Empty() const { return _front.empty() && _back.empty(); }
    size_t Size()  const { return _front.size() + _back.size(); }

    const T& At(size_t index) const {
        if (index >= Size())
            throw out_of_range("");
        return AtImpl(index);
    }
    T& At(size_t index)            { return CONST_TO_NON_CONST(Deque, .At(index)); }
    const T& operator[](size_t index) const {
        return AtImpl(index);
    }
    T& operator[](size_t index)    { return CONST_TO_NON_CONST(Deque, [index]); }

    const T& Front() const { return (_front.empty() ? _back.front() : _front.back()); }
    T& Front()                     { return CONST_TO_NON_CONST(Deque, .Front()); }

    const T& Back() const { return (_back.empty() ? _front.front() : _back.back()); }
    T& Back()                      { return CONST_TO_NON_CONST(Deque, .Back()); }

    void PushFront(const T& elem) { _front.push_back(elem); }
    void PushBack(const T& elem)  { _back.push_back(elem); }

    //  Deque: |_____/_____|
    //         \     /\    /
    // reversed _front _back
 private:
    T& AtImpl(size_t i) {
        return (i < _front.size() ? _front[_front.size() - i - 1] : _back[i - _front.size()]);
    }

 protected:
    vector<T> _front;
    vector<T> _back;
};
