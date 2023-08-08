#ifndef RING_OF_MEMBERS
#define RING_OF_MEMBERS
#include "basemath.h"
#include "complex.tpp"
#include "residue.h"

template <class T>
class RingOfMembers {
private:
    std::vector<T> members;
    unsigned int deg;

public:
    explicit RingOfMembers() : deg(0) {}
    explicit RingOfMembers(unsigned int deg, T value) : deg(deg) { members = std::vector<T>(deg, value); }
    explicit RingOfMembers(std::initializer_list<T> list) : members(list), deg(members.size()) {}
    RingOfMembers(const RingOfMembers &other) : members(other.members), deg(other.deg) {}
    ~RingOfMembers() {}

    unsigned int getDeg() const { return deg - 1; }

    RingOfMembers operator -() const
    {
        RingOfMembers result(*this);

        for (unsigned int i = 0; i < result.deg; ++i)
            result[i] = -result[i];

        return result;
    }

    RingOfMembers<T> operator +(const RingOfMembers<T> &other) const
    {
        RingOfMembers<T> result(deg > other.deg ? other : *this);

        while (result.deg < std::max(deg, other.deg))
        {
            ++result.deg;
            result.members.insert(result.members.begin(), static_cast<T>(0));
        }

        for (int i = 0; i < result.deg; ++i)
            result.members[i] = this->members[i] + other.members[i];

        return result;
    }

    void operator +=(const RingOfMembers<T> &other)
    {
        *this = *this + other;
    }

    RingOfMembers<T> operator -(const RingOfMembers &other) const
    {
        return *this + (-other);
    }

    void operator -=(const RingOfMembers<T> &other)
    {
        *this = *this - other;
    }

    RingOfMembers<T> operator *(const RingOfMembers& other) const
    {
        RingOfMembers<T> result((deg + other.deg) - 1, static_cast<T>(0));

        for (unsigned int i = 0; i < deg; ++i)
            for (unsigned int j = 0; j < other.deg; ++j)
                result.members[i + j] += members[i] * other.members[j];

        return result;
    }

    void operator *=(const RingOfMembers<T> &other)
    {
        *this = *this * other;
    }
//    RingOfMembers operator %(const RingOfMembers& other) const;
//    friend RingOfMembers GCD(const RingOfMembers& member_1, const RingOfMembers& member_2);

    std::string to_string(const T &value) const;

    operator std::string() const
    {
        std::string result;

        for (unsigned int i = 1; i <= deg; ++i)
        {
            if (members[deg - i] == static_cast<T>(1))
                if (deg - i == 0)
                    result += std::to_string(1);
                else if (deg - i == 1)
                    result += "x";
                else
                    result += "x^{" + std::to_string(deg - i) + "}";

            else if (members[deg - i] == static_cast<T>(-1))
                if (deg - i == 0)
                    result += std::to_string(-1);
                else if (deg - i == 1)
                    result += "-x";
                else
                    result += "-x^{" + std::to_string(deg - i) + "}";

            else if (members[deg - i] == static_cast<T>(0))
                continue;

            else
                if (deg - i == 0)
                    result += to_string(members[deg - i]);
                else if (deg - i == 1)
                    result += to_string(members[deg - i]) + "x";
                else
                    result += to_string(members[deg - i]) + "x^{" + std::to_string(deg - i) + "}";

            if (i + 1 <= deg && members[deg - (i + 1)] >= static_cast<T>(0))
                result += "+";
        }

        return result;
    }

    friend std::ostream& operator<< (std::ostream &out, const RingOfMembers<T> &other)
    {
        return out << (std::string)other;
    }
};

#endif //RING_OF_MEMBERS
