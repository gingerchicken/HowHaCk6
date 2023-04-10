#ifndef ClientModeShared_HOOKS_H
#define ClientModeShared_HOOKS_H

#include <Windows.h>

#include "../gconsole.h"
#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"

typedef bool(__thiscall* CreateMoveFn)(ClientModeShared* _this, float flInputSampleTime, CUserCmd* pCmd);

namespace HowHack {
	CreateMoveFn g_pOCreateMove;

	bool __fastcall hkCreateMove(ClientModeShared* _this,
#ifndef _WIN64
		void*,
#endif
		float flInputSampleTime, CUserCmd* pCmd) {
		
		// TODO - Add your own code here

		return g_pOCreateMove(_this, flInputSampleTime, pCmd);
	}
}

#endif