#ifndef DOOMRPG_STIMS_H
#define DOOMRPG_STIMS_H

#include "Defs.h"

str const CompoundNames[STIM_MAX];
str const CompoundColors[STIM_MAX];
int const StimStatsStart;
int const StimStatsEnd;
int const StimPowerupStart;
int const StimPowerupEnd;

NamedScript KeyBind OptionalArgs(1) void UseStim(bool);
NamedScript DECORATE void TossStim();
NamedScript DECORATE void AddCompound(int, int);
NamedScript DECORATE void AddCompoundDirect(int, int);

void CheckStim();
void MixStim(int);
void SetStim(int);

#endif
