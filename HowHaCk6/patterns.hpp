#pragma once
#ifndef PATTERNS_H
#define PATTERNS_H

#include <Windows.h>
#include <psapi.h>

#include <string>
#include <string_view>

// credits to osiris for the following
auto CreateBadCharactarTable(std::string_view pattern) {
	std::array<std::size_t, 256> table;

	auto lastWildcard = pattern.rfind('?');
	if (lastWildcard == std::string_view::npos)
		lastWildcard = 0;

	const auto defaultShift = (std::max)(std::size_t(1), pattern.length() - 1 - lastWildcard);
	table.fill(defaultShift);

	for (auto i = lastWildcard; i < pattern.length() - 1; ++i)
		table[static_cast<std::uint8_t>(pattern[i])] = pattern.length() - 1 - i;

	return table;
}

bool FindPattern(const char* szModuleName, std::string_view szPattern, const char* &szBuffer) {
	// Get the module handle
	HMODULE hModule = GetModuleHandleA(szModuleName);
	if (!hModule) return false;

	// Get the module information
	MODULEINFO oModuleInfo;
	if (!GetModuleInformation(GetCurrentProcess(), hModule, &oModuleInfo, sizeof(oModuleInfo))) return false;

	PVOID dwModuleBase = oModuleInfo.lpBaseOfDll;
	std::size_t iModuleSize = oModuleInfo.SizeOfImage;

	// Check that we have the base and size
	if (!dwModuleBase || !iModuleSize) return false;

	int iLastIdx = szPattern.length() - 1;
	const char* szStart = static_cast<const char*>(dwModuleBase);
	const char* szEnd = szStart + iModuleSize - szPattern.length();

	const auto szBadCharTable = CreateBadCharactarTable(szPattern);

	while (szStart <= szEnd) {
		int i = iLastIdx;
		while (i >= 0 && (szPattern[i] == '?' || szStart[i] == szPattern[i]))
			i--; // Shorten the search space

		if (i < 0) {
			szBuffer = szStart; // This seems problematic, I am not sure if it is copying.
			return true;
		}

		szStart += szBadCharTable[static_cast<std::uint8_t>(szStart[iLastIdx])];
	}

	return false;
}

#endif