
// Exp5MediaPlayerDlg.h : ͷ�ļ�
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

// CExp5MediaPlayerDlg �Ի���
class CExp5MediaPlayerDlg : public CDialogEx
{
// ����
public:
	CExp5MediaPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXP5MEDIAPLAYER_DIALOG };

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
