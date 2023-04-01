#include "gconsole.h"

void HowHack::Log(const char* format, ...) {
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void HowHack::SetupConsole() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	// Set the title
	SetConsoleTitleA("HowHaCk v6");

	Log("A wild HowHaCk v6 has appeared!\n\n");
}

void HowHack::LogHook(DWORD dwHook, const char* sHookName) {
	if (dwHook) {
		HowHack::Log("[+] %s: 0x%X\n", sHookName, dwHook);
	}
	else {
		HowHack::Log("[-] %s: 0x%X\n", sHookName, dwHook);
	}
}