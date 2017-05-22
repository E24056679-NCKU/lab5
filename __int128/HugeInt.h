#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
#include <string>

class HugeInt
{
public:
    HugeInt();
    HugeInt(int int32);
    HugeInt(__int128 int128);
    HugeInt(std::string str);

    friend std::ostream& operator<<(std::ostream &out, HugeInt &n);
    friend std::istream& operator>>(std::istream &in , HugeInt &n);

    friend HugeInt operator+(HugeInt lhs, HugeInt rhs);
    friend HugeInt operator-(HugeInt lhs, HugeInt rhs);

private:
    __int128 n;
    void constructFromString(std::string str);
};

HugeInt::HugeInt()
{
    n = 0;
}

HugeInt::HugeInt(int int32)
{
    n = int32;
}

HugeInt::HugeInt(__int128 int128)
{
    n = int128;
}

void HugeInt::constructFromString(std::string str)
{
    n = 0;
    for(int i=0;i<str.size();++i)
    {
        n *= 10;
        n += str[i] - '0';
    }
}

HugeInt::HugeInt(std::string str)
{
    constructFromString(str);
}

std::ostream& operator<<(std::ostream &out, HugeInt &n)
{
    if(n.n == 0)
    {
        out << 0;
        return out;
    }
    __int128 tmp = n.n;
    if(tmp < 0)
    {
        out << '-';
        tmp = -tmp;
    }
    int o[40], o_size = 0;
    for( ; tmp ; tmp /= 10)
        o[o_size++] = tmp%10;
    for(o_size -= 1 ; o_size >= 0 ; --o_size)
        out << o[o_size];
    return out;
}

std::istream& operator>>(std::istream &in , HugeInt &n)
{
    std::string str;
    in >> str;
    n.constructFromString(str);
    return in;
}

HugeInt operator+(HugeInt lhs, HugeInt rhs)
{
    lhs.n += rhs.n;
    return lhs;
}

HugeInt operator-(HugeInt lhs, HugeInt rhs)
{
    lhs.n -= rhs.n;
    return lhs;
}
#endif
