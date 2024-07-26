#include "CRAIIThread.h"

CRAIIThread::CRAIIThread()
{

}

CRAIIThread::CRAIIThread( std::thread&& t, RAII_THREAD_ACTION a ) : m_action( a ), m_thread( std::move( t ) )
{

}

CRAIIThread& CRAIIThread::operator=( CRAIIThread&& other ) noexcept
{
    if ( this == &other )
    {
        return *this;
    }
    m_action = other.m_action;
    m_thread = std::move( other.m_thread );

    return *this;
}

CRAIIThread::~CRAIIThread()
{
    if ( m_thread.joinable() ) 
    {
        if ( m_action == RAII_THREAD_ACTION::join ) 
        {
            m_thread.join();
        }
        else {
            m_thread.detach();
        }
    }
}

void CRAIIThread::Reset( std::thread&& t, RAII_THREAD_ACTION a )
{
    m_action = a;
    //m_thread = t;

}
