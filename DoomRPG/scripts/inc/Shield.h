#ifndef _SHIELD_DH_
#define _SHIELD_DH_

#include "Defs.h"

typedef struct
{
    str Actor;
    str Name;
    str Icon;
    
    int Capacity;
    int ChargeRate;
    fixed DelayRate;
} ShieldPart;

typedef void (*ShieldAccModScript NamedScript)();
typedef void (*ShieldAccEquipScript NamedScript)();
typedef void (*ShieldAccUnequipScript NamedScript)(bool);
typedef void (*ShieldAccDamageScript NamedScript)(int);
typedef void (*ShieldAccBreakScript NamedScript)();
typedef int  (*ShieldAccChargeScript NamedScript)(int);
typedef void (*ShieldAccOverchargeScript NamedScript)(int);
typedef bool (*ShieldAccFastChargeScript NamedScript)();
typedef void (*ShieldAccFullChargeScript NamedScript)();

typedef struct
{
    str Actor;
    str Name;
    str Icon;
    int Price;
    str Description;
    EShieldPassive PassiveEffect;
    
    ShieldAccModScript          Modifier;
    ShieldAccEquipScript        Equip;
    ShieldAccUnequipScript      Unequip;
    ShieldAccDamageScript       Damage;
    ShieldAccBreakScript        Break;
    ShieldAccChargeScript       Charge;
    ShieldAccOverchargeScript   Overcharge;
    ShieldAccFastChargeScript   FastCharge;
    ShieldAccFullChargeScript   FullCharge;
} ShieldAccessory;

AddressSpace extern GlobalArraySpace ShieldSpace;
typedef ShieldPart ShieldSpace *ShieldPartPtr;
typedef ShieldAccessory ShieldSpace *ShieldAccsPtr;

extern ShieldSpace int ShieldPartsMax[3];
extern ShieldSpace ShieldPart ShieldParts[3][MAX_PARTS];
extern ShieldSpace ShieldAccessory ShieldAccessories[MAX_ACCESSORIES];

NamedScript void BuildShieldParts();
NamedScript void ShieldTimer();
NamedScript void ShieldDamage(int);
NamedScript void ShieldBroken();
NamedScript void ShieldTimerReset();
NamedScript bool ActivateShield();
NamedScript bool DeactivateShield();

NamedScript void AMShieldCharge();
NamedScript KeyBind void ToggleShield();
NamedScript void AddShield(int);
NamedScript void AddRemoteShield(int, int);

// Accessory Equip/Unequip
void RemoveShieldAccessory();
void SetShieldAccessory(ShieldAccsPtr);

// Conversions
NamedScript void HealthConversion(int);
NamedScript void EPConversion(int);
NamedScript void BatteryConversion(int);
NamedScript void AmmoConversion(int);

// Charging
NamedScript int LightningCharge(int);
NamedScript int RegenShieldCharge(int);
NamedScript bool CellFastCharge();

// Damage Callbacks
NamedScript void BoosterShieldDamage(int);
NamedScript void SpookyDamage(int);
NamedScript void TimeyWimeyHurtyBall(int);
NamedScript void StaticChargeShieldDamage(int);
NamedScript void CounterDamage(int);
NamedScript void RegenShieldDamage(int);

// Break Callbacks
NamedScript void NovaShieldBreak();
NamedScript void TeleportBreak();
NamedScript void AdaptiveBreak();
NamedScript void StaticChargeShieldBreak();
NamedScript void FlanExplosion();
NamedScript void SpaghettiShieldBreak();

// Recharge Callbacks
NamedScript void SpaghettiShieldFullCharge();
NamedScript void TeleportFullCharge();

// Modifier Callbacks
NamedScript void X7Mod();
NamedScript void AmpShieldMod();
NamedScript void HurryMod();
NamedScript void Def2Mod();
NamedScript void BlzutMod();
NamedScript void RektMod();
NamedScript void LightAmpMod();
NamedScript void LightAmpUnequip(bool);
NamedScript void InvisibilityMod();
NamedScript void InvisibilityUnequip(bool);
NamedScript void LazyMod();
NamedScript void AccelerativeShieldMod();
NamedScript void TheKillingBoosterMod();
NamedScript void MinuteMaidMod();
NamedScript void AmericaShieldMod();
NamedScript void GhettoLuckMod();
NamedScript void SuperSqueezyScalarMod();
NamedScript void ReflectionMod();
NamedScript void ScarletWeatherRhapsodyShieldMod();
NamedScript void SanicMod();
NamedScript void NakedMod();
NamedScript void BloodyShieldSoRealMod();
NamedScript void FriendshipShieldMod();
NamedScript void ReflectionUnequip(bool);
NamedScript void RegenShieldMod();
NamedScript void MLGNoScopeShieldMod();
NamedScript void RussianRouletteMod();
NamedScript void OCDShieldMod();
NamedScript void ArenaShieldMod();
NamedScript void HowDidYouEvenMod();
NamedScript void OhYeahMod();
NamedScript void McDuckMod();
NamedScript void AmmoSpaceMod();
NamedScript void AmmoSpaceUnequip(bool);
NamedScript void TheAmazingBatteryShieldMod();
NamedScript void LilZiggyMod();
NamedScript void MurderBurgerMod();
NamedScript void LuckyBastardMod();
NamedScript void IronShieldMod();
NamedScript void EPRegenSwapperMod();
NamedScript void HoarderMod();

// General
void CheckShields();
void CheckShieldAccessory();
bool CheckShieldValid();

#endif
