#pragma once


// CWndTimer

class CWndTimer : public CWnd
{
	DECLARE_DYNAMIC(CWndTimer)

public:
	CWndTimer();
	virtual ~CWndTimer();

public:
	static unsigned int __stdcall ThreadTimer(void* pVoid);

protected:
	DECLARE_MESSAGE_MAP()
};


