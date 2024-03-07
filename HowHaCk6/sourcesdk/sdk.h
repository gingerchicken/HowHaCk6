#ifndef SDK_H
#define SDK_H

#include "tier1/checksum_crc.h"
#include "engine/vmatrix.h"
#include "luashared/CLuaInterface.h"
#include "luashared/CLuaShared.h"
#include "client/CClientEntityList.h"
#include "client/CHLClient.h"
#include "client/ClientModeShared.h"
#include "client/C_BasePlayer.h"
#include "engine/CEngineClient.h"
#include "engine/CVRenderView.h"
#include "client/CInputSystem.h"
#include "engine/CModelRender.h"
#include "engine/CMaterialSystem.h"
#include "client/CViewRender.h"
#include "tier0/Color.h"
#include "tier0/Vector.h"
#include "client/ConVar.h"
#include "client/CUniformRandomStream.h"
#include "engine/CModelInfo.h"
#include "client/CInput.h"
#include "engine/CModelInfo.h"
#include "engine/CIVDebugOverlay.h"
#include "engine/CGameEventManager.h"
#include "vgui/VPanelWrapper.h"
#include "vphysics/CPhysicsSurfaceProps.h"
#include "vguimatsurface/CMatSystemSurface.h"
#include "client/IPrediction.h"
#include "client/IGameMovement.h"
#include "vgui/ISurface.h"
#include "engine/gametrace.h"
#include "mathlib/mathlib.h"

class IDirect3DDevice9;

#endif