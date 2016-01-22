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
            .Total = Player.Payout.Total.Level,
            .Values =
            {
                { "XP", Player.Payout.XP },
                { "Level", Player.Payout.Levels },
                { "\CkRank", Player.Payout.Rank },
                { "\CkRank Levels", Player.Payout.RankLevels }
            }
        },
        {
            .Name = "Damage",
            .Sound = "payout/damage",
            .Color = "Red",
            .Total = Player.Payout.Total.Damage,
            .Values =
            {
                { "Damage Dealt", Player.Payout.DamageDealt },
                { "Damage Taken", Player.Payout.DamageTaken },
                { "Kills", Player.Payout.Kills },
                { "Deaths", Player.Payout.Deaths },
                { "\CaStatus Effect Hits", Player.Payout.StatusEffectHit },
                { "\CaStatus Effects Evaded", Player.Payout.StatusEffectsEvaded }
            }
        },
        {
            .Name = "Credits",
            .Sound = "payout/credits",
            .Color = "Gold",
            .Total = Player.Payout.Total.Credits,
            .Values =
            {
                { "Credits Found", Player.Payout.CreditsFound },
                { "Credits Spent", Player.Payout.CreditsSpent }
            }
        },
        {
            .Name = "Skills",
            .Sound = "payout/skills",
            .Color = "LightBlue",
            .Total = Player.Payout.Total.Skills,
            .Values =
            {
                { "Skills Used", Player.Payout.SkillsUsed },
                { "Skill Burnout", Player.Payout.SkillBurnout },
                { "Auras Used", Player.Payout.AurasUsed }
            }
        },
        {
            .Name = "Augs",
            .Sound = "payout/augs",
            .Color = "Yellow",
            .Total = Player.Payout.Total.Augs,
            .Values =
            {
                { "Augs Active", Player.Payout.AugsActive },
                { "Battery Drained", Player.Payout.AugBatteryUsed }
            }
        },
        {
            .Name = "Shields",
            .Sound = "payout/shields",
            .Color = "Cyan",
            .Total = Player.Payout.Total.Shields,
            .Values =
            {
                { "Shield Damage", Player.Payout.ShieldDamage },
                { "Shield Breaks", Player.Payout.ShieldBreaks }
            }
        },
        {
            .Name = "Stims",
            .Sound = "payout/stims",
            .Color = "Gray",
            .Total = Player.Payout.Total.Stims,
            .Values =
            {
                { "Stims Made", Player.Payout.StimsMade },
                { "Stims Used", Player.Payout.StimsUsed },
                { "Stims \CdToxicity\C-", Player.Payout.StimToxicity },
                { "Stims \CrImmunity\C-", Player.Payout.StimImmunity }
            }
        },
        {
            .Name = "Turret",
            .Sound = "payout/turret",
            .Color = "Green",
            .Total = Player.Payout.Total.Turret,
            .Values =
            {
                { "Turret Damage Taken", Player.Payout.TurretDamageTaken },
                { "Turret Maintenance Cost", Player.Payout.TurretMaintenanceCost },
                { "Turret \CkCharge\C- Time", Player.Payout.TurretChargeTime },
                { "Turret \CaRepair\C- Time", Player.Payout.TurretRepairTime },
                { "Turret \CnRefit\C- Time", Player.Payout.TurretRefitTime }
            }
        },
        {
            .Name = "Missions",
            .Sound = "payout/missions",
            .Color = "Orange",
            .Total = Player.Payout.Total.Missions,
            .Values =
            {
                { "Missions Completed", Player.Payout.MissionsCompleted }
            }
        },
        {
            .Name = "Maps",
            .Sound = "payout/maps",
            .Color = "Brown",
            .Total = Player.Payout.Total.Maps,
            .Values =
            {
                { "\CdMaps Completed", Player.Payout.MapsCompleted },
                { "\CfPar Times Beaten", Player.Payout.ParTimesBeaten },
                { "\CnItems Collected", Player.Payout.ItemsCollected },
                { "\CkSecrets Found", Player.Payout.SecretsFound },
            }
        },
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
    HudMessage("+%d PP", PayoutCalculatePPTotal());
    EndHudMessage(HUDMSG_FADEINOUT, PAYOUT_ID + PAYOUT_VALUES_MAX + PAYOUT_DATA_MAX + 1, "Gold", PAYOUT_TOTAL_X + 0.1, PAYOUT_TOTAL_Y + 12 + (8 * PAYOUT_DATA_MAX), 5.0, 0.5, 0.5);
    
    // Clear out Everything
    Delay(35 * 3);
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
        HudMessage("%S: %d", Data->Values[i].Name, Data->Values[i].Value);
        EndHudMessage(HUDMSG_FADEOUT, PAYOUT_ID + i + 1, Data->Color, PAYOUT_TEXT_X + 2 + 0.1, PAYOUT_TEXT_Y + (i * 8), 3.0, 2.0);
        Delay(35 / 8);
    }
    
    Delay(35 / 2);
    
    ActivatorSound("payout/total", 127);
    SetFont("BIGFONT");
    HudMessage("Total: %d", Data->Total);
    EndHudMessage(HUDMSG_FADEOUT, PAYOUT_ID + PAYOUT_VALUES_MAX, Data->Color, PAYOUT_TEXT_X + 0.1, PAYOUT_TEXT_Y + 4 + (8 * (TotalOffset + 1)), 3.0, 2.0);
    
    Delay(35);
    
    ActivatorSound("payout/totaladd", 127);
    SetFont("SMALLFONT");
    HudMessage("%S: %d", Data->Name, Data->Total);
    EndHudMessage(HUDMSG_FADEINOUT, PAYOUT_ID + PAYOUT_VALUES_MAX + Offset + 1, Data->Color, PAYOUT_TOTAL_X + 0.1, PAYOUT_TOTAL_Y + (8 * Offset), 50.0 - (5.0 * Offset), 0.5, 0.5);
    
    Delay(35 * 2);
}

void PayoutCalculateTotals()
{
    Player.Payout.Total.Level += (Player.Payout.XP / 100) +
                                 Player.Payout.Levels +
                                 (Player.Payout.Rank / 100) +
                                 Player.Payout.RankLevels;
}

int PayoutCalculatePPTotal()
{
    return 0;
}
