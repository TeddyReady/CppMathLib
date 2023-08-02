#ifndef RINGRESIDUE_H
#define RINGRESIDUE_H
#include "symbollegandre.h"
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
    int pow(int deg, const char *operation) const;
    int order(const char *operation) const;
    static std::vector<int> solveLinear(int a, int b, int module);

    static int countOfAnswersPrimeQuadro(int a, int module);
    static std::vector<int> solvePrimeQuadro(int a, int module);
};

#endif // RINGRESIDUE_H
