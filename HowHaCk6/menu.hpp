#pragma once
#ifndef MENU_H
#define MENU_H

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dtypes.h>
#include <dcommon.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx9.h"
#include "imgui/backends/imgui_impl_win32.h"

#include "interfaces.hpp"

#define MENU_KEY KEY_INSERT
#define DRAWING_FONT_SIZE 11

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace HowHack {
	bool bOpenMenu = true;
	WNDPROC oWndProc;

	void InitaliseMenu(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	void PresentMenu(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);

	int iScreenWidth, iScreenHeight;
	HWND hWindow;
	ID3DXLine* pLine;
	ID3DXFont* pFont;
	IDirect3DDevice9* pDevice;
	ImGuiStyle* pStyle;

	ImFont* pFontMenu;
	ImGuiIO* oIO;
}

void BuildMenu() {
	// ESP
	if (ImGui::Checkbox("ESP", &HowHack::oESP.m_bEnable)) {
		// TODO more settings
	}

	ImGui::Checkbox("Lua Grab", &HowHack::oLuaGrab.m_bEnable);

	ImGui::Checkbox("Bunny Hop", &HowHack::oBhop.m_bEnable);
}

void MenuKeyHandle(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static bool lastState = false;
	if (wParam == HowHack::g_pInputSystem->ButtonCodeToVirtualKey(MENU_KEY))
	{
		if (uMsg == WM_KEYDOWN && lastState == false) {
			lastState = true;
			HowHack::bOpenMenu = !HowHack::bOpenMenu;
		}
		else if (uMsg == WM_KEYUP)
		{
			lastState = false;
		}
	}
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MenuKeyHandle(hWnd, uMsg, wParam, lParam);
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	return CallWindowProcA(HowHack::oWndProc, hWnd, uMsg, wParam, lParam);
}

void HowHack::InitaliseMenu(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {
	static bool bInit = false;
	if (bInit) return;

	// Mark as initalised
	bInit = true;

	HowHack::g_pEngineClient->GetScreenSize(iScreenWidth, iScreenHeight);
	D3DXCreateLine(pDevice, &pLine);
	D3DXCreateFont(pDevice, DRAWING_FONT_SIZE, NULL, FW_HEAVY, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (L"Tahoma"), &pFont);
	HowHack::pDevice = pDevice;

	ImGui::CreateContext();

	HowHack::hWindow = FindWindowA("Valve001", nullptr);
	HowHack::oWndProc = (WNDPROC)SetWindowLongPtrW(HowHack::hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

	// TODO fix variable names
	IDirect3DSwapChain9* pChain = nullptr;
	D3DPRESENT_PARAMETERS pp = {};
	D3DDEVICE_CREATION_PARAMETERS param = {};
	pDevice->GetCreationParameters(&param);
	pDevice->GetSwapChain(0, &pChain);
	if (pChain)
		pChain->GetPresentParameters(&pp);

	ImGui_ImplWin32_Init(HowHack::hWindow);
	ImGui_ImplDX9_Init(HowHack::pDevice);

	pStyle = &ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
}

void HowHack::PresentMenu(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {	
	InitaliseMenu(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	HowHack::g_pInputSystem->EnableInput(!bOpenMenu);
	HowHack::g_pISurface->SetCursorAlwaysVisible(bOpenMenu);

	ITexture* rt = nullptr;
	auto context = HowHack::g_pMaterialSystem->GetRenderContext();
	if (context) {
		context->BeginRender();
		rt = context->GetRenderTarget();
		context->SetRenderTarget(nullptr);
		context->EndRender();
	}

	// Low-key yoinked from https://github.com/Gaztoof/GMod-SDK/blob/a65eedc7dad8ab2c20b87a110c8cfeafaba853f7/GMod-SDK/hooks/Present.h#L155
	// https://www.unknowncheatsme/forum/3137288-post2.html Thanks to him :)
	// If you don't do that, the color of the menu will match to V

	DWORD dwColourWhite, dwRGBWrite;
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwColourWhite);
	pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &dwRGBWrite);

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

	// Get the vertex declaration and shader
	IDirect3DVertexDeclaration9* pVertexDeclaration;
	IDirect3DVertexShader9* pVertexShader;

	pDevice->GetVertexDeclaration(&pVertexDeclaration);
	pDevice->GetVertexShader(&pVertexShader);

	ImGui::GetIO().MouseDrawCursor = HowHack::bOpenMenu;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (bOpenMenu) {
		if (ImGui::Begin("HowHaCk V6 :: Menu", &bOpenMenu)) {
			BuildMenu();
		}
		ImGui::End();
	}


	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwColourWhite);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, dwRGBWrite);
	pDevice->SetVertexDeclaration(pVertexDeclaration);
	pDevice->SetVertexShader(pVertexShader);

	if (rt) {
		if (context = HowHack::g_pMaterialSystem->GetRenderContext()) {
			context->BeginRender();
			context->SetRenderTarget(rt);
			context->EndRender();
		}
	}
}

#endif