// COM_FUNC2.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "COM_FUNC2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COM_FUNC2_API CString com_func(void)
{
	CString answer = _T("This is Component Design Library Function No.2!");
	return answer;
}