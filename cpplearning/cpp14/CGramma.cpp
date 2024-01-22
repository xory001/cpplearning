#include <iostream>
#include "CGramma.h"
#include "../inc.h"

void CGramma_Test()
{
    Testdectype();
    TestInitList();
}

int gramma_add(int a, int b)
{
    return a + b;
}

int Testdectype()
{
    auto f = [](int a, int b) -> decltype( a + b ) { return a + b; };
    auto sum = f(1, 2);

    auto f1 = [] { TRACE_INFO(""); return 0; };

    std::vector< int > vecInt;
    [&vecInt] { for (int i = 0; i < 10; i++) { vecInt.push_back(i); } }();

    decltype (f1()) total = sum;

    decltype (f(1,2)) total2 = sum;

    auto plus = [](int v1, int v2) -> int { return v1 + v2; };
    int sum2 = plus(1, 2);

    int j = 0;

    //using fnType = void(void);
    //fnType f1 = TestInitList;
    //f1();

    return 0;
}

void TestInitList()
{
    CGramma c1 = CGramma(10); //only call CGramma::CGramma(int size)

    return;
}

CGramma::CGramma(int size)
{
    TRACE_INFO_THIS("size = " << size);
    m_nSize = size;
}

CGramma::CGramma(const CGramma& other)
{
    TRACE_INFO_THIS("size = " << other.m_nSize);
    m_nSize = other.m_nSize;
}

CGramma::~CGramma()
{
    TRACE_INFO_THIS("");
}

CGramma& CGramma::operator=(const CGramma& other)
{
    TRACE_INFO_THIS("size = " << other.m_nSize);
    m_nSize = other.m_nSize;
    return *this;
}

int CGramma::GetSize()
{
    return m_nSize;
}
