#include <windows.h>
#include <stdio.h>

HMODULE GetSelfModuleHandle()
{
    MEMORY_BASIC_INFORMATION mbi;
    return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        WCHAR  dllDir[1024] = { 0 };
        WCHAR  exeDir[1024] = { 0 };
        WCHAR  username[1024] = { 0 };
        WCHAR  str[1024] = { 0 };
        DWORD size = 1024;

        GetModuleFileNameW(GetSelfModuleHandle(), dllDir, 1023);
        GetModuleFileNameW(nullptr, exeDir, 1023);
        GetUserNameW((wchar_t*)username, &size);
        wsprintfW(str, L"This file:\n%s\nwas loaded by:\n%s\nrunning as:\n%s", dllDir, exeDir, username);
        MessageBoxExW(NULL, str, L"Message", 0, 0);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

