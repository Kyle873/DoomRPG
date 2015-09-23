#ifndef _MISSIONS_DH_
#define _MISSIONS_DH_

#include "RPG.h"
#include "Monsters.h"

extern MissionInfo Missions[MAX_DIFFICULTIES][MAX_MISSIONS];

extern str MapArray MissionDifficulties[MAX_DIFFICULTIES];
extern str MapArray MissionTypes[MT_MAX];
extern bool MapRegister MissionInit;

NamedScript OptionalArgs(1) void PopulateMissions(int /* = -1 */);
NamedScript void InitMission();
NamedScript void MissionDeathCheck(int, MonsterStatsPtr);

MissionInfo CreateMission(int);
void CreateMissionAt(int, int);
void CheckMission();
void ClearMission();
void GetTargetMonster(MissionInfo *);
int CalculateAverageDifficulty();
str GetMissionMonsterActor(str);
int MissionTypeSort(void const *, void const *);

#endif
