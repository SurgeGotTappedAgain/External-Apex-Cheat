#pragma once

//#define OFFSET_RAN 0//0x34LLU
// you dont have to use toffset, i also dont and it works as expected
#define TOFFSET(d1) d1 //((d1)+offset_ran_var)

extern unsigned long long offset_ran_var;

#define ENTITY_SIZE_DEF				0x42E0		    //biggest entity offset //0x42E0

#define OFFSET_ENTITYLIST		    0x18DA338		//cl_entitylist
#define OFFSET_LOCAL_ENT			0x1C898F8		//LocalPlayer

#define OFFSET_TEAM					0x0450			//m_iTeamNum
#define OFFSET_HEALTH				0x0440			//m_iHealth
#define OFFSET_NAME					0x0589			//m_iName
#define OFFSET_SIG_NAME				0x0580			//m_iSignifierName
#define OFFSET_SHIELD				0x0170			//m_shieldHealth
#define OFFSET_MAX_SHIELD			0x0174			//m_shieldHealth +0x4
#define OFFSET_VISIBLE_TIME         0x1A4C          //m_visibletime

#define OFFSET_MODELNAME			0x30

#define OFFSET_NAMELIST				0x81330F0

#define OFFSET_LIFE_STATE			0x0798			//m_lifeState
#define OFFSET_BLEED_OUT_STATE		0x25E8			//m_bleedoutState

#define OFFSET_ITEM_ID				0x1618			//m_customScriptInt

#define OFFSET_BULLET_SPEED			0x1E50			//m_flProjectileSpeed
#define OFFSET_BULLET_GRAVITY		0x1E58			//m_flProjectileScale

#define OFFSET_CURRENT_WEAPON		0x19EC			//m_latestPrimaryWeapons
#define OFFSET_ORIGIN				0x14C			//m_vecAbsOrigin
#define OFFSET_BONES				0xF38			//m_nForceBone + 0x50 - 0x8 -> 48 8B 97 ?? ?? ?? ?? 48 8D 04 5B 48 C1
#define OFFSET_AIMPUNCH				0x2390			//m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS			0x1E30		// Search CameraPos, first movss at bottom
#define OFFSET_VIEWANGLES			0x2478			//m_ammoPoolCapacity - 0x14  -> 0F 57 C0 8B 86 ?? ?? ?? ?? F3
#define OFFSET_BREATH_ANGLES		(OFFSET_VIEWANGLES - 0x10)
#define OFFSET_OBSERVER_MODE		0x32A4			//m_iObserverMode
#define OFFSET_OBSERVING_TARGET		0x32A8			//m_hObserverTarget

#define OFFSET_HELMET_TYPE			0x4374			//m_helmetType

#define GLOW_CONTEXT 0x3C8 //Script_Highlight_SetCurrentContext
#define GLOW_LIFE_TIME 0x3A4 //Script_Highlight_SetLifeTime + 4
#define GLOW_DISTANCE 0x3B4 //Script_Highlight_SetFarFadeDist
#define GLOW_TYPE 0x2C4 //Script_Highlight_GetState + 4
#define GLOW_COLOR 0x1D0 //Script_CopyHighlightState 15th mov
#define GLOW_VISIBLE_TYPE 0x3D0 //Script_Highlight_SetVisibilityType 5th mov
#define GLOW_FADE 0x388 //Script_Highlight_GetCurrentInsideOpacity 3rd result of 3 offsets consecutive or first + 8

#define OFFSET_MATRIX				0x001B3BD0		//ViewMatrix
#define OFFSET_RENDER				0x408B768 	 	//ViewRender