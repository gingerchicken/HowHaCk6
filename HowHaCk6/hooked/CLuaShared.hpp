#ifndef CLuaShared_HOOKS_H
#define CLuaShared_HOOKS_H

#include <Windows.h>

#include "../gconsole.h"
#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"

typedef CLuaInterface* (__thiscall* CreateLuaInterfaceFn)(CLuaShared*, LuaInterfaceType, bool);

namespace HowHack {
	CreateLuaInterfaceFn g_pOCreateLuaInterface;

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

        return pLuaInterface;
    }
}

#endif