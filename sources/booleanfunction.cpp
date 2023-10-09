#include "booleanfunction.h"

BooleanFunction::BooleanFunction() {}
BooleanFunction::BooleanFunction(const std::vector<bool> &vec)
    : func(vec), degree(findMax2Degree(func.size()))
{
    if (func.size() / (pow(2, degree)) != 1)
        std::cout << "ERROR: incorrect BooleanFunction parameters."
                  << "Func size can be only degree of 2!";
}
BooleanFunction::BooleanFunction(std::initializer_list<bool> list)
    : BooleanFunction(std::vector<bool>(list)) {}

std::string BooleanFunction::printPolinomial() const
{
    std::vector<bool> pascal({func.at(0)}), iterator = func, tmp;

    for (size_t i = 0; i < iterator.size() - 1; ++i)
    {
        int curValue = (static_cast<int>(iterator[i]) + static_cast<int>(iterator[i+1])) % 2;
        tmp.push_back(static_cast<bool>(curValue));
        if (i + 1 == iterator.size() - 1)
        {
            i = -1;
            iterator = tmp;
            pascal.push_back(iterator.at(0));
            tmp.clear();
        }
    }

    std::string polinom;
    for (size_t i = 0; i < pascal.size(); ++i)
    {
        if (pascal.at(i) == true)
        {
            std::string binary = to2(i, degree);
            if (countOfSymbol(binary, '1') == 0)
            {
                polinom.append("1");
            }
            else
            {
                for (size_t j = 0; j < binary.size(); ++j)
                {
                    if (binary.at(j) == '1')
                    {
                        polinom.append("x_{" + std::to_string(j+1) + "}");
                        polinom.append("\\cdot ");
                    }
                }
                polinom.erase(polinom.size() - 6, 7);
            }
            polinom.append("+");
        }
    }
    return polinom.erase(polinom.size() - 1, 1);
}

BooleanFunction::operator std::string() const
{
    std::string str("f(");
    for (size_t i = 0; i < func.size(); ++i)
    {
        str.append(std::to_string(func.at(i)));
        if (i + 1 != func.size())
            str.append(", ");
    }
    return str + ")";
}

std::ostream& operator<< (std::ostream& out, const BooleanFunction &other)
{
    return out << std::string(other);
}
