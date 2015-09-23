#ifndef _MONSTERS_DH_
#define _MONSTERS_DH_

#include "Defs.h"

typedef struct
{
    // Basic
    int TID;
    str Actor;
    str ReplaceActor;
    Position position;
    int Flags;
    int RenderStyle;
    int SpawnHealth;
    int HealthMax;
    int RegenHealth;
    
    // Properties
    fixed Speed;
    fixed Height;
    fixed Radius;
    
    // Flags
    bool Init;
    bool NeedReinit;
    bool HealthBar;
    bool Named;
    bool Reinforcement;
    bool MegaBoss;
    
    // Missions
    int Target;
    
    // Stats
    int Level;
    int Threat;
    int Strength;
    int Defense;
    int Vitality;
    int Energy;
    int Regeneration;
    int Agility;
    int Capacity;
    int Luck;
    
    // Auras
    AuraInfo Aura;
} MonsterStats;

typedef struct
{
    str Actor;
    str Name;
    
    // This monster's relative threat level as a percentage
    int Difficulty;
    int ThreatLevel;
    // These guys are in short supply
    bool Boss;
    
    // Special event text for One Monster level events
    str Feeling;
} MonsterInfo;

typedef struct
{
    str Actor;
    str Music;
} MegabossInfo;

AddressSpace extern MapArraySpace MonsterSpace;
typedef MonsterInfo MonsterSpace const *MonsterInfoPtr;
typedef MegabossInfo MonsterSpace const *MegabossInfoPtr;

AddressSpace extern MapArraySpace MonsterStatsSpace;
typedef MonsterStats MonsterStatsSpace *MonsterStatsPtr;

extern MonsterStatsSpace int MonsterID;
extern MonsterStatsSpace MonsterStats Monsters[MAX_MONSTERS];
extern MonsterSpace MonsterInfo const MonsterData[MAX_DEF_MONSTERS];
extern MonsterSpace MonsterInfo const MonsterDataDRLA[MAX_DEF_MONSTERS_DRLA];
extern MonsterSpace MegabossInfo const MegaBosses[MAX_MEGABOSSES];

NamedScript DECORATE void MonsterInit(int);
NamedScript Console  void MonsterSet(int, int, int);
NamedScript Console  void MonsterSetShadow();
NamedScript Console  void MonsterModStat(int, int);
NamedScript Console  void MonsterDump();
NamedScript Console  void MonsterDamage(int, int);
NamedScript DECORATE void MonsterTransport(int, int, int);
NamedScript DECORATE void MonsterRegenHealer();

OptionalArgs(1) NamedScript void MonsterInitStats(int);
NamedScript void MonsterStatsHandler();
NamedScript void MonsterAuraDisplayHandler();
NamedScript void MonsterAggressionHandler();
OptionalArgs(1) NamedScript void MonsterLevelupHandler(bool);
NamedScript void MonsterEPDrainHandler();
NamedScript void MonsterRegenerationHandler();
NamedScript void MonsterDamageRetaliationHandler();
NamedScript void MonsterMoneyDrainHandler();
NamedScript void MonsterAmmoDrainHandler();
NamedScript void MonsterFellowResurrectionHandler();
NamedScript void MonsterEpicVisitTimeHandler();
NamedScript void MonsterDeathCheck();
NamedScript void MonsterDeath();
NamedScript int WhoKilledMe();
NamedScript int WhoShotMe();

void MonsterLevelup(MonsterStatsPtr);
void CapMonsterStats(MonsterStatsPtr);
int CalculateMonsterThreatLevel(MonsterStatsPtr);
int CalculateMonsterMaxHealth(MonsterStatsPtr);
fixed CalculateMonsterSpeed(MonsterStatsPtr);
void RemoveMonsterAura(MonsterStatsPtr);
str DetermineBestStatColor(MonsterStatsPtr);
int BestStat(MonsterStatsPtr);
int FindMonster(int);

#endif
