#ifndef DOOMRPG_ARENA_H
#define DOOMRPG_ARENA_H

#include "Defs.h"

int RPGGlobal ArenaMaxWave;

bool RPGMap ArenaActive;
bool RPGMap ArenaTimerActive;
int RPGMap ArenaState;
int RPGMap ArenaPlayerNumber;
int RPGMap ArenaMonstersTID;
int RPGMap ArenaSpotSpawns;
int RPGMap ArenaSectorTag;
int RPGMap ArenaWave;
int RPGMap ArenaTimer;
int RPGMap ArenaKeyTimer;
int RPGMap ArenaKeyTimerType;
int RPGMap ArenaCount;
int RPGMap ArenaMod;
int RPGMap ArenaEnvironment;
int RPGMap ArenaKey;

str const ArenaMods[AMOD_MAX];
str const ArenaEvents[AEVENT_MAX];
str const ArenaBonus[ABONUS_MAX];
str const ArenaMonsters[MAX_DEF_MONSTERS];

NamedScript MapSpecial void ArenaLoop();
NamedScript MapSpecial void ArenaStop();
NamedScript MapSpecial void SetArena(int, int, int);
NamedScript MapSpecial void ArenaChooseBonus();

void ArenaGetBonus(int);
void DropArenaItem(str);
void ArenaDrawHUD();
void ArenaCheckMod();
void ArenaSpawnMobs();
void ArenaSetEnvironment(int);

#endif
