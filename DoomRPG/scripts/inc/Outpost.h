#ifndef _OUTPOST_DH_
#define _OUTPOST_DH_

#include "Defs.h"

extern int OutpostNotoriety;

// Spawn Spots and TIDs
extern int RPGMap ShopSpecialTID;
extern int RPGMap SecretTeleportTID;
extern int RPGMap MarineSpotTID;
extern int RPGMap NotorietySpotTID;
extern int RPGMap MarineTID;
extern int RPGMap MarineMaxTID;
extern int RPGMap MarineBossTID;
extern int RPGMap TurretTID;
extern int RPGMap BossSpotTID;
extern int RPGMap ForcefieldID;
extern int RPGMap ForcefieldGeneratorID;
extern int RPGMap GeneratorTID;
extern int RPGMap EntrySectorID;
extern int RPGMap HallTeleportSpotID;
extern int RPGMap CameraTID;
extern int RPGMap RiftSpotTID;

// Timers
extern int RPGMap ForcefieldTimer;

// Choices
extern int RPGMap LevelChoice;
extern int RPGMap SkillChoice;
extern int RPGMap WaveChoice;

// Flags
extern bool RPGMap MarinesHostile;
extern bool RPGMap PowerOut;
extern bool RPGMap BossDead;
extern bool RPGMap Invasion;

NamedScript MapSpecial void EnterOutpost();
NamedScript MapSpecial void RegenArea(int);
NamedScript MapSpecial void LevelTransport();
NamedScript MapSpecial void SkillComputer();
NamedScript MapSpecial void ToggleArena();
NamedScript MapSpecial void PassArenaLine();
NamedScript MapSpecial void SelectArenaWave();
NamedScript MapSpecial void PissOffMarines(bool);
NamedScript MapSpecial void ModuleConverter();
NamedScript MapSpecial void CreditRoom(int);
NamedScript MapSpecial void ShopSpecial();
NamedScript MapSpecial void MissionBBS();
NamedScript MapSpecial void MinigameHandler();
NamedScript MapSpecial void OutpostSecret();
NamedScript MapSpecial void PowerOutage();
NamedScript void AlarmLoop();
NamedScript void PlaceBoss();
NamedScript void SpawnBoss();

void SpawnShopSpecialItem();
void ResetOutpostMusic(bool);
OptionalArgs(3) void SetOutpostMusic(int, bool, int, int);

#endif
