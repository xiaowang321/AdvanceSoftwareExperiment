
// Exp6ComponentDesignDlg.h : ͷ�ļ�
//

#pragma once

typedef CString(*dll_proc)(void);

// CExp6ComponentDesignDlg �Ի���
class CExp6ComponentDesignDlg : public CDialogEx
{
// ����
public:
	CExp6ComponentDesignDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXP6COMPONENTDESIGN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon; 
	CMenu m_hMenu;
	CDWordArray m_dwa;

	// ���ɵ���Ϣӳ�亯��
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
