// COM_FUNC1.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "COM_FUNC1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

COM_FUNC1_API CString com_func(void)
{
	CString answer = _T("This is Component Design Library Function No.1!");
	return answer;
}