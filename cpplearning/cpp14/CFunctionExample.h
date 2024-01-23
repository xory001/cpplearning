#pragma once
#include "../inc.h"

namespace cpp14
{
    
    void InitFunctionExample();
    void FunctionExample_ptr();

    template < typename T > T FunctionExample_TAdd(const T&& a, const T&& b) { return a + b; }
    int FunctionExample_Add(int a, int b);

    template< typename T>
    class CFunctionExample
    {
    public:
        T Add(T t1, T t2) { return t1 + t2; }

    protected:
        T m_t1;
        T m_t2;
  

    };
}

