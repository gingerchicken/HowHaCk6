#ifndef Present_HOOKS_H
#define Present_HOOKS_H

#include <Windows.h>

#include "../gconsole.h"
#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"

#include "../menu.hpp"

typedef HRESULT(__stdcall* PresentFn)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);

namespace HowHack {
	PresentFn g_pOPresent;

	HRESULT __stdcall hkPresent(IDirect3DDevice9* pDevice,
		CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {
		
		HowHack::PresentMenu(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

		return g_pOPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}
}

#endif