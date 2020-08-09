#include <iostream>
#include <numeric>
using namespace std;

class Rational {
public:
    Rational() {
        m_numerator   = 0;
        m_denominator = 1;
    }

    Rational(int numerator, int denominator) {

        m_numerator   = numerator;
        m_denominator = denominator;
        
        Reduce();

        if (m_denominator < 0)
        {
            m_numerator   = -m_numerator;
            m_denominator = -m_denominator;
        }
    }

    int Numerator() const {
        return m_numerator;
    }

    int Denominator() const {
        return m_denominator;
    }

    Rational operator +  (const Rational& another)
    {
        return { (m_numerator * another.m_denominator) + (another.m_numerator * m_denominator), m_denominator * another.m_denominator };
    }
    Rational operator -  (const Rational& another)
    {
        return { (m_numerator * another.m_denominator) - (another.m_numerator * m_denominator), m_denominator * another.m_denominator };
    }
    Rational operator *  (const Rational& another)
    {
        return { m_numerator * another.m_numerator, m_denominator * another.m_denominator };
    }
    Rational operator /  (const Rational& another)
    {
        return { m_numerator * another.m_denominator, m_denominator * another.m_numerator };
    }
    bool     operator <  (const Rational& another) const
    {
        return  (m_numerator * another.m_denominator < m_denominator* another.m_numerator);
    }
    bool     operator >  (const Rational& another) const
    {
        return  (m_numerator * another.m_denominator > m_denominator* another.m_numerator);
    }
    bool     operator <= (const Rational& another) const
    {
        return  !(m_numerator * another.m_denominator > m_denominator* another.m_numerator);
    }
    bool     operator >= (const Rational& another) const
    {
        return  !(m_numerator * another.m_denominator < m_denominator * another.m_numerator);
    }
    bool     operator == (const Rational& another) const
    {
        return  (m_numerator == another.m_numerator && m_denominator == another.m_denominator);
    }
    bool     operator != (const Rational& another) const
    {
        return !(*this == another);
    }

    friend ostream& operator << (ostream& str, const Rational& rat)
    {
        str << rat.m_numerator << "/" << rat.m_denominator;
        return str;
    }
    friend istream& operator >> (istream& str, Rational& rat)
    {
        if (str)
        {
            str >> rat.m_numerator;
            str.ignore(1);
            str >> rat.m_denominator;
            rat.Reduce();
        }
        return str;
    }

private:
    void Reduce()
    {
        int numerator   = m_numerator;
        int denominator = m_denominator;

        m_numerator   = numerator   / (gcd(numerator, denominator));
        m_denominator = denominator / (gcd(numerator, denominator));
    }
    int m_numerator;
    int m_denominator;
};

int main()
{
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}