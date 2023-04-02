#ifndef ESP_H
#define ESP_H

#include "../interfaces.hpp"
#include "../drawutil.hpp"
#include "../sourcesdk/sdk.h"

namespace HowHack {

	// TODO make this a singleton
	class CheatESP {
	public:
		static void DrawBoundingBox(C_BasePlayer* pPlayer) {
			CCollisionProperty* pCollision = pPlayer->GetCollideable();

			// Get the absolute origin
			Vector vOrigin = pPlayer->GetAbsOrigin();

			// TODO clean this up to make it more readable
			Vector vCollMid = Vector(pPlayer->GetCollideable()->OBBMins().x + pPlayer->GetCollideable()->OBBMaxs().x, pPlayer->GetCollideable()->OBBMins().y + pPlayer->GetCollideable()->OBBMaxs().y, pPlayer->GetCollideable()->OBBMins().z);

			// Get the world bounds
			Vector vMins;
			Vector vMaxs;
			pCollision->WorldSpaceTriggerBounds(&vMins, &vMaxs);

			// Convert them to screen positions
			Vector vTop, vBottom;
			if (!HowHack::WorldToScreen(vCollMid + vMaxs, vTop) || !HowHack::WorldToScreen(vCollMid + vMins, vBottom)) return;

			HowHack::DrawString("Top", 16, vTop.x, vTop.y);
			HowHack::DrawString("Bottom", 16, vBottom.x, vBottom.y);
		}

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

				// Draw the bounding box
				DrawBoundingBox(pPlayer);
			}	
		}
	};
}

#endif // !ESP_H