
// opencvMFCLearningDlg.h: 头文件
//

#pragma once


// COpencvMFCLearningDlg 对话框
class COpencvMFCLearningDlg : public CDialogEx
{
// 构造
public:
	COpencvMFCLearningDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVMFCLEARNING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	void ShowImage(UINT32 uDlgItemId, const std::string& strFile, const std::string& strWindowName);
	void ClearOpenCVRes();


	std::vector<std::string> m_vecWindowName;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
};
