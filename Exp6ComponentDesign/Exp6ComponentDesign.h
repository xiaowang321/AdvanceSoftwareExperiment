
// Exp6ComponentDesign.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExp6ComponentDesignApp: 
// �йش����ʵ�֣������ Exp6ComponentDesign.cpp
//

class CExp6ComponentDesignApp : public CWinApp
{
public:
	CExp6ComponentDesignApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExp6ComponentDesignApp theApp;