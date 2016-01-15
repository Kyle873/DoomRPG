#ifndef DRPG_TURRET_H
#define DRPG_TURRET_H

#include "Defs.h"

TurretUpgrade RPGMap TurretUpgradeData[MAX_UPGRADES];

NamedScript Type_ENTER void TurretCommandWheel();
NamedScript void TurretSetOffset(int, int, int);
NamedScript void TurretUseAmmo(int);
NamedScript int TurretGetProjectileDamage(int);
NamedScript int TurretGetProjectileProperty(int);
NamedScript void TurretPostSelfDestruct();

NamedScript Type_ENTER void TurretLoop();
NamedScript Type_ENTER void TurretLoopMaintenance();
NamedScript void TurretSensors();
NamedScript void TurretItemSensorThink();
NamedScript void TurretCrateSensorThink();
NamedScript void TurretPickStimMenu();

// Turret AI
NamedScript void TurretAI(int);
NamedScript bool TurretCheckTarget();
NamedScript bool TurretCheckTargetIsSelf();
NamedScript bool TurretCheckPlayerTarget();
NamedScript bool TurretCheckTargetSuitable();
NamedScript bool TurretCheckTargetDead();
NamedScript void TurretGetAttention(int, int);
NamedScript bool TurretForceTargetTID(int);
NamedScript void TurretSyncWithPlayerTarget();
NamedScript int TurretGetOwningPlayer();
NamedScript int TurretGetTargetTID();
NamedScript bool TurretWantsToSwitchToPlayerTarget();

void TurretFly(fixed, fixed, fixed);
void TurretTurn(fixed, fixed);

void BuildTurretData();
bool TurretTeleport(int);
void TurretMaintenance();
bool TurretLoadAmmo(int);
void TurretCommand(int);
bool TurretStim();
int TurretUpgradeCost(int);
void TurretPassVars();
int TurretSensorDistanceComparison(void const *, void const *);

void TurretSpawn();
void TurretDespawn();

#endif
