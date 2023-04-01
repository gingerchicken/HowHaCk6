#ifndef HOOKS_H
#define HOOKS_H

#include <Windows.h>

#include "gconsole.h"
#include "interfaces.hpp"
#include "vmt.hpp"

#include "hooked/CLuaShared.hpp"

namespace HowHack {
	VMTHook* g_pCLuaSharedHook;

	void SetupHooks() {
		g_pCLuaSharedHook = new VMTHook(g_pLuaShared);
		g_pOCreateLuaInterface = (CreateLuaInterfaceFn)g_pCLuaSharedHook->hookFunction(4, hkCreateLuaInterfaceFn);
	}

	void LogHook(DWORD dwHook, const char* sHookName) {
		if (dwHook) {
			HowHack::Log("[+] %s: 0x%X\n", sHookName, dwHook);
		}
		else {
			HowHack::Log("[-] %s: 0x%X\n", sHookName, dwHook);
		}
	}

	void LogHooks() {
		LogHook((DWORD)g_pOCreateLuaInterface, "CLuaShared::CreateLuaInterface");
	}
}

#endif