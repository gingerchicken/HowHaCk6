#ifndef ClientModeShared_HOOKS_H
#define ClientModeShared_HOOKS_H

#include <Windows.h>

#include "../gconsole.h"
#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"

#include "../modules/bhop.hpp"
#include "../modules/antiaim.hpp"
#include "../modules/aimbot.hpp"

typedef bool(__thiscall* CreateMoveFn)(ClientModeShared* _this, float flInputSampleTime, CUserCmd* pCmd);

namespace HowHack {
	CreateMoveFn g_pOCreateMove;
	QAngle oOldAngles(0,0,0);

	bool __fastcall hkCreateMove(ClientModeShared* _this,
#ifndef _WIN64
		void*,
#endif
		float flInputSampleTime, CUserCmd* pCmd) {
		
		oBhop.Hop(pCmd);

		oOldAngles = pCmd->viewangles;
		
		// Thingy
		if (pCmd->command_number == 0 || !g_pEngineClient->IsInGame() || !GetLocalPlayer() || !GetLocalPlayer()->IsAlive()) {
			g_pOCreateMove(_this, flInputSampleTime, pCmd);
			return false;
		}

		if (oAimbot.AfterCreateMove(pCmd)) {
			CorrectMovement(pCmd, oOldAngles);
			return false;
		}

		if (oAntiAim.AfterCreateMove(pCmd)) {
			CorrectMovement(pCmd, oOldAngles);
			return false;
		}

		return g_pOCreateMove(_this, flInputSampleTime, pCmd);
	}
}

#endif