
// Exp5MediaPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExp5MediaPlayerApp: 
// �йش����ʵ�֣������ Exp5MediaPlayer.cpp
//

class CExp5MediaPlayerApp : public CWinApp
{
public:
	CExp5MediaPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExp5MediaPlayerApp theApp;