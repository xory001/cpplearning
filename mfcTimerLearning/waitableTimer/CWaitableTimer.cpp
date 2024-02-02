#include "pch.h"
#include "CWaitableTimer.h"
#include <synchapi.h>
#include <process.h>

CWaitableTimer::CWaitableTimer()
{
    m_bThreadExit = false;
    m_hEventRun = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadWaitableTimer, this, 0, NULL);

}

CWaitableTimer::~CWaitableTimer()
{
    m_bThreadExit = true;
    SetEvent(m_hEventRun);
    WaitForSingleObject(m_hThread, 50);
    CloseHandle(m_hThread);
    CloseHandle(m_hEventRun);
}

bool CWaitableTimer::Start(UINT uMilliSecondTick, bool bOneShot /*= FALSE*/)
{
    m_uMilliSecondTick = uMilliSecondTick;
    m_bOneShot = bOneShot;
    SetEvent(m_hEventRun);
    return true;
}

bool CWaitableTimer::Stop()
{
    ResetEvent(m_hEventRun);
    return true;
}

void CWaitableTimer::Ptimerapcroutine(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
    CWaitableTimer* pThis = (CWaitableTimer*)lpArgToCompletionRoutine;
    FILETIME ft = { dwTimerLowValue, dwTimerHighValue };
    SYSTEMTIME st{};
    BOOL bRet = FileTimeToSystemTime(&ft, &st);
    if ( bRet )
    {
        //do something
    }
    TRACE_INFO("wMilliseconds = " << st.wMilliseconds );
}

UINT CWaitableTimer::ThreadWaitableTimer(LPVOID lpVoid)
{
    CWaitableTimer* pThis = (CWaitableTimer*)lpVoid;

    std::wostringstream oss;
    oss << L"__waitable__" << GetTickCount64();
    //dwFlag: 0, CREATE_WAITABLE_TIMER_MANUAL_RESET, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
    //dwDesiredAccess: TIMER_ALL_ACCESS, must be run by an Administrator
    //m_hWaitableTimer = CreateWaitableTimerExW(NULL, oss.str().c_str(), 0, 0 ); 
    HANDLE hWaitableTimer = CreateWaitableTimerW(NULL, FALSE, oss.str().c_str());

    while ( !pThis->m_bThreadExit )
    {
        WaitForSingleObject(pThis->m_hEventRun, INFINITE);
        
        LARGE_INTEGER li = { 0 };
        //LocalFileTimeToFileTime()
        //SystemTimeToFileTime()
        //GetLocalTime()
        //GetSystemTime()
        //GetFileTime();

        UINT uMilliSecondTick = pThis->m_bOneShot ? 0 : pThis->m_uMilliSecondTick;
        //call Ptimerapcroutine once
        BOOL bRet = SetWaitableTimer(hWaitableTimer, &li, uMilliSecondTick, Ptimerapcroutine, lpVoid, TRUE);
        SleepEx(INFINITE, TRUE);
        CancelWaitableTimer(hWaitableTimer);
    }
    CloseHandle(hWaitableTimer);

    _endthreadex(0);
    return 0;
}
