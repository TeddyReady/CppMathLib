///////////////////////////
/* Rational number class */
/*      @TeddyReady      */
///////////////////////////

#ifndef RATIONAL_H
#define RATIONAL_H
#include "basemath.h"

class Rational {
private:
    int num, den;

public:
    explicit Rational();
    explicit Rational(int num);
    explicit Rational(int num, int den);

    Rational simplify();

    Rational operator- ()                      const;
    Rational operator+ (const Rational &other) const;
    void operator+= (const Rational &other);
    Rational operator- (const Rational &other) const;
    void operator-= (const Rational &other);
    Rational operator* (const Rational &other) const;
    void operator*= (const Rational &other);
    Rational operator/ (const Rational &other) const;
    void operator/= (const Rational &other);

    bool operator== (const Rational &other) const;
    bool operator!= (const Rational &other) const;
    bool operator< (const Rational &other)  const;
    bool operator<= (const Rational &other) const;
    bool operator> (const Rational &other)  const;
    bool operator>= (const Rational &other) const;

    operator int()    const;
    operator double() const;

    friend QDebug operator<< (QDebug dbg, const Rational &other);
};

#endif //RATIONAL_H
