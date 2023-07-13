#ifndef RING_OF_MEMBERS
#define RING_OF_MEMBERS
#include "algebrastructures.h"
#include "basemath.h"

class RingOfMembers : protected BaseMath {
public:
    explicit RingOfMembers();
    explicit RingOfMembers(RingOfMembersOptions taskType, int module = 2);
    RingOfMembers(const RingOfMembers& other);
    ~RingOfMembers();

    void create(const QVector<QVariant> &options);
    QString description();
    QString task(const QString &optional);
    QString answer(const QVariant &other);

    void addElement(int number);
    void setModule(int module);
    int getDeg() const;
    int getModule() const;
    QString getMembers() const;
    QString getBaseSet() const;
    void clear();
    int last();
    int inverseElementInZn(int num) const;
    RingOfMembers operator -() const;
    RingOfMembers operator *(const RingOfMembers& member) const;
    RingOfMembers operator +(const RingOfMembers& member) const;
    RingOfMembers operator -(const RingOfMembers& member) const;
    RingOfMembers operator %(const RingOfMembers& member) const;
    friend RingOfMembers GCD(const RingOfMembers& member_1, const RingOfMembers& member_2);
private:
    RingOfMembersOptions taskType;

    QVector<int> members;
    int module;
};
Q_DECLARE_METATYPE(RingOfMembers)

#endif //RING_OF_MEMBERS
