///////////////////////////
/* Complex number class */
/*      @TeddyReady      */
///////////////////////////

#ifndef COMPLEX_H
#define COMPLEX_H
#include "basemath.h"

/* Complex numbers can be Integers or Reals */
/*           T - int or double              */

template <class T>
class Complex {
public:
    T a, b;

    Complex() : a(0), b(0) {}
    Complex(T a) : a(a), b(0) {}
    Complex(T a, T b) : a(a), b(b) {}

    T norm() const
    {
        return a*a + b*b;
    }


    Complex<T> operator- () const
    {
        return Complex<T>(-a, -b);
    }


    Complex<T> operator+ (const Complex<T>& other) const
    {
        return Complex<T>(a + other.a, b + other.b);
    }


    void operator+= (const Complex<T>& other)
    {
        *this = *this + other;
    }


    Complex<T> operator- (const Complex<T>& other) const
    {
        return *this + (-other);
    }


    void operator-= (const Complex<T>& other)
    {
        *this = *this - other;
    }


    Complex<T> operator* (const Complex<T>& other) const
    {
        return Complex<T>(a * other.a - b * other.b, a * other.b + other.a * b);
    }


    void operator*= (const Complex<T>& other)
    {
        *this = *this * other;
    }

    Complex<T> operator/ (const Complex<T>& other) const
    {
        Complex<T> num = *this * Complex<T>(other.a, -other.b);
        double den = other.norm();

        return Complex<T>(num.a / den, num.b/den);
    }


    void operator/= (const Complex<T>& other)
    {
        *this = *this / other;
    }


    Complex<int> operator% (const Complex<int>& other) const
    {
        Complex<double> result = Complex<double>(a, b) / Complex<double>(other.a, other.b);
        return (*this - other*Complex<int>(round(result.a), round(result.b)));
    }

    void operator%= (const Complex<int>& other)
    {
        *this = *this % other;
    }

    bool operator== (const Complex<T> &other) const
    {
        return this->norm() == other.norm();
    }

    bool operator!= (const Complex<T> &other) const
    {
        return !(*this == other);
    }

    bool operator< (const Complex<T> &other)  const
    {
        return this->norm() < other.norm();
    }

    bool operator<= (const Complex<T> &other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator> (const Complex<T> &other) const
    {
        return !(*this <= other);
    }

    bool operator>= (const Complex<T> &other) const
    {
        return !(*this < other);
    }


    friend QDebug operator<< (QDebug dbg, const Complex<T> &other)
    {
        if (other.b > 0)
            if (other.b == 1)
                dbg << QString::number(other.a) + "+i";
            else
                dbg << QString::number(other.a) + "+" + QString::number(other.b) + "i";

        else if (other.b == 0)
            dbg << QString::number(other.a);

        else
            if (other.b == -1)
                dbg << QString::number(other.a) + "-i";
            else
                dbg << QString::number(other.a) + QString::number(other.b) + "i";

        return dbg;
    }
};

#endif // COMPLEX_H
