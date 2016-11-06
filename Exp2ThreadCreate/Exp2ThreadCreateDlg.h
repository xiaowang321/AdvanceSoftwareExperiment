
// Exp2ThreadCreateDlg.h : ͷ�ļ�
//

#pragma once
#include "CircleBuffer.h"
#include "afxwin.h"


// CExp2ThreadCreateDlg �Ի���
class CExp2ThreadCreateDlg : public CDialogEx
{
// ����
public:
	CExp2ThreadCreateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXP2THREADCREATE_DIALOG };

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
public:
	CircleBuffer *buffer;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnDestroy();
	CEdit m_readdata;
	CEdit m_writedata;
};
//�߳���ر���������
UINT ReadProc(LPVOID lpParam);//���̺߳���
UINT WriteProc(LPVOID lpParam);//д�̺߳���
unsigned int GetRand(unsigned int MIN, unsigned int MAX);//���������
void LogWriteData(NODE data);//��д�̵߳�����д����־�ļ�
CString FormatData(NODE data);//�����̵߳����ݹ��ɷ���һ����ʽ���ַ���
