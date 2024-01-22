#include "CSTL.h"
#include "../inc.h"

void CSTL_Init()
{
    CSTL_Ptr();
}

void CSTL_Ptr()
{
    int* p = new int[32];
    for ( int i = 0; i < 32; i++ )
    {
        p[i] = i;
    }
    std::shared_ptr<int*> szBuf = std::make_shared<int*>( new int[8] );
    int *pszBuf = *szBuf;
    TRACE_INFO("szBuf = " << *szBuf);
    //(*szBuf)[0] = 1;
    //char a = szBuf[0];
    delete p;
    p = nullptr;
}

CSTL::CSTL()
{

}

CSTL::~CSTL()
{

}


