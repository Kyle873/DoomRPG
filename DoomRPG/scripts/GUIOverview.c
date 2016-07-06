#include "Defs.h"

#include "GUIOverview.h"
#include "GUI.h"
#include "Map.h"
#include "Menu.h"
#include "Stats.h"
#include "Stims.h"
#include "RPG.h"
#include "Utils.h"

struct
{
    GUIIcon *PlayerSpriteIcon;
    
    GUIIcon *ModuleIcon;
    GUIIcon *TurretPartsIcon;
    GUIIcon *AugChargeIcon;
    GUIIcon *AugSlotsIcon;
    GUIIcon *AugCanistersIcon;
    GUIIcon *AugUpgradesIcon;
    GUIIcon *StimsIcon;
    GUIIcon *ChipsGoldIcon;
    GUIIcon *ChipsPlatIcon;
    GUIIcon *InventoryIcon;
    
    GUIIcon *DRLAWeaponIcon;
    GUIIcon *DRLAArmorIcon;
    GUIIcon *DRLAModpackIcon;
    GUIIcon *DRLASkullIcon;
    GUIIcon *DRLADeviceIcon;
    
    GUIIcon *MapIcon;
    
    GUIIcon *ShAccIcon;
    GUIIcon *ShBatIcon;
    GUIIcon *ShCapIcon;
    GUIIcon *ShBodIcon;
} static GUIIcons;

struct
{
    GUILabel *NameLabel;
    GUILabel *LevelLabel;
    GUILabel *XPLabel;
    GUILabel *TitleLabel;
    GUILabel *RankLabel;
    GUILabel *PPLabel;
    
    GUILabel *ModuleLabel;
    GUILabel *TurretPartsLabel;
    GUILabel *AugChargeLabel;
    GUILabel *AugSlotsLabel;
    GUILabel *AugUpgradesLabel;
    GUILabel *StimsLabel;
    GUILabel *ChipsGoldLabel;
    GUILabel *ChipsPlatLabel;
    GUILabel *InventoryLabel;
    
    GUILabel *DRLALabel;
    
    GUILabel *MapNameLabel;
    GUILabel *MapInfoLabel;
    GUILabel *MapTimeLabel;
    GUILabel *MapKillsLabel;
    GUILabel *MapItemsLabel;
    GUILabel *MapSecretsLabel;
    
    GUILabel *ShNameLabel;
    GUILabel *ShCapLabel;
    GUILabel *ShCrgLabel;
    GUILabel *ShDlyLabel;
    
    GUILabel *CurStimLabel;
    
    GUILabel *ToxicityLabel;
    
    GUILabel *ToxicityRegenLabel;
    GUILabel *ToxicityEnergyLabel;
    GUILabel *ToxicitySpeedLabel;
} static GUILabels;

static GUIBar *CurStimBar[STIM_MAX];
static GUIBar *ToxicityBar[100];

// --------------------------------------------------
// GUI Panels
//

NamedScript void CreateOverviewPanel()
{
    GUIPanel *OverviewPanel = GUICreatePanel();
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Panel = OverviewPanel;
    
    OverviewPanel->Update = (PanelUpdateFunc)UpdateOverviewPanel;
    OverviewPanel->Close = (PanelCloseFunc)CloseOverviewPanel;
    
    int GUIElementID = GUI_CONTENTS_ID;
    
    // --------------------------------------------------
    // Player Sprite
    //
    
    str PlayerSprite = "PLAYA1";
    
    GUIIcons.PlayerSpriteIcon = GUIAddIcon(OverviewPanel, "Player Sprite");
    
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
    
    GUIIcons.PlayerSpriteIcon->Texture = PlayerSprite;
    GUIIcons.PlayerSpriteIcon->Control.X = 16;
    GUIIcons.PlayerSpriteIcon->Control.Y = 40;
    GUIIcons.PlayerSpriteIcon->Control.id = ++GUIElementID;
    
    // --------------------------------------------------
    // Player Info
    //
    
    GUILabels.NameLabel = GUIAddLabel(OverviewPanel, "Player Name");
    GUILabels.LevelLabel = GUIAddLabel(OverviewPanel, "Player Level");
    GUILabels.XPLabel = GUIAddLabel(OverviewPanel, "Player XP");
    GUILabels.TitleLabel = GUIAddLabel(OverviewPanel, "Player Rank Title");
    GUILabels.RankLabel = GUIAddLabel(OverviewPanel, "Player Rank");
    GUILabels.PPLabel = GUIAddLabel(OverviewPanel, "Player Payout Status");
    
    GUILabels.NameLabel->Control.X = 64;
    GUILabels.NameLabel->Control.Y = 16;
    GUILabels.NameLabel->Control.id = ++GUIElementID;
    GUILabels.NameLabel->Color = "White";
    GUILabels.NameLabel->Big = true;
    
    GUILabels.LevelLabel->Control.X = 64;
    GUILabels.LevelLabel->Control.Y = 28;
    GUILabels.LevelLabel->Control.id = ++GUIElementID;
    GUILabels.LevelLabel->Color = "White";
    GUILabels.LevelLabel->Big = true;
    
    GUILabels.XPLabel->Control.X = 64;
    GUILabels.XPLabel->Control.Y = 40;
    GUILabels.XPLabel->Control.id = ++GUIElementID;
    GUILabels.XPLabel->Color = "White";
    GUILabels.XPLabel->Big = true;
    
    GUILabels.TitleLabel->Control.X = 64;
    GUILabels.TitleLabel->Control.Y = 52;
    GUILabels.TitleLabel->Control.id = ++GUIElementID;
    GUILabels.TitleLabel->Color = "Yellow";
    GUILabels.TitleLabel->Big = true;
    
    GUILabels.RankLabel->Control.X = 64;
    GUILabels.RankLabel->Control.Y = 64;
    GUILabels.RankLabel->Control.id = ++GUIElementID;
    GUILabels.RankLabel->Color = "Yellow";
    GUILabels.RankLabel->Big = true;
    
    GUILabels.PPLabel->Control.X = 64;
    GUILabels.PPLabel->Control.Y = 76;
    GUILabels.PPLabel->Control.id = ++GUIElementID;
    GUILabels.PPLabel->Color = "Gold";
    GUILabels.PPLabel->Big = true;
    
    // --------------------------------------------------
    // Totals
    //
    
    
    GUIIcons.ModuleIcon = GUIAddIcon(OverviewPanel, "Module Icon");
    GUIIcons.TurretPartsIcon = GUIAddIcon(OverviewPanel, "Turret Parts Icon");
    GUIIcons.AugChargeIcon = GUIAddIcon(OverviewPanel, "Aug Charge icon");
    GUIIcons.AugSlotsIcon = GUIAddIcon(OverviewPanel, "Aug Slots Icon");
    GUIIcons.AugCanistersIcon = GUIAddIcon(OverviewPanel, "Aug Canisters Icon");
    GUIIcons.AugUpgradesIcon = GUIAddIcon(OverviewPanel, "Aug Upgrades Icon");
    GUIIcons.StimsIcon = GUIAddIcon(OverviewPanel, "Stims Icon");
    GUIIcons.ChipsGoldIcon = GUIAddIcon(OverviewPanel, "Gold Chips Icon");
    GUIIcons.ChipsPlatIcon = GUIAddIcon(OverviewPanel, "Platinum Chips Icon");
    GUIIcons.InventoryIcon = GUIAddIcon(OverviewPanel, "Inventory Icon");
    
    GUILabels.ModuleLabel = GUIAddLabel(OverviewPanel, "Module Count");
    GUILabels.TurretPartsLabel = GUIAddLabel(OverviewPanel, "Turret Part Count");
    GUILabels.AugChargeLabel = GUIAddLabel(OverviewPanel, "Aug Charge");
    GUILabels.AugSlotsLabel = GUIAddLabel(OverviewPanel, "Aug Slots");
    GUILabels.AugUpgradesLabel = GUIAddLabel(OverviewPanel, "Aug Upgrades");
    GUILabels.StimsLabel = GUIAddLabel(OverviewPanel, "Stim Counts");
    GUILabels.ChipsGoldLabel = GUIAddLabel(OverviewPanel, "Gold Chip Count");
    GUILabels.ChipsPlatLabel = GUIAddLabel(OverviewPanel, "Platinum Chip Count");
    GUILabels.InventoryLabel = GUIAddLabel(OverviewPanel, "Inventory Count");
    
    if (CompatMode == COMPAT_DRLA)
    {
        GUIIcons.DRLAWeaponIcon = GUIAddIcon(OverviewPanel, "DRLA Weapon Icon");
        GUIIcons.DRLAArmorIcon = GUIAddIcon(OverviewPanel, "DRLA Armor Icon");
        GUIIcons.DRLAModpackIcon = GUIAddIcon(OverviewPanel, "DRLA Modpack Icon");
        GUIIcons.DRLASkullIcon = GUIAddIcon(OverviewPanel, "DRLA Skull Icon");
        GUIIcons.DRLADeviceIcon = GUIAddIcon(OverviewPanel, "DRLA Device Icon");
        
        GUILabels.DRLALabel = GUIAddLabel(OverviewPanel, "DRLA Label");
        
        GUIIcons.DRLAWeaponIcon->Texture = "PISGX0";
        GUIIcons.DRLAWeaponIcon->Control.X = 14 - 4;
        GUIIcons.DRLAWeaponIcon->Control.Y = 466 - 16;
        GUIIcons.DRLAWeaponIcon->Control.id = ++GUIElementID;
        
        GUIIcons.DRLAArmorIcon->Texture = "HARMOR";
        GUIIcons.DRLAArmorIcon->Control.X = 44 - 16;
        GUIIcons.DRLAArmorIcon->Control.Y = 468 - 30;
        GUIIcons.DRLAArmorIcon->Control.id = ++GUIElementID;
        
        GUIIcons.DRLAModpackIcon->Texture = "GMODICON";
        GUIIcons.DRLAModpackIcon->Control.X = 18 - 16;
        GUIIcons.DRLAModpackIcon->Control.Y = 488 - 30;
        GUIIcons.DRLAModpackIcon->Control.id = ++GUIElementID;
        
        GUIIcons.DRLASkullIcon->Texture = "ISKLC0";
        GUIIcons.DRLASkullIcon->Control.X = 44 - 6;
        GUIIcons.DRLASkullIcon->Control.Y = 486 - 10;
        GUIIcons.DRLASkullIcon->Control.id = ++GUIElementID;
        
        GUIIcons.DRLADeviceIcon->Texture = "PHS1I0";
        GUIIcons.DRLADeviceIcon->Control.X = 32 - 24;
        GUIIcons.DRLADeviceIcon->Control.Y = 506 - 30;
        GUIIcons.DRLADeviceIcon->Control.id = ++GUIElementID;
        
        GUILabels.DRLALabel->Control.X = 84;
        GUILabels.DRLALabel->Control.Y = 500;
        GUILabels.DRLALabel->Control.id = ++GUIElementID;
        GUILabels.DRLALabel->Color = "White";
        GUILabels.DRLALabel->Big = true;
    }
    
    GUIIcons.ModuleIcon->Texture = "UMODA0";
    GUIIcons.ModuleIcon->Control.X = 24;
    GUIIcons.ModuleIcon->Control.Y = 96;
    GUIIcons.ModuleIcon->Control.id = ++GUIElementID;
    
    GUIIcons.TurretPartsIcon->Texture = "TPRTA0";
    GUIIcons.TurretPartsIcon->Control.X = 24;
    GUIIcons.TurretPartsIcon->Control.Y = 128;
    GUIIcons.TurretPartsIcon->Control.id = ++GUIElementID;
    
    GUIIcons.AugChargeIcon->Texture = "AUGBATT";
    GUIIcons.AugChargeIcon->Control.X = 24;
    GUIIcons.AugChargeIcon->Control.Y = 148;
    GUIIcons.AugChargeIcon->Control.id = ++GUIElementID;
    
    GUIIcons.AugSlotsIcon->Texture = "AUGUB0";
    GUIIcons.AugSlotsIcon->Control.X = 24;
    GUIIcons.AugSlotsIcon->Control.Y = 178;
    GUIIcons.AugSlotsIcon->Control.id = ++GUIElementID;
    
    GUIIcons.AugCanistersIcon->Texture = "AUGCA0";
    GUIIcons.AugCanistersIcon->Control.X = 16;
    GUIIcons.AugCanistersIcon->Control.Y = 204;
    GUIIcons.AugCanistersIcon->Control.id = ++GUIElementID;
    
    GUIIcons.AugUpgradesIcon->Texture = "AUGUA0";
    GUIIcons.AugUpgradesIcon->Control.X = 32;
    GUIIcons.AugUpgradesIcon->Control.Y = 198;
    GUIIcons.AugUpgradesIcon->Control.id = ++GUIElementID;
    
    GUIIcons.StimsIcon->Texture = "STIMB0";
    GUIIcons.StimsIcon->Control.X = 24;
    GUIIcons.StimsIcon->Control.Y = 248;
    GUIIcons.StimsIcon->Control.id = ++GUIElementID;
    
    GUIIcons.ChipsGoldIcon->Texture = "CHIPGOLD";
    GUIIcons.ChipsGoldIcon->Control.X = 8;
    GUIIcons.ChipsGoldIcon->Control.Y = 268;
    GUIIcons.ChipsGoldIcon->Control.id = ++GUIElementID;
    
    GUIIcons.ChipsPlatIcon->Texture = "CHIPPLAT";
    GUIIcons.ChipsPlatIcon->Control.X = 8;
    GUIIcons.ChipsPlatIcon->Control.Y = 304;
    GUIIcons.ChipsPlatIcon->Control.id = ++GUIElementID;
    
    GUIIcons.InventoryIcon->Texture = "GPAKA0";
    GUIIcons.InventoryIcon->Control.X = 24;
    GUIIcons.InventoryIcon->Control.Y = 396;
    GUIIcons.InventoryIcon->Control.id = ++GUIElementID;
    
    GUILabels.ModuleLabel->Control.X = 84;
    GUILabels.ModuleLabel->Control.Y = 116;
    GUILabels.ModuleLabel->Control.id = ++GUIElementID;
    GUILabels.ModuleLabel->Color = "Green";
    GUILabels.ModuleLabel->Big = true;
    
    GUILabels.TurretPartsLabel->Control.X = 84;
    GUILabels.TurretPartsLabel->Control.Y = 148;
    GUILabels.TurretPartsLabel->Control.id = ++GUIElementID;
    GUILabels.TurretPartsLabel->Color = "White";
    GUILabels.TurretPartsLabel->Big = true;
    
    GUILabels.AugChargeLabel->Control.X = 84;
    GUILabels.AugChargeLabel->Control.Y = 180;
    GUILabels.AugChargeLabel->Control.id = ++GUIElementID;
    GUILabels.AugChargeLabel->Color = "Yellow";
    GUILabels.AugChargeLabel->Big = true;
    
    GUILabels.AugSlotsLabel->Control.X = 84;
    GUILabels.AugSlotsLabel->Control.Y = 200;
    GUILabels.AugSlotsLabel->Control.id = ++GUIElementID;
    GUILabels.AugSlotsLabel->Color = "Green";
    GUILabels.AugSlotsLabel->Big = true;
    
    GUILabels.AugUpgradesLabel->Control.X = 84;
    GUILabels.AugUpgradesLabel->Control.Y = 224;
    GUILabels.AugUpgradesLabel->Control.id = ++GUIElementID;
    GUILabels.AugUpgradesLabel->Color = "Green";
    GUILabels.AugUpgradesLabel->Big = true;
    
    GUILabels.StimsLabel->Control.X = 84;
    GUILabels.StimsLabel->Control.Y = 264;
    GUILabels.StimsLabel->Control.id = ++GUIElementID;
    GUILabels.StimsLabel->Color = "White";
    GUILabels.StimsLabel->Big = true;
    
    GUILabels.ChipsGoldLabel->Control.X = 84;
    GUILabels.ChipsGoldLabel->Control.Y = 314;
    GUILabels.ChipsGoldLabel->Control.id = ++GUIElementID;
    GUILabels.ChipsGoldLabel->Color = "Gold";
    GUILabels.ChipsGoldLabel->Big = true;
    
    GUILabels.ChipsPlatLabel->Control.X = 84;
    GUILabels.ChipsPlatLabel->Control.Y = 350;
    GUILabels.ChipsPlatLabel->Control.id = ++GUIElementID;
    GUILabels.ChipsPlatLabel->Color = "White";
    GUILabels.ChipsPlatLabel->Big = true;
    
    GUILabels.InventoryLabel->Control.X = 84;
    GUILabels.InventoryLabel->Control.Y = 412;
    GUILabels.InventoryLabel->Control.id = ++GUIElementID;
    GUILabels.InventoryLabel->Color = "White";
    GUILabels.InventoryLabel->Big = true;
    
    // --------------------------------------------------
    // Map Stats
    //
    
    GUIIcons.MapIcon = GUIAddIcon(OverviewPanel, "Map Icon");
    
    GUILabels.MapNameLabel = GUIAddLabel(OverviewPanel, "Map Name");
    GUILabels.MapInfoLabel = GUIAddLabel(OverviewPanel, "Map Info");
    GUILabels.MapTimeLabel = GUIAddLabel(OverviewPanel, "Map Time");
    GUILabels.MapKillsLabel = GUIAddLabel(OverviewPanel, "Map Kills");
    GUILabels.MapItemsLabel = GUIAddLabel(OverviewPanel, "Map Items");
    GUILabels.MapSecretsLabel = GUIAddLabel(OverviewPanel, "Map Secrets");
    
    GUIIcons.MapIcon->Texture = "PMAPA0";
    GUIIcons.MapIcon->Control.X = 284;
    GUIIcons.MapIcon->Control.Y = 96;
    GUIIcons.MapIcon->Control.id = ++GUIElementID;
    
    GUILabels.MapNameLabel->Control.X = 328;
    GUILabels.MapNameLabel->Control.Y = 110;
    GUILabels.MapNameLabel->Control.id = ++GUIElementID;
    GUILabels.MapNameLabel->Color = "White";
    GUILabels.MapNameLabel->Big = true;
    
    GUILabels.MapInfoLabel->Control.X = 328;
    GUILabels.MapInfoLabel->Control.Y = 122;
    GUILabels.MapInfoLabel->Control.id = ++GUIElementID;
    GUILabels.MapInfoLabel->Color = "Green";
    GUILabels.MapInfoLabel->Big = true;
    
    GUILabels.MapTimeLabel->Control.X = 328;
    GUILabels.MapTimeLabel->Control.Y = 134;
    GUILabels.MapTimeLabel->Control.id = ++GUIElementID;
    GUILabels.MapTimeLabel->Color = "Orange";
    GUILabels.MapTimeLabel->Big = true;
    
    GUILabels.MapKillsLabel->Control.X = 328;
    GUILabels.MapKillsLabel->Control.Y = 146;
    GUILabels.MapKillsLabel->Control.id = ++GUIElementID;
    GUILabels.MapKillsLabel->Big = true;
    
    GUILabels.MapItemsLabel->Control.X = 328;
    GUILabels.MapItemsLabel->Control.Y = 158;
    GUILabels.MapItemsLabel->Control.id = ++GUIElementID;
    GUILabels.MapItemsLabel->Big = true;
    
    GUILabels.MapSecretsLabel->Control.X = 328;
    GUILabels.MapSecretsLabel->Control.Y = 170;
    GUILabels.MapSecretsLabel->Control.id = ++GUIElementID;
    GUILabels.MapSecretsLabel->Big = true;
    
    // --------------------------------------------------
    // Shield
    //
    GUIIcons.ShAccIcon = GUIAddIcon(OverviewPanel, "Shield Accessory");
    GUIIcons.ShBatIcon = GUIAddIcon(OverviewPanel, "Shield Battery");
    GUIIcons.ShCapIcon = GUIAddIcon(OverviewPanel, "Shield Capacitor");
    GUIIcons.ShBodIcon = GUIAddIcon(OverviewPanel, "Shield Body");
    
    GUIIcons.ShAccIcon->Texture = "SHA2A0";
    GUIIcons.ShAccIcon->Control.X = 286;
    GUIIcons.ShAccIcon->Control.Y = 205;
    GUIIcons.ShAccIcon->Control.id = ++GUIElementID;
    
    GUIIcons.ShBatIcon->Texture = "SHBAA0";
    GUIIcons.ShBatIcon->Control.X = 286;
    GUIIcons.ShBatIcon->Control.Y = 205;
    GUIIcons.ShBatIcon->Control.id = ++GUIElementID;
    
    GUIIcons.ShCapIcon->Texture = "SHCAA0";
    GUIIcons.ShCapIcon->Control.X = 286;
    GUIIcons.ShCapIcon->Control.Y = 205;
    GUIIcons.ShCapIcon->Control.id = ++GUIElementID;
    
    GUIIcons.ShBodIcon->Texture = "SHBOA0";
    GUIIcons.ShBodIcon->Control.X = 286;
    GUIIcons.ShBodIcon->Control.Y = 205;
    GUIIcons.ShBodIcon->Control.id = ++GUIElementID;
    
    GUILabels.ShNameLabel = GUIAddLabel(OverviewPanel, "Shield Name");
    GUILabels.ShCapLabel = GUIAddLabel(OverviewPanel, "Shield Capacity");
    GUILabels.ShCrgLabel = GUIAddLabel(OverviewPanel, "Shield Charge");
    GUILabels.ShDlyLabel = GUIAddLabel(OverviewPanel, "Shield Delay");
    
    GUILabels.ShNameLabel->Control.X = 324;
    GUILabels.ShNameLabel->Control.Y = 210;
    GUILabels.ShNameLabel->Control.id = ++GUIElementID;
    GUILabels.ShNameLabel->Color = "White";
    
    GUILabels.ShCapLabel->Control.X = 324;
    GUILabels.ShCapLabel->Control.Y = 218;
    GUILabels.ShCapLabel->Control.id = ++GUIElementID;
    GUILabels.ShCapLabel->Color = "White";
    
    GUILabels.ShCrgLabel->Control.X = 324;
    GUILabels.ShCrgLabel->Control.Y = 226;
    GUILabels.ShCrgLabel->Control.id = ++GUIElementID;
    GUILabels.ShCrgLabel->Color = "White";
    
    GUILabels.ShDlyLabel->Control.X = 324;
    GUILabels.ShDlyLabel->Control.Y = 234;
    GUILabels.ShDlyLabel->Control.id = ++GUIElementID;
    GUILabels.ShDlyLabel->Color = "White";
    
    // --------------------------------------------------
    // Current Stim / Toxicity
    //
    
    GUILabels.CurStimLabel = GUIAddLabel(OverviewPanel, "Current Stim");
    GUILabels.CurStimLabel->Control.X = 324;
    GUILabels.CurStimLabel->Control.Y = 260;
    GUILabels.CurStimLabel->Control.id = ++GUIElementID;
    GUILabels.CurStimLabel->Color = "Green";
    GUILabels.CurStimLabel->Big = true;
    
    GUITooltip *CurStimTooltip = GUICreateTooltip();
    CurStimTooltip->Type = TT_TITLE;
    CurStimTooltip->Title = "";
    CurStimTooltip->Text = "";
    
    for (int i = 0; i < STIM_MAX; i++)
    {
        CurStimBar[i] = GUIAddBar(OverviewPanel, StrParam("Stim Bar %d", i));
       
        CurStimBar[i]->Control.X = 326;
        CurStimBar[i]->Control.Y = 270;
        CurStimBar[i]->Control.id = ++GUIElementID;
        CurStimBar[i]->Texture = StrParam("Stim%d", i + 1);
        CurStimBar[i]->ValueMax = 100;
        CurStimBar[i]->Control.Tooltip = CurStimTooltip;
        
        GUIElementID = GUIElementID + 100;
    }    
    
    GUILabels.ToxicityLabel = GUIAddLabel(OverviewPanel, "Toxicity");
    GUILabels.ToxicityLabel->Control.X = 324;
    GUILabels.ToxicityLabel->Control.Y = 300;
    GUILabels.ToxicityLabel->Control.id = ++GUIElementID;
    GUILabels.ToxicityLabel->Color = "Green";
    GUILabels.ToxicityLabel->Big = true;
    
    for (int i = 0; i < sizeof(ToxicityBar); i++)
    {
        ToxicityBar[i] = GUIAddBar(OverviewPanel, StrParam("Toxicity Bar %d", i));
        ToxicityBar[i]->Control.X = 335 + i;
        ToxicityBar[i]->Control.Y = 305;
        ToxicityBar[i]->Control.id = TOXMETER_ID + i;
        ToxicityBar[i]->Texture = StrParam("PGreen");
        ToxicityBar[i]->Value = 1;
        ToxicityBar[i]->ValueMax = 1;
        ToxicityBar[i]->Type = GUI_BAR_FADE;
        ToxicityBar[i]->FadeLength = 1.0;
    }
    
    GUILabels.ToxicityRegenLabel = GUIAddLabel(OverviewPanel, "Toxicity Regen");
    GUILabels.ToxicityEnergyLabel = GUIAddLabel(OverviewPanel, "Toxicity Energy");
    GUILabels.ToxicitySpeedLabel = GUIAddLabel(OverviewPanel, "Toxicity Speed");
    
    GUILabels.ToxicityRegenLabel->Control.X = 450;
    GUILabels.ToxicityRegenLabel->Control.Y = 314;
    GUILabels.ToxicityRegenLabel->Control.id = ++GUIElementID;
    GUILabels.ToxicityRegenLabel->Color = "Brick";
    GUILabels.ToxicityRegenLabel->Text = "- No Regeneration";
    
    
    GUILabels.ToxicityEnergyLabel->Control.X = 450;
    GUILabels.ToxicityEnergyLabel->Control.Y = 322;
    GUILabels.ToxicityEnergyLabel->Control.id = ++GUIElementID;
    GUILabels.ToxicityEnergyLabel->Color = "Brick";
    GUILabels.ToxicityEnergyLabel->Text = "- Energy Loss";
    
    GUILabels.ToxicitySpeedLabel->Control.X = 450;
    GUILabels.ToxicitySpeedLabel->Control.Y = 330;
    GUILabels.ToxicitySpeedLabel->Control.id = ++GUIElementID;
    GUILabels.ToxicitySpeedLabel->Color = "Brick";
    GUILabels.ToxicitySpeedLabel->Text = "- Reduced Movement Speed";
    
}

NamedScript void UpdateOverviewPanel(GUIPanel *OverviewPanel)
{
    //-------------------------
    //Character
    //-------------------------
    
    GUILabels.NameLabel->Text = StrParam("%tS", PlayerNumber() + 1);
    GUILabels.LevelLabel->Text = StrParam("Level: %d", Player.Level);
    GUILabels.XPLabel->Text = StrParam("XP: %ld / %ld", Player.XP, Player.XPNext);
    GUILabels.TitleLabel->Text = StrParam("Title: %S (%d/%d)", Ranks[Player.RankLevel], Player.RankLevel, MAX_RANK);
    GUILabels.RankLabel->Text = StrParam("Rank: %ld / %ld", Player.Rank, Player.RankNext);
    if (Player.PayReady && !Player.PayingOut)
        GUILabels.PPLabel->Text = StrParam("PP: %d (%S) [\C[%S]Ready\C-]", Player.PP, FormatTime(Player.PayTimer), PayReadyColor);
    else
        GUILabels.PPLabel->Text = StrParam("PP: %d (%S)", Player.PP, FormatTime(Player.PayTimer));
    
    //-------------------------
    //Inventory
    //-------------------------
    
    GUILabels.ModuleLabel->Text = StrParam("%d", CheckInventory("DRPGModule"));
    GUILabels.TurretPartsLabel->Text = StrParam("%d", CheckInventory("DRPGTurretPart"));
    GUILabels.AugChargeLabel->Text = StrParam("%d%% / %d%%", (int)Player.Augs.Battery, (int)Player.Augs.BatteryMax);
    GUILabels.AugSlotsLabel->Text = StrParam("%d / %d", Player.Augs.SlotsUsed, Player.Augs.Slots);
    GUILabels.AugUpgradesLabel->Text = StrParam("%d / %d", CheckInventory("DRPGAugCanister"), CheckInventory("DRPGAugUpgradeCanister"));
    GUILabels.StimsLabel->Text = StrParam("S: %d\nM: %d\nL: %d\nXL: %d", CheckInventory("DRPGStimSmall"), CheckInventory("DRPGStimMedium"), CheckInventory("DRPGStimLarge"), CheckInventory("DRPGStimXL"));
    GUILabels.ChipsGoldLabel->Text = StrParam("%d", CheckInventory("DRPGChipGold"));
    GUILabels.ChipsPlatLabel->Text = StrParam("%d", CheckInventory("DRPGChipPlatinum"));
    GUILabels.InventoryLabel->Text = StrParam("Inventory: %d / %d\n\CaBullets: %d / %d\n\CiShells: %d / %d\n\CcRockets: %d / %d\n\CdCells: %d / %d",
                                    Player.InvItems, CheckInventoryMax(),
                                    CheckInventory("Clip"), GetAmmoCapacity("Clip"),
                                    CheckInventory("Shell"), GetAmmoCapacity("Shell"),
                                    CheckInventory("RocketAmmo"), GetAmmoCapacity("RocketAmmo"),
                                    CheckInventory("Cell"), GetAmmoCapacity("Cell"));


    //-----------------------------
    //DRLA Inventory
    //
    
    if (CompatMode == COMPAT_DRLA)
    {
        int IsTechnician = (PlayerClass(PlayerNumber()) == 2);
        int Weapons = CheckInventory("RLWeaponLimit");
        int Armors = CheckInventory("RLArmorInInventory");
        int ModPacks = (IsTechnician ? CheckInventory("RLScavengerModLimit") : CheckInventory("RLModLimit"));
        int Skulls = CheckInventory("RLSkullLimit");
        int Devices = CheckInventory("RLPhaseDeviceLimit");
        
        GUILabels.DRLALabel->Text = StrParam("DRLA Inventory:\n%SWeapons: %d / 6\n%SArmor: %d / %d\n%SModpacks: %d / %d\n%SSkulls: %d / %d\n%SDevices: %d / %d",
            (Weapons >= 6 ? "\Cf" : "\Ca"), Weapons,
            (Armors >= DRLA_ARMOR_MAX ? "\Cf" : "\Cd"), Armors, DRLA_ARMOR_MAX,
            (((!IsTechnician && ModPacks >= 4) || (IsTechnician && ModPacks >= 8)) ? "\Cf" : "\Cc"),
            ModPacks, (IsTechnician ? 8 : 4),
            (Skulls >= DRLA_SKULL_MAX ? "\Cf" : "\Cr"), Skulls, DRLA_SKULL_MAX,
            (Devices >= DRLA_DEVICE_MAX ? "\Cf" : "\Ct"), Devices, DRLA_DEVICE_MAX);
    }
    
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
    
    GUILabels.MapNameLabel->Text = CurrentLevel->NiceName;
    GUILabels.MapInfoLabel->Text = StrParam("%S, level %d - %S", CurrentLevel->LumpName, CurrentLevel->LevelNum, MapType);
    if (CurrentLevel->Par > 0)
        GUILabels.MapTimeLabel->Text = StrParam("Time: %S (Par: %S)", FormatTime(Timer()), FormatTime(CurrentLevel->Par * 35));
    else
        GUILabels.MapTimeLabel->Text = StrParam("Time: %S", FormatTime(Timer()));
    GUILabels.MapKillsLabel->Text = StrParam("Monsters: %d / %d", GetLevelInfo(LEVELINFO_KILLED_MONSTERS), GetLevelInfo(LEVELINFO_TOTAL_MONSTERS));
    GUILabels.MapItemsLabel->Text = StrParam("Items: %d / %d", GetLevelInfo(LEVELINFO_FOUND_ITEMS), GetLevelInfo(LEVELINFO_TOTAL_ITEMS));
    GUILabels.MapSecretsLabel->Text = StrParam("Secrets: %d / %d", GetLevelInfo(LEVELINFO_FOUND_SECRETS), GetLevelInfo(LEVELINFO_TOTAL_SECRETS));
    
    if (CurrentLevel && CurrentLevel->KillBonus)
        GUILabels.MapKillsLabel->Color = MenuCursorColor;
    else
        GUILabels.MapKillsLabel->Color = "Brick";
    if (CurrentLevel && CurrentLevel->ItemsBonus)
        GUILabels.MapItemsLabel->Color = MenuCursorColor;
    else
        GUILabels.MapItemsLabel->Color = "LightBlue";
    if (CurrentLevel && CurrentLevel->SecretsBonus)
        GUILabels.MapSecretsLabel->Color = MenuCursorColor;
    else
        GUILabels.MapSecretsLabel->Color = "Gold";
    
    if (CurrentLevel && !CurrentLevel->UACBase)
    {
        GUIIcons.MapIcon->Control.Visible = true;
        GUILabels.MapNameLabel->Control.Visible = true;
        GUILabels.MapInfoLabel->Control.Visible = true;
        GUILabels.MapTimeLabel->Control.Visible = true;
        GUILabels.MapKillsLabel->Control.Visible = true;
        GUILabels.MapItemsLabel->Control.Visible = true;
        GUILabels.MapSecretsLabel->Control.Visible = true;
    }
    else
    {
        GUIIcons.MapIcon->Control.Visible = false;
        GUILabels.MapNameLabel->Control.Visible = false;
        GUILabels.MapInfoLabel->Control.Visible = false;
        GUILabels.MapTimeLabel->Control.Visible = false;
        GUILabels.MapKillsLabel->Control.Visible = false;
        GUILabels.MapItemsLabel->Control.Visible = false;
        GUILabels.MapSecretsLabel->Control.Visible = false;
    }
    
    //-------------------------
    //Shield
    //-------------------------
    
    if (Player.Shield.Body != 0 || Player.Shield.Battery != 0 || Player.Shield.Capacitor != 0)
    {
        if (Player.Shield.Accessory)
        {
            GUIIcons.ShAccIcon->Control.Visible = true;
            GUIIcons.ShAccIcon->Texture = Player.Shield.Accessory->Icon;
        }
        else
            GUIIcons.ShAccIcon->Control.Visible = false;
        
        if (Player.Shield.Battery)
        {
            GUIIcons.ShBatIcon->Control.Visible = true;
            GUIIcons.ShBatIcon->Texture = Player.Shield.Battery->Icon;
        }
        else
            GUIIcons.ShBatIcon->Control.Visible = false;
        
        if (Player.Shield.Capacitor)
        {
            GUIIcons.ShCapIcon->Control.Visible = true;
            GUIIcons.ShCapIcon->Texture = Player.Shield.Capacitor->Icon;
        }
        else
            GUIIcons.ShCapIcon->Control.Visible = false;
        
        if (Player.Shield.Body)
        {
            GUIIcons.ShBodIcon->Control.Visible = true;
            GUIIcons.ShBodIcon->Texture = Player.Shield.Body->Icon;
        }
        else
            GUIIcons.ShBodIcon->Control.Visible = false;
        
        // Epic Shield Name
        str ShieldName = "";
        if (Player.Shield.Capacitor) ShieldName = StrParam("%S %S", ShieldName, Player.Shield.Capacitor->Name);
        if (Player.Shield.Battery)   ShieldName = StrParam("%S \C-%S", ShieldName, Player.Shield.Battery->Name);
        if (Player.Shield.Body)      ShieldName = StrParam("%S \C-%S", ShieldName, Player.Shield.Body->Name);
        if (Player.Shield.Accessory) ShieldName = StrParam("%S \C-%S", ShieldName, Player.Shield.Accessory->Name);
        ShieldName = StrParam("%S\C- Shield", ShieldName);
        GUILabels.ShNameLabel->Control.Visible = true;
        GUILabels.ShNameLabel->Text = StrParam("%S", ShieldName);
        
        GUILabels.ShCapLabel->Control.Visible = true;
        GUILabels.ShCapLabel->Text = StrParam(" \CvCapacity: %d / %d", Player.Shield.Charge, Player.Shield.Capacity);
        
        GUILabels.ShCrgLabel->Control.Visible = true;
        if (Player.Shield.Accessory && Player.Shield.Accessory->PassiveEffect == SHIELD_PASS_KILLSCHARGE)
        {
            GUILabels.ShCrgLabel->Text = " \CgDoes not recharge automatically";
            GUILabels.ShDlyLabel->Control.Visible = false;
        }
        else
        {
            GUILabels.ShCrgLabel->Text = StrParam(" \CdCharge: %d", Player.Shield.ChargeRate);
            GUILabels.ShDlyLabel->Control.Visible = true;
            GUILabels.ShDlyLabel->Text = StrParam(" \CaDelay: %.2k", Player.Shield.DelayRate);
        }
    }
    else
    {
        GUIIcons.ShAccIcon->Control.Visible = false;
        GUIIcons.ShBatIcon->Control.Visible = false;
        GUIIcons.ShCapIcon->Control.Visible = false;
        GUIIcons.ShBodIcon->Control.Visible = false;
        
        GUILabels.ShNameLabel->Control.Visible = false;
        GUILabels.ShCapLabel->Control.Visible = false;
        GUILabels.ShCrgLabel->Control.Visible = false;
        GUILabels.ShDlyLabel->Control.Visible = false;
    }
    
    // --------------------------------------------------
    // Current Stim
    //
    
    if (Player.Stim.Size > 0)
    {
        GUILabels.CurStimLabel->Control.Visible = true;
        // Draw Stim selection
        switch (Player.Stim.Size)
        {
            case 1:
            {
                GUILabels.CurStimLabel->Text = StrParam("Small Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
        
            case 2:
            {
                GUILabels.CurStimLabel->Text = StrParam("Medium Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
            
            case 3:
            {
                GUILabels.CurStimLabel->Text = StrParam("Large Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
                break;
            }
            
            case 4:
            {
                GUILabels.CurStimLabel->Text = StrParam("Extra-Large Stim: %d/%d", Player.Stim.Amount, Player.Stim.Capacity);
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
        
        CurStimBar[0]->Control.Tooltip->Title = StrParam("\CdToxicity: +%d%%", Player.Stim.Toxicity);
        str CompoundString = "";
        for (int i = 0; i < STIM_MAX; i++)
        {
            if(Player.Stim.Current[i] > 0)
            {
                CompoundString = StrParam("%S%S%S: \Cl%d\n", CompoundString, ColorCodeFromName(CompoundColors[i]), CompoundNames[i], Player.Stim.Current[i]);
            }
        }
        CurStimBar[0]->Control.Tooltip->Text = CompoundString;
    }
    else
    {
        GUILabels.CurStimLabel->Control.Visible = false;
        for (int i = 0; i < STIM_MAX; i++)
        {
            CurStimBar[i]->Control.Visible = false;
        }
    }
    
    // --------------------------------------------------
    //Toxicity
    //
    
    if (Player.Toxicity > 0 || Player.Stim.Size > 0)
    {
        GUILabels.ToxicityLabel->Control.Visible = true;
        GUILabels.ToxicityLabel->Text = StrParam("Toxicity: %d%%", Player.Toxicity);
        
        for (int i = 0; i < sizeof(ToxicityBar); i++)
        {
            ToxicityBar[i]->Control.Visible = true;
        }
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
        int ID = Player.ToxicTimer % 100;
        ToxicityBar[ID]->Texture = Color;
        if (Player.Toxicity >= 100)
            ToxicityBar[ID]->Control.Y = 305 + 16;
        else
            ToxicityBar[ID]->Control.Y = 305 + 16 + Player.ToxicOffset;
        ToxicityBar[ID]->FadePrint = true;
    }
    else
    {
        GUILabels.ToxicityLabel->Control.Visible = false;
        for (int i = 0; i < sizeof(ToxicityBar); i++)
        {
            ToxicityBar[i]->Control.Visible = false;
        }
    }
    
    if (GetActivatorCVar("drpg_menuhelp"))
    {
        GUILabels.ToxicityRegenLabel->Control.Visible = Player.Toxicity >= 25;
        GUILabels.ToxicityEnergyLabel->Control.Visible = Player.Toxicity >= 50;
        GUILabels.ToxicitySpeedLabel->Control.Visible = Player.Toxicity >= 75;
    }
    else
    {
        GUILabels.ToxicityRegenLabel->Control.Visible = false;
        GUILabels.ToxicityEnergyLabel->Control.Visible = false;
        GUILabels.ToxicitySpeedLabel->Control.Visible = false;
    }
    
    GUIUpdatePanelControls(OverviewPanel);
}

NamedScript void CloseOverviewPanel(GUIPanel *OverviewPanel)
{
    ClearToxicityMeter();
}
