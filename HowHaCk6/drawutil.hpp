#ifndef DRAWUTIL_H
#define DRAWUTIL_H

#include "../interfaces.hpp"
#include "../sourcesdk/tier0/Color.h"

namespace HowHack {
	void SimpleDrawText(const char* szText = "Sample Text", int font = 1, int x = 0, int y = 0, Color color = Color(255, 255, 255, 255)) {
		const size_t cSize = strlen(szText) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, szText, cSize);

		ISurface* surface = HowHack::g_pISurface;

		surface->DrawSetTextFont(font);
		surface->DrawSetTextColor(color);
		surface->DrawSetTextPos(x, y);
		surface->DrawPrintText(wc, cSize - 1);
		surface->DrawSetTextColor(255, 255, 255, 255);
		
		delete[] wc;
	}

	bool WorldToScreen(Vector oIn, Vector& oOut, bool bIgnoreInvisible = false) {
		const VMatrix oW2S = HowHack::g_pEngineClient->WorldToScreenMatrix();
		float w = oW2S[3][0] * oIn.x + oW2S[3][1] * oIn.y + oW2S[3][2] * oIn.z + oW2S[3][3];

		if (bIgnoreInvisible) w = abs(w);

		if (w < 0.001f) return false;

		int iWidth, iHeight;
		HowHack::g_pEngineClient->GetScreenSize(iWidth, iHeight);

		float fl1DBw = 1.f / w;
		oOut.x = (iWidth / 2.f) + (0.5f * ((oW2S[0][0] * oIn.x + oW2S[0][1] * oIn.y + oW2S[0][2] * oIn.z + oW2S[0][3]) * fl1DBw) * iWidth + 0.5f);
		oOut.y = (iHeight / 2.f) - (0.5f * ((oW2S[1][0] * oIn.x + oW2S[1][1] * oIn.y + oW2S[1][2] * oIn.z + oW2S[1][3]) * fl1DBw) * iHeight + 0.5f);
		oOut.z = 0.f;
		
		return true;
	}
}

#endif