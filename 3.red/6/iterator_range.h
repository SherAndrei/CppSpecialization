#pragma once

#include <algorithm>
using namespace std;

template <typename It>
class IteratorRange {
 public:
  IteratorRange(It first, It last)
    : first(first), last(last) {}

  It begin() const { return first; }
  It end()   const { return last; }

  size_t size() const { return last - first; }

 private:
  It first, last;
};

template <typename Container>
auto Head(Container& c, std::size_t top) {
  return IteratorRange(begin(c), next(begin(c), min(top, c.size())));
}
