
// Exp1TestMyDLLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exp1TestMyDLL.h"
#include "Exp1TestMyDLLDlg.h"
#include "afxdialogex.h"


#ifdef _STATIC
#include "simple_dll.h"
#pragma comment(lib,"simple_dll.lib")
#endif
#ifndef _STATIC
typedef int(*add)(int, int);
typedef void(*reverse)(char*);
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp1TestMyDLLDlg 对话框



CExp1TestMyDLLDlg::CExp1TestMyDLLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExp1TestMyDLLDlg::IDD, pParent)
	, m_call(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExp1TestMyDLLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_CCALL, m_call);
}

BEGIN_MESSAGE_MAP(CExp1TestMyDLLDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CCALL,IDC_STDCALL,&OnRadioClickedCall)
	ON_BN_CLICKED(IDC_ADD, &CExp1TestMyDLLDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REVERSE, &CExp1TestMyDLLDlg::OnBnClickedReverse)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CExp1TestMyDLLDlg 消息处理程序

BOOL CExp1TestMyDLLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CButton*)GetDlgItem(IDC_CCALL))->SetCheck(TRUE);
	op_call = C_CALL;
#ifndef _STATIC
	LoadDLL();
#endif
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExp1TestMyDLLDlg::OnPaint()
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
HCURSOR CExp1TestMyDLLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExp1TestMyDLLDlg::OnRadioClickedCall(UINT nID)
{
	switch (nID){
	case IDC_CCALL:
		op_call = C_CALL;
		GetDlgItem(IDC_RESULT)->SetWindowText("");
		GetDlgItem(IDC_REVERSESTR)->SetWindowText("");
		break;
	case IDC_STDCALL:
		op_call = STD_CALL;
		GetDlgItem(IDC_RESULT)->SetWindowText("");
		GetDlgItem(IDC_REVERSESTR)->SetWindowText("");
		break;
	}
}

void CExp1TestMyDLLDlg::OnDestroy(){
#ifndef _STATIC
	if (hm != NULL){
		FreeLibrary(hm);
	}
#endif
	SendMessage(WM_CLOSE);
}

void CExp1TestMyDLLDlg::OnBnClickedAdd()
{
	CString intx_str, inty_str, result_str;
	int intx, inty, result;
	GetDlgItem(IDC_NUM1)->GetWindowText(intx_str);
	GetDlgItem(IDC_NUM2)->GetWindowText(inty_str);
	if (intx_str.IsEmpty() || inty_str.IsEmpty()){
		MessageBox(_T("参数不完整，请输入待求和的整数"),_T("动态链接库的编写和调用"));
		return;
	}
	intx = _ttoi(intx_str);
	inty = _ttoi(inty_str);
	if (op_call == C_CALL){
#ifdef _STATIC
		result = c_add(intx, inty);
#endif
#ifndef _STATIC
		add dll_add = NULL;
		dll_add = (add)GetProcAddress((HINSTANCE)hm, "c_add");
		if (dll_add != NULL){
			result = dll_add(intx, inty);
		}
		else{
			MessageBox(_T("DLL加载失败，调用失效！"), _T("动态链接库的动态加载"));
			return;
		}
#endif
	}
	else{
#ifdef _STATIC
		result = s_add(intx,inty);
#endif
#ifndef _STATIC
		add dll_add = NULL;
		dll_add = (add)GetProcAddress((HINSTANCE)hm, "s_add");
		if (dll_add != NULL){
			result = dll_add(intx, inty);
		}
		else{
			MessageBox(_T("DLL加载失败，调用失效！"), _T("动态链接库的动态加载"));
			return;
		}
#endif
	}
	result_str.Format(_T("%d"),result);
	GetDlgItem(IDC_RESULT)->SetWindowText(result_str);
}

void CExp1TestMyDLLDlg::OnBnClickedReverse()
{
	CString sourse, result_str;
	GetDlgItem(IDC_SOURSESTR)->GetWindowText(sourse);
	if (sourse.IsEmpty()){
		MessageBox(_T("输入不能为空！"), _T("动态链接库的编写和调用"));
		return;
	}
	int len = sourse.GetLength();
	char *p = sourse.GetBuffer(len);
	if (op_call == C_CALL){
#ifdef _STATIC
		c_reverseString(p);
#endif
#ifndef _STATIC
		reverse dll_reverse = NULL;
		dll_reverse = (reverse)GetProcAddress((HINSTANCE)hm, "c_reverseString");
		if (dll_reverse != NULL){
			dll_reverse(p);
		}
		else{
			MessageBox(_T("DLL加载失败，调用失效！"), _T("动态链接库的动态加载"));
			return;
		}
#endif
	}
	else{
#ifdef _STATIC
		s_reverseString(p);
#endif
#ifndef _STATIC
		reverse dll_reverse = NULL;
		dll_reverse = (reverse)GetProcAddress((HINSTANCE)hm, "s_reverseString");
		if (dll_reverse != NULL){
			dll_reverse(p);
		}
		else{
			MessageBox(_T("DLL加载失败，调用失效！"), _T("动态链接库的动态加载"));
			return;
		}
#endif
	}
	result_str.Format(_T("%s"), p);
	GetDlgItem(IDC_REVERSESTR)->SetWindowText(result_str);
}

#ifndef _STATIC
void CExp1TestMyDLLDlg::LoadDLL(){
	CFileFind finder;
	CString name = _T("simple_dll.dll");
	BOOL bWorking = finder.FindFile(name);
	if (bWorking){
		int enable = 0;
		bWorking = finder.FindNextFile();
		hm = LoadLibrary(finder.GetFilePath());
		if (!hm)
		{
			MessageBox(_T("DLL加载失败！"), _T("动态链接库的动态加载"));
		}
	}
	else
		MessageBox(_T("DLL加载失败！"), _T("动态链接库的动态加载"));
}
#endif