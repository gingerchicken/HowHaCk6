#ifndef DRAWUTIL_H
#define DRAWUTIL_H

#include "interfaces.hpp"
#include "sourcesdk/tier0/Color.h"

enum GMOD_FONT {
	DebugFixed,
	DebugFixedSmall,
	DefaultFixedOutline,
	MenuItem,
	Default,
	TabLarge,
	DefaultBold,
	DefaultUnderline,
	DefaultSmall,
	DefaultSmallDropShadow,
	DefaultVerySmall,
	DefaultLarge,
	UiBold,
	MenuLarge,
	ConsoleText,
	Marlett,
	Trebuchet18,
	Trebuchet19,
	Trebuchet20,
	Trebuchet22,
	Trebuchet24,
	HUDNumber,
	HUDNumber1,
	HUDNumber2,
	HUDNumber3,
	HUDNumber4,
	HUDNumber5,
	HudHintTextLarge,
	HudHintTextSmall,
	CenterPrintText,
	HudSelectionText,
	DefaultFixed,
	DefaultFixedDropShadow,
	CloseCaption_Normal,
	CloseCaption_Bold,
	CloseCaption_BoldItalic,
	TitleFont,
	TitleFont2,
	ChatFont,
	TargetID,
	TargetIDSmall,
	HL2MPTypeDeath,
	BudgetLabel
};

namespace HowHack {
	void DrawString(const char* szText = "Sample Text", int iFont = 1, int iX = 0, int iY = 0, Color oColor = Color(255, 255, 255, 255)) {
		const size_t cSize = strlen(szText) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, szText, cSize);

		ISurface* surface = HowHack::g_pISurface;

		surface->DrawSetTextFont(iFont);
		surface->DrawSetTextColor(oColor);
		surface->DrawSetTextPos(iX, iY);
		surface->DrawPrintText(wc, cSize - 1);
		surface->DrawSetTextColor(255, 255, 255, 255);
		
		delete[] wc;
	}

	void DrawString(const char* szText = "Sample Text", GMOD_FONT eFont = TabLarge, int iX = 0, int iY = 0, Color oColor = Color(255, 255, 255, 255)) {
		int iFont = (int)eFont;
		DrawString(szText, iFont, iX, iY, oColor);
	}

	void DrawLine(int iFirstX = 0, int iFirstY = 0, int iSecondX = 0, int iSecondY = 0, Color oColor = Color(255, 255, 255, 255)) {
		ISurface* surface = HowHack::g_pISurface;
		
		surface->DrawSetColor(oColor);
		// surface->DrawLine(iFirstX, iFirstY, iSecondX, iSecondY);
		// The draw line function seems to not work.

		int aX[] = { iFirstX, iSecondX };
		int aY[] = { iFirstY, iSecondY };
		surface->DrawPolyLine(aX, aY, 2);

		surface->DrawSetColor(255, 255, 255, 255);
	}
	void DrawLine(Vector oFirstPos, Vector oSecondPos, Color oColor = Color(255, 255, 255, 255)) {
		DrawLine(oFirstPos.x, oFirstPos.y, oSecondPos.x, oSecondPos.y, oColor);
	}
	void DrawCircle(int iX, int iY, int iRadius, int iSegments, Color oColor = Color(255, 255, 255, 255)) {
		ISurface* surface = HowHack::g_pISurface;

		surface->DrawSetColor(oColor);
		surface->DrawOutlinedCircle(iX, iY, iRadius, iSegments);
		surface->DrawSetColor(Color(255, 255, 255, 255));
	}

	void DrawRect(int iX = 0, int iY = 0, int iWidth = 100, int iHeight = 100, Color oColor = Color(255, 255, 255, 255)) {
		ISurface* surface = HowHack::g_pISurface;
		
		surface->DrawSetColor(oColor);
		surface->DrawFilledRect(iX, iY, iX + iWidth, iY + iHeight);
		surface->DrawSetColor(255, 255, 255, 255);
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