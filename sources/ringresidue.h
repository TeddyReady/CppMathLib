#ifndef RINGRESIDUE_H
#define RINGRESIDUE_H
#include "residue.h"

enum class ResidueType {
    Zn           ,
    Zp           ,
    MultiGroup_Zn,
};

class RingResidue {
private:
    int n, module;
    ResidueType type;

public:
    explicit RingResidue();
    explicit RingResidue(int n, int module, ResidueType type);

    int countOfGenerators(const char *operation) const;
    int pow(int deg, const char *operation);
};

#endif // RINGRESIDUE_H
