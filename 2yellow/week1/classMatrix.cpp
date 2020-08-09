#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Matrix
{
public:
    Matrix(int nRows = 0, int nCols = 0)
    {
        Reset(nRows, nCols);
    }

    void Reset(int nRows, int nCols)
    {
        if (nCols < 0)
            throw out_of_range("Bad column number: " + to_string(nCols));
        if (nRows < 0)
            throw out_of_range("Bad row number: " + to_string(nRows));
        if (nRows == 0 || nCols == 0) {
            nRows = nCols = 0;
        }
        m_Rows = nRows;
        m_Columns = nCols;
        m_Coeffs.assign((m_Rows * m_Columns), 0);
    }
    int  At(int i, int j)            const
    {
        if (i < 0 || j < 0 || i > m_Rows - 1 || j > m_Columns - 1)
            throw out_of_range("");
        return m_Coeffs[(i * m_Columns + j)];
    }
    int& At(int i, int j) {
        if (i < 0 || j < 0 || i > m_Rows - 1 || j > m_Columns - 1)
            throw out_of_range("Bad position: " + to_string(i) + " " + to_string(j));
        return m_Coeffs[(i * m_Columns + j)];
    }
    int  GetNumRows()                const { return m_Rows; }
    int  GetNumColumns()             const { return m_Columns; }

    size_t size() const
    {
        return m_Coeffs.size();
    }

    bool            operator== (const Matrix& another) const
    {
        return m_Rows    == another.m_Rows    &&
               m_Columns == another.m_Columns &&
               m_Coeffs  == another.m_Coeffs;
    }
    Matrix          operator+  (const Matrix& another) const
    {
        if (m_Columns != another.m_Columns || m_Rows != another.m_Rows)
            throw invalid_argument("Bad dimensions");

        Matrix result(m_Rows, m_Columns);

        for (size_t i = 0; i < result.size(); ++i) {
            result.m_Coeffs[i] = m_Coeffs[i] + another.m_Coeffs[i];
        }

        return result;
    }
    friend istream& operator>> (istream& in, Matrix& matrix)
    {
        int nRows, nCols;
        in >> nRows >> nCols;
        matrix.Reset(nRows, nCols);

        for (int row = 0; row < nRows; ++row) {
            for (int column = 0; column < nCols; ++column) {
                in >> matrix.At(row, column);
            }
        }

        return in;
    }
    friend ostream& operator<< (ostream& out, const Matrix& matr)
    {
        out << matr.GetNumRows() << " " << matr.GetNumColumns() << endl;
        for (size_t i = 0; i < matr.size(); ++i) {
            if (i != 0 && i % matr.m_Columns == 0)
                out << endl;
            out << matr.m_Coeffs[i] << " ";
        }
        return out;
    }


private:
    int m_Rows;
    int m_Columns;
    vector<int> m_Coeffs;
};