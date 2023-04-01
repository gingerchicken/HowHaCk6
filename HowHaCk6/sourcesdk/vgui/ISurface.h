#ifndef ISURFACE_H
#define ISURFACE_H

#include "../vguimatsurface/CMatSystemSurface.h"

#include "./ISurfaceV30.h"
#include "../vgui/VPanelWrapper.h"

typedef unsigned long VPANEL;
typedef unsigned long HCursor;
typedef unsigned long HTexture;
typedef unsigned long HFont;

struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};
struct Vertex_t
{
	Vertex_t() {}
	Vertex_t(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
	void Init(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}

	Vector2D	m_Position;
	Vector2D	m_TexCoord;
};
enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,

	// Depth-stencil texture formats for shadow depth mapping
	IMAGE_FORMAT_NV_DST16,		// 
	IMAGE_FORMAT_NV_DST24,		//
	IMAGE_FORMAT_NV_INTZ,		// Vendor-specific depth-stencil texture
	IMAGE_FORMAT_NV_RAWZ,		// formats for shadow depth mapping 
	IMAGE_FORMAT_ATI_DST16,		// 
	IMAGE_FORMAT_ATI_DST24,		//
	IMAGE_FORMAT_NV_NULL,		// Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

	NUM_IMAGE_FORMATS
};
// Refactor these two
struct CharRenderInfo
{
	// Text pos
	int				x, y;
	// Top left and bottom right
	// This is now a pointer to an array maintained by the surface, to avoid copying the data on the 360
	Vertex_t* verts;
	int				textureId;
	int				abcA;
	int				abcB;
	int				abcC;
	int				fontTall;
	HFont			currentFont;
	// In:
	FontDrawType_t	drawType;
	wchar_t			ch;

	// Out
	bool			valid;
	// In/Out (true by default)
	bool			shouldclip;
};
/// <summary>
/// Not really sure of its purpose
/// </summary>
class IAppSystem
{
public:
	virtual void		Nothing_Important__00() = 0;
	virtual void		Nothing_Important__01() = 0;
	virtual void		Nothing_Important__02() = 0;
	virtual void		Nothing_Important__03() = 0;
};
class ISurface : public IAppSystem
{
public:
	// call to Shutdown surface; surface can no longer be used after this is called
	virtual void		Shutdown() = 0;

	// frame
	virtual void		RunFrame() = 0;

	// hierarchy root
	virtual VPanel* GetEmbeddedPanel() = 0;
	virtual void		SetEmbeddedPanel(VPanel* pPanel) = 0;

	// drawing context
	virtual void		PushMakeCurrent(VPanel* panel, bool useInsets) = 0;
	virtual void		PopMakeCurrent(VPanel* panel) = 0;

	// rendering functions
	virtual void		DrawSetColor(int r, int g, int b, int a) = 0;
	virtual void		DrawSetColor(Color col) = 0;

	virtual void		DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void		DrawFilledRectArray(IntRect* pRects, int numRects) = 0;
	virtual void		DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;

	virtual void		DrawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void		DrawPolyLine(int* px, int* py, int numPoints) = 0;

	virtual void		DrawSetTextFont(int font) = 0;
	virtual void		DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void		DrawSetTextColor(Color col) = 0;
	virtual void		DrawSetTextPos(int x, int y) = 0;
	virtual void		DrawGetTextPos(int& x, int& y) = 0;
	virtual void		DrawPrintText(const wchar_t* text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT) = 0;
	virtual void		DrawUnicodeChar(wchar_t wch, FontDrawType_t drawType = FONT_DRAW_DEFAULT) = 0;

	virtual void		DrawFlushText() = 0;		// flushes any buffered text (for rendering optimizations)
	virtual void* CreateHTMLWindow(void* events, VPanel* context) = 0;
	virtual void		Nothing__00(void*) = 0;
	virtual void		Nothing__01(void*) = 0;

	enum ETextureFormat
	{
		eTextureFormat_RGBA,
		eTextureFormat_BGRA,
		eTextureFormat_BGRA_Opaque, // bgra format but alpha is always 255, CEF does this, we can use this fact for better perf on win32 gdi
	};
	virtual int			DrawGetTextureId(char const* filename) = 0;
	virtual bool		DrawGetTextureFile(int id, char* filename, int maxlen) = 0;
	virtual void		DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
	virtual void		DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall, int hardwareFilter, bool forceReload) = 0;
	virtual void		DrawSetTexture(int id) = 0;
	virtual void		DrawGetTextureSize(int id, int& wide, int& tall) = 0;
	virtual void		DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual bool		IsTextureIDValid(int id) = 0;
	virtual bool		DeleteTextureByID(int id) = 0;

	virtual int			CreateNewTextureID(bool procedural = false) = 0;

	virtual void		GetScreenSize(int& wide, int& tall) = 0;
	virtual void		Nothing__02() = 0;
	virtual void		BringToFront(VPanel* panel) = 0;
	virtual void		SetForegroundWindow(VPanel* panel) = 0;
	virtual void		Nothing__03() = 0;
	virtual void		SetMinimized(VPanel* panel, bool state) = 0;
	virtual bool		IsMinimized(VPanel* panel) = 0;
	virtual void		Nothing__04() = 0;
	virtual void		SetTitle(VPanel* panel, const wchar_t* title) = 0;
	virtual void		Nothing__05() = 0;

	// windows stuff
	virtual void		CreatePopup(VPanel* panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
	virtual void		SwapBuffers(VPanel* panel) = 0;
	virtual void		Invalidate(VPanel* panel) = 0;
	virtual void		SetCursor(HCursor cursor) = 0;
	virtual void		SetCursorAlwaysVisible(bool visible) = 0;
	virtual bool		IsCursorVisible() = 0;
	virtual void		Nothing__08() = 0;
	virtual bool		IsWithin(int x, int y) = 0;
	virtual bool		HasFocus() = 0;

	// returns true if the surface supports minimize & maximize capabilities
	enum SurfaceFeature_e
	{
		ANTIALIASED_FONTS = 1,
		DROPSHADOW_FONTS = 2,
		ESCAPE_KEY = 3,
		OPENING_NEW_HTML_WINDOWS = 4,
		FRAME_MINIMIZE_MAXIMIZE = 5,
		OUTLINE_FONTS = 6,
		DIRECT_HWND_RENDER = 7,
	};
	virtual bool		SupportsFeature(SurfaceFeature_e feature) = 0;

	// restricts what gets drawn to one panel and it's children
	// currently only works in the game
	virtual void		RestrictPaintToSinglePanel(VPANEL panel) = 0;
	virtual void		Nothing__09() = 0;
	virtual void		Nothing__10() = 0;

	virtual void		UnlockCursor() = 0;
	virtual void		LockCursor() = 0;
	virtual void		Nothing__11() = 0;
	virtual void		Nothing__12() = 0;
	virtual void		SetTopLevelFocus(VPANEL panel) = 0;
	virtual int			ISCreateFont() = 0;
	virtual bool		SetFontGlyphSet(int font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) = 0;
	virtual bool		SetFontGlyphSet_Extended() = 0; // just use above lol.

	// adds a custom font file (only supports true type font files (.ttf) for now)
	virtual bool		AddCustomFontFile(const char* fontName, const char* fontFileName) = 0;

	// returns the details about the font
	virtual int			GetFontTall(int font) = 0;
	virtual int			GetFontTallRequested(int font) = 0;
	virtual int			GetFontAscent(int font, wchar_t wch) = 0;
	virtual bool		IsFontAdditive(int font) = 0;
	virtual void		GetCharABCwide(int font, int ch, int& a, int& b, int& c) = 0;
	virtual int			GetCharacterWidth(int font, int ch) = 0;
	virtual void		GetTextSize(int font, const wchar_t* text, int& wide, int& tall) = 0;

	virtual void		Nothing__13() = 0;
	virtual void		Nothing__14() = 0;

	// plays a sound
	virtual void		ISPlaySound(const char* fileName) = 0;


	//!! these functions should not be accessed directly, but only through other vgui items
	//!! need to move these to seperate interface
	virtual int			GetPopupCount() = 0;
	virtual VPanel* GetPopup(int index) = 0;
	virtual bool		ShouldPaintChildPanel(VPanel* childPanel) = 0;
	virtual bool		RecreateContext(VPanel* panel) = 0;
	virtual void		AddPanel(VPanel* panel) = 0;
	virtual void		ReleasePanel(VPanel* panel) = 0;
	virtual void		MovePopupToFront(VPanel* panel) = 0;
	virtual void		MovePopupToBack(VPanel* panel) = 0;

	virtual void		SolveTraverse(VPanel* panel, bool forceApplySchemeSettings = false) = 0;
	virtual void		PaintTraverse(VPanel* panel) = 0;

	virtual void		EnableMouseCapture(VPanel* panel, bool state) = 0;

	// returns the size of the workspace
	virtual void		GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;

	// gets the absolute coordinates of the screen (in windows space)
	virtual void		GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;

	// gets the base resolution used in proportional mode
	virtual void		GetProportionalBase(int& width, int& height) = 0;

	virtual void		CalculateMouseVisible() = 0;
	virtual bool		NeedKBInput() = 0;

	virtual void		Nothing__15() = 0;

	virtual void		SurfaceGetCursorPos(int& x, int& y) = 0;
	virtual void		SurfaceSetCursorPos(int x, int y) = 0;

	// SRC only functions!!!
	virtual void		DrawTexturedLine(const Vertex_t& a, const Vertex_t& b) = 0;
	virtual void		DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
	virtual void		DrawTexturedPolyLine(const Vertex_t* p, int n) = 0; // (Note: this connects the first and last points).
	virtual void		DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void		DrawTexturedPolygon(int n, Vertex_t* pVertice, bool bClipVertices = true) = 0;
	virtual const wchar_t* GetTitle(VPANEL panel) = 0;
	virtual bool		IsCursorLocked(void) const = 0;
	virtual void		SetWorkspaceInsets(int left, int top, int right, int bottom) = 0;
	// Lower level char drawing code, call DrawGet then pass in info to DrawRender
	virtual bool		DrawGetUnicodeCharRenderInfo(wchar_t ch, CharRenderInfo& info) = 0;
	virtual void		DrawRenderCharFromInfo(const CharRenderInfo& info) = 0;

	// global alpha setting functions
	// affect all subsequent draw calls - shouldn't normally be used directly, only in Panel::PaintTraverse()
	virtual void		DrawSetAlphaMultiplier(float alpha /* [0..1] */) = 0;
	virtual float		DrawGetAlphaMultiplier() = 0;

	// web browser
	virtual void		SetAllowHTMLJavaScript(bool state) = 0;

	// video mode changing
	virtual void		OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0;

	virtual void		Nothing__16() = 0;

	// create IVguiMatInfo object ( IMaterial wrapper in VguiMatSurface, NULL in CWin32Surface )
	virtual void* DrawGetTextureMatInfoFactory(int id) = 0;

	virtual void		PaintTraverseEx(VPANEL panel, bool paintPopups = false) = 0;
	virtual float		GetZPos() const = 0;

	// From the Xbox
	virtual void		SetPanelForInput(VPANEL vpanel) = 0;
	virtual void		DrawFilledRectFastFade(int x0, int y0, int x1, int y1, int fadeStartPt, int fadeEndPt, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void		DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void		DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat) = 0;
	virtual void		DrawSetTextScale(float sx, float sy) = 0;
	virtual bool		SetBitmapFontGlyphSet(int font, const char* windowsFontName, float scalex, float scaley, int flags) = 0;

	// adds a bitmap font file
	virtual bool		AddBitmapFontFile(const char* fontFileName) = 0;
	// sets a symbol for the bitmap font
	virtual void		SetBitmapFontName(const char* pName, const char* pFontFilename) = 0;
	// gets the bitmap font filename
	virtual const char* GetBitmapFontName(const char* pName) = 0;
	virtual void		ClearTemporaryFontCache(void) = 0;
	virtual void* GetIconImageForFullPath(char const* pFullPath) = 0;
	virtual void		DrawUnicodeString(const wchar_t* pwString, FontDrawType_t drawType = FONT_DRAW_DEFAULT) = 0;
	virtual void		PrecacheFontCharacters(int font, const wchar_t* pCharacters) = 0;
	// Console-only.  Get the string to use for the current video mode for layout files.
	virtual const char* GetResolutionKey(void) const = 0;
	virtual const char* GetFontName(int font) = 0;
	virtual const char* GetFontFamilyName(int font) = 0;
	virtual void		GetKernedCharWidth(int font, wchar_t ch, wchar_t chBefore, wchar_t chAfter, float& wide, float& abcA) = 0;
	virtual bool		ForceScreenSizeOverride(bool bState, int wide, int tall) = 0;
	// LocalToScreen, ParentLocalToScreen fixups for explicit PaintTraverse calls on Panels not at 0, 0 position
	virtual bool		ForceScreenPosOffset(bool bState, int x, int y) = 0;
	virtual void		OffsetAbsPos(int& x, int& y) = 0;

	// Causes fonts to get reloaded, etc.
	virtual void		ResetFontCaches() = 0;

	virtual int			GetTextureNumFrames(int id) = 0;
	virtual void		DrawSetTextureFrame(int id, int nFrame, unsigned int* pFrameCache) = 0;
	virtual bool		IsScreenSizeOverrideActive(void) = 0;
	virtual bool		IsScreenPosOverrideActive(void) = 0;

	virtual void		DestroyTextureID(int id) = 0;

	virtual void		DrawUpdateRegionTextureRGBA(int nTextureID, int x, int y, const unsigned char* pchData, int wide, int tall, ImageFormat imageFormat) = 0;

	virtual void		Nothing__17() = 0;

	virtual const char* GetWebkitHTMLUserAgentString() = 0;

	virtual void* AccessChromeHTMLController() = 0;

	// the origin of the viewport on the framebuffer (Which might not be 0,0 for stereo)
	virtual void		SetFullscreenViewport(int x, int y, int w, int h) = 0; // this uses NULL for the render target.
	virtual void		GetFullscreenViewport(int& x, int& y, int& w, int& h) = 0;
	virtual void		PushFullscreenViewport() = 0;
	virtual void		PopFullscreenViewport() = 0;

	// handles support for software cursors
	virtual void		SetSoftwareCursor(bool bUseSoftwareCursor) = 0;
	virtual void		PaintSoftwareCursor() = 0;
};

#endif // ISURFACE_H