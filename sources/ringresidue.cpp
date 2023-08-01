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
