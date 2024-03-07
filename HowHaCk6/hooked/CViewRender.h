#pragma once
#ifndef CViewRender_HOOKS_H
#define CViewRender_HOOKS_H

#include <Windows.h>

#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"
#include "ClientModeShared.hpp"

typedef void(__thiscall* RenderViewFn)(void*, CViewSetup&, int, int);

namespace HowHack {
	RenderViewFn g_pORenderView;

	void __fastcall hkRenderView(CViewRender* pViewRender, void*, CViewSetup& rSetup, int iClearFlags, int iDraw) {
		rSetup.angles = oOldAngles;

		g_pORenderView(pViewRender, rSetup, iClearFlags, iDraw);
	}
}

#endif