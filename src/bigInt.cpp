#include "bigInt.h"
#include <cstring>
#include <iostream>
using namespace std;

/// Initialization
BigInt::BigInt()
{
    num = "";
    sign = true;
}

BigInt::BigInt(const char* buffer)
{
    this->setNumber(buffer);
}

BigInt::BigInt(const Thread& buffer)
{
    this->setNumber(buffer);
}

BigInt::BigInt(const BigInt& source)
{
    Thread buffer = source.getNumber();
    bool sign = source.getSign();
    this->setNumber(buffer,sign);
}

void BigInt::operator = (const char* buffer)
{
    this->setNumber(buffer);
}

void BigInt::operator = (const Thread& buffer)
{
    this->setNumber(buffer);
}

void BigInt::operator = (const BigInt& source)
{
    Thread buffer = source.getNumber();
    bool sign = source.getSign();
    this->setNumber(buffer,sign);
}

///---------------------------------------------------------------->

///This compare function returns 2 if lhs>rhs or 1 if lhs<rhs
/// and 0 if lhs==rhs
int BigInt::compareMagnitude(const Thread& lhs,const Thread& rhs) const
{
    int m = lhs.length()-1,n = rhs.length()-1;
    if(m>n)
        return 2;
    if(m<n)
        return 1;
    while(m>=0 && n>=0)
    {
        if(lhs[m]>rhs[n])
            return 2;
        if(lhs[m]<rhs[n])
            return 1;
        m--;
        n--;
    }
    return 0;
}

Thread BigInt::getTensComplement(const Thread& buffer) const
{
    Thread res = "";
    int n = buffer.length()-1,z;
    while(n>=0)
    {
        z = 9 - buffer[n--]%48;
        res = (char)(z+48) + res;
    }
    Thread temp = "1";
    res = this->add(res,temp);
    return res;
}

///----------------------------------------------------------------->

///Arithmetic utility functions

Thread BigInt::add(const Thread& lhs,const Thread& rhs) const
{
    Thread res = "";
    int m = lhs.length()-1,n = rhs.length()-1;
    int c = 0,z;
    while(m>=0 && n>=0)
    {
        z = lhs[m--]%48 + rhs[n--]%48 + c;
        c = z/10;
        z = z%10;
        res = (char)(z+48) + res;
    }
    while(m>=0)
    {
        z = lhs[m--]%48 + c;
        c = z/10;
        z = z%10;
        res = (char)(z+48) + res;
    }
    while(n>=0)
    {
        z = rhs[n--]%48 + c;
        c = z/10;
        z = z%10;
        res = (char)(z+48) + res;
    }
    if(c)
        res = (char)(c+48) + res;
    return res;
}

///when passing rhs should always be the negative one
Thread BigInt::subtract(Thread& lhs,Thread& rhs) const
{
    Thread res = "";
    int m = lhs.length(),n = rhs.length();
    int z = this->compareMagnitude(lhs,rhs);
    if(z==0)
    {
        res = "0";
        return res;
    }
    if(m>n)
    {
        int i=0;
        while(i++<m-n)
            rhs = "0" + rhs;
    }
    if(m<n)
    {
        int i=0;
        while(i++<n-m)
            lhs = "0" + lhs;
    }
    Thread temp = this->getTensComplement(rhs);
    temp = this->add(lhs,temp);
    if(z==2)
    {
        for(int i=1;temp[i]!='\0';i++)
            res = res + temp[i];
    }
    if(z==1)
    {
        res = this->getTensComplement(temp);
        res = "-" + res;
    }
    return res;
}

Thread BigInt::multiply(Thread& lhs,Thread& rhs) const
{
    int m = lhs.length(),n = rhs.length();
    int i,j;
    int z,c=0,k=0;
    Thread res = "";
    Thread temp;
    for(i=m-1;i>=0;i--)
    {
        temp = "";
        z = k;
        while(z--)
            temp = temp + '0';
        for(j=n-1;j>=0;j--)
        {
            z = (lhs[i]%48)*(rhs[j]%48) + c;
            c = z/10;
            z = z%10;
            temp = (char)(z+48) + temp;
        }
        if(c)
            temp = (char)(c+48) + temp;
        res = this->add(res,temp);
        k++;
    }
    return res;
}

///----------------------------------------------------------------->

///----------------------------------------------------------------->
///Arithmetic operators

BigInt operator + (const BigInt& lhs,const BigInt& rhs)
{
    //BigInt temp;
    Thread res = "";
    Thread x = lhs.getNumber();
    Thread y = rhs.getNumber();
    bool lhsSign = lhs.getSign();
    bool rhsSign = rhs.getSign();
    if(lhsSign==rhsSign)
    {
        res = lhs.add(x,y);
        if(!lhsSign)
            res = '-' + res;
    }
    else
    {
        if(!lhsSign)
            res = lhs.subtract(y,x);
        if(!rhsSign)
            res = lhs.subtract(x,y);
    }
    BigInt temp(res);
    return temp;
}

BigInt operator - (const BigInt& lhs,const BigInt& rhs)
{
    BigInt temp;
    Thread x = lhs.getNumber();
    Thread y = rhs.getNumber();
    Thread res = "";
    bool lhsSign = lhs.getSign();
    bool rhsSign = !rhs.getSign();
    if(lhsSign == rhsSign)
    {
        res = lhs.add(x,y);
        if(!lhsSign)
            res = '-' + res;
    }
    else
    {
        if(!lhsSign)
            res = lhs.subtract(y,x);
        if(!rhsSign)
            res = lhs.subtract(x,y);
    }
    temp = res;
    return temp;
}

BigInt operator * (const BigInt& lhs,const BigInt& rhs)
{
    Thread x = lhs.getNumber();
    Thread y = rhs.getNumber();
    Thread res;
    bool lhsSign = lhs.getSign();
    bool rhsSign = rhs.getSign();
    res = lhs.multiply(x,y);
    if(lhsSign!=rhsSign)
        res = '-' + res;
    BigInt temp(res);
    return temp;
}

///---------------------------------------------------------------->

/// Utility Operator methods

bool BigInt::checkIfEqual(const Thread& x,const Thread& y) const
{
    int z = this->compareMagnitude(x,y);
    if(z==0)
        return true;
    return false;
}

bool BigInt::checkLarger(const BigInt& lhs,const BigInt& rhs) const
{
    bool lhsSign = lhs.getSign();
    bool rhsSign = rhs.getSign();
    if(lhsSign==rhsSign)
    {
        Thread x = lhs.getNumber();
        Thread y = rhs.getNumber();
        int z = this->compareMagnitude(x,y);
        if(lhsSign)
        {
            if(z==2)
                return true;
            else
                return false;
        }
        if(!lhsSign)
        {
            if(z==1)
                return true;
            else
                return false;
        }
    }
    else
    {
        if(!lhsSign)
            return false;
        if(!rhsSign)
            return true;
    }
    return false;
}

bool BigInt::checkLargerOrEqual(const BigInt& lhs,const BigInt& rhs) const
{
    bool lhsSign = lhs.getSign();
    bool rhsSign = rhs.getSign();
    if(lhsSign==rhsSign)
    {
        Thread x = lhs.getNumber();
        Thread y = rhs.getNumber();
        int z = this->compareMagnitude(x,y);
        if(lhsSign)
        {
            if(z==2 || z==0)
                return true;
            else
                return false;
        }
        if(!lhsSign)
        {
            if(z==1 || z==0)
                return true;
            else
                return false;
        }
    }
    else
    {
        if(!lhsSign)
            return false;
        if(!rhsSign)
            return true;
    }
    return false;
}

///---------------------------------------------------------------->

///Utility operators
bool operator == (const BigInt& lhs,const BigInt& rhs)
{
    Thread x = lhs.getNumber();
    Thread y = rhs.getNumber();
    bool lhsSign = lhs.getSign();
    bool rhsSign = rhs.getSign();
    bool res = lhs.checkIfEqual(x,y);
    if(res && lhsSign==rhsSign)
        return true;
    return false;
}

bool operator != (const BigInt& lhs,const BigInt& rhs)
{
    bool res = lhs==rhs;
    return !res;
}

bool operator > (const BigInt& lhs,const BigInt& rhs)
{
    bool res = lhs.checkLarger(lhs,rhs);
    return res;
}

bool operator < (const BigInt& lhs,const BigInt& rhs)
{
    bool res = lhs.checkLarger(rhs,lhs);
    return res;
}

bool operator >= (const BigInt& lhs,const BigInt& rhs)
{
    bool res = lhs.checkLargerOrEqual(lhs,rhs);
    return res;
}

bool operator <= (const BigInt& lhs,const BigInt& rhs)
{
    bool res = lhs.checkLargerOrEqual(rhs,lhs);
    return res;
}

///---------------------------------------------------------------->

///Getter and Setter methods

void BigInt::setNumber(const char* buffer)
{
    int k,n = strlen(buffer),i=0;
    if(buffer[0]=='-')
    {
        sign = false;
        k = 1;
    }
    else
    {
        sign = true;
        k = 0;
    }
    while(buffer[k]=='0')
        k++;
    if(k==n)
    {
        num = "0";
        return;
    }
    char* newBuffer = new char[n+1];
    for(;k<n;k++)
        newBuffer[i++] = buffer[k];
    newBuffer[i] = '\0';
    num = newBuffer;
    delete[] newBuffer;
}

void BigInt::setNumber(const Thread& buffer)
{
    int n = buffer.length();
    int k;
    if(buffer[0]=='-')
    {
        this->sign = false;
        k = 1;
    }
    else
    {
        this->sign = true;
        k = 0;
    }
    while(buffer[k]=='0')
        k++;
    if(k==n)
    {
        num = "0";
        return;
    }
    num = "";
    for(;k<n;k++)
        num = num + buffer[k];

}

void BigInt::setNumber(const Thread& buffer,bool sign)
{
    this->sign = sign;
    num = buffer;

}

Thread BigInt::getNumber() const
{
    return num;
}

bool BigInt::getSign() const
{
    return sign;
}

void BigInt::changeSign()
{
    this->sign = !this->sign;
}

///---------------------------------------------------------------->

ostream& operator >> (ostream& cout,BigInt& rhs)
{
    bool sign = rhs.getSign();
    Thread num = rhs.getNumber();
    if(!sign)
        cout<<"-";
    cout<<num;
    return cout;
}

