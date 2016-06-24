#include "Defs.h"

#include "GUIStats.h"
#include "GUI.h"
#include "Menu.h"
#include "Stats.h"
#include "RPG.h"
#include "Utils.h"

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
    GUIIcon *ModulesIcon = GUIAddIcon(StatsPanel, "Modules Icon");
    GUILabel *ModulesLabel = GUIAddLabel(StatsPanel, "Modules Label");

    ModulesIcon->Control.X = 10;
    ModulesIcon->Control.Y = 12;
    ModulesIcon->Control.id = ++GUIElementID;
    ModulesIcon->Texture = "UMODA0";

    ModulesLabel->Control.X = 46;
    ModulesLabel->Control.Y = 30;
    ModulesLabel->Control.id = ++GUIElementID;
    ModulesLabel->Big = true;
    ModulesLabel->Color = "Green";

    //Stat cost to increase tooltip
/*     GUITooltip *StatIncTooltip = GUICreateTooltip();

    StatIncTooltip->Type = TT_TITLE;
    StatIncTooltip->Color = "White";
    StatIncTooltip->Title = "";
    StatIncTooltip->Text = "Null"; */

    //Strength
    GUIIcon *StrengthIcon = GUIAddIcon(StatsPanel, "Strength Icon");
    GUILabel *StrengthLabel = GUIAddLabel(StatsPanel, "Strength Label");
    GUILabel *StrGenLabel = GUIAddLabel(StatsPanel, "Strength General Label");
    GUIBar *StrXPBar = GUIAddBar(StatsPanel, "Strength XP Bar");
    GUIBar *StrXPBGBar = GUIAddBar(StatsPanel, "Strength XP BG Bar");

    GUIIcon *StrLvlDnIcon = GUIAddIcon(StatsPanel, "Strength Level Down Icon");
    GUIIcon *StrLvlUpIcon = GUIAddIcon(StatsPanel, "Strength Level Up Icon");
    GUIButton *StrLvlMaxButton = GUIAddButton(StatsPanel, "Strength Level Max Button");
    GUIButton *StrDtlButton = GUIAddButton(StatsPanel, "Strength Detail Button");
    //GUILabel *StrDtlLabel = GUIAddLabel(StatsPanel, "Strength Detail Label");
    //GUILabel *StrXPLabel = GUIAddLabel(StatsPanel, "Strength XP Label");

    StrengthIcon->Control.X = 22;
    StrengthIcon->Control.Y = 58;
    StrengthIcon->Control.id = ++GUIElementID;
    StrengthIcon->Texture = "STAT1";

    StrengthLabel->Control.X = 60;
    StrengthLabel->Control.Y = 64;
    StrengthLabel->Control.id = ++GUIElementID;
    StrengthLabel->Big = true;
    StrengthLabel->Color = StatColors[STAT_STRENGTH];

    StrGenLabel->Control.X = 60;
    StrGenLabel->Control.Y = 76;
    StrGenLabel->Control.id = ++GUIElementID;
    StrGenLabel->Text = "+ damage dealt";
    StrGenLabel->Color = "White";

    StrXPBar->Control.X = 60;
    StrXPBar->Control.Y = 90;
    StrXPBar->Control.id = ++GUIElementID;
    StrXPBar->Control.Height = 16;
    StrXPBar->Value = 0;
    StrXPBar->ValueMax = 150;
    StrXPBar->Texture = "StatBar1";

    GUIElementID += 150;

    StrXPBGBar->Control.X = 60;
    StrXPBGBar->Control.Y = 90;
    StrXPBGBar->Control.id = ++GUIElementID;
    StrXPBGBar->Control.Height = 16;
    StrXPBGBar->Value = 150;
    StrXPBGBar->ValueMax = 150;
    StrXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    StrLvlDnIcon->Control.X = 224;
    StrLvlDnIcon->Control.Y = 76;
    StrLvlDnIcon->Control.Width = 18;
    StrLvlDnIcon->Control.Height = 18;
    StrLvlDnIcon->Control.id = ++GUIElementID;
    StrLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    StrLvlDnIcon->Control.Click = (ControlClickFunc)IconDownClick;
    StrLvlDnIcon->Texture = "HLISTDN";
    StrLvlDnIcon->Enabled = false;

    StrLvlUpIcon->Control.X = 224;
    StrLvlUpIcon->Control.Y = 58;
    StrLvlUpIcon->Control.Width = 18;
    StrLvlUpIcon->Control.Height = 18;
    StrLvlUpIcon->Control.id = ++GUIElementID;
    StrLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    StrLvlUpIcon->Control.Click = (ControlClickFunc)IconUpClick;
    StrLvlUpIcon->Texture = "HLISTUP";

    StrLvlMaxButton->Control.X = 248;
    StrLvlMaxButton->Control.Y = 66;
    StrLvlMaxButton->Control.Width = 42;
    StrLvlMaxButton->Control.Height = 16;
    StrLvlMaxButton->Control.id = ++GUIElementID;
    StrLvlMaxButton->Text = "MAX";
    StrLvlMaxButton->Big = true;
    StrLvlMaxButton->Color = "Green";

    StrDtlButton->Control.X = 260;
    StrDtlButton->Control.Y = 82;
    StrDtlButton->Control.Width = 16;
    StrDtlButton->Control.Height = 16;
    StrDtlButton->Control.id = ++GUIElementID;
    StrDtlButton->Text = "...";
    StrDtlButton->Big = true;
    StrDtlButton->Color = "Green";

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
    GUIIcon *DefenseIcon = GUIAddIcon(StatsPanel, "Defense Icon");
    GUILabel *DefenseLabel = GUIAddLabel(StatsPanel, "Defense Label");
    GUILabel *DefGenLabel = GUIAddLabel(StatsPanel, "Defense General Label");
    //GUILabel *DefXPLabel = GUIAddLabel(StatsPanel, "Defense XP Label");
    GUIBar *DefXPBar = GUIAddBar(StatsPanel, "Defense XP Bar");
    GUIBar *DefXPBGBar = GUIAddBar(StatsPanel, "Defense XP BG Bar");

    GUIIcon *DefLvlDnIcon = GUIAddIcon(StatsPanel, "Defense Level Down Icon");
    GUIIcon *DefLvlUpIcon = GUIAddIcon(StatsPanel, "Defense Level Up Icon");
    GUIButton *DefLvlMaxButton = GUIAddButton(StatsPanel, "Defense Level Max Button");
    GUIButton *DefDtlButton = GUIAddButton(StatsPanel, "Defense Detail Button");

    DefenseIcon->Control.X = 22;
    DefenseIcon->Control.Y = 112 - 6;
    DefenseIcon->Control.id = ++GUIElementID;
    DefenseIcon->Texture = "STAT2";

    DefenseLabel->Control.X = 60;
    DefenseLabel->Control.Y = 118;
    DefenseLabel->Control.id = ++GUIElementID;
    DefenseLabel->Big = true;
    DefenseLabel->Color = StatColors[STAT_DEFENSE];

    DefGenLabel->Control.X = 60;
    DefGenLabel->Control.Y = 136;
    DefGenLabel->Control.id = ++GUIElementID;
    DefGenLabel->Text = "- damage taken\n- knockback";
    DefGenLabel->Color = "White";

    /* DefXPLabel->Control.X = 135;
    DefXPLabel->Control.Y = 157;
    DefXPLabel->Control.id = ++GUIElementID;
    DefXPLabel->Alignment = LA_CENTER;
    DefXPLabel->Color = "Grey";
    DefXPLabel->Text = ""; */

    DefXPBar->Control.X = 60;
    DefXPBar->Control.Y = 154;
    DefXPBar->Control.id = ++GUIElementID;
    DefXPBar->Control.Height = 16;
    DefXPBar->Value = 0;
    DefXPBar->ValueMax = 150;
    DefXPBar->Texture = "StatBar2";

    GUIElementID += 150;

    DefXPBGBar->Control.X = 60;
    DefXPBGBar->Control.Y = 154;
    DefXPBGBar->Control.id = ++GUIElementID;
    DefXPBGBar->Control.Height = 16;
    DefXPBGBar->Value = 150;
    DefXPBGBar->ValueMax = 150;
    DefXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    DefLvlDnIcon->Control.X = 224;
    DefLvlDnIcon->Control.Y = 130;
    DefLvlDnIcon->Control.Width = 18;
    DefLvlDnIcon->Control.Height = 18;
    DefLvlDnIcon->Control.id = ++GUIElementID;
    DefLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    DefLvlDnIcon->Texture = "HLISTDN";
    DefLvlDnIcon->Enabled = false;

    DefLvlUpIcon->Control.X = 224;
    DefLvlUpIcon->Control.Y = 112;
    DefLvlUpIcon->Control.Width = 18;
    DefLvlUpIcon->Control.Height = 18;
    DefLvlUpIcon->Control.id = ++GUIElementID;
    DefLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    DefLvlUpIcon->Texture = "HLISTUP";

    DefLvlMaxButton->Control.X = 248;
    DefLvlMaxButton->Control.Y = 120;
    DefLvlMaxButton->Control.Width = 42;
    DefLvlMaxButton->Control.Height = 16;
    DefLvlMaxButton->Control.id = ++GUIElementID;
    DefLvlMaxButton->Text = "MAX";
    DefLvlMaxButton->Big = true;
    DefLvlMaxButton->Color = "Green";

    DefDtlButton->Control.X = 260;
    DefDtlButton->Control.Y = 136;
    DefDtlButton->Control.Width = 16;
    DefDtlButton->Control.Height = 16;
    DefDtlButton->Control.id = ++GUIElementID;
    DefDtlButton->Text = "...";
    DefDtlButton->Big = true;
    DefDtlButton->Color = "Green";

    //Vitality
    GUIIcon *VitalityIcon = GUIAddIcon(StatsPanel, "Vitality Icon");
    GUILabel *VitalityLabel = GUIAddLabel(StatsPanel, "Vitality Label");
    GUILabel *VitGenLabel = GUIAddLabel(StatsPanel, "Vitality General Label");
    //GUILabel *VitXPLabel = GUIAddLabel(StatsPanel, "Vitality XP Label");
    GUIBar *VitXPBar = GUIAddBar(StatsPanel, "Vitality XP Bar");
    GUIBar *VitXPBGBar = GUIAddBar(StatsPanel, "Vitality XP BG Bar");

    GUIIcon *VitLvlDnIcon = GUIAddIcon(StatsPanel, "Vitality Level Down Icon");
    GUIIcon *VitLvlUpIcon = GUIAddIcon(StatsPanel, "Vitality Level Up Icon");
    GUIButton *VitLvlMaxButton = GUIAddButton(StatsPanel, "Vitality Level Max Button");
    GUIButton *VitDtlButton = GUIAddButton(StatsPanel, "Vitality Detail Button");

    VitalityIcon->Control.X = 22;
    VitalityIcon->Control.Y = 172;
    VitalityIcon->Control.id = ++GUIElementID;
    VitalityIcon->Texture = "STAT3";

    VitalityLabel->Control.X = 60;
    VitalityLabel->Control.Y = 178;
    VitalityLabel->Control.id = ++GUIElementID;
    VitalityLabel->Big = true;
    VitalityLabel->Color = StatColors[STAT_VITALITY];

    VitGenLabel->Control.X = 60;
    VitGenLabel->Control.Y = 200;
    VitGenLabel->Control.id = ++GUIElementID;
    VitGenLabel->Text = "+ max HP\n+ HP regen amount\n+ status effect resist";
    VitGenLabel->Color = "White";

    /* VitXPLabel->Control.X = 135;
    VitXPLabel->Control.Y = 225;
    VitXPLabel->Control.id = ++GUIElementID;
    VitXPLabel->Alignment = LA_CENTER;
    VitXPLabel->Color = "Grey";
    VitXPLabel->Text = ""; */

    VitXPBar->Control.X = 60;
    VitXPBar->Control.Y = 222;
    VitXPBar->Control.id = ++GUIElementID;
    VitXPBar->Control.Height = 16;
    VitXPBar->Value = 0;
    VitXPBar->ValueMax = 150;
    VitXPBar->Texture = "StatBar3";

    GUIElementID += 150;

    VitXPBGBar->Control.X = 60;
    VitXPBGBar->Control.Y = 222;
    VitXPBGBar->Control.id = ++GUIElementID;
    VitXPBGBar->Control.Height = 16;
    VitXPBGBar->Value = 150;
    VitXPBGBar->ValueMax = 150;
    VitXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    VitLvlDnIcon->Control.X = 224;
    VitLvlDnIcon->Control.Y = 190;
    VitLvlDnIcon->Control.Width = 18;
    VitLvlDnIcon->Control.Height = 18;
    VitLvlDnIcon->Control.id = ++GUIElementID;
    VitLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    VitLvlDnIcon->Texture = "HLISTDN";
    VitLvlDnIcon->Enabled = false;

    VitLvlUpIcon->Control.X = 224;
    VitLvlUpIcon->Control.Y = 172;
    VitLvlUpIcon->Control.Width = 18;
    VitLvlUpIcon->Control.Height = 18;
    VitLvlUpIcon->Control.id = ++GUIElementID;
    VitLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    VitLvlUpIcon->Texture = "HLISTUP";

    VitLvlMaxButton->Control.X = 248;
    VitLvlMaxButton->Control.Y = 180;
    VitLvlMaxButton->Control.Width = 42;
    VitLvlMaxButton->Control.Height = 16;
    VitLvlMaxButton->Control.id = ++GUIElementID;
    VitLvlMaxButton->Text = "MAX";
    VitLvlMaxButton->Big = true;
    VitLvlMaxButton->Color = "Green";

    VitDtlButton->Control.X = 260;
    VitDtlButton->Control.Y = 196;
    VitDtlButton->Control.Width = 16;
    VitDtlButton->Control.Height = 16;
    VitDtlButton->Control.id = ++GUIElementID;
    VitDtlButton->Text = "...";
    VitDtlButton->Big = true;
    VitDtlButton->Color = "Green";

    //Energy
    GUIIcon *EnergyIcon = GUIAddIcon(StatsPanel, "Energy Icon");
    GUILabel *EnergyLabel = GUIAddLabel(StatsPanel, "Energy Label");
    GUILabel *EngGenLabel = GUIAddLabel(StatsPanel, "Energy General Label");
    //GUILabel *EngXPLabel = GUIAddLabel(StatsPanel, "Energy XP Label");
    GUIBar *EngXPBar = GUIAddBar(StatsPanel, "Energy XP Bar");
    GUIBar *EngXPBGBar = GUIAddBar(StatsPanel, "Energy XP BG Bar");

    GUIIcon *EngLvlDnIcon = GUIAddIcon(StatsPanel, "Energy Level Down Icon");
    GUIIcon *EngLvlUpIcon = GUIAddIcon(StatsPanel, "Energy Level Up Icon");
    GUIButton *EngLvlMaxButton = GUIAddButton(StatsPanel, "Energy Level Max Button");
    GUIButton *EngDtlButton = GUIAddButton(StatsPanel, "Energy Detail Button");

    EnergyIcon->Control.X = 22;
    EnergyIcon->Control.Y = 236;
    EnergyIcon->Control.id = ++GUIElementID;
    EnergyIcon->Texture = "STAT4";

    EnergyLabel->Control.X = 60;
    EnergyLabel->Control.Y = 242;
    EnergyLabel->Control.id = ++GUIElementID;
    EnergyLabel->Big = true;
    EnergyLabel->Color = StatColors[STAT_ENERGY];

    EngGenLabel->Control.X = 60;
    EngGenLabel->Control.Y = 268;
    EngGenLabel->Control.id = ++GUIElementID;
    EngGenLabel->Text = "+ max EP\n+ EP regen amount\n+ aura duration\n+ aura effect range";
    EngGenLabel->Color = "White";

    /* EngXPLabel->Control.X = 135;
    EngXPLabel->Control.Y = 295;
    EngXPLabel->Control.id = ++GUIElementID;
    EngXPLabel->Alignment = LA_CENTER;
    EngXPLabel->Color = "Grey";
    EngXPLabel->Text = ""; */

    EngXPBar->Control.X = 60;
    EngXPBar->Control.Y = 292;
    EngXPBar->Control.id = ++GUIElementID;
    EngXPBar->Control.Height = 16;
    EngXPBar->Value = 0;
    EngXPBar->ValueMax = 150;
    EngXPBar->Texture = "StatBar4";

    GUIElementID += 150;

    EngXPBGBar->Control.X = 60;
    EngXPBGBar->Control.Y = 292;
    EngXPBGBar->Control.id = ++GUIElementID;
    EngXPBGBar->Control.Height = 16;
    EngXPBGBar->Value = 150;
    EngXPBGBar->ValueMax = 150;
    EngXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    EngLvlDnIcon->Control.X = 224;
    EngLvlDnIcon->Control.Y = 254;
    EngLvlDnIcon->Control.Width = 18;
    EngLvlDnIcon->Control.Height = 18;
    EngLvlDnIcon->Control.id = ++GUIElementID;
    EngLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    EngLvlDnIcon->Texture = "HLISTDN";
    EngLvlDnIcon->Enabled = false;

    EngLvlUpIcon->Control.X = 224;
    EngLvlUpIcon->Control.Y = 236;
    EngLvlUpIcon->Control.Width = 18;
    EngLvlUpIcon->Control.Height = 18;
    EngLvlUpIcon->Control.id = ++GUIElementID;
    EngLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    EngLvlUpIcon->Texture = "HLISTUP";

    EngLvlMaxButton->Control.X = 248;
    EngLvlMaxButton->Control.Y = 244;
    EngLvlMaxButton->Control.Width = 42;
    EngLvlMaxButton->Control.Height = 16;
    EngLvlMaxButton->Control.id = ++GUIElementID;
    EngLvlMaxButton->Text = "MAX";
    EngLvlMaxButton->Big = true;
    EngLvlMaxButton->Color = "Green";

    EngDtlButton->Control.X = 260;
    EngDtlButton->Control.Y = 260;
    EngDtlButton->Control.Width = 16;
    EngDtlButton->Control.Height = 16;
    EngDtlButton->Control.id = ++GUIElementID;
    EngDtlButton->Text = "...";
    EngDtlButton->Big = true;
    EngDtlButton->Color = "Green";

    //Regen
    GUIIcon *RegenIcon = GUIAddIcon(StatsPanel, "Regen Icon");
    GUILabel *RegenLabel = GUIAddLabel(StatsPanel, "Regen Label");
    GUILabel *RgnGenLabel = GUIAddLabel(StatsPanel, "Regen General Label");
    //GUILabel *RgnXPLabel = GUIAddLabel(StatsPanel, "Regen XP Label");
    GUIBar *RgnXPBar = GUIAddBar(StatsPanel, "Regen XP Bar");
    GUIBar *RgnXPBGBar = GUIAddBar(StatsPanel, "Regen XP BG Bar");

    GUIIcon *RgnLvlDnIcon = GUIAddIcon(StatsPanel, "Regen Level Down Icon");
    GUIIcon *RgnLvlUpIcon = GUIAddIcon(StatsPanel, "Regen Level Up Icon");
    GUIButton *RgnLvlMaxButton = GUIAddButton(StatsPanel, "Regen Level Max Button");
    GUIButton *RgnDtlButton = GUIAddButton(StatsPanel, "Regen Detail Button");

    RegenIcon->Control.X = 22;
    RegenIcon->Control.Y = 308;
    RegenIcon->Control.id = ++GUIElementID;
    RegenIcon->Texture = "STAT5";

    RegenLabel->Control.X = 60;
    RegenLabel->Control.Y = 314;
    RegenLabel->Control.id = ++GUIElementID;
    RegenLabel->Big = true;
    RegenLabel->Color = StatColors[STAT_REGENERATION];

    RgnGenLabel->Control.X = 60;
    RgnGenLabel->Control.Y = 325;
    RgnGenLabel->Control.id = ++GUIElementID;
    RgnGenLabel->Text = "+ regen frequency";
    RgnGenLabel->Color = "White";

    /* RgnXPLabel->Control.X = 135;
    RgnXPLabel->Control.Y = 339;
    RgnXPLabel->Control.id = ++GUIElementID;
    RgnXPLabel->Alignment = LA_CENTER;
    RgnXPLabel->Color = "Grey";
    RgnXPLabel->Text = ""; */

    RgnXPBar->Control.X = 60;
    RgnXPBar->Control.Y = 336;
    RgnXPBar->Control.id = ++GUIElementID;
    RgnXPBar->Control.Height = 16;
    RgnXPBar->Value = 0;
    RgnXPBar->ValueMax = 150;
    RgnXPBar->Texture = "StatBar5";

    GUIElementID += 150;

    RgnXPBGBar->Control.X = 60;
    RgnXPBGBar->Control.Y = 336;
    RgnXPBGBar->Control.id = ++GUIElementID;
    RgnXPBGBar->Control.Height = 16;
    RgnXPBGBar->Value = 150;
    RgnXPBGBar->ValueMax = 150;
    RgnXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    RgnLvlDnIcon->Control.X = 224;
    RgnLvlDnIcon->Control.Y = 326;
    RgnLvlDnIcon->Control.Width = 18;
    RgnLvlDnIcon->Control.Height = 18;
    RgnLvlDnIcon->Control.id = ++GUIElementID;
    RgnLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    RgnLvlDnIcon->Texture = "HLISTDN";
    RgnLvlDnIcon->Enabled = false;

    RgnLvlUpIcon->Control.X = 224;
    RgnLvlUpIcon->Control.Y = 308;
    RgnLvlUpIcon->Control.Width = 18;
    RgnLvlUpIcon->Control.Height = 18;
    RgnLvlUpIcon->Control.id = ++GUIElementID;
    RgnLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    RgnLvlUpIcon->Texture = "HLISTUP";

    RgnLvlMaxButton->Control.X = 248;
    RgnLvlMaxButton->Control.Y = 316;
    RgnLvlMaxButton->Control.Width = 42;
    RgnLvlMaxButton->Control.Height = 16;
    RgnLvlMaxButton->Control.id = ++GUIElementID;
    RgnLvlMaxButton->Text = "MAX";
    RgnLvlMaxButton->Big = true;
    RgnLvlMaxButton->Color = "Green";

    RgnDtlButton->Control.X = 260;
    RgnDtlButton->Control.Y = 332;
    RgnDtlButton->Control.Width = 16;
    RgnDtlButton->Control.Height = 16;
    RgnDtlButton->Control.id = ++GUIElementID;
    RgnDtlButton->Text = "...";
    RgnDtlButton->Big = true;
    RgnDtlButton->Color = "Green";

    //Agility
    GUIIcon *AgilityIcon = GUIAddIcon(StatsPanel, "Agility Icon");
    GUILabel *AgilityLabel = GUIAddLabel(StatsPanel, "Agility Label");
    GUILabel *AglGenLabel = GUIAddLabel(StatsPanel, "Agility General Label");
    //GUILabel *AglXPLabel = GUIAddLabel(StatsPanel, "Agility XP Label");
    GUIBar *AglXPBar = GUIAddBar(StatsPanel, "Agility XP Bar");
    GUIBar *AglXPBGBar = GUIAddBar(StatsPanel, "Agility XP BG Bar");

    GUIIcon *AglLvlDnIcon = GUIAddIcon(StatsPanel, "Agility Level Down Icon");
    GUIIcon *AglLvlUpIcon = GUIAddIcon(StatsPanel, "Agility Level Up Icon");
    GUIButton *AglLvlMaxButton = GUIAddButton(StatsPanel, "Agility Level Max Button");
    GUIButton *AglDtlButton = GUIAddButton(StatsPanel, "Agility Detail Button");

    AgilityIcon->Control.X = 22;
    AgilityIcon->Control.Y = 352;
    AgilityIcon->Control.id = ++GUIElementID;
    AgilityIcon->Texture = "STAT6";

    AgilityLabel->Control.X = 60;
    AgilityLabel->Control.Y = 358;
    AgilityLabel->Control.id = ++GUIElementID;
    AgilityLabel->Big = true;
    AgilityLabel->Color = StatColors[STAT_AGILITY];

    AglGenLabel->Control.X = 60;
    AglGenLabel->Control.Y = 384;
    AglGenLabel->Control.id = ++GUIElementID;
    AglGenLabel->Text = "+ movement speed\n+ jump height\n+ weapon fire rate\n+ survival chance";
    AglGenLabel->Color = "White";

    /* AglXPLabel->Control.X = 135;
    AglXPLabel->Control.Y = 411;
    AglXPLabel->Control.id = ++GUIElementID;
    AglXPLabel->Alignment = LA_CENTER;
    AglXPLabel->Color = "Grey";
    AglXPLabel->Text = ""; */

    AglXPBar->Control.X = 60;
    AglXPBar->Control.Y = 408;
    AglXPBar->Control.id = ++GUIElementID;
    AglXPBar->Control.Height = 16;
    AglXPBar->Value = 0;
    AglXPBar->ValueMax = 150;
    AglXPBar->Texture = "StatBar6";

    GUIElementID += 150;

    AglXPBGBar->Control.X = 60;
    AglXPBGBar->Control.Y = 408;
    AglXPBGBar->Control.id = ++GUIElementID;
    AglXPBGBar->Control.Height = 16;
    AglXPBGBar->Value = 150;
    AglXPBGBar->ValueMax = 150;
    AglXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    AglLvlDnIcon->Control.X = 224;
    AglLvlDnIcon->Control.Y = 370;
    AglLvlDnIcon->Control.Width = 18;
    AglLvlDnIcon->Control.Height = 18;
    AglLvlDnIcon->Control.id = ++GUIElementID;
    AglLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    AglLvlDnIcon->Texture = "HLISTDN";
    AglLvlDnIcon->Enabled = false;

    AglLvlUpIcon->Control.X = 224;
    AglLvlUpIcon->Control.Y = 352;
    AglLvlUpIcon->Control.Width = 18;
    AglLvlUpIcon->Control.Height = 18;
    AglLvlUpIcon->Control.id = ++GUIElementID;
    AglLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    AglLvlUpIcon->Texture = "HLISTUP";

    AglLvlMaxButton->Control.X = 248;
    AglLvlMaxButton->Control.Y = 360;
    AglLvlMaxButton->Control.Width = 42;
    AglLvlMaxButton->Control.Height = 16;
    AglLvlMaxButton->Control.id = ++GUIElementID;
    AglLvlMaxButton->Text = "MAX";
    AglLvlMaxButton->Big = true;
    AglLvlMaxButton->Color = "Green";

    AglDtlButton->Control.X = 260;
    AglDtlButton->Control.Y = 376;
    AglDtlButton->Control.Width = 16;
    AglDtlButton->Control.Height = 16;
    AglDtlButton->Control.id = ++GUIElementID;
    AglDtlButton->Text = "...";
    AglDtlButton->Big = true;
    AglDtlButton->Color = "Green";

    //Capacity
    GUIIcon *CapacityIcon = GUIAddIcon(StatsPanel, "Capacity Icon");
    GUILabel *CapacityLabel = GUIAddLabel(StatsPanel, "Capacity Label");
    GUILabel *CapGenLabel = GUIAddLabel(StatsPanel, "Capacity General Label");
    //GUILabel *CapXPLabel = GUIAddLabel(StatsPanel, "Capacity XP Label");
    GUIBar *CapXPBar = GUIAddBar(StatsPanel, "Capacity XP Bar");
    GUIBar *CapXPBGBar = GUIAddBar(StatsPanel, "Capacity XP BG Bar");

    GUIIcon *CapLvlDnIcon = GUIAddIcon(StatsPanel, "Capacity Level Down Icon");
    GUIIcon *CapLvlUpIcon = GUIAddIcon(StatsPanel, "Capacity Level Up Icon");
    GUIButton *CapLvlMaxButton = GUIAddButton(StatsPanel, "Capacity Level Max Button");
    GUIButton *CapDtlButton = GUIAddButton(StatsPanel, "Capacity Detail Button");

    CapacityIcon->Control.X = 22;
    CapacityIcon->Control.Y = 416;
    CapacityIcon->Control.id = ++GUIElementID;
    CapacityIcon->Texture = "STAT7";

    CapacityLabel->Control.X = 60;
    CapacityLabel->Control.Y = 426;
    CapacityLabel->Control.id = ++GUIElementID;
    CapacityLabel->Big = true;
    CapacityLabel->Color = StatColors[STAT_CAPACITY];

    CapGenLabel->Control.X = 60;
    CapGenLabel->Control.Y = 456;
    CapGenLabel->Control.id = ++GUIElementID;
    CapGenLabel->Text = "+ inventory capacity\n+ ammo capacity\n+ aug battery size\n+ stim capacity\n+ medkit capacity";
    CapGenLabel->Color = "White";

    /* CapXPLabel->Control.X = 135;
    CapXPLabel->Control.Y = 489;
    CapXPLabel->Control.id = ++GUIElementID;
    CapXPLabel->Alignment = LA_CENTER;
    CapXPLabel->Color = "Grey";
    CapXPLabel->Text = ""; */

    CapXPBar->Control.X = 60;
    CapXPBar->Control.Y = 486;
    CapXPBar->Control.id = ++GUIElementID;
    CapXPBar->Control.Height = 16;
    CapXPBar->Value = 0;
    CapXPBar->ValueMax = 150;
    CapXPBar->Texture = "StatBar7";

    GUIElementID += 150;

    CapXPBGBar->Control.X = 60;
    CapXPBGBar->Control.Y = 486;
    CapXPBGBar->Control.id = ++GUIElementID;
    CapXPBGBar->Control.Height = 16;
    CapXPBGBar->Value = 150;
    CapXPBGBar->ValueMax = 150;
    CapXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    CapLvlDnIcon->Control.X = 224;
    CapLvlDnIcon->Control.Y = 438;
    CapLvlDnIcon->Control.Width = 18;
    CapLvlDnIcon->Control.Height = 18;
    CapLvlDnIcon->Control.id = ++GUIElementID;
    CapLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    CapLvlDnIcon->Texture = "HLISTDN";
    CapLvlDnIcon->Enabled = false;

    CapLvlUpIcon->Control.X = 224;
    CapLvlUpIcon->Control.Y = 420;
    CapLvlUpIcon->Control.Width = 18;
    CapLvlUpIcon->Control.Height = 18;
    CapLvlUpIcon->Control.id = ++GUIElementID;
    CapLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    CapLvlUpIcon->Texture = "HLISTUP";

    CapLvlMaxButton->Control.X = 248;
    CapLvlMaxButton->Control.Y = 428;
    CapLvlMaxButton->Control.Width = 42;
    CapLvlMaxButton->Control.Height = 16;
    CapLvlMaxButton->Control.id = ++GUIElementID;
    CapLvlMaxButton->Text = "MAX";
    CapLvlMaxButton->Big = true;
    CapLvlMaxButton->Color = "Green";

    CapDtlButton->Control.X = 260;
    CapDtlButton->Control.Y = 444;
    CapDtlButton->Control.Width = 16;
    CapDtlButton->Control.Height = 16;
    CapDtlButton->Control.id = ++GUIElementID;
    CapDtlButton->Text = "...";
    CapDtlButton->Big = true;
    CapDtlButton->Color = "Green";

    //Luck
    GUIIcon *LuckIcon = GUIAddIcon(StatsPanel, "Luck Icon");
    GUILabel *LuckLabel = GUIAddLabel(StatsPanel, "Luck Label");
    GUILabel *LckGenLabel = GUIAddLabel(StatsPanel, "Luck General Label");
    //GUILabel *LckXPLabel = GUIAddLabel(StatsPanel, "Luck XP Label");
    GUIBar *LckXPBar = GUIAddBar(StatsPanel, "Luck XP Bar");
    GUIBar *LckXPBGBar = GUIAddBar(StatsPanel, "Luck XP BG Bar");

    GUIIcon *LckLvlDnIcon = GUIAddIcon(StatsPanel, "Luck Level Down Icon");
    GUIIcon *LckLvlUpIcon = GUIAddIcon(StatsPanel, "Luck Level Up Icon");
    GUIButton *LckLvlMaxButton = GUIAddButton(StatsPanel, "Luck Level Max Button");
    GUIButton *LckDtlButton = GUIAddButton(StatsPanel, "Luck Detail Button");

    LuckIcon->Control.X = 22;
    LuckIcon->Control.Y = 492;
    LuckIcon->Control.id = ++GUIElementID;
    LuckIcon->Texture = "STAT8";

    LuckLabel->Control.X = 60;
    LuckLabel->Control.Y = 506;
    LuckLabel->Control.id = ++GUIElementID;
    LuckLabel->Big = true;
    LuckLabel->Color = StatColors[STAT_LUCK];

    LckGenLabel->Control.X = 60;
    LckGenLabel->Control.Y = 518;
    LckGenLabel->Control.id = ++GUIElementID;
    LckGenLabel->Text = "+ loot drops";
    LckGenLabel->Color = "White";

    /* LckXPLabel->Control.X = 135;
    LckXPLabel->Control.Y = 533;
    LckXPLabel->Control.id = ++GUIElementID;
    LckXPLabel->Alignment = LA_CENTER;
    LckXPLabel->Color = "Grey";
    LckXPLabel->Text = ""; */

    LckXPBar->Control.X = 60;
    LckXPBar->Control.Y = 530;
    LckXPBar->Control.id = ++GUIElementID;
    LckXPBar->Control.Height = 16;
    LckXPBar->Value = 0;
    LckXPBar->ValueMax = 150;
    LckXPBar->Texture = "StatBar8";

    GUIElementID += 150;

    LckXPBGBar->Control.X = 60;
    LckXPBGBar->Control.Y = 530;
    LckXPBGBar->Control.id = ++GUIElementID;
    LckXPBGBar->Control.Height = 16;
    LckXPBGBar->Value = 150;
    LckXPBGBar->ValueMax = 150;
    LckXPBGBar->Texture = "StatBarB";

    GUIElementID += 150;

    LckLvlDnIcon->Control.X = 224;
    LckLvlDnIcon->Control.Y = 518;
    LckLvlDnIcon->Control.Width = 18;
    LckLvlDnIcon->Control.Height = 18;
    LckLvlDnIcon->Control.id = ++GUIElementID;
    LckLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    LckLvlDnIcon->Texture = "HLISTDN";
    LckLvlDnIcon->Enabled = false;

    LckLvlUpIcon->Control.X = 224;
    LckLvlUpIcon->Control.Y = 500;
    LckLvlUpIcon->Control.Width = 18;
    LckLvlUpIcon->Control.Height = 18;
    LckLvlUpIcon->Control.id = ++GUIElementID;
    LckLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    LckLvlUpIcon->Texture = "HLISTUP";

    LckLvlMaxButton->Control.X = 248;
    LckLvlMaxButton->Control.Y = 508;
    LckLvlMaxButton->Control.Width = 42;
    LckLvlMaxButton->Control.Height = 16;
    LckLvlMaxButton->Control.id = ++GUIElementID;
    LckLvlMaxButton->Text = "MAX";
    LckLvlMaxButton->Big = true;
    LckLvlMaxButton->Color = "Green";

    LckDtlButton->Control.X = 260;
    LckDtlButton->Control.Y = 524;
    LckDtlButton->Control.Width = 16;
    LckDtlButton->Control.Height = 16;
    LckDtlButton->Control.id = ++GUIElementID;
    LckDtlButton->Text = "...";
    LckDtlButton->Big = true;
    LckDtlButton->Color = "Green";

    //Order Form Border
    GUIBorder *OrderFormBorder = GUIAddBorder(StatsPanel, "Order Form Border");

    OrderFormBorder->Control.X = 600;
    OrderFormBorder->Control.Y = 16;
    OrderFormBorder->Control.Width = 196;
    OrderFormBorder->Control.Height = 532;
    OrderFormBorder->Control.id = MAKE_ID('O','F','B','R');

    //Clear/Confirm Buttons
    GUIButton *OrderClearButton = GUIAddButton(StatsPanel, "Order Form Clear Button");
    GUIButton *OrderConfirmButton = GUIAddButton(StatsPanel, "Order Form Confirm Button");

    OrderClearButton->Control.X = 610;
    OrderClearButton->Control.Y = 520;
    OrderClearButton->Control.id = ++GUIElementID;
    OrderClearButton->Control.Width = 64;
    OrderClearButton->Control.Height = 16;
    OrderClearButton->Text = "CLEAR";
    OrderClearButton->Big = true;
    OrderClearButton->Color = "Dark Grey";
    OrderClearButton->HoverColor = "Dark Grey";

    OrderConfirmButton->Control.X = 694;
    OrderConfirmButton->Control.Y = 520;
    OrderConfirmButton->Control.id = ++GUIElementID;
    OrderConfirmButton->Control.Width = 90;
    OrderConfirmButton->Control.Height = 16;
    OrderConfirmButton->Text = "CONFIRM";
    OrderConfirmButton->Big = true;
    OrderConfirmButton->Color = "Dark Grey";
    OrderConfirmButton->HoverColor = "Dark Grey";
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


    GUILabel *ModulesLabel = (GUILabel *)GUIControlByName(StatsPanel, "Modules Label");

    GUILabel *StrengthLabel = (GUILabel *)GUIControlByName(StatsPanel, "Strength Label");
    GUILabel *DefenseLabel = (GUILabel *)GUIControlByName(StatsPanel, "Defense Label");
    GUILabel *VitalityLabel = (GUILabel *)GUIControlByName(StatsPanel, "Vitality Label");
    GUILabel *EnergyLabel = (GUILabel *)GUIControlByName(StatsPanel, "Energy Label");
    GUILabel *RegenLabel = (GUILabel *)GUIControlByName(StatsPanel, "Regen Label");
    GUILabel *AgilityLabel = (GUILabel *)GUIControlByName(StatsPanel, "Agility Label");
    GUILabel *CapacityLabel = (GUILabel *)GUIControlByName(StatsPanel, "Capacity Label");
    GUILabel *LuckLabel = (GUILabel *)GUIControlByName(StatsPanel, "Luck Label");

    //GUILabel *StrDtlLabel = (GUILabel *)GUIControlByName(StatsPanel, "Strength Detail Label");

    /* GUILabel *XPLabel[STAT_MAX] =
    {
        (GUILabel *)GUIControlByName(StatsPanel, "Strength XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Defense XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Vitality XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Energy XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Regen XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Agility XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Capacity XP Label"),
        (GUILabel *)GUIControlByName(StatsPanel, "Luck XP Label")
    }; */

    GUIBar *XPBar[STAT_MAX] =
    {
        (GUIBar *)GUIControlByName(StatsPanel, "Strength XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Defense XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Vitality XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Energy XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Regen XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Agility XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Capacity XP Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Luck XP Bar")
    };

    GUIBar *XPBGBar[STAT_MAX] =
    {
        (GUIBar *)GUIControlByName(StatsPanel, "Strength XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Defense XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Vitality XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Energy XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Regen XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Agility XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Capacity XP BG Bar"),
        (GUIBar *)GUIControlByName(StatsPanel, "Luck XP BG Bar")
    };

    GUIIcon *LvlIcon[STAT_MAX * 2] =
    {
        (GUIIcon *)GUIControlByName(StatsPanel, "Strength Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Strength Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Defense Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Defense Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Vitality Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Vitality Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Energy Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Energy Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Regen Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Regen Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Agility Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Agility Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Capacity Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Capacity Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Luck Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Luck Level Down Icon")
    };

    //Update Current Modules
    ModulesLabel->Text = StrParam("%d", CheckInventory("DRPGModule"));

    //Update Current Stats
    StrengthLabel->Text = StrParam("Strength: %d", Player.Strength);
    DefenseLabel->Text = StrParam("Defense: %d", Player.Defense);
    VitalityLabel->Text = StrParam("Vitality: %d", Player.Vitality);
    EnergyLabel->Text = StrParam("Energy: %d", Player.Energy);
    RegenLabel->Text = StrParam("Regen: %d", Player.Regeneration);
    AgilityLabel->Text = StrParam("Agility: %d", Player.Agility);
    CapacityLabel->Text = StrParam("Capacity: %d", Player.Capacity);
    LuckLabel->Text = StrParam("Luck: %d", Player.Luck);

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
        (GUIIcon *)GUIControlByName(StatsPanel, "Strength Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Defense Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Vitality Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Energy Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Regen Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Agility Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Capacity Level Up Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Luck Level Up Icon")
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
        (GUIIcon *)GUIControlByName(StatsPanel, "Strength Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Defense Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Vitality Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Energy Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Regen Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Agility Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Capacity Level Down Icon"),
        (GUIIcon *)GUIControlByName(StatsPanel, "Luck Level Down Icon")
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
