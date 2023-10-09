#ifndef BOOLEANFUNCTION_H
#define BOOLEANFUNCTION_H
#include "basemath.h"

class BooleanFunction {
private:
    std::vector<bool> func;
    int degree;

public:
    BooleanFunction(std::initializer_list<bool> list);

    std::string printPolinomial() const;

    operator std::string() const;
    friend std::ostream& operator<< (std::ostream& out, const BooleanFunction &other);
};

#endif // BOOLEANFUNCTION_H
