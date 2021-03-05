#include "GamerHandler.h"
#include<Windows.h>
namespace seraphim {

	GamerHandler::GamerHandler()
	{
		targetExeName = "GamerWin32.exe";
		dllName = "Gamer.dll";
	}

	int GamerHandler::startProcess()
	{
		//CREATE_SUSPENDED
		STARTUPINFOA  si;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		PROCESS_INFORMATION  pi;
		ZeroMemory(&pi, sizeof(pi));
		auto flag = CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS;// | CREATE_SUSPENDED;
		if (pauseAtCreate)
			flag |= CREATE_SUSPENDED;
		auto rst = CreateProcess(targetExeName.c_str(), nullptr, nullptr, nullptr, false, flag, nullptr, nullptr, &si, &pi);
		hProcess = pi.hProcess;
		hTread = pi.hThread;
		pid = pi.dwProcessId;
		tid = pi.dwThreadId;
		return rst;
	}

	int GamerHandler::inject()
	{
		int code = 0;
		do {
		auto dwSize = dllName.size() +1;
		const char* pszLibFile = dllName.c_str();
		LPVOID pszLibFileRemote = (PWSTR)VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
		if (pszLibFileRemote == nullptr) {
			code = -1;
			break;
		}
		DWORD n = WriteProcessMemory(hProcess, pszLibFileRemote, (PVOID)pszLibFile, dwSize, NULL);
		if (n <= 0) {
			code = -2;
			break;
		}
		auto module = GetModuleHandle("Kernel32");
		if (module == nullptr) {
			code = -3;
			break;
		}
		PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(module, "LoadLibraryA");
		if (module == nullptr) {
			code = -4;
			break;
		}
		auto hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, pszLibFileRemote, 0, NULL);
		if (hThread == NULL) {
			code = -5;
			break;
		}

		} while (0);
		return code;

	}

	int GamerHandler::login(const string& uName, const string& uPasswd)
	{
		int code = 0;
		return 0;
	}

	int GamerHandler::pause()
	{
		int code = 0;
		SuspendThread(hTread);
		return 0;
	}

	int GamerHandler::resume()
	{
		int code = 0;
		code = ResumeThread(hTread);
		if (code < 0) {
			auto err = GetLastError();
			printf("%d", err);
		}
		return 0;

	}

	void GamerHandler::termindate()
	{
		auto bError = TerminateProcess(hProcess, 0);
		if (!bError) {
			int code = GetLastError();
			printf_s("Terminate Error error_code=%d\n", code);

		}
	}

	void GamerHandler::print()
	{

		char  msg[256];
		sprintf_s(msg, "pid=%d ph=%p  tid=%d th=%p",(DWORD) pid,hProcess,(DWORD)tid,hTread);
		OutputDebugString(msg);

	}

};

