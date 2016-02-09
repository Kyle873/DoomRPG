#include "Defs.h"

#include "Arena.h"
#include "Augs.h"
#include "ItemData.h"
#include "Map.h"
#include "Menu.h"
#include "Minigame.h"
#include "Mission.h"
#include "Outpost.h"
#include "RPG.h"
#include "Shield.h"
#include "Shop.h"
#include "Skills.h"
#include "Stats.h"
#include "Stims.h"
#include "Utils.h"

// Globals
int OutpostNotoriety;

// Spawn Spots and TIDs
int RPGMap ShopSpecialTID = 1001;
int RPGMap SecretTeleportTID = 1010;
int RPGMap MarineSpotTID = 1300;
int RPGMap NotorietySpotTID = 1301;
int RPGMap MarineTID = 1400;
int RPGMap MarineMaxTID = 1419;
int RPGMap MarineBossTID = 1421;
int RPGMap TurretTID = 1450;
int RPGMap BossSpotTID = 1475;
int RPGMap ForcefieldID = 1500;
int RPGMap ForcefieldGeneratorID = 1501;
int RPGMap GeneratorTID = 1510;
int RPGMap EntrySectorID = 200;
int RPGMap HallTeleportSpotID = 1601;
int RPGMap CameraTID = 1700;
int RPGMap RiftSpotTID = 1800;
int RPGMap CreditsBlockerID = 1900;

// Timers
int RPGMap ForcefieldTimer = 0;

// Choices
int RPGMap LevelChoice = 0;
int RPGMap SkillChoice = 0;
int RPGMap WaveChoice = 1;

// Flags
bool RPGMap MarinesHostile = false;
bool RPGMap PowerOut = false;
bool RPGMap BossDead = false;
bool RPGMap Invasion = false;

NamedScript MapSpecial void EnterOutpost()
{
    ForcefieldTimer = 35 * 60 * GameSkill(); // 1 Minute per skill level
    
    SetHudSize(320, 240, true);
    
    // Assign the current level to the level choice
    LevelChoice = FindLevelInfoIndex(TransporterLevel->LumpName);
    
    // Assign the current skill level to the skill choice
    SkillChoice = GameSkill() - 1;
    
    // Set the current wave to the max wave
    ArenaWave = ArenaMaxWave;
    
    // Spawn the Shop Special item
    SpawnShopSpecialItem();
    
    // Make the Portable Turret not attack Outpost Turrets
    SetActorProperty(TurretTID, APROP_Friendly, true);
    
    // Boss Placement
    PlaceBoss();
    
    // Get new Missions
    PopulateMissions();
    
    // Title map handling
    if (InTitle)
    {
        ChangeCamera(CameraTID, true, false);
        Thing_Activate(CameraTID);
        Delay(35 * Random(3, 5));
        PissOffMarines(false);
        
        ActivatorSound("misc/skillchange", 127);
        if (CompatMode == COMPAT_DRLA)
            AmbientSound("nightmarecyberdemon/sight", 127);
        
        while (InTitle)
        {
            PrintSpritePulse("M_DOOM", 1, 160.0 + 8.0, 80.0 - 8.0, 0.75, 64.0, 0.25);
            Delay(1);
        }
    }
}

NamedScript MapSpecial void RegenArea(int ID)
{
    // If you're dead, terminate
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    // Health
    if (ID == OREGEN_HEALTH)
    {
        int HealthCharges;
        bool DoMessage = false;
        
        if (CheckInventory("DRPGCredits") > 0 && Player.ActualHealth < Player.HealthMax)
        {
            HealthCharges = Player.HealthMax - Player.ActualHealth;
            if (HealthCharges > CheckInventory("DRPGCredits"))
                HealthCharges = CheckInventory("DRPGCredits");
            
            AddHealthDirect(HealthCharges, 100);
            TakeInventory("DRPGCredits", HealthCharges);
            DoMessage = true;
        }
        
        if (CheckInventory("DRPGCredits") >= 5 && Player.Toxicity > 0)
        {
            HealthCharges = Player.Toxicity;
            if (HealthCharges > CheckInventory("DRPGCredits") / 5)
                HealthCharges = CheckInventory("DRPGCredits") / 5;
            
            ClearToxicityMeter();
            Player.Toxicity -= HealthCharges;
            TakeInventory("DRPGCredits", HealthCharges * 5);
            DoMessage = true;
        }
        
        if (CheckInventory("DRPGCredits") >= 50 && HaveStatusEffect())
        {
            ClearStatusEffects();
            TakeInventory("DRPGCredits", 50);
            DoMessage = true;
        }
        
        if (DoMessage)
        {
            SetFont("BIGFONT");
            HudMessage("Health restored");
            EndHudMessage(HUDMSG_FADEOUT, 0, "Brick", 0.5, 0.33, 2.0, 0.5);
            FadeRange(255, 0, 0, 0.5, 255, 0, 0, 0.0, 1.0);
            ActivatorSound("regen/health", 127);
        }
    }
    
    // Armor
    if (ID == OREGEN_ARMOR)
    {
        if (CheckInventory("Armor") >= GetArmorInfo(ARMORINFO_SAVEAMOUNT))
            return;
        
        int ArmorPercent = CheckInventory("Armor") * 100 / GetArmorInfo(ARMORINFO_SAVEAMOUNT);
        int ArmorFee = (100 - ArmorPercent) / 5 * 5;
        if (ArmorFee < 5)
            ArmorFee = 5;
        
        if (CheckInventory("DRPGCredits") < ArmorFee)
        {
            SetFont("BIGFONT");
            HudMessage("You need %d credits to repair armor", ArmorFee);
            EndHudMessage(HUDMSG_FADEOUT, 1, "Red", 0.5, 0.33, 2.0, 0.5);
            ActivatorSound("menu/error", 127);
            return;
        }
        
        GiveInventory(GetArmorInfoString(ARMORINFO_CLASSNAME), 1);
        TakeInventory("DRPGCredits", ArmorFee);
        
        SetFont("BIGFONT");
        HudMessage("Armor repaired");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.33, 2.0, 0.5);
        FadeRange(0, 255, 0, 0.5, 0, 255, 0, 0.0, 1.0);
        ActivatorSound("regen/armor", 127);
    }
    
    // EP (and Shields)
    if (ID == OREGEN_EP)
    {
        // Holding Run will restore your Shield capacity
        if (GetPlayerInput(PlayerNumber(), INPUT_BUTTONS) & BT_SPEED && CheckShieldValid())
        {
            if (CheckInventory("DRPGCredits") < 1 || Player.Shield.Charge >= Player.Shield.Capacity) return;
            
            int ShieldCharges = (Player.Shield.Capacity - Player.Shield.Charge) / 5;
            if (Player.Shield.Charge % 5 > 0)
                ShieldCharges++;
            if (CheckInventory("DRPGCredits") < ShieldCharges)
                ShieldCharges = CheckInventory("DRPGCredits");
            
            int ShieldGive = ShieldCharges * 5;
            
            if (Player.Shield.Charge + ShieldGive > Player.Shield.Capacity)
                ShieldGive = Player.Shield.Capacity - Player.Shield.Charge;
            
            Player.Shield.Charge += ShieldGive;
            
            TakeInventory("DRPGCredits", ShieldCharges);
            
            SetFont("BIGFONT");
            HudMessage("Shield restored");
            EndHudMessage(HUDMSG_FADEOUT, 0, "Cyan", 0.5, 0.33, 2.0, 0.5);
            FadeRange(0, 255, 255, 0.5, 0, 255, 255, 0.0, 1.0);
            ActivatorSound("regen/shield", 127);
        }
        else
        {
            if (CheckInventory("DRPGCredits") < 1 || Player.EP >= Player.EPMax) return;
            
            int EPCharges = (Player.EPMax - Player.EP) / 5;
            if (Player.EP % 5 > 0)
                EPCharges++;
            if (CheckInventory("DRPGCredits") < EPCharges)
                EPCharges = CheckInventory("DRPGCredits");
            
            int EPGive = EPCharges * 5;
            
            if (Player.EP + EPGive > Player.EPMax)
                EPGive = Player.EPMax - Player.EP;
            
            Player.EP += EPGive;
            
            TakeInventory("DRPGCredits", EPCharges);
            
            SetFont("BIGFONT");
            HudMessage("EP restored");
            EndHudMessage(HUDMSG_FADEOUT, 0, "LightBlue", 0.5, 0.33, 2.0, 0.5);
            FadeRange(0, 255, 255, 0.5, 0, 255, 255, 0.0, 1.0);
            ActivatorSound("regen/ep", 127);
        }
    }
    
    // Augmentation Battery
    if (ID == OREGEN_AUG)
    {
        if (CheckInventory("DRPGCredits") < 10 || Player.Augs.Battery >= Player.Augs.BatteryMax) return;
        
        int BatteryCharges = Player.Augs.BatteryMax - Player.Augs.Battery;
        if (CheckInventory("DRPGCredits") / 10 < BatteryCharges)
            BatteryCharges = CheckInventory("DRPGCredits") / 10;
        
        AddBattery(BatteryCharges);
        TakeInventory("DRPGCredits", BatteryCharges * 10);
        
        if (Player.Augs.BatteryMax - Player.Augs.Battery < 1 && Player.Augs.BatteryMax - Player.Augs.Battery > 0)
            AddBattery(1); // One more to get rid of the fraction-of-a-percent
        
        SetFont("BIGFONT");
        HudMessage("Augmentation Battery Recharged");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Yellow", 0.5, 0.33, 2.0, 0.5);
        FadeRange(255, 255, 0, 0.5, 255, 255, 0, 0.0, 1.0);
        ActivatorSound("regen/battery", 127);
    }
}

NamedScript MapSpecial void LevelTransport()
{
    // if you're already in a menu, terminate
    if (Player.InMenu || Player.InShop || Player.OutpostMenu == OMENU_LEVELTRANSPORT) return;
    
    // If the Marines are hostile and the bosses aren't dead, terminate
    if (MarinesHostile && ThingCount(0, MarineBossTID) > 0) return;
    
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    Player.OutpostMenu = OMENU_LEVELTRANSPORT;
    
    SetHudSize(GetActivatorCVar("drpg_menu_width"), GetActivatorCVar("drpg_menu_height"), true);
    
    while (true)
    {
        // Stop Underflow
        if (LevelChoice < 0)
            LevelChoice = 0;
        
        // And Overflow
        if (LevelChoice >= KnownLevels.Position)
            LevelChoice = KnownLevels.Position - 1;
        
        LevelInfo *TeleDest = &((LevelInfo *)KnownLevels.Data)[LevelChoice];
        
        // Text
        SetFont("BIGFONT");
        HudMessage("Level Transporter");
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID, "White", 32.1, 32.1, 0.05, 0.5);
        
        str TitleColor = "Gold";
        if (TeleDest->NeedsRealInfo || !(TeleDest->Completed))
            TitleColor = "Red";
        else if (TeleDest->AllBonus)
            TitleColor = "Green";
        
        str MapType = "Standard Map";
        if (TeleDest->SecretMap)
            MapType = "Secret Map";
        if (TeleDest->UACBase)
            MapType = "UAC Base";
        if (TeleDest->UACArena)
            MapType = "UAC Arena";
        HudMessage("%S", TeleDest->NiceName);
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 1, TitleColor, 32.1, 64.1, 0.05, 0.5);
        SetFont("SMALLFONT");
        if (TeleDest->LevelNum > 0)
        {
            HudMessage("%S, level %d - %S", TeleDest->LumpName, TeleDest->LevelNum, MapType);
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 2, "Orange", 32.1, 80.1, 0.05, 0.5);
        }
        else
        {
            HudMessage("%S - %S", TeleDest->LumpName, MapType);
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 2, "DarkGreen", 32.1, 80.1, 0.05, 0.5);
        }
        
        if (!TeleDest->NeedsRealInfo && !TeleDest->UACBase && !TeleDest->UACArena)
        {
            str KillColor = "Brick";
            if (TeleDest->KillBonus && Timer() & 16)
                KillColor = "Green";
            str ItemColor = "LightBlue";
            if (TeleDest->ItemsBonus && Timer() & 16)
                ItemColor = "Green";
            str SecretColor = "Yellow";
            if (TeleDest->SecretsBonus && Timer() & 16)
                SecretColor = "Green";
            str ParColor = "Gold";
            if (TeleDest->ParBonus && TeleDest->Par > 0 && Timer() & 16)
                ParColor = "Green";
            
            if (TeleDest->MaxTotalMonsters > 0)
            {
                HudMessage("Kills: %d / %d (%d%%)", TeleDest->MaxMonstersKilled, TeleDest->MaxTotalMonsters, TeleDest->MaxMonsterPercentage);
                EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 3, KillColor, 32.1, 96.1, 0.05, 0.5);
            }
            if (TeleDest->MaxTotalItems > 0)
            {
                HudMessage("Items: %d / %d (%d%%)", TeleDest->MaxItemsFound, TeleDest->MaxTotalItems, TeleDest->MaxItemPercentage);
                EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 4, ItemColor, 32.1, 104.1, 0.05, 0.5);
            }
            if (TeleDest->MaxTotalSecrets > 0)
            {
                HudMessage("Secrets: %d / %d (%d%%)", TeleDest->MaxSecretsFound, TeleDest->MaxTotalSecrets, TeleDest->MaxSecretPercentage);
                EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 5, SecretColor, 32.1, 112.1, 0.05, 0.5);
            }
            
            if (TeleDest->Par > 0)
            {
                HudMessage("Par Time: %S", FormatTime(TeleDest->Par * 35));
                EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 6, ParColor, 32.1, 128.1, 0.05, 0.5);
            }
            if (TeleDest->ShortestTime < 0x7FFFFFFF)
            {
                HudMessage("Completion Time: %S", FormatTime(TeleDest->ShortestTime * 35));
                EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 7, ParColor, 32.1, 136.1, 0.05, 0.5);
            }
            else
            {
                HudMessage("Completion Time: \C[Red]N/A");
                EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 7, ParColor, 32.1, 136.1, 0.05, 0.5);
            }
            
            str AreaText = "No anomalies detected";
            switch (TeleDest->Event)
            {
            case MAPEVENT_NONE:
            default:
                break;
            case MAPEVENT_MEGABOSS:
                AreaText = "\C[Grey]Detected: Unknown Hostile Lifeform (Megaboss)\n\CgUse extreme caution when engaging target.\C-\nA quarantine has been issued for this area.";
                break;
            case MAPEVENT_TOXICHAZARD:
                AreaText = StrParam("\C[DarkGreen]Detected: High Radiation Levels (Environmental Hazard)\C-\n\CdHazard level: %d\C-\nPlease wear protective clothing when traversing this location.", TeleDest->HazardLevel);
                break;
            case MAPEVENT_NUCLEARBOMB:
                AreaText = "\C[Orange]Detected: Area-Destruction Device (Thermonuclear Bomb)\C-\nDo not stay within the detonation area.";
                break;
            case MAPEVENT_LOWPOWER:
                AreaText = "\C[Red]Detected: Electrical Grid Malfunction (Low Power)\C-\nPlease contact the maintenance team for replacement power cell.";
                break;
            case MAPEVENT_ALLAURAS:
                AreaText = "\C[Yellow]Detected: Abnormal Energy Signature (All Auras)\C-\nThreat levels have increased within this area.";
                break;
            case MAPEVENT_ONEMONSTER:
                AreaText = StrParam("\C[LightBlue]Detected: Anomalous Lifeform Distribution (One-Monster)\n\C[Red]Last seen: %S", TeleDest->SelectedMonster->Name);
                break;
            case MAPEVENT_HELLUNLEASHED:
                AreaText = "\C[Brick]Detected: Active Battle Front (Hell Unleashed)\n\CgTake preparatory measures before engaging the enemy.";
                break;
            case MAPEVENT_HARMONIZEDAURAS:
                AreaText = "\C[Green]Detected: Stable Demonic Energy Signature (Harmonized Destruction)\C-\nThreat levels have increased within this area.";
                break;
            case MAPEVENT_TELEPORTCRACKS:
                AreaText = "\C[Green]Detected: Spatial Instability (Cracks in the Veil)\C-\nTraverse the area with caution.";
                break;
            case MAPEVENT_DOOMSDAY:
                AreaText = "\C[Brick]Detected: Hell Zone (Doomsday)\n\CgUse EXTREME caution.";
                break;
            case MAPEVENT_ACIDRAIN:
                AreaText = "\C[DarkGreen]Weather Condition: Acid Rain (Vicious Downpour)\C-\nPlease wear protective clothing when traversing outdoor areas.";
                break;
            case MAPEVENT_DARKZONE:
                AreaText = "\C[Purple]Weather Condition: Dense Mist (The Dark Zone)\n\CaAvoid prolonged exposure if possible.";
                break;
            case MAPEVENT_DRLA_FEEDINGFRENZY:
                AreaText = StrParam("\C[LightBlue]Det%c%ccted: Anom%clous Lif%c%c%c%c\n\n\n       T     H  E       Y        F     %c    E  D\n\n\n          Y     %c        U      R         F     L     3      %c         H", 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94));
                break;
            case MAPEVENT_DRLA_OVERMIND:
                AreaText = StrParam("\C[Red]Er%cor: Unable to read addr%c%c%c%c\n\n\n\CgI SEE THE DARKNESS WITHIN YOUR SOUL.", 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94), 33 + Random(0, 94));
                break;
            case MAPEVENT_BONUS_RAINBOWS:
                AreaText = "\C[Grey]Detected: Internal Software Failure (\C[Red]R\C[Orange]A\C[Yellow]I\C[Green]N\C[Cyan]B\C[Blue]O\C[Purple]W\C[Brick]S\C[Grey])\n    \C[Brick]Kupo?";
                break;
            case MAPEVENT_SKILL_HELL:
                AreaText = "\C[Red]Detected: Internal Mechanism Corruption (Hell!)";
                break;
            case MAPEVENT_SKILL_ARMAGEDDON:
                AreaText = "\C[Grey]Detected: Internal Mechanism Corruption (Armageddon!)";
                break;
            case MAPEVENT_SPECIAL_SINSTORM:
                AreaText = "\C[Red]The source of the demon invasion is located here (Sinstorm)";
                break;
            }
            
            int MonsterAvgLevel = 0;
            int MonsterMinLevel = 0;
            int MonsterMaxLevel = 0;
            
            if (1)
            {
                int MonsterLevelType = GetCVar("drpg_monster_levels");
                fixed MonsterLevelWeight = GetCVarFixed("drpg_monster_level_weight");
                fixed MonsterMapWeight = GetCVarFixed("drpg_monster_map_weight");
                fixed MonsterRandomMinWeight = GetCVarFixed("drpg_monster_random_min_mult");
                fixed MonsterRandomMaxWeight = GetCVarFixed("drpg_monster_random_max_mult");
                int MonsterLevelNum = TeleDest->LevelNum;
                
                // Calculate Monster Level
                if (MonsterLevelType == 1 || MonsterLevelType == 3) // Player Level
                    MonsterAvgLevel += (int)((fixed)AveragePlayerLevel() * MonsterLevelWeight);
                if (MonsterLevelType == 2 || MonsterLevelType == 3) // Map Number
                    MonsterAvgLevel += (int)((fixed)MonsterLevelNum * MonsterMapWeight);
                
                MonsterMinLevel = MonsterAvgLevel * MonsterRandomMinWeight;
                MonsterMaxLevel = MonsterAvgLevel * MonsterRandomMaxWeight;
            }
            
            SetFont("BIGFONT");
            HudMessage("Area Status");
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 8, "Green", 32.1, 152.1, 0.05, 0.5);
            SetFont("SMALLFONT");
            HudMessage("Monster level (Approx.): %d - %d", MonsterMinLevel, MonsterMaxLevel);
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 9, "White", 32.1, 168.1, 0.05, 0.5);
            HudMessage("%S", AreaText);
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 10, "White", 32.1, 184.1, 0.05, 0.5);
        }
        else if (!TeleDest->NeedsRealInfo && TeleDest->UACBase)
        {
            str AreaText = "No anomalies detected";
            
            if (PowerOut)
                AreaText = "\C[Red]Detected: Electrical Grid Malfunction";
            else if (Invasion || MarinesHostile)
                AreaText = "\C[Brick]Detected: Security Breach";
            HudMessage("This is a secure UAC military base.");
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 3, "DarkGreen", 32.1, 96.1, 0.05, 0.5);
            SetFont("BIGFONT");
            HudMessage("Area Status");
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 8, "Green", 32.1, 152.1, 0.05, 0.5);
            SetFont("SMALLFONT");
            HudMessage("%S", AreaText);
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 9, "White", 32.1, 168.1, 0.05, 0.5);
        }
        else if (!TeleDest->NeedsRealInfo && TeleDest->UACArena)
        {
            HudMessage("This is a known UAC battle arena site.");
            EndHudMessage(HUDMSG_FADEOUT, MENU_ID + 3, "LightBlue", 32.1, 96.1, 0.05, 0.5);
        }
        
        // Input
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);

        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD && LevelChoice > 0)
        {
            ActivatorSound("menu/move", 127);
            LevelChoice--;
        }
        if (Buttons == BT_MOVELEFT && OldButtons != BT_MOVELEFT && LevelChoice > 0)
        {
            ActivatorSound("menu/move", 127);
            LevelChoice -= 10;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK && LevelChoice < KnownLevels.Position - 1)
        {
            ActivatorSound("menu/move", 127);
            LevelChoice++;
        }
        if (Buttons == BT_MOVERIGHT && OldButtons != BT_MOVERIGHT && LevelChoice < KnownLevels.Position - 1)
        {
            ActivatorSound("menu/move", 127);
            LevelChoice += 10;
        }
        if (Buttons == BT_USE && OldButtons != BT_USE && !Player.PayingOut)
        {
            if (CurrentLevel == TeleDest)
            {
                PrintError("You are already at this location.");
                ActivatorSound("menu/error", 127);
                SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
                Player.OutpostMenu = 0;
                return;
            }
            
            // Special handling for Marine Hostility and Emergency Power
            if (MarinesHostile || PowerOut)
            {
                bool IsTechnician = (CompatMode == COMPAT_DRLA && PlayerClass(PlayerNumber()) == 2);
                int TransportTimerMax = (35 * (5 + GameSkill() + PlayerCount())) / (IsTechnician ? 2 : 1);
                int TransportTimer = TransportTimerMax;
                
                // Setup power transfer
                SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
                SetPlayerProperty(0, 1, PROP_FROZEN);
                Player.OutpostMenu = 0;
                PlaySound(0, "transfer/loop", CHAN_BODY, 1.0, true, ATTN_NORM);
                
                // Power transfer loop
                while (TransportTimer > 0)
                {
                    // Calculate percentage complete and input
                    int TransportPercent = (int)Abs(100 - ((fixed)TransportTimer / (fixed)TransportTimerMax) * 100.0);
                    Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
                    
                    // Transfer is cancelled either by death or input
                    if (GetActorProperty(0, APROP_Health) <= 0 || Buttons & BT_SPEED)
                    {
                        PlaySound(0, "transfer/fail", CHAN_BODY, 1.0, false, ATTN_NORM);
                        SetPlayerProperty(0, 0, PROP_FROZEN);
                        return;
                    }
                    
                    // Draw transfer bar
                    DrawProgressBar("Transferring Power", TransportPercent);
                    
                    // Decrement timer
                    TransportTimer--;
                    Delay(1);
                }
                
                PlaySound(0, "transfer/complete", CHAN_BODY, 1.0, false, ATTN_NORM);
                Delay(10);
            }
            
            Player.OutpostMenu = 0;
            
            TransportOutFX(0);
            
            Delay(35 * 2);
            
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            SetPlayerProperty(0, 0, PROP_FROZEN);
            Transported = true;
            
            if (BossDead)
                OutpostNotoriety++;
            
            ChangeLevel(TeleDest->LumpName, 0, CHANGELEVEL_NOINTERMISSION, -1);
            
            break;
        }
        if (Buttons == BT_SPEED)
        {
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        
        Delay(1);
    }
}

NamedScript MapSpecial void SkillComputer()
{
    // If Marines are hostile or the power is out, terminate
    if (MarinesHostile || PowerOut) return;
    
    // Terminate if you aren't the Arbitrator
    if (InMultiplayer && !Arbitrator) return;
    
    // if you're already in a menu, terminate
    if (Player.InMenu || Player.InShop || Player.OutpostMenu == OMENU_SKILLCOMPUTER) return;
    
    ActivatorSound("misc/edgar", 127);
    
    Player.OutpostMenu = OMENU_SKILLCOMPUTER;
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    
    while (true)
    {
        // Draw the background
        if (GetCVar("drpg_menudim"))
            FadeRange(0, 0, 0, 0.5, 0, 0, 0, 0.0, 0.25);

        // Text
        SetFont("BIGFONT");
        HudMessage("Skill Level: \Cj%d (%S\Cj)", SkillChoice + 1, SkillLevels[SkillChoice]);
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID, "Gold", 0.5, 0.5, 0.05, 0.5);
        
        // Input
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);

        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD && SkillChoice > 0)
        {
            ActivatorSound("menu/move", 127);
            SkillChoice--;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK && SkillChoice < (CompatMode == COMPAT_DRLA ? 5 : 4))
        {
            ActivatorSound("menu/move", 127);
            SkillChoice++;
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            SetSkill(SkillChoice);
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        if (Buttons == BT_SPEED)
        {
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        
        Delay(1);
    }
}

NamedScript MapSpecial void ToggleArena()
{
    // If Marines are hostile or the power is out, terminate
    if (MarinesHostile || PowerOut) return;
    
    // If you try to toggle the Arena and you aren't the Arena Arbitrator, terminate
    if (InMultiplayer && (ArenaPlayerNumber >= 0 && PlayerNumber() != ArenaPlayerNumber)) return;
    
    ArenaActive = !ArenaActive;
    
    SetFont("BIGFONT");
    
    if (ArenaActive)
    {
        ActivatorSound("arena/activate", 127);
        HudMessage("Arena Active");
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID, "Green", 0.5, 0.5, 2.0, 1.0);
        ArenaPlayerNumber = PlayerNumber();
        ArenaSetMusic();
    }
    else
    {
        ActivatorSound("arena/deactivate", 127);
        HudMessage("Arena Inactive");
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID, "Red", 0.5, 0.5, 2.0, 1.0);
        ArenaPlayerNumber = -1;
        SetOutpostMusic((PowerOut ? OUTPOST_MUSIC_LOWPOWER : OUTPOST_MUSIC_NORMAL));
    }
}

NamedScript MapSpecial void PassArenaLine()
{
    // If Marines are hostile or the power is out, terminate
    if (MarinesHostile || PowerOut) return;
    
    if (InMultiplayer && (ArenaPlayerNumber >= 0 && PlayerNumber() != ArenaPlayerNumber)) return;
    
    if (ArenaActive)
    {
        Ceiling_LowerToFloor(99, 64);
        ArenaLoop();
    }
}

NamedScript MapSpecial void SelectArenaWave()
{
    // If Marines are hostile or the power is out, terminate
    if (MarinesHostile || PowerOut) return;
    
    // if you're already in a menu, terminate
    if (Player.OutpostMenu == OMENU_MODULECONVERTER) return;
    
    if (InMultiplayer && (ArenaPlayerNumber >= 0 && PlayerNumber() != ArenaPlayerNumber)) return;

    ActivatorSound("menu/move", 127);
    Player.OutpostMenu = OMENU_WAVESELECTOR;

    WaveChoice = ArenaMaxWave;
    
    Delay(1);

    while (true)
    {
        SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
        
        // Draw the background
        if (GetCVar("drpg_menudim"))
            FadeRange(0, 0, 0, 0.5, 0, 0, 0, 0.0, 0.25);
        
        // Text
        SetFont("BIGFONT");
        HudMessage("Wave: \Cd%d\C-/\Cd%d", WaveChoice, ArenaMaxWave);
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID, "White", 0.5, 0.5, 0.05, 1.0);
        
        // Input
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);

        if (Buttons == BT_FORWARD && OldButtons != BT_FORWARD && WaveChoice > 1)
        {
            ActivatorSound("menu/move", 127);
            WaveChoice--;
        }
        if (Buttons == BT_BACK && OldButtons != BT_BACK && WaveChoice < ArenaMaxWave)
        {
            ActivatorSound("menu/move", 127);
            WaveChoice++;
        }
        if ((Buttons == BT_LEFT && OldButtons != BT_LEFT) ||
            (Buttons == BT_MOVELEFT && OldButtons != BT_MOVELEFT))
        {
            ActivatorSound("menu/move", 127);
            WaveChoice -= 10;
            if (WaveChoice <= 0) WaveChoice = 1;
        }
        if ((Buttons == BT_RIGHT && OldButtons != BT_RIGHT) ||
            (Buttons == BT_MOVERIGHT && OldButtons != BT_MOVERIGHT))
        {
            ActivatorSound("menu/move", 127);
            WaveChoice += 10;
            if (WaveChoice > ArenaMaxWave) WaveChoice = ArenaMaxWave;
        }
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            if (WaveChoice > 1)
                ArenaWave = WaveChoice - 1;
            else
                ArenaWave = 1;
            
            ActivatorSound("menu/move", 127);
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        if (Buttons == BT_SPEED)
        {
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        
        Delay(1);
    }
}

NamedScript MapSpecial void PissOffMarines(bool Steal)
{
    int ForcefieldState;
    
    // If the Marines are already hostile, terminate
    if (MarinesHostile) return;
    
    // Only in a base
    if (!CurrentLevel->UACBase) return;
    
    // Set flag
    MarinesHostile = true;
    
    // Demotion
    if (Player.RankLevel > 0 && Steal)
        Player.Rank = RankTable[Player.RankLevel - 2];
    
    // Iterate Marines pre-Delay
    if (Steal)
        for (int i = MarineTID; i <= MarineMaxTID; i++)
        {
            // Sight Alert
            if (CheckSight(i, 0, 0))
            {
                PlaySound(i, "drpgmarines/shopkeephatred", 0, 1.0, false, ATTN_NORM);
                SpawnForced("DRPGAlertIcon", GetActorX(i), GetActorY(i), GetActorZ(i) + GetActorPropertyFixed(i, APROP_Height) + 4.0, 0, 0);
            }
        }
    
    Delay(35 * 2);
    
    // Combat music
    SetOutpostMusic((PowerOut ? OUTPOST_MUSIC_LOWPOWER_COMBAT : OUTPOST_MUSIC_COMBAT));
    
    // Remove Friendly flag from turrets
    if (!InTitle)
        SetActorProperty(TurretTID, APROP_Friendly, false);
    
    // Iterate Marines post-Delay
    for (int i = MarineTID; i <= MarineMaxTID; i++)
    {
        // Remove Friendly flag
        if (!InTitle)
            SetActorProperty(i, APROP_Friendly, false);
        
        // Enrage Marines
        if (GetActorProperty(i, APROP_Health) > 0 && !InTitle)
            SetActorState(i, "Enraged", false);
        
        // Give Credits to Marines
        SetActorInventory(i, "DRPGCredits", Random(10, 1000));
    }
    
    // Enrage Turrets
    if (ClassifyActor(TurretTID) & ACTOR_ALIVE && !InTitle)
    {
        SetActorState(TurretTID, "Enraged", false);
        
        // Power-down Turrets for Large Powersuit
        if (OutpostNotoriety >= 3)
            SetActorState(TurretTID, "PoweredDown", false);
    }
    
    // Enrage placeholder bosses
    if (!InTitle)
        SetActorState(MarineBossTID - 1, "Enraged", false);
    
    // Sector Lighting
    for (int i = 0; i <= MAX_OUTPOST_ID; i++)
    {
        Sector_SetColor(i, 255, 0, 0, 0);
        Light_Glow(i, 160, 192, 30);
    }
    
    // Drop the Credits room blocker
    Ceiling_LowerToFloor(CreditsBlockerID, 256);
    
    // Start the Alarm loop
    AlarmLoop();
    
    // Boss Spawning
    if (!InTitle) // These guys were absolutely massacring the monsters, ruining the cinematics
        SpawnBoss();
    
    // Raise Entry Forcefield
    if (!InTitle)
    {
        Line_SetBlocking(ForcefieldGeneratorID, BLOCKF_EVERYTHING | BLOCKF_SIGHT | BLOCKF_HITSCAN, 0);
        SetLineTexture(ForcefieldGeneratorID, SIDE_FRONT, TEXTURE_MIDDLE, "FORCEFIE");
        SpawnSpotForced("TeleportFog", GeneratorTID, 0, 0);
        SpawnSpotForced("DRPGForcefieldGenerator", GeneratorTID, GeneratorTID, 0);
    }
    
    // Title Map Handling
    if (InTitle)
    {
        // Create Hell Rifts
        SpawnSpotForced("DRPGTeleportRift", RiftSpotTID, RiftSpotTID, 0);
        
        Thing_Hate(TurretTID, RiftSpotTID + 1, 6);
        SetActorState(TurretTID, "Enraged", false);
        
        // Alert the Marines
        for (int i = MarineTID; i <= MarineMaxTID; i++)
            SetActorState(i, "See", false);
    }
    
    // Synchronize delay with SpawnBoss()
    if (OutpostNotoriety >= 3)
        Delay(35 * 30);
    
    // Loop
    while (true)
    {
        // Move all players outside the entry sector
        if (!BossDead && !InTitle)
            for (int i = 0; i < MAX_PLAYERS; i++)
                if (ThingCountSector(0, Players(i).TID, EntrySectorID) > 0)
                    TeleportOther(Players(i).TID, HallTeleportSpotID + i, true);
        
        // Spawn Reinforcements
        if ((Timer() % (35 * 10)) == 0 && OutpostNotoriety <= 2)
        {
            SpawnSpotForced("TeleportFog", MarineSpotTID, 0, 0);
            
            if (InTitle)
            {
                for (int i = HallTeleportSpotID; i < HallTeleportSpotID + 8; i++)
                {
                    SpawnSpotForced("TeleportFog", i, 0, 0);
                    if (CompatMode == COMPAT_DRLA)
                        SpawnSpotFacingForced("DRPGMarineReinforcementDRLASpawner", i, MarineTID);
                    else
                        SpawnSpotFacingForced("DRPGMarineReinforcementSpawner", i, MarineTID);
                }
            }
            else
            {
                if (OutpostNotoriety == 2) // Special handling for Chasing Minigunners
                    SpawnSpotFacingForced("DRPGMarineMinigunHuntingYerAss", MarineSpotTID, MarineTID);
                else
                    if (CompatMode == COMPAT_DRLA)
                        SpawnSpotFacingForced("DRPGMarineReinforcementDRLASpawner", MarineSpotTID, MarineTID);
                    else
                        SpawnSpotFacingForced("DRPGMarineReinforcementSpawner", MarineSpotTID, MarineTID);
                
                if (!InTitle)
                    SetActorProperty(MarineTID, APROP_Friendly, false);
            }
        }
        
        // Make the Marines fight enemies in title map
        if (InTitle)
        {
            for (int i = MarineTID; i <= MarineMaxTID; i++)
            {
                SetActorProperty(i, APROP_Friendly, true);
                Thing_ChangeTID(i, MarineTID);
            }
            
            SetActorProperty(MarineBossTID, APROP_Friendly, true);
            Thing_Hate(RiftSpotTID + 1, MarineTID, 6);
        }
        
        // Boss Timer
        if (ForcefieldTimer > 0 && OutpostNotoriety == 2)
        {
            // Set completion state on the Shield Generator
            SetActorState(GeneratorTID, StrParam("%dPowerLoop", ForcefieldTimer / ((35 * 60 * GameSkill()) / 7)), false);
            
            // Decrement timer
            ForcefieldTimer--;
        }
        
        // Different checks for specific Notoriety levels
        if (ForcefieldState == 0)
            if (OutpostNotoriety == 2 && ForcefieldTimer <= 0)
                ForcefieldState = 1;
            else if (OutpostNotoriety != 2 && ThingCount(0, MarineBossTID) <= 0)
                ForcefieldState = 1;
        
        // Bosses are dead or boss timer expires
        if (ForcefieldState == 1)
        {
            AmbientSound("misc/poweroff", 127);
            
            // Disable Entry Forcefield
            Line_SetBlocking(ForcefieldGeneratorID, 0, BLOCKF_EVERYTHING | BLOCKF_SIGHT | BLOCKF_HITSCAN);
            SetLineTexture(ForcefieldGeneratorID, SIDE_FRONT, TEXTURE_MIDDLE, "");
            SetActorState(GeneratorTID, "Death", false);
            
            // Boss is dead
            BossDead = true;
            ForcefieldState = 2;
        }
        
        Delay(1);
    }
}

// TODO
NamedScript MapSpecial void ModuleConverter()
{
    // If Marines are hostile or the power is out, terminate
    if (MarinesHostile || PowerOut) return;
    
    // if you're already in a menu, terminate
    if (Player.InMenu || Player.InShop || Player.OutpostMenu == OMENU_MODULECONVERTER) return;
}

// Credit Room Script
NamedScript MapSpecial void CreditRoom(int ID)
{
    if (ID == 1) // Enter
        SetOutpostMusic(OUTPOST_MUSIC_CREDITS);
    if (ID == 2) // Exit
        SetOutpostMusic((PowerOut ? OUTPOST_MUSIC_LOWPOWER : OUTPOST_MUSIC_NORMAL));
    
    if (ID == 3) // Kyle873 - That's me!
    {
        SetFont("BIGFONT");
        HudMessage("Kyle873");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 3.0, 2.0);
        Delay(35);
        SetFont("SMALLFONT");
        HudMessage("What do you mean I can't nerf XP Gain to 1 per monster?!");
        EndHudMessage(HUDMSG_FADEOUT, 0, "White", 0.5, 0.55, 3.0, 2.0);

        int RealCredits = CheckInventory("DRPGCredits");
        
        ActivatorSound("credits/payout", 127);
        Log("\CkYou have been paid -2147483648 by the UAC!");
        TakeInventory("DRPGCredits", RealCredits);
        Delay(35 * 10);
        GiveInventory("DRPGCredits", RealCredits);
    }
    
    if (ID == 4) // Lord Misfit
    {
        SetFont("BIGFONT");
        HudMessage("Lord Misfit");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 3.0, 2.0);
        Delay(35);
        SetFont("SMALLFONT");
        HudMessage("I swear it's a real bug this time!");
        EndHudMessage(HUDMSG_FADEOUT, 0, "White", 0.5, 0.55, 3.0, 2.0);
        
        str VarString = "SetVar";
        
        Delay(35 * 3);
        for (int i = 0; i < 100; i++)
        {
            if (Random(1, 3) == 1) VarString = StrParam("%S%S", VarString, "Var");
            HudMessage("%S", VarString);
            EndHudMessage(HUDMSG_FADEOUT, 0, ColorNames[Random(1, 21)], RandomFixed(0.0, 1.0), RandomFixed(0.0, 1.0), 3.0, 2.0);
            Delay(1);
        }
    }
    
    if (ID == 5) // Ryan Cordell
    {
        SetFont("BIGFONT");
        HudMessage("Ryan Cordell");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 7.0, 2.0);
        Delay(35);
        
        for (int i = 0; i < 10; i++)
        {
            ActivatorSound("weapons/rocklx", 127);
            Delay(Random(5, 10));
        }
        
        Delay(35 * 2);
        SetFont("SMALLFONT");
        HudMessage("Did I do that?");
        EndHudMessage(HUDMSG_FADEOUT, 0, "White", 0.5, 0.55, 3.0, 2.0);
    }
    
    if (ID == 6) // marrub
    {
        SetFont("BIGFONT");
        HudMessage("marrub");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 3.0, 2.0);
        Delay(35);
        HudMessage("I HOPE YOU LIKE SHOTGUNS!");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Brick", 0.5, 0.55, 3.0, 2.0);
        Delay(35 * 2);
        
        for (int i = 0; i < 50; i++)
        {
            DropItem(0, "DRPGDumbShotgun", 1, 255);
            Delay(1);
        }
    }

    if (ID == 7) // Kate
    {
        SetFont("BIGFONT");
        HudMessage("Kate");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 3.0, 2.0);
        Delay(35);
        HudMessage("\CgR\CiA\CkI\CdN\ChB\CtO\CaW\CjS");
        EndHudMessage(HUDMSG_FADEOUT, 0, "White", 0.5, 0.55, 3.0, 2.0);
        Delay(35);
        
        FadeTo(255, 0, 0, 0.5, 0.5);
        Delay(17);
        FadeTo(255, 128, 0, 0.5, 0.5);
        Delay(17);
        FadeTo(255, 255, 0, 0.5, 0.5);
        Delay(17);
        FadeTo(0, 255, 0, 0.5, 0.5);
        Delay(17);
        FadeTo(0, 0, 255, 0.5, 0.5);
        Delay(17);
        FadeTo(128, 0, 255, 0.5, 0.5);
        Delay(17);
        FadeTo(255, 0, 255, 0.5, 0.5);
        Delay(17);
        FadeTo(255, 255, 255, 0.5, 0.5);
        Delay(17);
        FadeTo(0, 0, 0, 0.0, 0.5);
    }
    
    if (ID == 8) // Yholl
    {
        SetFont("BIGFONT");
        HudMessage("Yholl");
        EndHudMessage(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 3.0, 2.0);
        Delay(35);
        HudMessage("\CaYour suffering pleases me");
        EndHudMessage(HUDMSG_FADEOUT, 0, "White", 0.5, 0.55, 3.0, 2.0);
        Delay(35);
        
        for (int i = 0; i < 50; i++)
        {
            DropItem(0, "DRPGDumbPistol", 1, 255);
            Delay(1);
        }
    }
}

// Shop Special UI
NamedScript MapSpecial void ShopSpecial()
{
    // if you're already in a menu, terminate
    if (Player.InMenu || Player.InShop || Player.OutpostMenu == OMENU_SHOPSPECIAL) return;
    
    // If there is no shop special
    if (ShopSpecialItem == GetBlankItem())
    {
        ActivatorSound("menu/error", 127);
        PrintError(StrParam("There is currently no Shop Special item.\n\nNext restock will be in \Cj%S\C-.", FormatTime(ShopSpecialTimer)));
        return;
    }
    
    // If the shop special was already bought
    if (ShopSpecialBought)
    {
        ActivatorSound("menu/error", 127);
        PrintError(StrParam("Shop Special is currently out of stock.\n\nNext restock will be in \Cj%S\C-.", FormatTime(ShopSpecialTimer)));
        return;
    }
    
    ActivatorSound("menu/move", 127);
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    Player.OutpostMenu = OMENU_SHOPSPECIAL;
    
    while (true)
    {
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
        str Name = ShopSpecialItem->Name;
        int Discount = GetCVar("drpg_shopspecial_discount") + Player.ShopDiscount;
        // Cap the Shop Special Discount at 75%
        if (Discount > 75)
            Discount = 75;
        int Cost = ShopSpecialItem->Price - ((ShopSpecialItem->Price * Discount) / 100);
        
        // If the item's already been bought or the timer expires, terminate
        if (ShopSpecialBought || ShopSpecialTimer <= 0)
        {
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        
        // The cost should always be at least 1 Credit
        if (Cost <= 0) Cost = 1;
        
        // Draw the background
        if (GetCVar("drpg_menudim"))
            FadeRange(0, 0, 0, 0.5, 0, 0, 0, 0.0, 0.25);
        
        // Input
        if (Buttons == BT_USE && OldButtons != BT_USE)
        {
            // Buy Item
            if (CheckInventory("DRPGCredits") >= Cost)
            {
                // DoomRL Compatibility

                TakeInventory("DRPGCredits", Cost);
                SpawnForced(ShopSpecialItem->Actor, GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
                SetActorVelocity(Player.TID, 0.01, 0.01, 0, true, false);
                ShopSpecialBought = true;
                
                ActivatorSound("credits/payout", 127);
                Delay(1);
                SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
                Player.OutpostMenu = 0;
                return;
            }
            else
            {
                PrintError("You don't have enough Credits to buy this item");
                ActivatorSound("menu/error", 127);
            }
        }
        if (Buttons == BT_SPEED)
        {
            ActivatorSound("menu/move", 127);
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
            return;
        }
        
        // Drawing
        SetHudSize(0, 0, false);
        SetFont("BIGFONT");
        HudMessage("%S\n\Ck%d C (Discount: %d%%)\n\CdTime Left: %S",
                   Name, Cost, Discount, FormatTime(ShopSpecialTimer));
        EndHudMessage(HUDMSG_FADEOUT, MENU_ID, "White", 1.5, 0.5, 0.05, 1.0);
        
        Delay(1);
    }
}

// Mission BBS
NamedScript MapSpecial void MissionBBS()
{
    int Index;
    int Difficulty;
    
    // If Marines are hostile, terminate
    if (MarinesHostile) return;
    
    // if you're already in a menu, terminate
    if (Player.InMenu || Player.InShop || Player.OutpostMenu == OMENU_BBS) return;
    
    // You need at least 1 Rank to get a mission
    if (Player.RankLevel == 0)
    {
        PrintError("You cannot accept any missions until you reach the first rank");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    // Make sure the Rewards List is finished Processing
    if (!RewardsInit || !MissionInit)
    {
        PrintError("The Mission BBS is currently processing requests...");
        ActivatorSound("menu/error", 127);
        return;
    }
    
    // Freeze the Player
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    
    Player.OutpostMenu = OMENU_BBS;
    
    ActivatorSound("menu/move", 127);
    
    while (Player.OutpostMenu == OMENU_BBS)
    {
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
        MissionInfo *Mission = &Missions[Difficulty][Index];
        
        // Set the HUD Size
        SetHudSize(GetActivatorCVar("drpg_menu_width"), GetActivatorCVar("drpg_menu_height"), true);
        
        // Title
        SetFont("BIGFONT");
        HudMessage("\CdMission BBS\n\CjDifficulty: (%S\C-)", MissionDifficulties[Difficulty]);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 0.1, 24.1, 0.05);
        
        // Mission Labels
        for (int i = MAX_MISSIONS - 1; i >= 0; i--)
        {
            MissionInfo *MissionIter = &Missions[Difficulty][i];
            
            // Cursor
            if (i == Index)
                PrintSprite("MissBoxH", 0, 0.1 + (i % (MAX_MISSIONS / 3) * 48.0) + Round((Cos((fixed)Timer() / 64.0) * 8.0)), 80.0 + (i / (MAX_MISSIONS / 3) * 48.0) + Round((Sin((fixed)Timer() / 64.0) * 8.0)), 0.05);
            
            // Icon
            PrintSprite(StrParam("BBS_M%d", MissionIter->Type + 1), 0, 8.1 + (i % (MAX_MISSIONS / 3) * 48.0), 80.0 + (i / (MAX_MISSIONS / 3) * 48.0), 0.05);
            
            // Box
            PrintSprite("MissBoxB", 0, 0.1 + (i % (MAX_MISSIONS / 3) * 48.0), 80.0 + (i / (MAX_MISSIONS / 3) * 48.0), 0.05);
        }
        
        // Currently selected Mission
        DrawMissionInfo(Mission, 0, 216, false);
        
        // Input
        if (Buttons & BT_FORWARD && !(OldButtons & BT_FORWARD))
        {
            ActivatorSound("menu/move", 127);
            Index -= MAX_MISSIONS / 3;
            if (Index < 0)
            {
                Index = 0;
                if (Difficulty > 0)
                    Difficulty--;
            }
        }
        if (Buttons & BT_BACK && !(OldButtons & BT_BACK))
        {
            ActivatorSound("menu/move", 127);
            Index += MAX_MISSIONS / 3;
            if (Index > MAX_MISSIONS - 1)
            {
                Index = 0;
                if (Difficulty < Player.RankLevel - 1)
                {
                    if (Difficulty >= MAX_DIFFICULTIES - 1)
                        Difficulty = MAX_DIFFICULTIES - 1;
                    else
                        Difficulty++;
                }
                else
                    Index = MAX_MISSIONS - 1;
            }
        }
        if (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT))
        {
            ActivatorSound("menu/move", 127);
            Index--;
            if (Index < 0)
            {
                Index = 0;
                if (Difficulty > 0)
                    Difficulty--;
            };
        };
        if (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT))
        {
            ActivatorSound("menu/move", 127);
            Index++;
            if (Index > MAX_MISSIONS - 1)
            {
                Index = 0;
                if (Difficulty < Player.RankLevel - 1)
                {
                    if (Difficulty >= MAX_DIFFICULTIES - 1)
                        Difficulty = MAX_DIFFICULTIES - 1;
                    else
                        Difficulty++;
                }
                else
                    Index = MAX_MISSIONS - 1;
            }
        }
        if (Buttons == BT_USE && OldButtons != BT_USE && !Player.Mission.Active)
        {
            ActivatorSound("mission/get", 127);
            Mission->Active = true;
            Player.Mission = *Mission;
            CreateMissionAt(Difficulty, Index);
        };
        if (Buttons == BT_SPEED)
        {
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            Player.OutpostMenu = 0;
        }
        if (Buttons == BT_ATTACK && OldButtons != BT_ATTACK && Player.Mission.Active)
        {
            ActivatorSound("mission/fail", 127);
            SetFont("BIGFONT");
            SetHudSize(640, 480, false);
            HudMessage("Mission Aborted!");
            EndHudMessage(HUDMSG_FADEOUT, MISSION_ID, "Red", 320.4, 400.0, 3.0, 2.0);
            ClearMission();
        }
        
        Delay(1);
    }
}

// Roulette
NamedScript MapSpecial void MinigameHandler()
{
    // Return if already in a minigame
    if (Player.InMenu || Player.InShop || Player.InMinigame) return;
    
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    
    // TODO: This will just play Roulette for now
    if (GetPlayerInput(PlayerNumber(), INPUT_BUTTONS) & BT_SPEED)
    {
        if (CheckInventory("DRPGChipPlatinum") > 0)
        {
            SetFont("BIGFONT");
            HudMessage("Rare Item Roulette");
            EndHudMessage(HUDMSG_FADEOUT, 0, "Gold", 0.5, 0.75, 0.75, 0.25);
            Delay(35);
            ItemRoulette(true);
        }
        else
        {
            PrintError("You need a \CjPlatinum Chip\C- to use the Rare Item Roulette");
            ActivatorSound("menu/error", 127);
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
        }
    }
    else
    {
        if (CheckInventory("DRPGChipGold") > 0)
        {
            SetFont("BIGFONT");
            HudMessage("Item Roulette");
            EndHudMessage(HUDMSG_FADEOUT, 0, "Gold", 0.5, 0.75, 0.75, 0.25);
            Delay(35);
            ItemRoulette(false);
        }
        else
        {
            SetFont("BIGFONT");
            PrintError("You need a \CfGold Chip\C- to use the Item Roulette");
            ActivatorSound("menu/error", 127);
            SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
        }
    }
}

// Handles the 6 Key Secret
NamedScript MapSpecial void OutpostSecret()
{
    if (CheckInventory("DRPGRedCard") && CheckInventory("DRPGYellowCard") && CheckInventory("DRPGBlueCard") &&
        CheckInventory("DRPGRedSkull") && CheckInventory("DRPGYellowSkull") && CheckInventory("DRPGBlueSkull"))
    {
        ActivatorSound("misc/secret", 127);
        Teleport(SecretTeleportTID + PlayerNumber(), false);
    }
}

NamedScript MapSpecial void PowerOutage()
{
    // If the power is already out, terminate
    if (PowerOut) return;
    
    Delay(10);
    
    PowerOut = true;
    
    // Blackout
    if (!MarinesHostile)
    {
        SetMusic("");
        ActivatorSound("misc/poweroff", 127);
        for (int i = 0; i < MAX_OUTPOST_ID; i++)
            Light_Fade(i, 0, 10);
    }
    
    // Disable Shop Forcefields
    Line_SetBlocking(ForcefieldID, 0, 1023);
    SetLineTexture(ForcefieldID, SIDE_FRONT, TEXTURE_MIDDLE, "");
    
    // Send Turrets into PoweredDown state
    SetActorState(TurretTID, "PoweredDown");
    
    // Randomized delay for the power to come back on
    Delay(Random(35 * 3, 35 * 5));
    
    // Enable Emergency Power
    if (!MarinesHostile)
    {
        SetOutpostMusic(OUTPOST_MUSIC_LOWPOWER);
        ActivatorSound("misc/poweron", 127);
        
        for (int i = 0; i < MAX_OUTPOST_ID; i++)
        {
            Sector_SetColor(i, 255, 0, 0, 0);
            Light_Fade(i, 160, 60);
        }
    }
}

NamedScript void AlarmLoop()
{
    while (true)
    {
        if ((Timer() % 30) == 0)
            AmbientSound("misc/alarm", 127);
        
        Delay(1);
    }
}

NamedScript void PlaceBoss()
{
    // Minigunners
    if (OutpostNotoriety == 0)
        SpawnSpotFacingForced("DRPGMarineMinigunNotActuallyPeople", BossSpotTID, MarineBossTID - 1);
    
    // Small Powersuit
    if (OutpostNotoriety == 1)
        SpawnSpotFacingForced("DRPGPowerSuitSlackingOffDownstairs", BossSpotTID + 1, MarineBossTID - 1);
    
    // Heavy Marines
    if (OutpostNotoriety == 2)
        SpawnSpotFacingForced("DRPGMarineMinigunNotActuallyPeople", BossSpotTID, MarineBossTID - 1);
    
    // Heavy Powersuit & Heavy Powersuit Mk. II
    if (OutpostNotoriety >= 3)
        SpawnSpotFacingForced("DRPGHeavyPowerSuitHavingASiesta", BossSpotTID + 2, MarineBossTID - 1);
}

NamedScript void SpawnBoss()
{
    // Minigunners
    if (OutpostNotoriety == 0)
    {
        SpawnSpotForced("TeleportFog", NotorietySpotTID, 0, 0);
        SpawnSpotFacingForced("DRPGMarineMinigun", NotorietySpotTID, MarineBossTID);
    }
    
    // Small Powersuit
    if (OutpostNotoriety == 1)
    {
        SpawnSpotForced("DRPGBigTeleportFog", NotorietySpotTID, 0, 0);
        SpawnSpotFacingForced("DRPGPowerSuit", NotorietySpotTID, MarineBossTID);
    }
    
    // Heavy Marines
    if (OutpostNotoriety == 2)
    {
        SpawnSpotForced("TeleportFog", NotorietySpotTID, 0, 0);
        SpawnSpotFacingForced("DRPGMarineMinigunHuntingYerAss", NotorietySpotTID, MarineBossTID);
    }
    
    // Heavy Powersuit
    if (OutpostNotoriety >= 3)
    {
        // Teleport out guards
        for (int i = MarineTID; i <= MarineMaxTID; i++)
        {
            SpawnSpot("TeleportFog", i, 0, 0);
            Thing_Remove(i);
        }
        
        SetMusic("");
        Delay(35 * 30);
        if (OutpostNotoriety >= 4)
            SetOutpostMusic(OUTPOST_MUSIC_BOSS);
        
        SpawnSpotForced("DRPGHugeTeleportFog", NotorietySpotTID + 1, 0, 0);
        SpawnSpotFacingForced((OutpostNotoriety >= 4 ? "DRPGSuperPowerSuit" : "DRPGHeavyPowerSuit"), NotorietySpotTID + 1, MarineBossTID);
    }
}

void SpawnShopSpecialItem()
{
    if (CurrentLevel->UACBase)
    {
        // Remove old item
        Thing_Remove(ShopSpecialTID + 1);
        
        // Spawn new item
        SpawnSpotForced("DRPGTurretTeleport", ShopSpecialTID, 0, 0);
        SpawnSpotForced(ShopSpecialItem->Actor, ShopSpecialTID, ShopSpecialTID + 1, 0);
        SetActorProperty(ShopSpecialTID + 1, APROP_Invulnerable, true);
        Thing_SetSpecial(ShopSpecialTID + 1, 80, 8);
    }
}

void SetOutpostMusic(int Type)
{
    str Music;
    
    switch (Type)
    {
    case OUTPOST_MUSIC_NORMAL:
        Music = "Outpost";
        break;
    case OUTPOST_MUSIC_COMBAT:
        Music = "Outpost2";
        break;
    case OUTPOST_MUSIC_LOWPOWER:
        Music = "Outpost3";
        break;
    case OUTPOST_MUSIC_LOWPOWER_COMBAT:
        Music = "Outpost4";
        break;
    case OUTPOST_MUSIC_BOSS:
        Music = "OPBoss";
        break;
    case OUTPOST_MUSIC_MEGABOSS:
        Music = "OPBoss2";
        break;
    case OUTPOST_MUSIC_CREDITS:
        Music = "OutpostC";
        break;
    }
    
    SetMusic(Music);
}
