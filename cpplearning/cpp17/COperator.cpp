#include "COperator.h"
#include <iostream>
#include "../inc.h"
#include <string.h>

namespace nsoperator
{ 
    void Init()
    {
       // CLog() << "DEBUG" << 1 << "123";
       // LDEBUG("nsoperator::Init" );
        //LDEBUG( 1 );
        std::wstring a(L"ÖÐ¹ú");
        //XTRACE_DEBUG( a );
        //XTRACE_DEBUG("1 = " << 1 << ", 123");

        COperator op;
        op.Display();
        op + 3;
        op.Display();
        op.operator+(4);
        op.Display();
        auto res1 = op.operator()( 1, 5 );
        auto res2 = op.operator()(1, 2, 3);
        auto res3 = op(1, 6);
        auto res4 =  op( 4, 5, 6);
        auto res5 = op(Add, 1, 9);
        op << Display;
       
        
        COperator op2 = NewCOperator(2);
        op2 = op2;

        std::cout << "COperater::Init exit" << std::endl;
    }

    int Add(int x, int y)
    {
        return x + y;
    }



    COperator& Display(COperator& op)
    {
        std::cout << "nsoperator::Display enter" << std::endl;
        op.Display();
        std::cout << "nsoperator::Display exit" << std::endl;
        return op;
    }

    COperator NewCOperator(int nAge)
    {
        COperator op(nAge);
        return op;
    }

    COperator::COperator()
    {
        m_nAge = 0;
    }

    COperator::COperator(const COperator& other)
    {
        std::cout << "COperator::COperator, other =  " << &other << std::endl;
        m_nAge = other.m_nAge;
    }

    COperator::COperator(int nAge)
    {
        //XTRACE_DEBUG_THIS("nAge = " << nAge);
        m_nAge = nAge;
    }

    COperator::~COperator()
    {

    }

    COperator& COperator::operator=(const COperator& other)
    {
        std::cout << "COperator::operator=, enter " << std::endl;
        if ( this == &other )
        {
            std::cout << "COperator::operator=, same inst, return *this " << std::endl;
            return *this;
        }
        m_nAge = other.m_nAge;
        std::cout << "COperator::operator=, exit " << std::endl;
        return *this;
    }

    COperator& COperator::operator+(int nAge)
    {
        m_nAge += nAge;
        return *this;
    }

    double COperator::operator()(int x1, int x2)
    {
        return ( (double)x1 + (double)x2 ) / 2;
    }

    int COperator::operator()(int x1, int x2, int x3)
    {
        return 0;// std::max(std::max(x1, x2), x3);
    }

    int COperator::operator()(pFnAdd fn, int x, int y)
    {
        return fn(x, y);
    }


    void COperator::Display()
    {
        std::cout << "COperator::Display, m_nAge = " << m_nAge << std::endl;
    }

    COperator& operator<<(COperator& op, pFnDispaly fn)
    {
        return fn(op);
    }
}

