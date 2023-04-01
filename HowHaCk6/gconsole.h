#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <cstdio>

namespace HowHack {
	void SetupConsole();
	void Log(const char* format, ...);
}

#endif