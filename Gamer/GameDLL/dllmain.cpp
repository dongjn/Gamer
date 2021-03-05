// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include<thread>

void work() {
    bool bRun = true;
    while (bRun) {
        Sleep(100);
        OutputDebugString("Gamer ---- Work ");
    }
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        std::thread t(work);
        t.detach();
        OutputDebugString("Gamer ---- DLL_PROCESS_ATTACH");
    }
        break;
    case DLL_THREAD_ATTACH:
        OutputDebugString("Gamer ---- DLL_THREAD_ATTACH");
        break;
    case DLL_THREAD_DETACH:
        OutputDebugString("Gamer ---- DLL_THREAD_DETACH");
        break;
    case DLL_PROCESS_DETACH:
        OutputDebugString("Gamer ---- DLL_PROCESS_DETACH");
        break;
    }
    return TRUE;
}

