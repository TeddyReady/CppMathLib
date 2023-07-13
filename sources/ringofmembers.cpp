#include "ringofmembers.h"

RingOfMembers::RingOfMembers() {}

RingOfMembers::RingOfMembers(RingOfMembersOptions taskType, int module) : taskType(taskType), module(module) {}

RingOfMembers::RingOfMembers(const RingOfMembers& other)
{
    members = other.members;
    module = other.module;
}

RingOfMembers::~RingOfMembers() {}

void RingOfMembers::create(const QVector<QVariant> &options)
{
    QPair<int, int> rangeDeg = options.at(0).value<QPair<int, int>>();
    QPair<int, int> rangeK = options.at(1).value<QPair<int, int>>();

    QRandomGenerator *random = QRandomGenerator::global();
    setModule(random->bounded(2, 20));

    int deg = static_cast<int>(random->bounded(rangeDeg.first, rangeDeg.second));
    for (int i = 0; i <= deg; ++i) {
        int value = static_cast<int>(random->bounded(rangeK.first, rangeK.second));
        if (value == 0 && i - 1 == deg) addElement(1);
        else addElement(value);
    }
    if (members.last() == 0) members[members.size() - 1] = 1;
    random = nullptr;
}

QString RingOfMembers::description()
{
    switch (taskType) {
    case RingOfMembersOptions::Summary:
        return QString("Вычислите сумму двух многочленов");
    case RingOfMembersOptions::Multiply:
        return QString("Вычислите произведение двух многочленов");
    case RingOfMembersOptions::Divide:
        return QString("Выполните деление многочлена с остатком");
    case RingOfMembersOptions::GCD:
        return QString("Вычислите НОД двух многочленов");
    default:
        break;
    } return QString("Undefined");
}

QString RingOfMembers::task(const QString &optional)
{
    switch (taskType) {
    case RingOfMembersOptions::Summary:
        return QString(getBaseSet() + ":\\left(" + getMembers() + "\\right)+\\left(" + optional + "\\right)=~?");
    case RingOfMembersOptions::Multiply:
        return QString(getBaseSet() + ":\\left(" + getMembers() + "\\right)\\cdot\\left(" + optional + "\\right)=~?");
    case RingOfMembersOptions::Divide:
        return QString(getBaseSet() + ":\\left(" + getMembers() + "\\right),\\left(" + optional + "\\right)\\Rightarrow~?");
    case RingOfMembersOptions::GCD:
        return QString(getBaseSet() + ":GCD(\\left(" + getMembers() + "\\right),\\left(" + optional + "\\right))=~?");
    default:
        break;
    } return QString("Undefined");

}

QString RingOfMembers::answer(const QVariant &other)
{
    switch (taskType) {
    case RingOfMembersOptions::Summary:
        return (*this + other.value<RingOfMembers>()).getMembers();
    case RingOfMembersOptions::Multiply:
        return (*this * other.value<RingOfMembers>()).getMembers();
    case RingOfMembersOptions::Divide: {
        RingOfMembers second = other.value<RingOfMembers>();
        second.setModule(this->getModule());
        while (second.members.last() == 0) second.members.pop_back();
        return (*this % second).getMembers();
    } case RingOfMembersOptions::GCD:
        return GCD(*this, other.value<RingOfMembers>()).getMembers();
    default:
        break;
    } return QString("Undefined");
}

void RingOfMembers::addElement(int number)
{
    number = toMod(number, module);
    members.push_back(number);
}

void RingOfMembers::setModule(int module)
{
    this->module = module;
    for (int i = 0; i < members.size(); ++i)
        members[i] = toMod(members[i], module);
}

int RingOfMembers::getDeg() const { return members.size() - 1; }

int RingOfMembers::getModule() const { return module; }

QString RingOfMembers::getMembers() const
{
    QString result;
    for (int i = members.size() - 1; i >= 0; --i)
    {
        if (members[i] == 0) continue;
        if (result.isEmpty()) {
            QString num;
            if (i == 1) num = "";
            else num = QString::number(i);
            if (members[i] == 1)
                result.append("x^{" + num + "}");
            else if (members[i] == -1)
                result.append("-x^{" + num + "}");
            else result.append(QString::number(members[i]) + "x^{" + num + "}");
        } else if (i == 1) {
            if (members[i] == 1)
                result.append("+x");
            else if (members[i] > 0)
                result.append("+" + QString::number(members[i]) + "x");
            else {
                if (members[i] == -1)
                    result.append("-x");
                else result.append(QString::number(members[i]) + "x");
            }
        } else if (i == 0) {
            if (members[i] > 0)
                result.append("+" + QString::number(members[i]));
            else
                result.append(QString::number(members[i]));
        } else {
            if (members[i] == 1)
                result.append("+x^{" + QString::number(i) + "}");
            else if (members[i] > 0)
                result.append("+" + QString::number(members[i]) + "x^{" + QString::number(i) + "}");
            else {
                if (members[i] == -1)
                    result.append("-x^{" + QString::number(i) + "}");
                else result.append(QString::number(members[i]) + "x^{" + QString::number(i) + "}");
            }
        }
    }

    return result;
}

QString RingOfMembers::getBaseSet() const
{
    return QString("\\mathbb{Z}_{" + QString::number(module) + "}[x]");
}

void RingOfMembers::clear()
{
    members.clear();
    module = 2;
}

int RingOfMembers::last()
{
    return members.last();
}

int RingOfMembers::inverseElementInZn(int num) const
{
    for (int i = 0; i < module; ++i)
        if ((num * i) % module == (i * num) % module == 1)
            return i;
    return -1;
}

RingOfMembers RingOfMembers::operator +(const RingOfMembers& member) const
{
    RingOfMembers mini(taskType), maxi(taskType);
    if (this->getDeg() > member.getDeg()) {
        mini = member;
        maxi = *this;
    } else {
        mini = *this;
        maxi = member;
    }

    for (int i = mini.getDeg(); i < maxi.getDeg(); ++i)
        mini.addElement(0);

    RingOfMembers result(taskType, module);
    for (int i = 0; i <= mini.getDeg(); ++i)
        result.addElement(mini.members[i] + maxi.members[i]);

    return result;
}

RingOfMembers RingOfMembers::operator -() const
{
    RingOfMembers result = *this;
    for (int i = 0; i <= result.getDeg(); ++i)
        result.members[i] = -result.members[i];
    return result;
}

RingOfMembers RingOfMembers::operator -(const RingOfMembers& member) const
{
    return *this + (-member);
}

RingOfMembers RingOfMembers::operator *(const RingOfMembers& member) const
{
    RingOfMembers mini(taskType), maxi(taskType);
    if (this->getDeg() > member.getDeg()) {
        mini = member;
        maxi = *this;
    } else {
        mini = *this;
        maxi = member;
    }

    QMap<int, int> multi;
    for (int i = 0; i <= mini.getDeg(); ++i)
        for (int j = 0; j <= maxi.getDeg(); ++j)
        {
            if (multi.contains(i+j))
                multi.insert(i+j, multi.value(i+j) + mini.members[i] * maxi.members[j]);
            else multi.insert(i+j, mini.members[i] * maxi.members[j]);
        }

    RingOfMembers result(taskType, module);
    foreach (const auto& key, multi.keys())
        result.addElement(multi.value(key));

    return result;
}

RingOfMembers RingOfMembers::operator %(const RingOfMembers& member) const
{
    if (member.getDeg() >= this->getDeg()) {
        RingOfMembers error;
        qDebug() << "ERROR DEGRATES!";
        return error;
    } else {
        RingOfMembers result = *this, quot = member;
        while (result.getDeg() >= quot.getDeg())
        {
            for (int i = 0; i < result.getDeg() - quot.getDeg(); ++i)
                quot.members.push_front(0);

            for (int i = 0; i <= quot.getDeg(); ++i)
                quot.members[i] *= (result.last() * inverseElementInZn(quot.last()));

            result = result - quot;
            result.members.pop_back();
            quot = member;
        } return result;
    }
}

RingOfMembers GCD(const RingOfMembers& member_1, const RingOfMembers& member_2)
{

}
