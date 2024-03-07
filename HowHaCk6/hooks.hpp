#ifndef HOOKS_H
#define HOOKS_H

#include <Windows.h>

#include "gconsole.h"
#include "interfaces.hpp"
#include "vmt.hpp"

#include "hooked/CLuaShared.hpp"
#include "hooked/VPanelWrapper.hpp"
#include "hooked/ClientModeShared.hpp"
#include "hooked/Present.hpp"
#include "hooked/CViewRender.h"

namespace HowHack {
	VMTHook* g_pCLuaSharedHook;
	VMTHook* g_pVPanelWrapperHook;
	VMTHook* g_pClientModeHook;
	VMTHook* g_pRenderViewHook;

	void SetupHooks() {
		g_pCLuaSharedHook = new VMTHook(g_pLuaShared);
		g_pOCreateLuaInterface = (CreateLuaInterfaceFn)g_pCLuaSharedHook->hookFunction(4, hkCreateLuaInterfaceFn);
	
		g_pVPanelWrapperHook = new VMTHook(g_pVPanelWrapper);
		g_pOPaintTraverse = (PaintTraverseFn)g_pVPanelWrapperHook->hookFunction(41, hkPaintTraverse);

		g_pClientModeHook = new VMTHook(g_pClientMode);
		g_pOCreateMove = (CreateMoveFn)g_pClientModeHook->hookFunction(21, hkCreateMove);

		g_pRenderViewHook = new VMTHook(g_pViewRender);
		g_pORenderView = (RenderViewFn)g_pRenderViewHook->hookFunction(6, hkRenderView);

		// Present
		char* pPresent = GetRealFromRelative((char*)FindPattern(MODULE_PRESENT, PATTERN_PRESENT), 2, 6, false);
		g_pOPresent = *(PresentFn*)(pPresent);
		// VMT when?
		*(PresentFn**)(pPresent) = (PresentFn*)hkPresent;
	}

	void LogHooks() {
		LogHook((DWORD)g_pOCreateLuaInterface, "CLuaShared::CreateLuaInterface");
		LogHook((DWORD)g_pOPaintTraverse, "VPanelWrapper::PaintTraverse");
		LogHook((DWORD)g_pOCreateMove, "ClientModeShared::CreateMove");
		LogHook((DWORD)g_pOPresent, "IDirect3DDevice9::Present");
		LogHook((DWORD)g_pORenderView, "CViewRender::RenderView");
	}
}

#endif