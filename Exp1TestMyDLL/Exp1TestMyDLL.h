
// Exp1TestMyDLL.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExp1TestMyDLLApp: 
// �йش����ʵ�֣������ Exp1TestMyDLL.cpp
//

class CExp1TestMyDLLApp : public CWinApp
{
public:
	CExp1TestMyDLLApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExp1TestMyDLLApp theApp;