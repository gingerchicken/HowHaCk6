#ifndef INTERFACES_H
#define INTERFACES_H

#include <Windows.h>

#include "sourcesdk/sdk.h"
#include "offsets.h"
#include "vmt.hpp"
#include "patterns.hpp"

typedef void* (*CreateInterfaceFn)(const char* sName, int* iReturnCode);

namespace HowHack {
	CHLClient* g_pCHLClient;
	CClientEntityList* g_pEntityList;
	CEngineClient* g_pEngineClient;
	CLuaShared* g_pLuaShared;
	CLuaInterface* g_pLuaInterface;
	VPanelWrapper* g_pVPanelWrapper;
	ISurface* g_pISurface;
	ClientModeShared* g_pClientMode;
	
	void UpdateLuaInterface(CLuaInterface* pLuaInterface);
	void* GetInterface(const char* sModule, const char* sInterface);
	void SetupInterfaces();
	void LogInterfaces();
	void LogInterface(DWORD dwInterface, const char* sInterfaceName);
	C_BasePlayer* GetLocalPlayer();
}

// AH HHAHAH HMEN S GHEHGEH
void* HowHack::GetInterface(const char* sModule, const char* sInterfaceName) {
	CreateInterfaceFn pInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(sModule), "CreateInterface");

	return (void*)pInterface(sInterfaceName, NULL);
}

void HowHack::LogInterface(DWORD dwInterface, const char* sInterfaceName) {
	if (dwInterface) {
		HowHack::Log("[+] %s: 0x%X\n", sInterfaceName, dwInterface);
	}
	else {
		HowHack::Log("[-] %s: 0x%X\n", sInterfaceName, dwInterface);
	}
}

void HowHack::LogInterfaces() {
	HowHack::LogInterface((DWORD)g_pCHLClient, "CHLClient");
	HowHack::LogInterface((DWORD)g_pEntityList, "IClientEntityList");
	HowHack::LogInterface((DWORD)g_pEngineClient, "CEngineClient");
	HowHack::LogInterface((DWORD)g_pLuaShared, "CLuaShared");
	HowHack::LogInterface((DWORD)g_pLuaInterface, "LuaInterface");
	HowHack::LogInterface((DWORD)g_pVPanelWrapper, "VPanelWrapper");
	HowHack::LogInterface((DWORD)g_pISurface, "ISurface");
	HowHack::LogInterface((DWORD)g_pClientMode, "ClientModeShared");
}

void HowHack::SetupInterfaces() {
	// Direct
	g_pEngineClient = (CEngineClient*)GetInterface("engine.dll", "VEngineClient015");
	g_pCHLClient = (CHLClient*)GetInterface("client.dll", "VClient017");
	g_pEntityList = (CClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
	g_pLuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");
	g_pVPanelWrapper = (VPanelWrapper*)GetInterface("vgui2.dll", "VGUI_Panel009");
	g_pISurface = (ISurface*)GetInterface("vguimatsurface.dll", "VGUI_Surface030"); // TODO what about steam overlay?
	
	// Offset'd
	g_pClientMode = GetVMT<ClientModeShared>((DWORD)g_pCHLClient, 10, OFFSET_CLIENT_MODE);
}

C_BasePlayer* HowHack::GetLocalPlayer() {
	return (C_BasePlayer*)g_pEntityList->GetClientEntity(g_pEngineClient->GetLocalPlayer());
}

void HowHack::UpdateLuaInterface(CLuaInterface* pLuaInterface) {
	Log("[+] Updating Lua Interface: 0x%X -> 0x%X\n", g_pLuaInterface, pLuaInterface);
	
	g_pLuaInterface = pLuaInterface;
}

#endif