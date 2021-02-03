#include <cstdint>
#include <utility>
#include <algorithm>

template <typename T>
class SimpleVector {
 public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size)
        : _size(size), _capacity(size)
        , _begin(new T[size]) {}

    SimpleVector(const SimpleVector& other)
        : _size(other._size), _capacity(other._capacity)
        , _begin(new T[other._capacity]) {
            std::copy(other.begin(), other.end(), _begin);
    }

    SimpleVector(SimpleVector&& other)
        : _size(other._size), _capacity(other._capacity)
        , _begin(other._begin) {
            other._begin = nullptr;
            other._capacity = other._size = 0u;
    }

    SimpleVector& operator =(const SimpleVector& rhs) {
        if (rhs._size <= _capacity) {
            std::copy(rhs.begin(), rhs.end(), begin());
            _size = rhs._size;
        } else {
            SimpleVector<T> tmp(rhs);
            std::swap(tmp._begin, _begin);
            std::swap(tmp._size, _size);
            std::swap(tmp._capacity, _capacity);
        }
        return *this;
    }

    SimpleVector& operator =(SimpleVector&& rhs) {
        _capacity = std::exchange(rhs._capacity, 0ul);
        _size     = std::exchange(rhs._size, 0ul);
        _begin    = std::exchange(rhs._begin, nullptr);
        return *this;
    }

    ~SimpleVector() { delete[] _begin; }

    T& operator[](size_t index) { return _begin[index]; }

    T* begin() { return _begin; }
    T* end()   { return _begin + _size; }

    const T* begin() const { return _begin; }
    const T* end()   const { return _begin + _size; }

    size_t Size()     const { return _size; }
    size_t Capacity() const { return _capacity; }

 private:
    void ExpandIfNeeded() {
        if (_size >= _capacity) {
            int new_capacity = (_capacity == 0 ? 1 : 2 * _capacity);
            T*  new_begin    = new T[new_capacity];
            std::move(begin(), end(), new_begin);
            delete[] _begin;
            _begin    = new_begin;
            _capacity = new_capacity;
        }
    }

 public:
    void PushBack(T value) {
        ExpandIfNeeded();
        _begin[_size++] = std::move(value);
    }

 private:
    T* _begin = nullptr;
    size_t _size     = 0;
    size_t _capacity = 0;
};
