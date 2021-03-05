#include "user32.h"
#include"hook_utility.h"
DesHook(GetMessageA);
DesHook(GetMessageW);

void InitUser32()
{
	OutputDebugStringA("InitUser32");
	do {
		auto module = LoadLibrary("user32");
		if (module == NULL) {
			OutputDebugStringA("NotFindUser32.dll");
			break;
		}
		CreateHook(GetMessageA, module);
		auto aSrcAddr = pHook(GetMessageA)->GetSrc();
		auto aDstAddr = pHook(GetMessageA)->GetDst();
		CreateHook(GetMessageW, module);
		auto wSrcAddr = pHook(GetMessageW)->GetSrc();
		auto wDstAddr = pHook(GetMessageW)->GetDst();
		printf("");
	} while (0);
}

BOOL
WINAPI __GetMessageA(_Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax)
{
	OutputDebugStringA("Gamer GetMessageA");
	BOOL rst = false;
	pHook(GetMessageA)->Remove();
	rst = GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	pHook(GetMessageA)->Install();
	return rst;
}

BOOL
WINAPI __GetMessageW(_Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax)
{
	OutputDebugStringA("Gamer GetMessageW");
	BOOL rst = false;
	pHook(GetMessageW)->Remove();
	rst = GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	pHook(GetMessageW)->Install();
	return rst;
}