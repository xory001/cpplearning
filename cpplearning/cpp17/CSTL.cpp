#include <any>
#include <functional>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>


#include "CSTL.h"
#include "../inc.h"

CSTL::CSTL()
{

}

CSTL::~CSTL()
{

}

void CSTL::Start()
{
    m_threadMutex.Start();
    Sleep( 1000 * 2 );
    return;

    any();
    share_ptr();
    CSTL_StringBuf();
}

void CSTL::share_ptr()
{
    {
        // 1. test arr init;
        char* pBuf1 = new char[8]; //pBuf1 is all 0xcd
        char* pBuf2 = new char[8](); //pBuf2 is all 0x00
        delete[]pBuf1;
        delete[]pBuf2;
    }

    {
        // 2. share_ptr use class method as custom deleter 
        std::shared_ptr<int> sp3( new int[10](), std::default_delete<int[]>() );
        std::shared_ptr<int> pArrInt;
        pArrInt.reset( new int[4](), CSTL::deleteArr<int> );
    }



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

template< typename T>
bool CSTL::deleteArr( T* t )
{
    delete[]t;
    return true;
}

void CSTL::CSTL_StringBuf()
{
    int i = 0x1234;
    int j = 0x5678;
    std::stringbuf buf;
    buf.sputn( (const char*)&i, 4 );
    buf.sputn( (const char*)&j, 4 );
    std::string strData = buf.str();
    const char* ptr = strData.c_str();
    
    TRACE_INFO( "strData len = " << strData.length() );
}


/********
CSTL::any
*/
template<class T, class F>
inline std::pair<const std::type_index, std::function<void( std::any const& )>>
to_any_visitor( F const& f )
{
    return
    {
        std::type_index( typeid( T ) ),
        [g = f]( std::any const& a )
        {
            if constexpr ( std::is_void_v<T> )
                g();
            else
                g( std::any_cast<T const&>( a ) );
        }
    };
}

static std::unordered_map<std::type_index, std::function<void( std::any const& )>>
any_visitor
{
    to_any_visitor<void>( [] { std::cout << "{}"; } ),
    to_any_visitor<int>( []( int x ) { std::cout << x; } ),
    to_any_visitor<unsigned>( []( unsigned x ) { std::cout << x; } ),
    to_any_visitor<float>( []( float x ) { std::cout << x; } ),
    to_any_visitor<double>( []( double x ) { std::cout << x; } ),
    to_any_visitor<char const*>( []( char const* s )
        { std::cout << std::quoted( s ); } ),
    // ……为你的类型添加更多的处理器……
};

inline void process( const std::any& a )
{
    if ( const auto it = any_visitor.find( std::type_index( a.type() ) );
        it != any_visitor.cend() )
        it->second( a );
    else
        std::cout << "未注册类型 " << std::quoted( a.type().name() );
}

template<class T, class F>
inline void register_any_visitor( F const& f )
{
    std::cout << "为类型 "
        << std::quoted( typeid( T ).name() ) << " 注册访问者\n";
    any_visitor.insert( to_any_visitor<T>( f ) );
}



void CSTL::any()
{
    std::vector<std::any> va{ {}, 42, 123u, 3.14159f, 2.71828, "C++17" };

    std::cout << "{ ";
    for ( const std::any& a : va )
    {
        process( a );
        std::cout << ", ";
    }
    std::cout << "}\n";

    process( std::any( 0xFULL ) ); //< 反注册类型 "y"（unsigned long long）
    std::cout << '\n';

    register_any_visitor<unsigned long long>( []( auto x )
        {
            std::cout << std::hex << std::showbase << x;
        } );

    process( std::any( 0xFULL ) ); //< OK: 0xf
    std::cout << '\n';
}


