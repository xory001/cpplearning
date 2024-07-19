#include <iostream>
#include "CSyntax.h"
#include "../inc.h"

namespace cpp17
{
    class A 
    {
    public:
        A() {}
        A(const A&) = delete;
        A& operator=(const A&) = delete;
        A(A&&) = default;
    };
    void f(A&& a) {}

    void StartGramma()
    {
        StartGramma_RRef();

        Gramma_Lambda();
        Testdectype();
        TestInitList();
    }

    void StartGramma_RRef()
    {
        //https://www.zhihu.com/question/302399669
        A a;
        auto f0 = [a{ std::move(a) }]()mutable->void {f(std::move(a)); };

        int i = 10;
        int& ri = i;
        int&& rii = 10;
        int&& rii2 = std::move(i);

        int nSize = 0;
        CGramma g(10);
        g.GetSize();
        g.GetSizeV2();
        //g.GetSizeV3(); //err
        g.GetSizeExEx();
        g.GetSizeExExV2();
        //g.GetSizeExExV3();  //err

        CGramma&& rrg = CGramma(20);  //the rvalue variable is lvalue
        rrg.GetSize();
        rrg.GetSizeV2();
        //nSize = rrg.GetSizeV3();
        nSize = std::move(rrg).GetSizeV3();
        nSize = CGramma(100).GetSizeV3();
        //rrg.GetSizeExV3();
    }

    void Gramma_Lambda()
    {
        auto f = [](auto a, auto b) { TRACE_INFO("a = " << a << ", b = " << b); return a + b; };
        auto ret1 = f(1, 2);
        TRACE_INFO("ret = " << ret1);

        auto ret2 = f(std::string( "a"), "b");
        TRACE_INFO("ret = " << ret2);
    }

    int gramma_add(int a, int b)
    {
        return a + b;
    }



    int Testdectype()
    {
        auto f = [](int a, int b) -> decltype(a + b) { return a + b; };
        auto sum = f(1, 2);

        auto f1 = [] { TRACE_INFO(""); return 0; };

        std::vector< int > vecInt;
        [&vecInt] { for (int i = 0; i < 10; i++) { vecInt.push_back(i); } }();

        decltype (f1()) total = sum;

        decltype (f(1, 2)) total2 = sum;

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


}