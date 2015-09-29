#ifndef DOOMRPG_STIMS_H
#define DOOMRPG_STIMS_H

#include "Defs.h"

str RPGMap CompoundNames[STIM_MAX];
int RPGMap CompoundColors[STIM_MAX];
int RPGMap StimStatsStart;
int RPGMap StimStatsEnd;
int RPGMap StimPowerupStart;
int RPGMap StimPowerupEnd;

NamedScript KeyBind OptionalArgs(1) void UseStim(bool);
NamedScript void TossStim();
NamedScript void AddCompound(int, int);
NamedScript void AddCompoundDirect(int, int);

void CheckStim();
void MixStim(int);
void SetStim(int);

#endif
