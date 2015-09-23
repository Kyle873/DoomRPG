#ifndef _UTILS_DH_
#define _UTILS_DH_

#include "Defs.h"
#include "Monsters.h"

AddressSpace extern GlobalArraySpace ItemSpace;

// Used by DropInventory()
typedef struct
{
    str Actor;
    bool NoDrop;
    bool TakeAll;
    int Max;
} DroppedItem;

extern int MapRegister AuraTID;
extern str MapArray SkillLevels[6];
extern str MapArray AuraIcons[AURA_MAX];

NamedScript DECORATE int InOutpost();
NamedScript DECORATE int GetUniqueTID();
NamedScript DECORATE int GetAmmoMax(int);
NamedScript DECORATE void SoulEffect(int);
NamedScript DECORATE void DestroyImmunity();
NamedScript DECORATE int GetSkillLevel();
NamedScript DECORATE int GetShopCard();
NamedScript DECORATE void SetDamageType(int);
NamedScript DECORATE int CheckAugBatteryMax();
NamedScript DECORATE int CheckInventoryMax();
NamedScript DECORATE int CheckCapacity();
NamedScript DECORATE int GetTimer();
NamedScript DECORATE int GetSpeed(int);
NamedScript DECORATE int HPEPMax();
NamedScript DECORATE int PowersuitCheck();
NamedScript DECORATE int ShieldRemoveArmor();
NamedScript DECORATE int GetAveragePlayerLevel();
NamedScript DECORATE int GetModuleSpawnFactor();
NamedScript DECORATE int StatusEffectSeverity(int);
NamedScript DECORATE int StatusEffectTimer(int);
NamedScript DECORATE int ImmunityCrystalCheck();
NamedScript DECORATE void RainbowTranslationPulse(int);

// Monsters
NamedScript DECORATE void HealMonster(int, int);
NamedScript DECORATE void TeleportMonster();
void DropMoney(int, int, int);
OptionalArgs(6) int DropMonsterItem(int, int, str, int, fixed, fixed, fixed, fixed, fixed, fixed);

// Players
NamedScript DECORATE void RegenBoost();
NamedScript KeyBind  void SetSkill(int);
NamedScript KeyBind  void Respec(bool, bool);
NamedScript DECORATE int GetAugBattery();
NamedScript DECORATE int GetAugBatteryMax();
NamedScript DECORATE int GetToxicity();
NamedScript DECORATE int GetStimPowerupActive();
NamedScript DECORATE void AddToxicity(int);
NamedScript DECORATE void AddStimImmunity(int);
NamedScript DECORATE void ClearBurnout();
NamedScript KeyBind  void PurgeDrops();
NamedScript          void CheckArmorStats();

bool StatsCapped();
OptionalArgs(1) int CalculatePay(int);
int AveragePlayerLevel();
int AveragePlayerRank();
int AveragePlayerCredits();
int AveragePlayerLuck();
bool HaveStatusEffect();
bool DropPlayerItem(str);
bool IsPlayerMoving();
int FindPlayerID(int);
OptionalArgs(1) bool SetActivatorToTargetExtended(int, int);
bool IsTimeFrozen();

// Inventory
int CheckInventoryTID(int, str);
int SetInventory(str, int);
int SetActorInventory(int, str, int);
void DropEntireInventory();

// Items
int GetAmmoAmount(str);

// Health
NamedScript DECORATE int GetHealthPercent(int);
NamedScript DECORATE int HealthBelowPercent(int);
NamedScript DECORATE int GetHealthMax();
NamedScript DECORATE void CapHealthItem();

// Shield
NamedScript DECORATE bool ShieldActive();
NamedScript DECORATE int GetShield();
NamedScript DECORATE int GetShieldMax();
NamedScript DECORATE bool ShieldHealthMax();

// EP
NamedScript DECORATE void AddEP(int, bool);
NamedScript DECORATE OptionalArgs(1) void RemoveEP(int, int);
NamedScript DECORATE int GetEP();
NamedScript DECORATE int GetEPMax();

// Skills
NamedScript KeyBind  void PlayerTeleport(int);
bool FireProjectile(str);
bool Nova(str, int);

// Auras
NamedScript void GetAuraTokens();
void SpawnAuras(int, bool);
bool IsStealth(int);
bool PlayerHasAura(int);
bool MonsterHasAura(MonsterStatsPtr);
bool PlayerHasShadowAura(int);
bool MonsterHasShadowAura(MonsterStatsPtr);

// Drawing
NamedScript void PrintTextWiggle(char *, int, int, int, int, fixed, fixed, fixed, fixed);
NamedScript void DrawStatUp(int);
void PrintSprite(str, int, fixed, fixed, fixed);
void PrintSpriteFade(str, int, fixed, fixed, fixed, fixed);
void PrintSpriteAlpha(str, int, fixed, fixed, fixed, fixed);
OptionalArgs(1) void PrintSpritePulse(str, int, fixed, fixed, fixed, fixed, fixed, bool);
OptionalArgs(2) void PrintMessage(str, int, fixed);
void PrintError(str);
void ClearMessage(int);
void DrawBattery();
void DrawMissionInfo(MissionInfo *, fixed, fixed, bool);
void DrawShieldInfo(int, fixed, fixed);
void DrawShieldModel(int, fixed, fixed);
OptionalArgs(1) void DrawBar(str, int, int, int, bool);
void DrawProgressBar(str, int);

// Compatibility/Extensions
void RemoveDRLAItem(int, int);
void GiveDRLAArmorToken(str);
void RemoveDRLAArmorToken(str);
void CheckDRLASetWeapons();

// Math
int CalcPercent(int, int);
int Pow(int, int);
int Abs(int);
int Round(fixed);
fixed AbsFixed(fixed);
fixed Min(fixed, fixed);
fixed Max(fixed, fixed);
fixed Distance(int, int);
fixed Distance3D(fixed, fixed, fixed, fixed, fixed, fixed);
fixed Distance2D(int, int, int, int);
fixed Lerp(fixed, fixed, fixed);
InterpData Interpolate(InterpData);
fixed Map(fixed, fixed, fixed, fixed, fixed);
fixed Curve(fixed, fixed, fixed, fixed, fixed);
fixed AltCurve(fixed, fixed, fixed, fixed, fixed);

// Strings
OptionalArgs(1) bool StartsWith(str, str, bool);
OptionalArgs(1) bool EndsWith(str, str, bool);
OptionalArgs(1) bool Contains(str, str, bool);
str FormatTime(int);

// Debugging/Cheats
NamedScript Console void Cheat(int);
NamedScript Console void ModStat(int, int);
NamedScript Console void ModStatXP(int, long int);
NamedScript Console void AllSkills();
NamedScript Console void LookupXPTable(int index);
NamedScript Console void GiveCredits(int);
NamedScript Console void Payout(int);
NamedScript Console void ShopSpecialShuffle();
NamedScript Console void GiveAugs(int, int, int);
NamedScript Console void FullShield();
NamedScript Console void FullLocker(int);
NamedScript Console void GiveCompounds(int);

// System
void CreateTranslations();
OptionalArgs(1) bool CheckInput(int, int /* = KEY_PRESSED */);
OptionalArgs(1) void LogMessage(str, int /* = LOG_NORMAL */);

// Dynamic Arrays
void ArrayCreate(DynamicArray *, char *, int, int);
void ArrayResize(DynamicArray *);
void ArrayDestroy(DynamicArray *);
void ArrayDump(DynamicArray *);

#endif
