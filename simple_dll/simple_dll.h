// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SIMPLE_DLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SIMPLE_DLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SIMPLE_DLL_EXPORTS
#define SIMPLE_DLL_API __declspec(dllexport)
#else
#define SIMPLE_DLL_API __declspec(dllimport)
#endif

extern "C" SIMPLE_DLL_API int _cdecl c_add(int x,int y);
extern "C" SIMPLE_DLL_API int _stdcall s_add(int x, int y);
extern "C" SIMPLE_DLL_API void _cdecl c_reverseString(char* sourse);
extern "C" SIMPLE_DLL_API void _stdcall s_reverseString(char* sourse);
