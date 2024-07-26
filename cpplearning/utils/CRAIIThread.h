#ifndef __RAII_THREAD_H__
#define __RAII_THREAD_H__

#include <thread>

enum class RAII_THREAD_ACTION
{
    join,
    detach,
};

class CRAIIThread final
{
public:
    CRAIIThread();
    CRAIIThread( std::thread&& t, RAII_THREAD_ACTION a );
    CRAIIThread& operator = ( CRAIIThread&& other ) noexcept;

    virtual ~CRAIIThread();

public:
    void Reset( std::thread&& t, RAII_THREAD_ACTION a );
    std::thread& get() { return m_thread; }

private:
    RAII_THREAD_ACTION m_action;
    std::thread m_thread;
};

#endif
