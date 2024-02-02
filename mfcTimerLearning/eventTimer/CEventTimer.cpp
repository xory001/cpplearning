#include "pch.h"
#include "CEventTimer.h"


#pragma comment(lib, "Winmm.lib")

CEventTimer::CEventTimer()
{
    MMRESULT mr = timeGetDevCaps(&m_timerCaps, sizeof(TIMECAPS));
    if (MMSYSERR_NOERROR != mr )
    {
        //init err
    }
    //at windows 10 pro x64 22h2
    //m_timerCaps.wPeriodMin = 1;
    //m_timerCaps.wPeriodMin = 1;
    TRACE_INFO_THIS("wPeriodMin = " << m_timerCaps.wPeriodMin << ", wPeriodMin = " << m_timerCaps.wPeriodMin);
}

CEventTimer::~CEventTimer()
{
    if ( NULL != m_timerId )
    {
        timeKillEvent(m_timerId);
        timeEndPeriod(m_timerCaps.wPeriodMin);
    }
}

bool CEventTimer::Start(UINT uMilliSecondTick, bool bOneShot /*= FALSE */)
{
    TRACE_INFO_THIS("uMilliSecondTick = " << uMilliSecondTick);
    if ( NULL != m_timerId )
    {
        return false;
    }
    if ( ( 0 == m_timerCaps.wPeriodMax ) && ( 0 == m_timerCaps.wPeriodMin ) )
    {
        return false;
    }

    if ( uMilliSecondTick < m_timerCaps.wPeriodMin || uMilliSecondTick > m_timerCaps.wPeriodMax )
    {
        return false;
    }

    MMRESULT mr = timeBeginPeriod(m_timerCaps.wPeriodMin);
    if (TIMERR_NOERROR != mr)
    {
        return false;
    }

    m_timerId = timeSetEvent(uMilliSecondTick, 0, TimerCallback, 
        (DWORD_PTR)this, bOneShot ? TIME_ONESHOT : TIME_PERIODIC );
    if ( NULL == m_timerId )
    {
        return false;
    }

    return true;
}

bool CEventTimer::Stop()
{
    MMRESULT mr = timeKillEvent(m_timerId);
    m_timerId = NULL;
    if (TIMERR_NOERROR != mr )
    {
        //has err
    }
    mr = timeEndPeriod(m_timerCaps.wPeriodMin);
    if (TIMERR_NOERROR != mr)
    {
        return false;
    }
    return true;
}

//callback is another thread, not the same thread which call 'timeSetEvent'
void CEventTimer::TimerCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    CEventTimer* pThis = (CEventTimer*)dwUser;
    TRACE_INFO("uTimerID = " << uTimerID);
}
