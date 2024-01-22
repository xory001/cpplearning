#pragma once
#include "..\inc.h"

namespace cpp14
{
    void InitThread();


    class CThread
    {
    public:
        CThread();
        virtual ~CThread();

    public:
        template<typename T> auto Add(T&& a, T&& b);
        static void threadAdd(int nInitVale, int nStep, int nCount);
        static void threadRandom(const std::string& strThreadId);
        static void threadNone();
    };

    template<typename T>
    auto cpp14::CThread::Add(T&& a, T&& b)
    {
        TRACE_INFO_THIS("a.type = " << typeid(a).name() );
        return a + b;
    }

}

