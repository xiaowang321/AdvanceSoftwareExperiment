
// Exp5MediaPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exp5MediaPlayer.h"
#include "Exp5MediaPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExp5MediaPlayerDlg 对话框



CExp5MediaPlayerDlg::CExp5MediaPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExp5MediaPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExp5MediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
}

BEGIN_MESSAGE_MAP(CExp5MediaPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CExp5MediaPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_PAUSE, &CExp5MediaPlayerDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_STOP, &CExp5MediaPlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_FILE, &CExp5MediaPlayerDlg::OnBnClickedFile)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CExp5MediaPlayerDlg 消息处理程序

BOOL CExp5MediaPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_progress.SetRange(0,100);
	ScreenClear();

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)){
		MessageBox(_T("错误：初始化COM失败！"),_T("基于DirectX的媒体播放器"));
		return FALSE;
	}
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr)){
		MessageBox(_T("错误：创建Filter Graph失败！"),_T("基于DirectX的媒体播放器"));
		return FALSE;
	}
	//  Query Interface
	hr |= pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr |= pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
	hr |= pGraph->QueryInterface(IID_IBasicVideo, (void **)&pVideo);
	hr |= pGraph->QueryInterface(IID_IBasicAudio, (void **)&pAudio);
	hr |= pGraph->QueryInterface(IID_IVideoWindow, (void **)&pWindow);
	hr |= pGraph->QueryInterface(IID_IMediaSeeking, (void **)&pSeeking);
	if (FAILED(hr)){
		MessageBox(_T("错误：接口查找失败！"),_T("基于DirectX的媒体播放器"));
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExp5MediaPlayerDlg::OnPaint()
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
HCURSOR CExp5MediaPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExp5MediaPlayerDlg::OnBnClickedPlay()
{
	HRESULT hr;
	if (m_url.IsEmpty())
	{
		MessageBox(_T("文件路径为空！"), _T("基于DirectX的媒体播放器"));
		return;
	}
	hr = pGraph->RenderFile(m_url, NULL);
	if (FAILED(hr)){
		MessageBox(_T("不支持该格式的媒体文件!"), _T("基于DirectX的媒体播放器"));
		return;
	}

	HWND screen_hwnd = NULL;
	RECT windowRect;
	screen_hwnd = this->GetDlgItem(IDC_SCREEN)->GetSafeHwnd();
	::GetClientRect(screen_hwnd, &windowRect);

	pWindow->put_Visible(OAFALSE);
	pWindow->put_Owner((OAHWND)screen_hwnd);
	pWindow->put_Left(0);
	pWindow->put_Top(0);
	pWindow->put_Width(windowRect.right - windowRect.left);
	pWindow->put_Height(windowRect.bottom - windowRect.top);
	pWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_THICKFRAME);
	pWindow->put_MessageDrain((OAHWND)screen_hwnd);//Receive Message
	pWindow->put_Visible(OATRUE);

	HWND dlg_hwnd = NULL;
	dlg_hwnd = this->GetSafeHwnd();
	pEvent->SetNotifyWindow((OAHWND)dlg_hwnd, WM_GRAPHNOTIFY, 0);

	hr = pControl->Run();

	mediaState = MediaPlay;
	SetButton(mediaState);
	SetTimer(1, 1000, NULL);
}


void CExp5MediaPlayerDlg::OnBnClickedPause()
{
	HRESULT hr;
	if (mediaState == MediaPlay){
		hr = pControl->Pause();
		mediaState = MediaPause;
		GetDlgItem(IDC_PAUSE)->SetWindowText(_T("继续"));
	}
	else if (mediaState == MediaPause){
		hr = pControl->Run();
		mediaState = MediaPlay;
		GetDlgItem(IDC_PAUSE)->SetWindowText(_T("暂停"));
	}
}


void CExp5MediaPlayerDlg::OnBnClickedStop()
{
	long long position = 0;
	HRESULT hr;
	hr = pSeeking->SetPositions(&position, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame,
		0, AM_SEEKING_NoPositioning);
	KillTimer(1);
	hr = pControl->Stop();
	IEnumFilters *pEnum = NULL;
	hr = pGraph->EnumFilters(&pEnum);
	if (SUCCEEDED(hr))
	{
		IBaseFilter *pFilter = NULL;
		while (S_OK == pEnum->Next(1, &pFilter, NULL))
		{
			pGraph->RemoveFilter(pFilter);
			pEnum->Reset();
			pFilter->Release();
		}
		pEnum->Release();
	}
	ScreenClear();
	mediaState = MediaChoose;
	SetButton(mediaState);
}


void CExp5MediaPlayerDlg::OnBnClickedFile()
{
	CString strfilter;
	strfilter.Append(_T("(*.avi;*.mp4;*.wmv;*.mp3)|*.avi;*.mp4;*.wmv;*.mp3||"));
	LPCTSTR lpszfilter = strfilter;
	CFileDialog dlg(TRUE, NULL, NULL, NULL, lpszfilter);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if (dlg.DoModal() == IDOK) {
		m_url = dlg.GetPathName();
		GetDlgItem(IDC_FILENAME)->SetWindowText(m_url);
	}
	if (m_url.IsEmpty())return;
	mediaState = MediaPerpare;
	SetButton(mediaState);
}

void CExp5MediaPlayerDlg::ScreenClear()
{
	mediaState = MediaChoose;
	SetButton(mediaState);
	GetDlgItem(IDC_CURRENTTIME)->SetWindowText(_T("00:00:00"));
	GetDlgItem(IDC_TOTALTIME)->SetWindowText(_T("00:00:00"));
	GetDlgItem(IDC_FILENAME)->SetWindowText(_T("未选择媒体文件"));
	m_progress.SetPos(0);

	CPaintDC dc(this);
	CRect   rect;
	GetDlgItem(IDC_SCREEN)->GetClientRect(&rect);
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_WELCOME);
	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	Invalidate(TRUE);
}

void CExp5MediaPlayerDlg::SetButton(MediaState state)
{
	switch (state){
	case MediaChoose:
		GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_FILE)->EnableWindow(TRUE);
		break;
	case MediaPerpare:
		GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_FILE)->EnableWindow(FALSE);
		break;
	default:
		GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_FILE)->EnableWindow(FALSE);
		break;
	}
	return;
}

void CExp5MediaPlayerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	if (pVideo)
		pVideo->Release();
	if (pAudio)
		pAudio->Release();
	if (pWindow)
		pWindow->Release();
	if (pSeeking)
		pSeeking->Release();
	if (pControl)
		pControl->Release();
	if (pEvent)
		pEvent->Release();
	if (pGraph)
		pGraph->Release();
	CoUninitialize();
}

void CExp5MediaPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1){
		CString current_str, total_str;
		long long current;
		long long total;
		int tns, thh, tmm, tss;
		int progress;
		pSeeking->GetCurrentPosition(&current);
		if (current != 0){
			tns = current / 10000000;
			thh = tns / 3600;
			tmm = (tns % 3600) / 60;
			tss = (tns % 60);
			current_str.Format(_T("%02d:%02d:%02d"), thh, tmm, tss);
			GetDlgItem(IDC_CURRENTTIME)->SetWindowText(current_str);
		}
		pSeeking->GetDuration(&total);
		if (total != 0){
			tns = total / 10000000;
			thh = tns / 3600;
			tmm = (tns % 3600) / 60;
			tss = (tns % 60);
			total_str.Format(_T("%02d:%02d:%02d"), thh, tmm, tss);
			GetDlgItem(IDC_TOTALTIME)->SetWindowText(total_str);

			progress = current * 100 / total;
			m_progress.SetPos(progress);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CExp5MediaPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetSafeHwnd() == m_progress.GetSafeHwnd()){
		float pos_bar = 0.0;
		long long duration = 0.0;
		long long pos_time = 0.0;
		if (nSBCode == SB_THUMBPOSITION){
			pos_bar = (float)nPos / 100.0;
			pSeeking->GetDuration(&duration);
			pos_time = pos_bar*duration;

			long long position = (long long)(pos_time);
			HRESULT hr = pSeeking->SetPositions(&position, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame,
				0, AM_SEEKING_NoPositioning);
		}
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
