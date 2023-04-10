#pragma once
#ifndef VPanelWrapper_HOOKS_H
#define VPanelWrapper_HOOKS_H

#include <Windows.h>

#include "../sourcesdk/sdk.h"	
#include "../interfaces.hpp"
#include "drawutil.hpp"

#include "../modules/esp.hpp"

typedef void(__thiscall* PaintTraverseFn)(VPanelWrapper*, VPanel* pPanel, bool bForceRepaint, bool bForceAllow);

namespace HowHack {
	PaintTraverseFn g_pOPaintTraverse;

	void __fastcall hkPaintTraverse(VPanelWrapper* _this,
#ifndef _WIN64
		void* edx,
#endif
		VPanel* pPanel, bool bForceRepaint, bool bForceAllow) {

		g_pOPaintTraverse(_this, pPanel, bForceRepaint, bForceAllow);
		
		// Garry's Mod HUD only!
		const char* szName = HowHack::g_pVPanelWrapper->GetName(pPanel);
		if (strcmp(szName, "HudGMOD")) return;

		HowHack::DrawString("Legacy is a good developer.", HUDNumber5, 5, 5);

		// TODO add a menu and toggle this
		HowHack::CheatESP::DrawESP();
	}
}

#endif