
// Exp1TestMyDLLDlg.h : 头文件
//

#pragma once

enum CALL{
	C_CALL,
	STD_CALL
};//标志两种调用方式

//使用条件编译的方式实现静态和动态两种调用方式
//#define _STATIC


// CExp1TestMyDLLDlg 对话框
class CExp1TestMyDLLDlg : public CDialogEx
{
// 构造
public:
	CExp1TestMyDLLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXP1TESTMYDLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void OnDestroy();
public:
	int m_call;
	CALL op_call;
	afx_msg void OnRadioClickedCall(UINT nID);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedReverse();
#ifndef _STATIC
	HMODULE hm;
	afx_msg void LoadDLL();
#endif
};
