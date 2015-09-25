#ifndef _RPG_DH_
#define _RPG_DH_

#include "Defs.h"
//#include "GUI.h"
#include "ItemData.h"
#include "Skills.h"
#include "Shield.h"
#include "Monsters.h"

// Version
extern str const Version;

// Flags
extern bool Transported;
extern bool GlobalsInitialized;
extern int CompatMode;

// Arrays
extern str PlayerWeapon[MAX_PLAYERS];

// Structs
extern PlayerData _PlayerData[MAX_PLAYERS];

// Item TIDs
extern bool RPGMap ItemTIDsInitialized;
extern int RPGMap ItemTIDs[MAX_ITEMS];

// --------------------------------------------------
// Multiplayer HUD
// 

// HUD Item Counts
extern int GlobalArray Address(18) Credits[MAX_PLAYERS];

// Energy Points (EP)
extern int GlobalArray Address(2) EP[MAX_PLAYERS];

// Shield
extern int GlobalArray Address(50) Shield[MAX_PLAYERS];
extern int GlobalArray Address(51) ShieldCapacity[MAX_PLAYERS];
extern int GlobalArray Address(52) ShieldHealth[MAX_PLAYERS];

NamedScript KeyBind void QuickHeal(bool);
NamedScript KeyBind void ToggleFocusMode();
NamedScript KeyBind void FocusMode();
NamedScript void StatusEffect(int, int, int);
NamedScript int AddHealth(int, int);
NamedScript int AddHealthDirect(int, int);
NamedScript void GiveTip();

NamedScript Type_OPEN void GlobalInit();
NamedScript Type_ENTER void Init();
NamedScript void Loop();
NamedScript void WeaponSpeed();
NamedScript void PlayerDamage();
NamedScript void StatRandomizer();
NamedScript void AutosaveHandler();
NamedScript Type_OPEN void ShopSpecialHandler();
NamedScript void ItemHandler();
NamedScript void ItemInit();
NamedScript OptionalArgs(1) void DynamicLootGenerator(str, int);
NamedScript Type_DEATH void Dead();
NamedScript Type_RESPAWN void Respawn();
NamedScript void SortStartingItems();
NamedScript void DefaultLoadout();

void CheckHUD();
void CheckKeys();
void CheckCompatibility();
void AssignTIDs();

#endif
