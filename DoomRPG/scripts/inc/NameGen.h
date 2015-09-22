#ifndef DOOMRPG__SCRIPTS__NAMEGEN_H
#define DOOMRPG__SCRIPTS__NAMEGEN_H

#include "Defs.h"

extern str SharedPool[NAME_MAX_SHARED];
extern str DemonNames[NAME_MAX_DEMON_NAMES];
extern str BossSuffixes[NAME_MAX_BOSS_SUFFIXES];
extern str ZombieRanks[NAME_MAX_ZOMBIE_RANK];
extern str MarineRanks[NAME_MAX_MARINE_RANK];
extern str MaleNames[NAME_MAX_MALE];
extern str FemaleNames[NAME_MAX_FEMALE];
extern str LastNames[NAME_MAX_LAST];
extern str MegabossSuffixes[7];
extern str PowersuitNames[NAME_MAX_SUIT];
extern str NameColors[NAME_MAX_COLORS];

str GenerateName(str Actor, str Tag);
str GenerateMonsterName();
str GenerateZombieName(bool Female);
str GenerateMarineName(bool Female);
str GenerateMegabossName(int SuffixIndex);
str GeneratePowersuitName();

#endif // DOOMRPG__SCRIPTS__NAMEGEN_H

