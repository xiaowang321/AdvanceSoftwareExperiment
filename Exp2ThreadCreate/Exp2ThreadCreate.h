
// Exp2ThreadCreate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExp2ThreadCreateApp: 
// �йش����ʵ�֣������ Exp2ThreadCreate.cpp
//

class CExp2ThreadCreateApp : public CWinApp
{
public:
	CExp2ThreadCreateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExp2ThreadCreateApp theApp;