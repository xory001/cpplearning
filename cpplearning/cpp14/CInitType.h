#pragma once

namespace cpp17
{


    //func
    void InitType();


    //class
    class CValueInit
    {
    public:
        virtual ~CValueInit();

    protected:
        long long m_id;
    };

    class CDefaultInit
    {
    public:
        CDefaultInit();
        CDefaultInit( long long  id );
        CDefaultInit(const CDefaultInit& other);
        virtual ~CDefaultInit();
        CDefaultInit& operator=(const CDefaultInit& other);
        

    protected:
        long long m_id;
    };
};

