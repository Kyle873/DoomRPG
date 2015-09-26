#ifndef _ARENA_DH_
#define _ARENA_DH_

#include "Defs.dh"

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

str RPGMap ArenaMods[AMOD_MAX];
str RPGMap ArenaEvents[AEVENT_MAX];
str RPGMap ArenaBonus[ABONUS_MAX];
str RPGMap Monsters[MAX_DEF_MONSTERS];

NamedScript void ArenaLoop();
NamedScript void ArenaStop();
NamedScript void SetArena(int, int, int);
NamedScript void ArenaChooseBonus();

void ArenaGetBonus(int);
void DropArenaItem(str);
void ArenaDrawHUD();
void ArenaCheckMod();
void ArenaSpawnMobs();
void ArenaSetEnvironment(int);

#endif
