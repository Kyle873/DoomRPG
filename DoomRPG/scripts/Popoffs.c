#include "RPG.h"

#include "Monsters.h"
#include "Popoffs.h"
#include "Shield.h"
#include "Utils.h"

// Handles Damage Numbers
// TODO: GDCC is running this obscenely slowly, need to optimize the FUCK out of it
NamedScript void DamageNumbers()
{
    Start:
    
    // Initial delay so we don't show max health being calculated or other nonsense
    Delay(4);
    
    while (GetCVar("drpg_damagenumbers"))
    {
        int Health = GetActorProperty(0, APROP_Health);
        bool ShieldActive = CheckInventory("DRPGShield");
        int Shield = Player.Shield.Charge;
        int Color;
        int OldTID;
        
        // Lag handling
        Delay(1 + GetDamageNumbersDelay());
        
        // Check Health
        Health = Health - GetActorProperty(0, APROP_Health);
        
        // Nullify Health if a Shield is active
        if (PlayerNumber() > -1 && CheckInventory("DRPGShield") || GetActorProperty(0, APROP_Health) >= SHIELD_HEALTH - GetActorProperty(0, APROP_SpawnHealth))
            Health = 0;
        
        // Shield breaking hits will cause a major health drop, don't show this
        if (PlayerNumber() > -1 && Health >= (SHIELD_HEALTH / 1000) - GetActorProperty(0, APROP_SpawnHealth))
            Health = 0;
        
        // Shield checks
        if (CheckInventory("DRPGShield"))
            Shield = Shield - Player.Shield.Charge;
        
        if (Health != 0 || Shield != 0)
        {
            if (Health >= GetActorProperty(0, APROP_SpawnHealth)) // Critical
                Color = DNUM_CRITICAL;
            else if (Health < 0 && !CheckInventory("DRPGShield")) // Healed
                Color = DNUM_HEAL;
            else if (Health == 1) // Scratch
                Color = DNUM_SCRATCH;
            else if (ShieldActive && Shield > 0) // Shield Loss
                Color = DNUM_SHIELDLOSS;
            else if (ShieldActive && Shield < 0) // Shield Gain
                Color = DNUM_SHIELDGAIN;
            else // Normal
                Color = DNUM_NORMAL;
            
            // Damage Popoff
            if (CheckInventory("DRPGShield"))
                Popoff(0, Shield, Color, "DRPGDigit", true);
            else
                Popoff(0, Health, Color, "DRPGDigit", true);
        }
            
        // Terminate if the Actor is dead
        if (ClassifyActor(0) & ACTOR_DEAD) return;
    }
    
    Delay(35);
    goto Start;
}

// Handles informational popoffs
NamedScript void InfoPopoffs()
{
    Start:
    
    while (GetCVar("drpg_popoffs"))
    {
        int BeforeCredits;
        int AfterCredits;
        int BeforeEP;
        int AfterEP;
        
        // Before Checks
        BeforeCredits = CheckInventory("DRPGCredits");
        BeforeEP = Player.EP;
        
        Delay(1);
        
        // After Checks
        AfterCredits = CheckInventory("DRPGCredits");
        AfterEP = Player.EP;
        
        // Credits Popoffs
        if (AfterCredits > BeforeCredits)
            Popoff(Player.TID, AfterCredits - BeforeCredits, DNUM_CREDGAIN, "DRPGDigit", true);
        if (AfterCredits < BeforeCredits)
            Popoff(Player.TID, AfterCredits - BeforeCredits, DNUM_CREDLOSS, "DRPGDigit", true);
        
        // EP Popoffs
        if (AfterEP > BeforeEP)
            Popoff(Player.TID, AfterEP - BeforeEP, DNUM_EPGAIN, "DRPGDigit", true);
        if (AfterEP < BeforeEP)
            Popoff(Player.TID, AfterEP - BeforeEP, DNUM_EPLOSS, "DRPGDigit", true);
            
        // Terminate if the Player is dead
        if (GetActorProperty(0, APROP_Health) <= 0) return;
    }
    
    Delay(1);
    goto Start;
}

// Spawns digits for Module pickups
NamedScript DECORATE void ModulePopoffs()
{
    while (!(ClassifyActor(0) == ACTOR_WORLD))
    {
        Popoff(0, GetUserVariable(0, "user_amount"), 0, "DRPGDigitalDigit", false);
        Delay(1);
    }
}

// Spawn a popoff number
void Popoff(int TID, int Value, int Color, str DigitType, bool FloatAway)
{
    int Digits[DNUM_DIGITS];
    int DigitTID = UniqueTID();
    int DigitBase = 1;
    fixed X = GetActorX(TID);
    fixed Y = GetActorY(TID);
    fixed Z = GetActorZ(TID);
    
    // Handling for height
    if (ClassifyActor(TID) & ACTOR_MONSTER)
        Z += Monsters[GetMonsterID(TID)].Height;
    else
        Z += GetActorPropertyFixed(TID, APROP_Height);
    
    // Ceiling monsters need special Z calculations
    if (CheckFlag(TID, "CEILINGHUGGER"))
        Z = GetActorZ(TID) - Monsters[GetMonsterID(TID)].Height;
    
    // Prevent digit overflow
    if (Value > 9999999)
        Value = 9999999;
    
    // Put the digits into the array
    for (int i = 0; i < DNUM_DIGITS; i++)
        Digits[i] = GetDigit(Abs(Value), i);
    
    // Digit Spawning
    for (int i = 0; i < DNUM_DIGITS; i++)
    {
        str DigitActor = StrParam("%S%dNum%d", DigitType, i + 1, Digits[i]);
        
        if (Value >= DigitBase || Value <= -DigitBase)
            switch (Digits[1])
            {
            case 0: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 1: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 2: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 3: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 4: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 5: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 6: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 7: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 8: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            case 9: Spawn(DigitActor, X, Y, Z, DigitTID, 0);    break;
            }
        
        DigitBase *= 10;
    }
    
    // Color
    if (Color > 0)
        Thing_SetTranslation(DigitTID, Color);
    
    // Set Fade Speed
    SetUserVariable(DigitTID, "user_fade", GetCVar("drpg_damagenumbers_fade"));
    
    // Float away
    if (FloatAway)
    {
        if (CheckFlag(TID, "CEILINGHUGGER"))
            SetActorVelocity(DigitTID, RandomFixed(-1.0, 1.0), RandomFixed(-1.0, 1.0), -0.5, 0, 0);
        else
            SetActorVelocity(DigitTID, RandomFixed(-1.0, 1.0), RandomFixed(-1.0, 1.0), 0.5, 0, 0);
    }
}

int GetDigit(int Num, int Digit)
{
    return (Num / Pow(10, Digit)) % 10;
}

int GetDamageNumbersDelay()
{
    int Monsters = GetLevelInfo(LEVELINFO_KILLED_MONSTERS);
    int TotalMonsters = GetLevelInfo(LEVELINFO_TOTAL_MONSTERS);
    
    return (TotalMonsters - Monsters) / DNUM_MONSTER_DIV;
}
