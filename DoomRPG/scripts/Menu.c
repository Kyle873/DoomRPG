#include "Defs.h"

#include "Augs.h"
#include "Crate.h"
#include "ItemData.h"
#include "Map.h"
#include "Menu.h"
#include "Minigame.h"
#include "Mission.h"
#include "RPG.h"
#include "Shield.h"
#include "Shop.h"
#include "Skills.h"
#include "Stats.h"
#include "Stims.h"
#include "Turret.h"
#include "Payout.h"
#include "Utils.h"

str RPGMap MainMenu[MAX_MENU] =
{
    "Stats",
    "Augmentations",
    "Skills",
    "Shield",
    "Stims",
    "Turret",
    "Shop"
};

str RPGMap MainMenuColor[MAX_MENU] =
{
    "Red",
    "Yellow",
    "LightBlue",
    "Cyan",
    "Gray",
    "Green",
    "Gold"
};

str RPGMap CursorColors[6] =
{
    "Blue", "LightBlue", "Cyan", "White", "Cyan", "LightBlue"
};

str RPGMap PayReadyColors[4] =
{
    "Brown", "Yellow", "Gold", "Yellow",
};

str RPGMap MenuCursorColor;
str RPGMap PayReadyColor;

/* --------------------------------------------------

   GUI MENU
   
   Extremely super WIP, not even close to working
   Don't fuck with it, it'll eat your face and probably
   steal your lunch money too

   -------------------------------------------------- */

NamedScript void UpdateMenu()
{
    while (true)
    {
        Delay(1);
    }
}

// --------------------------------------------------
   
NamedScript KeyBind void OpenMenu()
{
    // If you're dead, terminate
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    //If in the Mission BBS menu or Transport Menu
    if (Player.OutpostMenu == OMENU_BBS || Player.OutpostMenu == OMENU_LEVELTRANSPORT) 
    {
      ActivatorSound("menu/leave", 127);
      SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
      Player.OutpostMenu = 0;
      return;
    }
    
    // If you're in an Outpost menu, return
    if (Player.OutpostMenu > 0) return;
    
    // If you're in any minigames, terminate
    if (Player.InMinigame) return;
    
    // If you're looking inside a crate, return
    if (Player.CrateOpen) return;
    
    if (Player.InShop && CurrentLevel->UACBase)
    {
        ActivatorSound("menu/leave", 127);
        SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
        Player.InMenu = false;
        Player.InShop = false;
        return;
    }
    else if (Player.InShop)
        Player.InShop = false;
    
    if (Player.InMenu)
    {
        if (Player.Menu > 0) 
        {
            Player.Menu = MENUPAGE_MAIN;
            Player.MenuIndex = 0;
            ClearToxicityMeter();
            return;
        }
        else
        {
            ActivatorSound("menu/leave", 127);
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.InMenu = false;
            Player.MenuIndex = 0;
            Player.Menu = MENUPAGE_MAIN;
            ClearToxicityMeter();
        }
    }
    else
    {
      if (GetCVar("drpg_debug"))
            Log("\CdDEBUG: \CfOpening Menu");
        ActivatorSound("menu/enter", 127);
        Player.InMenu = true;
        Player.Menu = MENUPAGE_MAIN;
        Player.MenuIndex = 0;
    }
}

void MenuLoop()
{
    // Freeze the Player
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    
    // Set the HUD Size
    SetHudSize(GetActivatorCVar("drpg_menu_width"), GetActivatorCVar("drpg_menu_height"), true);
    
    // Draw current menu
    if (Player.Menu == MENUPAGE_MAIN)   DrawMainMenu();
    if (Player.Menu == MENUPAGE_STATS)  DrawStatsMenu();
    if (Player.Menu == MENUPAGE_AUGS)   DrawAugsMenu();
    if (Player.Menu == MENUPAGE_SKILLS) DrawSkillMenu();
    if (Player.Menu == MENUPAGE_SHIELD) DrawShieldMenu();
    if (Player.Menu == MENUPAGE_STIMS)  DrawStimsMenu();
    if (Player.Menu == MENUPAGE_TURRET) DrawTurretMenu();
    
    // Handle menu input
    MenuInput();
}

void DrawMainMenu()
{
    fixed X = 0.0;
    fixed Y = 10.0;
    int CurrentKills = GetLevelInfo(LEVELINFO_KILLED_MONSTERS);
    int CurrentItems = GetLevelInfo(LEVELINFO_FOUND_ITEMS);
    int CurrentSecretsFound = GetLevelInfo(LEVELINFO_FOUND_SECRETS);
    int TotalKills = GetLevelInfo(LEVELINFO_TOTAL_MONSTERS);
    int TotalItems = GetLevelInfo(LEVELINFO_TOTAL_ITEMS);
    int TotalSecretsFound = GetLevelInfo(LEVELINFO_TOTAL_SECRETS);
    int Modules = CheckInventory("DRPGModule");
    int TurretParts = CheckInventory("DRPGTurretPart");
    int AugCanisters = CheckInventory("DRPGAugCanister");
    int AugUpgradeCanisters = CheckInventory("DRPGAugUpgradeCanister");
    int SmallStims = CheckInventory("DRPGStimSmall");
    int MediumStims = CheckInventory("DRPGStimMedium");
    int LargeStims = CheckInventory("DRPGStimLarge");
    int XLStims = CheckInventory("DRPGStimXL");
    int GoldChips = CheckInventory("DRPGChipGold");
    int PlatinumChips = CheckInventory("DRPGChipPlatinum");
    bool AllKills = (CurrentLevel && CurrentLevel->KillBonus);
    bool AllItems = (CurrentLevel && CurrentLevel->ItemsBonus);
    bool AllSecrets = (CurrentLevel && CurrentLevel->SecretsBonus);
    
    if (!CurrentLevel->UACBase && !GetCVar("drpg_shoptype"))
    {
        MainMenuColor[6] = "Blue";
        MainMenu[6] = "Locker";
    }
    else
    {
        MainMenuColor[6] = "Gold";
        MainMenu[6] = "Shop";
    }
    
    SetFont("BIGFONT");
    
    // Clear the tips
    HudMessage("");
    EndHudMessage(HUDMSG_PLAIN, MAKE_ID('1','T','I','P'), "Untranslated", 0, 0, 0.05);
    HudMessage("");
    EndHudMessage(HUDMSG_PLAIN, MAKE_ID('2','T','I','P'), "Untranslated", 0, 0, 0.05);
    
    // Draw Menu
    for (int i = 0; i < MAX_MENU; i++)
    {
        HudMessage("%S", MainMenu[i]);
        EndHudMessage(HUDMSG_PLAIN, 0, (i == Player.MenuIndex ? MenuCursorColor : MainMenuColor[i]), X + 0.1, Y, 0.05);
        
        Y += 15.0;
        if (i > 0 && i % 5 == 0)
        {
            X += 192.0;
            Y = 10.0;
        }
    }
    
    // Reset X
    X = 0;
    
    // Player Icon
    DrawPlayerSprite(PlayerNumber(), 16.1, 148.1);

    // XP/Rank Display
    SetFont("BIGFONT");
    HudMessage("Level: %d", Player.Level);
    EndHudMessage(HUDMSG_PLAIN, 0, "White",          40.1, 100.0, 0.05);
    HudMessage("XP: %ld / %ld", Player.XP, Player.XPNext);
    EndHudMessage(HUDMSG_PLAIN, 0, "White",          40.1, 112.0, 0.05);
    HudMessage("Title: %S (%d/%d)", Ranks[Player.RankLevel], Player.RankLevel, MAX_RANK);
    EndHudMessage(HUDMSG_PLAIN, 0, "Yellow",         40.1, 124.0, 0.05);
    HudMessage("Rank: %ld / %ld", Player.Rank, Player.RankNext);
    EndHudMessage(HUDMSG_PLAIN, 0, "Yellow",         40.1, 136.0, 0.05);
    if (Player.PayReady && !Player.PayingOut)
        HudMessage("PP: %d (%S) [\C[%S]Ready\C-]", Player.PP, FormatTime(Player.PayTimer), PayReadyColor);
    else
        HudMessage("PP: %d (%S)", Player.PP, FormatTime(Player.PayTimer));
    EndHudMessage(HUDMSG_PLAIN, 0, "Gold",           40.1, 148.0, 0.05);
    
    if (GetPlayerInput(PlayerNumber(), INPUT_BUTTONS) & BT_SPEED && Player.Mission.Active)
        DrawMissionInfo(&Player.Mission, 16, 188, true);
    else
    {
        // Quick Reference
        SetFont("BIGFONT");
        HudMessage("%d", Modules);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",          40.1, 188.0, 0.05);
        HudMessage("%d", TurretParts);
        EndHudMessage(HUDMSG_PLAIN, 0, "White",          40.1, 216.0, 0.05);
        HudMessage("%d", AugCanisters);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",          40.1, 240.0, 0.05);
        HudMessage("%d", AugUpgradeCanisters);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",          40.1, 257.0, 0.05);
        HudMessage("%d / %d", Player.Augs.SlotsUsed, Player.Augs.Slots);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",          40.1, 274.0, 0.05);
        HudMessage("%d%%", (int)Player.Augs.Battery);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow",         40.1, 295.0, 0.05);
        HudMessage("S: %d\nM: %d\nL: %d\nXL: %d", SmallStims, MediumStims, LargeStims, XLStims);
        EndHudMessage(HUDMSG_PLAIN, 0, "White",          40.1, 334.0, 0.05);
        PrintSprite("UMODA0", 0, 18.1, 198.1, 0.05);
        PrintSprite("TPRTA0", 0, 36.1, 224.1, 0.05);
        PrintSprite("AUGCA0", 0, 16.1, 252.1, 0.05);
        PrintSprite("AUGUA0", 0, 16.1, 264.1, 0.05);
        PrintSprite("AUGUB0", 0, 16.1, 284.1, 0.05);
        PrintSprite("AUGBATT", 0, 16.1, 296.1, 0.05);
        PrintSprite("STIMB0", 0, 16.1, 348.1, 0.05);
        
        // Level Stats
        if (!CurrentLevel->UACBase)
        {
            SetFont("BIGFONT");
            HudMessage("Monsters: %d / %d", CurrentKills, TotalKills);
            EndHudMessage(HUDMSG_PLAIN, 0, (AllKills ? MenuCursorColor : "Brick"),       180.1, 178.0, 0.05);
            HudMessage("Items: %d / %d", CurrentItems, TotalItems);
            EndHudMessage(HUDMSG_PLAIN, 0, (AllItems ? MenuCursorColor : "LightBlue"),   180.1, 193.0, 0.05);
            HudMessage("Secrets: %d / %d", CurrentSecretsFound, TotalSecretsFound);
            EndHudMessage(HUDMSG_PLAIN, 0, (AllSecrets ? MenuCursorColor : "Yellow"),    180.1, 207.0, 0.05);
        }
        
        // Chips
        SetFont("BIGFONT");
        HudMessage("%d", GoldChips);
        EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 156.0, 182.1, 0.05);
        HudMessage("%d", PlatinumChips);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 156.0, 194.1, 0.05);
        SetHudClipRect(140, 175, 16, 64);
        PrintSprite("CHIPGOLD", 0, 140.1, 178.1, 0.05);
        SetHudClipRect(156, 175, 16, 64);
        PrintSprite("CHIPPLAT", 0, 140.1, 178.1, 0.05);
        SetHudClipRect(0, 0, 0, 0);
        
        // Shield
        DrawShieldInfo(-1, 173, 232, 0);
        
        // Current Stim
        if (Player.Stim.Size > 0)
        {
            SetFont("BIGFONT");
            
            // Draw Stim selection
            if (Player.Stim.Size == 1)
            {
                HudMessage("Small Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 176.1, 290.0, 0.05);
            }
            else if (Player.Stim.Size == 2)
            {
                HudMessage("Medium Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 176.1, 290.0, 0.05);
            }
            else if (Player.Stim.Size == 3)
            {
                HudMessage("Large Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 176.1, 290.0, 0.05);
            }
            else if (Player.Stim.Size == 4)
            {
                HudMessage("Extra-Large Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 176.1, 290.0, 0.05);
            }

            // Stim Compound Bar
            if (Player.Stim.Size > 0)
                for (int i = 0; i < STIM_MAX; i++)
                    if (Player.Stim.Current[i] > 0)
                    {
                        DrawBar(StrParam("Stim%d", i + 1), 177 + X, 300, Player.Stim.Current[i], true);
                        X += Player.Stim.Current[i];
                    }
        }
        
        // Toxicity
        if (Player.Toxicity > 0 || Player.Stim.Size > 0)
            DrawToxicityBar(176.0, 320.0, false);
    }
}

void DrawStatsMenu()
{
    int *Stats[STAT_MAX] =
    {
        &Player.Strength,
        &Player.Defense,
        &Player.Vitality,
        &Player.Energy,
        &Player.Regeneration,
        &Player.Agility,
        &Player.Capacity,
        &Player.Luck
    };
    
    // Title
    SetFont("BIGFONT");
    if (Player.StatPage == STATPAGE_STATS)
    {
        HudMessage("Stats");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    }
    if (Player.StatPage == STATPAGE_STATXP)
    {
        HudMessage("Stats XP");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    }
    if (Player.StatPage == STATPAGE_PERKS)
    {
        HudMessage("Perks");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    }
    if (Player.StatPage == STATPAGE_TEAM)
    {
        HudMessage("Team");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    }
    
    // Stats Page
    if (Player.StatPage == STATPAGE_STATS)
    {
        int Cost = (int)((((fixed)*Stats[Player.MenuIndex] + 1) * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));
        if (Cost < 0)
            Cost = -Cost;
        else if (Cost == 0)
            Cost = (int)((1 * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));

        // Upgrade Modules
        PrintSprite("UMODA0", 0, 16.1, 304.1, 0.05);
        SetFont("BIGFONT");
        HudMessage("%d", CheckInventory("DRPGModule"));
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 40.1, 288.1, 0.05);
        HudMessage("-%d", Cost);
        EndHudMessage(HUDMSG_PLAIN, 0, "Red", 40.1, 302.1, 0.05);
        
        SetFont("BIGFONT");
        if (Player.MenuIndex == 0)
        {
            HudMessage("Strength: %d", Player.Strength);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   0.1,    25.0,   0.05);
        }
        if (Player.MenuIndex == 1)
        {
            HudMessage("Defense: %d", Player.Defense);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   200.1,  25.0,   0.05);
        }
        if (Player.MenuIndex == 2)
        {
            HudMessage("Vitality: %d", Player.Vitality);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   0.1,    75.0,   0.05);
        }
        if (Player.MenuIndex == 3)
        {
            HudMessage("Energy: %d", Player.Energy);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   200.1,  75.0,   0.05);
        }
        if (Player.MenuIndex == 4)
        {
            HudMessage("Regen: %d", Player.Regeneration);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   0.1,    125.0,  0.05);
        }
        if (Player.MenuIndex == 5)
        {
            HudMessage("Agility: %d", Player.Agility);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   200.1,  125.0,  0.05);
        }
        if (Player.MenuIndex == 6) 
        {
            HudMessage("Capacity: %d", Player.Capacity);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   0.1,    175.0,  0.05);
        }
        if (Player.MenuIndex == 7)
        {
            HudMessage("Luck: %d", Player.Luck);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor,   200.1,  175.0,  0.05);
        }

        // Primary Stats
        SetFont("BIGFONT");
        HudMessage("Strength: %d", Player.Strength);
        EndHudMessage(HUDMSG_PLAIN, 0, "Red",        0.1,    25.0,   0.05);
        HudMessage("Defense: %d", Player.Defense);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",      200.1,  25.0,   0.05);
        HudMessage("Vitality: %d", Player.Vitality);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",      0.1,    75.0,   0.05);
        HudMessage("Energy: %d", Player.Energy);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",  200.1,  75.0,   0.05);
        HudMessage("Regen: %d", Player.Regeneration);
        EndHudMessage(HUDMSG_PLAIN, 0, "Purple",     0.1,    125.0,  0.05);
        HudMessage("Agility: %d", Player.Agility);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange",     200.1,  125.0,  0.05);
        HudMessage("Capacity: %d", Player.Capacity);
        EndHudMessage(HUDMSG_PLAIN, 0, "Blue",       0.1,    175.0,  0.05);
        HudMessage("Luck: %d", Player.Luck);
        EndHudMessage(HUDMSG_PLAIN, 0, "Gold",       200.1,  175.0,  0.05);
        
        // Ammo Amounts
        int Bullets = CheckInventory("Clip");
        int MaxBullets = GetAmmoCapacity("Clip");
        int Shells = CheckInventory("Shell");
        int MaxShells = GetAmmoCapacity("Shell");
        int Rockets = CheckInventory("RocketAmmo");
        int MaxRockets = GetAmmoCapacity("RocketAmmo");
        int Cells = CheckInventory("Cell");
        int MaxCells = GetAmmoCapacity("Cell");
        
        // Secondary Stats
        SetFont("SMALLFONT");
        if (Player.Strength > 0)
        {
            HudMessage("+%d%% Base Damage", Player.Level * (10 - GameSkill()));
            EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   36.0,   0.05);
        }
        else
        {
            HudMessage("%d%% Base Damage", Player.Level * (10 - GameSkill()));
            EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   36.0,   0.05);
        }
        if (Player.Strength > 0)
        {
            HudMessage("+%d%% Bonus Damage", Player.BonusDamage);
            EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   44.0,   0.05);
        }
        else
        {
            HudMessage("%d%% Bonus Damage", Player.BonusDamage);
            EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   44.0,   0.05);
        }
        HudMessage("%.2kX Multiplier", (Player.DamageMult > 1k ? Player.DamageMult : 1k));
        EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   52.0,   0.05);
        if (Player.Strength > 0)
        {
            HudMessage("+%d%% Total Damage", (int)(Player.TotalDamage * (Player.DamageMult > 1k ? Player.DamageMult : 1k)));
            EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   60.0,   0.05);
        }
        else
        {
            HudMessage("%d%% Total Damage", (int)(Player.TotalDamage * (Player.DamageMult > 1k ? Player.DamageMult : 1k)));
            EndHudMessage(HUDMSG_PLAIN, 0, "Red",                30.1,   60.0,   0.05);
        }
        if (Player.Defense > 0)
        {
            HudMessage("%.2k%% Damage Reduction", (Player.Defense > 0 ? (1.0 - Player.DamageFactor) : 0) * 100.0);
            EndHudMessage(HUDMSG_PLAIN, 0, "Green",              230.1,  36.0,   0.05);
        }
        else
        {
            HudMessage("%.2k%% Damage Reduction", ((1.0 - Player.DamageFactor) * 100.0));
            EndHudMessage(HUDMSG_PLAIN, 0, "Green",              230.1,  36.0,   0.05);
        }
        HudMessage("%d Mass", Player.Mass);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",              230.1,  44.0,   0.05);
        HudMessage("%d Max HP", Player.HealthMax);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   86.0,   0.05);
        HudMessage("%d HP Regen", Player.HPAmount);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   94.0,   0.05);
        HudMessage("%.2k%% Status Resist", Player.StatusEffectResist);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   102.0,  0.05);
        HudMessage("%d Max EP", Player.EPMax);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",          230.1,  86.0,   0.05);
        HudMessage("%d EP Regen", Player.EPAmount);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",          230.1,  94.0,   0.05);
        HudMessage("%S Sec Aura Time", FormatTime(AURA_CALCTIME));
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",          230.1,  102.0,  0.05);
        HudMessage("%d Aura Range", (int)Player.Aura.Range);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",          230.1,  110.0,  0.05);
        HudMessage("HP Timer: %.2k Sec", (fixed)(Player.HPTime / (35.0K * 2.0K)));
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   136.0,  0.05);
        HudMessage("EP Timer: %.2k Sec", (fixed)(Player.EPTime / (35.0K * 2.0K)));
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",          30.1,   144.0,  0.05);
        HudMessage("Regen Bonus: %d Sec", (int)(5.0 + ((fixed)Player.Regeneration / 13.33)));
        EndHudMessage(HUDMSG_PLAIN, 0, "Purple",             30.1,   152.0,  0.05);
        HudMessage("Toxicity Regen: %d Sec", 30 - Player.ToxicityRegenBonus);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",              30.1,   160.0,  0.05);
        HudMessage("Speed: %.2k", Player.Speed);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange",             230.1,  136.0,  0.05);
        HudMessage("Jump Height: %.2k", Player.JumpHeight);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange",             230.1,  144.0,  0.05);
        HudMessage("%d%% Weapon Speed", Player.WeaponSpeed);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange",             230.1,  152.0,  0.05);
        HudMessage("%.2k%% Survival Bonus", Player.SurvivalBonus);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange",             230.1,  160.0,  0.05);
        HudMessage("Bullets: %d/%d", Bullets, MaxBullets);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   186.0,  0.05);
        HudMessage("Shells: %d/%d", Shells, MaxShells);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange",             30.1,   194.0,  0.05);
        HudMessage("Rockets: %d/%d", Rockets, MaxRockets);
        EndHudMessage(HUDMSG_PLAIN, 0, "DarkGray",           30.1,   202.0,  0.05);
        HudMessage("Cells: %d/%d", Cells, MaxCells);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green",              30.1,   210.0,  0.05);
        HudMessage("Aug Battery Max: %d%%", (int)Player.Augs.BatteryMax);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow",             30.1,   218.0,  0.05);
        HudMessage("Stim Vial Max: %d", Player.Stim.VialMax);
        EndHudMessage(HUDMSG_PLAIN, 0, "Cyan",               30.1,   226.0,  0.05);
        HudMessage("Medkit: %d/%d", Player.Medkit, Player.MedkitMax);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   234.0,  0.05);
        if (GetCVar("drpg_inv_capacity"))
        {
            HudMessage("Inventory: %d/%d", Player.InvItems, CheckInventoryMax());
            EndHudMessage(HUDMSG_PLAIN, 0, "White",          30.1,   242.0,  0.05);
        }
        if (CompatMode == COMPAT_DRLA)
        {
            HudMessage("Weapons: %d/%d", CheckInventory("RLWeaponLimit"), DRLA_WEAPON_MAX);
            EndHudMessage(HUDMSG_PLAIN, 0, "Brick",              30.1,   250.0,  0.05);
            HudMessage("Armors: %d/%d", CheckInventory("RLArmorInInventory"), DRLA_ARMOR_MAX);
            EndHudMessage(HUDMSG_PLAIN, 0, "Green",              30.1,   258.0,  0.05);
            HudMessage("Skulls: %d/%d", CheckInventory("RLSkullLimit"), DRLA_SKULL_MAX);
            EndHudMessage(HUDMSG_PLAIN, 0, "Orange",             30.1,   266.0,  0.05);
            HudMessage("Phase Devices: %d/%d", CheckInventory("RLPhaseDeviceLimit"), DRLA_DEVICE_MAX);
            EndHudMessage(HUDMSG_PLAIN, 0, "Gray",               30.1,   274.0,  0.05);
        };
        
        // Luck
        SetFont("BIGFONT");
        HudMessage("%d", LUCK_HEALTHDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.HealthDrop ? "Gold" : "Gray"), 246.0, 204.0, 0.05);
        HudMessage("%d", LUCK_EPDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.EPDrop ? "Gold" : "Gray"), 284.0, 204.0, 0.05);
        HudMessage("%d", LUCK_ARMORDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.ArmorDrop ? "Gold" : "Gray"), 322.0, 204.0, 0.05);
        HudMessage("%d", LUCK_WEAPONDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.WeaponDrop ? "Gold" : "Gray"), 246.0, 240.0, 0.05);
        HudMessage("%d", LUCK_POWERUPDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.PowerupDrop ? "Gold" : "Gray"), 284.0, 240.0, 0.05);
        HudMessage("%d", LUCK_STIMDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.StimDrop ? "Gold" : "Gray"), 322.0, 240.0, 0.05);
        HudMessage("%d", LUCK_MODULEDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.ModuleDrop ? "Gold" : "Gray"), 246.0, 275.0, 0.05);
        HudMessage("%d", LUCK_SHIELDDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.ShieldDrop ? "Gold" : "Gray"), 284.0, 276.0, 0.05);
        HudMessage("%d", LUCK_AUGDROP);
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.AugDrop ? "Gold" : "Gray"), 322.0, 276.0, 0.05);
        PrintSprite("MEDIA0", 0, 260.0, 212.0, 0.05);
        PrintSprite("EPUPA0", 0, 300.0, 218.0, 0.05);
        PrintSprite("ARM1A0", 0, 336.0, 210.0, 0.05);
        PrintSprite("PISTA0", 0, 258.0, 238.0, 0.05);
        PrintSprite("PINVA0", 0, 294.0, 245.0, 0.05);
        PrintSprite("STVLJ0", 0, 326.0, 238.0, 0.05);
        PrintSprite("UMODA0", 0, 257.0, 282.0, 0.05);
        PrintSprite("SHPAA0", 0, 302.0, 293.0, 0.05);
        PrintSprite("AUGCA0", 0, 334.0, 282.0, 0.05);
		SetFont("SMALLFONT");
        if (Player.Luck > 0)
        {
            HudMessage("\CfCredit\C- Drop Rate: \Cf+%d%%", Player.Luck);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 292.0, 0.05);
        }
		if (Player.HealthDrop)
        {
			HudMessage("\CaHealth\C- Drop Rate: \Cf%k%%", Player.HealthChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 300.0, 0.05);
        }
		if (Player.EPDrop)
        {
			HudMessage("\CnEP\C- Drop Rate: \Cf%k%%", Player.EPChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 308.0, 0.05);
        }
		if (Player.ArmorDrop)
        {
			HudMessage("\CdArmor\C- Drop Rate: \Cf%k%%", Player.ArmorChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 316.0, 0.05);
        }
		if (Player.WeaponDrop)
        {
			HudMessage("\CgWeapon\C- Drop Rate: \Cf%k%%", Player.WeaponChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 324.0, 0.05);
        }
		if (Player.PowerupDrop)
        {
			HudMessage("\CqPowerup\C- Drop Rate: \Cf%k%%", Player.PowerupChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 332.0, 0.05);
        }
		if (Player.StimDrop)
        {
			HudMessage("\CrStim\C- Drop Rate: \Cf%k%%", Player.StimChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 340.0, 0.05);
        }
		if (Player.ModuleDrop)
        {
			HudMessage("\CdModule\C- Drop Rate: \Cf%k%%", Player.ModuleChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 348.0, 0.05);
        }
		if (Player.ShieldDrop)
        {
			HudMessage("\CvShield\C- Drop Rate: \Cf%k%%", Player.ShieldChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 356.0, 0.05);
        }
		if (Player.AugDrop)
        {
			HudMessage("\CkAug\C- Drop Rate: \Cf%k%%", Player.AugChance);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 230.1, 364.0, 0.05);
        }
        
        // Perk Icons
        if (Player.Perks[STAT_STRENGTH]) PrintSprite("STATP", 0, 16.1 + 8.0, 60.1, 0.05);
        if (Player.Perks[STAT_DEFENSE]) PrintSprite("STATP", 0, 214.1 + 8.0, 56.1, 0.05);
        if (Player.Perks[STAT_VITALITY]) PrintSprite("STATP", 0, 16.1 + 8.0, 110.1, 0.05);
        if (Player.Perks[STAT_ENERGY]) PrintSprite("STATP", 0, 214.1 + 8.0, 112.1, 0.05);
        if (Player.Perks[STAT_REGENERATION]) PrintSprite("STATP", 0, 16.1 + 8.0, 162.1, 0.05);
        if (Player.Perks[STAT_AGILITY]) PrintSprite("STATP", 0, 214.1 + 8.0, 160.1, 0.05);
        if (Player.Perks[STAT_CAPACITY]) PrintSprite("STATP", 0, 16.1 + 8.0, 210.1, 0.05);
        if (Player.Perks[STAT_LUCK]) PrintSprite("STATP", 0, 216.1 + 8.0, 210.1, 0.05);
        
        // Icons
        PrintSprite("STAT1", 0, 16.1, 60.1, 0.05);
        PrintSprite("STAT2", 0, 214.1, 56.1, 0.05);
        PrintSprite("STAT3", 0, 16.1, 110.1, 0.05);
        PrintSprite("STAT4", 0, 214.1, 112.1, 0.05);
        PrintSprite("STAT5", 0, 16.1, 162.1, 0.05);
        PrintSprite("STAT6", 0, 214.1, 160.1, 0.05);
        PrintSprite("STAT7", 0, 16.1, 210.1, 0.05);
        PrintSprite("STAT8", 0, 216.1, 210.1, 0.05);
    };
    
    // Stats XP Page
    if (Player.StatPage == STATPAGE_STATXP)
    {
        str const StatNames[STAT_MAX] =
        {
            "Strength",
            "Defense",
            "Vitality",
            "Energy",
            "Regen",
            "Agility",
            "Capacity",
            "Luck"
        };
        
        int *Stats[STAT_MAX] =
        {
            &Player.Strength,
            &Player.Defense,
            &Player.Vitality,
            &Player.Energy,
            &Player.Regeneration,
            &Player.Agility,
            &Player.Capacity,
            &Player.Luck
        };
        
        long int *StatXP[STAT_MAX] =
        {
            &Player.StrengthXP,
            &Player.DefenseXP,
            &Player.VitalityXP,
            &Player.EnergyXP,
            &Player.RegenerationXP,
            &Player.AgilityXP,
            &Player.CapacityXP,
            &Player.LuckXP
        };
        
        for (int i = 0; i < STAT_MAX; i++)
        {
            // Icons
            if (*Stats[i] < Player.StatCap)
                PrintSprite(StrParam("STAT%d", i + 1), 0, 16.1, 56.1 + (i * 44.0), 0.05);
            else
                PrintSpritePulse(StrParam("STAT%d", i + 1), 0, 16.1, 56.1 + (i * 44.0), 0.75, 64.0, 0.25);
            
            // XP
            SetFont("BIGFONT");
            if (*Stats[i] < Player.StatCap)
            {
                HudMessage("%S: %ld/%ld (%d)", StatNames[i], *StatXP[i], StatTable[*Stats[i]], *Stats[i]);
                EndHudMessage(HUDMSG_PLAIN, 0, StatColors[i], 40.1, 32.0 + (i * 44.0), 0.05);
            }
            else
            {
                HudMessage("%S: %ld (%d)", StatNames[i], *StatXP[i], *Stats[i]);
                EndHudMessage(HUDMSG_PLAIN, 0, StatColors[i], 40.1, 32.0 + (i * 44.0), 0.05);
            }
            
            // Bar
            long int CurrentXP = *StatXP[i];
            long int LastXP = StatTable[*Stats[i] - 1];
            long int NextXP = StatTable[*Stats[i]];
            if (*Stats[i] == 0)
                LastXP = 0;
            long int StatPercent = ((CurrentXP - LastXP) * 100) / (NextXP - LastXP);
            if (*Stats[i] >= Player.StatCap)
                StatPercent = 100;
            if (StatPercent > 100)
                StatPercent = 100;
            DrawBar(StrParam("StatBar%d", i + 1), 40.1, 48.0 + (i * 44.0), StatPercent * 3, true);
            DrawBar("StatBarB", 40.1, 48.0 + (i * 44.0), 100 * 3, false);
        }
    }
    
    // Perks Page
    if (Player.StatPage == STATPAGE_PERKS)
    {
        // Holds the perk information
        str const PerkInfo[STAT_MAX][3] = 
        {
            // Strength
            {
                "Damage exponentially increases as health lowers",
                NULL
            },
            
            // Defense
            {
                "Damage taken exponentially decreases as health lowers",
                NULL
            },
            
            // Vitality
            {
                "No Movement Penalties",
                "2x HP regeneration rate below 10% health",
                NULL
            },
            
            // Energy
            {
                "2x EP regeneration rate when burned out",
                "Can stack an extra Aura every +10 Energy invested",
                NULL
            },
            
            // Regeneration
            {
                "Regeneration speeds increase as your HP/EP gets lower",
                NULL
            },
            
            // Agility
            {
                "+30% Survival Bonus",
                "Movement increases Regeneration speed",
                NULL
            },
            
            // Capacity
            {
                "Ammo regeneration",
                NULL
            },
            
            // Luck
            {
                "Always have full automap and scanner",
                NULL
            }
        };
        
        for (int i = 0; i < STAT_MAX; i++)
        {
            str Description = "";
            str Color = "Gray";
            
            // Icon
            if (Player.Perks[i])
                PrintSpritePulse(StrParam("STAT%d", i + 1), 0, 16.1, 56.1 + (i * 44.0), 0.75, 64.0, 0.25);
            else
                PrintSpriteAlpha(StrParam("STAT%d", i + 1), 0, 16.1, 56.1 + (i * 44.0), 0.05, 0.5);
            
            // Build description string
            for (int j = 0; PerkInfo[i][j] != NULL; j++)
                Description = StrParam("%S%S\n", Description, PerkInfo[i][j]);
            
            // Determine Color
            if (Player.Perks[i])
                Color = StatColors[i];
            
            // Descriptions
            SetFont("SMALLFONT");
            HudMessage("%S", Description);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, 40.1, 44.0 + (i * 44.0), 0.05);        
        }
    }
    
    // Team Page
    if (Player.StatPage == STATPAGE_TEAM)
    {
        PlayerData *PlayerPtr = &Players(Player.MenuIndex);
        int PlayerNum = Player.MenuIndex;
        fixed X = 32.1;
        fixed Y = 52.0;
        
        // Player List
        SetFont("SMALLFONT");
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (!PlayerInGame(i)) continue;
            
            // Currently selected
            if (Player.MenuIndex == i)
            {
                HudMessage("-->");
                EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, X - 24.0, Y, 0.05);
            }
            
            if (i == PlayerNumber())
            {
                HudMessage("%tS", i + 1);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", X, Y, 0.05);
            }
            else
            {
                HudMessage("%tS (\Ci%d\C-)", i + 1, Distance(Player.TID, Players(i).TID));
                EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            }
            
            Y += 8.0;
        }
        
        // Player Icon
        DrawPlayerSprite(PlayerNum, 184.1, 100.1);
        
        // XP/Rank
        SetFont("BIGFONT");
        HudMessage("Level: %d", PlayerPtr->Level);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 208.1, 56.0, 0.05);
        HudMessage("XP: %ld / %ld", PlayerPtr->XP, PlayerPtr->XPNext);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 208.1, 68.0, 0.05);
        HudMessage("Title: %S (%d/%d)", Ranks[PlayerPtr->RankLevel], PlayerPtr->RankLevel, MAX_RANK);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 208.1, 80.0, 0.05);
        HudMessage("Rank: %ld / %ld", PlayerPtr->Rank, PlayerPtr->RankNext);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 208.1, 92.0, 0.05);
        HudMessage("PP: %ld", PlayerPtr->PP);
        EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 208.1, 104.0, 0.05);
       
        // Stats
        HudMessage("%d", PlayerPtr->Strength);
        EndHudMessage(HUDMSG_PLAIN, 0, "Red", 244.0, 120.0, 0.05);
        HudMessage("%d", PlayerPtr->Defense);
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 244.0, 140.0, 0.05);
        HudMessage("%d", PlayerPtr->Vitality);
        EndHudMessage(HUDMSG_PLAIN, 0, "Brick", 244.0, 160.0, 0.05);
        HudMessage("%d", PlayerPtr->Energy);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue", 244.0, 180.0, 0.05);
        HudMessage("%d", PlayerPtr->Regeneration);
        EndHudMessage(HUDMSG_PLAIN, 0, "Purple", 244.0, 200.0, 0.05);
        HudMessage("%d", PlayerPtr->Agility);
        EndHudMessage(HUDMSG_PLAIN, 0, "Orange", 244.0, 220.0, 0.05);
        HudMessage("%d", PlayerPtr->Capacity);
        EndHudMessage(HUDMSG_PLAIN, 0, "Blue", 244.0, 240.0, 0.05);
        HudMessage("%d", PlayerPtr->Luck);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 244.0, 260.0, 0.05);
        PrintSprite("STAT1S", 0, 228.0, 139.0, 0.05);
        PrintSprite("STAT2S", 0, 228.0, 157.0, 0.05);
        PrintSprite("STAT3S", 0, 228.0, 179.0, 0.05);
        PrintSprite("STAT4S", 0, 228.0, 199.0, 0.05);
        PrintSprite("STAT5S", 0, 228.0, 221.0, 0.05);
        PrintSprite("STAT6S", 0, 228.0, 240.0, 0.05);
        PrintSprite("STAT7S", 0, 228.0, 260.0, 0.05);
        PrintSprite("STAT8S", 0, 228.0, 280.0, 0.05);
        
        // Augs
        for (int i = 0; i < AUG_MAX; i++)
        {
            AugInfoPtr AugPtr = &AugData[i];
            
            SetFont("SMALLFONT");
            
            if (PlayerPtr->Augs.Active[i])
            {
                HudMessage("E");
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 271.1 + ((i % 3) * 34.0), 140.0 + ((i / 3) * 34.0), 0.05);
            }
            
            // Draw the level and max level
            HudMessage("%d/%d", PlayerPtr->Augs.Level[i], AugPtr->MaxLevel);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 303.2 + ((i % 3) * 34.0), 140.0 + ((i / 3) * 34.0), 0.05);
            
            // Icon
            if (PlayerPtr->Augs.Active[i])
                PrintSprite(StrParam("Aug%dE", i + 1), 0, 280.1 + ((i % 3) * 34.0), 120.1 + ((i / 3) * 34.0), 0.05);
            else if (PlayerPtr->Augs.Level[i] > 0)
                PrintSprite(StrParam("Aug%dB", i + 1), 0, 280.1 + ((i % 3) * 34.0), 120.1 + ((i / 3) * 34.0), 0.05);
            else
                PrintSprite(StrParam("Aug%d", i + 1), 0, 280.1 + ((i % 3) * 34.0), 120.1 + ((i / 3) * 34.0), 0.05);
        }
        
        // Aug Battery
        PrintSprite("AUGBATT", 0, 286.1, 228.1, 0.05);
        SetFont("BIGFONT");
        HudMessage("%d%%", PlayerPtr->Augs.Battery);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 306.1, 228.0, 0.05);
        
        // Toxicity
        if (PlayerPtr->Toxicity > 0 || PlayerPtr->Stim.Size > 0)
            DrawToxicityBar(276.0, 250.0, true);
        
        // Shield
        DrawShieldInfo(Player.MenuIndex, 232, 281, 0);
        
        // Health/Armor
        int Health = PlayerPtr->ActualHealth;
        str Armor = (CompatMode == COMPAT_DRLA && CheckActorInventory(PlayerPtr->TID, "RLIndestructibleArmorWorn") ? "\CaIndestructible\Cd" : StrParam("%d", CheckActorInventory(PlayerPtr->TID, "Armor")));
        SetFont("SMALLFONT");
        if (CheckActorInventory(PlayerPtr->TID, "Armor") > 0)
        {
            HudMessage("\Ca%d Health\C- / \Cd%S Armor", Health, Armor);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 48.1, 348.0, 0.05);
        }
        else
        {
            HudMessage("\Ca%d Health", Health);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 48.1, 348.0, 0.05);
        }
        
        // Weapon
        for (int i = 0; i < ItemMax[0]; i++)
        {
            ItemInfoPtr ItemPtr = &ItemData[0][i];

            // Horrible, horrible hacks
            if (PlayerWeapon[PlayerNum] == ItemPtr->Actor)
            {
                SetFont("SMALLFONT");
                HudMessage("\CgWeapon: \C-%S", ItemPtr->Name);
                EndHudMessage(HUDMSG_PLAIN, 0, "White", 48.1, 356.0, 0.05);
                PrintSprite(ItemPtr->Sprite.Name, 0, 100.0 + ItemPtr->Sprite.XOff, 312 + ItemPtr->Sprite.YOff, 0.05);
                break;
            }
        }
        
        // Armor
        for (int i = 1; i < ItemMax[3]; i++)
        {
            ItemInfoPtr ItemPtr = &ItemData[3][i];
            str Actor = ItemPtr->Actor;

            // DoomRL Compatibility
            if (CompatMode == COMPAT_DRLA)
            {
                Actor = StrLeft(Actor, StrLen(Actor) - 6); // Strip "Pickup" off the end
                Actor = StrParam("%SToken", Actor);
            }
            
            if ((CompatMode == COMPAT_DRLA ? CheckActorInventory(PlayerPtr->TID, Actor) : GetArmorType(StrParam("%SEffect", Actor), PlayerNum)))
            {
                SetFont("SMALLFONT");
                HudMessage("\CdArmor: \C-%S", ItemPtr->Name);
                EndHudMessage(HUDMSG_PLAIN, 0, "White", 48.1, 364.0, 0.05);
                PrintSprite(ItemPtr->Sprite.Name, 0, 160.0 + ItemPtr->Sprite.XOff, 312 + ItemPtr->Sprite.YOff, 0.05);
                break;
            }
        }
    }
}

void DrawAugsMenu()
{
    // Titles
    SetFont("BIGFONT");
    HudMessage("Augmentations");
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    
    // Upgrade Requirements (if applicable)
    int SelectedIndex = Player.MenuIndex;
    AugInfoPtr SelectedAug = &AugData[SelectedIndex];
    str UpgradeCanisterAmount = "";
    str UpgradeComponentAmount = "";
    if (Player.Augs.Level[SelectedIndex] == 0)
    {
        UpgradeCanisterAmount = " \Cg(-1)";
    }
    else if (Player.Augs.Level[SelectedIndex] < SelectedAug->MaxLevel)
    {
        UpgradeCanisterAmount = " \Cg(-1)";
        UpgradeComponentAmount = StrParam(" \Cg(%d)", -(Player.Augs.Level[SelectedIndex] + 1));
    };
    
    // Aug Canisters
    PrintSprite("AUGCA0", 0, 200.0, 54.0, 0.05);
    SetFont("BIGFONT");
    HudMessage("%d%S", CheckInventory("DRPGAugCanister"), UpgradeCanisterAmount);
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 208.1, 30.0, 0.05);
    
    // Aug Upgrade Canisters
    PrintSprite("AUGUA0", 0, 200.0, 72.0, 0.05);
    SetFont("BIGFONT");
    HudMessage("%d%S", CheckInventory("DRPGAugUpgradeCanister"), UpgradeComponentAmount);
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 208.1, 53.0, 0.05);
    
    // Aug Slots
    PrintSprite("AUGUB0", 0, 204.0, 102.0, 0.05);
    SetFont("BIGFONT");
    HudMessage("%d / %d", Player.Augs.SlotsUsed, Player.Augs.Slots);
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 208.1, 76.0, 0.05);
    
    // Aug Battery Power
    PrintSprite("AUGBATT", 0, 200.0, 110.0, 0.05);
    SetFont("BIGFONT");
    HudMessage("%d%%", (int)Player.Augs.Battery);
    EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 208.1, 99.0, 0.05);
    
    // Draw Aug slots
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5; j++)
        {
            int Index = j + (i * 5);
            AugInfoPtr AugPtr = &AugData[Index];
            
            // Catch to make sure unimplemented stuff isn't drawn
            if (Index > AUG_MAX - 1) continue;
            
            // Draw the augs that we have
            SetFont("SMALLFONT");
            
            // Draw the E if it's equipped
            if (Player.Augs.Active[Index])
            {
                HudMessage("E");
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
            }
            
            // Draw the level and max level
            HudMessage("%d/%d", Player.Augs.Level[Index], AugPtr->MaxLevel);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 32.2 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
            
            // Icon
            if (Player.MenuIndex == Index)
            {
                if (Player.Augs.Active[Index])
                    PrintSpritePulse(StrParam("Aug%dE", Index + 1), 0, 9.1 + (j * 34.0), 28.1 + (i * 34.0), 0.75, 32.0, 0.25);
                else if (Player.Augs.Level[Index] > 0)
                    PrintSpritePulse(StrParam("Aug%dB", Index + 1), 0, 9.1 + (j * 34.0), 28.1 + (i * 34.0), 0.75, 32.0, 0.25);
                else
                    PrintSpritePulse(StrParam("Aug%d", Index + 1), 0, 9.1 + (j * 34.0), 28.1 + (i * 34.0), 0.75, 32.0, 0.25);
            }
            else
            {
                if (Player.Augs.Active[Index])
                    PrintSprite(StrParam("Aug%dE", Index + 1), 0, 9.1 + (j * 34.0), 28.1 + (i * 34.0), 0.05);
                else if (Player.Augs.Level[Index] > 0)
                    PrintSprite(StrParam("Aug%dB", Index + 1), 0, 9.1 + (j * 34.0), 28.1 + (i * 34.0), 0.05);
                else
                    PrintSprite(StrParam("Aug%d", Index + 1), 0, 9.1 + (j * 34.0), 28.1 + (i * 34.0), 0.05);
            }
            
            // Currently highlighted Aug's name/description
            SetFont("SMALLFONT");
            if (Player.MenuIndex == Index)
            {
                HudMessage("\Ca%S", AugPtr->Name);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 128.1, 0.05);
                
                for (int k = 0; k < AugPtr->MaxLevel; k++)
                {
                    AugInfoPtr AugIterPtr = &AugData[Player.MenuIndex];
                    
                    if (Player.Augs.Level[Index] <= k)
                    {
                        HudMessage("\Cu%S", AugIterPtr->Description[k]);
                        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 136.1 + (k * 8.0), 0.05);
                    }
                    else
                    {
                        HudMessage("\Cd%S", AugIterPtr->Description[k]);
                        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 136.1 + (k * 8.0), 0.05);
                    }
                }
            }

            // Draw the cursor
            if (Player.MenuIndex == Index)
                PrintSprite("SelectBo", 0, 2.1 + (j * 34.0), 36.0 + (i * 34.0), 0.05);

            // Boxes
            PrintSprite("ItemBox", 0, 0.1 + (j * 34.0), 36.0 + (i * 34.0), 0.05);
        }
}

void DrawSkillMenu()
{
    // Skill Catagories
    auto str SkillCategories[MAX_CATEGORIES] =
    {
        "\CaHealing/Support",
        "\CqPowerups",
        "\CnAuras",
        "\CgAttacks",
        "\CiSummoning",
        "\CcUtility"
    };
    
    SkillPtr CurrentSkill = &Skills[Player.SkillPage][Player.MenuIndex];
    SkillLevelInfo *SkillLevel = &Player.SkillLevel[Player.SkillPage][Player.MenuIndex];
    int SkillCost = ScaleEPCost(CurrentSkill->Cost * SkillLevel->CurrentLevel);
    int SkillCostNext = ScaleEPCost(CurrentSkill->Cost * (SkillLevel->CurrentLevel + 1));
    
    // Title
    SetFont("BIGFONT");
    HudMessage("Skills");
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);

    // Skill Category
    HudMessage("%S\C- \Cd(%d/%d)", SkillCategories[Player.SkillPage], Player.SkillPage + 1, MAX_CATEGORIES);
    EndHudMessage(HUDMSG_PLAIN, 0, "White", 0.1, 25.0, 0.05);
    
    // Upgrade Modules
    PrintSprite("UMODA0", 0, 232.1, 64.1, 0.05);
    SetFont("BIGFONT");
    if (SkillLevel->Level < CurrentSkill->MaxLevel)
    {
        HudMessage("%d \Cg(-%d)", CheckInventory("DRPGModule"), (int)((((fixed)SkillLevel->Level + 1) * (fixed)MODULE_SKILL_MULT) * GetCVarFixed("drpg_module_skillfactor")));
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 256.1, 54.0, 0.05);
    }
    else
    {
        HudMessage("%d", CheckInventory("DRPGModule"));
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 256.1, 54.0, 0.05);
    }
    
    // Skill Cost/Next Level Cost
    PrintSprite("EPUPA0", 0, 248.0, 88.1, 0.05);
    SetFont("BIGFONT");
    if (SkillLevel->Level == 0)
    {
        HudMessage("Base Cost: %d", SkillCostNext);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue", 256.1, 74.1, 0.05);
    }
    else if (SkillLevel->Level < CurrentSkill->MaxLevel)
    {
        HudMessage("%d\nNext Level: %d", SkillCost, SkillCostNext);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue", 256.1, 74.1, 0.05);
    }
    else
    {
        HudMessage("%d", SkillCost);
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue", 256.1, 74.1, 0.05);
    }
    
    // Skill Cost Multiplier/Refund
    if (Player.SkillCostMult > 0 || Player.SkillRefundMult > 0)
    {
        PrintSpritePulse("Aura", 0, 232.0, 111.0, 0.75, 64.0, 0.25);
        SetFont("BIGFONT");
        if (Player.SkillRefundMult > 0)
        {
            HudMessage("+%d%% Skill Cost\n%d%% Skill Cost Refund", Player.SkillCostMult, RoundInt(Player.SkillRefundMult * 100));
            EndHudMessage(HUDMSG_PLAIN, 0, "Cyan", 256.1, 112.0, 0.05);
        }
        else
        {
            HudMessage("+%d%% Skill Cost", Player.SkillCostMult);
            EndHudMessage(HUDMSG_PLAIN, 0, "Cyan", 256.1, 112.0, 0.05);
        }
    }
    
    // Active Aura Levels
    if (Player.Aura.Time > 0 || Player.Aura.Team)
    {
        str const AuraColors[AURA_MAX + 1] =
        {
            "Red",
            "Green",
            "White",
            "Brick",
            "Cyan",
            "Purple",
            "Orange",
            "Blue",
            "Yellow",
            "Black"
        };
        
        for (int i = 0; i < AURA_MAX; i++)
            if (Player.Aura.Type[i].Active)
            {
                PrintSpritePulse(AuraIcons[i], 0, 232.0 + (i * 24.0), 176.0, 0.75, 64.0, 0.25);
                SetFont("BIGFONT");
                HudMessage("%d", Player.Aura.Type[i].Level);
                EndHudMessage(HUDMSG_PLAIN, 0, AuraColors[i], 232.0 + (i * 24.0), 160.0, 0.05);
            }
    }
    
    // Skill Grid
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
        {
            int Index = j + (i * 6);
            SkillPtr CurrentSkillIter = &Skills[Player.SkillPage][Index];
            SkillLevelInfo *SkillLevelIter = &Player.SkillLevel[Player.SkillPage][Index];
            str Color = "Red";
            
            // Break when we reach the last skill
            if (Index >= SkillCategoryMax[Player.SkillPage]) break;
            
            SetFont("SMALLFONT");
            
            // This skill is on a skill key
            for (int k = 0; k < MAX_SKILLKEYS; k++)
                if (Player.SkillCategory[k] == Player.SkillPage && Player.SkillIndex[k] == Index)
                {
                    HudMessage("%d", k + 1);
                    EndHudMessage(HUDMSG_PLAIN, 0, "White", 24.1 + (j * 34.0), 40.0 + (i * 34.0), 0.05);
                }
            
            // Determine Skill Levels Color
            if (SkillLevelIter->Level >= CurrentSkillIter->MaxLevel)
                Color = "Green";
            else if (SkillLevelIter->Level > 0)
                Color = "White";
            
            // Skill Levels
            HudMessage("%d/%d", SkillLevelIter->CurrentLevel, CurrentSkillIter->MaxLevel);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, 0.1 + (j * 34.0), 64.0 + (i * 34.0), 0.05);
            
            // Skill Icon
            if (Player.MenuIndex == Index)
                PrintSpritePulse(Skills[Player.SkillPage][Index].Icon, 0, 0.1 + (j * 34.0), 52.0 + (i * 34.0), 0.75, 32.0, 0.25);
            else
                PrintSprite(Skills[Player.SkillPage][Index].Icon, 0, 0.1 + (j * 34.0), 52.0 + (i * 34.0), 0.05);
            
            // Highlight Box
            if (Player.MenuIndex == Index)
                PrintSprite("SelectBo", 0, 0.1 + (j * 34.0), 52.0 + (i * 34.0), 0.05);
            
            // Box
            PrintSprite("ItemBox", 0, 0.1 + (j * 34.0), 52.0 + (i * 34.0), 0.05);
        }
    
    // Skill Name
    SetFont("BIGFONT");
    HudMessage("%S", CurrentSkill->Name);
    EndHudMessage(HUDMSG_PLAIN, 0, (SkillLevel->Level > 0 ? "White" : "Red"), 0.1, 154.1, 0.05);
    
    // Skill Description
    SetFont("SMALLFONT");
    if (SkillLevel->Level > 0 && SkillLevel->Level < CurrentSkill->MaxLevel)
    {
        HudMessage("%S\n\n\CdNext Level\n%S",
                   CurrentSkill->Description[SkillLevel->CurrentLevel - 1],
                   CurrentSkill->Description[SkillLevel->Level]);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 0.1, 168.1, 0.05);
    }
    else if (SkillLevel->Level == CurrentSkill->MaxLevel)
    {
        HudMessage("%S", CurrentSkill->Description[SkillLevel->CurrentLevel - 1]);
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", 0.1, 168.1, 0.05);
    }
    else
    {
        HudMessage("%S", CurrentSkill->Description[0]);
        EndHudMessage(HUDMSG_PLAIN, 0, "DarkGray", 0.1, 168.1, 0.05);
    }
}
void DrawShieldMenu()
{
    str const PageTitles[4] =
    {
        "\CjBodies",
        "\CfBatteries",
        "\CnCapacitors",
        "\CdAccessories"
    };
    
    str Description = "";
    int Amount;
    
    // Title
    SetFont("BIGFONT");
    HudMessage("Shield");
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    
    // Page
    HudMessage("%S", PageTitles[Player.ShieldPage]);
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 208.1, 10.0, 0.05);
    
    // Reset New! status on highlighted parts
    if (Player.ShieldPage == SHIELDPAGE_ACCESSORY)
    {
        if (Player.NewShieldAccessoryParts[Player.MenuIndex])
            Player.NewShieldAccessoryParts[Player.MenuIndex] = false;
    }
    else
    {
        if (Player.NewShieldParts[Player.ShieldPage][Player.MenuIndex])
            Player.NewShieldParts[Player.ShieldPage][Player.MenuIndex] = false;
    }
    
    // Draw Components
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ShieldPartPtr CurrentPart;
            ShieldAccsPtr CurrentAccessory;
            int MaxItems;
            int Index = j + (i * 10);
            
            if (Player.ShieldPage == SHIELDPAGE_ACCESSORY)
            {
                CurrentAccessory = &ShieldAccessories[Index];
                MaxItems = MAX_ACCESSORIES;
            }
            else
            {
                CurrentPart = &ShieldParts[Player.ShieldPage][Index];
                MaxItems = ShieldPartsMax[Player.ShieldPage];
            }
            
            // Break if we're at the end of the list
            if (Index >= MaxItems) break;
            
            // Draw Available Components
            if (Index < MaxItems)
            {
                SetFont("SMALLFONT");
                
                // NEW!
                if (Player.ShieldPage == SHIELDPAGE_BODY && Player.NewShieldParts[SHIELDPAGE_BODY][Index] && CheckInventory(CurrentPart->Actor) > 0)
                {
                    HudMessage("NEW!");
                    EndHudMessage(HUDMSG_PLAIN, 0, "White",     0.1 + (j * 34.0), 20.1 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_BATTERY && Player.NewShieldParts[SHIELDPAGE_BATTERY][Index] && CheckInventory(CurrentPart->Actor) > 0)
                {
                    HudMessage("NEW!");
                    EndHudMessage(HUDMSG_PLAIN, 0, "Gold",      0.1 + (j * 34.0), 20.1 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_CAPACITOR && Player.NewShieldParts[SHIELDPAGE_CAPACITOR][Index] && CheckInventory(CurrentPart->Actor) > 0)
                {
                    HudMessage("NEW!");
                    EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue", 0.1 + (j * 34.0), 20.1 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_ACCESSORY && Player.NewShieldAccessoryParts[Index] && CheckInventory(CurrentAccessory->Actor) > 0)
                {
                    HudMessage("NEW!");
                    EndHudMessage(HUDMSG_PLAIN, 0, "Green",     0.1 + (j * 34.0), 20.1 + (i * 34.0), 0.05);
                }
                
                // Draw Equipped Status
                if (Player.ShieldPage == SHIELDPAGE_BODY && Player.Shield.Body && !StrCmp(Player.Shield.Body->Actor, CurrentPart->Actor))
                {
                    HudMessage("E");
                    EndHudMessage(HUDMSG_PLAIN, 0, "White",        0.1 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_BATTERY && Player.Shield.Battery && !StrCmp(Player.Shield.Battery->Actor, CurrentPart->Actor))
                {
                    HudMessage("E");
                    EndHudMessage(HUDMSG_PLAIN, 0, "Gold",         0.1 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_CAPACITOR && Player.Shield.Capacitor && !StrCmp(Player.Shield.Capacitor->Actor, CurrentPart->Actor))
                {
                    HudMessage("E");
                    EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue",    0.1 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_ACCESSORY && Player.Shield.Accessory && !StrCmp(Player.Shield.Accessory->Actor, CurrentAccessory->Actor))
                {
                    HudMessage("E");
                    EndHudMessage(HUDMSG_PLAIN, 0, "Green",        0.1 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
                }
                
                // Draw Quantity if you have more than one
                if (Player.ShieldPage < SHIELDPAGE_ACCESSORY && CheckInventory(CurrentPart->Actor) > 1)
                {
                    HudMessage("%d", CheckInventory(CurrentPart->Actor));
                    EndHudMessage(HUDMSG_PLAIN, 0, "White", 32.2 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
                }
                if (Player.ShieldPage == SHIELDPAGE_ACCESSORY && CheckInventory(CurrentAccessory->Actor) > 1)
                {
                    HudMessage("%d", CheckInventory(CurrentAccessory->Actor));
                    EndHudMessage(HUDMSG_PLAIN, 0, "White", 32.2 + (j * 34.0), 48.0 + (i * 34.0), 0.05);
                }
            }
            
            // Draw Components and set Description
            if (Player.ShieldPage < SHIELDPAGE_ACCESSORY)
            {
                if (Index < MaxItems && CheckInventory(CurrentPart->Actor))
                {
                    // Draw Component
                    if (Player.MenuIndex == Index)
                        PrintSpritePulse(CurrentPart->Icon, 0, 17.1 + (j * 34.0), 52.1 + (i * 34.0), 0.75, 32.0, 0.25);
                    else if (Player.NewShieldParts[Player.ShieldPage][Index])
                        PrintSpritePulse(CurrentPart->Icon, 0, 17.1 + (j * 34.0), 52.1 + (i * 34.0), 0.75, 64.0, 0.25);
                    else
                        PrintSprite(CurrentPart->Icon, 0, 17.1 + (j * 34.0), 52.1 + (i * 34.0), 0.05);
                    
                    // Set Description
                    if (Index == Player.MenuIndex)
                    {
                        // Name
                        Description = StrParam("%S", CurrentPart->Name);
                        
                        str Prepend;
                        
                        // Capacity
                        if (CurrentPart->Capacity < 0)
                            Prepend = "\Cc";
                        else
                            Prepend = "\Cj+";
                        if (CurrentPart->Capacity != 0)
                            Description = StrParam("%S\n%S%d Capacity", Description, Prepend, CurrentPart->Capacity);
                        
                        // Charge Rate
                        if (CurrentPart->ChargeRate < 0)
                            Prepend = "\Cc";
                        else
                            Prepend = "\Cj+";
                        if (CurrentPart->ChargeRate != 0)
                            Description = StrParam("%S\n%S%d Charge Rate/Sec", Description, Prepend, CurrentPart->ChargeRate);
                        
                        // Delay Rate
                        if (CurrentPart->DelayRate > 0)
                            Prepend = "\Cc+";
                        else
                            Prepend = "\Cj";
                        if (CurrentPart->DelayRate != 0)
                            Description = StrParam("%S\n%S%.2k Delay", Description, Prepend, CurrentPart->DelayRate);
                    }
                }
            }
            else if (Player.ShieldPage == SHIELDPAGE_ACCESSORY)
            {
                if (Index < MaxItems && CheckInventory(CurrentAccessory->Actor))
                {
                    // Draw Component
                    if (Player.MenuIndex == Index)
                        PrintSpritePulse(CurrentAccessory->Icon, 0, 17.1 + (j * 34.0), 52.1 + (i * 34.0), 0.75, 32.0, 0.25);
                    else if (Player.NewShieldAccessoryParts[Index])
                        PrintSpritePulse(CurrentAccessory->Icon, 0, 17.1 + (j * 34.0), 52.1 + (i * 34.0), 0.75, 64.0, 0.25);
                    else
                        PrintSprite(CurrentAccessory->Icon, 0, 17.1 + (j * 34.0), 52.1 + (i * 34.0), 0.05);
                    
                    // Set Description
                    if (Index == Player.MenuIndex)
                    {
                        // Name
                        Description = StrParam("%S", CurrentAccessory->Name);
                        
                        str Prepend;
                        
                        // Extra Description
                        if (CurrentAccessory->Description != "")
                            Description = StrParam("%S\n%S", Description, CurrentAccessory->Description);
                    }
                }
            }

            // Draw the cursor
            if (Player.MenuIndex == Index)
                PrintSprite("SelectBo", 0, 2.1 + (j * 34.0), 36.0 + (i * 34.0), 0.05);

            // Boxes
            PrintSprite("ItemBox", 0, 0.1 + (j * 34.0), 36.0 + (i * 34.0), 0.05);
        }
    }
    
    // Shield Stats/Model
    DrawShieldInfo(-1, 32, 272, 0);
    
    // Component Description
    SetFont("SMALLFONT");
    HudMessage("%S", Description);
    EndHudMessage(HUDMSG_PLAIN, 0, "White", 0.1, 320.1, 0.05);
}

void DrawStimsMenu()
{
    fixed X = 32.1;
    fixed Y = 50.0;
    str StimString;
    str Color;
    
    // Title
    SetFont("BIGFONT");
    HudMessage("Stims");
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    
    // Stim String
    if (Player.Stim.Size == 1)
        StimString = StrParam("Small Stim: %d/%d (\Cq+%d%% Toxicity\C-)", Player.Stim.Amount, Player.Stim.Capacity, Player.Stim.Toxicity);
    else if (Player.Stim.Size == 2)
        StimString = StrParam("Medium Stim: %d/%d (\Cq+%d%% Toxicity\C-)", Player.Stim.Amount, Player.Stim.Capacity, Player.Stim.Toxicity);
    else if (Player.Stim.Size == 3)
        StimString = StrParam("Large Stim: %d/%d (\Cq+%d%% Toxicity\C-)", Player.Stim.Amount, Player.Stim.Capacity, Player.Stim.Toxicity);
    else if (Player.Stim.Size == 4)
        StimString = StrParam("Extra-Large Stim: %d/%d (\Cq+%d%% Toxicity\C-)", Player.Stim.Amount, Player.Stim.Capacity, Player.Stim.Toxicity);
    else
    {
        if (Player.StimSelected == 0)
            StimString = StrParam("Small Stim: %d", CheckInventory("DRPGStimSmall"));
        else if (Player.StimSelected == 1)
            StimString = StrParam("Medium Stim: %d", CheckInventory("DRPGStimMedium"));
        else if (Player.StimSelected == 2)
            StimString = StrParam("Large Stim: %d", CheckInventory("DRPGStimLarge"));
        else if (Player.StimSelected == 3)
            StimString = StrParam("Extra-Large Stim: %d", CheckInventory("DRPGStimXL"));
    }
    
    // Set the Color
    if (Player.MenuIndex == 0)
        Color = MenuCursorColor;
    else if (Player.Stim.Size > 0)
        Color = "Green";
    else
        Color = "White";
    
    // Draw Current Stim
    HudMessage("%S", StimString);
    EndHudMessage(HUDMSG_PLAIN, 0, Color, 30.1, 24.0, 0.05);
    
    // Draw Current Stim Bar
    if (Player.Stim.Size > 0)
        for (int i = 0; i < STIM_MAX; i++)
            if (Player.Stim.Current[i] > 0)
            {
                DrawBar(StrParam("Stim%d", i + 1), X, 34, Player.Stim.Current[i], true);
                X += Player.Stim.Current[i];
            }
    
    for (int i = 1; i <= STIM_MAX; i++)
    {
        // Reset X
        X = 32.1;
        
        // Set the Color
        if (i == Player.MenuIndex)
            Color = MenuCursorColor;
        else
            Color = CompoundColors[i - 1];
        
        // Vial Bar
        int Amount = (int)(((fixed)Player.Stim.Vials[i - 1] / (fixed)(Player.Stim.VialMax + 1)) * 100.0);
        if (Amount > 100)
            Amount = 100;
        DrawBar(StrParam("Stim%d", i), X, Y, Amount);
        
        // Vial
        X += 112.0;
        SetFont("SMALLFONT");
        HudMessage("%S: %d/%d", CompoundNames[i - 1], Player.Stim.Vials[i - 1], Player.Stim.VialMax);
        EndHudMessage(HUDMSG_PLAIN, 0, Color, X, Y, 0.05);
        
        if (i == StimStatsEnd || i == StimPowerupStart)
            Y += 16.0;
        else
            Y += 8.0;
    }
    
    // Toxicity
    DrawToxicityBar(32.0, 240.0, false);
    
    // Immunity
    SetFont("BIGFONT");
    HudMessage("Immunity: %d%%", Player.StimImmunity);
    EndHudMessage(HUDMSG_PLAIN, 0, "DarkRed", 256.0, 240.0, 0.05);
}

// This was written while I am sick and messed up on medication
// Good luck figuring it out
// [KS] Challenge accepted
void DrawTurretMenu()
{
    int Count = 0;
    int Parts = CheckInventory("DRPGTurretPart");
    str Color = "Red";
    int PageMax = MAX_UPGRADES / TURRET_PAGE_MAX;
    int Page = Player.MenuIndex / TURRET_PAGE_MAX;
    TurretUpgradePtr Upgrade = &TurretUpgradeData[Player.MenuIndex];
    
    // Title
    SetFont("BIGFONT");
    if (Player.TurretPage == TURRETPAGE_COMMAND)
    {
        HudMessage("Turret (\CkCommand\C-)");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    }
    if (Player.TurretPage == TURRETPAGE_UPGRADE)
    {
        HudMessage("Turret (\CvUpgrade\C-)");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 0.1, 10.0, 0.05);
    }
    
    // Icon
    if (Player.Turret.Init)
        PrintSprite("PTURA3A7", 0, 32.1, 46.0 + (int)(Sin((fixed)Timer() / 64.0) * 8.0), 0.05);
    
    // Parts
    SetFont("BIGFONT");
    if (Player.Turret.Upgrade[Player.MenuIndex] < Upgrade->MaxLevel)
    {
        HudMessage("%d \Cg(-%d)", Parts, TurretUpgradeCost(Player.MenuIndex));
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 96.0, 38.0, 0.05);
    }
    else
    {
        HudMessage("%d", Parts);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 96.0, 38.0, 0.05);
    }
    PrintSprite("TPRTA0", 0, 96.1, 56.0, 0.05);
    
    // Timers
    DrawTurretTimers(160.0, 38.0);
    
    // Modules
    while (Count < TURRET_PAGE_MAX)
    {
        int Index = (Page * TURRET_PAGE_MAX) + Count;
        fixed X = 24.0 + ((Count % (TURRET_PAGE_MAX / 4)) * 48.0);
        fixed Y = 80.0 + ((Count / (TURRET_PAGE_MAX / 4)) * 48.0);
        TurretUpgradePtr UpgradeIter = &TurretUpgradeData[Index];
        
        // Stop if we've hit the page or upgrade max limit
        if (Index >= MAX_UPGRADES) break;
        
        // Highlight
        if (Index == Player.MenuIndex)
            PrintSpritePulse("TurrBoxH", 0, X, Y, 0.75, 32.0, 0.25);
        
        // Upgrade Level
        if (Player.TurretPage == TURRETPAGE_UPGRADE)
        {
            if (Player.Turret.Upgrade[Index] >= UpgradeIter->MaxLevel)
                Color = "Green";
            else if (Player.Turret.Upgrade[Index] > 0)
                Color = "White";
            else
                Color = "Red";
            SetFont("SMALLFONT");
            HudMessage("%d/%d", Player.Turret.Upgrade[Index], UpgradeIter->MaxLevel);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, X, Y + 16.0, 0.05);
        }
        else if (Player.Turret.Upgrade[Index] > 0)
            DrawTurretInfo(X, Y, Index);
        
        // Icon
        if (Index == Player.MenuIndex)
            PrintSpritePulse(StrParam("T_UPG%d", Index + 1), 0, X, Y, 0.75, 32.0, 0.25);
        else
            PrintSprite(StrParam("T_UPG%d", Index + 1), 0, X, Y, 0.05);
        
        // Box
        PrintSprite("TurrBoxB", 0, X, Y, 0.05);
        
        Count++;
    }
    
    // Upgrade Name
    SetFont("BIGFONT");
    HudMessage("%S", Upgrade->Name);
    EndHudMessage(HUDMSG_PLAIN, 0, "White", 0.1, 256.1, 0.05);
    
    // Upgrade Description
    SetFont("SMALLFONT");
    HudMessage("\Cd%S\n\Cv%S\n\Ck%S", Upgrade->Description, Upgrade->UpgradeInfo, Upgrade->CommandInfo);
    EndHudMessage(HUDMSG_PLAIN, 0, "White", 0.1, 284.1, 0.05);
}

void DrawTurretInfo(fixed X, fixed Y, int Index)
{
    str Info = "";
    
    switch (Index)
    {
    case TU_BUILD:
        if (Player.Turret.Active)
            Info = "\CdON";
        else
            Info = "\CaOFF";
        break;
    case TU_WEAPON_BULLET:
        if (Player.Turret.Weapon == TW_BULLET)
            Info = "\CaON";
        break;
    case TU_WEAPON_BULLET_CAPACITY:
        Y -= 4.0;
        Info = StrParam("\Ca%d\n\Ca%d", Player.Turret.BulletAmmo, Player.Turret.BulletAmmoMax);
        break;
    case TU_WEAPON_PELLET:
        if (Player.Turret.Weapon == TW_PELLET)
            Info = "\CiON";
        break;
    case TU_WEAPON_PELLET_CAPACITY:
        Y -= 4.0;
        Info = StrParam("\Ci%d\n\Ci%d", Player.Turret.ShellAmmo, Player.Turret.ShellAmmoMax);
        break;
    case TU_WEAPON_ROCKET:
        if (Player.Turret.Weapon == TW_ROCKET)
            Info = "\CcON";
        break;
    case TU_WEAPON_ROCKET_CAPACITY:
        Y -= 4.0;
        Info = StrParam("\Cc%d\n\Cc%d", Player.Turret.RocketAmmo, Player.Turret.RocketAmmoMax);
        break;
    case TU_WEAPON_PLASMA:
        if (Player.Turret.Weapon == TW_PLASMA)
            Info = "\CnON";
        break;
    case TU_WEAPON_PLASMA_CAPACITY:
        Y -= 4.0;
        Info = StrParam("\Cn%d\n\Cn%d", Player.Turret.PlasmaAmmo, Player.Turret.PlasmaAmmoMax);
        break;
    case TU_WEAPON_RAILGUN:
        if (Player.Turret.Weapon == TW_RAILGUN)
            Info = "\CdON";
        break;
    case TU_WEAPON_RAILGUN_CAPACITY:
        Y -= 4.0;
        Info = StrParam("\Cd%d\n\Cd%d", Player.Turret.RailAmmo, Player.Turret.RailAmmoMax);
        break;
    case TU_AMMO_AUTOLOADER:
        if (Player.Turret.Autoload)
            Info = "\CdON";
        else
            Info = "\CaOFF";
        break;
    case TU_AMMO_NANOGEN:
        Y -= 4.0;
        Info = StrParam("\Cj%d\n\CjSec", 15 - Player.Turret.Upgrade[TU_AMMO_NANOGEN]);
        break;
    case TU_WEAPON_SELFDESTRUCT:
        Info = "\CgGo";
        break;
    case TU_ARMOR_PLATING:
        Info = StrParam("\Ca%d", Player.Turret.HealthMax);
        break;
    case TU_ARMOR_PLATING_MELEE:
        Info = StrParam("\Cc%d%%", Player.Turret.Upgrade[TU_ARMOR_PLATING_MELEE] * 5);
        break;
    case TU_ARMOR_PLATING_BULLET:
        Info = StrParam("\Cj%d%%", Player.Turret.Upgrade[TU_ARMOR_PLATING_BULLET] * 5);
        break;
    case TU_ARMOR_PLATING_FIRE:
        Info = StrParam("\Cg%d%%", Player.Turret.Upgrade[TU_ARMOR_PLATING_FIRE] * 5);
        break;
    case TU_ARMOR_PLATING_PLASMA:
        Info = StrParam("\Cn%d%%", Player.Turret.Upgrade[TU_ARMOR_PLATING_PLASMA] * 5);
        break;
    case TU_ARMOR_MODULE_PHASE:
        Y -= 4.0;
        Info = StrParam("\Cn%d\n\CnSec", Player.Turret.Upgrade[TU_ARMOR_MODULE_PHASE]);
        break;
    case TU_ARMOR_MODULE_REPAIR:
        Y -= 4.0;
        Info = StrParam("\Ca%.2k\n\CaSec", 30 - (Player.Turret.Upgrade[TU_ARMOR_MODULE_REPAIR] * 2.5));
        break;
    case TU_ASSIST_HEALTH:
        Info = StrParam("\Ca%d%%", Player.Turret.Upgrade[TU_ASSIST_HEALTH] * 2);
        break;
    case TU_ASSIST_ARMOR:
        Y -= 4.0;
        Info = StrParam("\Cd%.2k\n\CdSec", 30 - (Player.Turret.Upgrade[TU_ASSIST_ARMOR] * 2.5));
        break;
    case TU_ASSIST_AUG:
        Y -= 4.0;
        Info = StrParam("\Ck%.2k\n\CkSec", 30 - (Player.Turret.Upgrade[TU_ASSIST_AUG] * 2.5));
        break;
    case TU_ASSIST_SHIELD:
        Y -= 4.0;
        Info = StrParam("\Cv%.2k\n\CvSec", 30 - (Player.Turret.Upgrade[TU_ASSIST_SHIELD] * 2.5));
        break;
    case TU_ASSIST_INJECTOR_TYPE:
        if (Player.Turret.StimFocused)
            Info = "\CdFocus";
        else
            Info = "\CcBroad";
        break;
    case TU_ASSIST_TELEPORT:
        if (Player.Turret.TeleportEnabled)
            Info = "\CdON";
        else
            Info = "\CaOFF";
        break;
    case TU_ASSIST_TEAM:
        Y -= 4.0;
        Info = StrParam("\Cj%d\n\CjRange", Player.Turret.Upgrade[TU_ASSIST_TEAM] * 256);
        break;
    case TU_SENSORS_MODULEFINDER:
    case TU_SENSORS_ITEMFINDER:
    case TU_SENSORS_SUPPLYFINDER:
        Info = "\CdGo";
        break;
    case TU_BATTERY_CAPACITY:
        Info = StrParam("\Ck%S", FormatTime(Player.Turret.BatteryMax * 35));
        break;
    case TU_BATTERY_GENERATOR_KINETIC:
        Y -= 4.0;
        Info = StrParam("\Ck%d Sec\n\CkDelay", 11 - Player.Turret.Upgrade[TU_BATTERY_GENERATOR_KINETIC]);
        break;
    case TU_BATTERY_GENERATOR_ILLUMINATION:
        Y -= 4.0;
        Info = StrParam("\Ck%d Sec\n\CkDelay", 11 - Player.Turret.Upgrade[TU_BATTERY_GENERATOR_ILLUMINATION]);
        break;
    case TU_BATTERY_GENERATOR_FORCE:
        Y -= 4.0;
        Info = StrParam("\Cj+%d\n\CjDMG", Player.Turret.Upgrade[TU_BATTERY_GENERATOR_FORCE]);
        break;
    case TU_BATTERY_GENERATOR_THERMAL:
        Y -= 4.0;
        Info = StrParam("\Cg+%d\n\CgDMG", Player.Turret.Upgrade[TU_BATTERY_GENERATOR_THERMAL]);
        break;
    case TU_BATTERY_GENERATOR_PLASMA:
        Y -= 4.0;
        Info = StrParam("\Cn+%d\n\CnDMG", Player.Turret.Upgrade[TU_BATTERY_GENERATOR_PLASMA]);
        break;
    case TU_BATTERY_GENERATOR_NUCLEAR:
        Y -= 4.0;
        Info = StrParam("\Cd+%d\n\CdDMG", Player.Turret.Upgrade[TU_BATTERY_GENERATOR_NUCLEAR]);
        break;
    case TU_COMMAND_DRAW_FIRE:
        if (Player.Turret.Command == TC_DRAW_FIRE)
            Info = "\CdON";
        break;
    case TU_COMMAND_HOLD_POSITION:
        if (Player.Turret.Command == TC_HOLD_POSITION)
            Info = "\CdON";
        break;
    }
    
    SetFont("SMALLFONT");
    HudMessage("%S", Info);
    EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 0.4, Y + 16.0, 0.05);
}

void DrawTurretTimers(fixed X, fixed Y)
{
    str const VialSprites[STIM_MAX] =
    {
        "STVLA0",
        "STVLB0",
        "STVLC0",
        "STVLD0",
        "STVLE0",
        "STVLF0",
        "STVLG0",
        "STVLH0",
        "STVLI0",
        "STVLJ0",
        "STVLK0",
        "STVLL0",
        "STVLM0",
        "STVLN0",
        "STVLO0",
        "STVLP0",
        "STVLQ0",
        "STVLR0",
        "STVLS0"
    };
    
    int VialType = (Timer() / 35) % STIM_MAX;
    
    // Timers
    if (Player.Turret.Init)
    {
        // Charge Timer
        SetFont("BIGFONT");
        HudMessage("%S", FormatTime(Player.Turret.ChargeTimer * 35));
        EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", X + 0.1, Y, 0.05);
        if (Player.Turret.Maintenance && Player.Turret.ChargeTimer > 0)
            PrintSpritePulse("TCharge", 0, X + 0.1, Y - 3.0, 0.5, 32.0, 0.5);
        else
            PrintSprite("TCharge", 0, X + 0.1, Y - 3.0, 0.05);
        
        // Repair Timer
        SetFont("BIGFONT");
        HudMessage("%S", FormatTime(Player.Turret.RepairTimer * 35));
        EndHudMessage(HUDMSG_PLAIN, 0, (Player.Turret.PaidForRepair ? "Brick" : "Red"), X + 64.1, Y, 0.05);
        if (Player.Turret.Maintenance && Player.Turret.RepairTimer > 0)
            PrintSpritePulse("TRepair", 0, X + 64.1, Y - 3.0, 0.5, 32.0, 0.5);
        else
            PrintSprite("TRepair", 0, X + 64.1, Y - 3.0, 0.05);
        
        // Refit Timer
        SetFont("BIGFONT");
        HudMessage("%S", FormatTime(Player.Turret.RefitTimer * 35));
        EndHudMessage(HUDMSG_PLAIN, 0, "LightBlue", X + 128.1, Y, 0.05);
        if (Player.Turret.Maintenance && Player.Turret.RefitTimer > 0)
            PrintSpritePulse("TRefit", 0, X + 128.1, Y - 3.0, 0.5, 32.0, 0.5);
        else
            PrintSprite("TRefit", 0, X + 128.1, Y - 3.0, 0.05);
        
        // Stim Timer
        if (Player.Turret.Upgrade[TU_ASSIST_INJECTOR])
        {
            SetFont("BIGFONT");
            if (Player.Turret.StimTimer > 0)
            {
                HudMessage("%S", FormatTime(Player.Turret.StimTimer * 35));
                EndHudMessage(HUDMSG_PLAIN, 0, "Gray", X + 204.1, Y, 0.05);
                PrintSpritePulse("STCAA0", 0, X + 204.1 - 16.0, Y - 3.0 + 2.0, 0.5, 32.0, 0.5);
            }
            else
            {
                HudMessage("Ready");
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", X + 204.1, Y, 0.05);
                PrintSprite(VialSprites[VialType], 0, X + 204.1 - 16.0 + 4.0, Y - 3.0 + 18.0, 0.05);
            }
        }
    }
}

void MenuInput()
{
    int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
    int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
    
    // Reset the menu block
    Player.MenuBlock = false;
    
    // Main Menu
    if (Player.Menu == MENUPAGE_MAIN)
    {
        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex--;
            if (Player.MenuIndex < 0) Player.MenuIndex = MAX_MENU - 1;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex++;
            if (Player.MenuIndex > MAX_MENU - 1) Player.MenuIndex = 0;
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            Player.MenuBlock = true;
            
            if (Player.MenuIndex == MAX_MENU - 1)
                OpenShop(false);
            else
            {
                ActivatorSound("menu/move", 127);
                Player.Menu = Player.MenuIndex + 1;
                Player.MenuIndex = 0;
                Player.DelayTimer = 0;
                ClearToxicityMeter();
            }
        }
        if (Buttons == BT_JUMP && !Player.PayingOut && CurrentLevel->UACBase)
            CalculatePayout();
    }
    
    // Stats menu
    if (Player.Menu == MENUPAGE_STATS && !Player.MenuBlock)
    {
        if (Buttons & BT_FORWARD && !(OldButtons & BT_FORWARD))
        {
            if (Player.StatPage == STATPAGE_STATS)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex -= 2;
                if (Player.MenuIndex < 0) Player.MenuIndex = STAT_MAX - 1;
            }
            else if (Player.StatPage == STATPAGE_TEAM)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex--;
                ClearToxicityMeter();
                if (Player.MenuIndex < 0) Player.MenuIndex = PlayerCount() - 1;
            }
        }
        if (Buttons & BT_BACK && !(OldButtons & BT_BACK))
        {
            if (Player.StatPage == STATPAGE_STATS)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex += 2;
                if (Player.MenuIndex > STAT_MAX - 1) Player.MenuIndex = 0;
            }
            else if (Player.StatPage == STATPAGE_TEAM)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex++;
                ClearToxicityMeter();
                if (Player.MenuIndex > PlayerCount() - 1) Player.MenuIndex = 0;
            }
        }
        if ((Buttons & BT_LEFT && !(OldButtons & BT_LEFT)) ||
            (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT)))
        {
            if (Buttons & BT_SPEED)
            {
                if (Player.StatPage > 0)
                {
                    ActivatorSound("menu/move", 127);
                    Player.StatPage--;
                    Player.MenuIndex = 0;
                    if (Player.StatPage == STATPAGE_STATXP && !GetCVar("drpg_levelup_natural"))
                        Player.StatPage--;
                }
            }
            else if (Player.StatPage == STATPAGE_STATS)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex--;
                if (Player.MenuIndex < 0) Player.MenuIndex = STAT_MAX - 1;
            }
        }
        if ((Buttons & BT_RIGHT && !(OldButtons & BT_RIGHT)) ||
            (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT)))
        {
            if (Buttons & BT_SPEED)
            {
                if (Player.StatPage < STATPAGE_MAX - (InMultiplayer ? 1 : 2))
                {
                    ActivatorSound("menu/move", 127);
                    Player.StatPage++;
                    Player.MenuIndex = 0;
                    if (Player.StatPage == STATPAGE_STATXP && !GetCVar("drpg_levelup_natural"))
                        Player.StatPage++;
                }
            }
            else if (Player.StatPage == STATPAGE_STATS)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex++;
                if (Player.MenuIndex > STAT_MAX - 1) Player.MenuIndex = 0;
            }
        }
        if (Buttons == BT_USE && (OldButtons != BT_USE || Player.DelayTimer > 35.0 * GetActivatorCVarFixed("drpg_menu_repeat")))
            if (Player.StatPage == STATPAGE_STATS)
                IncreaseStat(Player.MenuIndex);
            else if (Player.StatPage == STATPAGE_TEAM && Player.MenuIndex != PlayerNumber())
            {
                PlayerTeleport(Player.MenuIndex);
                Player.EP -= ScaleEPCost(50);
                Player.Menu = MENUPAGE_MAIN;
                Player.MenuIndex = 0;
                Player.InMenu = false;
                SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            }
        if (Buttons == BT_ATTACK && OldButtons != BT_ATTACK && Player.StatPage == STATPAGE_TEAM)
        {
            Player.PlayerView = Player.MenuIndex;
            ActivatorSound("menu/move", 127);
        }
        if (Buttons == BT_USE)
            Player.DelayTimer++;
    }
    
    // Augmentations menu
    if (Player.Menu == MENUPAGE_AUGS && !Player.MenuBlock)
    {
        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD && Player.MenuIndex > 0)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex -= 5;
            if (Player.MenuIndex < 0) Player.MenuIndex = 0;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK && Player.MenuIndex < AUG_MAX - 1)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex += 5;
            if (Player.MenuIndex > AUG_MAX - 1) Player.MenuIndex = AUG_MAX - 1;
        }
        if (((Buttons == BT_LEFT && OldButtons != BT_LEFT) ||
            (Buttons == BT_MOVELEFT && OldButtons != BT_MOVELEFT))
            && Player.MenuIndex > 0)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex--;
        }
        if (((Buttons == BT_RIGHT && OldButtons != BT_RIGHT) ||
            (Buttons == BT_MOVERIGHT && OldButtons != BT_MOVERIGHT))
            && Player.MenuIndex < AUG_MAX - 1)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex++;
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            EquipAug(Player.MenuIndex);
            
            // If the player starts manually toggling augs, don't try to automatically activate any later.
            ClearDisabledAugs();
        }
        if (Buttons & BT_SPEED && !(OldButtons & BT_SPEED))
            LevelUpAug(Player.MenuIndex);
    }
    
    // Skills Menu
    if (Player.Menu == MENUPAGE_SKILLS && !Player.MenuBlock && !Player.SkillWheelOpen)
    {
        if (Buttons & BT_FORWARD && !(OldButtons & BT_FORWARD))
        {
            if (Buttons & BT_SPEED)
            {
                if (Player.SkillLevel[Player.SkillPage][Player.MenuIndex].CurrentLevel > 1)
                {
                    Player.SkillLevel[Player.SkillPage][Player.MenuIndex].CurrentLevel--;
                    ActivatorSound("menu/move", 127);
                }
            }
            else if (Player.MenuIndex > 0)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex -= 6;
                if (Player.MenuIndex < 0) Player.MenuIndex = 0;
            }
        }
        if (Buttons & BT_BACK && !(OldButtons & BT_BACK))
        {
            if (Buttons & BT_SPEED)
            {
                if (Player.SkillLevel[Player.SkillPage][Player.MenuIndex].CurrentLevel < Player.SkillLevel[Player.SkillPage][Player.MenuIndex].Level)
                {
                    Player.SkillLevel[Player.SkillPage][Player.MenuIndex].CurrentLevel++;
                    ActivatorSound("menu/move", 127);
                }
            }
            else if (Player.MenuIndex < SkillCategoryMax[Player.SkillPage] - 1)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex += 6;
                if (Player.MenuIndex > SkillCategoryMax[Player.SkillPage] - 1) Player.MenuIndex = SkillCategoryMax[Player.SkillPage] - 1;
            }
        }
        if ((Buttons & BT_LEFT && !(OldButtons & BT_LEFT)) ||
            (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT)))
        {
            if (Buttons & BT_SPEED)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex = 0;
                Player.SkillPage--;
                if (Player.SkillPage < 0) Player.SkillPage = MAX_CATEGORIES - 1;
            }
            else if (Player.MenuIndex > 0)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex--;
            }
        }
        if ((Buttons & BT_RIGHT && !(OldButtons & BT_RIGHT)) ||
            (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT)))
        {
            if (Buttons & BT_SPEED)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex = 0;
                Player.SkillPage++;
                if (Player.SkillPage >= MAX_CATEGORIES) Player.SkillPage = 0;
            }
            else if (Player.MenuIndex < SkillCategoryMax[Player.SkillPage] - 1)
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex++;
            }
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
            IncreaseSkill(Player.SkillPage, Player.MenuIndex);
        if (Buttons & BT_ATTACK && !(OldButtons & BT_ATTACK))
            UseSkill(0);
    }
    
    // Shield Menu
    if (Player.Menu == MENUPAGE_SHIELD && !Player.MenuBlock)
    {
        int PartsMax;
        ShieldPartPtr CurrentPart;
        ShieldAccsPtr CurrentAccessory;
        
        if (Player.ShieldPage == 3)
        {
            CurrentAccessory = &ShieldAccessories[Player.MenuIndex];
            PartsMax = MAX_ACCESSORIES;
        }
        else
        {
            CurrentPart = &ShieldParts[Player.ShieldPage][Player.MenuIndex];
            PartsMax = ShieldPartsMax[Player.ShieldPage];
        }
        
        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex -= 10;
            if (Player.MenuIndex < 0) Player.MenuIndex = 0;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK)
        {
            ActivatorSound("menu/move", 127);
            Player.MenuIndex += 10;
            if (Player.MenuIndex > PartsMax - 1) Player.MenuIndex = PartsMax - 1;
        }
        if ((Buttons & BT_LEFT && !(OldButtons & BT_LEFT)) ||
            (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT)))
        {
            if (Buttons & BT_SPEED)
            {
                if (Player.ShieldPage > 0)
                {
                    ActivatorSound("menu/move", 127);
                    Player.ShieldPage--;
                    Player.MenuIndex = 0;
                }
            }
            else
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex--;
                if (Player.MenuIndex < 0) Player.MenuIndex = PartsMax - 1;
            }
        }
        if ((Buttons & BT_RIGHT && !(OldButtons & BT_RIGHT)) ||
            (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT)))
        {
            if (Buttons & BT_SPEED)
            {
                if (Player.ShieldPage < 3)
                {
                    ActivatorSound("menu/move", 127);
                    Player.ShieldPage++;
                    Player.MenuIndex = 0;
                }
            }
            else
            {
                ActivatorSound("menu/move", 127);
                Player.MenuIndex++;
                if (Player.MenuIndex > PartsMax - 1) Player.MenuIndex = 0;
            }
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            if (Player.MenuIndex < PartsMax)
            {
                for (int i = 0; i < SHIELDPAGE_ACCESSORY; i++)
                    if (i == Player.ShieldPage)
                        if (CheckInventory(CurrentPart->Actor))
                        {
                            if (i == SHIELDPAGE_BODY) Player.Shield.Body = CurrentPart;
                            if (i == SHIELDPAGE_BATTERY) Player.Shield.Battery = CurrentPart;
                            if (i == SHIELDPAGE_CAPACITOR) Player.Shield.Capacitor = CurrentPart;
                            
                            ActivatorSound("shield/equip", 127);
                        }
                if (Player.ShieldPage == SHIELDPAGE_ACCESSORY)
                    if (CheckInventory(CurrentAccessory->Actor))
                    {
                        SetShieldAccessory(CurrentAccessory);
                        
                        ActivatorSound("shield/equip", 127);
                    }
            }
        }
        if (Buttons & BT_USE && !(OldButtons & BT_USE) && Buttons & BT_SPEED)
        {
            if (Player.MenuIndex < PartsMax)
                for (int i = 0; i < SHIELDPAGE_MAX; i++)
                    if (i == Player.ShieldPage)
                    {
                        if (i == SHIELDPAGE_BODY) Player.Shield.Body = NULL;
                        if (i == SHIELDPAGE_BATTERY) Player.Shield.Battery = NULL;
                        if (i == SHIELDPAGE_CAPACITOR) Player.Shield.Capacitor = NULL;
                        if (i == SHIELDPAGE_ACCESSORY) RemoveShieldAccessory();
                        
                        ActivatorSound("shield/unequip", 127);
                    }
        }
    }
    
    // Stims Menu
    if (Player.Menu == MENUPAGE_STIMS && !Player.MenuBlock)
    {
        if (Buttons == BT_FORWARD && (OldButtons != BT_FORWARD || Player.DelayTimer > 35.0 * GetActivatorCVarFixed("drpg_menu_repeat")))
        {
            Player.MenuIndex--;
            ActivatorSound("menu/move", 127);
            if (Player.MenuIndex < 0) Player.MenuIndex = STIM_MAX;
        }
        if (Buttons == BT_FORWARD)
            Player.DelayTimer++;
        if (Buttons == BT_BACK && (OldButtons != BT_BACK || Player.DelayTimer > 35.0 * GetActivatorCVarFixed("drpg_menu_repeat")))
        {
            Player.MenuIndex++;
            ActivatorSound("menu/move", 127);
            if (Player.MenuIndex > STIM_MAX) Player.MenuIndex = 0;
        }
        if (Buttons == BT_BACK)
            Player.DelayTimer++;
        if (((Buttons == BT_LEFT && OldButtons != BT_LEFT) ||
            (Buttons == BT_MOVELEFT && OldButtons != BT_MOVELEFT))
            && Player.StimSelected > 0)
        {
            if (Player.Stim.Size > 0) return;
            
            Player.StimSelected--;
            ActivatorSound("menu/move", 127);
        }
        if (((Buttons == BT_RIGHT && OldButtons != BT_RIGHT) ||
            (Buttons == BT_MOVERIGHT && OldButtons != BT_MOVERIGHT))
            && Player.StimSelected < 4 - 1)
        {
            if (Player.Stim.Size > 0) return;
            
            Player.StimSelected++;
            ActivatorSound("menu/move", 127);
        }
        if (Buttons == BT_USE && (OldButtons != BT_USE || Player.DelayTimer > 35.0 * GetActivatorCVarFixed("drpg_menu_repeat")))
        {
            if (Player.MenuIndex == 0)
                SetStim(Player.StimSelected);
            else
                MixStim(Player.MenuIndex - 1);
        }
        if (Buttons == BT_USE)
            Player.DelayTimer++;
    }
    
    // Turret Menu
    if (Player.Menu == MENUPAGE_TURRET && !Player.MenuBlock)
    {
        if (Buttons & BT_FORWARD && !(OldButtons & BT_FORWARD) && Player.MenuIndex > 0)
        {
            Player.MenuIndex -= TURRET_PAGE_MAX / 4;
            if (Player.MenuIndex < 0) Player.MenuIndex = 0;
            ActivatorSound("menu/move", 127);
        }
        if (Buttons & BT_BACK && !(OldButtons & BT_BACK) && Player.MenuIndex < MAX_UPGRADES - 1)
        {
            Player.MenuIndex += TURRET_PAGE_MAX / 4;
            if (Player.MenuIndex >= MAX_UPGRADES - 1) Player.MenuIndex = MAX_UPGRADES - 1;
            ActivatorSound("menu/move", 127);
        }
        if (((Buttons & BT_LEFT && !(OldButtons & BT_LEFT)) ||
            (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT)))
            && Player.MenuIndex > 0)
        {
            Player.MenuIndex--;
            ActivatorSound("menu/move", 127);
        }
        if (((Buttons & BT_RIGHT && !(OldButtons & BT_RIGHT)) ||
            (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT)))
            && Player.MenuIndex < MAX_UPGRADES - 1)
        {
            Player.MenuIndex++;
            ActivatorSound("menu/move", 127);
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            if (Player.TurretPage == TURRETPAGE_COMMAND)
                TurretCommand(Player.MenuIndex);
            else if (Player.TurretPage == TURRETPAGE_UPGRADE)
                UpgradeTurret(Player.MenuIndex);
        }
        if (Buttons == BT_SPEED && OldButtons != BT_SPEED)
            TurretMaintenance();
        if (Buttons == BT_JUMP && OldButtons != BT_JUMP)
        {
            Player.TurretPage++;
            if (Player.TurretPage >= TURRETPAGE_MAX)
                Player.TurretPage = TURRETPAGE_COMMAND;
            ActivatorSound("menu/move", 127);
        }
    }
    
    // Reset the Delay Timer if no buttons are pressed
    if (Buttons == 0 && OldButtons == 0)
        Player.DelayTimer = 0;
}

void IncreaseStat(int Stat)
{
    int *Stats[STAT_MAX] =
    {
        &Player.Strength,
        &Player.Defense,
        &Player.Vitality,
        &Player.Energy,
        &Player.Regeneration,
        &Player.Agility,
        &Player.Capacity,
        &Player.Luck
    };
    
    long int *StatXP[STAT_MAX] =
    {
        &Player.StrengthXP,
        &Player.DefenseXP,
        &Player.VitalityXP,
        &Player.EnergyXP,
        &Player.RegenerationXP,
        &Player.AgilityXP,
        &Player.CapacityXP,
        &Player.LuckXP
    };
    
    // Don't allow increasing of stats while you have a stim active
    if (Player.Stim.Active)
    {
        if (!GetActivatorCVar("drpg_auto_spend"))
        {
            PrintError("You cannot increase stats while a stim is active");
            ActivatorSound("menu/error", 127);
        }
        
        return;
    }
    
    // Determine the cost of the stat upgrade
    int Cost = (int)((((fixed)*Stats[Stat] + 1) * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));
    if (Cost < 0)
        Cost = -Cost;
    else if (Cost == 0)
        Cost = (int)((1 * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));

    // Make sure you have enough Modules
    if (CheckInventory("DRPGModule") < Cost && (Player.InMenu || Player.GUI.Open))
    {
        if (Player.DelayTimer > 0 || GetActivatorCVar("drpg_auto_spend")) return;
        PrintError("You don't have enough Modules to upgrade this stat");
        ActivatorSound("menu/error", 127);
        
        return;
    }
    
    // Check Stat Caps
    CheckStatCaps();
    
    // Upgrade the Stat
    if (*Stats[Stat] < Player.StatCap)
    {
        if (GetCVar("drpg_levelup_natural")) // Natural Leveling
            *StatXP[Stat] = StatTable[*Stats[Stat]];
        else
            (*Stats[Stat])++;
    }
    else
    {
        if (!GetActivatorCVar("drpg_auto_spend")) // From the menu
            PrintStatError();
        
        return;
    }
    
    if (Player.InMenu || Player.GUI.Open) // Spent the point in the menu, make a sound
        ActivatorSound("menu/move", 127);
    
    TakeInventory("DRPGModule", Cost);
}

void IncreaseSkill(int Category, int Index)
{
    SkillPtr CurrentSkill = &Skills[Category][Index];
    SkillLevelInfo *SkillLevel = &Player.SkillLevel[Category][Index];
    int Cost = (int)((((fixed)SkillLevel->Level + 1) * (fixed)MODULE_SKILL_MULT) * GetCVarFixed("drpg_module_skillfactor"));
    
    if (CheckInventory("DRPGModule") >= Cost)
    {
        if (SkillLevel->Level < CurrentSkill->MaxLevel && CheckInventory("DRPGModule") >= Cost)
        {
            SkillLevel->Level++;
            SkillLevel->CurrentLevel++;
            TakeInventory("DRPGModule", Cost);
            ActivatorSound("menu/move", 127);
        }
    }
    else
    {
        PrintError("You don't have enough Modules");
        ActivatorSound("menu/error", 127);
    }
}

void UpgradeTurret(int Index)
{
    if (Index > 0 && !Player.Turret.Upgrade[TU_BUILD])
    {
        PrintError("You haven't built the turret yet");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    if (Player.Turret.Upgrade[Index] < TurretUpgradeData[Index].MaxLevel)
    {
        if (CheckInventory("DRPGTurretPart") >= TurretUpgradeCost(Index))
        {
            TakeInventory("DRPGTurretPart", TurretUpgradeCost(Index));
            ActivatorSound("turret/upgrade", 127);
            
            Player.Turret.Upgrade[Index]++;
            
            // Refit
            if (Index > 0)
            {
                TurretDespawn();
                Player.Turret.RefitTimer += Player.Turret.Upgrade[Index] * (10 - Player.Turret.Upgrade[TU_HARDWARE_SPECS]);
            }
            else // Build
            {
                Player.Turret.Health = 100;
                Player.Turret.RefitTimer += 60;
                
                // Automatically start maintenance to begin building the turret
                if (CheckInventory("DRPGCredits") > 0)
                    Player.Turret.Maintenance = true;
            }
        }
        else
        {
            PrintError("You don't have enough Turret Parts to perform this upgrade");
            ActivatorSound("menu/error", 127);
        }
    }
}

void PrintStatError()
{
    if (Player.DelayTimer > 0) return;
    
    SetHudSize(0, 0, false);
    SetFont("BIGFONT");
    HudMessage("You cannot increase stats past %d", Player.StatCap);
    EndHudMessage(HUDMSG_FADEOUT, 0, "Red", 0.5, 0.5, 2.0, 1.0);
    ActivatorSound("menu/error", 127);
}

void MenuHelp()
{
    fixed X = 0.1;
    fixed Y = 380.1;
    
    // Return if the help CVAR is off
    if (!GetActivatorCVar("drpg_menuhelp")) return;
    
    // Set the HUD Size and Font
    SetHudSize(GetActivatorCVar("drpg_menu_width"), GetActivatorCVar("drpg_menu_height"), true);
    SetFont("SMALLFONT");
    
    // Main Menu Help
    if (Player.InMenu && !Player.InShop)
        switch (Player.Menu)
        {
        case MENUPAGE_MAIN:
            HudMessage("\Cd%jS and %jS\C- to navigate\n\Cd%jS\C- to select\nHold \Cd%jS\C- to show current Mission Info",
                       "+forward", "+back", "+use", "+speed");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case MENUPAGE_STATS:
            if (Player.StatPage == STATPAGE_STATS)
            {
                HudMessage("\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS + %jS/%jS\C- to switch pages\n\Cd%jS\C- to Increase Stat",
                           "+forward", "+back", "+moveleft", "+moveright", "+speed", "+moveleft", "+moveright", "+use");
                EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            }
            else if (Player.StatPage == STATPAGE_STATXP || Player.StatPage == STATPAGE_PERKS)
            {
                HudMessage("\Cd%jS + %jS/%jS\C- to switch pages",
                           "+speed", "+moveleft", "+moveright");
                EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            }
            else if (Player.StatPage == STATPAGE_TEAM)
            {
                HudMessage("\Cd%jS/%jS\C- to navigate\n\Cd%jS + %jS/%jS\C- to switch pages\n\Cd%jS\C- to show Player's view on HUD\n\Cd%jS\C- to Teleport to selected Player (\Cn%d EP\C-)",
                           "+forward", "+back", "+speed", "+moveleft", "+moveright", "+attack", "+use", ScaleEPCost(50));
                EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            }
            break;
        case MENUPAGE_AUGS:
            HudMessage("\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS\C- to Toggle On/Off\n\Cd%jS\C- to Upgrade",
                       "+forward", "+back", "+moveleft", "+moveright", "+use", "+speed");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case MENUPAGE_SKILLS:
            HudMessage("\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS + %jS/%jS\C- to Switch Pages\n\Cd%jS\C- to Learn/Upgrade Skill\nHold \Cd%jS\C- to Assign Skill to Wheel Slot\n\Cd%jS + %jS/%jS\C- to Switch Current Skill Level\n\Cd%jS\C- to Quickuse selected skill",
                       "+forward", "+back", "+moveleft", "+moveright", "+speed", "+moveleft", "+moveright", "+use", "+user1", "+speed", "+forward", "+back", "+attack");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case MENUPAGE_SHIELD:
            HudMessage("\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS + %jS/%jS\C- to Switch Pages\n\Cd%jS\C- to Equip Part\n\Cd%jS + %jS\C- to Unequip Part",
                       "+forward", "+back", "+moveleft", "+moveright", "+speed", "+moveleft", "+moveright", "+use", "+speed", "+use");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case MENUPAGE_STIMS:
            HudMessage("\Cd%jS/%jS\C- to navigate\n\Cd%jS/%jS\C- to select Stim Size\n\Cd%jS\C- to Choose Stim or Add Compound to Stim",
                       "+forward", "+back", "+moveleft", "+moveright", "+use");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case MENUPAGE_TURRET:
            HudMessage("\Cd%jS\C- to Switch Pages\n\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS\C- to %S\n\Cd%jS\C- to %S\n\Cd%jS\C- to Exit",
                   "+jump", "+forward", "+back", "+moveleft", "+moveright", "+speed", Player.Turret.Maintenance? "reclaim Turret" : "maintenance Turret", "+use", (Player.TurretPage == TURRETPAGE_COMMAND)? "Issue Command" : "Upgrade Turret", "drpg_menu");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        }
    
    // Shop Menu Help
    if (!Player.InMenu && Player.InShop)
    {
        if (Player.LockerMode)
        {
            HudMessage("\Cd%jS\C- to switch to the Shop\n\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS + %jS/%jS\C- to Switch Pages\n\Cd%jS\C- to Deposit Item\n\Cd%jS + %jS\C- to Withdraw Item\n\Cd%jS\C- to toggle Auto-Storing of item\n\Cd%jS + %jS\C- to toggle Auto-Keeping of 1 item\n\Cd%jS\C- to Drop selected item\n\Cd%jS\C- to withdraw all items on the page\n\Cd%jS\C- to Exit",
                       "+jump", "+forward", "+back", "+moveleft", "+moveright", "+speed", "+moveleft", "+moveright", "+use", "+speed", "+use", "+attack", "+speed", "+attack", "+zoom", "+altattack", "drpg_menu");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
        }
        else
        {
            HudMessage("\Cd%jS\C- to switch to the Locker\n\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS + %jS/%jS\C- to Switch Pages\n\Cd%jS\C- to Buy Item\n\Cd%jS + %jS\C- to Sell Item\n\Cd%jS\C- to toggle Auto-Selling of item\n\Cd%jS + %jS\C- to toggle Auto-Keeping of 1 item\n\Cd%jS\C- to Drop selected item\n\Cd%jS\C- to Exit",
                       "+jump", "+forward", "+back", "+moveleft", "+moveright", "+speed", "+moveleft", "+moveright", "+use", "+speed", "+use", "+attack", "+speed", "+attack", "+zoom", "drpg_menu");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
        }
    }
    
    // Outpost Menus
    if (Player.OutpostMenu > 0)
    {
        switch (Player.OutpostMenu)
        {
        case OMENU_LEVELTRANSPORT:
            if (WadSmoosh)
            {
                HudMessage("\Cd%jS/%jS/%jS/%jS\C- to Select Level\n\Cd%jS+%jS/%jS+%jS\C- to Select IWAD\n\Cd%jS\C- to Teleport to Level\n\Cd%jS\C- to Exit",
                       "+forward", "+back", "+moveleft", "+moveright", "+speed", "+moveleft", "+speed", "+moveright", "+use", "drpg_menu");
            }
            else
            {
                HudMessage("\Cd%jS/%jS/%jS/%jS\C- to Select Level\n\Cd%jS\C- to Teleport to Level\n\Cd%jS\C- to Exit",
                       "+forward", "+back", "+moveleft", "+moveright", "+use", "drpg_menu");
            }
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case OMENU_SKILLCOMPUTER:
            HudMessage("\Cd%jS/%jS\C- to navigate\n\Cd%jS\C- to Change Skill\n\Cd%jS\C- to Exit",
                       "+forward", "+back", "+use", "+speed");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case OMENU_MODULECONVERTER:
            break;
        case OMENU_WAVESELECTOR:
            HudMessage("\Cd%jS/%jS/%jS/%jS\C- to Choose Wave\n\Cd%jS\C- to Change Wave\n\Cd%jS\C- to Exit",
                       "+forward", "+back", "+moveleft", "+moveright", "+use", "+speed");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case OMENU_SHOPSPECIAL:
            HudMessage("\Cd%jS\C- to buy\n\Cd%jS\C- to exit",
                       "+use", "+speed");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case OMENU_BONUSSELECTOR:
            HudMessage("\Cd%jS/%jS\C- to navigate\n\Cd%jS\C- to Select",
                       "+forward", "+back", "+use");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        case OMENU_BBS:
            HudMessage("\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS\C- to Accept Mission\n\Cd%jS\C- to Abort Mission\n\Cd%jS + %jS/%jS\C- to Switch Pages\n\Cd%jS\C- to Exit",
                       "+forward", "+back", "+moveleft", "+moveright", "+use", "+attack", "+speed", "+moveleft", "+moveright", "drpg_menu");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            break;
        }
    }
    
    // Crate Help
    if (Player.CrateOpen && Crates[Player.CrateID].Hacking == -1)
        HudMessage("\Cd%jS/%jS/%jS/%jS\C- to navigate\n\Cd%jS\C- to Take Item\n\Cd%jS\C- to Exit",
                   "+forward", "+back", "+moveleft", "+moveright", "+use", "+speed");
        EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
}

void DrawPlayerSprite(int PlayerNum, fixed X, fixed Y)
{
    if (CompatMode == COMPAT_DRLA)
    {
        if (PlayerClass(PlayerNum) == 0) // Marine
            PrintSprite("PMARA1", 0, X, Y, 0.05);
        if (PlayerClass(PlayerNum) == 1) // Scout
            PrintSprite("PSCOA1", 0, X + 4.0, Y - 2.0, 0.05);
        if (PlayerClass(PlayerNum) == 2) // Technician
            PrintSprite("PTECA1", 0, X + 2.0, Y - 2.0, 0.05);
        if (PlayerClass(PlayerNum) == 3) // Renegade
            PrintSprite("PRENA1", 0, X + 4.0, Y - 2.0, 0.05);
        if (PlayerClass(PlayerNum) == 4) // Demolitionist
            PrintSprite("PDMOA1", 0, X + 4.0, Y - 2.0, 0.05);
    }
    else
        PrintSprite("PLAYA1", 0, X, Y + 2.0, 0.05);
}

void DrawToxicityBar(fixed X, fixed Y, bool HideInfo)
{
    // Title
    SetFont("BIGFONT");
    HudMessage("Toxicity: %d%%", Player.Toxicity);
    EndHudMessage(HUDMSG_PLAIN, 0, "Green", X + 0.1, Y, 0.05);
    
    // Pixel Color
    str Color;
    if (Player.Toxicity >= 0 && Player.Toxicity <= 24)
        Color = "PGreen";
    if (Player.Toxicity >= 25 && Player.Toxicity <= 49)
        Color = "PYellow";
    if (Player.Toxicity >= 50 && Player.Toxicity <= 74)
        Color = "POrange";
    if (Player.Toxicity >= 75)
        Color = "PRed";
    
    // Beat
    int BeatTics[3] = { 8 / (1 + (Player.Toxicity >= 75)), 16 / (1 + (Player.Toxicity >= 50)), 8 / (1 + (Player.Toxicity >= 25)) };
    int TotalTics = 0;
    for (int i = 0; i < 3; i++)
        TotalTics += BeatTics[i];
    if ((Player.ToxicTimer % (35 * (3 - (int)((fixed)Player.Toxicity * 0.0275k)))) < TotalTics)
    {
        if (Player.ToxicOffset >= -8 && Player.ToxicStage == 0)
            Player.ToxicOffset -= 1 + (Player.Toxicity >= 75);
        if (Player.ToxicOffset <= 8 && Player.ToxicStage == 1)
            Player.ToxicOffset += 1 + (Player.Toxicity >= 50);
        if (Player.ToxicOffset >= 0 && Player.ToxicStage == 2)
            Player.ToxicOffset -= 1 + (Player.Toxicity >= 25);
        
        if (Player.ToxicOffset == -8)
            Player.ToxicStage = 1;
        if (Player.ToxicOffset == 8)
            Player.ToxicStage = 2;
        if (Player.ToxicOffset == 0 && Player.ToxicStage == 2)
            Player.ToxicStage = 0;
    }
    
    // Increase Timer
    Player.ToxicTimer++;

    // Draw Pixel
    if (Player.Toxicity >= 100)
        PrintSpriteFade(Color, TOXMETER_ID + (Player.ToxicTimer % 100), X + (Player.ToxicTimer % 100), Y + 16, 0.05, 1.0);
    else
        PrintSpriteFade(Color, TOXMETER_ID + (Player.ToxicTimer % 100), X + (Player.ToxicTimer % 100), Y + 16 + Player.ToxicOffset, 0.05, 1.0);
    
    
    // Toxicity Penalties
    if (GetActivatorCVar("drpg_menuhelp") && !HideInfo)
    {
        SetFont("SMALLFONT");
        if (Player.Toxicity >= 25)
        {
            HudMessage("- No Regeneration");
            EndHudMessage(HUDMSG_PLAIN, 0, "Brick", X + 0.1, Y + 32, 0.05);
        }
        if (Player.Toxicity >= 50)
        {
            HudMessage("- Energy Loss");
            EndHudMessage(HUDMSG_PLAIN, 0, "Brick", X + 0.1, Y + 40, 0.05);
        }
        if (Player.Toxicity >= 75)
        {
            HudMessage("- Reduced Movement Speed");
            EndHudMessage(HUDMSG_PLAIN, 0, "Brick", X + 0.1, Y + 48, 0.05);
        }
    }
}

void ClearToxicityMeter()
{
    Player.ToxicTimer = 0;
    Player.ToxicOffset = 0;
    Player.ToxicStage = 0;
    
    for (int i = TOXMETER_ID; i < TOXMETER_ID + 100; i++)
        ClearMessage(i);
}
