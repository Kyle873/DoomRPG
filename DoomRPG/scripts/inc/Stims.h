#ifndef DOOMRPG_STIMS_H
#define DOOMRPG_STIMS_H

#include "Defs.h"

extern str const CompoundNames[STIM_MAX];
extern str const CompoundColors[STIM_MAX];
extern int const StimStatsStart;
extern int const StimStatsEnd;
extern int const StimPowerupStart;
extern int const StimPowerupEnd;

NamedScript KeyBind OptionalArgs(1) void UseStim(bool);
NamedScript DECORATE void TossStim();
NamedScript DECORATE void AddCompound(int, int);
NamedScript DECORATE void AddCompoundDirect(int, int);

void CheckStim();
void MixStim(int);
void SetStim(int);

#endif
