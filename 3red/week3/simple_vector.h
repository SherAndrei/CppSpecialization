#pragma once
#include <cstdlib>
#include <algorithm>
// Реализуйте шаблон SimpleVector

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size)
        : _size(size), _capacity(size)
        , _begin(new T[size])
    {}
    
    ~SimpleVector() { delete[] _begin; }

    T& operator[](size_t index) { return _begin[index]; }
    
    T* begin() { return _begin; }
    T* end()   { return _begin + _size; }

    size_t Size()     const { return _size; }
    size_t Capacity() const { return _capacity; }
    void PushBack(const T& value) {
        if (_size >= _capacity) {
            int new_capacity = (_capacity == 0 ? 1 : 2 * _capacity);
            T*  new_begin    = new T[new_capacity];
            std::copy(begin(), end(), new_begin);
            delete[] _begin;
            _begin    = new_begin;
            _capacity = new_capacity;
        }
        _begin[_size++] = value;
    }

private:
    T* _begin = nullptr;
    size_t _size     = 0;
    size_t _capacity = 0;
};
