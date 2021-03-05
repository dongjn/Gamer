#include "kernel32.h"
#include"hook_utility.h"

DesHook(CreateProcessA);

void InitKernerl32()
{
	auto  module = LoadLibraryA("kernel32");
	CreateHook(CreateProcessA, module);
}

BOOL
WINAPI __CreateProcessA(_In_opt_ LPCSTR lpApplicationName, _Inout_opt_ LPSTR lpCommandLine, _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ BOOL bInheritHandles,
	_In_ DWORD dwCreationFlags, _In_opt_ LPVOID lpEnvironment,
	_In_opt_ LPCSTR lpCurrentDirectory, _In_ LPSTARTUPINFOA lpStartupInfo,
	_Out_ LPPROCESS_INFORMATION lpProcessInformation)
{
	pHook(CreateProcessA)->Remove();
	auto rst = CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	pHook(CreateProcessA)->Install();
	return rst;
}