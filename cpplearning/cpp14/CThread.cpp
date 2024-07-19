#include "CThread.h"
#include "../inc.h"
#include <thread>

namespace cpp17
{
    struct ThreadExecutor {
        void operator()() { /***/ }
    };

    void InitThread()
    {
        std::thread trd_1(ThreadExecutor()); // 1) 申明函数， c++ 推导规格：如果可以推导成函数申明，则必须推导成函数申明
        std::thread trd_2(ThreadExecutor{}); // 2) 创建了子线程
        std::thread trd_3{ ThreadExecutor{} }; // 3)


        std::thread a;
        
        
        CThread t1;
        int a1 = 10;
        int a2 = 20;
        int a3 = t1.Add(a1, a2);
        int a4 = t1.Add(1, 2);
        
    }


    CThread::CThread()
    {

    }

    CThread::~CThread()
    {

    }

    void CThread::threadAdd(int nInitVale, int nStep, int nCount)
    {
        TRACE_INFO("thread start");
        int n = 0;
        int nSum = 0;
        for (int i = nInitVale; ; i += nStep)
        {
            nSum += i;
            n++;
            TRACE_INFO("n = " << nSum << ", nSum = " << nSum);
            if (n >= nCount)
            {
                break;
            }
        }
        TRACE_INFO("thread stop");
    }

    void CThread::threadRandom(const std::string& strThreadId)
    {
        TRACE_DEBUG("thread start, id = " << strThreadId);
        int n = 0;
        int nSum = 0;
        for (int i = 0; i < 100; i++)
        {
            TRACE_DEBUG("i = " << i);
        }
        TRACE_DEBUG("thread stop, id = " << strThreadId);
    }

    void CThread::threadNone()
    {
        TRACE_WARNING("thread start");
        int n = 0;
        int nSum = 0;
        for (int i = 0; i < 100; i++)
        {
            TRACE_WARNING("i = " << i);
        }
        TRACE_WARNING("thread stop");
    }


}