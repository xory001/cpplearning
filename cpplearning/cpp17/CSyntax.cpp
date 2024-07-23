#include <iostream>
#include <exception>
#include "CSyntax.h"
#include "../inc.h"

namespace cpp17
{



    CSyntax_ReturnValOptimi::CSyntax_ReturnValOptimi():m_nIntVal(0)
    {
        TRACE_INFO_THIS( "" );
    }


    CSyntax_ReturnValOptimi::CSyntax_ReturnValOptimi( int nVal ):CSyntax_ReturnValOptimi( nVal, "" )
    {
        TRACE_INFO_THIS( "m_nIntVal = " << m_nIntVal );
    }

    CSyntax_ReturnValOptimi::CSyntax_ReturnValOptimi( const std::string& strVal ) : CSyntax_ReturnValOptimi( 0, strVal )
    {
        TRACE_INFO_THIS( "strVal = " << strVal );
    }

    CSyntax_ReturnValOptimi::CSyntax_ReturnValOptimi( int nVal, const std::string& strVal ) : m_nIntVal(nVal), m_strVal{strVal}
    {
        TRACE_INFO_THIS( "m_nIntVal = " << m_nIntVal << ", m_strVal = " << m_strVal );
    }

    CSyntax_ReturnValOptimi::~CSyntax_ReturnValOptimi()
    {
        TRACE_INFO_THIS( "" );
    }

    void CSyntax_ReturnValOptimi::Display()
    {
        TRACE_INFO_THIS( "m_nIntVal = " << m_nIntVal << ", m_strVal = " << m_strVal );
    }

    ///////
    ///////CSyntax
    ///////
    CSyntax::CSyntax()
    {

    }

    CSyntax::~CSyntax()
    {
        TRACE_INFO_THIS("");
    }

    void CSyntax::Start()
    {
        /*
        2024.07.22 10:13:25.214 INFO    [t=2424][this=0x0000005CD295ED98]
        [cpp17::CSyntax_ReturnValOptimi::CSyntax_ReturnValOptimi:29][m_nIntVal = 1, m_strVal = a]

        2024.07.22 10:13:25.217 INFO    [t=2424][this=0x0000005CD295ED98]
        [cpp17::CSyntax_ReturnValOptimi::~CSyntax_ReturnValOptimi:34][]

        2024.07.22 10:13:25.220 INFO    [t=2424][this=0x0000005CD295EF48]
        [cpp17::CSyntax_ReturnValOptimi::Display:39][m_nIntVal = 1, m_strVal = a]
        */
        CSyntax_ReturnValOptimi retVal = ReturnValueOptimization();
        retVal.Display();
        TRACE_INFO_THIS( "----------call ReturnValueOptimization( 1 )" );

        /*
        2024.07.22 10:13:25.226 INFO    [t=2424][this=0x0000005CD295ED08]
        [cpp17::CSyntax_ReturnValOptimi::CSyntax_ReturnValOptimi:29][m_nIntVal = 1, m_strVal = 1]

        2024.07.22 10:13:25.230 INFO    [t=2424][this=0x0000005CD295ED08]
        [cpp17::CSyntax_ReturnValOptimi::~CSyntax_ReturnValOptimi:34][]

        2024.07.22 10:13:25.234 INFO    [t=2424][this=0x0000005CD295EF98]
        [cpp17::CSyntax_ReturnValOptimi::Display:39][m_nIntVal = 1, m_strVal = 1]
        */
        CSyntax_ReturnValOptimi retVal1 = ReturnValueOptimization( 1 );
        retVal1.Display();

        system( "pause" );

        RRef();
        Lambda();
        Decltype();
    }

    void f( CSyntax_A&& a ) {}
    void CSyntax::RRef()
    {
        //https://www.zhihu.com/question/302399669
        CSyntax_A a;
        auto f0 = [a{ std::move( a ) }]()mutable->void {f( std::move( a ) ); };
    }


    void CSyntax::Lambda()
    {
        auto f = []( auto a, auto b ) { TRACE_INFO( "a = " << a << ", b = " << b ); return a + b; };
        auto ret1 = f( 1, 2 );
        TRACE_INFO( "ret = " << ret1 );

        auto ret2 = f( std::string( "a" ), "b" );
        TRACE_INFO( "ret = " << ret2 );
    }

    void CSyntax::Decltype()
    {
        auto f = []( int a, int b ) -> decltype( a + b ) { return a + b; };
        auto sum = f( 1, 2 );

        auto f1 = [] { TRACE_INFO( "" ); return 0; };

        std::vector< int > vecInt;
        [&vecInt] { for ( int i = 0; i < 10; i++ ) { vecInt.push_back( i ); } }( );

        decltype ( f1() ) total = sum;

        decltype ( f( 1, 2 ) ) total2 = sum;

        auto plus = []( int v1, int v2 ) -> int { return v1 + v2; };
        int sum2 = plus( 1, 2 );

        int j = 0;

        //using fnType = void(void);
        //fnType f1 = TestInitList;
        //f1();

    }


    CSyntax_ReturnValOptimi CSyntax::ReturnValueOptimization()
    {
        //vs2019 has no effect for /Zc:nrvo- 
        CSyntax_ReturnValOptimi retVal{ 1, "a" };
        return retVal;
    }

    CSyntax_ReturnValOptimi CSyntax::ReturnValueOptimization( int nVal )
    {
        if ( nVal )
        {
            CSyntax_ReturnValOptimi rvo1{ nVal, "1" };
            return rvo1;
        }
        else
        {
            CSyntax_ReturnValOptimi rvo0{ nVal, "0" };
            return rvo0;
        }
    }

}