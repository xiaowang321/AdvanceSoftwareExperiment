
// Exp5MediaPlayerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <dshow.h>

#pragma comment(lib,"strmiids.lib")

enum MediaState{
	MediaChoose,
	MediaPerpare,
	MediaPlay,
	MediaPause
};

#define WM_GRAPHNOTIFY  (WM_USER+30)

// CExp5MediaPlayerDlg 对话框
class CExp5MediaPlayerDlg : public CDialogEx
{
// 构造
public:
	CExp5MediaPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXP5MEDIAPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IGraphBuilder *pGraph;
	IMediaControl *pControl;
	IMediaEventEx *pEvent;
	IBasicVideo *pVideo;
	IBasicAudio *pAudio;
	IVideoWindow *pWindow;
	IMediaSeeking *pSeeking;

	MediaState mediaState;
	CSliderCtrl m_progress;
	CString m_url;

	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedFile();

	void ScreenClear();
	void SetButton(MediaState state);
	void OnDestroy();
	void OnTimer(UINT_PTR nIDEvent);
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
