#ifndef ESP_H
#define ESP_H

#include "../interfaces.hpp"
#include "../drawutil.hpp"
#include "../sourcesdk/sdk.h"

namespace HowHack {
	class CheatESP {
	public:
		static void DrawESP() {
			// Ensure we are in game
			if (!g_pEngineClient->IsInGame()) return;

			// Get local player
			C_BasePlayer* pLocalPlayer = (C_BasePlayer*)g_pEntityList->GetClientEntity(g_pEngineClient->GetLocalPlayer());
			if (!pLocalPlayer) return;

			// Get the other players
			for (int i = 0; i < g_pEntityList->GetHighestEntityIndex(); i++) {
				C_BaseEntity* pEntity = (C_BaseEntity*)g_pEntityList->GetClientEntity(i);
				if (!pEntity) continue;

				// Get the player's name (and check if it is a player)
				player_info_t pInfo;
				if (!g_pEngineClient->GetPlayerInfo(i, &pInfo)) continue;

				// Get the player
				C_BasePlayer* pPlayer = (C_BasePlayer*)pEntity;

				// Get the player's health
				int iHealth = pPlayer->GetHealth();
				// Get the player's position
				Vector vOrigin = pPlayer->EyePosition();
				Vector vScreen; // TODO change this to Vector2D once you have implemented the functions
				if (!HowHack::WorldToScreen(vOrigin, vScreen)) continue;
				
				// Draw the player's name
				HowHack::DrawString(pInfo.name, 16, vScreen.x, vScreen.y);
				// Draw the player's health
				HowHack::DrawString(std::to_string(iHealth).c_str(), 16, vScreen.x, vScreen.y + 16);
			}	
		}
	};
}

#endif // !ESP_H