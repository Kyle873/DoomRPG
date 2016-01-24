#include "Defs.h"

#include "Arena.h"
#include "Map.h"
#include "Menu.h"
#include "Outpost.h"
#include "RPG.h"
#include "Stats.h"
#include "Stims.h"
#include "Turret.h"
#include "Utils.h"

str const CompoundNames[STIM_MAX] =
{
    // Stats
    "Strength",
    "Defense",
    "Vitality",
    "Energy",
    "Regeneration",
    "Agility",
    "Capacity",
    "Luck",
    
    // Boosters
    "Purifier",
    "Potency",
    
    // Powerups
    "Indestructible",
    "Shadow",
    "Infinity",
    "Chrono",
    "Adrenaline",
    "Gravity",
    "Vampire",
    "Rage",
    "Magnetic"
};

str const CompoundColors[STIM_MAX] =
{
    // Stats
    "Red",
    "Green",
    "Brick",
    "LightBlue",
    "Purple",
    "Orange",
    "Blue",
    "Gold",
    
    // Boosters
    "DarkGray",
    "White",
    
    // Powerups
    "DarkGreen",
    "DarkRed",
    "Yellow",
    "Green",
    "Purple",
    "Orange",
    "Brick",
    "Black",
    "Gray"
};

int const StimStatsStart = 0;
int const StimStatsEnd = 8;
int const StimPowerupStart = 10;
int const StimPowerupEnd = STIM_MAX;

NamedScript KeyBind void UseStim(bool Force)
{
    bool Turret = false;
    int Size;
    int Injector[STIM_MAX];
    
    // If you're dead, terminate
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    // Generate and Activate Turret Stim
    if (GetPlayerInput(PlayerNumber(), INPUT_BUTTONS) & BT_SPEED && Player.Turret.Active)
    {
        Turret = true;
        
        // Focused injection handling
        if (Player.Turret.StimFocused && Player.Turret.StimTimer <= 0)
        {
            Player.Turret.StimPicked = false;
            TurretPickStimMenu();
            
            // Wait for the player to pick a vial type
            while (!Player.Turret.StimPicked)
                Delay(1);
            
            // If the player cancelled out of the menu, return
            if (Player.Turret.StimVialType == -1)
                return;
        }
        
        // Store Injector for restore later
        Size = Player.Stim.Size;
        for (int i = 0; i < STIM_MAX; i++)
            Injector[i] = Player.Stim.Current[i];
        
        if (!TurretStim())
            return;
        
        Delay(1);
    }
    
    if (!Force && Player.Stim.Size == 0 && !Turret)
    {
        PrintError("You don't have an injector ready");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (!Force && Player.Stim.Amount == 0 && !Turret)
    {
        PrintError("Your current injector is empty");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    // Store previous states
    if (!Player.Stim.Active)
    {
        Player.Stim.PrevStats[0] = Player.Strength;
        Player.Stim.PrevStats[1] = Player.Defense;
        Player.Stim.PrevStats[2] = Player.Vitality;
        Player.Stim.PrevStats[3] = Player.Energy;
        Player.Stim.PrevStats[4] = Player.Regeneration;
        Player.Stim.PrevStats[5] = Player.Agility;
        Player.Stim.PrevStats[6] = Player.Capacity;
        Player.Stim.PrevStats[7] = Player.Luck;
    }
    
    // Set Timer for Stat bonuses
    for (int i = StimStatsStart; i < StimStatsEnd + 2; i++)
        if (Player.Stim.Current[i] > 0)
        {
            int InitialTime = 35 * (60 + (Player.Stim.Current[STIM_PURIFIER] * 30));
            InitialTime -= InitialTime * Player.StimImmunity / 100;
            
            Player.Stim.Active = true;
            Player.Stim.Timer += InitialTime;
            
            if (Player.Stim.Timer >= Player.Stim.TimerMax)
                Player.Stim.TimerMax = Player.Stim.Timer;
        }
    
    // Apply Multiplier and Potency
    for (int i = StimStatsStart; i < StimStatsEnd; i++)
        Player.Stim.Current[i] = (Player.Stim.Current[i] * 5) + (Player.Stim.Current[STIM_POTENCY] * 5);
    
    // Apply Stat Bonuses
    Player.StrengthBonus += Player.Stim.Current[STIM_STRENGTH];
    Player.DefenseBonus += Player.Stim.Current[STIM_DEFENSE];
    Player.VitalityBonus += Player.Stim.Current[STIM_VITALITY];
    Player.EnergyBonus += Player.Stim.Current[STIM_ENERGY];
    Player.RegenerationBonus += Player.Stim.Current[STIM_REGENERATION];
    Player.AgilityBonus += Player.Stim.Current[STIM_AGILITY];
    Player.CapacityBonus += Player.Stim.Current[STIM_CAPACITY];
    Player.LuckBonus += Player.Stim.Current[STIM_LUCK];
    
    // Setup Powerup Timers
    for (int i = StimPowerupStart; i < StimPowerupEnd; i++)
        if (Player.Stim.Current[i] > 0)
        {
            int InitialTime = (35 * Player.Stim.Current[i]) * 30;
            InitialTime -= InitialTime * Player.StimImmunity / 100;
            
            Player.Stim.PowerupTimer[i] += InitialTime;
            
            if (Player.Stim.PowerupTimer[i] > Player.Stim.PowerupTimerMax[i])
                Player.Stim.PowerupTimerMax[i] = Player.Stim.PowerupTimer[i];
        }
    
    // Apply Active Flags
    for (int i = 0; i < STIM_MAX; i++)
        if (Player.Stim.Current[i] > 0)
            Player.Stim.ActiveBonus[i] = true;
    
    // Add Toxicity
    Player.Toxicity += Player.Stim.Toxicity;
    Player.Payout.StimToxicity += Player.Stim.Toxicity;
    
    // Add Immunity
    Player.StimImmunity += Player.Stim.Toxicity * 5;
    Player.Payout.StimImmunity += Player.Stim.Toxicity * 5;
    if (Player.StimImmunity > 100)
        Player.StimImmunity = 100;
    
    // Apply current Stim to last used Stim
    for (int i = 0; i < STIM_MAX; i++)
        Player.Stim.Last[i] += Player.Stim.Current[i];
    
    // Restore Injector if it was saved from a turret
    if (Turret)
    {
        Size = Player.Stim.Size;
        for (int i = 0; i < STIM_MAX; i++)
            Player.Stim.Current[i] = Injector[i];
    }
    
    // Clear the Stim
    Player.Stim.Size = 0;
    Player.Stim.Amount = 0;
    for (int i = 0; i < STIM_MAX; i++)
        Player.Stim.Current[i] = 0;
    
    // FX
    ClearToxicityMeter();
    ActivatorSound("items/stim", 127);
    if (Random(0, 100) == 0) // DRUGS
        ActivatorSound("misc/drugs", 127);
    FadeRange(255, 255, 255, 0.25, 255, 255, 255, 0, 1.0);
    if (!Turret)
        TossStim();
    
    // Payout
    Player.Payout.StimsUsed++;
}

NamedScript KeyBind void ThrowAwayStim()
{
    if (Player.Stim.Size == 0)
    {
        PrintError("You don't have an injector ready");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (Player.Stim.Amount == 0)
    {
        switch (Player.Stim.Size)
        {
        case 1:
            GiveInventory("DRPGStimSmall", 1);
            break;
        case 2:
            GiveInventory("DRPGStimMedium", 1);
            break;
        case 3:
            GiveInventory("DRPGStimLarge", 1);
            break;
        case 4:
            GiveInventory("DRPGStimXL", 1);
            break;
        }
        
        Player.Stim.Size = 0;
        PrintMessage("Stored away the empty injector for later use");
        ActivatorSound("menu/leave", 127);
        return;
    }
    
    // [KS] I'm witty.
    if (Player.Stim.Toxicity >= 200)
    {
        switch (Random(1, 5))
        {
        case 1:
            PrintMessage("It seemed like a good idea at the time\n\nPerhaps there was a little too much alcohol involved then");
            break;
        case 2:
            PrintMessage("If you were Russian... You would still say this is Overkill");
            break;
        case 3:
            PrintMessage("You imagine that a mixture like that would probably work better as a chemical explosive");
            break;
        case 4:
            PrintMessage("That stim would've turned you more demon than the demons");
            break;
        case 5:
            PrintMessage("Threw away the entirely unusable stim");
            break;
        }
    }
    else if (Player.Stim.Toxicity >= 150)
    {
        switch (Random(1, 5))
        {
        case 1:
            PrintMessage("If it could kill an elephant, it probably shouldn't be going into you");
            break;
        case 2:
            PrintMessage("You managed to make a mixture more potent than most forms of party drinks");
            break;
        case 3:
            PrintMessage("You could smell the toxicity from off-planet");
            break;
        case 4:
            PrintMessage("You consider throwing it at the enemies instead\nNah, it'd just make them angrier");
            break;
        case 5:
            PrintMessage("Threw away the unusable stim");
            break;
        }
    }
    else if (Player.Stim.Toxicity >= 100)
    {
        switch (Random(1, 5))
        {
        case 1:
            PrintMessage("Congratulations, you've produced death");
            break;
        case 2:
            PrintMessage("You carefully examine the stim, and notice it's unsuitable for humans");
            break;
        case 3:
            PrintMessage("You may want to lay up on the stat boosters a little next time");
            break;
        case 4:
            PrintMessage("Well that stim's no good now");
            break;
        case 5:
            PrintMessage("Threw away the toxic stim");
            break;
        }
    }
    else
    {
        switch (Random(1, 5))
        {
        case 1:
            PrintMessage("You decide there are better methods of dealing with the whole monster problem");
            break;
        case 2:
            PrintMessage("You decide now is not the time for injections");
            break;
        case 3:
            PrintMessage("You decide you don't need the stim now");
            break;
        case 4:
            PrintMessage("You chuck away the stim, having no need for it");
            break;
        case 5:
            PrintMessage("Threw away the stim");
            break;
        }
    }

    // Clear the Stim
    Player.Stim.Size = 0;
    Player.Stim.Amount = 0;
    for (int i = 0; i < STIM_MAX; i++)
        Player.Stim.Current[i] = 0;
    
    // FX
    ClearToxicityMeter();
    TossStim();
    
    ActivatorSound("menu/leave", 127);
}

NamedScript DECORATE void TossStim()
{
    int TID = UniqueTID();
    str StimTossActor;
    fixed Angle = GetActorAngle(0);
    fixed VelX;
    fixed VelY;
    
    // Injector size
    switch (Player.Stim.Size)
    {
    case 1: // Small
        StimTossActor = "DRPGStimSmallTossed";
        break;
    case 2: // Medium
        StimTossActor = "DRPGStimMediumTossed";
        break;
    case 3: // Large
        StimTossActor = "DRPGStimLargeTossed";
        break;
    case 0: // Detox
    case 4: // XL
        StimTossActor = "DRPGStimXLTossed";  
        break;
    }
    
    // Spawn the empty injector
    SpawnForced(StimTossActor, GetActorX(0), GetActorY(0), GetActorZ(0) + 48.0, TID, 0);
    
    // Toss direction
    switch (Random(1, 3))
    {
    case 1: // Left side
        Angle -= 0.25;
        break;
    case 2: // Right side
        Angle += 0.25;
        break;
    case 3: // Behind
        Angle -= 0.5;
        break;
    }
    
    VelX = Cos(Angle);
    VelY = Sin(Angle);
    
    // Adjust the trajectory
    SetActorVelocity(TID, VelX * RandomFixed(2.0, 4.0), VelY * RandomFixed(2.0, 4.0), 0.0, false, false);
}

NamedScript DECORATE void AddCompound(int Type, int Amount)
{
    Player.Stim.Vials[Type] += Amount;
    
    if (Player.Stim.Vials[Type] > Player.Stim.VialMax)
        Player.Stim.Vials[Type] = Player.Stim.VialMax;
}

NamedScript DECORATE void AddCompoundDirect(int Type, int Amount)
{
    Player.Stim.Current[Type] = Amount;
    UseStim(true);
}

void CheckStim()
{
    str const StimPowerupActors[9] =
    {
        "DRPGPowerStimIndestructible",
        "DRPGPowerStimShadow",
        "DRPGPowerStimInfinity",
        "DRPGPowerStimChrono",
        "DRPGPowerStimAdrenaline",
        "DRPGPowerStimGravity",
        "DRPGPowerStimVampire",
        "DRPGPowerStimRage",
        "DRPGPowerStimMagnetic",
    };
    
    // Toxicity multiplier for Potency and Purifier stims
    int StimToxicityMultiplier = 1 + Player.Stim.Current[STIM_POTENCY] + Player.Stim.Current[STIM_PURIFIER];
    
    // Stim maximum capacities
    if (Player.Stim.Size == 1) // Small
        Player.Stim.Capacity = 10;
    if (Player.Stim.Size == 2) // Medium
        Player.Stim.Capacity = 25;
    if (Player.Stim.Size == 3) // Large
        Player.Stim.Capacity = 50;
    if (Player.Stim.Size == 4) // Extra-Large
        Player.Stim.Capacity = 100;
    
    // Reset toxicity var
    Player.Stim.Toxicity = 0;
    
    // Toxicity From amount of different compounds
    for (int i = 0; i < STIM_MAX; i++)
        if (Player.Stim.Current[i] > 0)
            Player.Stim.Toxicity += StimToxicityMultiplier;
    
    // Toxicity from total amount of compounds
    Player.Stim.Toxicity += (Player.Stim.Amount * StimToxicityMultiplier) / 5;
    
    // Toxicity added Based on Skill
    Player.Stim.Toxicity += GameSkill() * StimToxicityMultiplier;
    
    // Calculate the current Stim amount
    Player.Stim.Amount = 0;
    for (int i = 0; i < STIM_MAX; i++)
        Player.Stim.Amount += Player.Stim.Current[i];
    
    // Mugshot
    if (Player.Stim.Timer > 0)
        SetMugShotState("Ouch");
    
    if ((!CurrentLevel->UACBase || ArenaActive || MarinesHostile) && Timer() > 4)
    {
        // Stim Timer handling
        if (Player.Stim.Timer > 0)
            Player.Stim.Timer--;
        if (Player.Stim.Timer <= 0) // Reset timer maximums
        {
            Player.Stim.Timer = 0;
            Player.Stim.TimerMax = 0;
        }
        
        // Powerup Timer Handling
        for (int i = StimPowerupStart; i < StimPowerupEnd; i++)
        {
            // Tick timers
            if (Player.Stim.PowerupTimer[i] > 0)
            {
                if (i != STIM_CHRONO &&     // Skip these as they have their own handling
                    i != STIM_ADRENALINE &&
                    i != STIM_RAGE &&
                    i != STIM_MAGNETIC)
                    GiveInventory(StrParam("%S", StimPowerupActors[i - StimPowerupStart]), 1);
                
                Player.Stim.PowerupTimer[i]--;
            }
            
            // Time Freeze Handling
            if (i == STIM_CHRONO && !IsPlayerMoving() && Player.Stim.PowerupTimer[i] > 0)
                GiveInventory(StrParam("%S", StimPowerupActors[i - StimPowerupStart]), 1);
            
            // Regeneration Handling
            if (i == STIM_ADRENALINE && Player.Stim.PowerupTimer[i] > 0)
                Player.RegenBoostTimer = Player.Stim.PowerupTimer[i];
            
            // Reset timer maximums and active state
            if (Player.Stim.PowerupTimer[i] <= 0)
            {
                Player.Stim.ActiveBonus[i] = false;
                Player.Stim.Last[i] = 0;
                Player.Stim.PowerupTimer[i] = 0;
                Player.Stim.PowerupTimerMax[i] = 0;
            }
        }
        
        // Remove bonuses and active flags when Stim has expired
        if (Player.Stim.Timer <= 0 && Player.Stim.Active)
        {
            Player.Stim.Active = false;
            
            // Restore previous stats
            Player.Strength = Player.Stim.PrevStats[STAT_STRENGTH];
            Player.Defense = Player.Stim.PrevStats[STAT_DEFENSE];
            Player.Vitality = Player.Stim.PrevStats[STAT_VITALITY];
            Player.Energy = Player.Stim.PrevStats[STAT_ENERGY];
            Player.Regeneration = Player.Stim.PrevStats[STAT_REGENERATION];
            Player.Agility = Player.Stim.PrevStats[STAT_AGILITY];
            Player.Capacity = Player.Stim.PrevStats[STAT_CAPACITY];
            Player.Luck = Player.Stim.PrevStats[STAT_LUCK];
            
            for (int i = 0; i < StimStatsEnd; i++)
            {
                Player.Stim.ActiveBonus[i] = false;
                Player.Stim.Last[i] = 0;
            }
        }
    }
    else if (Player.Stim.ActiveBonus[STIM_ADRENALINE]) // Hack to reset the regen boost timer per-tic if the stims are deactivated after they are active
        Player.RegenBoostTimer = 0;
}

void MixStim(int Type)
{
    if (Player.Stim.Size == 0)
    {
        PrintError("You don't have an injector ready");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (Player.Stim.Vials[Type] <= 0)
    {
        PrintError("You don't have any vials of this type left");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (Player.Stim.Amount >= Player.Stim.Capacity)
    {
        PrintError("The injector is currently full");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    // Add from vial to stim
    ActivatorSound("menu/move", 127);
    Player.Stim.Vials[Type]--;
    Player.Stim.Current[Type]++;
}

void SetStim(int Type)
{
    if ((Type == 0 && !CheckInventory("DRPGStimSmall")) || 
        (Type == 1 && !CheckInventory("DRPGStimMedium")) ||
        (Type == 2 && !CheckInventory("DRPGStimLarge")) ||
        (Type == 3 && !CheckInventory("DRPGStimXL")))
    {
        PrintError("You have no injectors of this type");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (Player.Stim.Size > 0)
    {
        PrintError("You already have a stim ready");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    Player.Stim.Size = Type + 1;
    ActivatorSound("menu/move", 127);
    
    if (Type == 0) TakeInventory("DRPGStimSmall", 1);
    if (Type == 1) TakeInventory("DRPGStimMedium", 1);
    if (Type == 2) TakeInventory("DRPGStimLarge", 1);
    if (Type == 3) TakeInventory("DRPGStimXL", 1);
    
    // Payout
    Player.Payout.StimsMade++;
}
