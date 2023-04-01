#ifndef CLuaShared_HOOKS_H
#define CLuaShared_HOOKS_H

#include <Windows.h>

#include "../gconsole.h"
#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"

typedef CLuaInterface* (__thiscall* CreateLuaInterfaceFn)(CLuaShared*, LuaInterfaceType, bool);
typedef bool(__thiscall* RunStringExFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool, bool, bool);

namespace HowHack {
    VMTHook* g_pLuaInterfaceHook;

	CreateLuaInterfaceFn g_pOCreateLuaInterface;
    RunStringExFn g_pORunStringEx;

    void UpdateLuaInterfaceHooks(CLuaInterface* pLuaInterface);

    CLuaInterface* __fastcall hkCreateLuaInterfaceFn(CLuaShared* _this,
#ifndef _WIN64
        void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
        LuaInterfaceType eLuaStateType, bool bRenew)
    {
        CLuaInterface* pLuaInterface = g_pOCreateLuaInterface(_this, eLuaStateType, bRenew);
        if (eLuaStateType != LuaInterfaceType::LUA_CLIENT) return pLuaInterface;

        // TODO hook the lua state

        HowHack::UpdateLuaInterface(pLuaInterface);
        HowHack::UpdateLuaInterfaceHooks(pLuaInterface);

        return pLuaInterface;
    }

    bool __fastcall hkRunStringEx(CLuaInterface* _this,
#ifndef _WIN64
        void*,
#endif
        const char* szFilename, const char* szPath, const char* szStringToRun, bool bRun, bool bPrintErrors, bool bDontPushErrors, bool bNoReturns) {
        // TODO
        return g_pORunStringEx(_this, szFilename, szPath, szStringToRun, bRun, bPrintErrors, bDontPushErrors, bNoReturns);
    }


    void UpdateLuaInterfaceHooks(CLuaInterface* pLuaInterface) {
        // TODO potential memory leak from not deleting the old hook
        if (pLuaInterface == nullptr) return;

        // Create a new hook
        g_pLuaInterfaceHook = new VMTHook(pLuaInterface);
    
        // Hook the functions
        g_pORunStringEx = (RunStringExFn)g_pLuaInterfaceHook->hookFunction(111, hkRunStringEx);

        // Say what we did
        LogHook((DWORD)g_pORunStringEx, "CLuaInterface::RunStringEx");
    }

}

#endif