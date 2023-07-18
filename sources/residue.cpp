#include "residue.h"

Zn::Zn(): n(0), module(1) {} 
Zn::Zn(int n, int module): n(n), module(module)
{
    if (module == 0)
    {
        std::cerr << "ERROR in residue.cpp: Module cannot be zero!" << std::endl;
        this->module = 1;
    }

    simplify();
}

void Zn::simplify()
{
    while (n >= module)
        n -= module;

    while (n < 0)
        n += module;
}

Zn Zn::operator- () const
{
    return Zn(-n, module);
}

Zn Zn::operator+ (const Zn &other) const
{
    if (module != other.module)
    {
        std::cerr << "ERROR in residue.cpp: Modules does be equal!" << std::endl;
        return *this;
    }

    return Zn(n + other.n, module);
}

void Zn::operator+= (const Zn &other)
{
    *this = *this + other;
}

Zn Zn::operator- (const Zn &other) const
{
    return *this + (-other);
}

void Zn::operator-= (const Zn &other)
{
    *this = *this - other;
}

Zn Zn::operator* (const Zn &other) const
{
    if (module != other.module)
    {
        std::cerr << "ERROR in residue.cpp: Modules does be equal!" << std::endl;
        return *this;
    }

    return Zn(n * other.n, module);
}

void Zn::operator*= (const Zn &other)
{
    *this = *this * other;
}

bool Zn::operator== (const Zn &other) const
{
    if (module != other.module)
    {
        std::cerr << "ERROR in residue.cpp: Modules does be equal!" << std::endl;
        return false;
    }

    return (n == other.n);
}

bool Zn::operator!= (const Zn &other) const
{
    return !(*this == other);
}

bool Zn::operator< (const Zn &other) const
{
    if (module != other.module)
    {
        std::cerr << "ERROR in residue.cpp: Modules does be equal!" << std::endl;
        return false;
    }
    return (n < other.n);
}

bool Zn::operator<= (const Zn &other) const
{
    return (*this < other || *this == other);
}

bool Zn::operator> (const Zn &other) const
{
    return !(*this <= other);
}

bool Zn::operator>= (const Zn &other) const
{
    return !(*this < other); 
}

std::ostream& operator<< (std::ostream& out, const Zn &other)
{
    out << other.n << " mod(" << other.module << ")";
    return out;
}

Zp::Zp() : Zn() {}
Zp::Zp(int n, int module): Zn(n, module) 
{
    if (!isPrime(module))
    {
        std::cerr << "ERROR in residue.cpp: Zp capture only primes values!" << std::endl;
        this->n = 0;
        this->module = 1; 
    }
}

Zp Zp::operator~ () const
{
    for(int i = 0; i < module; ++i)
    {

        if (Zp(n * i, module).n == 1)
            return Zp(i, module);

    } return Zp(0, module);
}

Zp Zp::operator/ (const Zp &other) const
{
    Zn result(*this * (~other));
    return Zp(result.n, result.module);
}

void Zp::operator/= (const Zp &other)
{
    *this = *this / other;
}
