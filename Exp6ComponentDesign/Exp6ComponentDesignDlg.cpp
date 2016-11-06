// Exp6ComponentDesignDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Exp6ComponentDesign.h"
#include "Exp6ComponentDesignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExp6ComponentDesignDlg �Ի���
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

// CExp6ComponentDesignDlg ��Ϣ�������
BOOL CExp6ComponentDesignDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CMenu *pMenu = this->GetMenu();
	pMenu->EnableMenuItem(ID_FUNC1, MF_DISABLED | MF_GRAYED);
	pMenu->EnableMenuItem(ID_FUNC2, MF_DISABLED | MF_GRAYED);
	pMenu->EnableMenuItem(ID_FUNC3, MF_DISABLED | MF_GRAYED);

	LoadDLL();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExp6ComponentDesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
			MessageBox(_T("����DLLʧ�ܣ�"),_T("�������˼��ĳ������"));
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
		FreeLibrary((HMODULE)m_dwa[i]);//ж��DLL��
	}
}

void CExp6ComponentDesignDlg::ExecuteFuncFromDLL(int nID)
{
	int num = nID - ID_FUNC1;
	dll_proc proc;
	proc = (dll_proc)GetProcAddress((HINSTANCE)m_dwa.GetAt(num), "com_func");
	if (proc != NULL){
		CString answer = proc();
		MessageBox(answer, _T("�������˼��ĳ������"));
	}
}
