
// Exp1TestMyDLLDlg.h : ͷ�ļ�
//

#pragma once

enum CALL{
	C_CALL,
	STD_CALL
};//��־���ֵ��÷�ʽ

//ʹ����������ķ�ʽʵ�־�̬�Ͷ�̬���ֵ��÷�ʽ
//#define _STATIC


// CExp1TestMyDLLDlg �Ի���
class CExp1TestMyDLLDlg : public CDialogEx
{
// ����
public:
	CExp1TestMyDLLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXP1TESTMYDLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
