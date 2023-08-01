#include "ringresidue.h"

RingResidue::RingResidue() : n(0), module(-1), type(ResidueType::Zn) {}
RingResidue::RingResidue(int n, int module, ResidueType type) : n(n), module(module), type(type) {}

int RingResidue::countOfGenerators(const char *operation) const
{
    switch (type)
    {
    case ResidueType::Zn:
        return Zn(n, module).countOfGenerators(operation);
    case ResidueType::Zp:
        return Zp(n, module).countOfGenerators(operation);

    default:
        return -1;
    }
}

int RingResidue::pow(int deg, const char *operation) const
{
    if (not strcmp(operation, "+"))
        return (n * deg) % module;
    else
        return modulePower(n, deg, module);
}

int RingResidue::order(const char *operation) const
{
    if (not strcmp(operation, "+"))
    {
        Zn residue(n, module);
        switch (type)
        {
        case ResidueType::Zn:
        case ResidueType::Zp:
            if (n == 0) return 1;
            for (int i = 2; i <= residue.capacity(); ++i)
            {
                if (GCD(i, residue.capacity()) == 1) continue;

                if (residue * Zn(i, module) == Zn(0, module))
                    return i;
            }
            return -2;

        default:
            return -1;
        }
    } else {
        if (type == ResidueType::Zn && not isPrime(module)) return -1;

        MultiGroup_Zn residue(n, module);
        if (n == 1) return 1;
        for (int i = 2; i <= residue.capacity(); ++i)
        {
            if (GCD(i, residue.capacity()) == 1) continue;

            if (residue * residue == MultiGroup_Zn(1, module))
                return i;
            else
                residue *= residue;
        }
        return -2;
    }
}
