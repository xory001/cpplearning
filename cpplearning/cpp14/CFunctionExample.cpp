#include "..\inc.h"
#include "CFunctionExample.h"


namespace cpp14
{
    //template<typename T> using TAddInt = auto FunctionExample_TAdd<T,T>;

    void InitFunctionExample()
    {
        FunctionExample_ptr();

        CFunctionExample<int> fr;
        auto r1 = fr.Add(1, 2);
        TRACE_INFO("r1 = " << r1);
    }

    void FunctionExample_ptr()
    {
        std::array<int, 32> buf{};
        for ( int i:buf)
        {
            TRACE_INFO("i = " << i);
        }

        //memset(buf.data(), 1, 32);
        //for (int i : buf)
        //{
        //    TRACE_INFO("i = " << i);
        //}

        typedef std::function< int(int, int) > TCalc;
        typedef int (*func)(int, int);
        //func pfn = FunctionExample_TAdd<int>;
        
        auto f1 = [](int a, int b){ return a + b; };
        auto fSub = [](int a, int b) { return a - b; };

        decltype(FunctionExample_TAdd<int>)* f2 = FunctionExample_TAdd<int>;
        int y3 = f2(1, 2);
        decltype(FunctionExample_Add)* f3 = FunctionExample_Add;
        std::map<std::string, TCalc> mapCalc;
        mapCalc.insert(std::make_pair("+", f1));
        mapCalc.insert({ "+", fSub });
        mapCalc.insert({ "+", FunctionExample_TAdd<int> });
        mapCalc.insert(std::make_pair("+", std::minus<int>()));
        mapCalc.insert(std::make_pair("+", f3));
    }

    int FunctionExample_Add(int a, int b)
    {
        return a + b;
    }

}
