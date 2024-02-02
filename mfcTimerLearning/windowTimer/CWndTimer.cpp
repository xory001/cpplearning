// D:\xory\svnclient\cpplearning\mfcTimerLearning\windowTimer\CWndTimer.cpp: 实现文件
//

#include "pch.h"
#include "../mfcTimerLearning.h"
#include "CWndTimer.h"
#include <process.h>

// CWndTimer

IMPLEMENT_DYNAMIC(CWndTimer, CWnd)

CWndTimer::CWndTimer()
{

}

CWndTimer::~CWndTimer()
{
}


unsigned int __stdcall CWndTimer::ThreadTimer(void* pVoid)
{
    _endthreadex(0);
    return 0;
}

BEGIN_MESSAGE_MAP(CWndTimer, CWnd)
END_MESSAGE_MAP()



// CWndTimer 消息处理程序


