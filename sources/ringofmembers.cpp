#include "ringofmembers.tpp"

template <>
std::string RingOfMembers<int>::to_string(const int &value) const
{
    return std::to_string(value);
}

template <>
std::string RingOfMembers<double>::to_string(const double &value) const
{
    return std::to_string(value);
}

template <>
std::string RingOfMembers<Zn>::to_string(const Zn &value) const
{
    return (std::string)value;
}

template <>
std::string RingOfMembers<Zp>::to_string(const Zp &value) const
{
    return (std::string)value;
}

template <>
std::string RingOfMembers<MultiGroup_Zn>::to_string(const MultiGroup_Zn &value) const
{
    return (std::string)value;
}

template <>
std::string RingOfMembers<Complex<int>>::to_string(const Complex<int> &value) const
{
    return (std::string)value;
}

template <>
std::string RingOfMembers<Complex<double>>::to_string(const Complex<double> &value) const
{
    return (std::string)value;
}
