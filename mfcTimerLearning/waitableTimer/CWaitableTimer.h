#pragma once

class CWaitableTimer
{
public:
    CWaitableTimer();
    virtual ~CWaitableTimer();

public:
    bool Start(UINT uMilliSecondTick, bool bOneShot = FALSE);
    bool Stop();

protected:
    static void APIENTRY Ptimerapcroutine(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue);
    
    static UINT ThreadWaitableTimer(LPVOID lpVoid);
    bool m_bThreadExit = false;

protected:
    HANDLE m_hThread = INVALID_HANDLE_VALUE;
    HANDLE m_hEventRun = INVALID_HANDLE_VALUE;
    UINT m_uMilliSecondTick = 0;
    bool m_bOneShot = false;
};

