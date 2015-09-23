#ifndef _SKILLS_DH_
#define _SKILLS_DH_

#include "Defs.h"

typedef struct
{
    int CurrentLevel;
    int Level;
} SkillLevelInfo;

typedef bool (*SkillUseScript NamedScript Console)(SkillLevelInfo *, void *);

typedef struct
{
    str Name;
    int Cost;
    int MaxLevel;
    SkillUseScript Use;
    str Description[MAX_LEVELS];
    str Icon;
} Skill;

AddressSpace extern MapArraySpace SkillSpace;
typedef Skill SkillSpace *SkillPtr;

extern Skill SkillSpace SkillData[MAX_CATEGORIES][MAX_SKILLS];

extern bool MapRegister Overdrive;
extern int MapRegister BulletTimeTimer;

extern int MapArray SkillCategoryMax[MAX_CATEGORIES];

NamedScript Type_ENTER void SkillWheel();
NamedScript KeyBind void UseSkill(int);

// --------------------------------------------------
// Skill Scripts

// Healing/Support
NamedScript Console bool Heal(SkillLevelInfo *, void *);
NamedScript Console bool HealSummons(SkillLevelInfo *, void *);
NamedScript Console bool Decontaminate(SkillLevelInfo *, void *);
NamedScript Console bool Repair(SkillLevelInfo *, void *);

// Powerups
NamedScript Console bool Powerup(SkillLevelInfo *, void *);
NamedScript Console bool BulletTime(SkillLevelInfo *, void *);
NamedScript Console bool DropSupply(SkillLevelInfo *, void *);

// Auras
NamedScript Console bool UseAura(SkillLevelInfo *, void *);

// Attacks
NamedScript Console bool Weaken(SkillLevelInfo *, void *);
NamedScript Console bool Translocate(SkillLevelInfo *, void *);
NamedScript Console bool Repulse(SkillLevelInfo *, void *);
NamedScript Console bool AuraSteal(SkillLevelInfo *, void *);
NamedScript Console bool SoulSteal(SkillLevelInfo *, void *);
NamedScript Console bool Disruption(SkillLevelInfo *, void *);
NamedScript Console bool PlasmaBeam(SkillLevelInfo *, void *);
NamedScript Console void PlasmaBeam1();
NamedScript Console void PlasmaBeam2();
NamedScript Console void PlasmaBeam3();

// Summons
NamedScript Console bool Summon(SkillLevelInfo *, void *);

// Utility
NamedScript Console bool BreakdownArmor(SkillLevelInfo *, void *);
NamedScript Console bool ForceWall(SkillLevelInfo *, void *);
NamedScript Console bool Rally(SkillLevelInfo *, void *);
NamedScript Console bool Unsummon(SkillLevelInfo *, void *);
NamedScript Console bool Recall(SkillLevelInfo *, void *);
NamedScript Console bool Magnetize(SkillLevelInfo *, void *);
NamedScript Console bool Transport(SkillLevelInfo *, void *);

// --------------------------------------------------
// Utility Scripts

NamedScript DECORATE void RemoveAura();
NamedScript DECORATE void ClearStatusEffects();
NamedScript void TransportOutFX(int);
NamedScript void TransportInFX(int);

NamedScript void CleanDropTIDArray();

void BuildSkillData();

int ScaleEPCost(int);

void CheckSkills();
void CheckAuras();

#endif
