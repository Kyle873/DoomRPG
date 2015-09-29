#ifndef DOOMRPG_MAP_H
#define DOOMRPG_MAP_H

#include "Monsters.h"

typedef struct
{
    // MAPINFO Level Number
    int LevelNum;
    
    // If we start in the Outpost, we set this on MAP01 to tell ourselves that
    // we need to replace the placeholder info with real info.
    bool NeedsRealInfo;
    
    // Map is an Outpost or an Arena
    bool UACBase;
    bool UACArena;
    
    // Name data
    str LumpName;
    str NiceName;
    
    // Level stats
    bool Completed;
    
    int MaxMonstersKilled;
    int MaxTotalMonsters;
    int MaxMonsterPercentage;
    int MaxItemsFound;
    int MaxTotalItems;
    int MaxItemPercentage;
    int MaxSecretsFound;
    int MaxTotalSecrets;
    int MaxSecretPercentage;
    int ShortestTime;
    int UniqueSecrets;
    
    // Par/Sucks time
    int Par;
    int Sucks;
    
    // 100% Bonuses
    bool KillBonus;
    bool ItemsBonus;
    bool SecretsBonus;
    bool AllBonus;
    bool ParBonus;
    
    // Miscellaneous
    int AdditionalMonsters;
    bool SecretMap;
    
    // Event stuff
    DynamicArray MonsterPositions;
    unsigned int Event;
    bool EventCompleted;
    
    // Megaboss Event
    MegabossInfoPtr MegabossActor;
    
    // Environmental Hazard Event
    int HazardLevel;
    int RadLeft;
    int GeneratorFuel;
    
    // Thermonuclear Bomb event
    int BombTime;
    bool BombExplode;
    bool BombAnnouncing;
    bool BombKeyActive[MAX_NUKE_KEYS];
    bool BombKeyDisarming[MAX_NUKE_KEYS];
    int BombKeyTimer[MAX_NUKE_KEYS];
    
    // Low Power Event
    bool PowerGeneratorActive;
    
    // One Monster Event
    MonsterInfoPtr SelectedMonster;
    
    // Hell Unleashed Event
    int HellUnleashedActive;
    int PandoraBoxTID;
    fixed LevelAdd;
    fixed RareAdd;
    
    // Harmonized Destruction event
    int AuraType;
    
    // Doomsday Event
    int DoomTime;
} LevelInfo;

extern DynamicArray KnownLevels;
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

NamedScript Type_OPEN void MapInit();
NamedScript void MapLoop();
NamedScript void CalculateBonusMaps();
NamedScript void ReduceMonsterCount(bool *);
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
NamedScript void EnvironmentalHazardRefillGenerator();
NamedScript void EnvironmentalHazardDisarm();

// Thermonuclear Bomb
NamedScript void ThermonuclearBombEvent();
NamedScript void ThermonuclearBombAnnounce(int);
NamedScript void ThermonuclearBombActivate();
NamedScript void ThermonuclearBombExplode();

// Low Power
NamedScript void LowPowerEvent();
NamedScript void PowerGeneratorActivate();

// One Monster
NamedScript void OneMonsterEvent();

// Hell Unleashed
NamedScript void HellUnleashedEvent();
NamedScript void HellUnleashedStart();
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

NumberedScript(MAP_EXIT_SCRIPTNUM) void MapExit(bool);
NamedScript void AddUnknownMap(str, str, int, int);

int LevelSort(void const *, void const *);
void AddAdditionalMonsters();
bool SpawnEventActor(str, int);
bool CheckMapEvent(int, LevelInfo *);
void MapEventReward();
OptionalArgs(1) LevelInfo *FindLevelInfo(str);
OptionalArgs(1) int FindLevelInfoIndex(str);

#endif
