#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <cstdio>

namespace HowHack {
	void SetupConsole() {
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

		Log("A wild HowHaCk v6.0.0.0 has appeared!\n\n");
	}
	
	void Log(const char* format, ...) {
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

#endif