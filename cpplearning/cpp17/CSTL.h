#pragma once
#include "CSTLThreadMutex.h"

class CSTL
{
public:
    CSTL();
    ~CSTL();

public:
    void Start();

protected:
    void share_ptr();
    void CSTL_StringBuf();
    void any();

    //deleter
    template< typename T>
    static bool deleteArr( T* t );

private:
    CSTLThreadMutex m_threadMutex;
};

