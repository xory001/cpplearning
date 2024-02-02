#pragma once

class CTimerQueueTimer
{
public:
    CTimerQueueTimer();
    virtual ~CTimerQueueTimer();
public:
    bool Start(UINT uMilliSecondTick, bool bOneShot = FALSE);
    bool Stop();

protected:
    static void __stdcall WaitOrTimerCallback(PVOID pVoid, BOOLEAN bTimerOrWaitFired );

protected:
    HANDLE m_hTimerQueue = INVALID_HANDLE_VALUE;
    HANDLE m_hTimerQueueTimer = INVALID_HANDLE_VALUE;
};

