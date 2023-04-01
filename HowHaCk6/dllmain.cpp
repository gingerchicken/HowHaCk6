// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"

#include "gconsole.h"

#include "interfaces.hpp"
#include "hooks.hpp"

#include "sourcesdk/sdk.h"

void SimpleInitalise() {
    HowHack::SetupConsole();
    HowHack::Log("Dll attached!\n");

    HowHack::Log("Setting up interfaces...\n");
    HowHack::SetupInterfaces();
    HowHack::LogInterfaces();

    HowHack::Log("Hooking interfaces...\n");
    HowHack::SetupHooks();
    HowHack::LogHooks();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        SimpleInitalise();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

