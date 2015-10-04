#include "RPG.h"

#include "Arena.h"
#include "Augs.h"
#include "Outpost.h"
#include "Map.h"
#include "Shield.h"
#include "Stats.h"
#include "Skills.h"
#include "Utils.h"

AugInfo RPGMap AugData[AUG_MAX] =
{
    // Name, Max Level, Description...
    
    // Augs
    {
        .Name = "Muscle Replacer",
        .MaxLevel = 6,
        .Description =
        {
            "1.25x Damage",
            "1.5x Damage",
            "1.75x Damage",
            "2x Damage",
            "3x Damage",
            "4x Damage"
        },
        .TokenActor = "DRPGAugTokenStrength"
    },
    {
        .Name = "Dermal Armor",
        .MaxLevel = 5,
        .Description =
        {
            "+5% Damage Reduction",
            "+10% Damage Reduction",
            "+15% Damage Reduction",
            "+20% Damage Reduction",
            "+25% Damage Reduction"
        },
        .TokenActor = "DRPGAugTokenDefense"
    },
    {
        .Name = "Pain Inhibitor",
        .MaxLevel = 7,
        .Description =
        {
            "2x Max Health",
            "2x Health Regen",
            "+5% Status Effect Resist",
            "+10% Status Effect Resist",
            "+15% Status Effect Resist",
            "+20% Status Effect Resist",
            "+25% Status Effect Resist"
        },
        .TokenActor = "DRPGAugTokenVitality"
    },
    {
        .Name = "Psi Projector",
        .MaxLevel = 9,
        .Description =
        {
            "2x Max EP",
            "2x EP Regen",
            "2x Aura Timer",
            "2x Aura Range",
            "5% Skill Cost Refund",
            "10% Skill Cost Refund",
            "15% Skill Cost Refund",
            "20% Skill Cost Refund",
            "25% Skill Cost Refund"
        },
        .TokenActor = "DRPGAugTokenEnergy"
    },
    {
        .Name = "Adrenaline Booster",
        .MaxLevel = 8,
        .Description =
        {
            "2x HP/EP Regen Amounts",
            "-2x HP/EP Regen Timers",
            "4x HP/EP Regen Amounts",
            "-4x HP/EP Regen Timers",
            "+5 Second Toxicity Regen Time",
            "+10 Second Toxicity Regen Time",
            "+15 Second Toxicity Regen Time",
            "+20 Second Toxicity Regen Time"
        },
        .TokenActor = "DRPGAugTokenRegen"
    },
    {
        .Name = "Wired Reflexes",
        .MaxLevel = 4,
        .Description =
        {
            "2x Movement Speed",
            "2x Jump Height",
            "Double Weapon Speed",
            "+5% Survival Chance",
            "+10% Survival Chance",
            "+15% Survival Chance",
            "+20% Survival Chance",
            "+25% Survival Chance"
        },
        .TokenActor = "DRPGAugTokenAgility"
    },
    {
        .Name = "Weight Distributor",
        .MaxLevel = 3,
        .Description =
        {
            "2x Ammo Limits",
            "4x Ammo Limits",
            "2x Stim Vial Capacity"
        },
        .TokenActor = "DRPGAugTokenCapacity"
    },
    {
        .Name = "Precognition Unit",
        .MaxLevel = 6,
        .Description =
        {
            "1.25x Luck Drop Chances",
            "1.5x Luck Drop Chances",
            "1.75x Luck Drop Chances",
            "2x Luck Drop Chances",
            "3x Luck Drop Chances",
            "4x Luck Drop Chances"
        },
        .TokenActor = "DRPGAugTokenLuck"
    },
    {
        .Name = "Battery Recharger",
        .MaxLevel = 8,
        .Description =
        {
            "+0.5 Recharge Rate",
            "+1 Recharge Rate",
            "+1.5 Recharge Rate",
            "+2 Recharge Rate",
            "+2.5 Recharge Rate",
            "+3 Recharge Rate",
            "+3.5 Recharge Rate",
            "+4 Recharge Rate"
        },
        .TokenActor = "DRPGAugTokenBattery"
    }
};

NamedScript DECORATE OptionalArgs(1) void DisableAugs(bool NoDrain)
{
    // Disable Augs and give tokens designating which Augs were disabled
    for (int i = 0; i < AUG_MAX; i++)
    {
        if (Player.Augs.Active[i])
        {
            // Disable Aug
            Player.Augs.Active[i] = false;
            SetInventory(AugData[i].TokenActor, Player.Augs.Level[i]);
            
            // Screen fuckery
            SetHudSize(640, 480, false);
            SetFont("AugDView");
            HudMessage("A");
            EndHudMessage(HUDMSG_FADEOUT | HUDMSG_ADDBLEND, 0, "Untranslated", 320.0, 240.0, 3.0, 0.5);
        }
    }
    
    // Reset Aug slots
    Player.Augs.SlotsUsed = 0;
    
    // Halve your current battery amount
    if (!NoDrain)
        Player.Augs.Battery /= 2;
    
    // Disabled sound
    ActivatorSound("aug/disable", 127);
}

NamedScript DECORATE void ReactivateDisabledAugs()
{
    // Check that we *can* activate augs.
    if (Player.StatusType[SE_EMP] || Player.Augs.Battery <= 0)
        return;
    
    for (int i = 0; i < AUG_MAX; i++)
    {
        // If there aren't enough slots left to equip any more augs, then don't try to activate any more.
        if (Player.Augs.SlotsUsed >= Player.Augs.Slots)
            break;
        
        if (CheckInventory(AugData[i].TokenActor) && !Player.Augs.Active[i] && Player.Augs.Level[i] > 0)
            EquipAug(i);
    }
    
    ClearDisabledAugs();
}

void ClearDisabledAugs()
{
    for (int i = 0; i < AUG_MAX; i++)
        TakeInventory(AugData[i].TokenActor, AugData[i].MaxLevel);
}

NamedScript DECORATE void AddBattery(int Amount)
{
    int PrevBattery = Player.Augs.Battery;
    
    Player.Augs.Battery += Amount;
    
    if (Player.Augs.Battery > Player.Augs.BatteryMax)
        Player.Augs.Battery = Player.Augs.BatteryMax;
    
    if (PrevBattery != Player.Augs.Battery)
        DrawBattery();
}

void CheckAugSlots()
{
    Player.Augs.Slots = Player.Augs.BaseSlots + CheckInventory("DRPGAugSlotUpgrade");
    
    // AW-G01 Accessory handling
    if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_AUGSLOT && Player.Shield.Active)
        Player.Augs.Slots++;
    
    // Cap max Aug slots at the max amount of available Augs
    if (Player.Augs.Slots > AUG_MAX) Player.Augs.Slots = AUG_MAX;
    
    // Unequip Augs if you pass the limit (sell a slot upgrade, change difficulty, etc)
    if (Player.Augs.SlotsUsed > Player.Augs.Slots)
        for (int i = AUG_MAX - 1; i >= 0 && Player.Augs.SlotsUsed > Player.Augs.Slots; i--)
            if (Player.Augs.Active[i])
            {
                Player.Augs.Active[i] = false;
                Player.Augs.SlotsUsed--;
                break;
            }
}

void CheckAugs()
{
    // Sanity check to prevent negative slots used
    if (Player.Augs.SlotsUsed < 0)
        Player.Augs.SlotsUsed = 0;
    
    // Determine max Battery
    Player.Augs.BatteryMax = Player.Capacity * 10;
    
    // Play energy drained sound
    if (Player.Augs.Battery <= 0 && Player.Augs.SlotsUsed > 0)
        ActivatorSound("aug/dead", 127);
    
    // Disable Augs if your battery is dead
    if (Player.Augs.Battery <= 0)
    {
        for (int i = 0; i < AUG_MAX; i++)
            if (Player.Augs.Active[i])
                Player.Augs.Active[i] = false;
        
        // Reset the amount of slots used
        Player.Augs.SlotsUsed = 0;
    }
    
    // Battery Handling
    if ((!CurrentLevel->UACBase || ArenaActive || MarinesHostile) && !CheckInventory("PowerTimeFreezer"))
    {
        // Reset drain
        Player.Augs.BatteryDrain = 0;
        
        // Calculate Battery Drain
        for (int i = 0; i < AUG_MAX; i++)
            if (Player.Augs.Active[i] && i != AUG_BATTERY)
                Player.Augs.BatteryDrain += Player.Augs.Level[i];
        
        // Decrease Battery
        if (Player.Augs.SlotsUsed > 0 && (Timer() % 35) == 0)
        {
            Player.Augs.Battery -= (Player.Augs.BatteryDrain / 10);
            DrawBattery();
        }
        
        // Permanently Display battery amount on the HUD if CVAR is set
        if ((Player.Augs.SlotsUsed > 0 && GetActivatorCVar("drpg_aug_alwaysshow")) || GetActivatorCVar("drpg_hud_preview"))
            DrawBattery();
    }
    
    // Sanity check to prevent battery from going negative
    if (Player.Augs.Battery < 0)
        Player.Augs.Battery = 0;

    // Sanity check to prevent Battery from exceeding max amount
    if (Player.Augs.Battery > Player.Augs.BatteryMax)
        Player.Augs.Battery = Player.Augs.BatteryMax;
    
    // Battery Recharging
    if ((!CurrentLevel->UACBase || ArenaActive || MarinesHostile) && Player.Augs.Active[AUG_BATTERY] && Player.Augs.Battery < Player.Augs.BatteryMax)
        if ((Timer() % 35) == 0 && !IsPlayerMoving())
        {
            Player.Augs.Battery += (fixed)Player.Augs.Level[AUG_BATTERY] / 2.0;
            DrawBattery();
        }
    
    // Strength Aug
    if (Player.Augs.Active[AUG_STRENGTH])
    {
        if (Player.Augs.Level[AUG_STRENGTH] == 1)
            Player.DamageMult += 1.25;
        if (Player.Augs.Level[AUG_STRENGTH] == 2)
            Player.DamageMult += 1.5;
        if (Player.Augs.Level[AUG_STRENGTH] == 3)
            Player.DamageMult += 1.75;
        if (Player.Augs.Level[AUG_STRENGTH] == 4)
            Player.DamageMult += 2;
        if (Player.Augs.Level[AUG_STRENGTH] == 5)
            Player.DamageMult += 3;
        if (Player.Augs.Level[AUG_STRENGTH] >= 6)
            Player.DamageMult += 4;
    }
    
    // Defense Aug
    if (Player.Augs.Active[AUG_DEFENSE])
        Player.DamageFactor -= (fixed)Player.Augs.Level[AUG_DEFENSE] / 20.0;
    
    // Vitality Aug
    if (Player.Augs.Active[AUG_VITALITY])
    {
        if (Player.Augs.Level[AUG_VITALITY] >= 1)
            Player.HealthMax *= 2;
        if (Player.Augs.Level[AUG_VITALITY] >= 2)
            Player.HPAmount *= 2;
        if (Player.Augs.Level[AUG_VITALITY] == 3)
            Player.StatusEffectResist += 5;
        if (Player.Augs.Level[AUG_VITALITY] == 4)
            Player.StatusEffectResist += 10;
        if (Player.Augs.Level[AUG_VITALITY] == 5)
            Player.StatusEffectResist += 15;
        if (Player.Augs.Level[AUG_VITALITY] == 6)
            Player.StatusEffectResist += 20;
        if (Player.Augs.Level[AUG_VITALITY] >= 7)
            Player.StatusEffectResist += 25;
    }
    
    // Energy Aug
    if (Player.Augs.Active[AUG_ENERGY])
    {
        if (Player.Augs.Level[AUG_ENERGY] >= 1)
            Player.EPMax *= 2;
        if (Player.Augs.Level[AUG_ENERGY] >= 2)
            Player.EPAmount *= 2;
        if (Player.Augs.Level[AUG_ENERGY] >= 3)
            Player.AuraBonus = true;
        else
            Player.AuraBonus = false;
        if (Player.Augs.Level[AUG_ENERGY] >= 4)
            Player.Aura.Range *= 2;
    }
    
    // Regeneration Aug
    if (Player.Augs.Active[AUG_REGENERATION])
    {
        if (Player.Augs.Level[AUG_REGENERATION] >= 1)
        {
            Player.HPAmount *= 2;
            Player.EPAmount *= 2;
        }
        if (Player.Augs.Level[AUG_REGENERATION] >= 2)
        {
            Player.HPTime /= 2;
            Player.EPTime /= 2;
        }
        if (Player.Augs.Level[AUG_REGENERATION] >= 3)
        {
            Player.HPAmount *= 2;
            Player.EPAmount *= 2;
        }
        if (Player.Augs.Level[AUG_REGENERATION] >= 4)
        {
            Player.HPTime /= 2;
            Player.EPTime /= 2;
        }
        if (Player.Augs.Level[AUG_REGENERATION] == 5)
            Player.ToxicityRegenBonus += 5;
        if (Player.Augs.Level[AUG_REGENERATION] == 6)
            Player.ToxicityRegenBonus += 10;
        if (Player.Augs.Level[AUG_REGENERATION] == 7)
            Player.ToxicityRegenBonus += 15;
        if (Player.Augs.Level[AUG_REGENERATION] >= 8)
            Player.ToxicityRegenBonus += 20;
    }

    // Agility Aug
    if (Player.Augs.Active[AUG_AGILITY])
    {
        if (Player.Augs.Level[AUG_AGILITY] >= 1)
            Player.Speed *= 2;
        if (Player.Augs.Level[AUG_AGILITY] >= 2)
            Player.JumpHeight *= 2;
        if (Player.Augs.Level[AUG_AGILITY] >= 3)
            Player.WeaponSpeed = 100;
        if (Player.Augs.Level[AUG_AGILITY] == 4)
            Player.SurvivalBonus += 5;
        if (Player.Augs.Level[AUG_AGILITY] == 5)
            Player.SurvivalBonus += 10;
        if (Player.Augs.Level[AUG_AGILITY] == 6)
            Player.SurvivalBonus += 15;
        if (Player.Augs.Level[AUG_AGILITY] == 7)
            Player.SurvivalBonus += 20;
        if (Player.Augs.Level[AUG_AGILITY] >= 8)
            Player.SurvivalBonus += 25;
    }
    
    // Capacity Aug
    if (Player.Augs.Active[AUG_CAPACITY])
    {
        int AmmoMult;
        
        if (Player.Augs.Level[AUG_CAPACITY] == 1)
            AmmoMult = 2;
        if (Player.Augs.Level[AUG_CAPACITY] >= 2)
            AmmoMult = 4;
        if (Player.Augs.Level[AUG_CAPACITY] >= 3)
            Player.Stim.VialMax *= 2;
        
        SetAmmoCapacity("Clip", Player.Capacity * 20 * AmmoMult);
        SetAmmoCapacity("Shell", Player.Capacity * 5 * AmmoMult);
        SetAmmoCapacity("RocketAmmo", Player.Capacity * 5 * AmmoMult);
        SetAmmoCapacity("Cell", Player.Capacity * 30 * AmmoMult);
    }

    // Luck Aug
    if (Player.Augs.Active[AUG_LUCK])
    {
        fixed LuckMult;
        
        if (Player.Augs.Level[AUG_LUCK] == 1)
            LuckMult = 1.25;
        if (Player.Augs.Level[AUG_LUCK] == 2)
            LuckMult = 1.5;
        if (Player.Augs.Level[AUG_LUCK] == 3)
            LuckMult = 1.75;
        if (Player.Augs.Level[AUG_LUCK] == 4)
            LuckMult = 2;
        if (Player.Augs.Level[AUG_LUCK] == 5)
            LuckMult = 3;
        if (Player.Augs.Level[AUG_LUCK] >= 6)
            LuckMult = 4;
        
        Player.HealthChance *= LuckMult;
        Player.EPChance *= LuckMult;
        Player.ArmorChance *= LuckMult;
        Player.WeaponChance *= LuckMult;
        Player.PowerupChance *= LuckMult;
        Player.ModuleChance *= LuckMult;
        Player.AugChance *= LuckMult;
        Player.ShieldChance *= LuckMult;
        Player.StimChance *= LuckMult;
    }
}

void AugDamage(int Amount)
{
    // Lightning damage type increases your Battery
    if (Player.DamageType == DT_LIGHTNING && Amount / 5 > 0)
        AddBattery(Amount / 5);
}

void EquipAug(int Aug)
{
    // If you don't have this aug yet, return
    if (Player.Augs.Level[Aug] == 0)
    {
        PrintError("This aug has not been activated yet");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    // If battery is dead, return
    if (Player.Augs.Battery <= 0)
    {
        PrintError("Your aug battery is depleted");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (Player.Augs.Level[Aug] > 0)
    {
        if (Player.Augs.Active[Aug])
        {
            ActivatorSound("aug/equip", 127);
            Player.Augs.SlotsUsed--;
            Player.Augs.Active[Aug] = false;
        }
        else
        {
            Player.Augs.SlotsUsed++;
            
            if (Player.Augs.SlotsUsed > Player.Augs.Slots)
            {
                PrintError("You are already using all of your aug slots");
                ActivatorSound("menu/error", 127);
                Player.Augs.SlotsUsed--;
            }
            else
            {
                ActivatorSound("aug/equip", 127);
                Player.Augs.Active[Aug] = true;
            }
        }
    }
}

void LevelUpAug(int AugIndex)
{
    if (Player.Augs.Level[AugIndex] < AugData[AugIndex].MaxLevel)
    {
        bool CanLevel = true;
        
        if (Player.Augs.Level[AugIndex] == 0)
        {
            if (CheckInventory("DRPGAugCanister"))
            {
                ActivatorSound("aug/levelup", 127);
                TakeInventory("DRPGAugCanister", 1);
            }
            else
                CanLevel = false;
        }
        else 
        {
            if (CheckInventory("DRPGAugCanister") && CheckInventory("DRPGAugUpgradeCanister") >= Player.Augs.Level[AugIndex] + 1)
            {
                ActivatorSound("aug/levelup", 127);
                TakeInventory("DRPGAugCanister", 1);
                TakeInventory("DRPGAugUpgradeCanister", Player.Augs.Level[AugIndex] + 1);
            }
            else
                CanLevel = false;
        }
        
        if (!CanLevel)
        {
            PrintError("You cannot upgrade this aug");
            ActivatorSound("menu/error", 127);
            return;
        }
        
        Player.Augs.Level[AugIndex]++;
    }
}
