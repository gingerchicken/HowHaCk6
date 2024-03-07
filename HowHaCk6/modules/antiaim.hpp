#pragma once
#ifndef ANTIAIM_H
#define ANTIAIM_H

#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"
#include "module.hpp"

#include "../mathutil.hpp"

namespace HowHack {
	class AntiAim : public Module {
	public:
		bool m_bFlip = false;

		bool AfterCreateMove(CUserCmd* pCmd) {
			if (!this->m_bEnable) return false;

			// real anti-aim xddd (nah just a placeholder trust)

			pCmd->viewangles.x = (rand() % 100 > 50 ? 1 : -1) * 89.0f;
			pCmd->viewangles.y = (m_bFlip = !m_bFlip) ? 0 : rand() % 180;

			return true;
		}
	};



	AntiAim oAntiAim;
}


#endif