#include "..\inc.h"
#include "CInitType.h"
#include "CThread.h"
#include <thread>
#include "CSyntax.h"
#include "CSTL.h"
#include "CPointer.h"

namespace cpp17
{
    void InitType()
    {
       
        //reference: https://en.cppreference.com/w/cpp/language/initialization
        // https://www.zhihu.com/question/36735960
        // https://www.zhihu.com/question/35843839/answer/64719309
        // https://www.zhihu.com/question/55773877
        //no user define constructor
        {
            {
                std::puts("--------default init-------");
                CValueInit a;  // id = random
                int i; // i = random
                TRACE_INFO("i = " << i);
            }
            {
                std::puts("--------value init-------");
                CValueInit a = CValueInit();  // id = 0
                int i = int(); // i = 0
                TRACE_INFO("i = " << i);
            }
            {
                std::puts("--------value init-------");
                CValueInit a = CValueInit{};  // id = 0
                int i = int{}; // i = 0;
                TRACE_INFO("i = " << i);
            }
            {
                std::puts("--------value init-------");
                CValueInit a{};  // id = 0;
                int i{}; // i = 0;
                TRACE_INFO("i = " << i);
            }
            {
                std::puts("--------default init-------");
                CValueInit* a = new CValueInit;  // id =  random
                delete a;

                int* pi = new int; //*pi = random
                TRACE_INFO("pi = " << *pi);
                delete pi;

                std::puts("--------value init-------");
                a = new CValueInit();  //id = 0
                delete a;

                pi = new int(); //*pi = 0
                TRACE_INFO("pi = " << *pi);
                delete pi;

                std::puts("--------value init-------");
                a = new CValueInit{};  //id = 0
                delete a;

                pi = new int{};  //*pi = 0
                TRACE_INFO("pi = " << *pi);
                delete pi;
            }
            {
                std::puts("-------aggregate initialization-------");
                CValueInit its[4] = { CValueInit(), CValueInit{} }; //, user zero init if params less then array size, so all id = 0;
            }
        }


        int i = 0;
    }

    CValueInit::~CValueInit()
    {
        TRACE_INFO_THIS("id = " << m_id);
    }

    CDefaultInit::CDefaultInit(const CDefaultInit& other)
    {
        m_id = other.m_id;
        TRACE_INFO_THIS("id = " << m_id);
    }

    CDefaultInit::CDefaultInit():CDefaultInit(0)
    {
        TRACE_INFO_THIS("id = " << m_id);
    }

    CDefaultInit::CDefaultInit(long long id):m_id{id}
    {
        TRACE_INFO_THIS("id = " << m_id);
    }

    CDefaultInit::~CDefaultInit()
    {
        TRACE_INFO_THIS("id = " << m_id);
    }

    CDefaultInit& CDefaultInit::operator=(const CDefaultInit& other)
    {
        m_id = other.m_id;
        TRACE_INFO_THIS("id = " << m_id);
        return *this;
    }

}

