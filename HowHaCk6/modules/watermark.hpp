#pragma once
#ifndef WATERMARK_H
#define WATERMARK_H

#include "../interfaces.hpp"
#include "../gconsole.h"
#include "../drawutil.hpp"
#include "module.hpp"

namespace HowHack {
	class Watermark : public Module {
	public:
		void DrawWatermark() {
			if (!this->m_bEnable) return;

			HowHack::DrawString("Legacy is a good developer.", HUDNumber5, 15, 15);
		}
	};

	Watermark oWatermark;
}

#endif