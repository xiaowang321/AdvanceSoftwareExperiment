// COM_FUNC3.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "COM_FUNC3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COM_FUNC3_API CString com_func(void){
	CString answer = _T("This is Component Design Library Function No.3!");
	return answer;
}