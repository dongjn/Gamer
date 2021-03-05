#pragma once
#include<Windows.h>
#ifdef __cplusplus
extern"C" {
#endif

	void InitUser32();

	BOOL
		WINAPI
		__GetMessageA(
			_Out_ LPMSG lpMsg,
			_In_opt_ HWND hWnd,
			_In_ UINT wMsgFilterMin,
			_In_ UINT wMsgFilterMax);

	BOOL
		WINAPI
		__GetMessageW(
			_Out_ LPMSG lpMsg,
			_In_opt_ HWND hWnd,
			_In_ UINT wMsgFilterMin,
			_In_ UINT wMsgFilterMax);
#ifdef __cplusplus
}

#endif
