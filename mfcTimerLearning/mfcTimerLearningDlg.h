
// mfcTimerLearningDlg.h: 头文件
//

#pragma once

#include "eventTimer/CEventTimer.h"
#include "waitableTimer/CWaitableTimer.h"
#include "timerQueueTimer/CTimerQueueTimer.h"

// CMfcTimerLearningDlg 对话框
class CMfcTimerLearningDlg : public CDialogEx
{
// 构造
public:
	CMfcTimerLearningDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTIMERLEARNING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	void CreateConsole();
	void DestroyConsole();


protected:
	CEventTimer m_eventTimer;
	CWaitableTimer m_waiableTimer;
	CTimerQueueTimer m_timerQueueTimer;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTimerEventStart();
	afx_msg void OnBnClickedButtoneventTimerStop();
	afx_msg void OnBnClickedButtonWaitableTimerStart();
	afx_msg void OnBnClickedButtonWaitableTimerStop();
	afx_msg void OnBnClickedButtonTimerqueueTimerStart();
	afx_msg void OnBnClickedButtonTimerqueueTimerStop();
};
