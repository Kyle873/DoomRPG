#ifndef DOOMRPG_HUD_H
#define DOOMRPG_HUD_H

#include "Defs.h"

NamedScript Type_ENTER void StatusEffectHUD();
NamedScript Type_ENTER void OverviewHUD();
NamedScript Type_ENTER void ComboHUD();
NamedScript Type_ENTER void SkillHUD();
NamedScript Type_ENTER void StimHUD();
NamedScript Type_ENTER void MissionHUD();
NamedScript Type_ENTER void AuraTimerHUD();
NamedScript Type_ENTER void PowerupHUD();
NamedScript Type_ENTER void EventHUD();
NamedScript Type_ENTER void CoopViewHUD();
NamedScript Type_ENTER void MultiplayerHUD();
NamedScript Type_ENTER void TurretHUD();
NamedScript Type_ENTER void StatHUD();
NamedScript void DamageHUD(int, bool);

// Add-on specific
NamedScript Type_ENTER void DRLAHUD();
NamedScript Type_ENTER void LegenDoomHUD();
str GetLegendaryEffectImage(LegendaryDef const *, int, str);

#endif
