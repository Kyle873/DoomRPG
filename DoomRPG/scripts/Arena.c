#include "Defs.h"

#include "Arena.h"
#include "RPG.h"
#include "Utils.h"
#include "Outpost.h"
#include "Menu.h"

int RPGGlobal ArenaMaxWave;

bool RPGMap ArenaActive = false;
bool RPGMap ArenaTimerActive = false;
int RPGMap ArenaState = ARENA_READY;
int RPGMap ArenaPlayerNumber = -1;
int RPGMap ArenaMonstersTID = 1099;
int RPGMap ArenaSpotSpawns = 1100;
int RPGMap ArenaSectorTag = 100;
int RPGMap ArenaWave;
int RPGMap ArenaTimer;
int RPGMap ArenaKeyTimer;
int RPGMap ArenaKeyTimerType;
int RPGMap ArenaCount;
int RPGMap ArenaMod;
int RPGMap ArenaEnvironment;
int RPGMap ArenaKey;

str const ArenaMods[AMOD_MAX] =
{
	"None",
    "\CgNo Regeneration"
};

str const ArenaEvents[AEVENT_MAX] =
{
	"None",
    "\CmBlackout",
    "\CjFoggy",
    "\CiThe Floor is Lava",
    "\CuGrayscale"
};

str const ArenaBonus[ABONUS_MAX] =
{
    "\CjSelect Your Own!",
    "\CvFull EP",
    "\CfMoney Drop",
    "\CfChip Drop",
    "\CeAmmo Drop",
    "\CaHealth Drop",
    "\CdArmor Drop",
    "\CgWeapon Drop",
    "\CqPowerup Drop",
    "\CkStim Drop",
    "\CiCrate Drop",
    "\CtMod Drop",
    "\CjKey Drop"
};

str const ArenaMonsters[MAX_DEF_MONSTERS] =
{
    "ZombieMan", "ShotgunGuy", "DoomImp", "Demon", "Spectre", "ChaingunGuy",
    "HellKnight", "BaronOfHell", "Cacodemon", "LostSoul",
    "PainElemental", "Revenant", "Fatso", "Arachnotron", "ArchVile",
    "Cyberdemon", "SpiderMastermind"
};

// Arena Script
NamedScript MapSpecial void ArenaLoop()
{
    ArenaSetEnvironment(AEVENT_NONE);
    
    // Arena Loop
    while (true)
    {
        // Stop the script if the Arena is stopped or the Arena activator dies
        if (!ArenaActive || ClassifyActor(Players(ArenaPlayerNumber).TID) & ACTOR_DEAD)
        {
            ArenaStop();
            return;
        }
        
        // Arena HUD
        ArenaDrawHUD();
        
        // Arena Status Handling
        if (ArenaState == ARENA_INTERMISSION)
        {
            int BonusRandomizer = Random(-10, ABONUS_MAX - 1);

            ArenaMod = -1;
            ArenaGetBonus(BonusRandomizer);
            ArenaSetEnvironment(AEVENT_NONE);
            ArenaState = ARENA_WAITING;
        }
        else if (ArenaState == ARENA_WAITING)
        {
            int Buttons = GetPlayerInput(ArenaPlayerNumber, INPUT_BUTTONS);
            int OldButtons = GetPlayerInput(ArenaPlayerNumber, INPUT_OLDBUTTONS);
            bool Ready = true;
            
            SetHudSize(0, 0, false);
            SetFont("BIGFONT");
            
            if (ArenaPlayerNumber == PlayerNumber())
            {
                if (!Player.InMenu && !Player.InShop && !Player.OutpostMenu)
                {
                    HudMessage("Press \Cd%jS\C- to start the next wave\nPress \Cd%jS\C- to exit the Arena", "+use" , "+speed");
                    EndHudMessage(HUDMSG_PLAIN, 0, "White", 1.5, 0.75, 0.05);
                }
                
                if (Buttons & BT_USE && (!Player.InMenu && !Player.InShop && !Player.OutpostMenu && !Player.CrateOpen) && !Player.MenuBlock)
                {
                    // Check to see if others are still in the menu
                    for (int i = 0; i < MAX_PLAYERS; i++)
                        if (Players(i).InMenu || Players(i).InShop)
                            Ready = false;
                    
                    if (Ready)
                    {
                        ArenaKeyTimer++;
                        ArenaKeyTimerType = AKTIMER_CONTINUE;
                        if (ArenaKeyTimer > ARENA_HOLDTIME)
                        {
                            // Multiplayer Countdown
                            if (InMultiplayer)
                            {
                                SetFont("BIGFONT");
                                for (int i = 3; i > 0; i--)
                                {
                                    HudMessage("%d", i);
                                    EndHudMessageBold(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 0.25, 0.75);
                                    Delay(35);
                                }
                            }
                            
                            ArenaWave++;
                            ArenaState = ARENA_READY;
                        }
                    }
                    else
                    {
                        PrintError("Someone is currently in a menu");
                        ActivatorSound("menu/error", 127);
                    }
                }
                else if (Buttons & BT_SPEED && (!Player.InMenu && !Player.InShop && !Player.OutpostMenu && !Player.CrateOpen))
                {
                    ArenaKeyTimer++;
                    ArenaKeyTimerType = AKTIMER_STOP;
                    if (ArenaKeyTimer > ARENA_HOLDTIME)
                    {
                        ArenaStop();
                        return;
                    }
                }
                else
                    ArenaKeyTimer = 0;
                
                // Reset menu block
                if (Buttons == 0 && OldButtons == 0)
                    Player.MenuBlock = false;
            }
        }
        else if (ArenaState == ARENA_READY)
        {
            // Clean corpses every couple of waves
            if (ArenaWave > 1 && (ArenaWave % 5) == 0)
                Thing_Remove(ArenaMonstersTID);
            
            // Change up the music
            if (ArenaWave > 1 && (ArenaWave % 10) == 0)
                SetOutpostMusic(OUTPOST_MUSIC_COMBAT);
            
            // Update the global Max Wave
            if (ArenaWave >= ArenaMaxWave)
                ArenaMaxWave = ArenaWave;
            
            ArenaMod = Random(-10, AMOD_MAX - 1);
            ArenaSetEnvironment(AEVENT_RANDOM);
            ArenaSpawnMobs();
            ArenaState = ARENA_ACTIVE;
        }
        else if (ArenaState == ARENA_ACTIVE)
        {
            ArenaCheckMod();
            ArenaCount = ThingCount(0, ArenaMonstersTID);
            if (ArenaCount <= 0)
                ArenaState = ARENA_INTERMISSION;
            if (ArenaTimerActive && ArenaTimer > 0)
                ArenaTimer--;
        }
        
        Delay(1);
    }
}

// Stop the Arena session
NamedScript MapSpecial void ArenaStop()
{
    if (ArenaWave > 1)
        ArenaState = ARENA_WAITING;
    else
        ArenaState = ARENA_READY;
    
    ArenaActive = false;
    
    if (ArenaWave >= ArenaMaxWave)
        ArenaMaxWave = ArenaWave;
    
    ArenaPlayerNumber = -1;
    ArenaCount = 0;
    ArenaMod = -1;
    ArenaSetEnvironment(AEVENT_NONE);
    
    ResetOutpostMusic(false);
    
    Ceiling_RaiseByValue(ArenaSectorTag - 1, 64, 128);
    Thing_Remove(ArenaMonstersTID);
}

// Arena Test Script
NamedScript MapSpecial void SetArena(int Wave, int Environment, int Bonus)
{
    if (Wave > 0)
        ArenaWave = Wave;
    
    if (Environment >= 0)
        ArenaSetEnvironment(Environment);
    
    if (Bonus >= 0)
        ArenaGetBonus(Bonus);
}

NamedScript MapSpecial void ArenaChooseBonus()
{
    int BonusChoice = 1;
    bool CanChooseKey = false;
    
    // There's a 1/4 chance you can use Drop Key
    if (Random(1, 4) == 1) CanChooseKey = true;
    
    Player.OutpostMenu = OMENU_BONUSSELECTOR;
    
    while (true)
    {
        fixed X = 48.1;
        fixed Y = 50.0;
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
        
        SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
        
        // Prevent the menus from being opened
        Player.InMenu = false;
        Player.InShop = false;
        
        // Set the HUD Size
        SetHudSize(GetActivatorCVar("drpg_menu_width"), GetActivatorCVar("drpg_menu_height"), true);
        
        // Title
        SetFont("BIGFONT");
        HudMessage("Choose a Bonus");
        EndHudMessage(HUDMSG_PLAIN, 0, "Green", 24.1, 24.0, 0.05);
        
        // Input
        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD)
        {
            ActivatorSound("menu/move", 127);
            BonusChoice--;
            if (BonusChoice < 1) BonusChoice = ABONUS_MAX - (CanChooseKey ? 1 : 2);
            if (BonusChoice == ABONUS_MODDROP && CompatMode != COMPAT_DRLA) BonusChoice--;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK)
        {
            ActivatorSound("menu/move", 127);
            BonusChoice++;
            if (BonusChoice == ABONUS_MODDROP && CompatMode != COMPAT_DRLA) BonusChoice++;
            if (BonusChoice > ABONUS_MAX - (CanChooseKey ? 1 : 2)) BonusChoice = 1;
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            ArenaGetBonus(BonusChoice);
            Player.OutpostMenu = 0;
            Player.MenuBlock = true;
            return;
        }
            
        // Drawing
        for (int i = 1; i < ABONUS_MAX; i++)
        {
            // Skip Mod Drop if DRLA extension isn't enabled
            if (i == ABONUS_MODDROP && CompatMode != COMPAT_DRLA) continue;
            
            // Skip Key Drop if the randomizer hates you
            if (i == ABONUS_KEYDROP && !CanChooseKey) continue;
            
            // Cursor
            if (i == BonusChoice)
            {
                HudMessage("-->");
                EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, X - 24.0, Y, 0.05);
            }
            
            // Bonus String
            HudMessage("%S", ArenaBonus[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
            
            // Move down Y
            Y += 16.0;
        }
        
        Delay(1);
    }
}

void ArenaGetBonus(int Bonus)
{
    int SpawnAmount = ArenaWave * 5;
    str SpawnItem;
    
    // Cap the spawn amount so the game doesn't lag and crash into oblivion
    if (SpawnAmount > 1000)
        SpawnAmount = 1000;
    
    switch (Bonus)
    {
    case ABONUS_SELECT: // Choose Your Own!
        ActivatorSound("arena/pickbonus", 127);
        ArenaChooseBonus();
        break;
    case ABONUS_FULLEP: // Full EP
        if (InMultiplayer)
            for (int i = 0; i < MAX_PLAYERS; i++)
                Players(i).EP = Players(i).EPMax;
        else
        {
            if (Player.EP >= Player.EPMax)
            {
                ArenaGetBonus(Random(0, ABONUS_MAX - 1));
                return;
            }
            else
                Player.EP = Player.EPMax;
        }
        break;
    case ABONUS_MONEYDROP: // Money Drop
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (!PlayerInGame(i)) continue;
            
            GiveActorInventory(Players(i).TID, "DRPGCredits", SpawnAmount);
        }
        break;
    case ABONUS_CHIPDROP: // Chip Drop
        DropArenaItem("DRPGChipDropper");
        break;
    case ABONUS_AMMODROP: // Ammo Drop
        DropArenaItem("DRPGBackpackRandomizer");
        break;
    case ABONUS_HEALTHDROP: // Health Drop
        if (Random(1, 4) == 1)
            SpawnItem = "Megasphere";
        else if (Random(1, 2) == 1)
            SpawnItem = "Soulsphere";
        else
            SpawnItem = "DRPGHealthDropper";
        DropArenaItem(SpawnItem);
        break;
    case ABONUS_ARMORDROP: // Armor Drop
        if (Random(1, 2) == 1)
            SpawnItem = "DRPGBlueArmorRandomizer";
        else
            SpawnItem = "DRPGGreenArmorRandomizer";
        DropArenaItem(SpawnItem);
        break;
    case ABONUS_WEAPONDROP: // Weapon Drop
        DropArenaItem("DRPGWeaponDropper");
        break;
    case ABONUS_POWERUPDROP: // Powerup Drop
        DropArenaItem("DRPGPowerupDropper");
        break;
    case ABONUS_STIMDROP: // Stim Drop
        if (Random(1, 4) == 1)
            DropArenaItem("DRPGStimPackageStat");
        else if (Random(1, 8) == 1)
            DropArenaItem("DRPGStimPackagePowerup");
        DropArenaItem("DRPGStimDropper");
        break;
    case ABONUS_CRATEDROP: // Crate Drop
        DropArenaItem("DRPGCrate");
        break;
    case ABONUS_MODDROP: // Mod Drop (DRLA Only)
        if (CompatMode == COMPAT_DRLA)
            DropArenaItem("RLModPackSpawner");
        else
        {
            ArenaGetBonus(Random(0, ABONUS_MAX - 1));
            return;
        }
        break;
    case ABONUS_KEYDROP: // Key Drop
        if (ArenaKey == 0) SpawnItem = "DRPGRedCard";
        if (ArenaKey == 1) SpawnItem = "DRPGYellowCard";
        if (ArenaKey == 2) SpawnItem = "DRPGBlueCard";
        if (ArenaKey == 3) SpawnItem = "DRPGRedSkull";
        if (ArenaKey == 4) SpawnItem = "DRPGYellowSkull";
        if (ArenaKey == 5) SpawnItem = "DRPGBlueSkull";
        if (ArenaKey == 6)
        { 
            ArenaGetBonus(Random(0, ABONUS_MAX - 1));
            return;
        }
        DropArenaItem(SpawnItem);
        if (ArenaKey < 6) ArenaKey++;
        ActivatorSound("arena/keydrop", 127);
        break;
    }
    
    // Bonus Message
    if (Bonus > 0)
    {
        SetHudSize(0, 0, false);
        SetFont("BIGFONT");
        HudMessage("%S", ArenaBonus[Bonus]);
        EndHudMessageBold(HUDMSG_FADEOUT, MENU_ID, "White", 0.5, 0.5, 2.0, 1.0);
        if (Bonus != 10)
            ActivatorSound("arena/drop", 127);
    }
}

void DropArenaItem(str Item)
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (!PlayerInGame(i)) continue;
        
        int TID = UniqueTID();
        bool Success = false;
        fixed X = GetActorX(Players(i).TID);
        fixed Y = GetActorY(Players(i).TID);
        fixed Z = GetActorCeilingZ(Players(i).TID) - 32.0;
        fixed XSpeed = GetCVarFixed("drpg_monster_dropdist");
        fixed YSpeed = GetCVarFixed("drpg_monster_dropdist");
        fixed ZSpeed = 8.0;
        
        SpawnForced("DRPGTurretTeleport", X, Y, Z, 0, 0);
        Success = SpawnForced(Item, X, Y, Z, TID, 0);
        
        if (Success)
        {
            // Set Velocity
            SetActorVelocity(TID, RandomFixed(-XSpeed, XSpeed), RandomFixed(-YSpeed, YSpeed), ZSpeed, false, false);
            
            // Array has grown too big, resize it
            if (Players(i).DropTID.Position == Players(i).DropTID.Size)
                ArrayResize(&Players(i).DropTID);
            
            // Add item's TID to drop array
            ((int *)Players(i).DropTID.Data)[Players(i).DropTID.Position++] = TID;
        }
    }
}

void ArenaDrawHUD()
{
    fixed X = GetActivatorCVar("drpg_event_x") + 0.1;
    fixed Y = GetActivatorCVar("drpg_event_y") + 0.1;
    
    // Don't draw the HUD if you're in a menu
    if (Player.InMenu || Player.InShop || Player.OutpostMenu > 0) return;
    
    SetHudSize(GetActivatorCVar("drpg_hud_width"), GetActivatorCVar("drpg_hud_height"), false);
    SetFont("SMALLFONT");
    
    // Wave
    HudMessage("Wave: %d", ArenaWave);
    EndHudMessageBold(HUDMSG_PLAIN, 0, "Green", X, Y, 0.05);
    Y += 8.0;

    // Monster Count
    if (ArenaCount > 0)
    {
        HudMessage("Monsters: %d", ArenaCount);
        EndHudMessageBold(HUDMSG_PLAIN, 0, "Green", X, Y, 0.05);
        Y += 8.0;
    }
    
    // Timer
    if (ArenaTimerActive && ArenaTimer > 0)
    {
        HudMessage("Time: %d", ArenaTimer / 35 + 1);
        EndHudMessageBold(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
        Y += 8.0;
    }
    
    // Mod
    if (ArenaMod > 0)
    {
        HudMessage("%S", ArenaMods[ArenaMod]);
        EndHudMessageBold(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
        Y += 8.0;
    }

    // Environment
    if (ArenaEnvironment > 0)
    {
        HudMessage("%S", ArenaEvents[ArenaEnvironment]);
        EndHudMessageBold(HUDMSG_PLAIN, 0, "White", X, Y, 0.05);
        Y += 8.0;
    }
    
    // Cancel Timer
    if (ArenaKeyTimer > 0 && ArenaKeyTimer <= ARENA_HOLDTIME)
    {
        int Percent = CalcPercent(ArenaKeyTimer, ARENA_HOLDTIME);
        str Text;
        
        switch (ArenaKeyTimerType)
        {
        case AKTIMER_STOP:      Text = "Stopping Arena";    break;
        case AKTIMER_CONTINUE:  Text = "\CaNext Wave";      break;
        }
        
        DrawProgressBar(Text, Percent);
    }
}

void ArenaCheckMod()
{
    switch (ArenaMod)
    {
    case AMOD_NOREGEN:
        Player.HPRate = 0;
        Player.EPRate = 0;
        break;
    }
}

void ArenaSpawnMobs()
{
    int MonsterID = 1;
    int Spawned;
    
    for (int i = ArenaSpotSpawns; i <= ArenaSpotSpawns + 30; i++)
    {
        // Check to make sure there wasn't a chance that nothing at all spawned
        if (i == ArenaSpotSpawns + 30)
        {
            if (Spawned == 0)
                i = ArenaSpotSpawns;
            else
                break;
        }
        
        // Get a random monster from the list
        MonsterID = Random(-5, ArenaWave / 5);
        
        if (MonsterID > 14)
            MonsterID = 14;
        
        if (MonsterID < 0)
            MonsterID = 0;
        
        // Spawn the monster
        if (!Random(0, 2) && SpawnSpotFacing(ArenaMonsters[MonsterID], i, ArenaMonstersTID))
        {
            SpawnSpotForced("TeleportFog", i, 0, 0);
            Spawned++;
        }
    }
    
    bool Boss = (ArenaWave >= 75) && !Random(0, 7);
    
    if (Boss)
    {
        for (int i = 0; i < 32; i++)
        {
            int SpotTID = ArenaSpotSpawns + Random(0, 30);
            
            if (SpawnSpotFacing(ArenaMonsters[Random(15, 16)], SpotTID, ArenaMonstersTID))
            {
                SpawnSpot("TeleportFog", SpotTID, 0, 0);
                break;
            }
        }
    }
}

void ArenaSetEnvironment(int ID)
{
    int R, G, B;
    
    if (ID == AEVENT_RANDOM)
    {
        int EnvironmentRandomizer = Random(-10, AEVENT_MAX);
        if (EnvironmentRandomizer > 0)
            ID = EnvironmentRandomizer;
    }

    switch (ID)
    {
    case AEVENT_NONE:
        Light_Fade(ArenaSectorTag, 192, 35);
        Light_Fade(ArenaSectorTag + 1, 192, 35);
        Light_Fade(ArenaSectorTag + 2, 192, 35);
        Sector_SetFade(ArenaSectorTag, 0, 0, 0);
        Sector_SetFade(ArenaSectorTag + 1, 0, 0, 0);
        Sector_SetFade(ArenaSectorTag + 2, 0, 0, 0);
        ChangeFloor(ArenaSectorTag, "CEIL5_1");
        ChangeFloor(ArenaSectorTag + 1, "CEIL5_2");
        ChangeFloor(ArenaSectorTag + 2, "FLAT3");
        Sector_SetDamage(ArenaSectorTag, 0, 0);
        Sector_SetDamage(ArenaSectorTag + 1, 0, 0);
        Sector_SetDamage(ArenaSectorTag + 2, 0, 0);
        Sector_SetColor(ArenaSectorTag, 255, 255, 255);
        Sector_SetColor(ArenaSectorTag + 1, 255, 255, 255);
        Sector_SetColor(ArenaSectorTag + 2, 255, 255, 255);
        break;
    case AEVENT_BLACKOUT:
        Light_Fade(ArenaSectorTag, 0, 35);
        Light_Fade(ArenaSectorTag + 1, 0, 35);
        Light_Fade(ArenaSectorTag + 2, 0, 35);
        break;
    case AEVENT_FOGGY:
        R = Random(0, 255);
        G = Random(0, 255);
        B = Random(0, 255);
        Light_Fade(ArenaSectorTag, 128, 35);
        Light_Fade(ArenaSectorTag + 1, 128, 35);
        Light_Fade(ArenaSectorTag + 2, 128, 35);
        Sector_SetFade(ArenaSectorTag, R, G, B);
        Sector_SetFade(ArenaSectorTag + 1, R, G, B);
        Sector_SetFade(ArenaSectorTag + 2, R, G, B);
        break;
    case AEVENT_LAVA:
        ChangeFloor(ArenaSectorTag, "LAVA1");
        ChangeFloor(ArenaSectorTag + 1, "LAVA1");
        ChangeFloor(ArenaSectorTag + 2, "LAVA1");
        Sector_SetDamage(ArenaSectorTag, 1 + GameSkill(), MOD_SLIME);
        Sector_SetDamage(ArenaSectorTag + 1, 1 + GameSkill(), MOD_SLIME);
        Sector_SetDamage(ArenaSectorTag + 2, 1 + GameSkill(), MOD_SLIME);
        break;
    case AEVENT_GRAYSCALE:
        Sector_SetColor(ArenaSectorTag, 255, 255, 255, 255);
        Sector_SetColor(ArenaSectorTag + 1, 255, 255, 255, 255);
        Sector_SetColor(ArenaSectorTag + 2, 255, 255, 255, 255);
        break;
    }
    
    ArenaEnvironment = ID;
}
