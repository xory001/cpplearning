#pragma once
#include <iostream>

namespace nsoperator
{ 
    class COperator;

    void Init();

    typedef int (*pFnAdd)(int, int);
    int Add(int x, int y);
    COperator& Display(COperator& op);
    typedef COperator&(*pFnDispaly)(COperator&);

    //
    class COperator
    {
    public:
        COperator();
        COperator(int nAge);
        virtual ~COperator();
        COperator(const COperator& other);
        COperator& operator=( const COperator& other );


    public:
        COperator& operator+(int nAge); //class in operator override has one param only, https://blog.csdn.net/qq_44771627/article/details/122563302
        double operator()(int x1, int x2);
        int operator()(int x1, int x2, int x3);
        int operator()(pFnAdd fn, int x, int y );
        

    public:
        void Display();

    protected:
        //friend COperator& operator << (COperator& op, pFnDispaly fn);

    protected:
        int m_nAge;
    };


    COperator& operator << ( COperator& op, pFnDispaly fn ); //out of class operator override has two params

    COperator NewCOperator(int nAge);
}

