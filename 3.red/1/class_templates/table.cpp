#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "test_runner.h"

using namespace std;

#define LOG(x) cout << #x << " = " << x << endl

template<typename T>
class Table {
 public:
    Table(size_t rows, size_t columns) {
        Resize(rows, columns);
    }

    void Resize(size_t nRows, size_t nCols) {
        if (nRows == 0 || nCols == 0) {
            nRows = nCols = 0;
        }
        _coeffs.resize(nRows);
        for (auto& column : _coeffs)
            column.resize(nCols);

        _rows    = nRows;
        _columns = nCols;
    }

    pair<size_t, size_t> Size() const {
        return make_pair(_rows, _columns);
    }

    T& at(size_t nRow, size_t nCol) {
        return _coeffs[nRow][nCol];
    }

    vector<T>& operator[](size_t index) {
        return _coeffs[index];
    }

    const vector<T>& operator[](size_t index) const {
        return _coeffs[index];
    }

    friend ostream& operator<<(ostream& os, Table t) {
        for (size_t i = 0; i < t.Size().first; ++i)
            for (size_t j = 0; j < t.Size().second; ++j)
                os << t[i][j] << (j == t.Size().second - 1 ? '\n' : ' ');
        return os;
    }

    void fill(const T& elem) {
        for (auto& column : _coeffs)
            std::fill(column.begin(), column.end(), elem);
    }

 private:
    size_t _rows;
    size_t _columns;
    vector<vector<T>> _coeffs;
};


void MyTestSize() {
    {
        Table<int> t(1, 1);
        ASSERT_EQUAL(t.Size().first, 1u);
        ASSERT_EQUAL(t.Size().second, 1u);
    }
    {
        Table<int> t(0, 1);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);
    }
    {
        Table<int> t(1, 0);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);
    }
}

void MyTestFill() {
    {
        Table<int> t(3, 3);
        t.fill(1);
        ostringstream os;
        os << t;
        ASSERT_EQUAL(os.str(), "1 1 1\n1 1 1\n1 1 1\n");
    }
    {
        Table<int> t(1, 3);
        t.fill(1);
        ostringstream os;
        os << t;
        ASSERT_EQUAL(os.str(), "1 1 1\n");
    }
    {
        Table<int> t(3, 1);
        t.fill(1);
        ostringstream os;
        os << t;
        ASSERT_EQUAL(os.str(), "1\n1\n1\n");
    }
    {
        Table<string> t(3, 3);
        t.fill("abc");
        ostringstream os;
        os << t;
        ASSERT_EQUAL(os.str(), "abc abc abc\nabc abc abc\nabc abc abc\n");
    }
}

void MyTestOperator() {
    {
        Table<int> t(1, 1);
        t[0][0] = 42;
        ASSERT_EQUAL(t[0][0], 42);
    }
}

void MyTestResize() {
    {
        Table<int> t(1, 1);
        t.fill(1);
        t.Resize(3, 4);
        ASSERT_EQUAL(t.Size().first, 3u);
        ASSERT_EQUAL(t.Size().second, 4u);
        ostringstream os;
        os << t;
        ASSERT_EQUAL(os.str(), "1 0 0 0\n0 0 0 0\n0 0 0 0\n")
    }
    {
        Table<int> t(3, 3);
        t.fill(1);
        t.Resize(1, 1);
        ASSERT_EQUAL(t.Size().first, 1u);
        ASSERT_EQUAL(t.Size().second, 1u);
        ostringstream os;
        os << t;
        ASSERT_EQUAL(os.str(), "1\n")
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, MyTestSize);
    RUN_TEST(tr, MyTestFill);
    RUN_TEST(tr, MyTestOperator);
    RUN_TEST(tr, MyTestResize);
    return 0;
}
