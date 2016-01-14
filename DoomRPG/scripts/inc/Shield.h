#ifndef _SHIELD_DH_
#define _SHIELD_DH_

#include "Defs.h"

extern int const ShieldPartsMax[3];
extern ShieldPart const ShieldParts[3][MAX_PARTS];
extern ShieldAccessory const ShieldAccessories[MAX_ACCESSORIES];

NamedScript void ShieldTimer();
NamedScript void ShieldDamage(int);
NamedScript void ShieldBroken();
NamedScript void ShieldTimerReset();
NamedScript bool ActivateShield();
NamedScript bool DeactivateShield();

NamedScript DECORATE void AMShieldCharge();
NamedScript KeyBind void ToggleShield();
NamedScript DECORATE void AddShield(int);
NamedScript DECORATE void AddRemoteShield(int, int);

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
