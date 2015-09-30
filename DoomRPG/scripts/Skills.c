#include "RPG.h"

#include "Arena.h"
#include "Crate.h"
#include "Map.h"
#include "Menu.h"
#include "Monsters.h"
#include "Outpost.h"
#include "Shield.h"
#include "Shop.h"
#include "Skills.h"
#include "Stats.h"
#include "Utils.h"

int RPGMap BulletTimeTimer;

int RPGGlobal SkillCategoryMax[MAX_CATEGORIES] =
{
    4, 8, 9, 7, 17, 7
};

Skill RPGGlobal SkillData[MAX_CATEGORIES][MAX_SKILLS] =
{
    // Healing/Support
    {
        {
            .Name = "Heal",
            .Cost = 75,
            .MaxLevel = 4,
            .Use = Heal,
            .Description =
            {
                "Recover all of your health",
                "Recover all of your health\nHeals Status Effects",
                "Recover all of your health\nHeals Status Effects\n\CaAlso Effects Teammates",
                "Recover to 200% of your maximum health\n\CgSlowly drains back down to 100% maximum health\nHeals Status Effects\n\CaAlso Affects Teammates"
            }
        },
        {
            .Name = "Heal Summons",
            .Cost = 100,
            .MaxLevel = 1,
            .Use = HealSummons,
            .Description =
            {
                "Summons recover all of their health"
            }
        },
        {
            .Name = "Decontamination",
            .Cost = 300,
            .MaxLevel = 1,
            .Use = Decontaminate,
            .Description =
            {
                "Remove all of your Toxicity"
            }
        },
        {
            .Name = "Repair Armor",
            .Cost = 200,
            .MaxLevel = 1,
            .Use = Repair,
            .Description =
            {
                "Repair your currently worn armor"
            }
        },
    },
    
    // Powerups
    {
        {
            .Name = "Invulnerability",
            .Cost = 250,
            .MaxLevel = 2,
            .Use = Powerup,
            .Description =
            {
                "Invulnerability to all attacks\n\Cd(30 Sec)",
                "Invulnerability to all attacks\nProjectiles are reflected back at enemies\n\Cd(30 Sec)\nHalf cooldown time"
            }
        },
        {
            .Name = "Invisibility",
            .Cost = 100,
            .MaxLevel = 2,
            .Use = Powerup,
            .Description =
            {
                "Makes you invisible to enemies\n\Cd(30 sec)",
                "Makes you invisible to enemies\nSome projectiles pass through you\n\Cd(30 sec)"
            }
        },
        {
            .Name = "Time Freeze",
            .Cost = 200,
            .MaxLevel = 2,
            .Use = BulletTime,
            .Description =
            {
                "Stutter Time",
                "Freeze Time",
            }
        },
        {
            .Name = "Enviro-Shield",
            .Cost = 100,
            .MaxLevel = 1,
            .Use = Powerup,
            .Description =
            {
                "Protection from Damage Floors and other\nenvironmental hazards"
            }
        },
        {
            .Name = "Night Vision",
            .Cost = 200,
            .MaxLevel = 1,
            .Use = Powerup,
            .Description =
            {
                "Allows you to see in the dark"
            }
        },
        {
            .Name = "Berserk",
            .Cost = 200,
            .MaxLevel = 1,
            .Use = Powerup,
            .Description =
            {
                "Full Health\nIncreased Melee Damage"
            }
        },
        {
            .Name = "Mental Mapping",
            .Cost = 200,
            .MaxLevel = 1,
            .Use = Powerup,
            .Description =
            {
                "Full Map\nItem/Enemy Tracking"
            }
        },
        {
            .Name = "Supply Drop",
            .Cost = 200,
            .MaxLevel = 10,
            .Use = DropSupply,
            .Description =
            {
                "Drop a Large Backpack full of Ammo at your location"
                // Crate Drop Description is generated dynamically
            }
        }
    },
    
    // Auras
    {
        {
            .Name = "Red Aura",
            .Cost = 100,
            .MaxLevel = 6,
            .Use = UseAura,
            .Description =
            {
                "1.25x Damage",
                "1.5x Damage",
                "1.75x Damage",
                "2x Damage",
                "3x Damage",
                "4x Damage"
            }
        },
        {
            .Name = "Green Aura",
            .Cost = 100,
            .MaxLevel = 5,
            .Use = UseAura,
            .Description =
            {
                "+5% Damage Reduction",
                "+10% Damage Reduction",
                "+15% Damage Reduction\nDamage Floor Protection",
                "+20% Damage Reduction\nDamage Floor Protection",
                "+25% Damage Reduction\nDamage Floor Protection"
            }
        },
        {
            .Name = "White Aura",
            .Cost = 100,
            .MaxLevel = 5,
            .Use = UseAura,
            .Description =
            {
                "Double Combo",
                "Double Combo\nConstant Combo",
                "Double Combo\nConstant Combo\n2x XP Per Kill",
                "Double Combo\nConstant Combo\n2x XP Per Kill\nSlow XP Gain",
                "Double Combo\nConstant Combo\n2x XP Per Kill\nFast XP Gain"
            }
        },
        {
            .Name = "Pink Aura",
            .Cost = 100,
            .MaxLevel = 3,
            .Use = UseAura,
            .Description =
            {
                "Immune to Status Effects",
                "Immune to Status Effects\nDrain Enemy HP",
                "Immune to Status Effects\nDrain Enemy HP\nImmunity to EP, Ammo and Credit stealing effects"
            }
        },
        {
            .Name = "Blue Aura",
            .Cost = 100,
            .MaxLevel = 5,
            .Use = UseAura,
            .Description =
            {
                "10% Skill Cost Refund when using a Skill",
                "20% Skill Cost Refund when using a Skill",
                "30% Skill Cost Refund when using a Skill",
                "40% Skill Cost Refund when using a Skill",
                "50% Skill Cost Refund when using a Skill"
            }
        },
        {
            .Name = "Purple Aura",
            .Cost = 100,
            .MaxLevel = 4,
            .Use = UseAura,
            .Description =
            {
                "2x HP/EP Regen Amount",
                "3x HP/EP Regen Amount",
                "4x HP/EP Regen Amount",
                "4x HP/EP Regen Amount\n-2x HP/EP Regen Timers"
            }
        },
        {
            .Name = "Orange Aura",
            .Cost = 100,
            .MaxLevel = 3,
            .Use = UseAura,
            .Description =
            {
                "Double Movement Speed",
                "Double Movement Speed\nDouble Jump Height",
                "Double Movement Speed\nDouble Jump Height\nDouble Firing Speed"
            },
        },
        {
            .Name = "Dark Blue Aura",
            .Cost = 100,
            .MaxLevel = 7,
            .Use = UseAura,
            .Description =
            {
                "Clip Regen",
                "Clip Regen\nShell Regen",
                "Clip Regen\nShell Regen\nRocket Regen",
                "Clip Regen\nShell Regen\nRocket Regen\nCell Regen",
                "Clip Regen\nShell Regen\nRocket Regen\nCell Regen\n2x Regen Speed",
                "Clip Regen\nShell Regen\nRocket Regen\nCell Regen\n4x Regen Speed",
                "Clip Regen\nShell Regen\nRocket Regen\nCell Regen\n4x Regen Speed\nInfinite Ammo"
            }
        },
        {
            .Name = "Yellow Aura",
            .Cost = 100,
            .MaxLevel = 5,
            .Use = UseAura,
            .Description =
            {
                "Slow Money Generation\n1.25x Drop Chances",
                "Medium Money Generation\n1.5x Drop Chances",
                "Fast Money Generation\n2x Drop Chances",
                "Very Fast Money Generation\n4x Drop Chances",
                "Mega Money Generation\n8x Drop Chances"
            }
        }
    },
    
    // Attacks
    {
        {
            .Name = "Weaken",
            .Cost = 200,
            .MaxLevel = 5,
            .Use = Weaken,
            .Description =
            {
                "Weakens an enemy\nReduces stats by 1/16th",
                "Weakens an enemy\nReduces stats by 1/8th",
                "Weakens an enemy\nReduces stats by 1/4th",
                "Weakens an enemy\nReduces stats by half",
                "Weakens an enemy\nReduces stats by half\nDestroys all active Auras"
            }
        },
        {
            .Name = "Translocate",
            .Cost = 50,
            .MaxLevel = 1,
            .Use = Translocate,
            .Description =
            {
                "Teleports a monster to a random location\nin the area"
            }
        },
        {
            .Name = "Repulsion",
            .Cost = 50,
            .MaxLevel = 4,
            .Use = Repulse,
            .Description =
            {
                "A small blast which slightly pushes enemies away",
                "A blast which pushes enemies away",
                "A large blast which greatly pushes enemies away",
                "A huge blast which launches enemies away"
            }
        },
        {
            .Name = "Aura Steal",
            .Cost = 500,
            .MaxLevel = 1,
            .Use = AuraSteal,
            .Description =
            {
                "Steals an enemies Auras\nTime is based on their Energy\nCan only steal Auras if you currently have none active"
            }
        },
        {
            .Name = "Soul Steal",
            .Cost = 500,
            .MaxLevel = 1,
            .Use = SoulSteal,
            .Description =
            {
                "Kill a target below 25% health, stealing their health and soul"
            }
        },
        {
            .Name = "Disruption",
            .Cost = 50,
            .MaxLevel = 5,
            .Use = Disruption,
            .Description =
            {
                "Temporarily disables an enemy's auras",
                "Temporarily disables an enemy's auras\n\CdAffects Shadows auras",
                "Temporarily disables an enemy's auras\n\CdAffects Shadows auras\nTargeted enemy drops stolen items",
                "Temporarily disables enemies' auras\n\CdAffects Shadows auras\nDisrupts all enemies in a small radius",
                "Temporarily disables enemies' auras\n\CdAffects Shadows auras\nDisrupts all enemies in a large radius"
            }
        },
        {
            .Name = "Plasma Beam",
            .Cost = 65,
            .MaxLevel = 3,
            .Use = PlasmaBeam,
            .Description =
            {
                "Unleashes a beam of searing flames\n\CdDeals \CgFire\Cd damage",
                "Unleashes a beam of searing flames and crackling plasma\n\CdDeals \CgFire\Cd and \CvElectric\Cd damage\n\CdPierces through enemies",
                "Unleashes a beam of deadly and powerful dark energies\n\CdDeals \CuShadow\Cd damage\n\CdPierces through enemies\n\CdIgnores armors and defenses"
            }
        }
        /*
        {
            .Name = "Electro-Mine",
            .Cost = 100,
            .MaxLevel = 3,
            .Use = ElectroMine,
            .Description =
            {
                "Creates a floating electronic mine\nGravitates enemies toward it, then explodes",
                "Creates a floating electronic mine\nGravitates enemies toward it, then explodes\nEmits electrical arcs that drain enemies' health",
                "Creates a floating electronic mine\nGravitates enemies toward it, then explodes\nEmits electrical arcs that drain enemies' health and freezes them in place"
            }
        }
        */
    },
    
    // Summons
    {
        {
            .Name = "Summon Marine",
            .Cost = 100,
            .MaxLevel = 7,
            .Use = Summon,
            .Description =
            {
                "Summons a Marine\n\CjPistol",
                "Summons a Marine\n\CjShotgun",
                "Summons a Marine\n\CjSuper Shotgun",
                "Summons a Marine\n\CjChaingun",
                "Summons a Marine\n\CjRocket Launcher",
                "Summons a Marine\n\CjPlasma Rifle",
                "Summons a Marine\n\CjBFG 9000"
            }
        },
        {
            .Name = "Summon Former Human",
            .Cost = 10,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Former Human"
            }
        },
        {
            .Name = "Summon Former Sergeant",
            .Cost = 50,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Former Sergeant"
            }
        },
        {
            .Name = "Summon Former Commando",
            .Cost = 100,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Former Commando"
            }
        },
        {
            .Name = "Summon Imp",
            .Cost = 75,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Imp"
            }
        },
        {
            .Name = "Summon Demon",
            .Cost = 75,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Demon"
            }
        },
        {
            .Name = "Summon Cacodemon",
            .Cost = 100,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Cacodemon"
            }
        },
        {
            .Name = "Summon Hell Knight",
            .Cost = 150,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Hell Knight"
            }
        },
        {
            .Name = "Summon Baron of Hell",
            .Cost = 200,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Baron of Hell"
            }
        },
        {
            .Name = "Summon Lost Soul",
            .Cost = 25,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Lost Soul"
            }
        },
        {
            .Name = "Summon Pain Elemental",
            .Cost = 250,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Pain Elemental"
            }
        },
        {
            .Name = "Summon Revenant",
            .Cost = 500,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Revenant"
            }
        },
        {
            .Name = "Summon Mancubus",
            .Cost = 500,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Mancubus"
            }
        },
        {
            .Name = "Summon Arachnotron",
            .Cost = 250,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Arachnotron"
            }
        },
        {
            .Name = "Summon Arch-Vile",
            .Cost = 750,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Arch-Vile"
            }
        },
        {
            .Name = "Summon Cyberdemon",
            .Cost = 1000,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Cyberdemon"
            }
        },
        {
            .Name = "Summon Spider Mastermind",
            .Cost = 1000,
            .MaxLevel = 1,
            .Use = Summon,
            .Description =
            {
                "Summons a Spider Mastermind"
            }
        }
    },
    
    // Utility
    {
        {
            .Name = "Breakdown Armor",
            .Cost = 250,
            .MaxLevel = 1,
            .Use = BreakdownArmor,
            .Description =
            {
                "Breaks down your current Armor into Credits"
            }
        },
        {
            .Name = "Force Wall",
            .Cost = 100,
            .MaxLevel = 1,
            .Use = ForceWall,
            .Description =
            {
                "Creates a wall of force in front of you which blocks hitscans, projectiles and monsters\nHealth is determined by your Energy"
            }
        },
        {
            .Name = "Rally",
            .Cost = 0,
            .MaxLevel = 1,
            .Use = Rally,
            .Description =
            {
                "Teleports your summoned monsters to you"
            }
        },
        {
            .Name = "Unsummon",
            .Cost = 0,
            .MaxLevel = 2,
            .Use = Unsummon,
            .Description =
            {
                "Banishes all of the friendly creatures under your control",
                "Banishes all of the friendly creatures under your control\nEach creature banished restores \Cn1% EP"
            }
        },
        {
            .Name = "Recall",
            .Cost = 25,
            .MaxLevel = 1,
            .Use = Recall,
            .Description =
            {
                "Brings you to the beginning of the level"
            }
        },
        {
            .Name = "Magnetize",
            .Cost = 100,
            .MaxLevel = 1,
            .Use = Magnetize,
            .Description =
            {
                "Pulls dropped items to you"
            }
        },
        {
            .Name = "Transport",
            .Cost = 0,
            .MaxLevel = 1,
            .Use = Transport,
            .Description =
            {
                "Brings you to the UAC Outpost\nUse in Outpost to return to current level"
            }
        }
    }
};

// Skill Wheel
NamedScript Type_ENTER void SkillWheel()
{
    bool Close = false;
    int Buttons;
    int OldButtons;
    int Radius = 128;
    int CurrentRadius = 0;
    int Cost = 0;
    int CurrentLevel = 0;
    int Level = 0;
    fixed LerpPos = 0;
    fixed Increment;
    fixed Location;
    fixed OldLocation;
    fixed Angle;
    fixed X;
    fixed Y;
    SkillPtr CurrentSkill;
    SkillLevelInfo *SkillLevel;
    
    Location = OldLocation = (Increment * (fixed)Player.WheelSelection);
    
    Start:
    
    // Check Input
    Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
    OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
    
    // Open the wheel
    if (Buttons & BT_USER1 && !((Player.InMenu && Player.Menu != 3) || Player.InShop || Player.OutpostMenu > 0 || Player.Turret.WheelOpen))
    {
        ActivatorSound("menu/click", 127);
        Player.SkillWheelOpen = true;
    }
    
    // Wheel Loop
    while (Player.SkillWheelOpen || CurrentRadius > 0)
    {
        SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
        
        // Check Input
        Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
        
        // Setup lerp location
        Increment = 1.0 / MAX_SKILLKEYS;
        Location = (Increment * (fixed)Player.WheelSelection);
        if (Location < 0.5 && OldLocation > 0.5 && OldLocation - Location > 0.5)
            OldLocation -= 1.0;
        else if (Location > 0.5 && OldLocation < 0.5 && Location - OldLocation > 0.5)
            OldLocation += 1.0;
        
        // Check for release
        if (!(Buttons & BT_USER1) && !(Buttons & BT_SPEED))
        {
            if (Player.WheelSelection != -1)
            {
                if (Player.InMenu && Player.Menu == 3)
                {
                    Player.SkillCategory[Player.WheelSelection] = Player.SkillPage;
                    Player.SkillIndex[Player.WheelSelection] = Player.MenuIndex;
                }
                else
                    Player.SkillSelected = Player.WheelSelection;
            }
            
            if (!Player.InMenu)
                SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
            
            Close = true;
        }
        
        // Animate Wheel
        if (Close)
        {
            CurrentRadius -= GetActivatorCVar("drpg_skill_wheelspeed");
            
            // Closed
            if (CurrentRadius <= 0)
            {
                Player.SkillWheelOpen = false;
                Close = false;
            }
        }
        else if (CurrentRadius < Radius)
            CurrentRadius += GetActivatorCVar("drpg_skill_wheelspeed");
        
        // Lerp position
        if (LerpPos <= 1.0)
            LerpPos += 0.1 * (fixed)GetActivatorCVar("drpg_skill_wheelspeed") / 16.0;
        if (LerpPos > 1.0)
            LerpPos = 1.0;
        
        // Input
        if (!Close)
        {
            if (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT))
            {
                ActivatorSound("menu/click", 127);
                Player.WheelSelection--;
                OldLocation = Location;
                LerpPos = 0;
                if (Player.WheelSelection < 0) Player.WheelSelection = MAX_SKILLKEYS - 1;
            }
            if (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT))
            {
                ActivatorSound("menu/click", 127);
                Player.WheelSelection++;
                OldLocation = Location;
                LerpPos = 0;
                if (Player.WheelSelection > MAX_SKILLKEYS - 1) Player.WheelSelection = 0;
            }
            if (Buttons & BT_SPEED && Player.SkillCategory[Player.WheelSelection] != -1 && Player.SkillIndex[Player.WheelSelection] != -1)
            {
                SkillLevel = &Player.SkillLevel[Player.SkillCategory[Player.WheelSelection]][Player.SkillIndex[Player.WheelSelection]];
                
                // Decrease selected skill level
                if (Buttons & BT_FORWARD && !(OldButtons & BT_FORWARD) && SkillLevel->CurrentLevel > 1)
                {
                    SkillLevel->CurrentLevel--;
                    AmbientSound("menu/move", 127);
                }
                
                // Increase selected skill level
                if (Buttons & BT_BACK && !(OldButtons & BT_BACK) && SkillLevel->CurrentLevel < SkillLevel->Level)
                {
                    SkillLevel->CurrentLevel++;
                    AmbientSound("menu/move", 127);
                }
                
                // Clear Skill
                if (Buttons & BT_USE)
                {
                    Player.SkillCategory[Player.WheelSelection] = -1;
                    Player.SkillIndex[Player.WheelSelection] = -1;
                    AmbientSound("menu/move", 127);
                }
            }
        }
        
        // Draw Wheel
        SetHudSize(640, 480, false);
        for (int i = 0; i < MAX_SKILLKEYS; i++)
        {
            Angle = 0.25 + Lerp(OldLocation, Location, LerpPos) - (Increment * i);
            X = 320.0 + CurrentRadius * Cos(Angle);
            Y = 240.0 + CurrentRadius * Sin(Angle);
            Level = Player.SkillLevel[Player.SkillCategory[i]][Player.SkillIndex[i]].Level;
            CurrentLevel = Player.SkillLevel[Player.SkillCategory[i]][Player.SkillIndex[i]].CurrentLevel;
            Cost = ScaleEPCost(Skills[Player.SkillCategory[i]][Player.SkillIndex[i]].Cost * CurrentLevel);
            
            // Slot Number, Cost, Levels
            SetFont("SMALLFONT");
            HudMessage("%d", i + 1);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", (int)(X + 18), (int)(Y - 18), 0.05);
            if (Player.SkillCategory[i] != -1 && Player.SkillIndex[i] != -1)
            {
                HudMessage("%d", Cost);
                EndHudMessage(HUDMSG_PLAIN, 0, (Level ? "Light Blue" : "Red"), (int)(X - 21) + 0.1, (int)(Y - 18), 0.05);
                HudMessage("%d/%d", CurrentLevel, Level);
                EndHudMessage(HUDMSG_PLAIN, 0, (Level > 0 ? "Green" : "Red"), (int)X, (int)(Y + 18), 0.05);
            }
            
            // Icon
            if (Player.SkillCategory[i] != -1 && Player.SkillIndex[i] != -1)
                PrintSprite(Skills[Player.SkillCategory[i]][Player.SkillIndex[i]].Icon, 0, (int)X, (int)Y, 0.05);
            else
                PrintSprite("SprNone", 0, (int)X, (int)Y, 0.05);
        }
        
        // Cursor
        PrintSprite("ItemBoxH", 0, 320, 240 + CurrentRadius, 0.05);
        
        // Name
        if (Player.SkillCategory[Player.WheelSelection] != -1 && Player.SkillIndex[Player.WheelSelection] != -1)
        {
            CurrentSkill = &SkillData[Player.SkillCategory[Player.WheelSelection]][Player.SkillIndex[Player.WheelSelection]];
            Level = Player.SkillLevel[Player.SkillCategory[Player.WheelSelection]][Player.SkillIndex[Player.WheelSelection]].Level;
            
            SetFont("BIGFONT");
            HudMessage("%S", CurrentSkill->Name);
            EndHudMessage(HUDMSG_PLAIN, 0, (Level > 0 ? "White" : "Red"), 320, 240 + CurrentRadius + 32, 0.05);
        }
        
        Delay(1);
    }
    
    // Update the Skill Wheel CVARS
    if (Player.FirstRun)
        for (int i = 0; i < MAX_SKILLKEYS; i++)
        {
            SetCVar(StrParam("drpg_skillwheel_category_%d", i + 1), Player.SkillCategory[i]);
            SetCVar(StrParam("drpg_skillwheel_index_%d", i + 1), Player.SkillIndex[i]);
        }
    
    Delay(1);
    goto Start;
}

NamedScript KeyBind void UseSkill(int Key)
{
    // Current Skill
    int Index = (Player.InMenu && Player.Menu == 3 ? -1 : Player.SkillSelected);
    SkillPtr CurrentSkill;
    SkillLevelInfo *SkillLevel;
    
    // Quick Use handling
    if (Key > 0)
    {
        CurrentSkill = &Skills[Player.SkillCategory[Key - 1]][Player.SkillIndex[Key - 1]];
        SkillLevel = &Player.SkillLevel[Player.SkillCategory[Key - 1]][Player.SkillIndex[Key - 1]];
    }
    else
    {
        CurrentSkill = &Skills[Player.SkillCategory[Index]][Player.SkillIndex[Index]];
        SkillLevel = &Player.SkillLevel[Player.SkillCategory[Index]][Player.SkillIndex[Index]];
    }
    
    // If you're dead, terminate
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    // If you have no current skill selected, terminate
    if (Player.SkillSelected == -1 && !Player.InMenu) return;
    
    // If the key is unassigned, terminate
    if (Index != -1)
        if (Player.SkillCategory[Index] == -1 || Player.SkillIndex[Index] == -1) return;
    
    // Using a skill will disturb your Focus
    Player.Focusing = false;
    
    // You can't use skills if you're Silenced
    if (Player.StatusType[SE_SILENCE]) return;
    
    // Quickuse
    if (Index == -1)
    {
        CurrentSkill = &Skills[Player.SkillPage][Player.MenuIndex];
        SkillLevel = &Player.SkillLevel[Player.SkillPage][Player.MenuIndex];
    }
    
    int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
    int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
    int EPCost = ScaleEPCost(CurrentSkill->Cost * SkillLevel->CurrentLevel);
    bool Success;
    
    // Overdrive?
    Player.Overdrive = false;
    if (Buttons & BT_SPEED && (!Player.InMenu && !Player.InShop))
        Player.Overdrive = true;
    
    // Overdriving an unlearnt skill will learn it
    if (Player.Overdrive && CheckInventory("DRPGModule") >= MODULE_SKILL_MULT && SkillLevel->Level == 0)
    {
        SkillLevel->Level++;
        SkillLevel->CurrentLevel++;
        TakeInventory("DRPGModule", MODULE_SKILL_MULT);
        FadeRange(0, 255, 255, 0.5, 0, 255, 255, 0.0, 0.5);
        ActivatorSound("health/epcapsule", 127);
        return;
    }
    
    // Check if the Skill has been learned yet
    if (SkillLevel->Level == 0)
    {
        SetFont("BIGFONT");
        PrintError("You don't know this skill yet");
        ActivatorSound("skills/fail", 127);
        return;
    }

    // Can't use skills while burned out
    if (Player.EP < 0)
    {
        SetFont("BIGFONT");
        PrintError("You can't use skills while burned out");
        ActivatorSound("skills/fail", 127);
        return;
    }
    
    // Use the Skill
    if (Player.EP >= EPCost || Player.Overdrive)
    {
        // Data to pass to the script pointer
        void *Data = NULL;
        auto int DataCategory = (Index == -1 ? Player.SkillPage : Player.SkillCategory[Player.SkillSelected]);
        auto int DataIndex = (Index == -1 ? Player.MenuIndex : Player.SkillIndex[Player.SkillSelected]);
        
        if (Key > 0)
        {
            DataCategory = Player.SkillCategory[Key - 1];
            DataIndex = Player.SkillIndex[Key - 1];
        }
        
        // Powerups, Auras and Summons need their index passed
        if (DataCategory == 1 || DataCategory == 2 || DataCategory == 4)
            Data = &DataIndex;
        
        // Debugging
        if (GetCVar("drpg_debug"))
        {
            Log("\CdDEBUG: \C-EP Cost for %S (\CdLevel %d\C-): \Cn%d", CurrentSkill->Name, SkillLevel->CurrentLevel, EPCost);
            Log("\CdDEBUG: \C-Data Category/Index: \Cd%d\C-, \Cd%d", DataCategory, DataIndex);
            Log("\CdDEBUG: \C-Skill Data passed: \Cd%d", *(int *)Data);
        }
        
        // PWAA-9001 Accessory Handling - Increase skill level intermittently
        if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_SKILLPLUS && Player.Shield.Active && SkillLevel->CurrentLevel < CurrentSkill->MaxLevel)
            SkillLevel->CurrentLevel++;
        
        // Use Skill
        Success = CurrentSkill->Use(SkillLevel, Data);
        
        // PWAA-9001 Accessory Handling - Change back to previous level
        if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_SKILLPLUS && Player.Shield.Active && SkillLevel->CurrentLevel < CurrentSkill->MaxLevel)
            SkillLevel->CurrentLevel--;
        
        // Check if the skill use was successful
        if (Success)
        {
            // Energy Stat XP for skill usage
            if (GetCVar("drpg_levelup_natural") && !Player.Stim.Active)
            {
                fixed Scale = GetCVarFixed("drpg_energy_scalexp");
                if (GetCVar("drpg_allow_spec"))
                {
                    if (GetActivatorCVar("drpg_character_spec") == 4)
                        Scale *= 2;
                }
                Player.EnergyXP += (int)(EPCost * 10 * Scale);
            }
            
            // EFF-C13 Shield Accessory
            if (!Player.Shield.Accessory || Player.Shield.Accessory->PassiveEffect != SHIELD_PASS_MORESKILLS || Random(1, 4) == 1)
                Player.EP -= EPCost;
            
            // TUFF-MAG3 Shield Accessory
            if (Player.Shield.Active && Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_SKILLTOSHIELD)
                Player.Shield.Charge += EPCost / 10;
            
            // Blue Aura Refund
            if (Player.SkillRefundMult > 0)
                Player.EP += EPCost * Player.SkillRefundMult;
        }
    }
    else // Not enough EP
    {
        SetFont("BIGFONT");
        PrintError("Not enough EP to use this skill!");
        ActivatorSound("skills/fail", 127);
    }
}

NamedScript Console bool Heal(SkillLevelInfo *SkillLevel, void *Data)
{
    int PlayerTID = Player.TID;
    bool Team = (SkillLevel->CurrentLevel >= 3);
    
    // Refund - If your health is max or above at levels lower than 3 or you don't have a status effect
    if ((SkillLevel->CurrentLevel < 3 && Player.ActualHealth >= Player.HealthMax) && !HaveStatusEffect())
    {
        PrintError("You are already at max health");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Healing
    if (Team)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (!PlayerInGame(i)) continue;
            
            SetActivator(Players(i).TID);
            
            if (SkillLevel->CurrentLevel >= 4)
            {
                AddHealth(200, 200);
                Players(i).OverHeal = true;
            }
            else
                AddHealth(100, 100);
        }
        
        SetActivator(PlayerTID);
    }
    else
    {
        if (SkillLevel->CurrentLevel >= 4)
        {
            AddHealth(200, 200);
            Player.OverHeal = true;
        }
        else
            AddHealth(100, 100);
    }
    
    // Remove Status Effects
    if (SkillLevel->CurrentLevel >= 2)
    {
        if (Team)
        {
            for (int i = 0; i < MAX_PLAYERS; i++)
            {
                if (!PlayerInGame(i)) continue;
                
                SetActivator(Players(i).TID);
                
                ClearStatusEffects();
            }
            
            SetActivator(PlayerTID);
        }
        else
            ClearStatusEffects();
    }
    
    if (Team)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (!PlayerInGame(i)) continue;
            
            SetActivator(Players(i).TID);
            
            FadeRange(255, 0, 255, 0.5, 255, 0, 255, 0, 1.0);
            ActivatorSound("skills/heal", (Players(i).TID == PlayerTID ? 127 : 64));
        }
        
        SetActivator(PlayerTID);
    }
    else
    {
        FadeRange(255, 0, 255, 0.5, 255, 0, 255, 0, 1.0);
        ActivatorSound("skills/heal", 127);
    }
    
    return true;
}

NamedScript Console bool HealSummons(SkillLevelInfo *SkillLevel, void *Data)
{
    // Refund - If you have no summoned monsters
    if (Player.Summons == 0)
    {
        PrintError("You have no summoned friendlies");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    FadeRange(255, 0, 255, 0.5, 255, 0, 255, 0, 1.0);
    
    for (int i = 0; i < MAX_SUMMONS; i++)
        if (Player.SummonTID[i] > 0)
        {
            MonsterStatsPtr Stats = &Monsters[GetMonsterID(Player.SummonTID[i])];
            SetActorProperty(Player.SummonTID[i], APROP_Health, Stats->HealthMax);
        }
    
    ActivatorSound("skills/heal2", 127);
    
    return true;
}

NamedScript Console bool Decontaminate(SkillLevelInfo *SkillLevel, void *Data)
{
    if (Player.Toxicity <= 0)
    {
        PrintError("You have no toxicity");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    Player.Toxicity = 0;
    ClearToxicityMeter();
    
    ActivatorSound("skills/decontaminate", 127);
    FadeRange(0, 255, 0, 0.5, 0, 255, 0, 0.0, 1.0);
    
    Player.SkillCostMult += 25;
    
    return true;
}

NamedScript Console bool Repair(SkillLevelInfo *SkillLevel, void *Data)
{
    if (CheckInventory("Armor") == 0 || CheckInventory("Armor") >= GetArmorInfo(ARMORINFO_SAVEAMOUNT))
    {
        PrintError("You aren't wearing any armor");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    FadeRange(0, 255, 0, 0.5, 0, 255, 0, 0, 1.0);
    GiveInventory(GetArmorInfoString(ARMORINFO_CLASSNAME), 1);
    
    ActivatorSound("skills/repair", 127);
    
    return true;
}

NamedScript Console bool Powerup(SkillLevelInfo *SkillLevel, void *Data)
{
    int Index = *(int *)Data;
    
    switch (Index)
    {
    case 0: // Invulnerability
        if (Player.SkillPowerupCooldown > 0)
        {
            PrintError(StrParam("You must wait %S before using Invulnerability", FormatTime(Player.SkillPowerupCooldown)));
            ActivatorSound("menu/error", 127);
            return false;
        };
        ActivatorSound("powerups/protect", 127);
        GiveInventory(StrParam("DRPGSkillInvulnerability%d", SkillLevel->CurrentLevel), 1);
        Player.SkillPowerupCooldown = 35 * 60 * (SkillLevel->CurrentLevel > 1 ? 5 : 10);
        break;
    case 1: // Invisibility
        ActivatorSound("powerups/invis", 127);
        GiveInventory(StrParam("DRPGSkillInvisibility%d", SkillLevel->CurrentLevel), 1);
        break;
    case 3: // Iron Feet
        ActivatorSound("powerups/suit", 127);
        GiveInventory("DRPGSkillIronFeet", 1);
        break;
    case 4: // Night Vision
        ActivatorSound("powerups/light", 127);
        GiveInventory("DRPGSkillLightAmp", 1);
        break;
    case 5: // Berserk
        ActivatorSound("powerups/berserk", 127);
        GiveInventory("PowerStrength", 1);
        break;
    case 6: // Mental Mapping
        ActivatorSound("powerups/map", 127);
        GiveInventory("DRPGAllMapRevealer", 1);
        GiveInventory("DRPGAllMapScanner", 1);
        break;
    }
    
    return true;
}

NamedScript Console bool BulletTime(SkillLevelInfo *SkillLevel, void *Data)
{
    if (Player.SkillPowerupCooldown > 0)
    {
        PrintError(StrParam("You must wait %S before using Time Freeze", FormatTime(Player.SkillPowerupCooldown)));
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    if (SkillLevel->CurrentLevel == 1) // Stutter Time
    {
        BulletTimeTimer = 350;
        SpawnForced("DRPGTimeFreezerQuickSound", GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
        TakeInventory("PowerTimeFreezer", 1);
        GiveInventory("DRPGTimeFreezerQuick", 1);
        Player.SkillPowerupCooldown = 35 * 60 * 5;
    }
    if (SkillLevel->CurrentLevel == 2) // Freeze Time
    {
        SpawnForced("DRPGTimeFreezerSound", GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
        GiveInventory("DRPGTimeFreezer", 1);
        Player.SkillPowerupCooldown = 35 * 60 * 10;
    }
    
    return true;
}

NamedScript Console bool DropWeapon(SkillLevelInfo *SkillLevel, void *Data)
{
    fixed Angle = GetActorAngle(0);
    fixed X = GetActorX(0) + Cos(Angle) * 96.0;
    fixed Y = GetActorY(0) + Sin(Angle) * 96.0;
    fixed Z = GetActorZ(0) + 48.0;
    str Weapon;
    
    switch (SkillLevel->CurrentLevel)
    {
    case 1: Weapon = "Pistol";          break;
    case 2: Weapon = "Shotgun";         break;
    case 3: Weapon = "SuperShotgun";    break;
    case 4: Weapon = "Chaingun";        break;
    case 5: Weapon = "RocketLauncher";  break;
    case 6: Weapon = "PlasmaRifle";     break;
    case 7: Weapon = "BFG9000";         break;
    }
    
    if (Spawn(Weapon, X, Y, Z, 0, Angle))
    {
        ActivatorSound("skills/drop", 127);
        Spawn("TeleportFog", X, Y, Z, 0, Angle);
        return true;
    }
    else
    {
        PrintError("You cannot drop weapons here");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    return false;
}

NamedScript Console bool DropSupply(SkillLevelInfo *SkillLevel, void *Data)
{
    fixed Angle = GetActorAngle(0);
    fixed X = GetActorX(0) + Cos(Angle) * 96.0;
    fixed Y = GetActorY(0) + Sin(Angle) * 96.0;
    fixed Z = GetActorZ(0) + 48.0;
    bool Spawned = false;
    
    if (SkillLevel->CurrentLevel > 1 && Player.SkillSupplyCooldown > 0)
    {
        PrintError(StrParam("You must wait %S before calling in new supplies", FormatTime(Player.SkillSupplyCooldown)));
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    if (SkillLevel->CurrentLevel > 1)
        Spawned = Spawn("DRPGCrate", X, Y, Z, 0, Angle);
    else
        Spawned = Spawn("DRPGBigBackpack", X, Y, Z, 0, Angle);
    
    if (Spawned)
    {
        // Set Crate's rarity level based on skill level
        if (SkillLevel->CurrentLevel > 1)
        {
            // Cooldown timer
            Player.SkillSupplyCooldown = 35 * 60 * 5;
            
            Delay(1);
            Crates[CrateID - 1].SupplyDrop = true;
            Crates[CrateID - 1].Rarity = SkillLevel->CurrentLevel - 2;
        }
        
        ActivatorSound("skills/drop", 127);
        Spawn("TeleportFog", X, Y, Z, 0, Angle);
        return true;
    }
    else
    {
        PrintError("A supply drop cannot be performed at your current location");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    return false;
}

NamedScript Console bool UseAura(SkillLevelInfo *SkillLevel, void *Data)
{
    int Index = *(int *)Data;
    bool Stack = false;
    
    // Is the Aura you used the same as the one you already have active?
    if (Player.Aura.Type[Index].Active)
        Stack = true;
    
    if (!Stack)
    {
        // Aura stacking handling with Energy perk
        if (Player.Perks[STAT_ENERGY])
        {
            int StackMax = 1 + ((Player.Energy - 100) / 10);
            int Auras = 0;
            
            Log("\CnAura Max Stack: %d", StackMax);
            
            // Count the current Auras
            for (int i = 0; i < AURA_MAX; i++)
                if (Player.Aura.Type[i].Active)
                    Auras++;
            
            // Make sure the proper Aura stack is maintained
            while (Auras >= StackMax)
            {
                for (int i = 0; i < AURA_MAX; i++)
                {
                    // Variance
                    if (Random(1, 2) == 1) continue;
                    
                    if (Player.Aura.Type[i].Active)
                    {
                        Player.Aura.Type[i].Active = false;
                        Auras--;
                        break;
                    }
                }
                
                if ((Timer() % 5) == 0)
                    Delay(1);
            }
        }
        else // Remove all other Auras first if you don't have the Energy
            for (int i = 0; i < AURA_MAX; i++)
                Player.Aura.Type[i].Active = false;
    }
    
    // Should the timer be stacked because you used the same Aura?
    if (Stack || Player.Perks[STAT_ENERGY])
        Player.Aura.Time += AURA_CALCTIME;
    else
        Player.Aura.Time = AURA_CALCTIME;
    
    // Apply Aura
    Player.Aura.Type[Index].Active = true;
    Player.Aura.Type[Index].Level = SkillLevel->CurrentLevel;
    
    // Aura Cost Multiplier
    Player.SkillCostMult += 10;
    
    ActivatorSound("skills/buff", 127);
    return true;
}

NamedScript Console bool Weaken(SkillLevelInfo *SkillLevel, void *Data)
{
    int PlayerNum = PlayerNumber();
    int StatDivide;
    
    SetActivatorToTargetExtended(Players(PlayerNum).TID);
    
    // Pointer
    MonsterStatsPtr Stats = &Monsters[GetMonsterID(0)];
    
    // Refund - If the Player has no target
    if (ActivatorTID() == Players(PlayerNum).TID)
    {
        PrintError("You have no target");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Refund - If the target isn't actually a valid monster
    if (!Stats->Init || !(ClassifyActor(0) & ACTOR_MONSTER))
    {
        PrintError("Target is not a valid enemy");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target is immune to Weaken
    if (Stats->Flags & MF_NOWEAKEN)
    {
        PrintError("Target is immune to weakening");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Determine stat division
    // TODO: formula-ify this?
    switch (SkillLevel->CurrentLevel)
    {
    case 1:         StatDivide = 16;    break;
    case 2:         StatDivide = 8;     break;
    case 3:         StatDivide = 4;     break;
    case 4: case 5: StatDivide = 2;     break;
    }
    
    // Bosses will double the divider
    if (Stats->Flags & MF_BOSS)
        StatDivide *= 2;
    
    // MegaBosses will quadruple the divider
    if (Stats->Flags & MF_MEGABOSS)
        StatDivide *= 4;
    
    // Halve the monster's level and stats
    Stats->Level -= (Stats->Level / StatDivide);
    Stats->Strength -= (Stats->Strength / StatDivide);
    Stats->Defense -= (Stats->Defense / StatDivide);
    Stats->Vitality -= (Stats->Vitality / StatDivide);
    Stats->Energy -= (Stats->Energy / StatDivide);
    Stats->Regeneration -= (Stats->Regeneration / StatDivide);
    Stats->Agility -= (Stats->Agility / StatDivide);
    Stats->Capacity -= (Stats->Capacity / StatDivide);
    Stats->Luck -= (Stats->Luck / StatDivide);
    
    // Destroy Aura
    if (SkillLevel->CurrentLevel >= 5)
        RemoveMonsterAura(Stats);
    
    // Cap Level
    if (Stats->Level < 1)
        Stats->Level = 1;
    
    // Re-calculate the monster's threat level
    Stats->Threat = CalculateMonsterThreatLevel(0);
    
    // Red Aura retaliates! (if it still can)
    SetInventory("DRPGMonsterEPAttacked", 1);
    
    // Reset Activator
    SetActivator(Players(PlayerNum).TID);
    
    FadeRange(0, 0, 0, 0.25, 0, 0, 0, 0.0, 1.0);
    ActivatorSound("skills/weaken", 127);
    return true;
}

NamedScript Console bool Translocate(SkillLevelInfo *SkillLevel, void *Data)
{
    if (CurrentLevel->UACBase)
    {
        PrintError("Cannot translocate here");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    FireProjectile("DRPGTranslocateBall");
    return true;
}

NamedScript Console bool Repulse(SkillLevelInfo *SkillLevel, void *Data)
{
    SetInventory(StrParam("DRPGSkillBlast%d", SkillLevel->CurrentLevel), 1);
    UseInventory(StrParam("DRPGSkillBlast%d", SkillLevel->CurrentLevel));
    
    FadeRange(255, 255, 0, 0.1, 255, 255, 0, 0.0, 0.5 + (0.25 * SkillLevel->CurrentLevel));
    
    return true;
}

NamedScript Console bool AuraSteal(SkillLevelInfo *SkillLevel, void *Data)
{
    int PlayerNum = PlayerNumber();
    
    SetActivatorToTargetExtended(Players(PlayerNum).TID);
    
    // Pointer
    MonsterStatsPtr Stats = &Monsters[GetMonsterID(0)];
    
    // Refund - If the Player has no target
    if (ActivatorTID() == Players(PlayerNum).TID)
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("You have no target");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Refund - If the target isn't actually a valid monster
    if (!Stats->Init || !(ClassifyActor(0) & ACTOR_MONSTER))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target is not a valid enemy");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target doesn't have an Aura
    if (!MonsterHasAura(Stats))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target does not have any auras");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If you already have an Aura
    if (PlayerHasAura(PlayerNum))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("You already have an active aura");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target has a shadow Aura
    if (MonsterHasShadowAura(Stats))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target's auras are too strong");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    for (int i = 0; i < AURA_MAX; i++)
        if (Stats->Aura.Type[i].Active)
        {
            // Transfer
            Players(PlayerNum).Aura.Type[i].Active = true;
            
            // Determine Level
            int Level = Players(PlayerNum).Energy / 25 + 1;
            if (Level > Skills[2][i].MaxLevel)
                Level = Skills[2][i].MaxLevel;
            Players(PlayerNum).Aura.Type[i].Level = Level;
        }
    
    // Add Time
    Players(PlayerNum).Aura.Time += Stats->Aura.Time;
    
    // Remove from enemy
    RemoveMonsterAura(Stats);
    
    ActivatorSound("skills/aurasteal", 127);
    return true;
}

NamedScript Console bool SoulSteal(SkillLevelInfo *SkillLevel, void *Data)
{
    str const SoulTypes[SOUL_MAX] =
    {
        "DRPGSoulRed",
        "DRPGSoulGreen",
        "DRPGSoulWhite",
        "DRPGSoulPink",
        "DRPGSoulBlue",
        "DRPGSoulPurple",
        "DRPGSoulOrange",
        "DRPGSoulDarkBlue",
        "DRPGSoulYellow"
    };
    
    str const SoulTypesStat[SOUL_MAX] =
    {
        "DRPGSoulRed",
        "DRPGSoulGreen",
        "DRPGSoulPink",
        "DRPGSoulBlue",
        "DRPGSoulPurple",
        "DRPGSoulOrange",
        "DRPGSoulDarkBlue",
        "DRPGSoulYellow"
    };
    
    int PlayerNum = PlayerNumber();
    int UniqueMonsterTID = UniqueTID();
    int RealMonsterTID;
    
    // Refund - If the Player has no target
    if (!SetActivatorToTargetExtended(Players(PlayerNum).TID))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("You have no target");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Pointer
    MonsterStatsPtr Stats = &Monsters[GetMonsterID(0)];
    
    // Refund - If the target is too far away
    if (Distance(0, Players(PlayerNum).TID) > 1024.0)
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target is too far away");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target isn't actually a valid monster
    if (!Stats->Init || !(ClassifyActor(0) & ACTOR_MONSTER))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target is not a valid enemy");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target is a boss or can never have an aura to begin with
    if (Stats->Flags & MF_BOSS || Stats->Flags & MF_NOAURA || Stats->Flags & MF_MEGABOSS || CheckFlag(0, "BOSS"))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target's soul is too strong");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target is not weak enough (Below 25% Health)
    if (CalcPercent(GetActorProperty(0, APROP_Health), Stats->HealthMax) > 25)
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target is not weak enough");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Don't gain XP from this
    Stats->Flags |= MF_NOXP;
    
    // Temporary changing of TID to handle missions properly
    RealMonsterTID = ActivatorTID();
    Thing_ChangeTID(0, UniqueMonsterTID);
    
    int LeechAmount = GetActorProperty(0, APROP_Health);
    
    // Kill it
    SetActivator(Players(PlayerNum).TID);
    SetActorProperty(UniqueMonsterTID, APROP_Health, 0);
    SetActivator(UniqueMonsterTID);

    // Drop the Soul
    if (MonsterHasAura(Stats))
    {
        for (int i = 0; i < AURA_MAX; i++)
            if (Stats->Aura.Type[i].Active)
                DropMonsterItem(PlayerNum, 0, SoulTypes[i], 256);
    }
    else
        DropMonsterItem(PlayerNum, 0, SoulTypesStat[BestStat(Stats)], 256);
    
    // Move activation back to the user
    SetActivator(Players(PlayerNum).TID);
    
    // Reset the temporary TID
    Thing_ChangeTID(UniqueMonsterTID, RealMonsterTID);
    
    // Heal the user
    AddHealthDirect(LeechAmount, 100);
    
    FadeRange(0, 0, 0, 0.5, 0, 0, 0, 0.0, 0.25);
    ActivatorSound("skills/soulsteal", 127);
    return true;
}

NamedScript Console bool Disruption(SkillLevelInfo *SkillLevel, void *Data)
{
    int PlayerNum = PlayerNumber();
    int UniqueMonsterTID = UniqueTID();
    int RealMonsterTID;
    int BeforeHealthAmount;
    int AfterHealthAmount;
    bool AllowsXP;
    
    if (SkillLevel->CurrentLevel >= 4)
    {
        if (SkillLevel->CurrentLevel == 5)
            GiveInventory("DRPGAreaDisruptionLarge", 1);
        else
            GiveInventory("DRPGAreaDisruptionSmall", 1);

        FadeRange(0, 64, 255, 0.5, 0, 64, 255, 0.0, 0.25);
        ActivatorSound("skills/disruption", 127);
        
        return true;
    }
    
    // Move activation to the user's target
    if (!SetActivatorToTargetExtended(Players(PlayerNum).TID))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("You have no target");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Pointer
    MonsterStatsPtr Stats = &Monsters[GetMonsterID(0)];
    
    // Refund - If the target isn't actually a valid monster
    if (!Stats->Init || !(ClassifyActor(0) & ACTOR_MONSTER))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target is not a valid enemy");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    // Refund - If the target can't be disrupted (eg. has no aura)
    if (!MonsterHasAura(Stats) || (MonsterHasShadowAura(Stats) && SkillLevel->CurrentLevel < 2))
    {
        SetActivator(Players(PlayerNum).TID);
        PrintError("Target cannot be disrupted");
        ThingSound(Players(PlayerNum).TID, "menu/error", 127);
        return false;
    }
    
    if (SkillLevel->CurrentLevel == 3)
    {
        // Drop stolen ammo
        if (Stats->Aura.Type[AURA_DARKBLUE].Active)
        {
            while (CheckInventory("Clip") >= 10)
            {
                DropMonsterItem(PlayerNum, 0, "DRPGStolenClip", 256);
                TakeInventory("Clip", 10);
            }
            while (CheckInventory("Shell") >= 4)
            {
                DropMonsterItem(PlayerNum, 0, "DRPGStolenShell", 256);
                TakeInventory("Shell", 4);
            }
            while (CheckInventory("RocketAmmo") >= 1)
            {
                DropMonsterItem(PlayerNum, 0, "DRPGStolenRocketAmmo", 256);
                TakeInventory("RocketAmmo", 1);
            }
            while (CheckInventory("Cell") >= 20)
            {
                DropMonsterItem(PlayerNum, 0, "DRPGStolenCell", 256);
                TakeInventory("Cell", 20);
            }
        }
        
        // Drop stolen credits
        int StolenCredits = CheckInventory("DRPGCredits") - Stats->Capacity;
        if (Stats->Aura.Type[AURA_YELLOW].Active && StolenCredits > 0)
        {
            DropMoney(PlayerNum, 0, StolenCredits);
            TakeInventory("DRPGCredits", StolenCredits);
        }
    }
    
    SetInventory("DRPGMonsterDisrupted", 35 * 30);
    
    // Move activation back to the user
    SetActivator(Players(PlayerNum).TID);
    
    // Reset the temporary TID
    Thing_ChangeTID(UniqueMonsterTID, RealMonsterTID);
    
    FadeRange(0, 64, 255, 0.5, 0, 64, 255, 0.0, 0.25);
    ActivatorSound("skills/disruption", 127);
    return true;
}

NamedScript Console bool PlasmaBeam(SkillLevelInfo *SkillLevel, void *Data)
{
    switch (SkillLevel->CurrentLevel)
    {
    case 1:
    default:
        PlasmaBeam1();
        break;
    case 2:
        PlasmaBeam2();
        break;
    case 3:
        PlasmaBeam3();
        break;
    }
    
    return true;
}

NamedScript Console void PlasmaBeam1()
{
    int BeamTime = 35;
    
    ActivatorSound("skills/plasmabeam1", 127);
    
    while (BeamTime--)
    {
        GiveInventory("DRPGSkillPlasmaBeam1", 1);
        Delay(1);
    }
}

NamedScript Console void PlasmaBeam2()
{
    int BeamTime = 35;
    
    ActivatorSound("skills/plasmabeam1", 63);
    ActivatorSound("skills/plasmabeam2", 64);
    
    while (BeamTime--)
    {
        GiveInventory("DRPGSkillPlasmaBeam2", 1);
        Delay(1);
    }
}

NamedScript Console void PlasmaBeam3()
{
    int BeamTime = 35;
    
    ActivatorSound("skills/plasmabeam3", 127);
    
    while (BeamTime--)
    {
        GiveInventory("DRPGSkillPlasmaBeam3", 1);
        Delay(1);
    }
}

NamedScript Console bool Summon(SkillLevelInfo *SkillLevel, void *Data)
{
    int Index = *(int *)Data;
    fixed Angle = GetActorAngle(0);
    fixed X = GetActorX(0);
    fixed Y = GetActorY(0);
    fixed Z = GetActorZ(0);
    int NewID = UniqueTID();
    bool Success;
    fixed Radius;
    str Name;
    
    str const Summons[] =
    {
        "ZombieMan",
        "ShotgunGuy",
        "ChaingunGuy",
        "DoomImp",
        "Demon",
        "Cacodemon",
        "HellKnight",
        "BaronOfHell",
        "LostSoul",
        "PainElemental",
        "Revenant",
        "Fatso",
        "Arachnotron",
        "Archvile",
        "Cyberdemon",
        "SpiderMastermind"
    };
    
    str const DRLASummons[][6] =
    {
        // Former Human
        {
            "RLDRPGSummonedFormerHuman",
            "RLDRPGSummonedEliteHuman",
            "RLDRPGSummonedFormerCaptain"
        },
        
        // Former Sergeant
        {
            "RLDRPGSummonedFormerSergeant",
            "RLDRPGSummonedEliteSergeant"
        },
        
        // Former Commando
        {
            "RLDRPGSummonedFormerCommando",
            "RLDRPGSummonedEliteCommando",
            "RLDRPGSummonedEliteCaptain2"
        },
        
        // Imp
        {
            "RLDRPGSummonedImp",
            "RLDRPGSummonedNightmareImp",
            "RLDRPGSummonedCyberneticImp"
        },
        
        // Demon
        {
            "RLDRPGSummonedDemon",
            "RLDRPGSummonedSpectre",
            "RLDRPGSummonedNightmareDemon",
            "RLDRPGSummonedNightmareSpectre",
            "RLDRPGSummonedCyberneticDemon",
            "RLDRPGSummonedCyberneticSpectre"
        },
        
        // Cacodemon
        {
            "RLDRPGSummonedCacodemon",
            "RLDRPGSummonedNightmareCacodemon"
        },
        
        // Hell Knight
        {
            "RLDRPGSummonedHellKnight",
            "RLDRPGSummonedNightmareHellKnight",
            "RLDRPGSummonedCyberneticHellKnight"
        },
        
        // Baron of Hell
        {
            "RLDRPGSummonedBaronOfHell",
            "RLDRPGSummonedNightmareBaronOfHell",
            "RLDRPGSummonedCyberneticBaronOfHell"
        },
        
        // Lost Soul
        {
            "RLDRPGSummonedLostSoul",
            "RLDRPGSummonedNightmareLostSoul",
            "RLDRPGSummonedCyberneticLostSoul"
        },
        
        // Pain Elemental
        {
            "RLDRPGSummonedPainElemental",
            "RLDRPGSummonedNightmarePainElemental"
        },
        
        // Revenant
        {
            "RLDRPGSummonedRevenant",
            "RLDRPGSummonedNightmareRevenant",
            "RLDRPGSummonedCyberneticRevenant"
        },
        
        // Mancubus
        {
            "RLDRPGSummonedMancubus",
            "RLDRPGSummonedNightmareMancubus",
            "RLDRPGSummonedCyberneticMancubus"
        },
        
        // Arachnotron
        {
            "RLDRPGSummonedArachnotron",
            "RLDRPGSummonedNightmareArachnotron",
            "RLDRPGSummonedCyberneticArachnotron"
        },
        
        // Arch-Vile
        {
            "RLDRPGSummonedArchVile",
            "RLDRPGSummonedNightmareArchVile"
        },
        
        // Cyberdemon
        {
            "RLDRPGSummonedCyberdemon",
            "RLDRPGSummonedNightmareCyberdemon"
        },
        
        // Spider Mastermind
        {
            "RLDRPGSummonedSpiderMastermind",
            "RLDRPGSummonedCyberneticSpiderMastermind"
        }
    };
    
    // Stop if you're in the Outpost
    if (CurrentLevel->UACBase)
    {
        PrintError("You cannot summon friendlies here");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Stop if you already have the maximum amount of summons
    if (Player.Summons >= MAX_SUMMONS)
    {
        PrintError("You cannot summon any more friendlies");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    if (Index == 0) // Marines
    {
        switch (SkillLevel->CurrentLevel)
        {
        case 1: Name = "DRPGMarineGuardPistolSummoned";    break;
        case 2: Name = "DRPGMarineShotgunSummoned";        break;
        case 3: Name = "DRPGMarineDoubleShotgunSummoned";  break;
        case 4: Name = "DRPGMarineChaingunSummoned";;      break;
        case 5: Name = "DRPGMarineRocketLauncherSummoned"; break;
        case 6: Name = "DRPGMarinePlasmaRifleSummoned";    break;
        case 7: Name = "DRPGMarineBFG9000Summoned";        break;
        };
    }
    else // Monsters
    {
        if (CompatMode == COMPAT_DRLA)
            Name = DRLASummons[Index - 1][SkillLevel->CurrentLevel - 1];
        else if (CompatMode == COMPAT_EXTRAS)
            Name = StrParam("DRPG%SExtras", Summons[Index - 1]);
        else
            Name = StrParam("DRPG%S", Summons[Index - 1]);
    }
    
    // Perform a dummy summon to get the Radius and add it to X and Y
    SpawnForced(Name, 0, 0, 0, NewID, 0);
    Radius = GetActorPropertyFixed(NewID, APROP_Radius);
    X += Cos(Angle) * (Radius * 1.5 + 16.0);
    Y += Sin(Angle) * (Radius * 1.5 + 16.0);
    Thing_Remove(NewID);
    
    // With the new radius, try and summon the actual monster
    Success = Spawn(Name, X, Y, Z, NewID, Angle);
    
    if (Success)
    {
        SpawnForced("TeleportFog", X, Y, Z, 0, Angle);
        SetActorAngle(NewID, Angle);
        SetActorProperty(NewID, APROP_Friendly, true);
        SetActorProperty(NewID, APROP_MasterTID, Player.TID);
        SetActorPropertyString(NewID, APROP_Species, "Player");
        GiveActorInventory(NewID, "DRPGFriendlyBooster", 1);
        if (Index != 0) // Marines need to run their Spawn state
            SetActorState(NewID, "See");
        
        // Add summon to your summon array
        for (int i = 0; i < MAX_SUMMONS; i++)
            if (Player.SummonTID[i] == 0)
            {
                Player.SummonTID[i] = NewID;
                Player.Summons++;
                break;
            }
        
        // Setup Stats
        Delay(4); // We need this initial delay to make sure the ID is valid
        MonsterStatsPtr Stats = &Monsters[GetMonsterID(NewID)];
        fixed Modifier = 1.0 + (fixed)Player.Level * ((fixed)Player.Energy / 20.0);
        Stats->Level = (int)Modifier;
        Stats->Strength = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Defense = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Vitality = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Energy = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Regeneration = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Agility = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Capacity = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Luck = (int)Modifier + Random(0, Stats->Level / GameSkill());
        Stats->Threat = CalculateMonsterThreatLevel(&Monsters[GetMonsterID(NewID)]);
        Stats->Flags |= MF_NOXP;
        Stats->Flags |= MF_NODROPS;
        Stats->NeedReinit = true;
        
        return true;
    }
    else
    {
        PrintError("You cannot summon a friendly here");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    return false;
}

NamedScript Console bool BreakdownArmor(SkillLevelInfo *SkillLevel, void *Data)
{
    int Armor = CheckInventory("BasicArmor");
    
    // Kind of hackish to prevent breaking down Armors that use high values for indestructibleness
    if (CompatMode == COMPAT_DRLA && Armor >= 99999)
    {
        PrintError("You cannot breakdown indestructible armors");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    if (Armor > 0)
    {
        // DoomRL Compatibility
        if (CompatMode == COMPAT_DRLA)
        {
            RemoveDRLAArmorToken(GetArmorInfoString(ARMORINFO_CLASSNAME));
            TakeInventory("RL100ArmorWorn", 1);
            TakeInventory("RL150ArmorWorn", 1);
            TakeInventory("RL200ArmorWorn", 1);
            TakeInventory("RL100RegenArmorWorn", 1);
            TakeInventory("RLIndestructibleArmorWorn", 1);
        }
        
        TakeInventory("BasicArmor", Armor);
        GiveInventory("DRPGCredits", Armor);
        
        ActivatorSound("skills/breakdown", 127);
        return true;
    }
    else
    {
        PrintError("You're not wearing any armor");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    return false;
}

NamedScript Console bool ForceWall(SkillLevelInfo *SkillLevel, void *Data)
{
    int TID = UniqueTID();
    fixed Angle = GetActorAngle(0);
    fixed X = GetActorX(0) + Cos(Angle) * 96.0;
    fixed Y = GetActorY(0) + Sin(Angle) * 96.0;
    fixed Z = GetActorZ(0);
    
    if (Spawn("DRPGForceWall", X, Y, Z, TID, Angle))
    {
        Delay(4);
        
        MonsterStatsPtr Stats = &Monsters[GetMonsterID(TID)];
        
        // Determine Defense and Health
        Stats->SpawnHealth = GetActorProperty(0, APROP_SpawnHealth);
        Stats->Defense = Player.Energy * 5;
        Stats->Vitality = Player.Energy * 5;
        Stats->HealthMax = CalculateMonsterMaxHealth(Stats);
        SetActorProperty(TID, APROP_Health, Stats->HealthMax);
        
        return true;
    }
    else
    {
        PrintError("Cannot place a force wall here");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    return false;
}

NamedScript Console bool Rally(SkillLevelInfo *SkillLevel, void *Data)
{
    fixed X = GetActorX(0);
    fixed Y = GetActorY(0);
    fixed Z = GetActorZ(0);
    fixed Angle = GetActorAngle(0);
    
    // Fail if you have no summons active
    if (Player.Summons == 0)
    {
        PrintError("You have no summoned friendlies");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    SpawnForced("TeleportFog", X, Y, Z, 0, Angle);
    
    for (int i = 0; i < MAX_SUMMONS; i++)
        if (Player.SummonTID[i] > 0)
            SetActorPosition(Player.SummonTID[i], X, Y, Z, 0);
    
    ActivatorSound("skills/rally", 127);
    return true;
}

NamedScript Console bool Unsummon(SkillLevelInfo *SkillLevel, void *Data)
{
    int EPAdd;
    
    // Fail if you have no summons active
    if (Player.Summons == 0)
    {
        PrintError("You have no summoned friendlies");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    for (int i = 0; i < MAX_SUMMONS; i++)
    {
        // Continue if there's no summon in this slot
        if (Player.SummonTID[i] == 0) continue;
        
        if (SkillLevel->CurrentLevel == 2 && GetActorProperty(Player.SummonTID[i], APROP_Health) > 0)
            EPAdd += (int)((fixed)Player.EPMax * 0.01) + 1;
        
        // Player.Overdrive - Remove summons (teleport out) instead of killing them
        if (GetActorProperty(Player.SummonTID[i], APROP_Health) > 0)
        {
            SpawnForced("TeleportFog", GetActorX(Player.SummonTID[i]), GetActorY(Player.SummonTID[i]), GetActorZ(Player.SummonTID[i]), 0, 0);
            Thing_Remove(Player.SummonTID[i]);
        }
        
        // Remove the summon from the array
        Player.SummonTID[i] = 0;
    }
    
    
    Log("EPAdd: %d", EPAdd);
    if (SkillLevel->CurrentLevel == 2)
        Player.EP += EPAdd;

    Player.Summons = 0;
    
    FadeRange(192, 0, 0, 0.5, 192, 0, 0, 0.0, 1.0);
    ActivatorSound("skills/unsummon", 127);
    return true;
}

NamedScript Console bool Recall(SkillLevelInfo *SkillLevel, void *Data)
{
    // Fail if you're in the Arena or Marines are hostile
    if (ArenaActive || MarinesHostile)
    {
        PrintError("You cannot recall from this location");
        ActivatorSound("menu/error", 127);
        return false;
    }
        
    SetInventory("ArtiTeleport", 1);
    UseInventory("ArtiTeleport");
    return true;
}

NamedScript Console bool Magnetize(SkillLevelInfo *SkillLevel, void *Data)
{
    int *TID = (int *)Player.DropTID.Data;
    fixed Angle = GetActorAngle(0);
    fixed X = GetActorX(0);
    fixed Y = GetActorY(0);
    fixed Z = GetActorZ(0) + (GetActorPropertyFixed(0, APROP_Height) / 2);
    int AngleDivide;
    fixed AngleAdd;
    int CreditCount;
    
    // Count Credits
    for (int i = 0; i < Player.DropTID.Position; i++)
        if (ThingCount(0, TID[i]) > 0 && StartsWith(GetActorClass(TID[i]), "DRPGCredits"))
        {
            if (GetActorClass(TID[i]) == "DRPGCredits1")
                CreditCount++;
            if (GetActorClass(TID[i]) == "DRPGCredits5")
                CreditCount += 5;
            if (GetActorClass(TID[i]) == "DRPGCredits10")
                CreditCount += 10;
            if (GetActorClass(TID[i]) == "DRPGCredits20")
                CreditCount += 20;
            if (GetActorClass(TID[i]) == "DRPGCredits50")
                CreditCount += 50;
            if (GetActorClass(TID[i]) == "DRPGCredits100")
                CreditCount += 100;
            if (GetActorClass(TID[i]) == "DRPGCredits1000")
                CreditCount += 1000;
            
            int HolderTID = UniqueTID();
            SpawnSpot("DRPGCreditsEmpty", TID[i], HolderTID, Random(0, 255));
            SetActorVelocity(HolderTID, RandomFixed(-8, 8), RandomFixed(-8, 8), RandomFixed(2, 8), false, false);
            Thing_Remove(TID[i]);
        }
    
    // Give calculated Credits
    if (CreditCount > 0)
    {
        if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_DOSHMAGNET)
            CreditCount *= 3;
        
        GiveInventory("DRPGCredits", CreditCount);
        ActivatorSound("credits/pickup", 127);
    }
    
    CleanDropTIDArray();
    
    AngleDivide = Player.DropTID.Position;
    
    // Refund - If there are no items in the array
    if (Player.DropTID.Position == 0 && CreditCount == 0)
    {
        PrintError("No magnetizeable items detected");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Player.Overdrive - Pull the items on top of you and pick them all up
    if (Player.Overdrive)
    {
        for (int i = 0; i < Player.DropTID.Position; i++)
        {
            SetActorPosition(TID[i], X, Y, Z, 0);
            SetActorVelocity(TID[i], 0, 0, 0, false, false);
        }
        
        SetActorVelocity(0, 0.01, 0.01, 0, true, false);
        
        FadeRange(0, 0, 0, 0.5, 0, 0, 0, 0.0, 1.0);
        ActivatorSound("skills/magnet", 127);
        return true;
    }
    
    AngleAdd = 1.0 / AngleDivide;
    
    for (int i = 0; i < Player.DropTID.Position; i++)
    {
        X = GetActorX(0) + Cos(Angle) * 64.0;
        Y = GetActorY(0) + Sin(Angle) * 64.0;
        SetActorPosition(TID[i], X, Y, Z, 0);
        SetActorVelocity(TID[i], 0, 0, 0, false, false);
        Angle += AngleAdd;
    }
    
    FadeRange(0, 0, 0, 0.5, 0, 0, 0, 0.0, 1.0);
    ActivatorSound("skills/magnet", 127);
    return true;
}

NamedScript Console bool Transport(SkillLevelInfo *SkillLevel, void *Data)
{
    // If you're dead, terminate
    if (GetActorProperty(0, APROP_Health) <= 0) return false;
    
    // [marrub] For Seryder
    if (CheckInventory("DRPGDisallowTransport"))
    {
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Don't allow Transport while the arena is active, if the Marines are hostile, or you're in an Outpost-related menu
    if (ArenaActive || MarinesHostile || Player.OutpostMenu > 0)
    {
        PrintError("There was a malwith the transportation system");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Don't allow Transport during the Hell Unleashed event
    if (CurrentLevel && CurrentLevel->Event == MAPEVENT_HELLUNLEASHED && CurrentLevel->HellUnleashedActive)
    {
        PrintError("Error reaching Outpost transportation system");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Same for Feeding Frenzy
    if (CurrentLevel && CurrentLevel->Event == MAPEVENT_DRLA_FEEDINGFRENZY)
    {
        PrintError("Error reaching Outpost transportation system");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    // Multiplayer
    if (InMultiplayer && PlayerCount() > 1)
    {
        int Players = PlayerCount();
        bool Ready = false; 
        bool Force = (Arbitrator && Player.Overdrive);
        bool Voted[MAX_PLAYERS];
        int PlayersApprove = 0;
        int PlayersDeny = 0;
        
        for (int i = 0; i < MAX_PLAYERS; i++)
            Voted[i] = false;
        
        while (!Ready && !Force)
        {
            // Freeze all players
            SetPlayerProperty(1, 1, PROP_TOTALLYFROZEN);
            
            // Input
            for (int i = 0; i < Players; i++)
            {
                // Skip input checks if you've already voted
                if (Voted[i]) continue;
                
                int Buttons = GetPlayerInput(i, INPUT_BUTTONS);
                
                if (Buttons == BT_USE)
                {
                    ActivatorSound("menu/move", 127);
                    PlayersApprove++;
                    Voted[i] = true;
                }
                if (Buttons == BT_SPEED)
                {
                    ActivatorSound("menu/move", 127);
                    PlayersDeny++;
                    Voted[i] = true;
                }
            }
            
            // Check that everyone has voted
            Ready = true;
            for (int i = 0; i < Players; i++)
                if (!Voted[i])
                {
                    Ready = false;
                    break;
                }
            
            // Drawing
            SetFont("BIGFONT");
            HudMessage("\Cd%N\C- has requested Transport\n\C-Players: %d (\Cd%d\C-/\Cg%d\C-)\n\n\Cd%K\C- to Approve\n\Cd%K\C- to Deny",
                       PlayerNumber() + 1, Players, PlayersApprove, PlayersDeny, "+use", "+speed");
            EndHudMessageBold(HUDMSG_FADEOUT, MENU_ID, "White", 0.5, 0.75, 1.0, 4.0);
            
            Delay(1);
        }
        
        // Ready - tally votes and confirm/deny Transport
        if (Ready || Force)
        {
            Transported = true;
            
            SetPlayerProperty(1, 0, PROP_TOTALLYFROZEN);
            
            // Approved
            if (PlayersApprove > PlayersDeny || Force)
            {
                for (int i = 0; i < MAX_PLAYERS; i++)
                {
                    // Player is not in-game
                    if (!PlayerInGame(i)) continue;
                    
                    SpawnForced("DRPGTransportEffect", GetActorX(Players(i).TID), GetActorY(Players(i).TID), GetActorZ(Players(i).TID), 0, 0);
                    TransportOutFX(Players(i).TID);
                    ThingSound(Players(i).TID, "misc/transport", 96);
                }
                
                SetFont("BIGFONT");
                HudMessage("Transport Approved!");
                EndHudMessageBold(HUDMSG_FADEOUT, 0, "Green", 0.5, 0.5, 1.0, 1.0);
                Delay(35 * 2);
            }
            
            // Denied
            else if (PlayersDeny > PlayersApprove)
            {
                SetFont("BIGFONT");
                HudMessage("Transport Denied!");
                EndHudMessageBold(HUDMSG_FADEOUT, 0, "Red", 0.5, 0.5, 1.0, 2.0);
                return false;
            }
            
            // Draw
            else if (PlayersApprove > 0 && PlayersDeny > 0 && PlayersApprove == PlayersDeny)
            {
                SetFont("BIGFONT");
                HudMessage("Draw!");
                EndHudMessageBold(HUDMSG_FADEOUT, 0, "White", 0.5, 0.5, 1.0, 2.0);
                return false;
            }
            
            // Error
            else
            {
                SetFont("BIGFONT");
                HudMessage("An error has occured with the Transport System!");
                EndHudMessageBold(HUDMSG_FADEOUT, 0, "Red", 0.5, 0.5, 1.0, 2.0);
                if (GetCVar("drpg_debug")) // Output EVERYTHING for investigation
                {
                    //Output Players;
                    //Output Ready;
                    //Output Force;
                    //Output Voted;
                    //Output PlayersApprove;
                    //Output PlayersDeny;
                }
                return false;
            }
        }
    }
    else // Single Player
    {
        Transported = true;
        
        // Transport FX
        TransportOutFX(0);
        
        // Delay and unfreeze Player
        Delay(35 * 2);
    }
    
    // Transport
    if (!CurrentLevel->UACBase)
    {
        TransporterLevel = FindLevelInfo();
       
        ChangeLevel(DefaultOutpost->LumpName, 0, CHANGELEVEL_NOINTERMISSION, CurrentSkill);
        return true;
    }
    else
    {
        ChangeLevel(TransporterLevel->LumpName, 0, CHANGELEVEL_NOINTERMISSION, CurrentSkill);
        Transported = true;
        return true;
    }
}

NamedScript void TransportOutFX(int tid)
{
    if (tid != 0)
        SetActivator(tid);
    
    if (GetActorZ(0) == GetActorFloorZ(0))
        SetActorPosition(0, GetActorX(0), GetActorY(0), GetActorZ(0)+1, false);
    GiveInventory("DRPGTransportSetNonShootable", 1);
    ActivatorSound("misc/transport", 96);
    SpawnForced("DRPGTransportEffect", GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
    SetActorProperty(0, APROP_RenderStyle, STYLE_AddStencil);
    SetActorProperty(0, APROP_StencilColor, 0x00FF00);
    for (int ticker = 0; ticker < 70; ticker++)
    {
        SetActorVelocity(0, 0, 0, 0, false, false);
        SetActorPropertyFixed(0, APROP_Alpha, 1.0 - ((1.0 / 70.0) * ticker));
        Delay(1);
    }
}

NamedScript void TransportInFX(int tid)
{
    if (tid != 0)
        SetActivator(tid);
    
    GiveInventory("DRPGTransportUnsetNonShootable", 1);
    ActivatorSound("misc/transport", 96);
    SpawnForced("DRPGTransportEffect", GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
    SetActorProperty(0, APROP_RenderStyle, STYLE_Normal);
    SetActorPropertyFixed(0, APROP_Alpha, 1.0);
}

NamedScript DECORATE void RemoveAura()
{
    Player.Aura.Time = 0;
    Player.Aura.Team = false;
    
    for (int i = 0; i < AURA_MAX; i++)
    {
        Player.Aura.Type[i].Active = false;
        Player.Aura.Type[i].Level = 0;
    }
}

NamedScript DECORATE void ClearStatusEffects()
{
    for (int i = 0; i < SE_MAX; i++)
    {
        if (i == SE_RADIATION && Player.StatusType[i])
            StopSound(Player.TID, 7);
        
        Player.StatusType[i] = false;
        Player.StatusTypeHUD = SE_NONE;
        Player.StatusIntensity[i] = 0;
        Player.StatusTimer[i] = 0;
        Player.StatusTimerMax[i] = 0;
    }
}

NamedScript void CleanDropTIDArray()
{
    // [KS] !!WARNING!! THIS CANNOT BE A FUNCTION.
    int *TID = (int *)Player.DropTID.Data;
    for (int i = 0; i < Player.DropTID.Position; i++)
    {
        if (TID[i] == 0 || ClassifyActor(TID[i]) == ACTOR_NONE)
        {
            TID[i] = TID[Player.DropTID.Position - 1];
            TID[Player.DropTID.Position - 1] = 0;
            Player.DropTID.Position--;
            i -= 2;
            if (i < -1)
                i = -1;
        }
    }
}

void BuildSkillData()
{
    // Generate the description for the Supply Drop
    for (int i = 1; i < Skills[1][7].MaxLevel; i++)
        Skills[1][7].Description[i] = StrParam("%S\nDrop a UAC Supply Crate at your location\n\CjRarity Level: %S", Skills[1][7].Description[0], CrateRarityNames[i - 1]);
    
    // DoomRL Compatibility
    if (CompatMode == COMPAT_DRLA)
    {
        // DoomRLA has different damage types than usual
        Skills[3][6].Description[1] = "Unleashes a beam of searing flames and crackling plasma\n\CdDeals \CgFire\Cd and \CnPlasma\Cd damage\n\CdPierces through enemies";
        Skills[3][6].Description[2] = "Unleashes a beam of deadly and powerful dark energies\n\CdDeals \CuPiercing\Cd damage\n\CdPierces through enemies\n\CdIgnores armors and defenses";

        // DoomRL Marines use slightly different weapons
        Skills[4][0].Description[2] = "Summons a Marine\n\CjDouble Shotgun";
        Skills[4][0].Description[3] = "Summons a Marine\n\CjBattle Rifle";
        
        // Summoning Skills - Names
        Skills[4][1].Name = "Summon Former Human";
        Skills[4][2].Name = "Summon Former Sergeant";
        Skills[4][3].Name = "Summon Former Commando";
        
        // Summoning Skills - Levels
        Skills[4][1].MaxLevel = 3;
        Skills[4][2].MaxLevel = 2;
        Skills[4][3].MaxLevel = 3;
        Skills[4][4].MaxLevel = 3;
        Skills[4][5].MaxLevel = 6;
        Skills[4][6].MaxLevel = 2;
        Skills[4][7].MaxLevel = 3;
        Skills[4][8].MaxLevel = 3;
        Skills[4][9].MaxLevel = 3;
        Skills[4][10].MaxLevel = 2;
        Skills[4][11].MaxLevel = 3;
        Skills[4][12].MaxLevel = 3;
        Skills[4][13].MaxLevel = 3;
        Skills[4][14].MaxLevel = 2;
        Skills[4][15].MaxLevel = 2;
        Skills[4][16].MaxLevel = 2;
        
        // Summoning Skills - Descriptions
        Skills[4][1].Description[0] = "Summons a Former Human";
        Skills[4][1].Description[1] = "Summons an Elite Human";
        Skills[4][1].Description[2] = "Summons a Former Human Captain";
        Skills[4][2].Description[0] = "Summons a Former Sergeant";
        Skills[4][2].Description[1] = "Summons an Elite Sergeant";
        Skills[4][3].Description[0] = "Summons a Former Commando";
        Skills[4][3].Description[1] = "Summons an Elite Commando";
        Skills[4][3].Description[2] = "Summons an Elite Human Captain";
        Skills[4][4].Description[1] = "Summons a Nightmare Imp";
        Skills[4][4].Description[2] = "Summons a Cyber-Imp";
        Skills[4][5].Description[1] = "Summons a Spectre";
        Skills[4][5].Description[2] = "Summons a Nightmare Demon";
        Skills[4][5].Description[3] = "Summons a Nightmare Spectre";
        Skills[4][5].Description[4] = "Summons a Mech-Demon";
        Skills[4][5].Description[5] = "Summons a Mechtre";
        Skills[4][6].Description[1] = "Summons a Nightmare Cacodemon";
        Skills[4][7].Description[1] = "Summons a Nightmare Knight";
        Skills[4][7].Description[2] = "Summons a Cybruiser";
        Skills[4][8].Description[1] = "Summons a Baron of Nightmares";
        Skills[4][8].Description[2] = "Summons a Techno-Lord";
        Skills[4][9].Description[1] = "Summons a Nightmare Soul";
        Skills[4][9].Description[2] = "Summons a Hellmine";
        Skills[4][10].Description[1] = "Summons a Nightmare Elemental";
        Skills[4][11].Description[1] = "Summons a Nightmare Revenant";
        Skills[4][11].Description[2] = "Summons a Heavy Revenant";
        Skills[4][12].Description[1] = "Summons a Nightmare Mancubus";
        Skills[4][12].Description[2] = "Summons a Volacubus";
        Skills[4][13].Description[1] = "Summons a Nightmare Arachnotron";
        Skills[4][13].Description[2] = "Summons a Arachnsentinel";
        Skills[4][14].Description[1] = "Summons a Nightmare Arch-Vile";
        Skills[4][15].Description[1] = "Summons a Nightmare Cyberdemon";
        Skills[4][16].Description[1] = "Summons a Spider Overmind";
    }
    
    // Icons
    for (int i = 0; i < MAX_CATEGORIES; i++)
        for (int j = 0; j < MAX_SKILLS; j++)
            Skills[i][j].Icon = StrParam("SKIL%d_%d", i + 1, j + 1);
}

int ScaleEPCost(int Cost)
{
    int ScaleCost = Cost;
    
    // Multiplier CVAR
    ScaleCost *= (GetCVarFixed("drpg_skill_costscale") * 100);
    ScaleCost /= 100;
    
    // Aura Multiplier
    if (Player.SkillCostMult > 0)
        ScaleCost += (Player.SkillCostMult * ScaleCost) / 100;
    
    return ScaleCost;
}

void CheckSkills()
{
    // Reset the Skill refund multiplier from the Blue Aura and Energy Augmentation
    Player.SkillRefundMult = 0;
    
    // Level 4 and 5 of the Energy Augmentation increase skill refund rate
    if (Player.Augs.Active[AUG_ENERGY])
    {
        if (Player.Augs.Level[AUG_ENERGY] == 4)
            Player.SkillRefundMult += 0.05;
        else if (Player.Augs.Level[AUG_ENERGY] == 5)
            Player.SkillRefundMult += 0.1;
        else if (Player.Augs.Level[AUG_ENERGY] == 6)
            Player.SkillRefundMult += 0.15;
        else if (Player.Augs.Level[AUG_ENERGY] == 7)
            Player.SkillRefundMult += 0.2;
        else if (Player.Augs.Level[AUG_ENERGY] >= 8)
            Player.SkillRefundMult += 0.25;
    }
    
    // Summoned Monsters Handling
    for (int i = 0; i < MAX_SUMMONS; i++)
        if (Player.SummonTID[i] != 0 && GetActorProperty(Player.SummonTID[i], APROP_Health) <= 0)
        {
            SpawnForced("TeleportFog", GetActorX(Player.SummonTID[i]), GetActorY(Player.SummonTID[i]), GetActorZ(Player.SummonTID[i]), 0, 0);
            Thing_Remove(Player.SummonTID[i]);
            Player.SummonTID[i] = 0;
            Player.Summons--;
        }
    
    // Powerup cooldown timer handling
    if (Player.SkillPowerupCooldown > 0)
        Player.SkillPowerupCooldown--;
    
    // Supply Drop cooldown timer handling
    if (Player.SkillSupplyCooldown > 0)
        Player.SkillSupplyCooldown--;
    
    // Cost multiplier timer handling
    if ((!CurrentLevel->UACBase || ArenaActive || MarinesHostile) && Player.SkillCostMult > 0 && !PlayerHasAura(PlayerNumber()))
        if ((Timer() % (35 * GetCVar("drpg_skill_costcooldown"))) == 0)
            Player.SkillCostMult--;
    
    // Bullet-Time timer handling
    if (BulletTimeTimer > 0)
    {
        if (BulletTimeTimer % 3)
            GiveInventory("DRPGTimeFreezerQuick", 1);
        
        BulletTimeTimer--;
    }
}

void CheckAuras()
{
    fixed LuckMult = 1;
    fixed X = GetActorX(0);
    fixed Y = GetActorY(0);
    fixed Z = GetActorZ(0);
    int Angle = GetActorAngle(0) * 256;
    int AmmoRegenMult = 1;
    bool Shadow = PlayerHasShadowAura(PlayerNumber());
    
    // Team Aura Handling
    if (InMultiplayer && Player.Aura.Time > 0)
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            // Skip yourself
            if (Player.TID == Players(i).TID) continue;
            
            if (Distance(Player.TID, Players(i).TID) <= Player.Aura.Range)
            {
                Players(i).Aura.Team = true;
                
                for (int j = 0; j < AURA_MAX; j++)
                    if (Player.Aura.Type[j].Active && Player.Aura.Type[j].Level >= Players(i).Aura.Type[j].Level)
                        Players(i).Aura.Type[j] = Player.Aura.Type[j];
            }
            else
                Players(i).Aura.Team = false;
        }
    
    // TEEM-AU5 Shield Accessory Handling
    if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_DATAURA && Player.Shield.Active)
        for (int i = 0; i < MAX_PLAYERS; i++)
            for (int j = 0; j < AURA_MAX; j++)
                if (Player.Aura.Type[j].Active && Players(i).Aura.Type[j].Active)
                {
                    Players(i).Aura.DefenseBoost = true;
                    break;
                }
    if (Player.Aura.DefenseBoost)
    {
        Player.DamageFactor += 0.2;
        Player.Aura.DefenseBoost = false;
    }
    
    // Aura handling
    if (Player.Aura.Time > 0 || Player.Aura.Team)
    {
        // Red Aura
        if (Player.Aura.Type[AURA_RED].Active)
        {
            if (Player.SoulActive[SOUL_RED])
                Player.DamageMult += 4;
            else if (Player.Aura.Type[AURA_RED].Level == 1)
                Player.DamageMult += 1.25;
            else if (Player.Aura.Type[AURA_RED].Level == 2)
                Player.DamageMult += 1.5;
            else if (Player.Aura.Type[AURA_RED].Level == 3)
                Player.DamageMult += 1.75;
            else if (Player.Aura.Type[AURA_RED].Level == 4)
                Player.DamageMult += 2;
            else if (Player.Aura.Type[AURA_RED].Level == 5)
                Player.DamageMult += 3;
            else if (Player.Aura.Type[AURA_RED].Level == 6)
                Player.DamageMult += 4;
        }
        
        // Green Aura
        if (Player.Aura.Type[AURA_GREEN].Active)
        {
            if (Player.Aura.Type[AURA_GREEN].Level >= 1)
                Player.DamageFactor -= (fixed)Player.Aura.Type[AURA_GREEN].Level / 20.0;
            if (Player.Aura.Type[AURA_GREEN].Level >= 3 || Player.SoulActive[SOUL_GREEN])
                GiveInventory("DRPGGreenAuraIronFeet", 1);
        }
        
        // White Aura
        if (Player.Aura.Type[AURA_WHITE].Active && (!CurrentLevel->UACBase || ArenaActive || MarinesHostile))
        {
            if (Player.Aura.Type[AURA_WHITE].Level >= 2 || Player.SoulActive[SOUL_WHITE])
            {
                if (Player.Combo == 0) Player.Combo++;
                Player.ComboTimer = COMBO_MAX - 1;
            }
            if (Player.Aura.Type[AURA_WHITE].Level == 3)
                if ((Timer() % (35 * 4)) == 1)
                    Player.XPGained += XPTable[Player.Level] / 100 / (Player.Level + 1);
            if (Player.Aura.Type[AURA_WHITE].Level >= 4 || Player.SoulActive[SOUL_WHITE])
                if ((Timer() % (35 * 2)) == 1)
                    Player.XPGained += XPTable[Player.Level] / 100 / (Player.Level + 1);
        }
        
        // Pink Aura
        if (Player.Aura.Type[AURA_PINK].Active)
            if (Player.Aura.Type[AURA_PINK].Level >= 2 || Player.SoulActive[SOUL_PINK])
                GiveInventory("DRPGPinkAuraDrain", 1);
        
        // Blue Aura
        if (Player.Aura.Type[AURA_BLUE].Active)
        {
            if (Player.Aura.Type[AURA_BLUE].Level == 1)
                Player.SkillRefundMult += 0.05;
            if (Player.Aura.Type[AURA_BLUE].Level == 2)
                Player.SkillRefundMult += 0.1;
            if (Player.Aura.Type[AURA_BLUE].Level == 3)
                Player.SkillRefundMult += 0.15;
            if (Player.Aura.Type[AURA_BLUE].Level == 4)
                Player.SkillRefundMult += 0.2;
            if (Player.Aura.Type[AURA_BLUE].Level >= 5 || Player.SoulActive[SOUL_BLUE])
                Player.SkillRefundMult += 0.25;
        }
        
        // Purple Aura
        if (Player.Aura.Type[AURA_PURPLE].Active)
        {
            if (Player.Aura.Type[AURA_PURPLE].Level == 1)
            {
                Player.HPAmount *= 2;
                Player.EPAmount *= 2;
            }
            if (Player.Aura.Type[AURA_PURPLE].Level == 2)
            {
                Player.HPAmount *= 3;
                Player.EPAmount *= 3;
            }
            if (Player.Aura.Type[AURA_PURPLE].Level == 3)
            {
                Player.HPAmount *= 4;
                Player.EPAmount *= 4;
            }
            if (Player.Aura.Type[AURA_PURPLE].Level >= 4 || Player.SoulActive[SOUL_PURPLE])
            {
                Player.HPAmount *= 4;
                Player.EPAmount *= 4;
                Player.HPTime /= 2;
                Player.EPTime /= 2;
            }
        }
        
        // Orange Aura
        if (Player.Aura.Type[AURA_ORANGE].Level)
        {
            if (Player.Aura.Type[AURA_ORANGE].Level >= 1 || Player.SoulActive[SOUL_ORANGE])
                Player.Speed *= 2;
            if (Player.Aura.Type[AURA_ORANGE].Level >= 2 || Player.SoulActive[SOUL_ORANGE])
                Player.JumpHeight *= 2;
            if (Player.Aura.Type[AURA_ORANGE].Level >= 3 || Player.SoulActive[SOUL_ORANGE])
                Player.WeaponSpeed = 100;
        }

        // Dark Blue Aura
        if (Player.Aura.Type[AURA_DARKBLUE].Active)
        {
            if (Player.Aura.Type[AURA_DARKBLUE].Level == 5)
                AmmoRegenMult = 2;
            if (Player.Aura.Type[AURA_DARKBLUE].Level >= 6 || Player.SoulActive[SOUL_DARKBLUE])
                AmmoRegenMult = 4;
            if (Player.Aura.Type[AURA_DARKBLUE].Level >= 1 || Player.SoulActive[SOUL_DARKBLUE])
                if ((Timer() % (35 / 2)) == 0)
                    GiveInventory("Clip", AmmoRegenMult);
            if (Player.Aura.Type[AURA_DARKBLUE].Level >= 2 || Player.SoulActive[SOUL_DARKBLUE])
                if ((Timer() % 35) == 1)
                    GiveInventory("Shell", AmmoRegenMult);
            if (Player.Aura.Type[AURA_DARKBLUE].Level >= 3 || Player.SoulActive[SOUL_DARKBLUE])
                if ((Timer() % (35 * 2)) == 0)
                    GiveInventory("RocketAmmo", AmmoRegenMult);
            if (Player.Aura.Type[AURA_DARKBLUE].Level >= 4 || Player.SoulActive[SOUL_DARKBLUE])
                if ((Timer() % (35 / 2)) == 0)
                    GiveInventory("Cell", AmmoRegenMult);
            if (Player.Aura.Type[AURA_DARKBLUE].Level >= 7 || Player.SoulActive[SOUL_DARKBLUE])
                GiveInventory("DRPGDarkBlueAuraInfiniteAmmo", 1);
        }
        
        // Yellow Aura
        if (Player.Aura.Type[AURA_YELLOW].Active && (!CurrentLevel->UACBase || ArenaActive || MarinesHostile))
        {
            if ((Timer() % (35 * (6 - Player.Aura.Type[AURA_YELLOW].Level))) == 1)
                GiveInventory("DRPGCredits", (Player.RankLevel + 1));
            if (Player.Aura.Type[AURA_YELLOW].Level == 1)
                LuckMult = 1.25;
            if (Player.Aura.Type[AURA_YELLOW].Level == 2)
                LuckMult = 1.5;
            if (Player.Aura.Type[AURA_YELLOW].Level == 3)
                LuckMult = 2;
            if (Player.Aura.Type[AURA_YELLOW].Level == 4)
                LuckMult = 4;
            if (Player.Aura.Type[AURA_YELLOW].Level >= 5 || Player.SoulActive[SOUL_YELLOW])
                LuckMult = 8;
            
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
        
        // Spawn Aura
        if (PlayerHasAura(PlayerNumber()))
            SpawnAuras(Player.TID, false);
    }
    
    // Decrease Aura Timer
    if (!CurrentLevel->UACBase || ArenaActive || MarinesHostile)
        for (int i = 0; i < AURA_MAX; i++)
            if (Player.Aura.Time > 0 && Player.Aura.Type[i].Active)
                if (!CheckInventory("PowerTimeFreezer") && !CheckInventory("DRPGPowerStimChrono"))
                {
                    Player.Aura.Time--;
                    break; // Remove this for Yholl-style behavior, still contemplating
                }
    
    // Reset Aura and Soul States
    if (Player.Aura.Time <= 0 || !Player.Aura.Team)
    {
        // Reset Auras
        for (int i = 0; i < AURA_MAX; i++)
            if (Player.Aura.Time <= 0)
            {
                Player.Aura.Type[i].Active = false;
                Player.Aura.Type[i].Level = 0;
            }
        
        // Reset Souls
        for (int i = 0; i < SOUL_MAX; i++)
            Player.SoulActive[i] = false;
    }
}
