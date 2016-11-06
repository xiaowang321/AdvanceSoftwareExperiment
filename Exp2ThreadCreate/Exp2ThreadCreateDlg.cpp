// Exp2ThreadCreateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Exp2ThreadCreate.h"
#include "Exp2ThreadCreateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinThread *ReadThread = NULL;
CWinThread *WriteThread = NULL;
HANDLE ReadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//���¼�����ʱ����Խ��ж�����,��ʼ״̬Ϊδ����
HANDLE WriteEvent = CreateEvent(NULL, TRUE, TRUE, NULL);//���¼�����ʱ����Խ���д��������ʼ״̬Ϊ����
//ע���¼������������Ե��ö�д���������������д�������óɹ���

// CExp2ThreadCreateDlg �Ի���

CExp2ThreadCreateDlg::CExp2ThreadCreateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExp2ThreadCreateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	buffer = new CircleBuffer(this->m_hWnd);
}

void CExp2ThreadCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_READDATA, m_readdata);
	DDX_Control(pDX, IDC_WRITEDATA, m_writedata);
}

BEGIN_MESSAGE_MAP(CExp2ThreadCreateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CExp2ThreadCreateDlg::OnBnClickedStart)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CExp2ThreadCreateDlg ��Ϣ�������

BOOL CExp2ThreadCreateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExp2ThreadCreateDlg::OnPaint()
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
HCURSOR CExp2ThreadCreateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExp2ThreadCreateDlg::OnDestroy()
{
	if (buffer != NULL)
		delete buffer;
}

void CExp2ThreadCreateDlg::OnBnClickedStart()
{
	GetDlgItem(IDC_READDATA)->SetWindowText(_T(""));
	GetDlgItem(IDC_WRITEDATA)->SetWindowText(_T(""));
	ReadThread = AfxBeginThread(ReadProc,this);
	WriteThread = AfxBeginThread(WriteProc,this);
}

UINT ReadProc(LPVOID lpParam)
{
	CExp2ThreadCreateDlg* dlg = (CExp2ThreadCreateDlg*)lpParam;
	NODE readData;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20;i++){
		while (1){
			if (dlg->buffer->ReadBuffer(&readData))
			{
				SetEvent(WriteEvent);//����д����
				int time = GetRand(1, 6);
				Sleep(500 * time);
				break;//����ѭ��
			}//ֻ�е�������ʧ��ʱ����ζ�Ŷ�д��ͻ����Ҫ�ȴ�����
			WaitForSingleObject(ReadEvent, INFINITE);//�ȴ�����������
			ResetEvent(ReadEvent);//���ö�����
		}
		CString display;
		dlg->GetDlgItem(IDC_READDATA)->GetWindowText(display);
		display += FormatData(readData);
		dlg->GetDlgItem(IDC_READDATA)->SetWindowText(display);
		dlg->m_readdata.LineScroll(dlg->m_readdata.GetLineCount());
	}
	return 0;
}

UINT WriteProc(LPVOID lpParam)
{
	CExp2ThreadCreateDlg* dlg = (CExp2ThreadCreateDlg*)lpParam;
	NODE writeData;
	int j = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20;i++){
		writeData.dataSize = GetRand(1,NODE_SIZE);
		for (int i = 0; i < writeData.dataSize; i++){
			writeData.data[i] = GetRand(0, RAND_MAX);
		}
		j++;
		LogWriteData(writeData);//������д����־�ļ�����
		while (1){
			if (dlg->buffer->WriteBuffer(&writeData)){
				SetEvent(ReadEvent);//���������
				int time = GetRand(1, 6);
				Sleep(500 * time);
				break;//����ѭ��
			}
			WaitForSingleObject(WriteEvent, INFINITE);//�ȴ�д��������
			ResetEvent(WriteEvent);//����д����
		}
		CString display;
		dlg->GetDlgItem(IDC_WRITEDATA)->GetWindowText(display);
		display += FormatData(writeData);
		dlg->GetDlgItem(IDC_WRITEDATA)->SetWindowText(display);
		dlg->m_writedata.LineScroll(dlg->m_writedata.GetLineCount());
	}
	return 0;
}

CString FormatData(NODE data)
{
	CString target = _T("(");
	CString temp;
	for (int i = 0; i < data.dataSize; i++){
		if (i < data.dataSize - 1){
			temp.Format(_T("%u,"), data.data[i]);
			target += temp;
		}
		else{
			temp.Format(_T("%u)\r\n"), data.data[i]);
			target += temp;
		}
	}
	return target;
}

unsigned int GetRand(unsigned int MIN, unsigned int MAX)
{
	unsigned int max;
	max = RAND_MAX;//rand()��������������ֵ
	return (unsigned int)(rand()*(MAX - MIN) / max + MIN);
}


void LogWriteData(NODE data)
{
	//�����ļ�
	FILE *fp = fopen("writeData.log", "a");//���ļ�����д��
	fprintf(fp, "%d:(", data.dataSize);
	for (int i = 0; i < data.dataSize; i++){
		if (i < data.dataSize - 1){
			fprintf(fp, "%u,", data.data[i]);
		}
		else{
			fprintf(fp, "%u)\r\n", data.data[i]);
		}
	}
	fclose(fp);
}