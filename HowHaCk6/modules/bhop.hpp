#pragma once
#ifndef BHOP_H
#define BHOP_H

#include "../interfaces.hpp"
#include "../gconsole.h"
#include "module.hpp"

namespace HowHack {

	// TODO make this a singleton
	class CheatBHOP : public Module {
	public:
		void Hop(CUserCmd* pCmd) {
			if (!m_bEnable) return;

			int iFlags = GetLocalPlayer()->getFlags();

			if (g_pInputSystem->IsButtonDown(KEY_SPACE) && GetLocalPlayer()->getMoveType() != MOVETYPE_NOCLIP) {
				if (!(iFlags & FL_ONGROUND)) {
					pCmd->buttons &= ~IN_JUMP;
				}
				else {
					pCmd->buttons |= IN_JUMP;
				}
			}
		}
	};

	CheatBHOP oBhop;
}

#endif