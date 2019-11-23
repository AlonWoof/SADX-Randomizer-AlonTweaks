#pragma once

VoidFunc(BigHoldingFroggy, 0x48cce4);

 void SetGammaTimer();  //force to 6 min instead of 3
 void BigWeightHook(); //force to 2000g



 void AllUpgrades();
 void FixCharacterSFX();



 void LoadTails_AI_R();
 void LoadTails_AI_Original(); //Normal AI (Tails Only)


 VoidFunc(EggViperBounceHit, 0x441280);

 VoidFunc(PushMSIcon, 0x425e6d);
 VoidFunc(CharSel_LoadThing, 0x512bc0);

 FunctionPointer(ObjectMaster*, CheckLoadBird, (), 0x4C6820);
 DataPointer(float, EggViperFloatThing, 0x3c6e330);
DataPointer(char, InitUpgrade, 0x3c5a954);
DataPointer(int, BigWeight, 0x3C52510);

void FixVictoryTailsVoice();

void FixAISFXJump();

void FixAISFXSonic();
void FixAISFXAmy();
void FixAISFXAmy2();
void FixAISFXAmy3();
void FixAISFXAmy4();
void FixAISFXAmy5();
void FixAISFXAmy6();


int GetCharacter0ID();
int GetCharacter1ID();
void ResultVoiceFix();