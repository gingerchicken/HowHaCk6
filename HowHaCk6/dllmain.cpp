// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"

#include "sourcesdk/sdk.h"
#include "gconsole.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        HowHack::SetupConsole();
        HowHack::Log("Dll attached!\n");

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

