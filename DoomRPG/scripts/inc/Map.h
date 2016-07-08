#ifndef DOOMRPG_MAP_H
#define DOOMRPG_MAP_H

#include "Defs.h"

extern DynamicArray WSMapPacks[MAX_WSMAPPACKS];
extern DynamicArray *KnownLevels;
extern LevelInfo *CurrentLevel;
extern LevelInfo *PreviousLevel;
extern LevelInfo *TransporterLevel;
extern LevelInfo *DefaultOutpost;
extern int PreviousLevelNum;
extern int PreviousPrimaryLevelNum;
extern bool UsedSecretExit;
extern bool PreviousLevelSecret;
extern bool WaitingForReplacements;
extern int AllBonusMaps;
extern int CurrentSkill;

extern bool MapPackActive[MAX_WSMAPPACKS];

NamedScript Type_OPEN void MapInit();
NamedScript void MapLoop();
NamedScript void CalculateBonusMaps();
NamedScriptSync void ReduceMonsterCount();
NamedScript OptionalArgs(1) void DecideMapEvent(LevelInfo *, bool);
NamedScript void SetupMapEvent();
NamedScript void SetupMapMissions();
NamedScript void SetupOutpostEvent();
NamedScript Type_UNLOADING void ResetMapEvent();
NamedScript void AddMiniboss();
NamedScript void HellSkillTransport(int);

// Event Scripts
// --------------------------------------------------

// Megaboss
NamedScript void MegaBossEvent();

// Environmental Hazard
NamedScript void EnvironmentalHazard();
NamedScript void EnvironmentalHazardSetColors();
NamedScript void EnvironmentalHazardDamage();
NamedScript DECORATE void EnvironmentalHazardRefillGenerator();
NamedScript void EnvironmentalHazardDisarm();

// Thermonuclear Bomb
NamedScript void ThermonuclearBombEvent();
NamedScript void ThermonuclearBombAnnounce(int);
NamedScript DECORATE void ThermonuclearBombActivate();
NamedScript DECORATE void ThermonuclearBombExplode();

// Low Power
NamedScript void LowPowerEvent();
NamedScript DECORATE void PowerGeneratorActivate();

// One Monster
NamedScript void OneMonsterEvent();

// Hell Unleashed
NamedScript void HellUnleashedEvent();
NamedScript DECORATE void HellUnleashedStart();
NamedScript void HellUnleashedSpawnMonsters();

// Harmonized Destruction
NamedScript void HarmonizedDestructionEvent();

// Cracks in the Veil
NamedScript void TeleportCracksEvent();
NamedScript void TeleporterCrackView(int);
NamedScript void TeleporterCrack(int, int);

// Doomsday
NamedScript void DoomsdayEvent();
NamedScript void DoomsdayFirebomb(int);
NamedScript void DoomsdayFlameRain(int);
NamedScript Type_RESPAWN void DoomsdaySupplement();

// Vicious Downpour
NamedScript void ViciousDownpourEvent();
NamedScript void AcidRain(int);

// The Dark Zone
NamedScript void DarkZoneEvent();
NamedScript void DarkZoneFloorMist(int);

// Feeding Frenzy
NamedScript void FeedingFrenzyEvent();
NamedScript void FeedingFrenzyVisualHorror(int);

// Whispers of Darkness
NamedScript void WhispersofDarknessEvent();
NamedScript void WhispersofDarknessBackgroundCreepiness();
NamedScript void WhispersofDarknessMindRaper(int);
NamedScript void WhispersofDarknessVisionIntensifier(int);

// Rainbows
NamedScript void RainbowEvent();

// Sinstorm
NamedScript void SinstormEvent();
NamedScript void SinstormSpawner(int);

NumberedScript(MAP_EXIT_SCRIPTNUM) MapSpecial void MapExit(bool);
NamedScript MapSpecial void AddUnknownMap(str, str, int, int);

int LevelSort(void const *, void const *);
void AddAdditionalMonsters();
bool SpawnEventActor(str, int);
bool CheckMapEvent(int, LevelInfo *);
void MapEventReward();
OptionalArgs(1) LevelInfo *FindLevelInfo(str);
OptionalArgs(1) int FindLevelInfoIndex(str);

NamedScript void InitWadSmoosh();

#endif
