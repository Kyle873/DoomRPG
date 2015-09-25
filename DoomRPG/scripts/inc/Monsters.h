#ifndef _MONSTERS_DH_
#define _MONSTERS_DH_

#include "Defs.h"

extern int RPGMap MonsterID;
extern MonsterStats RPGMap Monsters[MAX_MONSTERS];
extern MonsterInfo const MonsterData[MAX_DEF_MONSTERS];
extern MonsterInfo const MonsterDataDRLA[MAX_DEF_MONSTERS_DRLA];
extern MegabossInfo const MegaBosses[MAX_MEGABOSSES];

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
