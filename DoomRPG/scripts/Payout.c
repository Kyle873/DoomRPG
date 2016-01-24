#include "Defs.h"

#include "RPG.h"
#include "Utils.h"
#include "Payout.h"

NamedScript Console void CalculatePayout()
{
    PayoutData Data[PAYOUT_DATA_MAX] =
    {
        {
            .Name = "Level / Rank",
            .Sound = "payout/level",
            .Color = "White",
            .Total = &Player.Payout.Total.Level,
            .Values =
            {
                { "XP", Player.Payout.XP },
                { "Levels", Player.Payout.Levels },
                { "\CkRank", Player.Payout.Rank },
                { "\CkRank Levels", Player.Payout.RankLevels }
            }
        },
        {
            .Name = "Damage",
            .Sound = "payout/damage",
            .Color = "Red",
            .Total = &Player.Payout.Total.Damage,
            .Values =
            {
                { "Kills", Player.Payout.Kills },
                { "Deaths", Player.Payout.Deaths },
                { "Damage Taken", Player.Payout.DamageTaken },
                { "\CaStatus Effect Hits", Player.Payout.StatusEffectHit },
                { "\CaStatus Effects Evaded", Player.Payout.StatusEffectsEvaded },
                { "\CiLives\C- Used", Player.Payout.LivesUsed }
            }
        },
        {
            .Name = "Credits",
            .Sound = "payout/credits",
            .Color = "Gold",
            .Total = &Player.Payout.Total.Credits,
            .Values =
            {
                { "Credits \CdFound\C-", Player.Payout.CreditsFound },
                { "Credits \CaSpent\C-", Player.Payout.CreditsSpent }
            }
        },
        {
            .Name = "Skills",
            .Sound = "payout/skills",
            .Color = "LightBlue",
            .Total = &Player.Payout.Total.Skills,
            .Values =
            {
                { "Skills Used", Player.Payout.SkillsUsed },
                { "Skills \CiOverdrived\C-", Player.Payout.SkillsOverdrive },
                { "Skill \ChBurnout\C-", Player.Payout.SkillBurnout },
                { "\CqPowerups\C- Used", Player.Payout.PowerupsUsed },
                { "\CaAuras\C- Used", Player.Payout.AurasUsed },
                { "Summoned \CgMonsters\C-", Player.Payout.SkillSummons }
            }
        },
        {
            .Name = "Augs",
            .Sound = "payout/augs",
            .Color = "Yellow",
            .Total = &Player.Payout.Total.Augs,
            .Values =
            {
                { "Battery \CsDrained\C-", Player.Payout.AugBatteryUsed },
                { "Augs \CnDisrupted\C-", Player.Payout.AugsDisrupted }
            }
        },
        {
            .Name = "Shields",
            .Sound = "payout/shields",
            .Color = "Cyan",
            .Total = &Player.Payout.Total.Shields,
            .Values =
            {
                { "Shield \CgDamage\C-", Player.Payout.ShieldDamage },
                { "Shield \CrBreaks\C-", Player.Payout.ShieldBreaks }
            }
        },
        {
            .Name = "Stims",
            .Sound = "payout/stims",
            .Color = "Gray",
            .Total = &Player.Payout.Total.Stims,
            .Values =
            {
                { "Stims \CjMade\C-", Player.Payout.StimsMade },
                { "Stims \CdUsed\C-", Player.Payout.StimsUsed },
                { "Stims \CqToxicity\C-", Player.Payout.StimToxicity },
                { "Stims \CrImmunity\C-", Player.Payout.StimImmunity }
            }
        },
        {
            .Name = "Turret",
            .Sound = "payout/turret",
            .Color = "Green",
            .Total = &Player.Payout.Total.Turret,
            .Values =
            {
                { "Turret \CgDamage\C- Taken", Player.Payout.TurretDamageTaken },
                { "Turret \CfMaintenance Cost\C-", Player.Payout.TurretMaintenanceCost },
                { "Turret \CkCharge\C- Time", Player.Payout.TurretChargeTime },
                { "Turret \CaRepair\C- Time", Player.Payout.TurretRepairTime },
                { "Turret \CnRefit\C- Time", Player.Payout.TurretRefitTime }
            }
        },
        {
            .Name = "Missions",
            .Sound = "payout/missions",
            .Color = "Orange",
            .Total = &Player.Payout.Total.Missions,
            .Values =
            {
                { "Missions \CdCompleted\C-", Player.Payout.MissionsCompleted }
            }
        },
        {
            .Name = "Maps",
            .Sound = "payout/maps",
            .Color = "Brown",
            .Total = &Player.Payout.Total.Maps,
            .Values =
            {
                { "\CdMaps Completed", Player.Payout.MapsCompleted },
                { "\CfPar Times Beaten", Player.Payout.ParTimesBeaten },
                { "\CnItems Collected", Player.Payout.ItemsFound },
                { "\CkSecrets Found", Player.Payout.SecretsFound },
            }
        }
    };
    
    // Startup
    SetHudSize(320, 240, true);
    ActivatorSound("payout/start", 127);
    Delay(35);
    
    // Calculate Totals
    PayoutCalculateTotals();
    
    // Payouts
    for (int i = 0; i < PAYOUT_DATA_MAX; i++)
        PayoutDrawData(&Data[i], i);
    
    // Finished
    ActivatorSound("payout/end", 127);
    SetFont("BIGFONT");
    if (PayoutCalculatePPTotal() > 0)
    {
        HudMessage("+%d PP", PayoutCalculatePPTotal());
        EndHudMessage(HUDMSG_FADEINOUT, PAYOUT_ID + PAYOUT_VALUES_MAX + PAYOUT_DATA_MAX + 1, "Gold", PAYOUT_TOTAL_X + 0.1, PAYOUT_TOTAL_Y + 12 + (8 * PAYOUT_DATA_MAX), 5.0, 0.5, 0.5);
    }
    else
    {
        HudMessage("%d PP", PayoutCalculatePPTotal());
        EndHudMessage(HUDMSG_FADEINOUT, PAYOUT_ID + PAYOUT_VALUES_MAX + PAYOUT_DATA_MAX + 1, "Red", PAYOUT_TOTAL_X + 0.1, PAYOUT_TOTAL_Y + 12 + (8 * PAYOUT_DATA_MAX), 5.0, 0.5, 0.5);
    }
    PayoutAddPP();
}

NamedScriptSync void PayoutDrawData(PayoutData *Data, int Offset)
{
    int TotalOffset = 0;
    
    SetHudSize(320, 240, true);
    
    ActivatorSound(Data->Sound, 127);
    SetFont("BIGFONT");
    HudMessage(Data->Name);
    EndHudMessage(HUDMSG_FADEOUT, PAYOUT_ID, Data->Color, PAYOUT_TEXT_X + 0.1, PAYOUT_TEXT_Y - 24, 3.0, 2.0);
    Delay(35);
    
    SetFont("SMALLFONT");
    
    for (int i = 0; i < PAYOUT_VALUES_MAX; i++)
    {
        if (StrLen(Data->Values[i].Name) == 0)
            break;
        
        TotalOffset++;
        
        ActivatorSound("payout/next", 127);
        HudMessage("%S: \Cf%d", Data->Values[i].Name, Data->Values[i].Value);
        EndHudMessage(HUDMSG_FADEOUT, PAYOUT_ID + i + 1, Data->Color, PAYOUT_TEXT_X + 2 + 0.1, PAYOUT_TEXT_Y + (i * 8), 3.0, 2.0);
        Delay(35 / 8);
    }
    
    Delay(35 / 2 + (TotalOffset * 2));
    
    ActivatorSound("payout/total", 127);
    SetFont("BIGFONT");
    HudMessage("Total: \Cf%d", *Data->Total);
    EndHudMessage(HUDMSG_FADEOUT, PAYOUT_ID + PAYOUT_VALUES_MAX, Data->Color, PAYOUT_TEXT_X + 0.1, PAYOUT_TEXT_Y + 4 + (8 * (TotalOffset + 1)), 3.0, 2.0);
    
    Delay(35);
    
    ActivatorSound("payout/totaladd", 127);
    SetFont("SMALLFONT");
    HudMessage("%S: \Cf%d", Data->Name, *Data->Total);
    EndHudMessage(HUDMSG_FADEINOUT, PAYOUT_ID + PAYOUT_VALUES_MAX + Offset + 1, Data->Color, PAYOUT_TOTAL_X + 0.1, PAYOUT_TOTAL_Y + (8 * Offset), 50.0 - (5.0 * Offset), 0.5, 0.5);
    
    Delay(35 * 2);
}

void PayoutCalculateTotals()
{
    // Level / Rank
    Player.Payout.Total.Level += Player.Payout.XP / 100;
    Player.Payout.Total.Level += Player.Payout.Levels * 100;
    Player.Payout.Total.Level += Player.Payout.Rank / 100;
    Player.Payout.Total.Level += Player.Payout.RankLevels * 1000;
    
    // Damage
    Player.Payout.Total.Damage += Player.Payout.Kills * 10;
    Player.Payout.Total.Damage -= Player.Payout.Deaths * 1000;
    Player.Payout.Total.Damage += Player.Payout.DamageTaken / 10;
    Player.Payout.Total.Damage += Player.Payout.StatusEffectHit * 100;
    Player.Payout.Total.Damage += Player.Payout.StatusEffectsEvaded * 250;
    Player.Payout.Total.Damage += Player.Payout.LivesUsed * 100;
    
    // Credits
    Player.Payout.Total.Credits += Player.Payout.CreditsFound / 100;
    Player.Payout.Total.Credits += Player.Payout.CreditsSpent / 1000;
    
    // Skills
    Player.Payout.Total.Skills += Player.Payout.SkillsUsed * 10;
    Player.Payout.Total.Skills += Player.Payout.SkillsOverdrive * 10;
    Player.Payout.Total.Skills += Player.Payout.SkillBurnout / 35;
    Player.Payout.Total.Skills += Player.Payout.PowerupsUsed * 100;
    Player.Payout.Total.Skills += Player.Payout.AurasUsed * 100;
    Player.Payout.Total.Skills += Player.Payout.SkillSummons * 100;
    
    // Augs
    Player.Payout.Total.Augs += Player.Payout.AugBatteryUsed / 10;
    Player.Payout.Total.Augs += Player.Payout.AugsDisrupted * 100;
    
    // Shields
    Player.Payout.Total.Shields += Player.Payout.ShieldDamage / 10;
    Player.Payout.Total.Shields += Player.Payout.ShieldBreaks * 10;

    // Stims
    Player.Payout.Total.Stims += Player.Payout.StimsMade * 10;
    Player.Payout.Total.Stims += Player.Payout.StimsUsed * 100;
    Player.Payout.Total.Stims += Player.Payout.StimToxicity;
    Player.Payout.Total.Stims += Player.Payout.StimImmunity;
    
    // Turret
    Player.Payout.Total.Turret += Player.Payout.TurretDamageTaken;
    Player.Payout.Total.Turret += Player.Payout.TurretMaintenanceCost / 35;
    Player.Payout.Total.Turret += Player.Payout.TurretChargeTime / 35;
    Player.Payout.Total.Turret += Player.Payout.TurretRepairTime / 35;
    Player.Payout.Total.Turret += Player.Payout.TurretRefitTime / 35;
    
    // Missions
    Player.Payout.Total.Missions += Player.Payout.MissionsCompleted * 1000;
    
    // Maps
    Player.Payout.Total.Maps += Player.Payout.MapsCompleted * 1000;
    Player.Payout.Total.Maps += Player.Payout.ParTimesBeaten * 1000;
    Player.Payout.Total.Maps += Player.Payout.ItemsFound;
    Player.Payout.Total.Maps += Player.Payout.SecretsFound * 100;
}

void PayoutAddPP()
{
    Player.PP += Player.Payout.Total.Level;
    Player.PP += Player.Payout.Total.Damage;
    Player.PP += Player.Payout.Total.Credits;
    Player.PP += Player.Payout.Total.Skills;
    Player.PP += Player.Payout.Total.Augs;
    Player.PP += Player.Payout.Total.Shields;
    Player.PP += Player.Payout.Total.Stims;
    Player.PP += Player.Payout.Total.Turret;
    Player.PP += Player.Payout.Total.Missions;
    Player.PP += Player.Payout.Total.Maps;
    
    Player.Payout = (Payout){ 0 };
}

int PayoutCalculatePPTotal()
{
    return (Player.Payout.Total.Level +
            Player.Payout.Total.Damage +
            Player.Payout.Total.Credits +
            Player.Payout.Total.Skills +
            Player.Payout.Total.Augs +
            Player.Payout.Total.Stims +
            Player.Payout.Total.Shields +
            Player.Payout.Total.Turret +
            Player.Payout.Total.Missions +
            Player.Payout.Total.Maps);
}
