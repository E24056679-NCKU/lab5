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
    HugeInt(HugeInt &&rhs);
    HugeInt(const std::string &str);
    HugeInt(const std::string &&str);
    HugeInt(int n);

    friend std::ostream&  operator<<(std::ostream &out, HugeInt  &n);
    friend std::ostream&  operator<<(std::ostream &out, HugeInt &&n);
    friend std::istream&  operator>>(std::istream  &in, HugeInt  &n);

    friend HugeInt&& operator+(const HugeInt  &lhs, const HugeInt  &rhs);
    friend HugeInt&& operator+(const HugeInt  &lhs,       HugeInt &&rhs);
    friend HugeInt&& operator+(      HugeInt &&lhs, const HugeInt  &rhs);
    friend HugeInt&& operator+(      HugeInt &&lhs,       HugeInt &&rhs);
    friend HugeInt&& operator-(const HugeInt  &lhs, const HugeInt  &rhs);
    friend HugeInt&& operator-(const HugeInt  &lhs,       HugeInt &&rhs);
    friend HugeInt&& operator-(      HugeInt &&lhs, const HugeInt  &rhs);
    friend HugeInt&& operator-(      HugeInt &&lhs,       HugeInt &&rhs);

    HugeInt&  operator=(HugeInt &&rhs);


private:
    std::vector<int> num;
    void constructFromString(const std::string &str);

    // this list stores pointers of temp-objects created by + and - . prevent memory leak
    static std::list<HugeInt*> tmpObjectPtrs;
    // clear list tmpObjectsPtrs
    static void clearTmpObjects();

    static HugeInt& add(HugeInt &lhs, const HugeInt &rhs); // overwrite the result to lhs
    static HugeInt& sub(HugeInt &lhs, const HugeInt &rhs); // overwrite the result to lhs
};
std::list<HugeInt*> HugeInt::tmpObjectPtrs = std::list<HugeInt*>();


HugeInt::HugeInt()
{
    num.emplace_back(0);
}

HugeInt::HugeInt(const HugeInt &n)
{
    num = n.num;
}

HugeInt::HugeInt(HugeInt &&rhs)
{
    num = rhs.num;
}

HugeInt::HugeInt(const std::string &str)
{
    constructFromString(str);
}

HugeInt::HugeInt(const std::string &&str)
{
    constructFromString(str);
}

void HugeInt::constructFromString(const std::string &str)
{
    num.clear();
    for(int i=str.size()-1;i>=0;--i)
        num.emplace_back(str[i]-'0');
}

HugeInt::HugeInt(int n)
{
    while(n)
    {
        num.emplace_back(n%10);
        n /= 10;
    }
}

std::ostream& operator<<(std::ostream &out, HugeInt &n)
{
    for(int i=n.num.size()-1;i>=0;--i)
        out << n.num[i];
    return out;
}

std::ostream& operator<<(std::ostream &out, HugeInt &&n)
{
    out << n;
    return out;
}

std::istream& operator>>(std::istream &in, HugeInt &n)
{
    std::string str;
    in >> str;
    n.constructFromString(str);
    return in;
}

HugeInt&& operator+(const HugeInt  &lhs, const HugeInt  &rhs)
{
    HugeInt *tmp = new HugeInt(lhs);
    HugeInt::tmpObjectPtrs.emplace_back(tmp);
    return std::move( HugeInt::add(*tmp, rhs) );
}

HugeInt&& operator+(const HugeInt  &lhs,       HugeInt &&rhs)
{
    return std::move( HugeInt::add(rhs, lhs) );
}

HugeInt&& operator+(      HugeInt &&lhs, const HugeInt  &rhs)
{
    return std::move( HugeInt::add(lhs, rhs) );
}

HugeInt&& operator+(      HugeInt &&lhs,       HugeInt &&rhs)
{
    return std::move( HugeInt::add(lhs, rhs) );
}

HugeInt&& operator-(const HugeInt  &lhs, const HugeInt  &rhs)
{
    HugeInt *tmp = new HugeInt(lhs);
    HugeInt::tmpObjectPtrs.emplace_back(tmp);
    return std::move( HugeInt::sub(*tmp, rhs) );
}

HugeInt&& operator-(const HugeInt  &lhs,       HugeInt &&rhs)
{
    HugeInt *tmp = new HugeInt(lhs);
    HugeInt::tmpObjectPtrs.emplace_back(tmp);
    return std::move( HugeInt::sub(*tmp, rhs) );
}

HugeInt&& operator-(      HugeInt &&lhs, const HugeInt  &rhs)
{
    return std::move( HugeInt::sub(lhs, rhs) );
}

HugeInt&& operator-(      HugeInt &&lhs,       HugeInt &&rhs)
{
    return std::move( HugeInt::sub(lhs, rhs) );
}

HugeInt&  HugeInt::operator=(HugeInt &&rhs)
{
    this->num = rhs.num;
    clearTmpObjects();
    return *this;
}

void HugeInt::clearTmpObjects()
{
    for(auto &ptr : tmpObjectPtrs)
    {
        delete ptr;
    }
    tmpObjectPtrs.clear();
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
        lhs.num.emplace_back(1);
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
