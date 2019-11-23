#include "stdafx.h"
#include "Utils.h"
#include "RM.h"
#include "RandomHelpers.h"

HelperFunctions extern help;
extern int CustomLayout;
extern bool Missions;
extern int levelCount;

void __cdecl RedMountain_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.ReplaceFile("system\\SET0500S.BIN", "system\\levels\\Red Mountain\\Sonic-RM-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0501S.BIN", "system\\levels\\Red Mountain\\Sonic-RM-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0503S.BIN", "system\\levels\\Red Mountain\\Sonic-RM-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0504S.BIN", "system\\levels\\Red Mountain\\Sonic-RM-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0500S.bin", "system\\cam\\CAM0500S.bin");
	helperFunctions.ReplaceFile("system\\CAM0501S.bin", "system\\cam\\CAM0501S.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, RM1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, RM2_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET0500M.BIN", "system\\levels\\Red Mountain\\Tails-RM-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0501M.BIN", "system\\levels\\Red Mountain\\Tails-RM-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0503M.BIN", "system\\levels\\Red Mountain\\Tails-RM-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0504M.BIN", "system\\levels\\Red Mountain\\Tails-RM-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0500M.bin", "system\\cam\\CAM0500M.bin");
	helperFunctions.ReplaceFile("system\\CAM0501M.bin", "system\\cam\\CAM0501M.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, RM1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, RM2_StartPositions[0]);


	//Knuckles
	helperFunctions.ReplaceFile("system\\SET0500K.BIN", "system\\levels\\Red Mountain\\Knux-RM-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0501K.BIN", "system\\levels\\Red Mountain\\Knux-RM-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0503K.BIN", "system\\levels\\Red Mountain\\Knux-RM-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0504K.BIN", "system\\levels\\Red Mountain\\Knux-RM-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0500K.bin", "system\\cam\\CAM0500K.bin");
	helperFunctions.ReplaceFile("system\\CAM0501K.bin", "system\\cam\\CAM0501K.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, RM1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, RM2_StartPositions[0]);


	//Amy
	helperFunctions.ReplaceFile("system\\SET0500A.BIN", "system\\levels\\Red Mountain\\Amy-RM-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0501A.BIN", "system\\levels\\Red Mountain\\Amy-RM-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0503A.BIN", "system\\levels\\Red Mountain\\Amy-RM-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0504A.BIN", "system\\levels\\Red Mountain\\Amy-RM-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0500A.bin", "system\\cam\\CAM0500A.bin");
	helperFunctions.ReplaceFile("system\\CAM0501A.bin", "system\\cam\\CAM0501A.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, RM1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, RM2_StartPositions[0]);


	//Big
	helperFunctions.ReplaceFile("system\\SET0500B.BIN", "system\\levels\\Red Mountain\\Big-RM-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0501B.BIN", "system\\levels\\Red Mountain\\Big-RM-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0503B.BIN", "system\\levels\\Red Mountain\\Big-RM-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0504B.BIN", "system\\levels\\Red Mountain\\Big-RM-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0500B.bin", "system\\cam\\CAM0500B.bin");
	helperFunctions.ReplaceFile("system\\CAM0501B.bin", "system\\cam\\CAM0501B.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, RM1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, RM2_StartPositions[0]);


	//Gamma
	helperFunctions.ReplaceFile("system\\SET0500E.BIN", "system\\levels\\Red Mountain\\Gamma-RM-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0501E.BIN", "system\\levels\\Red Mountain\\Gamma-RM-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0503E.BIN", "system\\levels\\Red Mountain\\Gamma-RM-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0504E.BIN", "system\\levels\\Red Mountain\\Gamma-RM-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0500E.bin", "system\\cam\\CAM0500E.bin");
	helperFunctions.ReplaceFile("system\\CAM0501E.bin", "system\\cam\\CAM0501E.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, RM1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, RM2_StartPositions[0]);

	RedMountainDeathZones[0] = RedMountain1DeathZones;

}



void RedMountainAct4() {

	if (CurrentAct == 1)
		CustomLayout = rand() % 2;
	else
		CustomLayout = randomizedSets[levelCount].layout;

	
	if (CurrentAct == 1)
	{
		if (CurrentCharacter == Characters_Gamma) //This scenario shouldn't be possible, but just in case.
		{
			LoadSetFile(0, "0500");
			LoadSetFile(1, "0501"); //load Sonic version
			WriteData<1>((void*)0x6027c5, 0x00); //Fix Lava (Sonic Version)
			WriteData<1>((void*)0x6027cb, 0x74); //restore original
			CustomLayout = 0;
		}
		else
		{
			LoadSetFile(0, "0500");
			LoadSetFile(1, "0503"); //load Gamma version
			WriteData<1>((void*)0x6027c5, 0x08); //Fix Red Mountain Lava (Gamma layout.)
			WriteData<1>((void*)0x6027cb, 0x75); //fix Red Mountain Lava for everyone.
			CustomLayout = 1;
		}
	}

	if (CurrentAct == 0)
	{
		CustomLayout = randomizedSets[levelCount].layout;

		switch (CustomLayout)
		{
		case 0:
			LoadSetFile(0, "0500");
			LoadSetFile(1, "0501");
			return;
			break;
		case 1:
			LoadSetFile(0, "0500");
			LoadSetFile(1, "0501"); 
			break;
		case 2: //100 Rings
			LoadSetFile(0, "0500");
			LoadSetFile(1, "0501"); 
			break;
		case 3: //Lost Chao
			LoadSetFile(0, "0504");
			LoadSetFile(1, "0501"); 
			break;
		}
	}

	return;
}



void CamRedMountain() {

	if (CustomLayout == 1)
	{
		LoadCamFile(1, "0503"); //load the camera used for Gamma.
		return;
	}
	else
	{
		LoadCamFile(1, "0501"); //load the camera used for Sonic.
		return;
	}
}


ObjectListEntry RedMountainObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4CBDE0, "O DYNAMITE" } /* "O DYNAMITE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x60EE00, "o_honoo" } /* "o_honoo" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60EA70, "o_komokosu" } /* "o_komokosu" */,
	{ 6, 3, 1, 25000000, 0, (ObjectFuncPtr)0x602670, "o_yougan" } /* "o_yougan" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E8B0, "o_untei1" } /* "o_untei1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E8F0, "o_untei2" } /* "o_untei2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E930, "o_untei3" } /* "o_untei3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E980, "o_untei6" } /* "o_untei6" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60DD50, "O HAKA" } /* "O HAKA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60DD80, "O CHAIR" } /* "O CHAIR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E410, "O BONEHEAD" } /* "O BONEHEAD" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60E4D0, "O BONESTICK" } /* "O BONESTICK" */,
	{ 6, 3, 1, 638401, 0, (ObjectFuncPtr)0x60E150, "O MASIBA" } /* "O MASIBA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D810, "O GRAVE" } /* "O GRAVE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60CB20, "O LIGHT" } /* "O LIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D570, "O PIPEI" } /* "O PIPEI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D5F0, "O PIPEL" } /* "O PIPEL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D5B0, "O PIPEBOX" } /* "O PIPEBOX" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60D4F0, "O VENT" } /* "O VENT" */,
	{ 3, 3, 1, 998001, 0, (ObjectFuncPtr)0x60D260, "O HANMA" } /* "O HANMA" */,
	{ 2, 3, 1, 249001, 0, (ObjectFuncPtr)0x605DF0, "O SAKU" } /* "O SAKU" */,
	{ 2, 6, 1, 249001, 0, (ObjectFuncPtr)0x605E40, "O SAKU2" } /* "O SAKU2" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x605E90, "O ROUYA" } /* "O ROUYA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60CAF0, "O LIGHTB" } /* "O LIGHTB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60C820, "OGL" } /* "OGL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x601EB0, "Ex Rock" } /* "Ex Rock" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x60C640, "O Erupt" } /* "O Erupt" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x60B390, "O GEAR" } /* "O GEAR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60B1E0, "O RELAY P" } /* "O RELAY P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x60B080, "O SIGNBOARD" } /* "O SIGNBOARD" */,
	{ 6, 3, 1, 998001, 0, (ObjectFuncPtr)0x60AFC0, "O PROPELLER" } /* "O PROPELLER" */,
	{ 2, 3, 1, 638401, 0, (ObjectFuncPtr)0x60A9F0, "O BREAKSTEP" } /* "O BREAKSTEP" */,
	{ 2, 3, 1, 638401, 0, (ObjectFuncPtr)0x609F00, "O BREAKSTEP2" } /* "O BREAKSTEP2" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x609360, "Mtn SpiderA" } /* "Mtn SpiderA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x609560, "Mtn SpiderB" } /* "Mtn SpiderB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x607BA0, "O TREE1" } /* "O TREE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x6089B0, "O Futa" } /* "O Futa" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x608730, "MagmaCnt" } /* "MagmaCnt" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x6085B0, "Syuujin b" } /* "Syuujin b" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x608630, "Syuujin r" } /* "Syuujin r" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x6086B0, "Syuujin g" } /* "Syuujin g" */,
	{ 3, 3, 1, 10000, 0, (ObjectFuncPtr)0x608380, "O MT KUSA" } /* "O MT KUSA" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x6080D0, "O TURI1" } /* "O TURI1" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x6080F0, "O TURI2" } /* "O TURI2" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x608110, "O TURI3" } /* "O TURI3" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x608130, "O TURI4" } /* "O TURI4" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x607F60, "O ASIBA1" } /* "O ASIBA1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x607CB0, "O TREE2" } /* "O TREE2" */,
	{ 15, 3, 1, 40000, 0, (ObjectFuncPtr)0x6077D0, "O Bat" } /* "O Bat" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x605EE0, "MT_SOTO" } /* "MT_SOTO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x605F00, "MT_TBOX" } /* "MT_TBOX" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x606F20, "O HAGO" } /* "O HAGO" */,
	{ 6, 3, 1, 638401, 0, (ObjectFuncPtr)0x603F80, "O ZAKO" } /* "O ZAKO" */,
	{ 6, 3, 1, 638401, 0, (ObjectFuncPtr)0x603FF0, "O ZAKO_B" } /* "O ZAKO_B" */,
	{ 6, 3, 1, 810000, 0, (ObjectFuncPtr)0x606B20, "O DEKA" } /* "O DEKA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x606820, "O LAMP1" } /* "O LAMP1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x606840, "O LAMP2" } /* "O LAMP2" */,
	{ 3, 3, 1, 1000000, 0, (ObjectFuncPtr)0x6063B0, "O HATAKI" } /* "O HATAKI" */,
	{ 6, 3, 1, 998001, 0, (ObjectFuncPtr)0x602960, "O MYOUGAN" } /* "O MYOUGAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x605F50, "MT_TSAKU" } /* "MT_TSAKU" */,
	{ 2, 3, 1, 10000, 0, (ObjectFuncPtr)0x605C50, "O BLOW" } /* "O BLOW" */,
	{ 2, 3, 1, 10000, 0, (ObjectFuncPtr)0x605D40, "O BLOW2" } /* "O BLOW2" */,
	{ 2, 3, 5, 250000, 0, (ObjectFuncPtr)0x4AD140, "E SARU  " } /* "E SARU  " */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0DF0, "SPINA A" } /* "SPINA A" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0F40, "SPINA B" } /* "SPINA B" */,
	{ 2, 3, 5, 250000, 0, (ObjectFuncPtr)0x4AF860, "E UNI C" } /* "E UNI C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ 2, 3, 1, 25000000, 0, (ObjectFuncPtr)0x6028B0, "O YE102" } /* "O YE102" */,
	{ 2, 3, 1, 4000000, 0, (ObjectFuncPtr)0x605B40, "E E_104" } /* "E E_104" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 6, 3, 1, 250000, 0, (ObjectFuncPtr)0x6042A0, "O BPOLE" } /* "O BPOLE" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" } /* "O FROG" */
};

ObjectList RedMountainObjectList = { arraylengthandptrT(RedMountainObjectList_list, int) };

void __cdecl RMObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_RedMountain * 8 +1] = &RedMountainObjectList;
}

