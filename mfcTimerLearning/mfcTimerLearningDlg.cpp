
// mfcTimerLearningDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "mfcTimerLearning.h"
#include "mfcTimerLearningDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMfcTimerLearningDlg 对话框



CMfcTimerLearningDlg::CMfcTimerLearningDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTIMERLEARNING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcTimerLearningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CMfcTimerLearningDlg::CreateConsole()
{
	if (AllocConsole())
	{
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "r", stdin);
		freopen("CON", "w", stderr);
		freopen("CON", "w", stdout);
	}
}

void CMfcTimerLearningDlg::DestroyConsole()
{
	fclose(stdin);
	fclose(stderr);
	fclose(stdout);
	FreeConsole();
}

BEGIN_MESSAGE_MAP(CMfcTimerLearningDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TIMER_EVENT_START, &CMfcTimerLearningDlg::OnBnClickedButtonTimerEventStart)
	ON_BN_CLICKED(IDC_BUTTONEVENT_TIMER_STOP, &CMfcTimerLearningDlg::OnBnClickedButtoneventTimerStop)
	ON_BN_CLICKED(IDC_BUTTON_WAITABLE_TIMER_START, &CMfcTimerLearningDlg::OnBnClickedButtonWaitableTimerStart)
	ON_BN_CLICKED(IDC_BUTTON_WAITABLE_TIMER_STOP, &CMfcTimerLearningDlg::OnBnClickedButtonWaitableTimerStop)
	ON_BN_CLICKED(IDC_BUTTON_TIMERQUEUE_TIMER_START, &CMfcTimerLearningDlg::OnBnClickedButtonTimerqueueTimerStart)
	ON_BN_CLICKED(IDC_BUTTON_TIMERQUEUE_TIMER_STOP, &CMfcTimerLearningDlg::OnBnClickedButtonTimerqueueTimerStop)
END_MESSAGE_MAP()


// CMfcTimerLearningDlg 消息处理程序

BOOL CMfcTimerLearningDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//DWORD dwRet = WaitForSingleObject(hEvent, INFINITE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMfcTimerLearningDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMfcTimerLearningDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMfcTimerLearningDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcTimerLearningDlg::OnBnClickedButtonTimerEventStart()
{
	CreateConsole();
	m_eventTimer.Start(10);
	xlog::CWriter(xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_DEBUG) << "text";
}


void CMfcTimerLearningDlg::OnBnClickedButtoneventTimerStop()
{
	m_eventTimer.Stop();
	DestroyConsole();
}


void CMfcTimerLearningDlg::OnBnClickedButtonWaitableTimerStart()
{
	m_waiableTimer.Start(10);
}


void CMfcTimerLearningDlg::OnBnClickedButtonWaitableTimerStop()
{
	m_waiableTimer.Stop();
}


void CMfcTimerLearningDlg::OnBnClickedButtonTimerqueueTimerStart()
{
	m_timerQueueTimer.Start(10, false);
}


void CMfcTimerLearningDlg::OnBnClickedButtonTimerqueueTimerStop()
{
	m_timerQueueTimer.Stop();
}
