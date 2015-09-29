#ifndef DOOMRPG_CRATE_H
#define DOOMRPG_CRATE_H

extern str const CrateRarityNames[MAX_DIFFICULTIES];
extern int RPGMap CrateID;
extern CrateInfo RPGMap Crates[CRATE_MAX];

NamedScript void InitCrate();
NamedScript void UseCrate(int);
NamedScript void CrateHack();

void GenerateCrate(int, int);
void CrateTakeItem();
bool CrateEmpty(int);
bool CrateEmptyTID(int);
void DrawCrate();
void CrateInput();

#endif
