#pragma once
#include "../engine/vmatrix.h"
#include "../tier0/Color.h"
#include "../vgui/ISurfaceV30.h"

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

// Auto reconstructed from vtable block @ 0x000D7724
// from "vguimatsurface.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CMatSystemSurface
{
public:
	//Don't forget the constructor.
	/*0*/	virtual void* Connect(void* (*)(char const*, int*)) = 0;
	/*1*/	virtual void* Disconnect(void) = 0;
	/*2*/	virtual void* QueryInterface(char const*) = 0;
	/*3*/	virtual void* Init(void) = 0;
	/*4*/	virtual void* Shutdown(void) = 0;
	/*4*/	virtual void* NULLMETHOD0(void) = 0;
	/*4*/	virtual void* NULLMETHOD1(void) = 0;
	/*4*/	virtual void* NULLMETHOD2(void) = 0;
	/*4*/	virtual void* NULLMETHOD3(void) = 0;
	/*5*/	virtual void* RunFrame(void) = 0;
	/*6*/	virtual void* GetEmbeddedPanel(void) = 0;
	/*7*/	virtual void* SetEmbeddedPanel(unsigned int) = 0;
	/*8*/	virtual void* PushMakeCurrent(unsigned int, bool) = 0;
	/*9*/	virtual void* PopMakeCurrent(unsigned int) = 0;
	/*10*/	virtual void* DrawSetColor(int, int, int, int) = 0;
	/*11*/	virtual void* DrawSetColor(Color) = 0;
	/*12*/	virtual void* DrawFilledRect(int, int, int, int) = 0;
	/*13*/	virtual void* DrawFilledRectArray(void*, int) = 0;
	/*14*/	virtual void* DrawOutlinedRect(int, int, int, int) = 0;
	/*15*/	virtual void* DrawLine(int, int, int, int) = 0;
	/*16*/	virtual void* DrawPolyLine(int*, int*, int) = 0;
	/*17*/	virtual void* DrawSetTextFont(unsigned long) = 0;
	/*18*/	virtual void* DrawSetTextColor(int, int, int, int) = 0;
	/*19*/	virtual void* DrawSetTextColor(Color) = 0;
	/*20*/	virtual void* DrawSetTextPos(int, int) = 0;
	/*21*/	virtual void* DrawGetTextPos(int&, int&) = 0;
	/*22*/	virtual void* DrawPrintText(wchar_t const*, int, FontDrawType_t drawType = FONT_DRAW_DEFAULT) = 0;
	/*23*/	virtual void* DrawUnicodeChar(wchar_t, void*) = 0;
	/*24*/	virtual void* DrawFlushText(void) = 0;
	/*25*/	virtual void* CreateHTMLWindow(void*, unsigned int) = 0;
	/*26*/	virtual void* PaintHTMLWindow(void*) = 0;
	/*27*/	virtual void* DeleteHTMLWindow(void*) = 0;
	/*28*/	virtual void* DrawGetTextureId(char const*) = 0;
	/*29*/	virtual void* DrawGetTextureFile(int, char*, int) = 0;
	/*30*/	virtual void* DrawSetTextureFile(int, char const*, int, bool) = 0;
	/*31*/	virtual void* DrawSetTextureRGBA(int, unsigned char const*, int, int, int, bool) = 0;
	/*32*/	virtual void* DrawSetTexture(int) = 0;
	/*33*/	virtual void* DrawGetTextureSize(int, int&, int&) = 0;
	/*34*/	virtual void* DrawTexturedRect(int, int, int, int) = 0;
	/*35*/	virtual void* IsTextureIDValid(int) = 0;
	/*36*/	virtual void* DeleteTextureByID(int) = 0;
	/*37*/	virtual void* CreateNewTextureID(bool) = 0;
	/*38*/	virtual void* GetScreenSize(int&, int&) = 0;
	/*39*/	virtual void* SetAsTopMost(unsigned int, bool) = 0;
	/*40*/	virtual void* BringToFront(unsigned int) = 0;
	/*41*/	virtual void* SetForegroundWindow(unsigned int) = 0;
	/*42*/	virtual void* SetPanelVisible(unsigned int, bool) = 0;
	/*43*/	virtual void* SetMinimized(unsigned int, bool) = 0;
	/*44*/	virtual void* IsMinimized(unsigned int) = 0;
	/*45*/	virtual void* FlashWindow(unsigned int, bool) = 0;
	/*46*/	virtual void* SetTitle(unsigned int, wchar_t const*) = 0;
	/*47*/	virtual void* SetAsToolBar(unsigned int, bool) = 0;
	/*48*/	virtual void* CreatePopup(unsigned int, bool, bool, bool, bool, bool) = 0;
	/*49*/	virtual void* SwapBuffers(unsigned int) = 0;
	/*50*/	virtual void* Invalidate(unsigned int) = 0;
	/*51*/	virtual void SetCursor(unsigned long) = 0;
	/*52*/	virtual void SetCursorAlwaysVisible(bool) = 0;
	/*53*/	virtual bool IsCursorVisible(void) = 0;
	/*58*/	virtual void* RestrictPaintToSinglePanel(unsigned int) = 0;
	/*59*/	virtual void* SetModalPanel(unsigned int) = 0;
	/*60*/	virtual void* GetModalPanel(void) = 0;
	/*61*/	virtual void* UnlockCursor(void) = 0;
	/*62*/	virtual void* LockCursor(void) = 0;
	/*63*/	virtual void* SetTranslateExtendedKeys(bool) = 0;
	/*64*/	virtual void* GetTopmostPopup(void) = 0;
	/*65*/	virtual void* SetTopLevelFocus(unsigned int) = 0;
	/*67*/	virtual void* NULLMETHOD4(void) = 0;
	/*67*/	virtual void* NULLMETHOD5(void) = 0;
	/*67*/	virtual void* NULLMETHOD6(void) = 0;
	/*67*/	virtual void* NULLMETHOD7(void) = 0;
	/*66*/	virtual void* CreateFont(void) = 0;
	/*67*/	virtual void* SetFontGlyphSet(unsigned long, char const*, int, int, int, int, int, int, int) = 0;
	/*68*/	virtual void* SetFontGlyphSet_Extended(unsigned long, char const*, int, int, int, int, int, bool) = 0;
	/*69*/	virtual void* AddCustomFontFile(char const*, char const*) = 0;
	/*70*/	virtual void* GetFontTall(unsigned long) = 0;
	/*71*/	virtual void* GetFontTallRequested(unsigned long) = 0;
	/*72*/	virtual void* GetFontAscent(unsigned long, wchar_t) = 0;
	/*73*/	virtual void* IsFontAdditive(unsigned long) = 0;
	/*74*/	virtual void* GetCharABCwide(unsigned long, int, int&, int&, int&) = 0;
	/*75*/	virtual void* GetCharacterWidth(unsigned long, int) = 0;
	/*76*/	virtual void* GetTextSize(unsigned long, wchar_t const*, int&, int&) = 0;
	/*77*/	virtual void* GetNotifyPanel(void) = 0;
	/*78*/	virtual void* SetNotifyIcon(unsigned int, unsigned long, unsigned int, char const*) = 0;
	/*79*/	virtual void* PlaySound(char const*) = 0;
	/*80*/	virtual void* GetPopupCount(void) = 0;
	/*81*/	virtual void* GetPopup(int) = 0;
	/*82*/	virtual void* ShouldPaintChildPanel(unsigned int) = 0;
	/*83*/	virtual void* RecreateContext(unsigned int) = 0;
	/*84*/	virtual void* AddPanel(unsigned int) = 0;
	/*85*/	virtual void* ReleasePanel(unsigned int) = 0;
	/*86*/	virtual void* MovePopupToFront(unsigned int) = 0;
	/*87*/	virtual void* MovePopupToBack(unsigned int) = 0;
	/*88*/	virtual void* SolveTraverse(unsigned int, bool) = 0;
	/*89*/	virtual void* PaintTraverse(unsigned int) = 0;
	/*90*/	virtual void* EnableMouseCapture(unsigned int, bool) = 0;
	/*91*/	virtual void* GetWorkspaceBounds(int&, int&, int&, int&) = 0;
	/*92*/	virtual void* GetAbsoluteWindowBounds(int&, int&, int&, int&) = 0;
	/*93*/	virtual void* GetProportionalBase(int&, int&) = 0;
	/*94*/	virtual void* CalculateMouseVisible(void) = 0;
	/*95*/	virtual void* NeedKBInput(void) = 0;
	/*96*/	virtual void* HasCursorPosFunctions(void) = 0;
	/*97*/	virtual void* SurfaceGetCursorPos(int&, int&) = 0;
	/*98*/	virtual void* SurfaceSetCursorPos(int, int) = 0;
	/*99*/	virtual void* DrawTexturedLine(SurfaceV30::Vertex_t const&, SurfaceV30::Vertex_t const&) = 0;
	/*100*/	virtual void* DrawOutlinedCircle(int, int, int, int) = 0;
	/*101*/	virtual void* DrawTexturedPolyLine(SurfaceV30::Vertex_t const*, int) = 0;
	/*102*/	virtual void* DrawTexturedSubRect(int, int, int, int, float, float, float, float) = 0;
	/*103*/	virtual void* DrawTexturedPolygon(int, SurfaceV30::Vertex_t*, bool) = 0;
	/*104*/	virtual void* GetTitle(unsigned int) = 0;
	/*105*/	virtual void* IsCursorLocked(void)const = 0;
	/*106*/	virtual void* SetWorkspaceInsets(int, int, int, int) = 0;
	/*107*/	virtual void* DrawGetUnicodeCharRenderInfo(wchar_t, void*) = 0;
	/*108*/	virtual void* DrawRenderCharFromInfo(void* const) = 0;
	/*109*/	virtual void* DrawSetAlphaMultiplier(float) = 0;
	/*110*/	virtual void* DrawGetAlphaMultiplier(void) = 0;
	/*111*/	virtual void* SetAllowHTMLJavaScript(bool) = 0;
	/*112*/	virtual void* OnScreenSizeChanged(int, int) = 0;
	/*113*/	virtual void* CreateCursorFromFile(char const*, char const*) = 0;
	/*114*/	virtual void* DrawGetTextureMatInfoFactory(int) = 0;
	/*115*/	virtual void* PaintTraverseEx(unsigned int, bool) = 0;
	/*116*/	virtual void* GetZPos(void)const = 0;
	/*117*/	virtual void* SetPanelForInput(unsigned int) = 0;
	/*118*/	virtual void* DrawFilledRectFastFade(int, int, int, int, int, int, unsigned int, unsigned int, bool) = 0;
	/*119*/	virtual void* DrawFilledRectFade(int, int, int, int, unsigned int, unsigned int, bool) = 0;
	/*120*/	virtual void* DrawSetTextureRGBAEx(int, unsigned char const*, int, int, void*, int) = 0;
	/*121*/	virtual void* DrawSetTextScale(float, float) = 0;
	/*122*/	virtual void* SetBitmapFontGlyphSet(unsigned long, char const*, float, float, int) = 0;
	/*123*/	virtual void* AddBitmapFontFile(char const*) = 0;
	/*124*/	virtual void* SetBitmapFontName(char const*, char const*) = 0;
	/*125*/	virtual void* GetBitmapFontName(char const*) = 0;
	/*126*/	virtual void* ClearTemporaryFontCache(void) = 0;
	/*127*/	virtual void* GetIconImageForFullPath(char const*) = 0;
	/*128*/	virtual void* DrawUnicodeString(wchar_t const*, void*) = 0;
	/*129*/	virtual void* PrecacheFontCharacters(unsigned long, wchar_t const*) = 0;
	/*130*/	virtual void* GetResolutionKey(void)const = 0;
	/*131*/	virtual void* GetFontName(unsigned long) = 0;
	/*132*/	virtual void* GetFontFamilyName(unsigned long) = 0;
	/*133*/	virtual void* GetKernedCharWidth(unsigned long, wchar_t, wchar_t, wchar_t, float&, float&) = 0;
	/*134*/	virtual void* ForceScreenSizeOverride(bool, int, int) = 0;
	/*135*/	virtual void* ForceScreenPosOffset(bool, int, int) = 0;
	/*136*/	virtual void* OffsetAbsPos(int&, int&) = 0;
	/*137*/	virtual void* ResetFontCaches(void) = 0;
	/*138*/	virtual void* GetTextureNumFrames(int) = 0;
	/*139*/	virtual void* DrawSetTextureFrame(int, int, unsigned int*) = 0;
	/*140*/	virtual void* IsScreenSizeOverrideActive(void) = 0;
	/*141*/	virtual void* IsScreenPosOverrideActive(void) = 0;
	/*142*/	virtual void* DestroyTextureID(int) = 0;
	/*143*/	virtual void* DrawUpdateRegionTextureRGBA(int, int, int, unsigned char const*, int, int, void*) = 0;
	/*144*/	virtual void* BHTMLWindowNeedsPaint(void*) = 0;
	/*145*/	virtual void* GetWebkitHTMLUserAgentString(void) = 0;
	/*146*/	virtual void* AccessChromeHTMLController(void) = 0;
	/*147*/	virtual void* SetFullscreenViewport(int, int, int, int) = 0;
	/*148*/	virtual void* GetFullscreenViewport(int&, int&, int&, int&) = 0;
	/*149*/	virtual void* PushFullscreenViewport(void) = 0;
	/*150*/	virtual void* PopFullscreenViewport(void) = 0;
	/*151*/	virtual void* SetSoftwareCursor(bool) = 0;
	/*152*/	virtual void* PaintSoftwareCursor(void) = 0;
	/*153*/	virtual void* GMOD_ClearFontCache(void) = 0;
	/*154*/	virtual void* GMOD_GetTextSize(unsigned long, wchar_t const*, int&, int&) = 0;
	/*155*/	virtual void* GMOD_DrawGetColor(void) = 0;
	/*156*/	virtual void* GMOD_DrawGetTextColor(void) = 0;
	/*157*/	virtual void* AttachToWindow(void*, bool) = 0;
	/*158*/	virtual void* EnableWindowsMessages(bool) = 0;
	/*159*/	virtual void* Begin3DPaint(int, int, int, int, bool) = 0;
	/*160*/	virtual void* End3DPaint(void) = 0;
	/*161*/	virtual void* DisableClipping(bool) = 0;
	/*162*/	virtual void* GetClippingRect(int&, int&, int&, int&, bool&) = 0;
	/*163*/	virtual void* SetClippingRect(int, int, int, int) = 0;
	/*164*/	virtual void* SetMouseCallbacks(void (*)(int&, int&), void (*)(int, int)) = 0;
	/*165*/	virtual void* InstallPlaySoundFunc(void (*)(char const*)) = 0;
	/*166*/	virtual void* DrawColoredCircle(int, int, float, int, int, int, int) = 0;
	/*167*/	virtual void* DrawColoredText(unsigned long, int, int, int, int, int, int, char const*, ...) = 0;
	/*168*/	virtual void* DrawColoredTextRect(unsigned long, int, int, int, int, int, int, int, int, char const*, ...) = 0;
	/*169*/	virtual void* DrawTextHeight(unsigned long, int, int&, char const*, ...) = 0;
	/*170*/	virtual void* DrawTextLen(unsigned long, char const*, ...) = 0;
	/*171*/	virtual void* DrawPanelIn3DSpace(unsigned int, VMatrix const&, int, int, float, float) = 0;
	/*172*/	virtual void* DrawSetTextureMaterial(int, IMaterial*) = 0;
	/*173*/	virtual void* HandleInputEvent(void*) = 0;
	/*174*/	virtual void* Set3DPaintTempRenderTarget(char const*) = 0;
	/*175*/	virtual void* Reset3DPaintTempRenderTarget(void) = 0;
	/*176*/	virtual void* DrawGetTextureMaterial(int) = 0;

};