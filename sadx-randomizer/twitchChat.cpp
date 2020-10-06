#include "stdafx.h"

int FastTimer = 0;

bool isVsChatPossible() {
	if (!CharObj2Ptrs[0] || !vsChat || GameState != 15 || CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2 || CurrentLevel >= LevelIDs_SSGarden)
		return false;

	return true;
}

void adjustObjectPosition(ObjectMaster* obj) {
	if (!isVsChatPossible())
		return;

	EntityData1* data = obj->Data1;
	if (CharObj2Ptrs[0]->Speed.x >= 3 || CharObj2Ptrs[0]->Speed.z >= 3)
		data->Position = UnitMatrix_GetPoint(&EntityData1Ptrs[0]->Position, &data->Rotation, 0.0f, 0.0f, 35.0f);
	else
		data->Position = EntityData1Ptrs[0]->Position;
}

extern "C" {

	__declspec(dllexport) void SpawnSpring() {
		if (!isVsChatPossible())
			return;


		ObjectMaster* spring = LoadObject((LoadObj)2, 2, SpringB_Main);
		spring->Data1->Rotation = { rand() % 0x8000, rand() % 0x8000, rand() % 0x8000 };
		spring->Data1->Scale.y = rand() % 4 + 1 * 2.5;		
		adjustObjectPosition(spring);

		return;
	}

	__declspec(dllexport) void SpawnSpeedPad() {
		if (!isVsChatPossible())
			return;


		ObjectMaster* speed = LoadObject((LoadObj)3, 3, DashPanel_Main);
		speed->Data1->Scale.x = rand() % 5 + 10 * 2.5;
		speed->Data1->Rotation.y = rand() % 0x8000;
		adjustObjectPosition(speed);


		return;
	}

	__declspec(dllexport) void SpawnSpikeBall() {
		if (!isVsChatPossible())
			return;


		ObjectMaster* spike = LoadObject((LoadObj)6, 3, SwingSpikeBall_Load);
		spike->Data1->Rotation.y = rand() % 80 + 1000;
		spike->Data1->Scale.x = rand() % 5 + 8 * 1.5;
		adjustObjectPosition(spike);
		spike->Data1->Position.y += 2;
		spike->Data1->Position.x += 80;
		return;
	}

	__declspec(dllexport) void StopPlayer() {
		if (!isVsChatPossible())
			return;
		CharObj2Ptrs[0]->Speed = { 0, 0, 0 };
		return;
	}

	__declspec(dllexport) void SuperJump() {
		if (!isVsChatPossible())
			return;
		CharObj2Ptrs[0]->Speed.y = CharObj2Ptrs[0]->PhysicsData.VSpeedCap;
		return;
	}

	__declspec(dllexport) void GottaGoFast() {
		if (!isVsChatPossible())
			return;
		FastTimer = 120;
		return;
	}


	__declspec(dllexport) void HurtPlayer() {
		if (!isVsChatPossible())
			return;
		if (Rings > 0)
			return HurtCharacter(0);
	}

	__declspec(dllexport) void GivePowerUP(int id) {
		if (!isVsChatPossible())
			return;

		if (id < 0 || id > 8) //failsafe
			id = rand() % 9;

		if (!id)
			GiveSpeedShoes(EntityData1Ptrs[0]); //fix funny crash
		else
			ItemBoxPowerups[id].Function(EntityData1Ptrs[0]);

		DoThingWithItemBoxPowerupIndex(id);
	}

	__declspec(dllexport) void GrowCharacter() {
		if (!isVsChatPossible())
			return;

		bool isCharacterSmall = false;

		if (SONIC_OBJECTS[0]->scl[0] < 1 || MILES_OBJECTS[0]->scl[0] < 1 || KNUCKLES_OBJECTS[0]->scl[0] < 1 || AMY_OBJECTS[0]->scl[0] < 1 || E102_OBJECTS[0]->scl[0] < 1 || BIG_OBJECTS[0]->scl[0] < 1)
			isCharacterSmall = true;


		for (int i = 0; i < 3; i++) {

			switch (EntityData1Ptrs[0]->CharID)
			{
			case Characters_Sonic:
			default:
				if (isCharacterSmall) //bring normal size
				{
					SONIC_OBJECTS[0]->scl[i] = 1;
					SONIC_OBJECTS[44]->scl[i] = 1;
					SONIC_OBJECTS[67]->scl[i] = 1;
					SONIC_OBJECTS[70]->scl[i] = 1;
					CharObj2Ptrs[0]->PhysicsData.YOff = 5.40000010;
				}
				else {
					SONIC_OBJECTS[0]->scl[i] = 4;
					SONIC_OBJECTS[44]->scl[i] = 4;
					SONIC_OBJECTS[67]->scl[i] = 4;
					SONIC_OBJECTS[68]->scl[i] = 4;
					SONIC_OBJECTS[70]->scl[i] = 4; //Metal Sonic
					CharObj2Ptrs[0]->PhysicsData.YOff = 18.50000000;
				}
				break;
			case Characters_Eggman:

				break;
			case Characters_Tails:
				if (isCharacterSmall) //bring normal size
				{
					MILES_OBJECTS[0]->scl[i] = 1;
					MILES_OBJECTS[1]->scl[i] = 1;
					MILES_OBJECTS[3]->scl[i] = 1;
					CharObj2Ptrs[0]->PhysicsData.YOff = 4.50000000;
				}
				else {
					MILES_OBJECTS[0]->scl[i] = 4;
					MILES_OBJECTS[1]->scl[i] = 4;
					MILES_OBJECTS[3]->scl[i] = 4;
					CharObj2Ptrs[0]->PhysicsData.YOff = 4.50000000;
				}
				break;
			case Characters_Tikal:
				break;
			case Characters_Knuckles:
				if (isCharacterSmall) //bring normal size
				{
					KNUCKLES_OBJECTS[0]->scl[i] = 1;
					KNUCKLES_OBJECTS[1]->scl[i] = 1;
					CharObj2Ptrs[0]->PhysicsData.YOff = 4.50000000;
				}
				else {
					KNUCKLES_OBJECTS[0]->scl[i] = 4;
					KNUCKLES_OBJECTS[1]->scl[i] = 4;
					CharObj2Ptrs[0]->PhysicsData.YOff = 18.50000000;
				}
				break;
			case Characters_Amy:
				if (isCharacterSmall) { //bring normal size
					AMY_OBJECTS[0]->scl[i] = 1;
					CharObj2Ptrs[0]->PhysicsData.YOff = 5.00000000;
				}
				else {
					AMY_OBJECTS[0]->scl[i] = 4;
					CharObj2Ptrs[0]->PhysicsData.YOff = 18.50000000;
				}
				
				break;
			case Characters_Gamma:
				if (isCharacterSmall) //bring normal size
				{
					E102_OBJECTS[0]->scl[i] = 1;
					E102_OBJECTS[1]->scl[i] = 1;
					CharObj2Ptrs[0]->PhysicsData.YOff = 4.50000000;
				}
				else {
					E102_OBJECTS[0]->scl[i] = 4;
					E102_OBJECTS[1]->scl[i] = 4;
					CharObj2Ptrs[0]->PhysicsData.YOff = 18.50000000;
				}
				break;
			case Characters_Big:
				if (isCharacterSmall) //bring normal size
				{
					BIG_OBJECTS[0]->scl[i] = 1;
					BIG_OBJECTS[1]->scl[i] = 1;
					CharObj2Ptrs[0]->PhysicsData.YOff = 4.50000000;
				}
				else {
					BIG_OBJECTS[0]->scl[i] = 3;
					BIG_OBJECTS[1]->scl[i] = 3;
					CharObj2Ptrs[0]->PhysicsData.YOff = 18.50000000;
				}
				break;
			}

		}
		
		return;
	}


	__declspec(dllexport) void ShrinkCharacter() {
		if (!isVsChatPossible())
			return;

		bool isCharacterBig = false;
		if (SONIC_OBJECTS[0]->scl[0] > 1 || MILES_OBJECTS[0]->scl[0] > 1 || KNUCKLES_OBJECTS[0]->scl[0] > 1 || AMY_OBJECTS[0]->scl[0] > 1 || E102_OBJECTS[0]->scl[0] > 1 || BIG_OBJECTS[0]->scl[0] > 1)
			isCharacterBig = true;

		for (int i = 0; i < 3; i++) {
			if (isCharacterBig) //bring normal size
			{
				SONIC_OBJECTS[0]->scl[i] = 1;
				SONIC_OBJECTS[44]->scl[i] = 1;
				SONIC_OBJECTS[67]->scl[i] = 1;
				CharObj2Ptrs[0]->PhysicsData.YOff = 5.40000010;
			}
			else {
				SONIC_OBJECTS[0]->scl[i] = 0.5;
				SONIC_OBJECTS[44]->scl[i] = 0.5;
				SONIC_OBJECTS[67]->scl[i] = 0.5;
				CharObj2Ptrs[0]->PhysicsData.YOff = 3.0;
			}
		}
		return;
	}


	__declspec(dllexport) void SwapMusic(int id) {
		if (!isVsChatPossible())
			return;

		if (id < 0 || id > 124)
			id = rand() % 125; //failsafe

		CurrentSong = id;
		LastSong = CurrentSong;
		return;
	}


	__declspec(dllexport) void ManiaPlayVoice(int id) {
		if (!isVsChatPossible())
			return;

		if (id < 0 || id > 2042) //failsafe
			id = rand() % 2043;

		PlayVoice_R(id);
		return;
	}
}

void RandomMadnessOnFrames() {
	if (!isVsChatPossible())
		return;

	if (FastTimer > 0) {
		FastTimer--;
		CharObj2Ptrs[0]->Speed.x = CharObj2Ptrs[0]->PhysicsData.HSpeedCap;
	}
}

void InitVsChat(const char* path)
{
	if (vsChat) {
		char buf[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, buf);
		SetCurrentDirectoryA(path);
		HMODULE hm = LoadLibraryA("SADXVsChat.dll");
		if (hm == NULL)
		{
			SetCurrentDirectoryA(buf);
			MessageBoxA(WindowHandle, "SADX Vs Twitch Chat: Error, failed to load helper DLL, Chat Command will not function!", "SADX Randomizer Error", MB_ICONINFORMATION);
			return;
		}
		GetProcAddress(hm, "Main")();
		SetCurrentDirectoryA(buf);
	}
}