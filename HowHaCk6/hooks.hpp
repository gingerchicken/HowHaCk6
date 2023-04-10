#ifndef HOOKS_H
#define HOOKS_H

#include <Windows.h>

#include "gconsole.h"
#include "interfaces.hpp"
#include "vmt.hpp"

#include "hooked/CLuaShared.hpp"
#include "hooked/VPanelWrapper.hpp"
#include "hooked/ClientModeShared.hpp"

namespace HowHack {
	VMTHook* g_pCLuaSharedHook;
	VMTHook* g_pVPanelWrapperHook;
	VMTHook* g_pClientModeHook;

	void SetupHooks() {
		g_pCLuaSharedHook = new VMTHook(g_pLuaShared);
		g_pOCreateLuaInterface = (CreateLuaInterfaceFn)g_pCLuaSharedHook->hookFunction(4, hkCreateLuaInterfaceFn);
	
		g_pVPanelWrapperHook = new VMTHook(g_pVPanelWrapper);
		g_pOPaintTraverse = (PaintTraverseFn)g_pVPanelWrapperHook->hookFunction(41, hkPaintTraverse);

		g_pClientModeHook = new VMTHook(g_pClientMode);
		g_pOCreateMove = (CreateMoveFn)g_pClientModeHook->hookFunction(21, hkCreateMove);
	}

	void LogHooks() {
		LogHook((DWORD)g_pOCreateLuaInterface, "CLuaShared::CreateLuaInterface");
		LogHook((DWORD)g_pOPaintTraverse, "VPanelWrapper::PaintTraverse");
		LogHook((DWORD)g_pOCreateMove, "ClientModeShared::CreateMove");
	}
}

#endif