// simple_dll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "simple_dll.h"


SIMPLE_DLL_API int _cdecl c_add(int x, int y)
{
	return (x + y);
}

SIMPLE_DLL_API int _stdcall s_add(int x, int y)
{
	return (x + y);
}

SIMPLE_DLL_API void _cdecl c_reverseString(char *sourse)
{
	char* prior, *tail;
	prior = sourse;
	tail = sourse;
	while (*tail != '\0')tail++;//tailָ��ָ����ַ�
	tail--;
	while (tail > prior)
	{
		char t = *prior;
		*prior++ = *tail;
		*tail-- = t;
	}
}

SIMPLE_DLL_API void _stdcall s_reverseString(char *sourse)
{
	char* prior, *tail;
	prior = sourse;
	tail = sourse;
	while (*tail != '\0')tail++;//tailָ��ָ����ַ�
	tail--;
	while (tail > prior)
	{
		char t = *prior;
		*prior++ = *tail;
		*tail-- = t;
	}
}

