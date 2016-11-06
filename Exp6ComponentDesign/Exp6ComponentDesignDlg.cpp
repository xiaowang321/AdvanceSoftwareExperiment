// Exp6ComponentDesignDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "Exp6ComponentDesign.h"
#include "Exp6ComponentDesignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExp6ComponentDesignDlg 对话框
CExp6ComponentDesignDlg::CExp6ComponentDesignDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExp6ComponentDesignDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExp6ComponentDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExp6ComponentDesignDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FUNC1, &CExp6ComponentDesignDlg::OnFunc1)
	ON_COMMAND(ID_FUNC2, &CExp6ComponentDesignDlg::OnFunc2)
	ON_COMMAND(ID_FUNC3, &CExp6ComponentDesignDlg::OnFunc3)
END_MESSAGE_MAP()

// CExp6ComponentDesignDlg 消息处理程序
BOOL CExp6ComponentDesignDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CMenu *pMenu = this->GetMenu();
	pMenu->EnableMenuItem(ID_FUNC1, MF_DISABLED | MF_GRAYED);
	pMenu->EnableMenuItem(ID_FUNC2, MF_DISABLED | MF_GRAYED);
	pMenu->EnableMenuItem(ID_FUNC3, MF_DISABLED | MF_GRAYED);

	LoadDLL();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExp6ComponentDesignDlg::OnPaint()
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
HCURSOR CExp6ComponentDesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExp6ComponentDesignDlg::OnFunc1()
{
	ExecuteFuncFromDLL(ID_FUNC1);
}

void CExp6ComponentDesignDlg::OnFunc2()
{
	ExecuteFuncFromDLL(ID_FUNC2);
}


void CExp6ComponentDesignDlg::OnFunc3()
{
	ExecuteFuncFromDLL(ID_FUNC3);
}

void CExp6ComponentDesignDlg::LoadDLL()
{
	CFileFind finder;
	CString name = _T("COM_FUNC*.dll");
	BOOL bWorking = finder.FindFile(name);
	int enable = 0;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		HMODULE hm = LoadLibrary(finder.GetFilePath());
		if (!hm)
		{
			MessageBox(_T("加载DLL失败！"),_T("基于组件思想的程序设计"));
		}
		else
		{ 
			m_dwa.Add((DWORD)hm);
			CMenu *pMenu = this->GetMenu();
			pMenu->EnableMenuItem(ID_FUNC1+enable, MF_ENABLED);
			enable++;
		}
	}
}

void CExp6ComponentDesignDlg::OnDestroy()
{
	for (int i = 0; i<m_dwa.GetSize(); i++)
	{
		FreeLibrary((HMODULE)m_dwa[i]);//卸载DLL库
	}
}

void CExp6ComponentDesignDlg::ExecuteFuncFromDLL(int nID)
{
	int num = nID - ID_FUNC1;
	dll_proc proc;
	proc = (dll_proc)GetProcAddress((HINSTANCE)m_dwa.GetAt(num), "com_func");
	if (proc != NULL){
		CString answer = proc();
		MessageBox(answer, _T("基于组件思想的程序设计"));
	}
}
