#ifndef _STATS_DH_
#define _STATS_DH_

#include "Defs.h"

extern long int XPCurve;

extern int const SoftStatCap;
extern int const HardStatCap;

extern long int XPTable[MAX_LEVEL];
extern long int *StatTable;
extern long int RankTable[MAX_RANK];

extern str Ranks[MAX_RANK + 1];
extern str LongRanks[MAX_RANK + 1];

NamedScript DECORATE void StatusEffect(int, int, int);
NamedScript DECORATE void TryStatusEffect(int, int, int);
NamedScript void AddXP(int, long int, long int);

void InitXPTable();
void InitStatXPTable();
void InitNegativeStatXPTable();
void InitRankTable();
void CheckCombo();
void CheckLevel();
void CheckRank();
void CheckHealth();
void CheckStats();
void CheckStatBonus();
void CheckRegen();
void DoRegen();
void ResetRegen();
void CheckStatCaps();
void CheckHardStatCaps();
void RecalculateStats();
void CheckStatBounds();
void CheckLuck();
void CheckBurnout();
void CheckPerks();
void CheckToxicity();
void CheckStimImmunity();
void ToxicityDamage();
void CheckStatusEffects();
void StatusDamage(int, fixed, bool);

#endif
