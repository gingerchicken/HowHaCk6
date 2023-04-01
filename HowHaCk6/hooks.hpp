#ifndef HOOKS_H
#define HOOKS_H

#include <Windows.h>

#include "gconsole.h"

#include "interfaces.hpp"
#include "vmt.hpp"

namespace HowHack {
	void SetupHooks() {

	}

	void LogHook(DWORD dwHook, const char* sHookName) {
		if (dwHook) {
			HowHack::Log("[+] %s: 0x%X\n", sHookName, dwHook);
		}
		else {
			HowHack::Log("[-] %s: 0x%X\n", sHookName, dwHook);
		}
	}

	void LogHooks() {

	}
}

#endif