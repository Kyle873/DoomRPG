#ifndef _OUTPOST_DH_
#define _OUTPOST_DH_

extern int OutpostNotoriety;

// Spawn Spots and TIDs
extern int MapRegister ShopSpecialTID;
extern int MapRegister SecretTeleportTID;
extern int MapRegister MarineSpotTID;
extern int MapRegister NotorietySpotTID;
extern int MapRegister MarineTID;
extern int MapRegister MarineMaxTID;
extern int MapRegister MarineBossTID;
extern int MapRegister TurretTID;
extern int MapRegister BossSpotTID;
extern int MapRegister ForcefieldID;
extern int MapRegister ForcefieldGeneratorID;
extern int MapRegister GeneratorTID;
extern int MapRegister EntrySectorID;
extern int MapRegister HallTeleportSpotID;
extern int MapRegister CameraTID;
extern int MapRegister RiftSpotTID;

// Timers
extern int MapRegister ForcefieldTimer;

// Choices
extern int MapRegister LevelChoice;
extern int MapRegister SkillChoice;
extern int MapRegister WaveChoice;

// Flags
extern bool MapRegister MarinesHostile;
extern bool MapRegister PowerOut;
extern bool MapRegister BossDead;
extern bool MapRegister Invasion;

NamedScript void EnterOutpost();
NamedScript void RegenArea(int);
NamedScript void StimInjector();
NamedScript void LevelTransport();
NamedScript void SkillComputer();
NamedScript void ToggleArena();
NamedScript void PassArenaLine();
NamedScript void SelectArenaWave();
NamedScript void PissOffMarines(bool);
NamedScript void ModuleConverter();
NamedScript void CreditRoom(int);
NamedScript void ShopSpecial();
NamedScript void MissionBBS();
NamedScript void MinigameHandler();
NamedScript void OutpostSecret();
NamedScript void PowerOutage();
NamedScript void AlarmLoop();
NamedScript void PlaceBoss();
NamedScript void SpawnBoss();

void SpawnShopSpecialItem();
void ResetOutpostMusic(bool);
OptionalArgs(3) void SetOutpostMusic(int, bool, int, int);

#endif
