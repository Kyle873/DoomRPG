#include "Defs.h"

#include "GUIStats.h"
#include "GUI.h"
#include "Menu.h"
#include "Stats.h"
#include "RPG.h"
#include "Utils.h"

struct
{
    GUIIcon *ModulesIcon;
    
    GUIIcon *StrengthIcon;
    GUIIcon *StrLvlDnIcon;
    GUIIcon *StrLvlUpIcon;
    GUIIcon *DefenseIcon;
    GUIIcon *DefLvlDnIcon;
    GUIIcon *DefLvlUpIcon;
    GUIIcon *VitalityIcon;
    GUIIcon *VitLvlDnIcon;
    GUIIcon *VitLvlUpIcon;
    GUIIcon *EnergyIcon;
    GUIIcon *EngLvlDnIcon;
    GUIIcon *EngLvlUpIcon;
    GUIIcon *RegenIcon;
    GUIIcon *RgnLvlDnIcon;
    GUIIcon *RgnLvlUpIcon;
    GUIIcon *AgilityIcon;
    GUIIcon *AglLvlDnIcon;
    GUIIcon *AglLvlUpIcon;
    GUIIcon *CapacityIcon;
    GUIIcon *CapLvlDnIcon;
    GUIIcon *CapLvlUpIcon;
    GUIIcon *LuckIcon;
    GUIIcon *LckLvlDnIcon;
    GUIIcon *LckLvlUpIcon;
} static GUIIcons;

struct
{
    GUILabel *ModulesLabel;
    
    GUILabel *StrengthLabel;
    GUILabel *StrGenLabel;
    GUILabel *DefenseLabel;
    GUILabel *DefGenLabel;
    GUILabel *VitalityLabel;
    GUILabel *VitGenLabel;
    GUILabel *EnergyLabel;
    GUILabel *EngGenLabel;
    GUILabel *RegenLabel;
    GUILabel *RgnGenLabel;
    GUILabel *AgilityLabel;
    GUILabel *AglGenLabel;
    GUILabel *CapacityLabel;
    GUILabel *CapGenLabel;
    GUILabel *LuckLabel;
    GUILabel *LckGenLabel;
} static GUILabels;

struct
{
    GUIBar *StrXPBar;
    GUIBar *StrXPBGBar;
    GUIBar *DefXPBar;
    GUIBar *DefXPBGBar;
    GUIBar *VitXPBar;
    GUIBar *VitXPBGBar;
    GUIBar *EngXPBar;
    GUIBar *EngXPBGBar;
    GUIBar *RgnXPBar;
    GUIBar *RgnXPBGBar;
    GUIBar *AglXPBar;
    GUIBar *AglXPBGBar;
    GUIBar *CapXPBar;
    GUIBar *CapXPBGBar;
    GUIBar *LckXPBar;
    GUIBar *LckXPBGBar;
} static GUIBars;

struct
{
    GUIButton *StrLvlMaxButton;
    GUIButton *StrDtlButton;
    GUIButton *DefLvlMaxButton;
    GUIButton *DefDtlButton;
    GUIButton *VitLvlMaxButton;
    GUIButton *VitDtlButton;
    GUIButton *EngLvlMaxButton;
    GUIButton *EngDtlButton;
    GUIButton *RgnLvlMaxButton;
    GUIButton *RgnDtlButton;
    GUIButton *AglLvlMaxButton;
    GUIButton *AglDtlButton;
    GUIButton *CapLvlMaxButton;
    GUIButton *CapDtlButton;
    GUIButton *LckLvlMaxButton;
    GUIButton *LckDtlButton;
    
    GUIButton *OrderClearButton;
    GUIButton *OrderConfirmButton;
} static GUIButtons;

GUIBorder *OrderFormBorder;
// --------------------------------------------------
// GUI Panels
//

NamedScript void CreateStatsPanel()
{
    GUIPanel *StatsPanel = GUICreatePanel();
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Panel = StatsPanel;

    StatsPanel->Update = (PanelUpdateFunc)UpdateStatsPanel;
    //StatsPanel->Close = (PanelCloseFunc)CloseStatsPanel;

    for (int i = 0; i < STAT_MAX; i++)
    {
        Player.OrderForm[i].ChangeLevels = 0;
        Player.OrderForm[i].ChangeCost = 0;
        Player.OrderForm[i].ChangeString = "";
    }

    int GUIElementID = GUI_CONTENTS_ID;

    //Modules
    GUIIcons.ModulesIcon = GUIAddIcon(StatsPanel, "Modules Icon");
    GUILabels.ModulesLabel = GUIAddLabel(StatsPanel, "Modules Label");

    GUIIcons.ModulesIcon->Control.X = 10;
    GUIIcons.ModulesIcon->Control.Y = 12;
    GUIIcons.ModulesIcon->Control.id = ++GUIElementID;
    GUIIcons.ModulesIcon->Texture = "UMODA0";

    GUILabels.ModulesLabel->Control.X = 46;
    GUILabels.ModulesLabel->Control.Y = 30;
    GUILabels.ModulesLabel->Control.id = ++GUIElementID;
    GUILabels.ModulesLabel->Big = true;
    GUILabels.ModulesLabel->Color = "Green";

    //Stat cost to increase tooltip
/*     GUITooltip *StatIncTooltip = GUICreateTooltip();

    StatIncTooltip->Type = TT_TITLE;
    StatIncTooltip->Color = "White";
    StatIncTooltip->Title = "";
    StatIncTooltip->Text = "Null"; */

    //Strength
    GUIIcons.StrengthIcon = GUIAddIcon(StatsPanel, "Strength Icon");
    GUILabels.StrengthLabel = GUIAddLabel(StatsPanel, "Strength Label");
    GUILabels.StrGenLabel = GUIAddLabel(StatsPanel, "Strength General Label");
    GUIBars.StrXPBar = GUIAddBar(StatsPanel, "Strength XP Bar");
    GUIBars.StrXPBGBar = GUIAddBar(StatsPanel, "Strength XP BG Bar");

    GUIIcons.StrLvlDnIcon = GUIAddIcon(StatsPanel, "Strength Level Down Icon");
    GUIIcons.StrLvlUpIcon = GUIAddIcon(StatsPanel, "Strength Level Up Icon");
    GUIButtons.StrLvlMaxButton = GUIAddButton(StatsPanel, "Strength Level Max Button");
    GUIButtons.StrDtlButton = GUIAddButton(StatsPanel, "Strength Detail Button");
    //GUILabel *StrDtlLabel = GUIAddLabel(StatsPanel, "Strength Detail Label");
    //GUILabel *StrXPLabel = GUIAddLabel(StatsPanel, "Strength XP Label");

    GUIIcons.StrengthIcon->Control.X = 22;
    GUIIcons.StrengthIcon->Control.Y = 58;
    GUIIcons.StrengthIcon->Control.id = ++GUIElementID;
    GUIIcons.StrengthIcon->Texture = "STAT1";

    GUILabels.StrengthLabel->Control.X = 60;
    GUILabels.StrengthLabel->Control.Y = 64;
    GUILabels.StrengthLabel->Control.id = ++GUIElementID;
    GUILabels.StrengthLabel->Big = true;
    GUILabels.StrengthLabel->Color = StatColors[STAT_STRENGTH];

    GUILabels.StrGenLabel->Control.X = 60;
    GUILabels.StrGenLabel->Control.Y = 76;
    GUILabels.StrGenLabel->Control.id = ++GUIElementID;
    GUILabels.StrGenLabel->Text = "+ damage dealt";
    GUILabels.StrGenLabel->Color = "White";

    GUIBars.StrXPBar->Control.X = 60;
    GUIBars.StrXPBar->Control.Y = 90;
    GUIBars.StrXPBar->Control.id = ++GUIElementID;
    GUIBars.StrXPBar->Control.Height = 12;
    GUIBars.StrXPBar->Value = 0;
    GUIBars.StrXPBar->ValueMax = 150;
    GUIBars.StrXPBar->Texture = "XPBarStr";
    GUIBars.StrXPBar->Type = GUI_BAR_CLIP;

    GUIBars.StrXPBGBar->Control.X = 60;
    GUIBars.StrXPBGBar->Control.Y = 90;
    GUIBars.StrXPBGBar->Control.id = ++GUIElementID;
    GUIBars.StrXPBGBar->Control.Height = 12;
    GUIBars.StrXPBGBar->Value = 150;
    GUIBars.StrXPBGBar->ValueMax = 150;
    GUIBars.StrXPBGBar->Texture = "XPBarBG";
    GUIBars.StrXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.StrLvlDnIcon->Control.X = 224;
    GUIIcons.StrLvlDnIcon->Control.Y = 76;
    GUIIcons.StrLvlDnIcon->Control.Width = 18;
    GUIIcons.StrLvlDnIcon->Control.Height = 18;
    GUIIcons.StrLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.StrLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.StrLvlDnIcon->Control.Click = (ControlClickFunc)IconDownClick;
    GUIIcons.StrLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.StrLvlDnIcon->Enabled = false;

    GUIIcons.StrLvlUpIcon->Control.X = 224;
    GUIIcons.StrLvlUpIcon->Control.Y = 58;
    GUIIcons.StrLvlUpIcon->Control.Width = 18;
    GUIIcons.StrLvlUpIcon->Control.Height = 18;
    GUIIcons.StrLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.StrLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.StrLvlUpIcon->Control.Click = (ControlClickFunc)IconUpClick;
    GUIIcons.StrLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.StrLvlMaxButton->Control.X = 248;
    GUIButtons.StrLvlMaxButton->Control.Y = 66;
    GUIButtons.StrLvlMaxButton->Control.Width = 42;
    GUIButtons.StrLvlMaxButton->Control.Height = 16;
    GUIButtons.StrLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.StrLvlMaxButton->Text = "MAX";
    GUIButtons.StrLvlMaxButton->Big = true;
    GUIButtons.StrLvlMaxButton->Color = "Green";

    GUIButtons.StrDtlButton->Control.X = 260;
    GUIButtons.StrDtlButton->Control.Y = 82;
    GUIButtons.StrDtlButton->Control.Width = 16;
    GUIButtons.StrDtlButton->Control.Height = 16;
    GUIButtons.StrDtlButton->Control.id = ++GUIElementID;
    GUIButtons.StrDtlButton->Text = "...";
    GUIButtons.StrDtlButton->Big = true;
    GUIButtons.StrDtlButton->Color = "Green";

    /*     StrDtlLabel->Control.X = 236;
    StrDtlLabel->Control.Y = 58;
    StrDtlLabel->Control.id = ++GUIElementID;
    StrDtlLabel->Text = "";
    StrDtlLabel->Color = StatColors[STAT_STRENGTH]; */

    /* StrXPLabel->Control.X = 135;
    StrXPLabel->Control.Y = 93;
    StrXPLabel->Control.id = ++GUIElementID;
    StrXPLabel->Alignment = LA_CENTER;
    StrXPLabel->Color = "Grey";
    StrXPLabel->Text = ""; */

    //Defense
    GUIIcons.DefenseIcon = GUIAddIcon(StatsPanel, "Defense Icon");
    GUILabels.DefenseLabel = GUIAddLabel(StatsPanel, "Defense Label");
    GUILabels.DefGenLabel = GUIAddLabel(StatsPanel, "Defense General Label");
    //GUILabel *DefXPLabel = GUIAddLabel(StatsPanel, "Defense XP Label");
    GUIBars.DefXPBar = GUIAddBar(StatsPanel, "Defense XP Bar");
    GUIBars.DefXPBGBar = GUIAddBar(StatsPanel, "Defense XP BG Bar");

    GUIIcons.DefLvlDnIcon = GUIAddIcon(StatsPanel, "Defense Level Down Icon");
    GUIIcons.DefLvlUpIcon = GUIAddIcon(StatsPanel, "Defense Level Up Icon");
    GUIButtons.DefLvlMaxButton = GUIAddButton(StatsPanel, "Defense Level Max Button");
    GUIButtons.DefDtlButton = GUIAddButton(StatsPanel, "Defense Detail Button");

    GUIIcons.DefenseIcon->Control.X = 22;
    GUIIcons.DefenseIcon->Control.Y = 112 - 6;
    GUIIcons.DefenseIcon->Control.id = ++GUIElementID;
    GUIIcons.DefenseIcon->Texture = "STAT2";

    GUILabels.DefenseLabel->Control.X = 60;
    GUILabels.DefenseLabel->Control.Y = 118;
    GUILabels.DefenseLabel->Control.id = ++GUIElementID;
    GUILabels.DefenseLabel->Big = true;
    GUILabels.DefenseLabel->Color = StatColors[STAT_DEFENSE];

    GUILabels.DefGenLabel->Control.X = 60;
    GUILabels.DefGenLabel->Control.Y = 136;
    GUILabels.DefGenLabel->Control.id = ++GUIElementID;
    GUILabels.DefGenLabel->Text = "- damage taken\n- knockback";
    GUILabels.DefGenLabel->Color = "White";

    /* DefXPLabel->Control.X = 135;
    DefXPLabel->Control.Y = 157;
    DefXPLabel->Control.id = ++GUIElementID;
    DefXPLabel->Alignment = LA_CENTER;
    DefXPLabel->Color = "Grey";
    DefXPLabel->Text = ""; */

    GUIBars.DefXPBar->Control.X = 60;
    GUIBars.DefXPBar->Control.Y = 154;
    GUIBars.DefXPBar->Control.id = ++GUIElementID;
    GUIBars.DefXPBar->Control.Height = 16;
    GUIBars.DefXPBar->Value = 0;
    GUIBars.DefXPBar->ValueMax = 150;
    GUIBars.DefXPBar->Texture = "XPBarDef";
    GUIBars.DefXPBar->Type = GUI_BAR_CLIP;

    GUIBars.DefXPBGBar->Control.X = 60;
    GUIBars.DefXPBGBar->Control.Y = 154;
    GUIBars.DefXPBGBar->Control.id = ++GUIElementID;
    GUIBars.DefXPBGBar->Control.Height = 16;
    GUIBars.DefXPBGBar->Value = 150;
    GUIBars.DefXPBGBar->ValueMax = 150;
    GUIBars.DefXPBGBar->Texture = "XPBarBG";
    GUIBars.DefXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.DefLvlDnIcon->Control.X = 224;
    GUIIcons.DefLvlDnIcon->Control.Y = 130;
    GUIIcons.DefLvlDnIcon->Control.Width = 18;
    GUIIcons.DefLvlDnIcon->Control.Height = 18;
    GUIIcons.DefLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.DefLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.DefLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.DefLvlDnIcon->Enabled = false;

    GUIIcons.DefLvlUpIcon->Control.X = 224;
    GUIIcons.DefLvlUpIcon->Control.Y = 112;
    GUIIcons.DefLvlUpIcon->Control.Width = 18;
    GUIIcons.DefLvlUpIcon->Control.Height = 18;
    GUIIcons.DefLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.DefLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.DefLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.DefLvlMaxButton->Control.X = 248;
    GUIButtons.DefLvlMaxButton->Control.Y = 120;
    GUIButtons.DefLvlMaxButton->Control.Width = 42;
    GUIButtons.DefLvlMaxButton->Control.Height = 16;
    GUIButtons.DefLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.DefLvlMaxButton->Text = "MAX";
    GUIButtons.DefLvlMaxButton->Big = true;
    GUIButtons.DefLvlMaxButton->Color = "Green";

    GUIButtons.DefDtlButton->Control.X = 260;
    GUIButtons.DefDtlButton->Control.Y = 136;
    GUIButtons.DefDtlButton->Control.Width = 16;
    GUIButtons.DefDtlButton->Control.Height = 16;
    GUIButtons.DefDtlButton->Control.id = ++GUIElementID;
    GUIButtons.DefDtlButton->Text = "...";
    GUIButtons.DefDtlButton->Big = true;
    GUIButtons.DefDtlButton->Color = "Green";

    //Vitality
    GUIIcons.VitalityIcon = GUIAddIcon(StatsPanel, "Vitality Icon");
    GUILabels.VitalityLabel = GUIAddLabel(StatsPanel, "Vitality Label");
    GUILabels.VitGenLabel = GUIAddLabel(StatsPanel, "Vitality General Label");
    //GUILabel *VitXPLabel = GUIAddLabel(StatsPanel, "Vitality XP Label");
    GUIBars.VitXPBar = GUIAddBar(StatsPanel, "Vitality XP Bar");
    GUIBars.VitXPBGBar = GUIAddBar(StatsPanel, "Vitality XP BG Bar");

    GUIIcons.VitLvlDnIcon = GUIAddIcon(StatsPanel, "Vitality Level Down Icon");
    GUIIcons.VitLvlUpIcon = GUIAddIcon(StatsPanel, "Vitality Level Up Icon");
    GUIButtons.VitLvlMaxButton = GUIAddButton(StatsPanel, "Vitality Level Max Button");
    GUIButtons.VitDtlButton = GUIAddButton(StatsPanel, "Vitality Detail Button");

    GUIIcons.VitalityIcon->Control.X = 22;
    GUIIcons.VitalityIcon->Control.Y = 172;
    GUIIcons.VitalityIcon->Control.id = ++GUIElementID;
    GUIIcons.VitalityIcon->Texture = "STAT3";

    GUILabels.VitalityLabel->Control.X = 60;
    GUILabels.VitalityLabel->Control.Y = 178;
    GUILabels.VitalityLabel->Control.id = ++GUIElementID;
    GUILabels.VitalityLabel->Big = true;
    GUILabels.VitalityLabel->Color = StatColors[STAT_VITALITY];

    GUILabels.VitGenLabel->Control.X = 60;
    GUILabels.VitGenLabel->Control.Y = 200;
    GUILabels.VitGenLabel->Control.id = ++GUIElementID;
    GUILabels.VitGenLabel->Text = "+ max HP\n+ HP regen amount\n+ status effect resist";
    GUILabels.VitGenLabel->Color = "White";

    /* VitXPLabel->Control.X = 135;
    VitXPLabel->Control.Y = 225;
    VitXPLabel->Control.id = ++GUIElementID;
    VitXPLabel->Alignment = LA_CENTER;
    VitXPLabel->Color = "Grey";
    VitXPLabel->Text = ""; */

    GUIBars.VitXPBar->Control.X = 60;
    GUIBars.VitXPBar->Control.Y = 222;
    GUIBars.VitXPBar->Control.id = ++GUIElementID;
    GUIBars.VitXPBar->Control.Height = 16;
    GUIBars.VitXPBar->Value = 0;
    GUIBars.VitXPBar->ValueMax = 150;
    GUIBars.VitXPBar->Texture = "XPBarVit";
    GUIBars.VitXPBar->Type = GUI_BAR_CLIP;

    GUIBars.VitXPBGBar->Control.X = 60;
    GUIBars.VitXPBGBar->Control.Y = 222;
    GUIBars.VitXPBGBar->Control.id = ++GUIElementID;
    GUIBars.VitXPBGBar->Control.Height = 16;
    GUIBars.VitXPBGBar->Value = 150;
    GUIBars.VitXPBGBar->ValueMax = 150;
    GUIBars.VitXPBGBar->Texture = "XPBarBG";
    GUIBars.VitXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.VitLvlDnIcon->Control.X = 224;
    GUIIcons.VitLvlDnIcon->Control.Y = 190;
    GUIIcons.VitLvlDnIcon->Control.Width = 18;
    GUIIcons.VitLvlDnIcon->Control.Height = 18;
    GUIIcons.VitLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.VitLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.VitLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.VitLvlDnIcon->Enabled = false;

    GUIIcons.VitLvlUpIcon->Control.X = 224;
    GUIIcons.VitLvlUpIcon->Control.Y = 172;
    GUIIcons.VitLvlUpIcon->Control.Width = 18;
    GUIIcons.VitLvlUpIcon->Control.Height = 18;
    GUIIcons.VitLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.VitLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.VitLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.VitLvlMaxButton->Control.X = 248;
    GUIButtons.VitLvlMaxButton->Control.Y = 180;
    GUIButtons.VitLvlMaxButton->Control.Width = 42;
    GUIButtons.VitLvlMaxButton->Control.Height = 16;
    GUIButtons.VitLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.VitLvlMaxButton->Text = "MAX";
    GUIButtons.VitLvlMaxButton->Big = true;
    GUIButtons.VitLvlMaxButton->Color = "Green";

    GUIButtons.VitDtlButton->Control.X = 260;
    GUIButtons.VitDtlButton->Control.Y = 196;
    GUIButtons.VitDtlButton->Control.Width = 16;
    GUIButtons.VitDtlButton->Control.Height = 16;
    GUIButtons.VitDtlButton->Control.id = ++GUIElementID;
    GUIButtons.VitDtlButton->Text = "...";
    GUIButtons.VitDtlButton->Big = true;
    GUIButtons.VitDtlButton->Color = "Green";

    //Energy
    GUIIcons.EnergyIcon = GUIAddIcon(StatsPanel, "Energy Icon");
    GUILabels.EnergyLabel = GUIAddLabel(StatsPanel, "Energy Label");
    GUILabels.EngGenLabel = GUIAddLabel(StatsPanel, "Energy General Label");
    //GUILabel *EngXPLabel = GUIAddLabel(StatsPanel, "Energy XP Label");
    GUIBars.EngXPBar = GUIAddBar(StatsPanel, "Energy XP Bar");
    GUIBars.EngXPBGBar = GUIAddBar(StatsPanel, "Energy XP BG Bar");

    GUIIcons.EngLvlDnIcon = GUIAddIcon(StatsPanel, "Energy Level Down Icon");
    GUIIcons.EngLvlUpIcon = GUIAddIcon(StatsPanel, "Energy Level Up Icon");
    GUIButtons.EngLvlMaxButton = GUIAddButton(StatsPanel, "Energy Level Max Button");
    GUIButtons.EngDtlButton = GUIAddButton(StatsPanel, "Energy Detail Button");

    GUIIcons.EnergyIcon->Control.X = 22;
    GUIIcons.EnergyIcon->Control.Y = 236;
    GUIIcons.EnergyIcon->Control.id = ++GUIElementID;
    GUIIcons.EnergyIcon->Texture = "STAT4";

    GUILabels.EnergyLabel->Control.X = 60;
    GUILabels.EnergyLabel->Control.Y = 242;
    GUILabels.EnergyLabel->Control.id = ++GUIElementID;
    GUILabels.EnergyLabel->Big = true;
    GUILabels.EnergyLabel->Color = StatColors[STAT_ENERGY];

    GUILabels.EngGenLabel->Control.X = 60;
    GUILabels.EngGenLabel->Control.Y = 268;
    GUILabels.EngGenLabel->Control.id = ++GUIElementID;
    GUILabels.EngGenLabel->Text = "+ max EP\n+ EP regen amount\n+ aura duration\n+ aura effect range";
    GUILabels.EngGenLabel->Color = "White";

    /* EngXPLabel->Control.X = 135;
    EngXPLabel->Control.Y = 295;
    EngXPLabel->Control.id = ++GUIElementID;
    EngXPLabel->Alignment = LA_CENTER;
    EngXPLabel->Color = "Grey";
    EngXPLabel->Text = ""; */

    GUIBars.EngXPBar->Control.X = 60;
    GUIBars.EngXPBar->Control.Y = 292;
    GUIBars.EngXPBar->Control.id = ++GUIElementID;
    GUIBars.EngXPBar->Control.Height = 16;
    GUIBars.EngXPBar->Value = 0;
    GUIBars.EngXPBar->ValueMax = 150;
    GUIBars.EngXPBar->Texture = "XPBarEng";
    GUIBars.EngXPBar->Type = GUI_BAR_CLIP;

    GUIBars.EngXPBGBar->Control.X = 60;
    GUIBars.EngXPBGBar->Control.Y = 292;
    GUIBars.EngXPBGBar->Control.id = ++GUIElementID;
    GUIBars.EngXPBGBar->Control.Height = 16;
    GUIBars.EngXPBGBar->Value = 150;
    GUIBars.EngXPBGBar->ValueMax = 150;
    GUIBars.EngXPBGBar->Texture = "XPBarBG";
    GUIBars.EngXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.EngLvlDnIcon->Control.X = 224;
    GUIIcons.EngLvlDnIcon->Control.Y = 254;
    GUIIcons.EngLvlDnIcon->Control.Width = 18;
    GUIIcons.EngLvlDnIcon->Control.Height = 18;
    GUIIcons.EngLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.EngLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.EngLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.EngLvlDnIcon->Enabled = false;

    GUIIcons.EngLvlUpIcon->Control.X = 224;
    GUIIcons.EngLvlUpIcon->Control.Y = 236;
    GUIIcons.EngLvlUpIcon->Control.Width = 18;
    GUIIcons.EngLvlUpIcon->Control.Height = 18;
    GUIIcons.EngLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.EngLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.EngLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.EngLvlMaxButton->Control.X = 248;
    GUIButtons.EngLvlMaxButton->Control.Y = 244;
    GUIButtons.EngLvlMaxButton->Control.Width = 42;
    GUIButtons.EngLvlMaxButton->Control.Height = 16;
    GUIButtons.EngLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.EngLvlMaxButton->Text = "MAX";
    GUIButtons.EngLvlMaxButton->Big = true;
    GUIButtons.EngLvlMaxButton->Color = "Green";

    GUIButtons.EngDtlButton->Control.X = 260;
    GUIButtons.EngDtlButton->Control.Y = 260;
    GUIButtons.EngDtlButton->Control.Width = 16;
    GUIButtons.EngDtlButton->Control.Height = 16;
    GUIButtons.EngDtlButton->Control.id = ++GUIElementID;
    GUIButtons.EngDtlButton->Text = "...";
    GUIButtons.EngDtlButton->Big = true;
    GUIButtons.EngDtlButton->Color = "Green";

    //Regen
    GUIIcons.RegenIcon = GUIAddIcon(StatsPanel, "Regen Icon");
    GUILabels.RegenLabel = GUIAddLabel(StatsPanel, "Regen Label");
    GUILabels.RgnGenLabel = GUIAddLabel(StatsPanel, "Regen General Label");
    //GUILabel *RgnXPLabel = GUIAddLabel(StatsPanel, "Regen XP Label");
    GUIBars.RgnXPBar = GUIAddBar(StatsPanel, "Regen XP Bar");
    GUIBars.RgnXPBGBar = GUIAddBar(StatsPanel, "Regen XP BG Bar");

    GUIIcons.RgnLvlDnIcon = GUIAddIcon(StatsPanel, "Regen Level Down Icon");
    GUIIcons.RgnLvlUpIcon = GUIAddIcon(StatsPanel, "Regen Level Up Icon");
    GUIButtons.RgnLvlMaxButton = GUIAddButton(StatsPanel, "Regen Level Max Button");
    GUIButtons.RgnDtlButton = GUIAddButton(StatsPanel, "Regen Detail Button");

    GUIIcons.RegenIcon->Control.X = 22;
    GUIIcons.RegenIcon->Control.Y = 308;
    GUIIcons.RegenIcon->Control.id = ++GUIElementID;
    GUIIcons.RegenIcon->Texture = "STAT5";

    GUILabels.RegenLabel->Control.X = 60;
    GUILabels.RegenLabel->Control.Y = 314;
    GUILabels.RegenLabel->Control.id = ++GUIElementID;
    GUILabels.RegenLabel->Big = true;
    GUILabels.RegenLabel->Color = StatColors[STAT_REGENERATION];

    GUILabels.RgnGenLabel->Control.X = 60;
    GUILabels.RgnGenLabel->Control.Y = 325;
    GUILabels.RgnGenLabel->Control.id = ++GUIElementID;
    GUILabels.RgnGenLabel->Text = "+ regen frequency";
    GUILabels.RgnGenLabel->Color = "White";

    /* RgnXPLabel->Control.X = 135;
    RgnXPLabel->Control.Y = 339;
    RgnXPLabel->Control.id = ++GUIElementID;
    RgnXPLabel->Alignment = LA_CENTER;
    RgnXPLabel->Color = "Grey";
    RgnXPLabel->Text = ""; */

    GUIBars.RgnXPBar->Control.X = 60;
    GUIBars.RgnXPBar->Control.Y = 336;
    GUIBars.RgnXPBar->Control.id = ++GUIElementID;
    GUIBars.RgnXPBar->Control.Height = 16;
    GUIBars.RgnXPBar->Value = 0;
    GUIBars.RgnXPBar->ValueMax = 150;
    GUIBars.RgnXPBar->Texture = "XPBarRgn";
    GUIBars.RgnXPBar->Type = GUI_BAR_CLIP;

    GUIBars.RgnXPBGBar->Control.X = 60;
    GUIBars.RgnXPBGBar->Control.Y = 336;
    GUIBars.RgnXPBGBar->Control.id = ++GUIElementID;
    GUIBars.RgnXPBGBar->Control.Height = 16;
    GUIBars.RgnXPBGBar->Value = 150;
    GUIBars.RgnXPBGBar->ValueMax = 150;
    GUIBars.RgnXPBGBar->Texture = "XPBarBG";
    GUIBars.RgnXPBGBar->Type = GUI_BAR_CLIP;
    
    GUIIcons.RgnLvlDnIcon->Control.X = 224;
    GUIIcons.RgnLvlDnIcon->Control.Y = 326;
    GUIIcons.RgnLvlDnIcon->Control.Width = 18;
    GUIIcons.RgnLvlDnIcon->Control.Height = 18;
    GUIIcons.RgnLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.RgnLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.RgnLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.RgnLvlDnIcon->Enabled = false;

    GUIIcons.RgnLvlUpIcon->Control.X = 224;
    GUIIcons.RgnLvlUpIcon->Control.Y = 308;
    GUIIcons.RgnLvlUpIcon->Control.Width = 18;
    GUIIcons.RgnLvlUpIcon->Control.Height = 18;
    GUIIcons.RgnLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.RgnLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.RgnLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.RgnLvlMaxButton->Control.X = 248;
    GUIButtons.RgnLvlMaxButton->Control.Y = 316;
    GUIButtons.RgnLvlMaxButton->Control.Width = 42;
    GUIButtons.RgnLvlMaxButton->Control.Height = 16;
    GUIButtons.RgnLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.RgnLvlMaxButton->Text = "MAX";
    GUIButtons.RgnLvlMaxButton->Big = true;
    GUIButtons.RgnLvlMaxButton->Color = "Green";

    GUIButtons.RgnDtlButton->Control.X = 260;
    GUIButtons.RgnDtlButton->Control.Y = 332;
    GUIButtons.RgnDtlButton->Control.Width = 16;
    GUIButtons.RgnDtlButton->Control.Height = 16;
    GUIButtons.RgnDtlButton->Control.id = ++GUIElementID;
    GUIButtons.RgnDtlButton->Text = "...";
    GUIButtons.RgnDtlButton->Big = true;
    GUIButtons.RgnDtlButton->Color = "Green";

    //Agility
    GUIIcons.AgilityIcon = GUIAddIcon(StatsPanel, "Agility Icon");
    GUILabels.AgilityLabel = GUIAddLabel(StatsPanel, "Agility Label");
    GUILabels.AglGenLabel = GUIAddLabel(StatsPanel, "Agility General Label");
    //GUILabel *AglXPLabel = GUIAddLabel(StatsPanel, "Agility XP Label");
    GUIBars.AglXPBar = GUIAddBar(StatsPanel, "Agility XP Bar");
    GUIBars.AglXPBGBar = GUIAddBar(StatsPanel, "Agility XP BG Bar");

    GUIIcons.AglLvlDnIcon = GUIAddIcon(StatsPanel, "Agility Level Down Icon");
    GUIIcons.AglLvlUpIcon = GUIAddIcon(StatsPanel, "Agility Level Up Icon");
    GUIButtons.AglLvlMaxButton = GUIAddButton(StatsPanel, "Agility Level Max Button");
    GUIButtons.AglDtlButton = GUIAddButton(StatsPanel, "Agility Detail Button");

    GUIIcons.AgilityIcon->Control.X = 22;
    GUIIcons.AgilityIcon->Control.Y = 352;
    GUIIcons.AgilityIcon->Control.id = ++GUIElementID;
    GUIIcons.AgilityIcon->Texture = "STAT6";

    GUILabels.AgilityLabel->Control.X = 60;
    GUILabels.AgilityLabel->Control.Y = 358;
    GUILabels.AgilityLabel->Control.id = ++GUIElementID;
    GUILabels.AgilityLabel->Big = true;
    GUILabels.AgilityLabel->Color = StatColors[STAT_AGILITY];

    GUILabels.AglGenLabel->Control.X = 60;
    GUILabels.AglGenLabel->Control.Y = 384;
    GUILabels.AglGenLabel->Control.id = ++GUIElementID;
    GUILabels.AglGenLabel->Text = "+ movement speed\n+ jump height\n+ weapon fire rate\n+ survival chance";
    GUILabels.AglGenLabel->Color = "White";

    /* AglXPLabel->Control.X = 135;
    AglXPLabel->Control.Y = 411;
    AglXPLabel->Control.id = ++GUIElementID;
    AglXPLabel->Alignment = LA_CENTER;
    AglXPLabel->Color = "Grey";
    AglXPLabel->Text = ""; */

    GUIBars.AglXPBar->Control.X = 60;
    GUIBars.AglXPBar->Control.Y = 408;
    GUIBars.AglXPBar->Control.id = ++GUIElementID;
    GUIBars.AglXPBar->Control.Height = 16;
    GUIBars.AglXPBar->Value = 0;
    GUIBars.AglXPBar->ValueMax = 150;
    GUIBars.AglXPBar->Texture = "XPBarAgl";
    GUIBars.AglXPBar->Type = GUI_BAR_CLIP;

    GUIBars.AglXPBGBar->Control.X = 60;
    GUIBars.AglXPBGBar->Control.Y = 408;
    GUIBars.AglXPBGBar->Control.id = ++GUIElementID;
    GUIBars.AglXPBGBar->Control.Height = 16;
    GUIBars.AglXPBGBar->Value = 150;
    GUIBars.AglXPBGBar->ValueMax = 150;
    GUIBars.AglXPBGBar->Texture = "XPBarBG";
    GUIBars.AglXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.AglLvlDnIcon->Control.X = 224;
    GUIIcons.AglLvlDnIcon->Control.Y = 370;
    GUIIcons.AglLvlDnIcon->Control.Width = 18;
    GUIIcons.AglLvlDnIcon->Control.Height = 18;
    GUIIcons.AglLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.AglLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.AglLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.AglLvlDnIcon->Enabled = false;

    GUIIcons.AglLvlUpIcon->Control.X = 224;
    GUIIcons.AglLvlUpIcon->Control.Y = 352;
    GUIIcons.AglLvlUpIcon->Control.Width = 18;
    GUIIcons.AglLvlUpIcon->Control.Height = 18;
    GUIIcons.AglLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.AglLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.AglLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.AglLvlMaxButton->Control.X = 248;
    GUIButtons.AglLvlMaxButton->Control.Y = 360;
    GUIButtons.AglLvlMaxButton->Control.Width = 42;
    GUIButtons.AglLvlMaxButton->Control.Height = 16;
    GUIButtons.AglLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.AglLvlMaxButton->Text = "MAX";
    GUIButtons.AglLvlMaxButton->Big = true;
    GUIButtons.AglLvlMaxButton->Color = "Green";

    GUIButtons.AglDtlButton->Control.X = 260;
    GUIButtons.AglDtlButton->Control.Y = 376;
    GUIButtons.AglDtlButton->Control.Width = 16;
    GUIButtons.AglDtlButton->Control.Height = 16;
    GUIButtons.AglDtlButton->Control.id = ++GUIElementID;
    GUIButtons.AglDtlButton->Text = "...";
    GUIButtons.AglDtlButton->Big = true;
    GUIButtons.AglDtlButton->Color = "Green";

    //Capacity
    GUIIcons.CapacityIcon = GUIAddIcon(StatsPanel, "Capacity Icon");
    GUILabels.CapacityLabel = GUIAddLabel(StatsPanel, "Capacity Label");
    GUILabels.CapGenLabel = GUIAddLabel(StatsPanel, "Capacity General Label");
    //GUILabel *CapXPLabel = GUIAddLabel(StatsPanel, "Capacity XP Label");
    GUIBars.CapXPBar = GUIAddBar(StatsPanel, "Capacity XP Bar");
    GUIBars.CapXPBGBar = GUIAddBar(StatsPanel, "Capacity XP BG Bar");

    GUIIcons.CapLvlDnIcon = GUIAddIcon(StatsPanel, "Capacity Level Down Icon");
    GUIIcons.CapLvlUpIcon = GUIAddIcon(StatsPanel, "Capacity Level Up Icon");
    GUIButtons.CapLvlMaxButton = GUIAddButton(StatsPanel, "Capacity Level Max Button");
    GUIButtons.CapDtlButton = GUIAddButton(StatsPanel, "Capacity Detail Button");

    GUIIcons.CapacityIcon->Control.X = 22;
    GUIIcons.CapacityIcon->Control.Y = 416;
    GUIIcons.CapacityIcon->Control.id = ++GUIElementID;
    GUIIcons.CapacityIcon->Texture = "STAT7";

    GUILabels.CapacityLabel->Control.X = 60;
    GUILabels.CapacityLabel->Control.Y = 426;
    GUILabels.CapacityLabel->Control.id = ++GUIElementID;
    GUILabels.CapacityLabel->Big = true;
    GUILabels.CapacityLabel->Color = StatColors[STAT_CAPACITY];

    GUILabels.CapGenLabel->Control.X = 60;
    GUILabels.CapGenLabel->Control.Y = 456;
    GUILabels.CapGenLabel->Control.id = ++GUIElementID;
    GUILabels.CapGenLabel->Text = "+ inventory capacity\n+ ammo capacity\n+ aug battery size\n+ stim capacity\n+ medkit capacity";
    GUILabels.CapGenLabel->Color = "White";

    /* CapXPLabel->Control.X = 135;
    CapXPLabel->Control.Y = 489;
    CapXPLabel->Control.id = ++GUIElementID;
    CapXPLabel->Alignment = LA_CENTER;
    CapXPLabel->Color = "Grey";
    CapXPLabel->Text = ""; */

    GUIBars.CapXPBar->Control.X = 60;
    GUIBars.CapXPBar->Control.Y = 486;
    GUIBars.CapXPBar->Control.id = ++GUIElementID;
    GUIBars.CapXPBar->Control.Height = 16;
    GUIBars.CapXPBar->Value = 0;
    GUIBars.CapXPBar->ValueMax = 150;
    GUIBars.CapXPBar->Texture = "XPBarCap";
    GUIBars.CapXPBar->Type = GUI_BAR_CLIP;

    GUIBars.CapXPBGBar->Control.X = 60;
    GUIBars.CapXPBGBar->Control.Y = 486;
    GUIBars.CapXPBGBar->Control.id = ++GUIElementID;
    GUIBars.CapXPBGBar->Control.Height = 16;
    GUIBars.CapXPBGBar->Value = 150;
    GUIBars.CapXPBGBar->ValueMax = 150;
    GUIBars.CapXPBGBar->Texture = "XPBarBG";
    GUIBars.CapXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.CapLvlDnIcon->Control.X = 224;
    GUIIcons.CapLvlDnIcon->Control.Y = 438;
    GUIIcons.CapLvlDnIcon->Control.Width = 18;
    GUIIcons.CapLvlDnIcon->Control.Height = 18;
    GUIIcons.CapLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.CapLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.CapLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.CapLvlDnIcon->Enabled = false;

    GUIIcons.CapLvlUpIcon->Control.X = 224;
    GUIIcons.CapLvlUpIcon->Control.Y = 420;
    GUIIcons.CapLvlUpIcon->Control.Width = 18;
    GUIIcons.CapLvlUpIcon->Control.Height = 18;
    GUIIcons.CapLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.CapLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.CapLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.CapLvlMaxButton->Control.X = 248;
    GUIButtons.CapLvlMaxButton->Control.Y = 428;
    GUIButtons.CapLvlMaxButton->Control.Width = 42;
    GUIButtons.CapLvlMaxButton->Control.Height = 16;
    GUIButtons.CapLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.CapLvlMaxButton->Text = "MAX";
    GUIButtons.CapLvlMaxButton->Big = true;
    GUIButtons.CapLvlMaxButton->Color = "Green";

    GUIButtons.CapDtlButton->Control.X = 260;
    GUIButtons.CapDtlButton->Control.Y = 444;
    GUIButtons.CapDtlButton->Control.Width = 16;
    GUIButtons.CapDtlButton->Control.Height = 16;
    GUIButtons.CapDtlButton->Control.id = ++GUIElementID;
    GUIButtons.CapDtlButton->Text = "...";
    GUIButtons.CapDtlButton->Big = true;
    GUIButtons.CapDtlButton->Color = "Green";

    //Luck
    GUIIcons.LuckIcon = GUIAddIcon(StatsPanel, "Luck Icon");
    GUILabels.LuckLabel = GUIAddLabel(StatsPanel, "Luck Label");
    GUILabels.LckGenLabel = GUIAddLabel(StatsPanel, "Luck General Label");
    //GUILabel *LckXPLabel = GUIAddLabel(StatsPanel, "Luck XP Label");
    GUIBars.LckXPBar = GUIAddBar(StatsPanel, "Luck XP Bar");
    GUIBars.LckXPBGBar = GUIAddBar(StatsPanel, "Luck XP BG Bar");

    GUIIcons.LckLvlDnIcon = GUIAddIcon(StatsPanel, "Luck Level Down Icon");
    GUIIcons.LckLvlUpIcon = GUIAddIcon(StatsPanel, "Luck Level Up Icon");
    GUIButtons.LckLvlMaxButton = GUIAddButton(StatsPanel, "Luck Level Max Button");
    GUIButtons.LckDtlButton = GUIAddButton(StatsPanel, "Luck Detail Button");

    GUIIcons.LuckIcon->Control.X = 22;
    GUIIcons.LuckIcon->Control.Y = 492;
    GUIIcons.LuckIcon->Control.id = ++GUIElementID;
    GUIIcons.LuckIcon->Texture = "STAT8";

    GUILabels.LuckLabel->Control.X = 60;
    GUILabels.LuckLabel->Control.Y = 506;
    GUILabels.LuckLabel->Control.id = ++GUIElementID;
    GUILabels.LuckLabel->Big = true;
    GUILabels.LuckLabel->Color = StatColors[STAT_LUCK];

    GUILabels.LckGenLabel->Control.X = 60;
    GUILabels.LckGenLabel->Control.Y = 518;
    GUILabels.LckGenLabel->Control.id = ++GUIElementID;
    GUILabels.LckGenLabel->Text = "+ loot drops";
    GUILabels.LckGenLabel->Color = "White";

    /* LckXPLabel->Control.X = 135;
    LckXPLabel->Control.Y = 533;
    LckXPLabel->Control.id = ++GUIElementID;
    LckXPLabel->Alignment = LA_CENTER;
    LckXPLabel->Color = "Grey";
    LckXPLabel->Text = ""; */

    GUIBars.LckXPBar->Control.X = 60;
    GUIBars.LckXPBar->Control.Y = 530;
    GUIBars.LckXPBar->Control.id = ++GUIElementID;
    GUIBars.LckXPBar->Control.Height = 16;
    GUIBars.LckXPBar->Value = 0;
    GUIBars.LckXPBar->ValueMax = 150;
    GUIBars.LckXPBar->Texture = "XPBarLck";
    GUIBars.LckXPBar->Type = GUI_BAR_CLIP;

    GUIBars.LckXPBGBar->Control.X = 60;
    GUIBars.LckXPBGBar->Control.Y = 530;
    GUIBars.LckXPBGBar->Control.id = ++GUIElementID;
    GUIBars.LckXPBGBar->Control.Height = 16;
    GUIBars.LckXPBGBar->Value = 150;
    GUIBars.LckXPBGBar->ValueMax = 150;
    GUIBars.LckXPBGBar->Texture = "XPBarBG";
    GUIBars.LckXPBGBar->Type = GUI_BAR_CLIP;

    GUIIcons.LckLvlDnIcon->Control.X = 224;
    GUIIcons.LckLvlDnIcon->Control.Y = 518;
    GUIIcons.LckLvlDnIcon->Control.Width = 18;
    GUIIcons.LckLvlDnIcon->Control.Height = 18;
    GUIIcons.LckLvlDnIcon->Control.id = ++GUIElementID;
    GUIIcons.LckLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.LckLvlDnIcon->Texture = "HLISTDN";
    GUIIcons.LckLvlDnIcon->Enabled = false;

    GUIIcons.LckLvlUpIcon->Control.X = 224;
    GUIIcons.LckLvlUpIcon->Control.Y = 500;
    GUIIcons.LckLvlUpIcon->Control.Width = 18;
    GUIIcons.LckLvlUpIcon->Control.Height = 18;
    GUIIcons.LckLvlUpIcon->Control.id = ++GUIElementID;
    GUIIcons.LckLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    GUIIcons.LckLvlUpIcon->Texture = "HLISTUP";

    GUIButtons.LckLvlMaxButton->Control.X = 248;
    GUIButtons.LckLvlMaxButton->Control.Y = 508;
    GUIButtons.LckLvlMaxButton->Control.Width = 42;
    GUIButtons.LckLvlMaxButton->Control.Height = 16;
    GUIButtons.LckLvlMaxButton->Control.id = ++GUIElementID;
    GUIButtons.LckLvlMaxButton->Text = "MAX";
    GUIButtons.LckLvlMaxButton->Big = true;
    GUIButtons.LckLvlMaxButton->Color = "Green";

    GUIButtons.LckDtlButton->Control.X = 260;
    GUIButtons.LckDtlButton->Control.Y = 524;
    GUIButtons.LckDtlButton->Control.Width = 16;
    GUIButtons.LckDtlButton->Control.Height = 16;
    GUIButtons.LckDtlButton->Control.id = ++GUIElementID;
    GUIButtons.LckDtlButton->Text = "...";
    GUIButtons.LckDtlButton->Big = true;
    GUIButtons.LckDtlButton->Color = "Green";

    //Order Form Border
    OrderFormBorder = GUIAddBorder(StatsPanel, "Order Form Border");

    OrderFormBorder->Control.X = 600;
    OrderFormBorder->Control.Y = 16;
    OrderFormBorder->Control.Width = 196;
    OrderFormBorder->Control.Height = 532;
    OrderFormBorder->Control.id = MAKE_ID('O','F','B','R');

    //Clear/Confirm Buttons
    GUIButtons.OrderClearButton = GUIAddButton(StatsPanel, "Order Form Clear Button");
    GUIButtons.OrderConfirmButton = GUIAddButton(StatsPanel, "Order Form Confirm Button");

    GUIButtons.OrderClearButton->Control.X = 610;
    GUIButtons.OrderClearButton->Control.Y = 520;
    GUIButtons.OrderClearButton->Control.id = ++GUIElementID;
    GUIButtons.OrderClearButton->Control.Width = 64;
    GUIButtons.OrderClearButton->Control.Height = 16;
    GUIButtons.OrderClearButton->Text = "CLEAR";
    GUIButtons.OrderClearButton->Big = true;
    GUIButtons.OrderClearButton->Color = "Dark Grey";
    GUIButtons.OrderClearButton->HoverColor = "Dark Grey";

    GUIButtons.OrderConfirmButton->Control.X = 694;
    GUIButtons.OrderConfirmButton->Control.Y = 520;
    GUIButtons.OrderConfirmButton->Control.id = ++GUIElementID;
    GUIButtons.OrderConfirmButton->Control.Width = 90;
    GUIButtons.OrderConfirmButton->Control.Height = 16;
    GUIButtons.OrderConfirmButton->Text = "CONFIRM";
    GUIButtons.OrderConfirmButton->Big = true;
    GUIButtons.OrderConfirmButton->Color = "Dark Grey";
    GUIButtons.OrderConfirmButton->HoverColor = "Dark Grey";
}

NamedScript void UpdateStatsPanel(GUIPanel *StatsPanel)
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


    GUIBar *XPBar[STAT_MAX] =
    {
        GUIBars.StrXPBar,
        GUIBars.DefXPBar,
        GUIBars.VitXPBar,
        GUIBars.EngXPBar,
        GUIBars.RgnXPBar,
        GUIBars.AglXPBar,
        GUIBars.CapXPBar,
        GUIBars.LckXPBar
    };

    GUIBar *XPBGBar[STAT_MAX] =
    {
        GUIBars.StrXPBGBar,
        GUIBars.DefXPBGBar,
        GUIBars.VitXPBGBar,
        GUIBars.EngXPBGBar,
        GUIBars.RgnXPBGBar,
        GUIBars.AglXPBGBar,
        GUIBars.CapXPBGBar,
        GUIBars.LckXPBGBar
    };

    GUIIcon *LvlIcon[STAT_MAX * 2] =
    {
        GUIIcons.StrLvlUpIcon,
        GUIIcons.StrLvlDnIcon,
        GUIIcons.DefLvlUpIcon,
        GUIIcons.DefLvlDnIcon,
        GUIIcons.VitLvlUpIcon,
        GUIIcons.VitLvlDnIcon,
        GUIIcons.EngLvlUpIcon,
        GUIIcons.EngLvlDnIcon,
        GUIIcons.RgnLvlUpIcon,
        GUIIcons.RgnLvlDnIcon,
        GUIIcons.AglLvlUpIcon,
        GUIIcons.AglLvlDnIcon,
        GUIIcons.CapLvlUpIcon,
        GUIIcons.CapLvlDnIcon,
        GUIIcons.LckLvlUpIcon,
        GUIIcons.LckLvlDnIcon
    };

    //Update Current Modules
    GUILabels.ModulesLabel->Text = StrParam("%d", CheckInventory("DRPGModule"));

    //Update Current Stats
    GUILabels.StrengthLabel->Text = StrParam("Strength: %d", Player.Strength);
    GUILabels.DefenseLabel->Text = StrParam("Defense: %d", Player.Defense);
    GUILabels.VitalityLabel->Text = StrParam("Vitality: %d", Player.Vitality);
    GUILabels.EnergyLabel->Text = StrParam("Energy: %d", Player.Energy);
    GUILabels.RegenLabel->Text = StrParam("Regen: %d", Player.Regeneration);
    GUILabels.AgilityLabel->Text = StrParam("Agility: %d", Player.Agility);
    GUILabels.CapacityLabel->Text = StrParam("Capacity: %d", Player.Capacity);
    GUILabels.LuckLabel->Text = StrParam("Luck: %d", Player.Luck);

    /* StrDtlLabel->Text = StrParam("+%d%% base damage\n+%d%% bonus damage\n%.2kX Multiplier\n+%d%% Total Damage",
    Player.Level * (10 - GameSkill()), Player.BonusDamage,
    (Player.DamageMult > 1k ? Player.DamageMult : 1k),
    (int)(Player.TotalDamage * (Player.DamageMult > 1k ? Player.DamageMult : 1k))); */

    //Update XP bars
    if (GetCVar("drpg_levelup_natural"))
    {
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

            StatPercent = (int)(StatPercent * 1.5);
            XPBar[i]->Control.Visible = true;
            XPBGBar[i]->Control.Visible = true;
            XPBar[i]->Value = StatPercent;

            // XPLabel[i]->Control.Visible = true;
            // XPLabel[i]->Text = StrParam("%ld/%ld", *StatXP[i], StatTable[*Stats[i]]);
        }
    }
    else
    {
        for (int i = 0; i < STAT_MAX; i++)
        {
            XPBar[i]->Control.Visible = false;
            XPBGBar[i]->Control.Visible = false;

            //XPLabel[i]->Control.Visible = false;
        }
    }

    //Level Up/Down Icons
    for (int i = 0; i < sizeof(LvlIcon); i++)
    {
        if (i % 2 == 0) //Size of LvlIcon is double STAT_MAX - Even numbers are level up, odd level down
        {
            if (
                ((*Stats[(int)(i / 2)] + Player.OrderForm[(int)(i / 2)].ChangeLevels) >= Player.StatCap)
                 ||
                (
                 (CostOfStatUpgrade(*Stats[(int)(i / 2)] + Player.OrderForm[(int)(i / 2)].ChangeLevels)
                 + Player.OrderForm[(int)(i / 2)].ChangeCost)
                 > CheckInventory("DRPGModule")
                )
            ) //if current stat level + ordered levels >= stat soft cap OR if not enough modules to add more stats (these calcs are always to the next level)
                LvlIcon[i]->Enabled = false;
            else
                LvlIcon[i]->Enabled = true;
        }
        else
        {
            if (Player.OrderForm[(int)(i / 2)].ChangeLevels > 0)
                LvlIcon[i]->Enabled = true;
            else
                LvlIcon[i]->Enabled = false;
        }

        if (LvlIcon[i] && LvlIcon[i]->Enabled)
        {
            LvlIcon[i]->Pulse = 0;
            LvlIcon[i]->Alpha = 0;
        }
    }

    GUIUpdatePanelControls(StatsPanel);
}

NamedScript void ButtonClicked(GUIButton *GUIObj) //currently unused
{
    if (GUIObj->Control.Name == "Strength Button")
        IncreaseStat(0);
    if (GUIObj->Control.Name == "Defense Button")
        IncreaseStat(1);
    if (GUIObj->Control.Name == "Vitality Button")
        IncreaseStat(2);
    if (GUIObj->Control.Name == "Energy Button")
        IncreaseStat(3);
    if (GUIObj->Control.Name == "Regen Button")
        IncreaseStat(4);
    if (GUIObj->Control.Name == "Agility Button")
        IncreaseStat(5);
    if (GUIObj->Control.Name == "Capacity Button")
        IncreaseStat(6);
    if (GUIObj->Control.Name == "Luck Button")
        IncreaseStat(7);
}

NamedScript void IconHover(GUIIcon *GUIObj)
{

    if (GUIObj->Enabled)
    {
        GUIObj->Pulse = 32.0;
        GUIObj->Alpha = 0.75;
        GUIObj->Radius = 0.25;
    }
}

NamedScript void IconUpClick(GUIIcon *GUIObj)
{
    if (!GUIObj->Enabled)
        return;

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

    GUIPanel *StatsPanel = Player.GUI.TabStrip.Tabs[PANEL_STATS].Panel;

    GUIIcon *LvlIcon[STAT_MAX] =
    {
        GUIIcons.StrLvlUpIcon,
        GUIIcons.DefLvlUpIcon,
        GUIIcons.VitLvlUpIcon,
        GUIIcons.EngLvlUpIcon,
        GUIIcons.RgnLvlUpIcon,
        GUIIcons.AglLvlUpIcon,
        GUIIcons.CapLvlUpIcon,
        GUIIcons.LckLvlUpIcon
    };

    //Increase
    for (int i = 0; i < STAT_MAX; i++)
    {
        if (GUIObj == LvlIcon[i])
        {
            int CostOfNextLevel = CostOfStatUpgrade(*Stats[i] + Player.OrderForm[i].ChangeLevels);
            Player.OrderForm[i].ChangeLevels += 1;
            Player.OrderForm[i].ChangeCost += CostOfNextLevel;
            BuildOrderFormString(i);
        }
    }
}

NamedScript void IconDownClick(GUIIcon *GUIObj)
{
    if (!GUIObj->Enabled)
        return;

    GUIPanel *StatsPanel = Player.GUI.TabStrip.Tabs[PANEL_STATS].Panel;

    GUIIcon *LvlIcon[STAT_MAX] =
    {
        GUIIcons.StrLvlDnIcon,
        GUIIcons.DefLvlDnIcon,
        GUIIcons.VitLvlDnIcon,
        GUIIcons.EngLvlDnIcon,
        GUIIcons.RgnLvlDnIcon,
        GUIIcons.AglLvlDnIcon,
        GUIIcons.CapLvlDnIcon,
        GUIIcons.LckLvlDnIcon
    };

    //Decrease
}

void BuildOrderFormString(int Stat)
{
    str const StatColorsS[STAT_MAX] =
    {
        "\Cg",      // Strength
        "\Cd",      // Defense
        "\Ca",      // Vitality
        "\Cn",      // Energy
        "\Ct",      // Regeneration
        "\Ci",      // Agility
        "\Ch",      // Capacity
        "\Cf"       // Luck
    };

    int ChangeLevels = Player.OrderForm[Stat].ChangeLevels;
    int ChangeCost = Player.OrderForm[Stat].ChangeCost;
    str ChangeString = Player.OrderForm[Stat].ChangeString;

    switch(Stat)
    {
    case STAT_STRENGTH:
        {
            ChangeString = StrParam("%S+%d Strength\n\n+%d Bonus Damage\n",
                StatColorsS[STAT_STRENGTH], ChangeLevels, ChangeLevels);

            if (Player.Strength < 100 && Player.Strength + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SStrength Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_DEFENSE:
        {
            ChangeString = StrParam("%S+%d Defense\n\n+%d Damage Reduction\n+%d Mass\n",
                StatColorsS[STAT_DEFENSE], ChangeLevels, ChangeLevels,
                ChangeLevels * 10);

            if (Player.Defense < 100 && Player.Defense + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SDefense Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_VITALITY:
        {
            ChangeString = StrParam("%S+%d Vitality\n\n+%d Bonus Health\n+%f HP Regen Amount\n+%f Status Effect Resist\n",
                StatColorsS[STAT_VITALITY], ChangeLevels, ChangeLevels * 10,
                (fixed)(ChangeLevels / 50.0), (fixed)(ChangeLevels / 4.0));

            if (Player.Vitality < 100 && Player.Vitality + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SVitality Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_ENERGY:
        {
            ChangeString = StrParam("%S+%d Energy\n\n+%d Bonus EP\n+%f EP Regen Amount\n+%d Aura Range\n+%S Aura Time\n",
                StatColorsS[STAT_ENERGY], ChangeLevels, ChangeLevels * 10,
                (fixed)(ChangeLevels / 50.0), ChangeLevels * 16,
                FormatTime((((35 * 30) + (ChangeLevels * 5.25)) * (Player.AuraBonus + 1))));

            if (Player.Energy < 100 && Player.Energy + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SEnergy Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_REGENERATION:
        {
            int HPTime = (int)(Player.HPTime - (350k - ((fixed)(Player.Regeneration + ChangeLevels) * 1.575k) - ((fixed)Player.AgilityTimer * 0.5k) * 2k));
            int EPTime = (int)(Player.EPTime - (350k - ((fixed)(Player.Regeneration + ChangeLevels) * 1.575k) - ((fixed)Player.AgilityTimer * 0.5k) * 2k));
            int ToxBonus = (int)(((Player.Regeneration % 10) + ChangeLevels) / 10);
            int ToxRegenBonus = (Player.ToxicityRegenBonus + ToxBonus > 25 ? 25 - Player.ToxicityRegenBonus - ToxBonus : ToxBonus);
            ToxRegenBonus = (ToxRegenBonus < 0 ? 0 : ToxRegenBonus);

            ChangeString = StrParam("%S+%d Regeneration\n-%.2k HP Regen Delay\n-%.2k EP Regen Delay\n+%d Regen Sphere Time\n-%d Secs Toxicity Recovery\n",
                StatColorsS[STAT_REGENERATION], ChangeLevels,
                (fixed)(HPTime / (35.0K * 2.0K)),
                (fixed)(EPTime / (35.0K * 2.0K)),
                (int)((fixed)ChangeLevels / 13.33),
                ToxRegenBonus);

            if (Player.Regeneration < 100 && Player.Regeneration + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SRegen Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_AGILITY:
        {
            fixed Speed = (1.0 + 0.25 * ((fixed)(Player.Agility + ChangeLevels) / 100) - Player.Speed);
            fixed JumpHeight = (8.0 + (8.0 * ((fixed)(Player.Agility + ChangeLevels) / 100)) - Player.JumpHeight);
            int Firerate = (Player.Agility + ChangeLevels > 100 ? 100 - Player.Agility - ChangeLevels : ChangeLevels);
            Firerate = (Firerate < 0 ? 0 : Firerate);

            ChangeString = StrParam("%S+%d Agility\n\n+.2k Movement Speed\n+.2k Jump Height\n+%d Weapon Firerate\n+%.2k Survival Bonus\n",
                StatColorsS[STAT_AGILITY], ChangeLevels,
                Speed, JumpHeight, Firerate, (fixed)ChangeLevels / 10.0);

            if (Player.Agility < 100 && Player.Agility + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SAgility Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_CAPACITY:
        {
            ChangeString = StrParam("%S+%d Capacity\n\n+%d Bullets Max\n+%d Shells Max\n+%dRockets Max\n+%d Cells Max\n+%d Medkit Max\n+%d Aug Battery Max\n+%d Stim Vials Max\n",
                StatColorsS[STAT_CAPACITY], ChangeLevels,
                ChangeLevels * 20, ChangeLevels * 5,
                ChangeLevels * 5, ChangeLevels * 30,
                ChangeLevels * 10, ChangeLevels * 10,
                ChangeLevels * 10);

            if (GetCVar("drpg_inv_capacity"))
            {
                ChangeString = StrParam("%S+%d Inventory Max\n", ChangeString, ChangeLevels * 2);
            }

            if (CompatMode == COMPAT_DRLA)
            {
                int ArmorMax = (2 + (Player.Capacity + ChangeLevels) / 25) - DRLA_ARMOR_MAX;
                int DeviceMax = (4 + (Player.Capacity + ChangeLevels) / 50) - DRLA_DEVICE_MAX;
                if (ArmorMax > 0)
                {
                    ChangeString = StrParam("%S+%d DRLA Armors Max\n+%d DRLA Skulls Max\n", ChangeString, ArmorMax, ArmorMax);
                }
                if (DeviceMax > 0)
                {
                    ChangeString = StrParam("%S+%d DRLA Devices Max\n", ChangeString, DeviceMax);
                }
            }

            if (Player.Capacity < 100 && Player.Capacity + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%SCapacity Perk\n", ChangeString);
            }

            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    case STAT_LUCK:
        {
            ChangeString = StrParam("%S+%d Luck\n\n",
                StatColorsS[STAT_LUCK], ChangeLevels);
            
            if (Player.Luck < 100 && Player.Luck + ChangeLevels >= 100)
            {
                ChangeString = StrParam("%Luck Perk\n", ChangeString);
            }
            
            ChangeString = StrParam("%S\Cr-%d", ChangeString, ChangeCost);
            break;
        }
    }
}

int CostOfStatUpgrade(int Stat)
{
    int Cost = (int)((((fixed)Stat + 1) * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));
    if (Cost < 0)
        Cost = -Cost;
    else if (Cost == 0)
        Cost = (int)((1 * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));

    return Cost;
}
