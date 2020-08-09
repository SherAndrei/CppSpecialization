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

        if (denominator == 0)
            throw invalid_argument("Invalid argument");
        
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
        if (another.m_numerator == 0)
            throw invalid_argument("Division by zero");

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

int main() {

    Rational first, second;
    char operation;

    try {
    cin >> first >> operation >> second;

    switch (operation)
    {
    case ('+'): cout << first + second << endl;
        break;
    case ('-'): cout << first - second << endl;
        break;
    case ('*'): cout << first * second << endl;
        break;
    case ('/'): cout << first / second << endl;
        break;
    default:
        break;
    }
    } catch (invalid_argument& ex) {
        cout << ex.what() << endl;
    }

    return 0;
}