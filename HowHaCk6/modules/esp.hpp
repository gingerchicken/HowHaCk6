#ifndef ESP_H
#define ESP_H

#include <algorithm>

#include "../interfaces.hpp"
#include "../drawutil.hpp"
#include "../sourcesdk/sdk.h"

namespace HowHack {

	// TODO make this a singleton
	class CheatESP {
	public:
		static void DrawBoundingBox(C_BasePlayer* pPlayer, bool bBox = true, bool bFill = true) {
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

			float aX[] = { vTop.x, vBottom.x };
			float aY[] = { vTop.y, vBottom.y };

			// Sort the arrays
			std::sort(aX, aX + 2);
			std::sort(aY, aY + 2);

			// Create the vectors
			Vector vTopLeft = Vector(aX[0], aY[0], 0);
			Vector vBottomRight = Vector(aX[1], aY[1], 0);

			// Draw the box
			const Color oBoxColor(255, 255, 255, 255);
			const Color oBoxInnerColor(255, 0, 0, 50);
			
			// Calculate width and height
			int iWidth = vBottomRight.x - vTopLeft.x;
			int iHeight = vBottomRight.y - vTopLeft.y;

			if (bFill) DrawRect(vTopLeft.x, vTopLeft.y, iWidth, iHeight, oBoxInnerColor);

			if (bBox) {
				// Draw the lines
				DrawLine(vTopLeft.x, vTopLeft.y, vBottomRight.x, vTopLeft.y, oBoxColor);
				DrawLine(vTopLeft.x, vTopLeft.y, vTopLeft.x, vBottomRight.y, oBoxColor);
				DrawLine(vBottomRight.x, vTopLeft.y, vBottomRight.x, vBottomRight.y, oBoxColor);
				DrawLine(vTopLeft.x, vBottomRight.y, vBottomRight.x, vBottomRight.y, oBoxColor);
			}

#ifdef _DEBUG
			DrawString("TopL", 16, vTopLeft.x, vTopLeft.y);
			DrawString("TopR", 16, vBottomRight.x, vTopLeft.y);
			DrawString("BotL", 16, vTopLeft.x, vBottomRight.y);
			DrawString("BotR", 16, vBottomRight.x, vBottomRight.y);
#endif
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