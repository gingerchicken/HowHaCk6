#pragma once
#ifndef PATTERNS_H
#define PATTERNS_H

#include <Windows.h>
#include <psapi.h>

#include <string>
#include <array>
#include <iostream>
#include <string_view>

// credits to osiris for the following
std::array<std::size_t, 256> CreateBadCharactarTable(std::string_view pattern) {
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

const char* FindPattern(const char* szModuleName, std::string_view szPattern) {
	// Get the module handle
	HMODULE hModule = GetModuleHandleA(szModuleName);
	if (!hModule) return NULL;

	// Get the module information
	MODULEINFO oModuleInfo;
	if (!GetModuleInformation(GetCurrentProcess(), hModule, &oModuleInfo, sizeof(oModuleInfo))) return NULL;

	PVOID dwModuleBase = oModuleInfo.lpBaseOfDll;
	std::size_t iModuleSize = oModuleInfo.SizeOfImage;

	// Check that we have the base and size
	if (!dwModuleBase || !iModuleSize) return NULL;

	int iLastIdx = szPattern.length() - 1;
	const char* szStart = static_cast<const char*>(dwModuleBase);
	const char* szEnd = szStart + iModuleSize - szPattern.length();

	const auto szBadCharTable = CreateBadCharactarTable(szPattern);

	while (szStart <= szEnd) {
		int i = iLastIdx;
		while (i >= 0 && (szPattern[i] == '?' || szStart[i] == szPattern[i]))
			i--; // Shorten the search space

		if (i < 0) {
			return szStart;
		}

		szStart += szBadCharTable[static_cast<std::uint8_t>(szStart[iLastIdx])];
	}

	return NULL;
}

char* GetRealFromRelative(char* address, int offset, int instructionSize, bool isRelative) { // Address must be an instruction, not a pointer! And offset = the offset to the bytes you want to retrieve.
#ifdef _WIN64
	isRelative = true;
#endif
	if (!address) return NULL;

	char* instruction = address + offset;
	if (!isRelative) {
		return *(char**)(instruction);
	}

	int relativeAddress = *(int*)(instruction);
	char* realAddress = address + instructionSize + relativeAddress;
	return realAddress;
}

#endif