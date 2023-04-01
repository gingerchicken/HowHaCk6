#ifndef HOOKS_H
#define HOOKS_H

#include <Windows.h>

#include "gconsole.h"
#include "interfaces.hpp"
#include "vmt.hpp"

#include "hooked/CLuaShared.hpp"
#include "hooked/VPanelWrapper.hpp"

namespace HowHack {
	VMTHook* g_pCLuaSharedHook;
	VMTHook* g_pVPanelWrapperHook;

	void SetupHooks() {
		g_pCLuaSharedHook = new VMTHook(g_pLuaShared);
		g_pOCreateLuaInterface = (CreateLuaInterfaceFn)g_pCLuaSharedHook->hookFunction(4, hkCreateLuaInterfaceFn);
	
		g_pVPanelWrapperHook = new VMTHook(g_pVPanelWrapper);
		g_pOPaintTraverse = (PaintTraverseFn)g_pVPanelWrapperHook->hookFunction(41, hkPaintTraverse);
	}

	void LogHooks() {
		LogHook((DWORD)g_pOCreateLuaInterface, "CLuaShared::CreateLuaInterface");
		LogHook((DWORD)g_pOPaintTraverse, "VPanelWrapper::PaintTraverse");
	}
}

#endif