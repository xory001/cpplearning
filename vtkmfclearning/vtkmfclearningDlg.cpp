
// vtkmfclearningDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "vtkmfclearning.h"
#include "vtkmfclearningDlg.h"
#include "afxdialogex.h"

//vtk
#include <vtkAutoInit.h>
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"  
#include <vtkWin32OpenGLRenderWindow.h>

//VTK_MODULE_INIT(vtkRandomGraphSource);

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


// CVTKMFCLearningDlg 对话框



CVTKMFCLearningDlg::CVTKMFCLearningDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VTKMFCLEARNING_DIALOG, pParent)
{
	_renWin = nullptr;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVTKMFCLearningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CVTKMFCLearningDlg::RunVtk()
{
    vtkConeSource* cone = vtkConeSource::New();
    cone->SetHeight(3.0);
    cone->SetRadius(1.0);
    cone->SetResolution(10);

    //
    // In this example we terminate the pipeline with a mapper process object.
    // (Intermediate filters such as vtkShrinkPolyData could be inserted in
    // between the source and the mapper.)  We create an instance of
    // vtkPolyDataMapper to map the polygonal data into graphics primitives. We
    // connect the output of the cone source to the input of this mapper.
    //
    vtkPolyDataMapper* coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInputConnection(cone->GetOutputPort());

    //
    // Create an actor to represent the cone. The actor orchestrates rendering
    // of the mapper's graphics primitives. An actor also refers to properties
    // via a vtkProperty instance, and includes an internal transformation
    // matrix. We set this actor's mapper to be coneMapper which we created
    // above.
    //
    vtkActor* coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);

    //
    // Create the Renderer and assign actors to it. A renderer is like a
    // viewport. It is part or all of a window on the screen and it is
    // responsible for drawing the actors it has.  We also set the background
    // color here.
    //
    vtkRenderer* ren1 = vtkRenderer::New();
    ren1->AddActor(coneActor);
    ren1->SetBackground(0.1, 0.2, 0.4);

    //
    // Finally we create the render window which will show up on the screen.
    // We put our renderer into the render window using AddRenderer. We also
    // set the size to be 300 pixels by 300.
    //
    _renWin = vtkWin32OpenGLRenderWindow::New();
	_renWin->AddRenderer(ren1);
	_renWin->SetSize(300, 300);
	_renWin->SetParentId(m_hWnd);
	_renWin->MakeRenderWindowInteractor()->Start();
    //_renWin->MakeRenderWindowInteractor()->Start(); //add by xory,
    //
    // Now we loop over 360 degrees and render the cone each time.
    //
    //int i;
    //for (i = 0; i < 360; ++i)
    {
        // render the image
     //   renWin->Render();
        // rotate the active camera by one degree
    //    ren1->GetActiveCamera()->Azimuth(1);
    }

    //vtkRandomGraphSource* source = vtkRandomGraphSource::New();

    //vtkGraphLayoutView* view = vtkGraphLayoutView::New();
    //view->SetRepresentationFromInputConnection(
    //    source->GetOutputPort());

    //view->ResetCamera();
    //view->Render();
    //view->GetRenderWindow()->SetParentId( m_hWnd );
    //view->GetInteractor()->Start();

    //source->Delete();
    //view->Delete();
}

BEGIN_MESSAGE_MAP(CVTKMFCLearningDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CVTKMFCLearningDlg 消息处理程序

BOOL CVTKMFCLearningDlg::OnInitDialog()
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

	ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);
	RunVtk();

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVTKMFCLearningDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVTKMFCLearningDlg::OnPaint()
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
		_renWin->Render();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVTKMFCLearningDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

