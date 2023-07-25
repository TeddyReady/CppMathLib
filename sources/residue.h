#ifndef RESIDUE_H
#define RESIDUE_H
#include "eulerfunction.h"

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

    operator std::string() const;
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

// Zn* inverse elements group
class MultiGroup_Zn {
private:
    int n, module;

public:
    explicit MultiGroup_Zn();
    explicit MultiGroup_Zn(int n, int module);

    void simplify();

    MultiGroup_Zn operator~ ()                           const;
    MultiGroup_Zn operator* (const MultiGroup_Zn &other) const;
    void operator*= (const MultiGroup_Zn &other);
    MultiGroup_Zn operator/ (const MultiGroup_Zn &other) const;
    void operator/= (const MultiGroup_Zn &other);

    bool operator== (const MultiGroup_Zn &other) const;
    bool operator!= (const MultiGroup_Zn &other) const;
    bool operator< (const MultiGroup_Zn &other)  const;
    bool operator<= (const MultiGroup_Zn &other) const;
    bool operator> (const MultiGroup_Zn &other)  const;
    bool operator>= (const MultiGroup_Zn &other) const;

    operator std::string() const;
    friend std::ostream& operator<< (std::ostream& out, const MultiGroup_Zn &other);
};

#endif // RESIDUE_H
