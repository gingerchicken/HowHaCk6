#pragma once
#ifndef VPanelWrapper_HOOKS_H
#define VPanelWrapper_HOOKS_H

#include <Windows.h>

#include "../sourcesdk/sdk.h"	
#include "../interfaces.hpp"
#include "drawutil.hpp"

#include "esp.hpp"

typedef void(__thiscall* PaintTraverseFn)(VPanelWrapper*, VPanel* pPanel, bool bForceRepaint, bool bForceAllow);

namespace HowHack {
	PaintTraverseFn g_pOPaintTraverse;

	void __fastcall hkPaintTraverse(VPanelWrapper* _this,
#ifndef _WIN64
		void* edx,
#endif
		VPanel* pPanel, bool bForceRepaint, bool bForceAllow) {

		g_pOPaintTraverse(_this, pPanel, bForceRepaint, bForceAllow);
	}
}

#endif