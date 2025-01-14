#include "stdafx.h"
#include <fstream>

#define BackRingSize 34
//Back Ring Main Page, this is where the current goal of the stage is swapped with back ring, froggy, balloon etc. depending on the character.
//This is also where the race result are checked if the player 1 lose.

int RingCopy = 0; //Backring
char TimeSecCopy = 0;
char TimeMinCopy = 0;
char TimeFrameCopy = 0;
bool GetBackRing = false;

//back ring Model and Display Stuff
Trampoline* Capsule_Load_T = nullptr;
Trampoline* Froggy_Load_T = nullptr;
Trampoline* Froggy_Main_T = nullptr;
Trampoline* Balloon_Load_T = nullptr;
Trampoline* OTarget_T = nullptr;


void BackRingObj_Display(ObjectMaster* obj) {
	if (!MissedFrames) {
		njSetTexture(&GoalRingTextures);
		njPushMatrix(0);
		njTranslateV(nullptr, &obj->Data1->Position);
		njRotateY(nullptr, obj->Data1->Rotation.y);
		njScale(0, obj->Data1->Scale.x, obj->Data1->Scale.x, obj->Data1->Scale.x);
		DrawObject(&object_GoalRing);
		njPopMatrix(1);
	}
}


enum BackRing_Actions {
	BackRing_Init,
	BackRing_Seek,
	BackRing_Setting
};

int __cdecl CheckDynamiteBroken_r(int DynNumber)
{
	int v1; // edi
	EntityData1* data; // esi
	int result; // eax
	int v4; // [esp+10h] [ebp-4h]

	v1 = 0;
	v4 = 0;
	if (!dynamite_num)
	{
		result = 0;
		return result;
	}
	do
	{
		data = dynamiteArray[v1]->Data1;

		if (!data) { //fix nonsense crash when using backring
			break;
		}

		if (DynNumber == (unsigned __int64)data->Scale.x)
		{
			if ((data->Status & 0x100) == 0)
			{
				result = 0;
				return result;
			}
			++v4;
		}
		++v1;
	} while (v1 < (unsigned __int8)dynamite_num);
	if (v4)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

//ran every UNpaused frame
void BackRingObj_Main(ObjectMaster* obj) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* data = obj->Data1;

	switch (data->Action) {
	case BackRing_Init:
		obj->DisplaySub = BackRingObj_Display;
		data->Scale.x = 1;
		data->Action = BackRing_Seek;
		obj->SETData.SETData->Flags = 1; //the object will load only once forever ever
		PlayCustomSound_EntityAndVolume(CommonSound_BackRing, obj, 170, 2.0f, true);
		break;
	case BackRing_Seek:
		if (!IsPlayerInsideSphere_(&obj->Data1->Position, squareroot(obj->SETData.SETData->Distance)))
			return;

		if (IsSpecificPlayerInSphere(&data->Position, BackRingSize + 4, 0)) {
			data->CharIndex = TimeFrames;
			play1->Data1->Status &= ~(Status_Attack | Status_LightDash | Status_Unknown3);
			data->Action = BackRing_Setting;
			PlayVoice_Original(5001); //back ring hit SFX
			DisableControl();
			CharObj2Ptrs[0]->Speed.x = 1;
			CharObj2Ptrs[0]->Speed.z = 1;
			ResetGravity();
		}
		
		data->Rotation.y += 0x180;
		obj->DisplaySub(obj);
		break;
	case BackRing_Setting:
		if (data->Scale.x > 0) {
			data->Scale.x -= 0.06f;
			data->Rotation.y += 0x180;
			obj->DisplaySub(obj);
		}
		else {
			obj->Data1->Position.y += 10;
		}

		if (++data->InvulnerableTime > 70) {

			int color = 0x00000000;
			ScreenFade_Color = *(NJS_COLOR*)&color;
			if (CurrentMission == Mission2_100Rings && Rings < 100 || CurrentMission == Mission3_LostChao)
			{
				EnableControl();
				GetBackRing = true;
				DisablePause();
				RingCopy = Rings;
				TimeSecCopy = TimeSeconds;
				TimeMinCopy = TimeMinutes;
				TimeFrameCopy = TimeFrames;

				SoundManager_Delete2();
				ChaoSpawn = false;
				ResetRestartData();

				if (CurrentStageVersion == TailsVersion || CurrentStageVersion == AmyVersion) {
					GameState = 0xc;

				}
				else if (CurrentStageVersion == GammaVersion)
				{
					CurrentLevel = LevelCopy;
					CurrentAct = ActCopy;
					GameState = 7;
				}
				else
				{		
					GameMode = GameModes_Adventure_Field;
					GameState = 0xB;
				}
			}
			else
			{
				LoadLevelResults();
			}
			UpdateSetDataAndDelete(obj);
		}
		else {
			int color = 0xFFFFFFFF;
			ScreenFade_Color = *(NJS_COLOR*)&color;

			if (data->InvulnerableTime < 120) {
				if (data->InvulnerableTime < 60) {
					data->CharID += 4;
					ScreenFade_Color.argb.a = data->CharID;
				}
				else {
					ScreenFade_Color.argb.a = 0xFF;
				}
			}
			else {
				data->CharID -= 20;
				ScreenFade_Color.argb.a = data->CharID;
			}

			ScreenFade_DrawColor();
		}
		break;
	}		
}
	

//Replace the capsule according to the character and the mission.
void __cdecl CheckLoadCapsule_r(ObjectMaster* a1) {

	if (CurrentStageVersion == GammaVersion && CurrentMission < Mission2_100Rings)
	{
		if (CurrentAct == 2 && (CurrentLevel == LevelIDs_FinalEgg || (CurrentLevel == LevelIDs_HotShelter && CurrentCharacter == Characters_Gamma))) {
			return;
		}
	}

	if (CurrentMission < Mission2_100Rings && CurrentStageVersion != KnucklesVersion)
	{
		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			return;
		case Characters_Big:
			if (CurrentLevel != LevelIDs_SkyDeck)
			{
				a1->Data1->Position.y += 20;
				a1->MainSub = OFrog;
				OFrog(a1);
				return;
			}
			break;
		}
	}


	if (CurrentMission >= Mission2_100Rings)
	{
		a1->Data1->Position.y += 38;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		return;
	}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
		RaceResultCheck(a1);

	//call original function (Capsule.)
	if (CurrentStageVersion != KnucklesVersion && CurrentMission < Mission2_100Rings || CurrentLevel == LevelIDs_LostWorld && CurrentAct == 2) {
		ObjectFunc(origin, Capsule_Load_T->Target());
		origin(a1);
	}
}

void Check_DisplayBackRing_Big(ObjectMaster* a1) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* v1 = a1->Data1;

	if (CurrentMission >= Mission2_100Rings)
	{
		a1->Data1->Position.y += 28;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		return;
	}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
	{
		RaceResultCheck(a1);
		return;
	}
}

void Check_DisplayBackRing_Amy(ObjectMaster* a1) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* v1 = a1->Data1;

	if (CurrentMission >= Mission2_100Rings)
	{

		a1->Data1->Position.y += 0;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;

		return;
	}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
	{
		RaceResultCheck(a1);
		return;
	}
}

void Check_Display_Frog_Balloon(ObjectMaster* a1) {

		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			break;
		case Characters_Big:
			a1->Data1->Position.y += 20;
			a1->MainSub = OFrog;
			OFrog(a1);
			break;
		}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
		RaceResultCheck(a1);
}


void Check_Display_BackRing_Common(ObjectMaster* a1) {

	if (CurrentStageVersion == GammaVersion && (CurrentLevel == LevelIDs_RedMountain || CurrentLevel == LevelIDs_WindyValley || CurrentLevel == LevelIDs_HotShelter))
		a1->Data1->Position.y += 25;
	else
		a1->Data1->Position.y += 36;

	a1->DisplaySub = BackRingObj_Display;
	a1->MainSub = BackRingObj_Main;
}


//Check the current mission and replace Froggy with Back Ring.
void __cdecl CheckLoadFroggy_r(ObjectMaster* a1) {

	Check_DisplayBackRing_Big(a1);

	if (CurrentMission < Mission2_100Rings)
	{
		if (GetCharacter0ID() == Characters_Big && CurrentStageVersion == BigVersion)
		{
			return;
		}

		ObjectFunc(origin, Froggy_Load_T->Target());
		origin(a1);
	}
}

//Check the current mission and replace Froggy with Back Ring.
void __cdecl CheckLoadBig_Froggy_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && GetCharacter0ID() == Characters_Big)
	{
		ObjectFunc(origin, Froggy_Main_T->Target());
		origin(a1);
	}
	else {
		return;
	}
}

//Check the current mission and replace Balloon with Back Ring.
void __cdecl CheckLoadBalloon_r(ObjectMaster* a1) {

	Check_DisplayBackRing_Amy(a1);

	if (CurrentMission < Mission2_100Rings && CurrentStageVersion != KnucklesVersion)
	{
		ObjectFunc(origin, Balloon_Load_T->Target());
		origin(a1);
	}
}

Trampoline CasinoEmerald_Load_T(0x5dd0a0, 0x5dd0a6, CheckLoadCasinoEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadCasinoEmerald_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentMission >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
		RaceResultCheck(a1);

	//call original function (Emerald.)
	if (CurrentStageVersion != KnucklesVersion) {
		ObjectFunc(origin, CasinoEmerald_Load_T.Target());
		origin(a1);
	}
}

Trampoline WVEmerald_Load_T(0x4df3b0, 0x4df3b6, CheckLoadWVEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadWVEmerald_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentMission >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
		RaceResultCheck(a1);

	//call original function (Emerald.)
	ObjectFunc(origin, WVEmerald_Load_T.Target());
	origin(a1);
}

Trampoline ICEmerald_Load_T(0x4ecfa0, 0x4ecfa6, CheckLoadICEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadICEmerald_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentMission >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	if (Race && !isAIActive && CurrentMission < Mission2_100Rings)
		RaceResultCheck(a1);

	//call original function (Emerald.)
	ObjectFunc(origin, ICEmerald_Load_T.Target());
	origin(a1);
}


Trampoline CheckLoadTailsPlaneEC_t(0x4f9fb0, 0x4f9fb6, CheckLoadTailsPlaneEC_r);

void __cdecl CheckLoadTailsPlaneEC_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentMission >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	//call original function
	ObjectFunc(origin, CheckLoadTailsPlaneEC_t.Target());
	origin(a1);
}

Trampoline CheckLWTrigger_t(0x7b0da0, 0x7b0da6, CheckLWTrigger_r);

void __cdecl CheckLWTrigger_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentMission >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	//call original function
	ObjectFunc(origin, CheckLWTrigger_t.Target());
	origin(a1);
}

Trampoline CheckFETrigger_t(0x5b24f0, 0x5b24f6, CheckFETrigger_r);

void __cdecl CheckFETrigger_r(ObjectMaster* a1) {

	if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentMission >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	//call original function
	ObjectFunc(origin, CheckFETrigger_t.Target());
	origin(a1);
}


void OTarget_R(ObjectMaster* obj) { //Sonic Doll Final Egg


	if (CurrentMission < Mission2_100Rings) {
		ObjectFunc(origin, OTarget_T->Target());
		origin(obj);
	}
}

void BackRing_CheckAndApply() {
	if (GetBackRing && CurrentMission >= Mission2_100Rings)
	{
		Rings = RingCopy;
		TimeSeconds = TimeSecCopy;
		TimeMinutes = TimeMinCopy;
		TimeFrames = TimeFrameCopy;
		if (CurrentStageVersion == AmyVersion && CurrentLevel == LevelIDs_FinalEgg || CurrentStageVersion == TailsVersion)
			Lives++;
		ResetRestartData();
		ResetGravity();
		GameMode = GameModes_Adventure_ActionStg;
	}

	return;
}

void Set_BackRing() {

	Capsule_Load_T = new Trampoline((int)Capsule_Load, (int)Capsule_Load + 0x7, CheckLoadCapsule_r);
	Froggy_Load_T = new Trampoline((int)OFrog, (int)OFrog + 0x5, CheckLoadFroggy_r);
	Froggy_Main_T = new Trampoline((int)Froggy_Main, (int)Froggy_Main + 0x5, CheckLoadBig_Froggy_r);
	Balloon_Load_T = new Trampoline((int)Balloon_Main, (int)Balloon_Main + 0x6, CheckLoadBalloon_r);
	OTarget_T = new Trampoline((int)OTarget, (int)OTarget + 0x5, OTarget_R);

	WriteData((ObjectFuncPtr*)0x4FA050, CheckLoadCapsule_r); // crashed plane in Emerald Coast
	WriteData((ObjectFuncPtr*)0x4DF3F0, CheckLoadCapsule_r); // Chaos Emerald in Windy Valley
	WriteData((ObjectFuncPtr*)0x5DD0E0, CheckLoadCapsule_r); // Chaos Emerald in Casinopolis
	WriteData((ObjectFuncPtr*)0x4ECFE0, CheckLoadCapsule_r); // Chaos Emerald in Ice Cap
	WriteData((ObjectFuncPtr*)0x7B0DD3, CheckLoadCapsule_r); // ending of Lost World
	WriteData((ObjectFuncPtr*)0x5B2523, CheckLoadCapsule_r); // ending of Final Egg

	WriteJump(CheckDynamiteBroken, CheckDynamiteBroken_r);
}