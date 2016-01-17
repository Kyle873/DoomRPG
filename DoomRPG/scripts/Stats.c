#include "Defs.h"

#include "RPG.h"
#include "Utils.h"
#include "ItemData.h"
#include "Shield.h"
#include "Map.h"
#include "Arena.h"
#include "Outpost.h"
#include "Skills.h"
#include "Augs.h"

// Globals
long long int XPCurve;

// Stat Caps
int const SoftStatCap = 100;
int const HardStatCap = 1000;

// XP & Rank Tables
long long int XPTable[MAX_LEVEL];
long long int RealStatTable[MAX_LEVEL * 3 + 1];
long long int *StatTable;
long long int RankTable[MAX_RANK];

// Rank strings
str const Ranks[MAX_RANK + 1] =
{
    "Rec",
    "Pvt", "Pvt +",
    "PFC", "PFC +",
    "LCpl", "LCpl +",
    "Cpl", "Cpl +",
    "Sgt", "Sgt +",
    "SSgt", "SSgt +",
    "GySgt", "GySgt +",
    "MSgt", "MSgt +",
    "1stSgt", "1stSgt +",
    "MGySgt", "MGySgt +",
    "SgtMaj", "SgtMaj +",
    "SgtMajMarCor", "MSgtMarCor"
};

str const LongRanks[MAX_RANK + 1] =
{
    "Recruit",
    "Private", "Private +",
    "Private First Class", "Private First Class +",
    "Lance Corporal", "Lance Corporal +",
    "Corporal", "Corporal +",
    "Sergeant", "Sergeant +",
    "Staff Sergeant", "Staff Sergeant +",
    "Gunnery Sergeant", "Gunnery Sergeant +",
    "Master Sergeant", "Master Sergeant +",
    "First Sergeant", "First Sergeant +",
    "Master Gunnery Sergeant", "Master Gunnery Sergeant +",
    "Sergeant Major", "Sergeant Major +",
    "Sergeant Major of the Marine Corps", "Master Sergeant Major of the Marine Corps",
};

NamedScript DECORATE void StatusEffect(int Type, int Time, int Intensity)
{
    // Can't get Status Effects if Pink Aura is active
    if (Player.Aura.Type[AURA_PINK].Active || Player.SoulActive[SOUL_PINK]) return;
    
    if (Intensity <= 0)
        Intensity = 1;
    
    if (Player.StatusType[Type])
    {
        if (Intensity > Player.StatusIntensity[Type])
            Player.StatusIntensity[Type] = Intensity;
        
        Player.StatusTimer[Type] += Time * 35;
        
        if (Player.StatusTimer[Type] > Player.StatusTimerMax[Type])
            Player.StatusTimerMax[Type] = Player.StatusTimer[Type];
    }
    else
    {
        Player.StatusType[Type] = true;
        Player.StatusIntensity[Type] = Intensity;
        Player.StatusTimer[Type] = Time * 35;
        Player.StatusTimerMax[Type] = Player.StatusTimer[Type];
    }
}

NamedScript DECORATE void TryStatusEffect(int Type, int Time, int Intensity)
{
    // Can't get Status Effects if Pink Aura is active
    if (Player.Aura.Type[AURA_PINK].Active || Player.SoulActive[SOUL_PINK]) return;
    
    // Status Effect Resist check
    if (RandomFixed(0.0, 100.0) <= Player.StatusEffectResist)
        ActivatorSound("health/statuseffect2", 127);
    else // Apply status effect
    {
        ActivatorSound("health/statuseffect", 127);
        Player.StatusTypeHUD = Type;
        StatusEffect(Type, Time, Intensity);
    }
}

NamedScript void AddXP(int PlayerNum, long long int XP, long long int Rank)
{
    // Scale XP/Rank Gains using the XP Scaling Option
    XP = (int)(XP * GetCVarFixed("drpg_scalexp"));
    
    Players(PlayerNum).ComboTimer = COMBO_MAX;
    Players(PlayerNum).Combo++;
    
    Players(PlayerNum).XPGained += XP;
    Players(PlayerNum).RankGained += Rank;
    
    if (Players(PlayerNum).Aura.Type[AURA_WHITE].Active)
    {
        if (Players(PlayerNum).Aura.Time > 0)
            Players(PlayerNum).Combo++;
        if (Player.Aura.Type[AURA_WHITE].Level >= 3 && XP > 0 && Rank > 0)
            Players(PlayerNum).BonusGained += XP + Rank;
    }
}

NamedScript Console void PrintXPTable()
{
    for (int i = 0; i < MAX_LEVEL; i++)
    {
        Log("Level %d: %lld", i + 1, XPTable[i]);
        Delay(1);
    }
}

void InitXPTable()
{
    XPTable[0] = 200l + XPCurve;
    for (int i = 1; i < MAX_LEVEL; i++)
        XPTable[i] = ((XPTable[i - 1] / 2000l) + 1l) * (200l + XPCurve) + XPTable[i - 1];
}

void InitStatXPTable()
{
    StatTable = &RealStatTable[101];

    StatTable[0] = 200 + XPCurve;
    for (int i = 1; i < MAX_LEVEL * 2; i++)
        StatTable[i] = ((StatTable[i - 1] / 2000l) + 1l) * (200l + XPCurve) + StatTable[i - 1];
}

void InitNegativeStatXPTable()
{
    for (int i = 1; i <= MAX_LEVEL + 1; i++)
        StatTable[-i] = ((StatTable[i - 1] / 2000l) + 1l) * (200l + XPCurve) + StatTable[i - 1] * -1l;
}

void InitRankTable()
{
    RankTable[0] = 7500 + (XPCurve * 50);
    for (int i = 1; i < MAX_RANK; i++)
        RankTable[i] = ((RankTable[i - 1] / 20000l) + 1l) * (7500l + (XPCurve * 50l)) + RankTable[i - 1];
}

void CheckCombo()
{
    // Time Freeze special handling
    if (Player.Combo > 0 && (CheckInventory("PowerTimeFreezer") || CheckInventory("DRPGPowerStimChrono")) && Player.ComboTimer >= COMBO_MAX)
        Player.ComboTimer = COMBO_MAX - 1;
    
    // Subtract the combo timer each tic
    if ((Player.Combo > 0 || Player.ComboTimer < COMBO_MAX) && !CheckInventory("PowerTimeFreezer") && !CheckInventory("DRPGPowerStimChrono"))
        Player.ComboTimer--;
    
    // Reset values if you start the combo again while it was cooling down
    if (Player.ComboTimer == COMBO_MAX)
    {
        Player.BonusGained = 0;
        Player.XPGained = 0;
        Player.RankGained = 0;
    }
    
    // Add up and randomize the XP and Rank gain
    if (Player.ComboTimer == COMBO_STOP || (Player.Aura.Type[AURA_WHITE].Active && Player.Aura.Type[AURA_WHITE].Level >= 2 && Timer() == 4))
    {
        long int ComboBonus = ((Player.XPGained + Player.RankGained) / 100 * Player.Combo);
        
        // You cannot gain Negative XP, but you can lose Rank
        if (Player.XPGained < 0) Player.XPGained = 0;
        
        if (Player.Combo > 1)
        {
            Player.BonusGained += ComboBonus;
            Player.XP += Player.XPGained + ComboBonus;
            Player.Rank += Player.RankGained + ComboBonus;
        }
        else
        {
            Player.XP += Player.XPGained;
            Player.Rank += Player.RankGained;
        }
        
        Player.XPGained = 0;
        Player.RankGained = 0;
    }
    
    if (Player.ComboTimer < 0)
    {
        Player.Combo = 0;
        Player.ComboTimer = COMBO_MAX;
        Player.BonusGained = 0;
        Player.XPGained = 0;
        Player.RankGained = 0;
    }
}

// Keeps current level and XP updated
void CheckLevel()
{
    if (Player.Level < MAX_LEVEL)
        Player.XPNext = XPTable[Player.Level];
    
    if (Player.Level >= MAX_LEVEL)
    {
        Player.XP = XPTable[MAX_LEVEL - 1];
        Player.XPNext = XPTable[MAX_LEVEL - 1];
    }
    
    // Now check for a level up
    if (Player.XP >= XPTable[Player.Level] && Player.Level < MAX_LEVEL)
    {
        int Modules = (int)((((fixed)Player.Level + 1) * 100.0) * GetCVarFixed("drpg_module_levelfactor"));
        
        // Level Up
        Player.Level++;
        GiveInventory("DRPGModule", Modules);
        
        if (GetCVar("drpg_levelup_heal"))
        {
            HealThing(SHIELD_HEALTH);
            
            if (Player.EP < 0)
                Player.EP = 0;
            else
                Player.EP = Player.EPMax;
        }
        
        FadeRange(255, 255, 255, 0.5, 255, 255, 255, 0, 2.0);
        PrintMessage(StrParam("You have reached level %d", Player.Level), LEVELUP_ID, -32);
        
        ActivatorSound("misc/levelup", 96);
        SpawnForced("DRPGLevelUpArrow", GetActorX(0), GetActorY(0), GetActorZ(0) + GetActorPropertyFixed(Player.TID, APROP_Height), 0, 0);
    }
}

// Keeps current Rank updated
void CheckRank()
{
    Player.RankString = Ranks[Player.RankLevel];
    
    if (Player.RankLevel < MAX_RANK)
        Player.RankNext = RankTable[Player.RankLevel];
    
    if (Player.RankLevel >= MAX_RANK)
    {
        Player.Rank = RankTable[MAX_RANK - 1];
        Player.RankNext = RankTable[MAX_RANK - 1];
    }
    
    // Rank Demotion
    if (Player.RankLevel > 0 && Player.Rank < RankTable[Player.RankLevel - 1])
    {
        Player.RankLevel--;
        FadeRange(255, 0, 64, 0.25, 255, 0, 64, 0, 2.0);
        
        PrintMessage(StrParam("\CaYou have been demoted to rank %d: %S", Player.RankLevel, LongRanks[Player.RankLevel]), RANKUP_ID, 32);
    }
    
    // Rank Promotion
    if (Player.Rank >= RankTable[Player.RankLevel] && Player.RankLevel < MAX_RANK)
    {
        int NewItems;
        
        Player.RankLevel++;

        ActivatorSound("misc/rankup", 96);
        FadeRange(255, 255, 0, 0.5, 255, 255, 0, 0, 2.0);
        
        // Determine how many new items you've unlocked in the shop
        for (int i = 0; i < ItemCategories; i++)
            for (int j = 0; j < ItemMax[i]; j++)
                if (ItemData[i][j].Rank == Player.RankLevel)
                    NewItems++;
        
        PrintMessage(StrParam("\CkYou have been promoted to rank %d: %S", Player.RankLevel, LongRanks[Player.RankLevel]), RANKUP_ID, 32);
        
        SpawnForced("DRPGRankUpArrow", GetActorX(0), GetActorY(0), GetActorZ(0) + GetActorPropertyFixed(Player.TID, APROP_Height), 0, 0);
        
        // Tells you if you've unlocked new items in the Shop
        if (NewItems > 0)
            PrintMessage(StrParam("\CcYou have unlocked \Cf%d\Cc new items in the shop", NewItems), RANKUP_ID + 1, 96);
    }
    
    // Payment
    if (!CheckInventory("PowerTimeFreezer"))
        Player.PayTimer--;
    if (Player.PayTimer <= 0)
    {
        if (Player.RankLevel > 0)
        {
            int Pay = CalculatePay();
            
            GiveInventory("DRPGCredits", Pay);
            
            FadeRange(0, 255, 0, 0.1, 0, 255, 0, 0, 2.0);
            ActivatorSound("credits/payout", 127);
            if (InMultiplayer && Arbitrator && PlayerCount() > 1)
                Log("\CfYour group has been paid by the UAC");
            else if (!InMultiplayer)
                Log("\CfYou have been paid %d Credits by the UAC", Pay);
        }
        
        Player.PayTimer = 35 * 60 * GetCVar("drpg_pay_interval");
        Player.PayKills = 0;
        Player.PayBonus++;
        
        // Cap Pay Bonus
        if (Player.PayBonus > 1000)
            Player.PayBonus = 1000;
    }
}

void CheckHealth()
{
    // If you're dead, return
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    // Over-Heal behavior
    if (Player.OverHeal)
    {
        if ((Timer() % 35) == 0)
            Player.ActualHealth--;
        if (Player.ActualHealth <= Player.HealthMax)
            Player.OverHeal = false;
    }
    
    // < 10% Health
    if (Player.ActualHealth <= Player.HealthMax / 10 && !Player.Perks[STAT_VITALITY])
    {
        // Fade Effect
        FadeRange(255, 0, 0, 0.15 + (Sin(Timer() / 64.0) * 0.1), 255, 0, 0, 0.0, 1.0);
        
        // Heartbeat
        if ((Timer() % 64) == 0 && Player.ActualHealth > 0)
            ActivatorSound("health/low", 64);
        
        // Halve Movement Speed and Jump Height
        Player.Speed /= 2;
        Player.JumpHeight /= 2;
    }
}

void CheckStats()
{
    // VERY IMPORTANT CODE RIGHT HERE
    // If you're reading this and you'd like to modify stat curves, this is where you'd do it
    Player.LevelDamage = Player.Level * (10 - GameSkill());
    Player.BonusDamage = Player.Strength;
    Player.DamageMult = 0;
    Player.TotalDamage = Player.LevelDamage + Player.BonusDamage;
    if (Player.Defense > 0)
        Player.DamageFactor = (Player.Defense > 200 ? 0.25 : 1.0 - Curve((fixed)Player.Defense, 0, 200, 0.01, 0.75));
    else
        Player.DamageFactor = 1.0 + AbsFixed(((fixed)Player.Defense / 100.0));
    Player.Mass = 100 + (Player.Defense * 10);
	Player.HealthMax = Player.Vitality * 10;
    Player.StatusEffectResist = (fixed)Player.Vitality / 4.0;
    Player.EPMax = Player.Energy * 10;
    Player.Aura.Range = Player.Energy * 16;
    Player.ToxicityRegenBonus = Player.Regeneration / 10;
    Player.Speed = 1.0 + 0.25 * ((fixed)Player.Agility / 100);
    Player.JumpHeight = 8.0 + (8.0 * ((fixed)Player.Agility / 100));
    Player.WeaponSpeed = Player.Agility;
    SetAmmoCapacity("Clip", Player.Capacity * 20);
    SetAmmoCapacity("Shell", Player.Capacity * 5);
    SetAmmoCapacity("RocketAmmo", Player.Capacity * 5);
    SetAmmoCapacity("Cell", Player.Capacity * 30);
    Player.Stim.VialMax = Player.Capacity * 10;
    Player.SurvivalBonus = (fixed)Player.Agility / 10.0;
    if (CompatMode == COMPAT_DRLA) // DRLA - Total Armors/Boots, Skulls
    {
        SetAmmoCapacity("RLArmorInInventory", DRLA_ARMOR_MAX);
        SetAmmoCapacity("RLSkullLimit", DRLA_SKULL_MAX);
        SetAmmoCapacity("RLPhaseDeviceLimit", DRLA_DEVICE_MAX);
    }
    
    // Determine current stat cap
    Player.StatCap = SoftStatCap + Player.Level;
    
    // Per-stat leveling
    if (GetCVar("drpg_levelup_natural"))
    {
        if (Player.StrengthXP >= StatTable[Player.Strength] && Player.Strength < Player.StatCap)
        {
            Player.Strength++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_STRENGTH);
        }
        
        if (Player.DefenseXP >= StatTable[Player.Defense] && Player.Defense < Player.StatCap)
        {
            Player.Defense++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_DEFENSE);
        }
        
        if (Player.VitalityXP >= StatTable[Player.Vitality] && Player.Vitality < Player.StatCap)
        {
            Player.Vitality++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_VITALITY);
        }
        
        if (Player.EnergyXP >= StatTable[Player.Energy] && Player.Energy < Player.StatCap)
        {
            Player.Energy++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_ENERGY);
        }
        
        if (Player.RegenerationXP >= StatTable[Player.Regeneration] && Player.Regeneration < Player.StatCap)
        {
            Player.Regeneration++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_REGENERATION);
        }
        
        if (Player.AgilityXP >= StatTable[Player.Agility] && Player.Agility < Player.StatCap)
        {
            Player.Agility++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_AGILITY);
        }
        
        if (Player.CapacityXP >= StatTable[Player.Capacity] && Player.Capacity < Player.StatCap)
        {
            Player.Capacity++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_CAPACITY);
        }
        
        if (Player.LuckXP >= StatTable[Player.Luck] && Player.Luck < Player.StatCap)
        {
            Player.Luck++;
            ActivatorSound("misc/statup", 127);
            DrawStatUp(STAT_LUCK);
        }
        
        // Add Regeneration XP for having low Health and/or EP
        if ((Player.ActualHealth < Player.HealthMax || Player.EP < Player.EPMax || Player.Focusing) && !Player.Stim.Active)
        {
            if (Timer() % 7 == 0)
            {
                fixed Scale = GetCVarFixed("drpg_regeneration_scalexp");
                if (GetCVar("drpg_allow_spec"))
                {
                    if (GetActivatorCVar("drpg_character_spec") == 5)
                        Scale *= 2;
                }
                fixed Factor = 2.0 - AbsFixed(((Player.ActualHealth <= Player.HealthMax ? ((fixed)Player.ActualHealth / (fixed)Player.HealthMax) : 1.0) + (Player.EPMax > 0 ? ((fixed)Player.EP / Player.EPMax) : 0)));
                Factor += Player.Focusing ? 1 : 0;
                Player.RegenerationXP += (int)(Factor * (8.25 * Scale));
            }
        }
        
        // Add Defense XP for decreases in Health
        if (Player.PrevHealth != Player.ActualHealth && !Player.Stim.Active)
        {
            if (Player.ActualHealth < Player.PrevHealth)
            {
                fixed Scale = GetCVarFixed("drpg_defense_scalexp");
                if (GetCVar("drpg_allow_spec"))
                {
                    if (GetActivatorCVar("drpg_character_spec") == 2)
                        Scale *= 2;
                }
                int Factor = Player.PrevHealth - Player.ActualHealth;
                Player.DefenseXP += (int)(Factor * (11.25 * Scale));
            }
            
            Player.PrevHealth = Player.ActualHealth;
        }
        
        // Add Luck XP for increases in Credits
        if (Player.PrevCredits != CheckInventory("DRPGCredits") && !Player.Stim.Active)
        {
            if (CheckInventory("DRPGCredits") > Player.PrevCredits)
            {
                fixed Scale = GetCVarFixed("drpg_luck_scalexp");
                if (GetCVar("drpg_allow_spec"))
                {
                    if (GetActivatorCVar("drpg_character_spec") == 8)
                        Scale *= 2;
                }
                Player.LuckXP += (int)((CheckInventory("DRPGCredits") - Player.PrevCredits) * (2.25 * Scale));
            }
                
            Player.PrevCredits = CheckInventory("DRPGCredits");
        }
        
        // Add Agility XP for maintaining high X/Y velocity
        fixed Velocity = AbsFixed(GetActorVelX(0)) + AbsFixed(GetActorVelY(0));
        if (Timer() % 7 == 0 && !Player.Stim.Active)
        {
            fixed Scale = GetCVarFixed("drpg_agility_scalexp");
            if (GetCVar("drpg_allow_spec"))
            {
                if (GetActivatorCVar("drpg_character_spec") == 6)
                    Scale *= 2;
            }
            Player.AgilityXP += (int)(Velocity * (0.333 * Scale));
        }
    }
    
    // Scale Health with Vitality changes
    if (Player.PrevVitality != Player.Vitality)
    {
        if (Player.ActualHealth <= Player.HealthMax)
        {
            int HealthMax = Player.Vitality * 10;
            fixed Ratio = ((fixed)Player.ActualHealth + 0.5) / ((fixed)Player.PrevVitality * 10);
            Player.ActualHealth = Ratio * HealthMax;
        }
        
        Player.PrevVitality = Player.Vitality;
    }
	
    // Scale EP with Energy changes
    if (Player.PrevEnergy != Player.Energy && Player.EP > 0)
    {
        if (Player.EP <= Player.EPMax)
        {
            int EPMax = Player.Energy * 10;
            fixed Ratio = ((fixed)Player.EP + 0.5) / ((fixed)Player.PrevEnergy * 10);
            Player.EP = Ratio * EPMax;
        }
        
        Player.PrevEnergy = Player.Energy;
    }
    
    // Status Effect Checking
    if (Player.StatusType[SE_FATIGUE]) // Fatigue
    {
        Player.Speed = Player.Speed * (1.0 / ((fixed)Player.StatusIntensity[SE_FATIGUE] + 1));
        Player.JumpHeight = Player.JumpHeight * (1.0 / ((fixed)Player.StatusIntensity[SE_FATIGUE] + 1));
        
        if (Player.StatusIntensity[SE_FATIGUE] > 3)
            SetMugShotState("Rampage");
    }
    
    // DRLA Checking
    if (CheckInventory("RLTacticalBootsToken"))
        Player.SurvivalBonus += 20.0;
}

void CheckStatBonus()
{
    Player.Strength += Player.StrengthBonus;
    Player.Defense += Player.DefenseBonus;
    Player.Vitality += Player.VitalityBonus;
    Player.Energy += Player.EnergyBonus;
    Player.Regeneration += Player.RegenerationBonus;
    Player.Agility += Player.AgilityBonus;
    Player.Capacity += Player.CapacityBonus;
    Player.Luck += Player.LuckBonus;
    
    Player.StrengthBonus = 0;
    Player.DefenseBonus = 0;
    Player.VitalityBonus = 0;
    Player.EnergyBonus = 0;
    Player.RegenerationBonus = 0;
    Player.AgilityBonus = 0;
    Player.CapacityBonus = 0;
    Player.LuckBonus = 0;
}

void CheckRegen()
{
    // Determine the max timer amounts
    Player.HPTime = (int)(350k - ((fixed)Player.Regeneration * 1.575k) - ((fixed)Player.AgilityTimer * 0.5k) * 2k);
    Player.EPTime = (int)(350k - ((fixed)Player.Regeneration * 1.575k) - ((fixed)Player.AgilityTimer * 0.5k) * 2k);
    
    // Cap Times
    if (Player.HPTime < 35)
        Player.HPTime = 35;
    if (Player.EPTime < 35)
        Player.EPTime = 35;
    
    // Determine the max regen amounts
    Player.HPAmount = 1 + Player.Vitality / 50;
    Player.EPAmount = 1 + Player.Energy / 50;
}

// Regeneration
void DoRegen()
{
    int HPAmount = 1;
    int EPAmount = 1;
    int Overflow = 0;
    
    // HP Regen
    if (Player.HPRate >= Player.HPTime && ClassifyActor(Player.TID) & ACTOR_ALIVE)
        HealThing(Player.HPAmount);
    
    // EP Regen
    if (Player.EPRate >= Player.EPTime && Player.EP < Player.EPMax)
    {
        Player.EP += Player.EPAmount;
        Overflow = 0;
        
        if (Player.EP > Player.EPMax)
        {
            Overflow = Player.EP - Player.EPMax;
            Player.EP = Player.EPMax;
        }
        
        if (Player.Shield.Active && Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_EPOVERFLOW)
        {
            HealThing(Overflow);
            Player.Shield.Charge += Overflow;
        }
    }
    
    // Check and Reset timers
    if (Player.HPRate >= Player.HPTime)
        Player.HPRate = 0;
    if (Player.EPRate >= Player.EPTime)
        Player.EPRate = 0;
    
    // Now increment the timers
    int Buttons = GetPlayerInput(PlayerNumber(), MODINPUT_BUTTONS);
    
    // Regen Boost
    if (Player.RegenBoostTimer > 0)
    {
        fixed X = GetActorX(0);
        fixed Y = GetActorY(0);
        fixed Z = GetActorZ(0);
        int Angle = GetActorAngle(0) * 256;
        SpawnForced("DRPGRegenSphereEffect", X, Y, Z + 32.0, AuraTID, Angle);
        
        Player.HPRate += Player.RegenBoostTimer / (GameSkill() * GameSkill());
        Player.EPRate += Player.RegenBoostTimer / (GameSkill() * GameSkill());
        Player.RegenBoostTimer--;
        
        // Pass Radius and Height to the Auras for DECORATE usage
        SetUserVariable(AuraTID, "user_radius", (int)GetActorPropertyFixed(Player.TID, APROP_Radius));
        SetUserVariable(AuraTID, "user_height", (int)GetActorPropertyFixed(Player.TID, APROP_Height));
        Thing_ChangeTID(AuraTID, 0);
    }
    
    // Regeneration Perk - Exponentially increase Health/Energy regeneration rates up to 4x as they lower
    if (Player.Perks[STAT_REGENERATION])
    {
        // Health
        fixed Health = Player.ActualHealth;
        fixed MaxHealth = Player.HealthMax;
        
        fixed Multiplier = (1.0 - ((fixed)Health / (fixed)MaxHealth)) * 1.77;
        HPAmount += Multiplier * Multiplier;
        
        // EP
        fixed EP = Abs(Player.EP);
        fixed MaxEP = Player.EPMax;
        
        fixed Multiplier = (1.0 - ((fixed)EP / (fixed)MaxEP)) * 1.77;
        EPAmount += Multiplier * Multiplier;
    }
    
    // Movement/Crouching/Idling mechanics
    if (GetCVar("drpg_regen_movement"))
    {
        if (IsPlayerMoving()) // Movement - 50% Regen Rate
        {
            Player.HPRate += HPAmount;
            Player.EPRate += EPAmount;
        }
        else if (Buttons & BT_CROUCH) // Crouch - 150% Regen Rate
        {
            Player.HPRate += HPAmount + 3;
            Player.EPRate += EPAmount + 3;
        }
        else // Idle - 100% Regen Rate
        {
            Player.HPRate += HPAmount + 2;
            Player.EPRate += EPAmount + 2;
        }
    }
    else
    {
        Player.HPRate += HPAmount;
        Player.EPRate += EPAmount;
    }
}

void ResetRegen()
{
    // If damaged, reset the Healing timer
    Player.HPRate = 0;
}

// Keep stats capped at certain values
void CheckStatCaps()
{
    // Current Cap (Soft + level)
    if (Player.Strength > Player.StatCap)       Player.Strength = Player.StatCap;
    if (Player.Defense > Player.StatCap)        Player.Defense = Player.StatCap;
    if (Player.Vitality > Player.StatCap)       Player.Vitality = Player.StatCap;
    if (Player.Energy > Player.StatCap)         Player.Energy = Player.StatCap;
    if (Player.Regeneration > Player.StatCap)   Player.Regeneration = Player.StatCap;
    if (Player.Agility > Player.StatCap)        Player.Agility = Player.StatCap;
    if (Player.Capacity > Player.StatCap)       Player.Capacity = Player.StatCap;
    if (Player.Luck > Player.StatCap)           Player.Luck = Player.StatCap;
    
    // Negative Cap
    if (Player.Strength < -100)                 Player.Strength = -100;
    if (Player.Defense < -100)                  Player.Defense = -100;
    if (Player.Vitality < -100)                 Player.Vitality = -100;
    if (Player.Energy < -100)                   Player.Energy = -100;
    if (Player.Regeneration < -100)             Player.Regeneration = -100;
    if (Player.Agility < -100)                  Player.Agility = -100;
    if (Player.Capacity < -100)                 Player.Capacity = -100;
    if (Player.Luck < -100)                     Player.Luck = -100;
}

// Keep stats capped at the hard value
void CheckHardStatCaps()
{
    if (Player.Strength > HardStatCap)      Player.Strength = HardStatCap;
    if (Player.Defense > HardStatCap)       Player.Defense = HardStatCap;
    if (Player.Vitality > HardStatCap)      Player.Vitality = HardStatCap;
    if (Player.Energy > HardStatCap)        Player.Energy = HardStatCap;
    if (Player.Regeneration > HardStatCap)  Player.Regeneration = HardStatCap;
    if (Player.Agility > HardStatCap)       Player.Agility = HardStatCap;
    if (Player.Capacity > HardStatCap)      Player.Capacity = HardStatCap;
    if (Player.Luck > HardStatCap)          Player.Luck = HardStatCap;
}

void CheckStatBounds()
{
    // Cap Defense/DamageFactor
    if (Player.DamageFactor < 0.1k)
        Player.DamageFactor = 0.1k;
    
    // Prevent Mass from underflowing
    if (Player.Mass < 0k)
        Player.Mass = 0k;
    
    // Cap the max regen timer amounts to 1 second
    if (Player.HPTime < 35k)
        Player.HPTime = 35k;
    if (Player.EPTime < 35k)
        Player.EPTime = 35k;
    
    // Cap Status Effect Resistance
    if (Player.StatusEffectResist > 100.0k)
        Player.StatusEffectResist = 100.0k;
    
    // Cap Toxicity Regen Bonus
    if (Player.ToxicityRegenBonus > 25)
        Player.ToxicityRegenBonus = 25;
    
    // Prevent Shield Capacity from under/overflowing
    if (Player.Shield.Charge < 0)
        Player.Shield.Charge = 0;
    if (Player.Shield.Charge > Player.Shield.Capacity)
        Player.Shield.Charge = Player.Shield.Capacity;
    
    // Cap Shield stats
    if (CheckShieldValid())
    {
        if (Player.Shield.Capacity < 0)
            Player.Shield.Capacity = 0;
        if (Player.Shield.ChargeRate < 0)
            Player.Shield.ChargeRate = 0;
        if (Player.Shield.DelayRate < 1.0k)
            Player.Shield.DelayRate = 1.0k;
    };
    
    // Cap Weapon Speed
    if (Player.WeaponSpeed < 0k)
        Player.WeaponSpeed = 0k;
    if (Player.WeaponSpeed > 100k)
        Player.WeaponSpeed = 100k;
    
    // Cap Survival Bonus
    if (Player.SurvivalBonus < 0k)
        Player.SurvivalBonus = 0k;
    if (Player.SurvivalBonus > 75k && (!Player.Shield.Accessory || Player.Shield.Accessory->PassiveEffect != SHIELD_PASS_ROULETTE))
        Player.SurvivalBonus = 75k;
    
    // Cap chances at 100%
    if (Player.HealthChance > 100k)  Player.HealthChance = 100k;
    if (Player.EPChance > 100k)      Player.EPChance = 100k;
    if (Player.PowerupChance > 100k) Player.PowerupChance = 100k;
    if (Player.ArmorChance > 100k)   Player.ArmorChance = 100k;
    if (Player.WeaponChance > 100k)  Player.WeaponChance = 100k;
    if (Player.ModuleChance > 100k)  Player.ModuleChance = 100k;
    if (Player.AugChance > 100k)     Player.AugChance = 100k;
    if (Player.ShieldChance > 100k)  Player.ShieldChance = 100k;
    if (Player.StimChance > 100k)    Player.StimChance = 100k;

    // Speed capping CVAR
    if (Player.Speed > GetActivatorCVarFixed("drpg_maxspeed"))
        Player.Speed = GetActivatorCVarFixed("drpg_maxspeed");
        
    // Jump Height capping CVAR
    if (Player.JumpHeight > GetActivatorCVarFixed("drpg_maxjump"))
        Player.JumpHeight = GetActivatorCVarFixed("drpg_maxjump");
}

// Luck Chances
void CheckLuck()
{
    Player.HealthDrop =     (Player.Luck >= LUCK_HEALTHDROP ? true : false);
    Player.EPDrop =         (Player.Luck >= LUCK_EPDROP ? true : false);
    Player.ArmorDrop =      (Player.Luck >= LUCK_ARMORDROP ? true : false);
    Player.WeaponDrop =     (Player.Luck >= LUCK_WEAPONDROP ? true : false);
    Player.PowerupDrop =    (Player.Luck >= LUCK_POWERUPDROP ? true : false);
    Player.StimDrop =       (Player.Luck >= LUCK_STIMDROP ? true : false);
    Player.ModuleDrop =     (Player.Luck >= LUCK_MODULEDROP ? true : false);
    Player.AugDrop =        (Player.Luck >= LUCK_AUGDROP ? true : false);
    Player.ShieldDrop =     (Player.Luck >= LUCK_SHIELDDROP ? true : false);
    
    Player.HealthChance =   Curve(Player.Luck, LUCK_HEALTHDROP, 1000, LUCK_HEALTHCHANCE, LUCK_MAXHEALTHCHANCE);
    Player.EPChance =       Curve(Player.Luck, LUCK_EPDROP, 1000, LUCK_EPCHANCE, LUCK_MAXEPCHANCE);
    Player.ArmorChance =    Curve(Player.Luck, LUCK_ARMORDROP, 1000, LUCK_ARMORCHANCE, LUCK_MAXARMORCHANCE);
    Player.WeaponChance =   Curve(Player.Luck, LUCK_WEAPONDROP, 1000, LUCK_WEAPONCHANCE, LUCK_MAXWEAPONCHANCE);
    Player.PowerupChance =  Curve(Player.Luck, LUCK_POWERUPDROP, 1000, LUCK_POWERUPCHANCE, LUCK_MAXPOWERUPCHANCE);
    Player.StimChance =     Curve(Player.Luck, LUCK_STIMDROP, 1000, LUCK_STIMCHANCE, LUCK_MAXSTIMCHANCE);
    Player.ModuleChance =   Curve(Player.Luck, LUCK_MODULEDROP, 1000, LUCK_MODULECHANCE, LUCK_MAXMODULECHANCE);
    Player.ShieldChance =   Curve(Player.Luck, LUCK_SHIELDDROP, 1000, LUCK_SHIELDCHANCE, LUCK_MAXSHIELDCHANCE);
    Player.AugChance =      Curve(Player.Luck, LUCK_AUGDROP, 1000, LUCK_AUGCHANCE, LUCK_MAXAUGCHANCE);
    
    // Hell Unleashed Map Event
    if (CurrentLevel->Event == MAPEVENT_HELLUNLEASHED)
    {
        Player.HealthChance += CurrentLevel->RareAdd;
        Player.EPChance += CurrentLevel->RareAdd;
        Player.ArmorChance += CurrentLevel->RareAdd;
        Player.WeaponChance += CurrentLevel->RareAdd;
        Player.PowerupChance += CurrentLevel->RareAdd;
        Player.StimChance += CurrentLevel->RareAdd;
        Player.ModuleChance += CurrentLevel->RareAdd;
        Player.AugChance += CurrentLevel->RareAdd;
        Player.ShieldChance += CurrentLevel->RareAdd;
    }
}

void CheckBurnout()
{
    // Energy Burnout Effect
    if (Player.EP < 0)
    {
        // Dynamic Intensity
        fixed Intensity = -((fixed)Player.EP / (fixed)Player.EPMax);
        if (Intensity > 0.5) Intensity = 0.5;
        
        // Screen Effect
        FadeRange(0, 128, 255, Intensity + (Sin(Timer() / 64.0) * 0.25), 0, 128, 255, 0, 0.25);
        
        // Penalties
        Player.TotalDamage /= 2;
        Player.DamageFactor *= 2;
        Player.Mass /= 2;
        Player.HealthMax /= 2;
        Player.EPMax /= 2;
        Player.Speed /= 2;
        Player.JumpHeight /= 2;
        Player.SurvivalBonus /= 2;
        
        // Energy Perk
        if (Player.Perks[STAT_ENERGY])
            Player.EPTime /= 2;
    }
}

void CheckPerks()
{
    // If you're dead, return
    if (GetActorProperty(Player.TID, APROP_Health) <= 0) return;
    
    if (Player.Strength >= 100)     Player.Perks[STAT_STRENGTH] = true;     else Player.Perks[STAT_STRENGTH] = false;
    if (Player.Defense >= 100)      Player.Perks[STAT_DEFENSE] = true;      else Player.Perks[STAT_DEFENSE] = false;
    if (Player.Vitality >= 100)     Player.Perks[STAT_VITALITY] = true;     else Player.Perks[STAT_VITALITY] = false;
    if (Player.Energy >= 100)       Player.Perks[STAT_ENERGY] = true;       else Player.Perks[STAT_ENERGY] = false;
    if (Player.Regeneration >= 100) Player.Perks[STAT_REGENERATION] = true; else Player.Perks[STAT_REGENERATION] = false;
    if (Player.Agility >= 100)      Player.Perks[STAT_AGILITY] = true;      else Player.Perks[STAT_AGILITY] = false;
    if (Player.Capacity >= 100)     Player.Perks[STAT_CAPACITY] = true;     else Player.Perks[STAT_CAPACITY] = false;
    if (Player.Luck >= 100)         Player.Perks[STAT_LUCK] = true;         else Player.Perks[STAT_LUCK] = false;
    
    fixed StrengthPercent = ((fixed)Player.ActualHealth / (fixed)Player.HealthMax * 100);
    fixed DefensePercent = ((fixed)Player.ActualHealth / (fixed)Player.HealthMax);
    
    // Cap Strength Percent
    if (StrengthPercent > 100)
        StrengthPercent = 100;
    
    // Cap Defense Percent
    if (DefensePercent < 0.01)
        DefensePercent = 0.01;
    if (DefensePercent > 1.0)
        DefensePercent = 1.0;
    
    // Strength Perk - Exponentially increase Strength as Health Decreases
    if (Player.Perks[STAT_STRENGTH] && StrengthPercent < 100)
        Player.DamageMult += ((100 - StrengthPercent) / 12.5);
    
    // Defense Perk - Exponentially increase Defense as Health Decreases
    if (Player.Perks[STAT_DEFENSE] && DefensePercent > 0)
        Player.DamageFactor *= DefensePercent;
    
    // Vitality Perk - Halve Health regeneration time
    if (Player.Perks[STAT_VITALITY] && Player.ActualHealth < Player.HealthMax / 10 + 1)
        Player.HPTime /= 2;
    
    // Agility Perk
    if (Player.Perks[STAT_AGILITY])
    {
        // Increment Agility timer to effect regeneration times the longer you are moving
        if (GetActorVelX(Player.TID) != 0 || GetActorVelY(Player.TID) != 0)
            Player.AgilityTimer++;
        else
            Player.AgilityTimer = 0;
        
        // +30% Survival Bonus
        Player.SurvivalBonus += 30;
    }
    
    // Capacity Perk - Regenerate ammo
    if (Player.Perks[STAT_CAPACITY] && (Timer() % (35 * 30)) == 0)
    {
        GiveInventory("Clip", GetAmmoAmount("Clip"));
        GiveInventory("Shell", GetAmmoAmount("Shell"));
        GiveInventory("RocketAmmo", GetAmmoAmount("RocketAmmo"));
        GiveInventory("Cell", GetAmmoAmount("Cell"));
    }
    
    // Luck Perk - Always have Automap/Scanner
    // TODO: Ability to see secrets
    if (Player.Perks[STAT_LUCK])
    {
        GiveInventory("DRPGAllMapRevealer", 1);
        TakeInventory("PowerScanner", 1);
        GiveInventory("DRPGAllMapScanner", 1);
    }
}

void CheckToxicity()
{
    // Prevent Underflow
    if (Player.Toxicity < 0)
        Player.Toxicity = 0;
    
    // Slowly decrease Toxicity
    if (Player.Toxicity > 0 && (Timer() % (35 * (30 - Player.ToxicityRegenBonus)) == 0))
    {
        Player.Toxicity--;
        Player.ToxicTimer = 0;
        Player.ToxicOffset = 0;
        Player.ToxicStage = 0;
    }
    
    // Toxicity Penalties
    if (GetCVar("drpg_toxicity_penalties"))
    {
        if (Player.Toxicity >= 25 && Timer() % 35 == 0)
        {
            Player.HPRate = 0;
            Player.EPRate = 0;
        }
        if (Player.Toxicity >= 50 && Timer() % 35 == 0 && Player.EP > 0)
            Player.EP--;
        if (Player.Toxicity >= 75)
        {
            Player.Speed /= 2;
            Player.JumpHeight /= 2;
        }
    }
    
    // Death at 100% Toxicity
    if (Player.Toxicity >= 100)
    {
        SetActorProperty(Player.TID, APROP_Health, 0);
        SetActorState(Player.TID, "Death.Toxicity", false);
        Player.Toxicity = 0;
    }
}

void CheckStimImmunity()
{
    // Prevent Overflow
    if (Player.StimImmunity > 100)
        Player.StimImmunity = 100;
    
    if (!CurrentLevel->UACBase || ArenaActive || MarinesHostile)
        if ((Timer() % (35 * GameSkill())) == 0 && Player.StimImmunity > 0)
            Player.StimImmunity--;
}

void ToxicityDamage()
{
    // Check Damage Type for Toxicity
    if ((Player.DamageType == DT_TOXIC || Player.DamageType == DT_RADIATION) && !CheckInventory("PowerIronFeet") && !(Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_NOTOXIC && Player.Shield.Active))
        AddToxicity(Random(1, GameSkill()));
}

void CheckStatusEffects()
{
    if (Player.StatusType[SE_BLIND]) // Blind
        FadeRange(0, 0, 0, (0.5 + (Player.StatusIntensity[SE_BLIND] * 0.1)) - (Sin(Timer() / 128.0) * 0.25), 0, 0, 0, 0.0, 0.5);
    
    if (Player.StatusType[SE_CONFUSION]) // Confusion
    {
        SetHudSize(640, 480, true);
        SetFont(StrParam("P%iVIEW", PlayerNumber() + 1));
        
        fixed ViewCycle = Timer() / (120.0 - (10.0 * Player.StatusIntensity[SE_CONFUSION]));
        fixed ViewDist = 9.6 * Player.StatusIntensity[SE_CONFUSION] * ((fixed)Player.StatusTimer[SE_CONFUSION] / (fixed)Player.StatusTimerMax[SE_CONFUSION]);
        
        // View Spinning
        HudMessage("A");
        EndHudMessage(HUDMSG_PLAIN | HUDMSG_LAYER_UNDERHUD | HUDMSG_NOTWITHFULLMAP, CONFUSION_ID + 3, "Untranslated", 320, 240, 0.029);
        HudMessage("A");
        EndHudMessage(HUDMSG_PLAIN | HUDMSG_ALPHA | HUDMSG_LAYER_UNDERHUD | HUDMSG_NOTWITHFULLMAP, CONFUSION_ID, "Untranslated",
                   320 + (int)(Cos(ViewCycle) * ViewDist),
                   240 + (int)(Sin(ViewCycle) * ViewDist),
                   0.029, 0.3);
        HudMessage("A");
        EndHudMessage(HUDMSG_PLAIN | HUDMSG_ALPHA | HUDMSG_LAYER_UNDERHUD | HUDMSG_NOTWITHFULLMAP, CONFUSION_ID + 1, "Untranslated",
                   320 + (int)(Cos(ViewCycle + 0.333) * ViewDist),
                   240 + (int)(Sin(ViewCycle + 0.333) * ViewDist),
                   0.029, 0.6);
        HudMessage("A");
        EndHudMessage(HUDMSG_PLAIN | HUDMSG_ALPHA | HUDMSG_LAYER_UNDERHUD | HUDMSG_NOTWITHFULLMAP, CONFUSION_ID + 2, "Untranslated",
                   320 + (int)(Cos(ViewCycle + 0.667) * ViewDist),
                   240 + (int)(Sin(ViewCycle + 0.667) * ViewDist),
                   0.029, 0.9);
        
        // Text Nonsense
        if (Random(1, 100 - (int)(((fixed)Player.StatusTimer[SE_CONFUSION] / (fixed)Player.StatusTimerMax[SE_CONFUSION]) * (10.0 * (fixed)Player.StatusIntensity[SE_CONFUSION]))) == 1)
        {
            char const Letters[26] =
            {
                'A', 'B', 'C', 'D', 'E', 'F',
                'G', 'H', 'I', 'J', 'K', 'L',
                'M', 'N', 'O', 'P', 'Q', 'R',
                'S', 'T', 'U', 'V', 'W', 'X',
                'Y', 'Z'
            };
            
            // Build a jibberish string
            int Length = Random(5, 30);
            char *Nonsense;
            
            // Fill the char array with garbage
            for (int i = 0; i < Length - 1; i++) 
                Nonsense[i] = Letters[Random(0, 25)];
            Nonsense[Length] = '\0';
            
            SetFont((Random(1, 4) == 1 ? "BIGFONT" : "SMALLFONT"));
            PrintTextWiggle(Nonsense, CONFUSION_NONSENSE_ID + Random(0, 10000), Random(0, 21), Random(160, 480), Random(120, 360), RandomFixed(1.0, 5.0), RandomFixed(32.0, 64.0), Random(8, 12), RandomFixed(16.0, 64.0));
        }
        
        // Sprite Nonsense
        if (Random(1, 100 - (int)(((fixed)Player.StatusTimer[SE_CONFUSION] / (fixed)Player.StatusTimerMax[SE_CONFUSION]) * (10.0 * (fixed)Player.StatusIntensity[SE_CONFUSION]))) == 1)
        {
            str const Sprites[86] =
            {
                "TOKAA0", "TOKBA0", "TOKCA0",
                "AUGCA0", "AUGUA0", "AUGUB0", "AUGBATT",
                "STIMB0",
                
                "PINVA0", "PINSA0", "PVISA0",
                "SOULA0", "MEGAA0", "CONTA0",
                
                "Stim1", "Stim2", "Stim3", "Stim4",
                "Stim5", "Stim6", "Stim7", "Stim8",
                "Stim9", "Stim10", "Stim11", "Stim12",
                "Stim13", "Stim14", "Stim15", "Stim16",
                "Stim17", "Stim18", "Stim19",
                
                "BarSBlnd", "BarSConf", "BarSPois", "BarSCorr",
                "BarSViru", "BarSFati", "BarSSile", "BarSEMP",
                "BarSCurs",
                
                "Fill1", "Fill2", "Fill3", "Fill4",
                "Fill5", "Fill6", "Fill7", "Fill8",
                "Fill9", "Fill10", "FillBar", "FillShld",
                
                "MonLevel",
                "RankEmb", "RankEmb1", "RankEmb2", "RankEmb3",
                "RankEmb4", "RankEmb5", "RankEmb6",
                
                "DamNum0", "DamNum1", "DamNum2", "DamNum3",
                "DamNum4", "DamNum5", "DamNum6", "DamNum7",
                "DamNum8", "DamNum9",
                
                "STAT1S", "STAT2S", "STAT3S", "STAT4S",
                "STAT5S", "STAT6S", "STAT7S", "STAT8S",
                "STATP",
                
                "PRed", "POrange", "PYellow", "PGreen",
                
                "M_DOOM"
            };
            
            PrintSpriteFade(Sprites[Random(0, 85)], CONFUSION_NONSENSE_ID + Random(0, 10000), Random(160, 480), Random(120, 360), RandomFixed(1.0, 3.0), RandomFixed(1.0, 2.0));
        }
        
        SetHudSize(0, 0, false);
    }
    
    if (Player.StatusType[SE_POISON]) // Poison
        if ((Timer() % 35) == 0)
            if (Player.ActualHealth - Player.StatusIntensity[SE_POISON] > 0)
            {
                Player.ActualHealth -= Player.StatusIntensity[SE_POISON];
                FadeRange(0, 255, 0, 0.25, 0, 255, 0, 0.0, Player.StatusIntensity[SE_POISON] * 0.25);
            }
    
    if (Player.StatusType[SE_CORROSION]) // Corrosion
        if ((Timer() % 35) == 0 && CheckInventory("Armor") > 0)
            if (CheckInventory("Armor") - Player.StatusIntensity[SE_CORROSION] > 0)
            {
                TakeInventory("BasicArmor", Player.StatusIntensity[SE_CORROSION]);
                FadeRange(0, 255, 0, 0.25, 0, 255, 0, 0.0, Player.StatusIntensity[SE_CORROSION] * 0.25);
            }
    
    if (Player.StatusType[SE_VIRUS]) // Virus
    {
        if (Player.HPRate > 0) Player.HPRate -= 3 + Player.StatusIntensity[SE_VIRUS];
        if (Player.EPRate > 0) Player.EPRate -= 3 + Player.StatusIntensity[SE_VIRUS];
    }
    
    if (Player.StatusType[SE_SILENCE]) // Silence
        RemoveAura();
    
    if (Player.StatusType[SE_CURSE]) // Curse
        Player.DamageFactor = Player.DamageFactor * (1.0 * (Player.StatusIntensity[SE_CURSE] + 1));
    
    if (Player.StatusType[SE_EMP]) // EMP
    {
        if (Player.Shield.Active)
            DeactivateShield();
        if (Player.Augs.SlotsUsed > 0)
            DisableAugs(true);
        if ((Timer() % 35) == 0)
            Player.Augs.Battery -= Player.StatusIntensity[SE_EMP];
    }
    else if (GetActivatorCVar("drpg_augs_autoreactivate"))
        ReactivateDisabledAugs();
    
    if (Player.StatusType[SE_RADIATION]) // Radiation
    {
        // Geiger Sound Loop
        PlaySound(0, "misc/radiation", 7, 1.0, true, ATTN_NORM);
        
        if ((Timer() % 70) == 0)
        {
            // Trail Light
            SpawnForced("DRPGRadiationGlow2", GetActorX(0), GetActorY(0), GetActorZ(0) + (GetActorProperty(0, APROP_Height) / 2.0));
            
            // Poisoning
            if (Player.Toxicity < 85 && !(Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_NOTOXIC && Player.Shield.Active))
            {
                int i = Random(1, Player.StatusIntensity[SE_RADIATION]);
                if (Player.Toxicity + i > 85)
                    i = 85 - Player.Toxicity;
                AddToxicity(i);
                FadeRange(0, 255, 0, 0.25, 0, 255, 0, 0.0, i * 0.25);
            }
        }
        
        // Actor Light
        SpawnForced("DRPGRadiationGlow", GetActorX(0), GetActorY(0), GetActorZ(0) + (GetActorProperty(0, APROP_Height) / 2.0));
    }
    
    for (int i = 0; i < SE_MAX; i++)
    {
        // Disable an effect if the timer is 0
        if (Player.StatusType[i] && Player.StatusTimer[i] <= 0)
        {
            Player.StatusType[i] = false;
            Player.StatusIntensity[i] = 0;
            Player.StatusTimer[i] = 0;
            Player.StatusTimerMax[i] = 0;
            
            if (i == SE_RADIATION)
                StopSound(Player.TID, 7);
        }
        else if (Player.StatusTimer[i] > 0)
            Player.StatusTimer[i] -= 1 + (Player.RegenBoostTimer > 0 ? Player.RegenBoostTimer / 500 : 0);
    }
}

void StatusDamage(int Amount, fixed Chance, bool Critical)
{
    int Type = SE_NONE;
    int StatChance = 0;
    int Intensity = 0;
    int Time = 0;
    
    // Criticals boost chance 2.5x
    if (Critical)
        Chance *= 2.5;
    
    // We lucked out this time and won't get hit with a status effect
    if (RandomFixed(0.0, 100.0) >= Chance) return;
    
    // Calculate the intensity
    Intensity = (Amount * Player.HealthMax) / 1000;
    if (Intensity < 1)
        Intensity = 1;
    if (Intensity > 5)
        Intensity = 5;
    
    // Damage Types
    switch (Player.DamageType)
    {
    case DT_TOXIC:
        switch (Random(1, 3))
        {
        case 1:
            Type = SE_POISON;
            Time = Random(1, 10);
            break;
        case 2:
            Type = SE_CORROSION;
            Time = Random(1, 10);
            break;
        case 3:
            Type = SE_RADIATION;
            Time = Random(1, 10);
            break;
        }
        break;
    case DT_RADIATION:
        Type = SE_RADIATION;
        Time = Random(1, 10);
        break;
    case DT_MELEE:
        switch (Random(1, 3))
        {
        case 1:
            Type = SE_BLIND;
            Time = Random(5, 10);
            break;
        case 2:
            Type = SE_CONFUSION;
            Time = Random(5, 10);
            break;
        case 3:
            Type = SE_FATIGUE;
            Time = Random(5, 30);
            break;
        }
        break;
    case DT_PLASMA:
        switch (Random(1, 5))
        {
        case 1:
            Type = SE_POISON;
            Time = Random(5, 20);
            break;
        case 2:
            Type = SE_CORROSION;
            Time = Random(5, 20);
            break;
        case 3:
            Type = SE_VIRUS;
            Time = Random(60, 180);
            break;
        case 4:
            Type = SE_SILENCE;
            Intensity = 1; // Only has one level of intensity
            Time = Random(60, 180);
            break;
        case 5:
            Type = SE_CURSE;
            Time = Random(10, 60);
            break;
        }
        break;
    case DT_LIGHTNING:
        switch (Random(1, 4))
        {
        case 1:
            Type = SE_BLIND;
            Time = Random(5, 10);
            break;
        case 2:
            Type = SE_SILENCE;
            Intensity = 1; // Only has one level of intensity
            Time = Random(60, 180);
            break;
        case 3:
            Type = SE_EMP;
            Time = Random(5, 30);
            break;
        case 4:
            Type = SE_RADIATION;
            Time = Random(5, 20);
            break;
        }
        break;
    case DT_FIRE:
        switch (Random(1, 2))
        {
        case 1:
            Type = SE_BLIND;
            Time = Random(5, 10);
            break;
        case 2:
            Type = SE_FATIGUE;
            Time = Random(5, 30);
            break;
        }
        break;
    }
    
    if (Type >= 0)
        TryStatusEffect(Type, Time, Intensity);
}
