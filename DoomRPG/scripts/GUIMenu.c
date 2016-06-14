#include "Defs.h"

#include "GUIMenu.h"
#include "GUI.h"
#include "Map.h"
#include "Menu.h"
#include "Stats.h"
#include "RPG.h"
#include "Utils.h"

NamedScript void CreateGUIMenu()
{
    // Do first-time creation here
    
    CreateTabs();
    CreatePanels();
    
    Player.GUI.Created = true;
}

NamedScript void CreateTabs()
{
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Icon = "TMain";
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].HighlightedIcon = "HMain";
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Title = "Overview";
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Tooltip->Title = "Overview";
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Tooltip->Text = "A quick look at your numbers.";
    
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Icon = "TStats";
    Player.GUI.TabStrip.Tabs[PANEL_STATS].HighlightedIcon = "HStats";
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Title = "\CgStats";
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Tooltip->Title = "\CgStats";
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Tooltip->Text = "A check on your survivability.";
    
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Icon = "TAugs";
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].HighlightedIcon = "HAugs";
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Title = "\CkAugments";
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Tooltip->Title = "\CkAugments";
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Tooltip->Text = "Upgrades, for your eyes and more.";
    
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Icon = "TSkills";
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].HighlightedIcon = "HSkills";
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Title = "\CnSkills";
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Tooltip->Title = "\CnSkills";
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Tooltip->Text = "Flamethrowers, summons, and auras.";
    
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Icon = "TShield";
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].HighlightedIcon = "HShield";
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Title = "\CvShield";
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Tooltip->Title = "\CvShield";
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Tooltip->Text = "An alternative to getting shot.";
    
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Icon = "TStims";
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].HighlightedIcon = "HStims";
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Title = "\CcStims";
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Tooltip->Title = "\CcStims";
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Tooltip->Text = "Intravenous murder-boosters.";
    
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Icon = "TTurret";
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].HighlightedIcon = "HTurret";
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Title = "\CdTurret";
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Tooltip->Title = "\CdTurret";
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Tooltip->Text = "Your best beepy little buddy.";
    
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Icon = "TShop";
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].HighlightedIcon = "HShop";
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Title = "\CfShop";
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Tooltip->Title = "\CfShop";
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Tooltip->Text = "Purchase your necessities here.";
    
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Icon = "TPayout";
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].HighlightedIcon = "HPayout";
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Title = "\CfPayout";
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Tooltip->Title = "\CfPayout";
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Tooltip->Text = "Rewards for good performance.";
    
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Icon = "TMission";
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].HighlightedIcon = "HMission";
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Title = "\CaMissions";
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Tooltip->Title = "\CaMissions";
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Tooltip->Text = "Optional challenges, better pay.";
    
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Icon = "TTrans";
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].HighlightedIcon = "HTrans";
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Title = "\ChTransport";
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Tooltip->Title = "\ChTransport";
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Tooltip->Text = "An overview of the world.";
    
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Icon = "TTeam";
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].HighlightedIcon = "HTeam";
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Title = "\CqTeam";
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Tooltip->Title = "\CqTeam";
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Tooltip->Text = "An opinion on your teammates.";
    
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Icon = "TTips";
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].HighlightedIcon = "HTips";
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Title = "\CuTips";
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Tooltip->Type = TT_TITLE;
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Tooltip->Title = "\CuTips";
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Tooltip->Text = "For when you just don't know.";
    
    Player.GUI.TabStrip.Tabs[PANEL_MAX].Icon = "";
    Player.GUI.TabStrip.Tabs[PANEL_MAX].Title = "";
    Player.GUI.TabStrip.Tabs[PANEL_MAX].Enabled = false;
}

NamedScript void CreatePanels()
{
    CreateOverviewPanel();
}

// --------------------------------------------------
// GUI Panels
//

NamedScript void CreateOverviewPanel()
{
    GUIPanel *OverviewPanel = GUICreatePanel();
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Panel = OverviewPanel;
    
    OverviewPanel->Update = (PanelUpdateFunc)UpdateOverviewPanel;
    
    int GUIElementID = GUI_CONTENTS_ID;
    
    // --------------------------------------------------
    // Player Sprite
    //
    
    str PlayerSprite = "PLAYA1";
    
    GUIIcon *PlayerSpriteIcon = GUIAddIcon(OverviewPanel, "Player Sprite");
    
    if (CompatMode == COMPAT_DRLA)
    {
        if (PlayerClass(PlayerNumber()) == 0) // Marine
            PlayerSprite = "PMARA1";
        if (PlayerClass(PlayerNumber()) == 1) // Scout
            PlayerSprite = "PSCOA1";
        if (PlayerClass(PlayerNumber()) == 2) // Technician
            PlayerSprite = "PTECA1";
        if (PlayerClass(PlayerNumber()) == 3) // Renegade
            PlayerSprite = "PRENA1";
        if (PlayerClass(PlayerNumber()) == 4) // Demolitionist
            PlayerSprite = "PDMOA1";
    }
    
    PlayerSpriteIcon->Texture = PlayerSprite;
    PlayerSpriteIcon->Control.X = 16;
    PlayerSpriteIcon->Control.Y = 40;
    PlayerSpriteIcon->Control.id = ++GUIElementID;
    
    // --------------------------------------------------
    // Player Info
    //
    
    GUILabel *NameLabel = GUIAddLabel(OverviewPanel, "Player Name");
    GUILabel *LevelLabel = GUIAddLabel(OverviewPanel, "Player Level");
    GUILabel *XPLabel = GUIAddLabel(OverviewPanel, "Player XP");
    GUILabel *TitleLabel = GUIAddLabel(OverviewPanel, "Player Rank Title");
    GUILabel *RankLabel = GUIAddLabel(OverviewPanel, "Player Rank");
    GUILabel *PPLabel = GUIAddLabel(OverviewPanel, "Player Payout Status");
    
    NameLabel->Control.X = 64;
    NameLabel->Control.Y = 16;
    NameLabel->Control.id = ++GUIElementID;
    NameLabel->Color = "White";
    NameLabel->Big = true;
    
    LevelLabel->Control.X = 64;
    LevelLabel->Control.Y = 28;
    LevelLabel->Control.id = ++GUIElementID;
    LevelLabel->Color = "White";
    LevelLabel->Big = true;
    
    XPLabel->Control.X = 64;
    XPLabel->Control.Y = 40;
    XPLabel->Control.id = ++GUIElementID;
    XPLabel->Color = "White";
    XPLabel->Big = true;
    
    TitleLabel->Control.X = 64;
    TitleLabel->Control.Y = 52;
    TitleLabel->Control.id = ++GUIElementID;
    TitleLabel->Color = "Yellow";
    TitleLabel->Big = true;
    
    RankLabel->Control.X = 64;
    RankLabel->Control.Y = 64;
    RankLabel->Control.id = ++GUIElementID;
    RankLabel->Color = "Yellow";
    RankLabel->Big = true;
    
    PPLabel->Control.X = 64;
    PPLabel->Control.Y = 76;
    PPLabel->Control.id = ++GUIElementID;
    PPLabel->Color = "Gold";
    PPLabel->Big = true;
    
    // --------------------------------------------------
    // Totals
    //
    
    // TODO: Put DRLA stuff below the inventory/ammo totals
    
    GUIIcon *ModuleIcon = GUIAddIcon(OverviewPanel, "Module Icon");
    GUIIcon *TurretPartsIcon = GUIAddIcon(OverviewPanel, "Turret Parts Icon");
    GUIIcon *AugChargeIcon = GUIAddIcon(OverviewPanel, "Aug Charge icon");
    GUIIcon *AugSlotsIcon = GUIAddIcon(OverviewPanel, "Aug Slots Icon");
    GUIIcon *AugCanistersIcon = GUIAddIcon(OverviewPanel, "Aug Canisters Icon");
    GUIIcon *AugUpgradesIcon = GUIAddIcon(OverviewPanel, "Aug Upgrades Icon");
    GUIIcon *StimsIcon = GUIAddIcon(OverviewPanel, "Stims Icon");
    GUIIcon *ChipsGoldIcon = GUIAddIcon(OverviewPanel, "Gold Chips Icon");
    GUIIcon *ChipsPlatIcon = GUIAddIcon(OverviewPanel, "Platinum Chips Icon");
    GUIIcon *InventoryIcon = GUIAddIcon(OverviewPanel, "Inventory Icon");
    
    GUILabel *ModuleLabel = GUIAddLabel(OverviewPanel, "Module Count");
    GUILabel *TurretPartsLabel = GUIAddLabel(OverviewPanel, "Turret Part Count");
    GUILabel *AugChargeLabel = GUIAddLabel(OverviewPanel, "Aug Charge");
    GUILabel *AugSlotsLabel = GUIAddLabel(OverviewPanel, "Aug Slots");
    GUILabel *AugUpgradesLabel = GUIAddLabel(OverviewPanel, "Aug Upgrades");
    GUILabel *StimsLabel = GUIAddLabel(OverviewPanel, "Stim Counts");
    GUILabel *ChipsGoldLabel = GUIAddLabel(OverviewPanel, "Gold Chip Count");
    GUILabel *ChipsPlatLabel = GUIAddLabel(OverviewPanel, "Platinum Chip Count");
    GUILabel *InventoryLabel = GUIAddLabel(OverviewPanel, "Inventory Count");
    
    ModuleIcon->Texture = "UMODA0";
    ModuleIcon->Control.X = 24;
    ModuleIcon->Control.Y = 96;
    ModuleIcon->Control.id = ++GUIElementID;
    
    TurretPartsIcon->Texture = "TPRTA0";
    TurretPartsIcon->Control.X = 24;
    TurretPartsIcon->Control.Y = 128;
    TurretPartsIcon->Control.id = ++GUIElementID;
    
    AugChargeIcon->Texture = "AUGBATT";
    AugChargeIcon->Control.X = 24;
    AugChargeIcon->Control.Y = 148;
    AugChargeIcon->Control.id = ++GUIElementID;
    
    AugSlotsIcon->Texture = "AUGUB0";
    AugSlotsIcon->Control.X = 24;
    AugSlotsIcon->Control.Y = 178;
    AugSlotsIcon->Control.id = ++GUIElementID;
    
    AugCanistersIcon->Texture = "AUGCA0";
    AugCanistersIcon->Control.X = 16;
    AugCanistersIcon->Control.Y = 204;
    AugCanistersIcon->Control.id = ++GUIElementID;
    
    AugUpgradesIcon->Texture = "AUGUA0";
    AugUpgradesIcon->Control.X = 32;
    AugUpgradesIcon->Control.Y = 198;
    AugUpgradesIcon->Control.id = ++GUIElementID;
    
    StimsIcon->Texture = "STIMB0";
    StimsIcon->Control.X = 24;
    StimsIcon->Control.Y = 248;
    StimsIcon->Control.id = ++GUIElementID;
    
    ChipsGoldIcon->Texture = "CHIPGOLD";
    ChipsGoldIcon->Control.X = 8;
    ChipsGoldIcon->Control.Y = 268;
    ChipsGoldIcon->Control.id = ++GUIElementID;
    
    ChipsPlatIcon->Texture = "CHIPPLAT";
    ChipsPlatIcon->Control.X = 8;
    ChipsPlatIcon->Control.Y = 304;
    ChipsPlatIcon->Control.id = ++GUIElementID;
    
    InventoryIcon->Texture = "GPAKA0";
    InventoryIcon->Control.X = 24;
    InventoryIcon->Control.Y = 396;
    InventoryIcon->Control.id = ++GUIElementID;
    
    ModuleLabel->Control.X = 84;
    ModuleLabel->Control.Y = 116;
    ModuleLabel->Control.id = ++GUIElementID;
    ModuleLabel->Color = "Green";
    ModuleLabel->Big = true;
    
    TurretPartsLabel->Control.X = 84;
    TurretPartsLabel->Control.Y = 148;
    TurretPartsLabel->Control.id = ++GUIElementID;
    TurretPartsLabel->Color = "White";
    TurretPartsLabel->Big = true;
    
    AugChargeLabel->Control.X = 84;
    AugChargeLabel->Control.Y = 180;
    AugChargeLabel->Control.id = ++GUIElementID;
    AugChargeLabel->Color = "Yellow";
    AugChargeLabel->Big = true;
    
    AugSlotsLabel->Control.X = 84;
    AugSlotsLabel->Control.Y = 200;
    AugSlotsLabel->Control.id = ++GUIElementID;
    AugSlotsLabel->Color = "Green";
    AugSlotsLabel->Big = true;
    
    AugUpgradesLabel->Control.X = 84;
    AugUpgradesLabel->Control.Y = 224;
    AugUpgradesLabel->Control.id = ++GUIElementID;
    AugUpgradesLabel->Color = "Green";
    AugUpgradesLabel->Big = true;
    
    StimsLabel->Control.X = 84;
    StimsLabel->Control.Y = 264;
    StimsLabel->Control.id = ++GUIElementID;
    StimsLabel->Color = "White";
    StimsLabel->Big = true;
    
    ChipsGoldLabel->Control.X = 84;
    ChipsGoldLabel->Control.Y = 314;
    ChipsGoldLabel->Control.id = ++GUIElementID;
    ChipsGoldLabel->Color = "Gold";
    ChipsGoldLabel->Big = true;
    
    ChipsPlatLabel->Control.X = 84;
    ChipsPlatLabel->Control.Y = 350;
    ChipsPlatLabel->Control.id = ++GUIElementID;
    ChipsPlatLabel->Color = "White";
    ChipsPlatLabel->Big = true;
    
    InventoryLabel->Control.X = 84;
    InventoryLabel->Control.Y = 412;
    InventoryLabel->Control.id = ++GUIElementID;
    InventoryLabel->Color = "White";
    InventoryLabel->Big = true;
    
    // --------------------------------------------------
    // Map Stats
    //
    
    GUIIcon *MapIcon = GUIAddIcon(OverviewPanel, "Map Icon");
    
    GUILabel *MapNameLabel = GUIAddLabel(OverviewPanel, "Map Name");
    GUILabel *MapInfoLabel = GUIAddLabel(OverviewPanel, "Map Info");
    GUILabel *MapTimeLabel = GUIAddLabel(OverviewPanel, "Map Time");
    GUILabel *MapKillsLabel = GUIAddLabel(OverviewPanel, "Map Kills");
    GUILabel *MapItemsLabel = GUIAddLabel(OverviewPanel, "Map Items");
    GUILabel *MapSecretsLabel = GUIAddLabel(OverviewPanel, "Map Secrets");
    
    MapIcon->Texture = "PMAPA0";
    MapIcon->Control.X = 284;
    MapIcon->Control.Y = 96;
    MapIcon->Control.id = ++GUIElementID;
    
    MapNameLabel->Control.X = 328;
    MapNameLabel->Control.Y = 110;
    MapNameLabel->Control.id = ++GUIElementID;
    MapNameLabel->Color = "White";
    MapNameLabel->Big = true;
    
    MapInfoLabel->Control.X = 328;
    MapInfoLabel->Control.Y = 122;
    MapInfoLabel->Control.id = ++GUIElementID;
    MapInfoLabel->Color = "Green";
    MapInfoLabel->Big = true;
    
    MapTimeLabel->Control.X = 328;
    MapTimeLabel->Control.Y = 134;
    MapTimeLabel->Control.id = ++GUIElementID;
    MapTimeLabel->Color = "Orange";
    MapTimeLabel->Big = true;
    
    MapKillsLabel->Control.X = 328;
    MapKillsLabel->Control.Y = 146;
    MapKillsLabel->Control.id = ++GUIElementID;
    MapKillsLabel->Big = true;
    
    MapItemsLabel->Control.X = 328;
    MapItemsLabel->Control.Y = 158;
    MapItemsLabel->Control.id = ++GUIElementID;
    MapItemsLabel->Big = true;
    
    MapSecretsLabel->Control.X = 328;
    MapSecretsLabel->Control.Y = 170;
    MapSecretsLabel->Control.id = ++GUIElementID;
    MapSecretsLabel->Big = true;
    
    // --------------------------------------------------
    // Shield
    //
    GUIIcon *ShAccIcon = GUIAddIcon(OverviewPanel, "Shield Accessory");
    GUIIcon *ShBatIcon = GUIAddIcon(OverviewPanel, "Shield Battery");
    GUIIcon *ShCapIcon = GUIAddIcon(OverviewPanel, "Shield Capacitor");
    GUIIcon *ShBodIcon = GUIAddIcon(OverviewPanel, "Shield Body");
    
    ShAccIcon->Texture = "SHA2A0";
    ShAccIcon->Control.X = 286;
    ShAccIcon->Control.Y = 235;
    ShAccIcon->Control.id = ++GUIElementID;
    
    ShBatIcon->Texture = "SHBAA0";
    ShBatIcon->Control.X = 286;
    ShBatIcon->Control.Y = 235;
    ShBatIcon->Control.id = ++GUIElementID;
    
    ShCapIcon->Texture = "SHCAA0";
    ShCapIcon->Control.X = 286;
    ShCapIcon->Control.Y = 235;
    ShCapIcon->Control.id = ++GUIElementID;
    
    ShBodIcon->Texture = "SHBOA0";
    ShBodIcon->Control.X = 286;
    ShBodIcon->Control.Y = 235;
    ShBodIcon->Control.id = ++GUIElementID;
    
    GUILabel *ShNameLabel = GUIAddLabel(OverviewPanel, "Shield Name");
    GUILabel *ShCapLabel = GUIAddLabel(OverviewPanel, "Shield Capacity");
    GUILabel *ShCrgLabel = GUIAddLabel(OverviewPanel, "Shield Charge");
    GUILabel *ShDlyLabel = GUIAddLabel(OverviewPanel, "Shield Delay");
    
    ShNameLabel->Control.X = 324;
    ShNameLabel->Control.Y = 240;
    ShNameLabel->Control.id = ++GUIElementID;
    ShNameLabel->Color = "White";
    
    ShCapLabel->Control.X = 324;
    ShCapLabel->Control.Y = 248;
    ShCapLabel->Control.id = ++GUIElementID;
    ShCapLabel->Color = "White";
    
    ShCrgLabel->Control.X = 324;
    ShCrgLabel->Control.Y = 256;
    ShCrgLabel->Control.id = ++GUIElementID;
    ShCrgLabel->Color = "White";
    
    ShDlyLabel->Control.X = 324;
    ShDlyLabel->Control.Y = 264;
    ShDlyLabel->Control.id = ++GUIElementID;
    ShDlyLabel->Color = "White";
    
    // --------------------------------------------------
    // Current Stim / Toxicity
    //
    
    GUILabel *CurStimLabel = GUIAddLabel(OverviewPanel, "Current Stim");
    
    GUIBar *CurStimBar[STIM_MAX];
    for (int i = 0; i < STIM_MAX; i++)
    {
        CurStimBar[i] = GUIAddBar(OverviewPanel, StrParam("Stim Bar %d", i));
        
        CurStimBar[i]->Control.X = 326;
        CurStimBar[i]->Control.Y = 300;
        CurStimBar[i]->Control.id = ++GUIElementID;
        CurStimBar[i]->Texture = StrParam("Stim%d", i + 1);
        CurStimBar[i]->ValueMax = 100;
    }
    
    CurStimLabel->Control.X = 324;
    CurStimLabel->Control.Y = 290;
    CurStimLabel->Control.id = ++GUIElementID;
    CurStimLabel->Color = "Green";
    CurStimLabel->Big = true;
    
}

NamedScript void UpdateOverviewPanel(GUIPanel *OverviewPanel)
{
    GUILabel *NameLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Player Name");
    GUILabel *LevelLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Player Level");
    GUILabel *XPLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Player XP");
    GUILabel *TitleLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Player Rank Title");
    GUILabel *RankLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Player Rank");
    GUILabel *PPLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Player Payout Status");
    
    GUILabel *ModuleLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Module Count");
    GUILabel *TurretPartsLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Turret Part Count");
    GUILabel *AugChargeLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Aug Charge");
    GUILabel *AugSlotsLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Aug Slots");
    GUILabel *AugUpgradesLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Aug Upgrades");
    GUILabel *StimsLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Stim Counts");
    GUILabel *ChipsGoldLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Gold Chip Count");
    GUILabel *ChipsPlatLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Platinum Chip Count");
    GUILabel *InventoryLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Inventory Count");
    
    GUIIcon  *MapIcon = (GUIIcon *)GUIControlByName(OverviewPanel, "Map Icon");
    GUILabel *MapNameLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Map Name");
    GUILabel *MapInfoLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Map Info");
    GUILabel *MapTimeLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Map Time");
    GUILabel *MapKillsLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Map Kills");
    GUILabel *MapItemsLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Map Items");
    GUILabel *MapSecretsLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Map Secrets");
    
    GUIIcon  *ShAccIcon = (GUIIcon *)GUIControlByName(OverviewPanel, "Shield Accessory");
    GUIIcon  *ShBatIcon = (GUIIcon *)GUIControlByName(OverviewPanel, "Shield Battery");
    GUIIcon  *ShCapIcon = (GUIIcon *)GUIControlByName(OverviewPanel, "Shield Capacitor");
    GUIIcon  *ShBodIcon = (GUIIcon *)GUIControlByName(OverviewPanel, "Shield Body");
    
    GUILabel *ShNameLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Shield Name");
    GUILabel *ShCapLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Shield Capacity");
    GUILabel *ShCrgLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Shield Charge");
    GUILabel *ShDlyLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Shield Delay");
    
    GUILabel *CurStimLabel = (GUILabel *)GUIControlByName(OverviewPanel, "Current Stim");
    GUIBar *CurStimBar[STIM_MAX];
    for (int i = 0; i < STIM_MAX; i++)
    {
        CurStimBar[i] = (GUIBar *)GUIControlByName(OverviewPanel, StrParam("Stim Bar %d", i));
    }
    
    //-------------------------
    //Character
    //-------------------------
    
    NameLabel->Text = StrParam("%tS", PlayerNumber() + 1);
    LevelLabel->Text = StrParam("Level: %d", Player.Level);
    XPLabel->Text = StrParam("XP: %ld / %ld", Player.XP, Player.XPNext);
    TitleLabel->Text = StrParam("Title: %S (%d/%d)", Ranks[Player.RankLevel], Player.RankLevel, MAX_RANK);
    RankLabel->Text = StrParam("Rank: %ld / %ld", Player.Rank, Player.RankNext);
    if (Player.PayReady && !Player.PayingOut)
        PPLabel->Text = StrParam("PP: %d (%S) [\C[%S]Ready\C-]", Player.PP, FormatTime(Player.PayTimer), PayReadyColor);
    else
        PPLabel->Text = StrParam("PP: %d (%S)", Player.PP, FormatTime(Player.PayTimer));
    
    //-------------------------
    //Inventory
    //-------------------------
    
    ModuleLabel->Text = StrParam("%d", CheckInventory("DRPGModule"));
    TurretPartsLabel->Text = StrParam("%d", CheckInventory("DRPGTurretPart"));
    AugChargeLabel->Text = StrParam("%d%% / %d%%", (int)Player.Augs.Battery, (int)Player.Augs.BatteryMax);
    AugSlotsLabel->Text = StrParam("%d / %d", Player.Augs.SlotsUsed, Player.Augs.Slots);
    AugUpgradesLabel->Text = StrParam("%d / %d", CheckInventory("DRPGAugCanister"), CheckInventory("DRPGAugUpgradeCanister"));
    StimsLabel->Text = StrParam("S: %d\nM: %d\nL: %d\nXL: %d", CheckInventory("DRPGStimSmall"), CheckInventory("DRPGStimMedium"), CheckInventory("DRPGStimLarge"), CheckInventory("DRPGStimXL"));
    ChipsGoldLabel->Text = StrParam("%d", CheckInventory("DRPGChipGold"));
    ChipsPlatLabel->Text = StrParam("%d", CheckInventory("DRPGChipPlatinum"));
    InventoryLabel->Text = StrParam("Inventory: %d / %d\n\CaBullets: %d / %d\n\CiShells: %d / %d\n\CcRockets: %d / %d\n\CdCells: %d / %d",
                                    Player.InvItems, CheckInventoryMax(),
                                    CheckInventory("Clip"), GetAmmoCapacity("Clip"),
                                    CheckInventory("Shell"), GetAmmoCapacity("Shell"),
                                    CheckInventory("RocketAmmo"), GetAmmoCapacity("RocketAmmo"),
                                    CheckInventory("Cell"), GetAmmoCapacity("Cell"));
    
    //-------------------------
    //Map
    //-------------------------
    
    str MapType = "Standard Map";
    
    if (CurrentLevel->SecretMap)
        MapType = "Secret Map";
    if (CurrentLevel->UACBase)
        MapType = "UAC Base";
    if (CurrentLevel->UACArena)
        MapType = "UAC Arena";
    
    MapNameLabel->Text = StrParam("%S", CurrentLevel->NiceName);
    MapInfoLabel->Text = StrParam("%S, level %d - %S", CurrentLevel->LumpName, CurrentLevel->LevelNum, MapType);
    if (CurrentLevel->Par > 0)
        MapTimeLabel->Text = StrParam("Time: %S (Par: %S)", FormatTime(Timer()), FormatTime(CurrentLevel->Par * 35));
    else
        MapTimeLabel->Text = StrParam("Time: %S", FormatTime(Timer()));
    MapKillsLabel->Text = StrParam("Monsters: %d / %d", GetLevelInfo(LEVELINFO_KILLED_MONSTERS), GetLevelInfo(LEVELINFO_TOTAL_MONSTERS));
    MapItemsLabel->Text = StrParam("Items: %d / %d", GetLevelInfo(LEVELINFO_FOUND_ITEMS), GetLevelInfo(LEVELINFO_TOTAL_ITEMS));
    MapSecretsLabel->Text = StrParam("Secrets: %d / %d", GetLevelInfo(LEVELINFO_FOUND_SECRETS), GetLevelInfo(LEVELINFO_TOTAL_SECRETS));
    
    if (CurrentLevel && CurrentLevel->KillBonus)
        MapKillsLabel->Color = MenuCursorColor;
    else
        MapKillsLabel->Color = "Brick";
    if (CurrentLevel && CurrentLevel->ItemsBonus)
        MapItemsLabel->Color = MenuCursorColor;
    else
        MapItemsLabel->Color = "LightBlue";
    if (CurrentLevel && CurrentLevel->SecretsBonus)
        MapSecretsLabel->Color = MenuCursorColor;
    else
        MapSecretsLabel->Color = "Gold";
    
    if (CurrentLevel && !CurrentLevel->UACBase)
    {
        MapIcon->Control.Visible = true;
        MapNameLabel->Control.Visible = true;
        MapInfoLabel->Control.Visible = true;
        MapTimeLabel->Control.Visible = true;
        MapKillsLabel->Control.Visible = true;
        MapItemsLabel->Control.Visible = true;
        MapSecretsLabel->Control.Visible = true;
    }
    else
    {
        MapIcon->Control.Visible = false;
        MapNameLabel->Control.Visible = false;
        MapInfoLabel->Control.Visible = false;
        MapTimeLabel->Control.Visible = false;
        MapKillsLabel->Control.Visible = false;
        MapItemsLabel->Control.Visible = false;
        MapSecretsLabel->Control.Visible = false;
    }
    
    //-------------------------
    //Shield
    //-------------------------
    
    if (Player.Shield.Body != 0 || Player.Shield.Battery != 0 || Player.Shield.Capacitor != 0)
    {
        if (Player.Shield.Accessory)
        {
            ShAccIcon->Control.Visible = true;
            ShAccIcon->Texture = Player.Shield.Accessory->Icon;
        }
        else
            ShAccIcon->Control.Visible = false;
        
        if (Player.Shield.Battery)
        {
            ShBatIcon->Control.Visible = true;
            ShBatIcon->Texture = Player.Shield.Battery->Icon;
        }
        else
            ShBatIcon->Control.Visible = false;
        
        if (Player.Shield.Capacitor)
        {
            ShCapIcon->Control.Visible = true;
            ShCapIcon->Texture = Player.Shield.Capacitor->Icon;
        }
        else
            ShCapIcon->Control.Visible = false;
        
        if (Player.Shield.Body)
        {
            ShBodIcon->Control.Visible = true;
            ShBodIcon->Texture = Player.Shield.Body->Icon;
        }
        else
            ShBodIcon->Control.Visible = false;
        
        // Epic Shield Name
        str ShieldName = "";
        if (Player.Shield.Capacitor) ShieldName = StrParam("%S %S", ShieldName, Player.Shield.Capacitor->Name);
        if (Player.Shield.Battery)   ShieldName = StrParam("%S \C-%S", ShieldName, Player.Shield.Battery->Name);
        if (Player.Shield.Body)      ShieldName = StrParam("%S \C-%S", ShieldName, Player.Shield.Body->Name);
        if (Player.Shield.Accessory) ShieldName = StrParam("%S \C-%S", ShieldName, Player.Shield.Accessory->Name);
        ShieldName = StrParam("%S\C- Shield", ShieldName);
        ShNameLabel->Control.Visible = true;
        ShNameLabel->Text = StrParam("%S", ShieldName);
        
        ShCapLabel->Control.Visible = true;
        ShCapLabel->Text = StrParam(" \CvCapacity: %d / %d", Player.Shield.Charge, Player.Shield.Capacity);
        
        ShCrgLabel->Control.Visible = true;
        if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_KILLSCHARGE)
        {
            ShCrgLabel->Text = " \CgDoes not recharge automatically";
            ShDlyLabel->Control.Visible = false;
        }
        else
        {
            ShCrgLabel->Text = StrParam(" \CdCharge: %d", Player.Shield.ChargeRate);
            ShDlyLabel->Control.Visible = true;
            ShDlyLabel->Text = StrParam(" \CaDelay: %.2k", Player.Shield.DelayRate);
        }
    }
    else
    {
        ShAccIcon->Control.Visible = false;
        ShBatIcon->Control.Visible = false;
        ShCapIcon->Control.Visible = false;
        ShBodIcon->Control.Visible = false;
        
        ShNameLabel->Control.Visible = false;
        ShCapLabel->Control.Visible = false;
        ShCrgLabel->Control.Visible = false;
        ShDlyLabel->Control.Visible = false;
    }
    
    // --------------------------------------------------
    // Current Stim / Toxicity
    //
    
    if (Player.Stim.Size > 0)
    {
        CurStimLabel->Control.Visible = true;
        // Draw Stim selection
        switch (Player.Stim.Size)
        {
            case 1:
            {
                CurStimLabel->Text = StrParam("Small Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
        
            case 2:
            {
                CurStimLabel->Text = StrParam("Medium Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
            
            case 3:
            {
                CurStimLabel->Text = StrParam("Large Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
            
            case 4:
            {
                CurStimLabel->Text = StrParam("Extra-Large Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
        }
            
        int X = 0;
        for (int i = 0; i < STIM_MAX; i++)
        {
            CurStimBar[i]->Control.Visible = true;
            if (Player.Stim.Current[i] > 0)
            {
                CurStimBar[i]->Control.X = 326 + X;
                CurStimBar[i]->Value = Player.Stim.Current[i];
                X += Player.Stim.Current[i];
            }
        }
    }
    else
    {
        CurStimLabel->Control.Visible = false;
        for (int i = 0; i < STIM_MAX; i++)
        {
            CurStimBar[i]->Control.Visible = false;
        }
    }
    
    GUIUpdatePanelControls(OverviewPanel);
}