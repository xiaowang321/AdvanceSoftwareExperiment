
// Exp6ComponentDesignDlg.h : 头文件
//

#pragma once

typedef CString(*dll_proc)(void);

// CExp6ComponentDesignDlg 对话框
class CExp6ComponentDesignDlg : public CDialogEx
{
// 构造
public:
	CExp6ComponentDesignDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXP6COMPONENTDESIGN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon; 
	CMenu m_hMenu;
	CDWordArray m_dwa;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	void LoadDLL();
	afx_msg void OnFunc1();
	afx_msg void OnFunc2();
	afx_msg void OnFunc3();
	afx_msg void ExecuteFuncFromDLL(int);
};
