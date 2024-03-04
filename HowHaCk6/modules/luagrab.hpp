#pragma once

#ifndef LUAGRAB_H
#define LUAGRAB_H

#include <ShlObj.h>
#include <fstream>
#include <ostream>
#include <algorithm>

#include "../interfaces.hpp"
#include "../gconsole.h"
#include "module.hpp"

namespace HowHack {
	class CheatLuaGrab : public Module {
	public:
		static std::string GetLuaSavePath() {
			// TODO read a config or something
			return std::string("C:\\HowHack-Lua");
		}

		static std::string GetServerName() {
			std::string szName = "unconnected";

			// Get the net channel
			CNetChan* pNetChan = g_pEngineClient->GetNetChannelInfo();
			if (!pNetChan) return szName;

			// Get the address
			const char* szAddr = pNetChan->GetAddress();
			if (!szAddr) return szName;
			
			// Create a string from the char*
			szName = std::string(szAddr);

			// Remove the port
			szName = szName.substr(0, szName.find(":"));
			
			// Return it
			return szName;
		}

		void SaveLuaFile(CLuaInterface* pLua, const char* szFilename, const char* szPath, const char* szStringToRun, bool bRun, bool bPrintErrors, bool bDontPushErrors, bool bNoReturns) {
			if (!m_bEnable) return;
			
			std::string szRoot = GetLuaSavePath() + "\\" + GetServerName();

			// Create the directory recursively
			SHCreateDirectoryEx(NULL, std::wstring(szRoot.begin(), szRoot.end()).c_str(), NULL);

			// Create the file
			std::string szFile = szRoot + "\\" + szFilename;

			// Replace all / with \ because Windows is stupid
			std::replace(szFile.begin(), szFile.end(), '/', '\\');

			// The filename will include sub-directories, so we need to create them
			std::string szDir = szFile.substr(0, szFile.find_last_of("\\/"));

			Log("creating directory %s\n", szDir.c_str());

			// Create the directory recursively
			SHCreateDirectoryEx(NULL, std::wstring(szDir.begin(), szDir.end()).c_str(), NULL);

			// Open the file
			std::ofstream oFile(szFile.c_str());

			// Write the file
			oFile << szStringToRun;

			// Close the file
			oFile.close();
		}
	};

	CheatLuaGrab oLuaGrab;
}

#endif