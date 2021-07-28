#include <vector>
#include <future>
#include <thread>
#include <numeric>
#include <algorithm>
#include <iterator>

#include "test_runner.h"

template <typename Iterator>
class IteratorRange {
 public:
    IteratorRange(Iterator begin, Iterator end)
        : _begin(begin), _end(end) {}

    Iterator begin()  const { return _begin; }
    Iterator end()    const { return _end; }
    size_t   size()   const { return std::distance(_begin, _end); }
 private:
    const Iterator _begin, _end;
};

template <typename Iterator>
class Paginator {
 public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        if (page_size == 0)
            throw std::runtime_error("page size is 0");

        size_t remaining_size = std::distance(begin, end);
        Iterator current_page_begin = begin;
        while (remaining_size > 0) {
            size_t current_page_size  = std::min(page_size, remaining_size);
            Iterator current_page_end = std::next(current_page_begin, current_page_size);
            pages.push_back({ current_page_begin, current_page_end });

            remaining_size -= current_page_size;
            current_page_begin = current_page_end;
        }
    }

    auto   begin() const { return pages.begin(); }
    auto   end()   const { return pages.end(); }
    size_t size()  const { return pages.size(); }
 protected:
    std::vector<IteratorRange<Iterator>> pages;
};


template <typename C>
auto Paginate(C & c, size_t page_size) {
    return Paginator{ c.begin(), c.end(), page_size };
}

int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) {
    auto nthreads = std::thread::hardware_concurrency();
    auto size_per_thread = matrix.size() < nthreads ? matrix.size() : matrix.size() / nthreads;
    std::vector<std::future<int64_t>> futures;
    for (auto rows : Paginate(matrix, size_per_thread)) {
        futures.emplace_back(std::async([rows] {
            int64_t result = 0;
            for (const auto& row : rows) {
                result += std::accumulate(row.begin(), row.end(), 0);
            }
            return result;
        }));
    }
    int64_t result = 0;
    for (auto& future : futures)
        result += future.get();
    return result;
}

void TestCalculateMatrixSum() {
  const std::vector<std::vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
