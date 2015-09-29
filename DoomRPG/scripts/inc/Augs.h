#ifndef DOOMRPG_AUGS_H
#define DOOMRPG_AUGS_H

#include "Defs.h"

extern AugInfo RPGMap AugData[AUG_MAX];

NamedScript DECORATE OptionalArgs(1) void DisableAugs(bool);
NamedScript DECORATE void ReactivateDisabledAugs();
NamedScript DECORATE void AddBattery(int);

void CheckAugSlots();
void CheckAugs();
void EquipAug(int);
void LevelUpAug(int);
void AugDamage(int);
void ClearDisabledAugs();

#endif
