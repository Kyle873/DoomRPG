#ifndef DOOMRPG_ARENA_H
#define DOOMRPG_ARENA_H

#include "Defs.h"

extern int RPGGlobal ArenaMaxWave;

extern bool RPGMap ArenaActive;
extern bool RPGMap ArenaTimerActive;
extern int RPGMap ArenaState;
extern int RPGMap ArenaPlayerNumber;
extern int RPGMap ArenaMonstersTID;
extern int RPGMap ArenaSpotSpawns;
extern int RPGMap ArenaSectorTag;
extern int RPGMap ArenaWave;
extern int RPGMap ArenaTimer;
extern int RPGMap ArenaKeyTimer;
extern int RPGMap ArenaKeyTimerType;
extern int RPGMap ArenaCount;
extern int RPGMap ArenaMod;
extern int RPGMap ArenaEnvironment;
extern int RPGMap ArenaKey;

extern str const ArenaMods[AMOD_MAX];
extern str const ArenaEvents[AEVENT_MAX];
extern str const ArenaBonus[ABONUS_MAX];
extern str const ArenaMonsters[MAX_DEF_MONSTERS];

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
void ArenaSetMusic();


#endif
