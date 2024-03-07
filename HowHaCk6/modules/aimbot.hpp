#pragma once
#ifndef AIMBOT_H
#define AIMBOT_H

#include "../sourcesdk/sdk.h"
#include "../interfaces.hpp"
#include "module.hpp"

#include "../mathutil.hpp"
#include "../drawutil.hpp"

#define BONE_HEAD "ValveBiped.Bip01_Head1"
#define BONE_CHEST "ValveBiped.Bip01_Spine2"
#define BONE_STOMACH "ValveBiped.Bip01_Pelvis"

namespace HowHack {
	class Aimbot : public Module {
	private:
		mstudiobone_t* GetBoneIndexByName(studiohdr_t* pStudioHdr, char const* pName, int* outIndex = NULL) {
			int start = 0, end = pStudioHdr->numbones - 1;
			const BYTE* pBoneTable = pStudioHdr->GetBoneTableSortedByName();
			mstudiobone_t* pbones = pStudioHdr->pBone(0);

			while (start <= end)
			{
				int mid = (start + end) >> 1;
				const char* boneName = pbones[pBoneTable[mid]].pszName();
				int cmp = strcmp(boneName, pName);

				if (cmp < 0)
				{
					start = mid + 1;
				}
				else if (cmp > 0)
				{
					end = mid - 1;
				}
				else
				{
					if (outIndex != NULL)
						*outIndex = pBoneTable[mid];

					return pStudioHdr->pBone(pBoneTable[mid]);
				}
			}
			return nullptr;
		}

		bool CanHit(C_BasePlayer* pTarget, Vector vTo) {
			if (!GetLocalPlayer() || !GetLocalPlayer()->GetActiveWeapon())
				return false;

			trace_t oTrace;
			CTraceFilter oFilter;
			oFilter.pSkip = GetLocalPlayer();
			Ray_t oRay;

			Vector vFrom = GetLocalPlayer()->EyePosition();
			oRay.Init(vFrom, vTo);
			g_pEngineTrace->TraceRay(oRay, MASK_SHOT, &oFilter, &oTrace);

			return (oTrace.m_pEnt == pTarget || oTrace.fraction >= 0.98f); // TODO this is brokey
		}

		bool GetPosition(C_BasePlayer* pTarget, Vector& vOut) {
#ifdef UNSAFE_AIMBOT
			// Handle no model
			model_t* pModel = (model_t*)(pTarget->GetClientRenderable()->GetModel());
			if (!pModel) return false;

			studiohdr_t* pStudio = g_pModelInfo->GetStudiomodel(pModel);
			if (!pStudio) return false;

			if (pModel && _strcmpi(pStudio->name, "error.mdl") == 0) {
				vOut = pTarget->EyePosition();
				return true;
			}

			matrix3x4_t pBones[128];
			if (!pTarget->GetClientRenderable()->SetupBones(pBones, 128, BONE_USED_BY_HITBOX, g_pGlobalVarsBase->curtime))
				return false;


			int iSelectedHitbox = 0;

			// TODO why dont we use the pBone instead of getting all the bones
			mstudiobone_t* pBone = GetBoneIndexByName(pStudio, BONE_HEAD, &iSelectedHitbox);
			if (!pBone) return false;

			vOut.x = pBones[iSelectedHitbox][0][m_iTargetBone];
			vOut.y = pBones[iSelectedHitbox][1][m_iTargetBone];
			vOut.z = pBones[iSelectedHitbox][2][m_iTargetBone];

			return true;
#else
			vOut = pTarget->EyePosition();
			return true;
#endif
		}

		bool GetDistance(Vector vPos, float* fOut) {
			Vector vPosOut = Vector(0, 0, 0);

			if (!WorldToScreen(vPos, vPosOut)) return false;

			vPosOut.z = 0;

			int iWidth, iHeight;
			HowHack::g_pEngineClient->GetScreenSize(iWidth, iHeight);

			*fOut = Vector(iWidth / 2, iHeight / 2, 0).DistTo(vPosOut);

			return true;
		}

		void SetAngle(CUserCmd* pCmd, QAngle oAngle) {
			// TODO smoothing?

			if (!m_bSilent) {
				g_pEngineClient->SetViewAngles(oAngle);
				return;
			}

			pCmd->viewangles = oAngle;
		}

		void AimAtPosition(CUserCmd* pCmd, C_BasePlayer* pTarget, Vector vPos) {
			Vector vPredicted = pTarget->getVelocity() * g_pGlobalVarsBase->frametime * g_pGlobalVarsBase->interval_per_tick - GetLocalPlayer()->getVelocity() * g_pGlobalVarsBase->interval_per_tick;

			QAngle oAimAngles = (vPos - GetLocalPlayer()->EyePosition() + vPredicted).toAngle();

			// Hard snap
			SetAngle(pCmd, oAimAngles);
		}
	public:
		bool m_bFlip = false;
		bool m_bSilent = true;
		int m_iTargetBone = 3; // chest

		bool AfterCreateMove(CUserCmd* pCmd) {
			if (!this->m_bEnable) return false;

			C_BasePlayer* pLocalPlayer = GetLocalPlayer();
			if (!pLocalPlayer || !pCmd || !pLocalPlayer->IsAlive())
				return false;

			Vector2D vAngles(
				AngleNormalizePositive(pCmd->viewangles.x),
				AngleNormalizePositive(pCmd->viewangles.y)
			);

			bool bFound = false;
			C_BasePlayer* pTarget = nullptr;
			float fBestDistance = INFINITY;
			Vector vBestPos(0, 0, 0);
			for (int i = 1; i <= g_pEntityList->GetHighestEntityIndex(); i++) {
				C_BaseEntity* pEntity = (C_BaseEntity*)(g_pEntityList->GetClientEntity(i));
				if (!pEntity) continue;

				// Get the player's name (and check if it is a player)
				player_info_t oInfo;
				if (!g_pEngineClient->GetPlayerInfo(i, &oInfo)) continue;

				// Get the player
				C_BasePlayer* pPlayer = (C_BasePlayer*)pEntity;
			
				// Check if the player is us
				if (pPlayer == pLocalPlayer) continue;

				// Check if the player is dormant
				if (pPlayer->IsDormant()) continue;

				// Check if the player is alive
				if (!pPlayer->IsAlive()) continue;

				// Get the position
				Vector vPos;
				if (!this->GetPosition(pPlayer, vPos)) continue;

				// Check that they're visible
				if (!CanHit(pPlayer, vPos)) continue;

				// Get distance
				float fCurrentDistance = INFINITY;
				if (!GetDistance(vPos, &fCurrentDistance)) continue;

				// Check if the distance is less than the best distance
				if (fCurrentDistance >= fBestDistance) continue;

				// Set that the position was found
				bFound = true;

				// Copy the position
				vBestPos.x = vPos.x;
				vBestPos.y = vPos.y;
				vBestPos.z = vPos.z;

				// Set the distance
				fBestDistance = fCurrentDistance;

				pTarget = pPlayer;
			}

			// Check that a position was found
			if (!bFound) return false;

			// TODO fov?

			// Aim at the position
			AimAtPosition(pCmd, pTarget, vBestPos);

			return true;
		}
	};

	Aimbot oAimbot;
}

#endif