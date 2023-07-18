#ifndef RESIDUE_H
#define RESIDUE_H
#include "basemath.h"

class Zn {
public:
    int n, module;

public:
    explicit Zn();
    explicit Zn(int n, int module);

    void simplify();

    Zn operator- ()                   const;
    Zn operator+ (const Zn &other)    const;
    void operator+= (const Zn &other);
    Zn operator- (const Zn &other)    const;
    void operator-= (const Zn &other);
    Zn operator* (const Zn &other)    const;
    void operator*= (const Zn &other);

    bool operator== (const Zn &other) const;
    bool operator!= (const Zn &other) const;
    bool operator< (const Zn &other)  const;
    bool operator<= (const Zn &other) const;
    bool operator> (const Zn &other)  const;
    bool operator>= (const Zn &other) const;

    friend std::ostream& operator<< (std::ostream& out, const Zn &other);
};

class Zp : public Zn {
public:
    explicit Zp();
    explicit Zp(int n, int module);

    Zp operator~ ()                   const;
    Zp operator/ (const Zp &other)    const;
    void operator/= (const Zp &other);
};

#endif // RESIDUE_H
