#pragma once

#include <timeapi.h>
#include <Mmsystem.h>

class CEventTimer
{
public:
    CEventTimer();
    virtual ~CEventTimer();

public:
    bool Start( UINT uMilliSecondTick, bool bOneShot = FALSE );
    bool Stop();

protected:
    static void TimerCallback(
        UINT      uTimerID,
        UINT      uMsg,
        DWORD_PTR dwUser,
        DWORD_PTR dw1,
        DWORD_PTR dw2
        );

protected:
    TIMECAPS m_timerCaps = {};
    MMRESULT m_timerId = 0;
};

