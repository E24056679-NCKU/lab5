#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

class HugeInt
{
public:
    HugeInt();
    HugeInt(const HugeInt &n);
    HugeInt(std::string str);
    HugeInt(int n);
    ~HugeInt();

    friend std::ostream&  operator<<(std::ostream &out, HugeInt   n);
    friend std::istream&  operator>>(std::istream  &in, HugeInt  &n);
    friend HugeInt operator+(HugeInt lhs, HugeInt rhs);
    friend HugeInt operator-(HugeInt lhs, HugeInt rhs);
    HugeInt& operator=(HugeInt rhs);


private:
    std::vector<int> num;
    void constructFromString(const std::string &str);

    static HugeInt& add(HugeInt &lhs, const HugeInt &rhs); // overwrite the result to lhs
    static HugeInt& sub(HugeInt &lhs, const HugeInt &rhs); // overwrite the result to lhs
};


HugeInt::HugeInt()
{
#ifdef TEST
    std::cout << "ctor : null" << std::endl;
#endif
    num.push_back(0);
}

HugeInt::HugeInt(const HugeInt &n)
{
#ifdef TEST
    std::cout << "ctor : const HugeInt &n" << std::endl;
#endif
    num = n.num;
}

HugeInt::HugeInt(std::string str)
{
#ifdef TEST
    std::cout << "ctor : std::string str" << std::endl;
#endif
    constructFromString(str);
}

void HugeInt::constructFromString(const std::string &str)
{
    num.clear();
    for(int i=str.size()-1;i>=0;--i)
        num.push_back(str[i]-'0');
}

HugeInt::HugeInt(int n)
{
#ifdef TEST
    std::cout << "ctor : int n" << std::endl;
#endif
    while(n)
    {
        num.push_back(n%10);
        n /= 10;
    }
}

HugeInt::~HugeInt()
{
#ifdef TEST
    std::cout << "dtor" << std::endl;
#endif
}

std::ostream& operator<<(std::ostream &out, HugeInt  n)
{
    for(int i=n.num.size()-1;i>=0;--i)
        out << n.num[i];
    return out;
}

std::istream& operator>>(std::istream &in, HugeInt &n)
{
    std::string str;
    in >> str;
    n.constructFromString(str);
    return in;
}

HugeInt operator+(HugeInt lhs, HugeInt rhs)
{
    return HugeInt::add(lhs, rhs);
}

HugeInt operator-(HugeInt lhs, HugeInt rhs)
{
    return HugeInt::sub(lhs, rhs);
}

HugeInt& HugeInt::operator=(HugeInt rhs)
{
#ifdef TEST
    std::cout << "= called" << std::endl;
#endif
    this->num = rhs.num;
    return *this;
}

HugeInt& HugeInt::add(HugeInt &lhs, const HugeInt &rhs)
{
    lhs.num.resize(std::max(lhs.num.size(), rhs.num.size()));
    for(int i=0;i<rhs.num.size();++i)
        lhs.num[i] += rhs.num[i];
    for(int i=1;i<lhs.num.size();++i)
    {
        if(lhs.num[i-1] >= 10)
        {
            lhs.num[i-1] -= 10;
            ++ lhs.num[i];
        }
    }
    if(lhs.num.back() >= 10)
    {
        lhs.num.back() -= 10;
        lhs.num.push_back(1);
    }
    return lhs;
}

HugeInt& HugeInt::sub(HugeInt &lhs, const HugeInt &rhs)
{
    lhs.num.resize(std::max(lhs.num.size(), rhs.num.size()));
    for(int i=0;i<rhs.num.size();++i)
        lhs.num[i] -= rhs.num[i];
    for(int i=0, end = lhs.num.size()-1 ; i<end ;++i)
    {
        if(lhs.num[i] < 0)
        {
            lhs.num[i] += 10;
            -- lhs.num[i+1];
        }
    }
    if(lhs.num.back() == 0)
        lhs.num.pop_back();
    return lhs;
}

#endif
