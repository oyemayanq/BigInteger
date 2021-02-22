#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include "thread.h"

using namespace std;

class BigInt
{
    public:
        ///Initialization

        BigInt();
        BigInt(const char*);
        BigInt(const Thread&);
        BigInt(const BigInt&);

        void operator = (const char*);
        void operator = (const Thread&);
        void operator = (const BigInt&);


        ///Arithmetic operations
        friend BigInt operator + (const BigInt&,const BigInt&);
        friend BigInt operator - (const BigInt&,const BigInt&);
        friend BigInt operator * (const BigInt&,const BigInt&);

        friend bool operator == (const BigInt&,const BigInt&);
        friend bool operator != (const BigInt&,const BigInt&);
        friend bool operator > (const BigInt&,const BigInt&);
        friend bool operator < (const BigInt&,const BigInt&);
        friend bool operator >= (const BigInt&,const BigInt&);
        friend bool operator <= (const BigInt&,const BigInt&);

        friend ostream& operator >> (ostream&,BigInt&);

    private:
        Thread num;
        bool sign;

        void setNumber(const char*);
        void setNumber(const Thread&);
        void setNumber(const Thread&,bool);
        Thread getNumber() const;
        bool getSign() const;
        void changeSign();

        int compareMagnitude(const Thread&,const Thread&) const;
        Thread add(const Thread&,const Thread&) const;
        Thread subtract(Thread&,Thread&) const;
        Thread multiply(Thread&,Thread&) const;
        Thread getTensComplement(const Thread&) const;

        bool checkIfEqual(const Thread&,const Thread&) const;
        bool checkLarger(const BigInt&,const BigInt&) const;
        bool checkLargerOrEqual(const BigInt&,const BigInt&) const;
};

#endif // BIGINT_H
