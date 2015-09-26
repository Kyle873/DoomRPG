#ifndef _AUGS_DH_
#define _AUGS_DH_

#include "Defs.h"

typedef AugInfo RPGMap *AugInfoPtr;

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
