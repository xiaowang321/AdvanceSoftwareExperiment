// Exp2ThreadCreateDlg.cpp : 实现文件
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
HANDLE ReadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//该事件激活时则可以进行读操作,初始状态为未激活
HANDLE WriteEvent = CreateEvent(NULL, TRUE, TRUE, NULL);//该事件激活时则可以进行写操作，初始状态为激活
//注意事件激活仅代表可以调用读写函数，并不代表读写函数调用成功。

// CExp2ThreadCreateDlg 对话框

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

// CExp2ThreadCreateDlg 消息处理程序

BOOL CExp2ThreadCreateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExp2ThreadCreateDlg::OnPaint()
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
				SetEvent(WriteEvent);//激活写操作
				int time = GetRand(1, 6);
				Sleep(500 * time);
				break;//跳出循环
			}//只有当读操作失败时才意味着读写冲突，需要等待激活
			WaitForSingleObject(ReadEvent, INFINITE);//等待读操作激活
			ResetEvent(ReadEvent);//重置读操作
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
		LogWriteData(writeData);//将数据写入日志文件保存
		while (1){
			if (dlg->buffer->WriteBuffer(&writeData)){
				SetEvent(ReadEvent);//激活读操作
				int time = GetRand(1, 6);
				Sleep(500 * time);
				break;//跳出循环
			}
			WaitForSingleObject(WriteEvent, INFINITE);//等待写操作激活
			ResetEvent(WriteEvent);//重置写操作
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
	max = RAND_MAX;//rand()函数随机数的最大值
	return (unsigned int)(rand()*(MAX - MIN) / max + MIN);
}


void LogWriteData(NODE data)
{
	//创建文件
	FILE *fp = fopen("writeData.log", "a");//打开文件【续写】
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