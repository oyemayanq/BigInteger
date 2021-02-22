#include "thread.h"
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------------------>
///Initialization
Thread::Thread()
{
    //ctor
    str = nullptr;
}

Thread::Thread(const char* buffer)
{
    this->setThread(buffer);

}

Thread::Thread(const Thread& source)
{
    char* buffer = source.getThread();
    this->setThread(buffer);
}

void Thread::operator = (const char* buffer)
{
    this->setThread(buffer);
}

void Thread::operator = (const Thread& source)
{
    char* buffer = source.getThread();
    this->setThread(buffer);
}

//----------------------------------------------------------------->

///Utility methods

char Thread::operator [] (int n) const
{
    return str[n];
}

/// add methods

char* Thread::add(const char& x,const char* y) const
{
    int i=0;
    int n = strlen(y);
    char* temp = new char[n+2];
    temp[0] = x;
    for(i=0;i<n;i++)
        temp[i+1] = y[i];
    temp[i+1] = '\0';
    return temp;
}

char* Thread::add(const char* x,const char& y) const
{
    int i=0;
    int n = strlen(x);
    char* temp = new char[n+2];
    for(i=0;i<n;i++)
        temp[i] = x[i];
    temp[i++] = y;
    temp[i] = '\0';
    return temp;
}

char* Thread::add(const char* x,const char* y) const
{
    int n = strlen(x) + strlen(y);
    int i=0,j=0,k=0;
    char* temp = new char[n+1];
    while(x[i]!='\0')
        temp[k++] = x[i++];
    while(y[j]!='\0')
        temp[k++] = y[j++];
    temp[k] = '\0';
    return temp;
}


/// + operator methods

Thread operator + (const char& lhs,const Thread& rhs)
{
    char* x = rhs.getThread();
    char* res = rhs.add(lhs,x);
    Thread temp(res);
    delete[] res;
    return temp;
}

Thread operator + (const Thread& lhs,const char& rhs)
{
    char* x = lhs.getThread();
    char* res = lhs.add(x,rhs);
    Thread temp(res);
    delete[] res;
    return temp;
}

Thread operator + (const char* lhs,const Thread& rhs)
{
    char* x = rhs.getThread();
    char* res = rhs.add(lhs,x);
    Thread temp(res);
    delete[] res;
    return temp;
}

Thread operator + (const Thread& lhs,const char* rhs)
{
    char* x = lhs.getThread();
    char* res = lhs.add(x,rhs);
    Thread temp(res);
    delete[] res;
    return temp;
}

Thread operator + (const Thread& lhs,const Thread& rhs)
{
    char* x = lhs.getThread();
    char* y = rhs.getThread();
    char* res = lhs.add(x,y);
    Thread temp(res);
    delete[] res;
    return temp;
}

//----------------------------------------------------------------->

///Output operator method

ostream& operator << (ostream& out,Thread& rhs)
{
    int i=0;
    char* res = rhs.getThread();
    for(;res[i]!='\0';i++)
        out<<res[i];
    return out;
}

//----------------------------------------------------------------->
///Getter and setter

int Thread::length() const
{
    return strlen(str);
}

void Thread::setThread(const char* buffer)
{
    int i=0;
    int n = strlen(buffer);
    str = new char[n+1];
    for(;i<n;i++)
        str[i] = buffer[i];
    str[i] = '\0';
}

char* Thread::getThread() const
{
    return str;
}

//------------------------------------------------------------------->

///Destructor

Thread::~Thread()
{
    //dtor
    delete[] str;
}
