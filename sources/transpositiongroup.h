#ifndef TRANSPOSITIONGROUP_H
#define TRANSPOSITIONGROUP_H
#include "basemath.h"

enum class ViewMode {
    Standart, Cycle,
     Decomposition,
    Neighbors, None
};

class TranspositionGroup {
public:
    explicit TranspositionGroup();
    explicit TranspositionGroup(std::vector<std::pair<int, int>>);
    explicit TranspositionGroup(const std::string &str, int order);
    explicit TranspositionGroup(std::vector<int>, int);

    TranspositionGroup operator* (TranspositionGroup &trans);
    TranspositionGroup operator~ ();
    bool operator ==(const TranspositionGroup& trans);

    int getTask();
    std::vector<std::vector<int>>& getTransposition();
    ViewMode getViewMode();
    std::string writeToMode(ViewMode, bool forTest = false);
    std::string cycleType();
    int getHaos();
    std::string getEven(bool forTest = false);
    int getOrder();
    TranspositionGroup simplify(int);
private:
    std::vector<std::vector<int>> tp;
    ViewMode mode;
};

#endif // TRANSPOSITIONGROUP_H
