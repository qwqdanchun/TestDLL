#include <windows.h>
#include <stdio.h>

HMODULE GetSelfModuleHandle()
{
    MEMORY_BASIC_INFORMATION mbi;
    return ((VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}

void* xmemset(void* blk, int c, size_t n)
{
    unsigned char* dst = blk;

    while (n-- > 0)
        *dst++ = (unsigned char)c;

    return blk;
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
        WCHAR  dllDir[256] ;
        WCHAR  exeDir[256];
        WCHAR  username[256];
        WCHAR  str[1024];
        DWORD size = 256;
        xmemset(dllDir,0,sizeof(dllDir));
        xmemset(exeDir, 0, sizeof(exeDir));
        xmemset(username, 0, sizeof(username));
        xmemset(str, 0, sizeof(str));

        GetModuleFileNameW(GetSelfModuleHandle(), dllDir, 128);
        GetModuleFileNameW(NULL, exeDir, 128);
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

