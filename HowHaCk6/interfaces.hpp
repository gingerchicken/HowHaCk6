#ifndef INTERFACES_H
#define INTERFACES_H

#include <Windows.h>

typedef void* (*CreateInterfaceFn)(const char* sName, int* iReturnCode);

extern class CHLClient;
extern class IClientEntityList;
extern class CEngineClient;
extern class CLuaShared;

namespace HowHack {
	CHLClient* g_pCHLClient;
	IClientEntityList* g_pEntityList;
	CEngineClient* g_pEngineClient;
	CLuaShared* g_pLuaShared;

	void* GetInterface(const char* sModule, const char* sInterface);
	void SetupInterfaces();
	void LogInterfaces();
	void LogInterface(DWORD dwInterface, const char* sInterfaceName);
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
}

void HowHack::SetupInterfaces() {
	g_pEngineClient = (CEngineClient*)GetInterface("engine.dll", "VEngineClient015");
	g_pCHLClient = (CHLClient*)GetInterface("client.dll", "VClient017");
	g_pEntityList = (IClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
	g_pLuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");
}

#endif