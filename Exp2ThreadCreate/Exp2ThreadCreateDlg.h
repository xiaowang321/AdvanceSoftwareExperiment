
// Exp2ThreadCreateDlg.h : 头文件
//

#pragma once
#include "CircleBuffer.h"
#include "afxwin.h"


// CExp2ThreadCreateDlg 对话框
class CExp2ThreadCreateDlg : public CDialogEx
{
// 构造
public:
	CExp2ThreadCreateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXP2THREADCREATE_DIALOG };

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
public:
	CircleBuffer *buffer;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnDestroy();
	CEdit m_readdata;
	CEdit m_writedata;
};
//线程相关变量、函数
UINT ReadProc(LPVOID lpParam);//读线程函数
UINT WriteProc(LPVOID lpParam);//写线程函数
unsigned int GetRand(unsigned int MIN, unsigned int MAX);//随机数函数
void LogWriteData(NODE data);//将写线程的数据写入日志文件
CString FormatData(NODE data);//将读线程的数据构成符合一定格式的字符串
