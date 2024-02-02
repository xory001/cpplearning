#include "pch.h"
#include "CTimerQueueTimer.h"


CTimerQueueTimer::CTimerQueueTimer()
{

}

CTimerQueueTimer::~CTimerQueueTimer()
{
    Stop();
    

    if ( INVALID_HANDLE_VALUE != m_hTimerQueue )
    {
        DeleteTimerQueue(m_hTimerQueue);
    }
}

bool CTimerQueueTimer::Start(UINT uMilliSecondTick, bool bOneShot /*= FALSE*/)
{
    TRACE_INFO_THIS("uMilliSecondTick = " << uMilliSecondTick << ", bOneShot = " << bOneShot );
    if (INVALID_HANDLE_VALUE == m_hTimerQueue)
    {
        m_hTimerQueue = CreateTimerQueue();
    }
    if ( m_hTimerQueue )
    {
        if ( CreateTimerQueueTimer( &m_hTimerQueueTimer, m_hTimerQueue, WaitOrTimerCallback, 
            this, 0, bOneShot ? 0 : uMilliSecondTick, WT_EXECUTEINTIMERTHREAD) )
        {
            return true;
        }
    }
    return false;
}

bool CTimerQueueTimer::Stop()
{
    if (INVALID_HANDLE_VALUE != m_hTimerQueueTimer)
    {
        DeleteTimerQueueTimer(m_hTimerQueue, m_hTimerQueueTimer, NULL);
    }
    m_hTimerQueueTimer = NULL;

    return true;
}

//callback is another thread, not the same thread which call 'timeSetEvent'
void __stdcall CTimerQueueTimer::WaitOrTimerCallback(PVOID pVoid, BOOLEAN bTimerOrWaitFired)
{
    TRACE_INFO("");
}
