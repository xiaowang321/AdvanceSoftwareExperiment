
// Exp1TestMyDLLDlg.cpp : ʵ���ļ�
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


// CExp1TestMyDLLDlg �Ի���



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


// CExp1TestMyDLLDlg ��Ϣ�������

BOOL CExp1TestMyDLLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	((CButton*)GetDlgItem(IDC_CCALL))->SetCheck(TRUE);
	op_call = C_CALL;
#ifndef _STATIC
	LoadDLL();
#endif
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExp1TestMyDLLDlg::OnPaint()
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
		MessageBox(_T("���������������������͵�����"),_T("��̬���ӿ�ı�д�͵���"));
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
			MessageBox(_T("DLL����ʧ�ܣ�����ʧЧ��"), _T("��̬���ӿ�Ķ�̬����"));
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
			MessageBox(_T("DLL����ʧ�ܣ�����ʧЧ��"), _T("��̬���ӿ�Ķ�̬����"));
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
		MessageBox(_T("���벻��Ϊ�գ�"), _T("��̬���ӿ�ı�д�͵���"));
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
			MessageBox(_T("DLL����ʧ�ܣ�����ʧЧ��"), _T("��̬���ӿ�Ķ�̬����"));
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
			MessageBox(_T("DLL����ʧ�ܣ�����ʧЧ��"), _T("��̬���ӿ�Ķ�̬����"));
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
			MessageBox(_T("DLL����ʧ�ܣ�"), _T("��̬���ӿ�Ķ�̬����"));
		}
	}
	else
		MessageBox(_T("DLL����ʧ�ܣ�"), _T("��̬���ӿ�Ķ�̬����"));
}
#endif