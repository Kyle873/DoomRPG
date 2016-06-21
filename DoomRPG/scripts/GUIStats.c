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
    StrLvlDnIcon->Control.id = ++GUIElementID;
    StrLvlDnIcon->Control.Hover = (ControlHoverFunc)IconHover;
    StrLvlDnIcon->Texture = "HLISTDN";
    StrLvlDnIcon->Alpha = 0.4;
    
    StrLvlUpIcon->Control.X = 224;
    StrLvlUpIcon->Control.Y = 58;
    StrLvlUpIcon->Control.id = ++GUIElementID;
    StrLvlUpIcon->Control.Hover = (ControlHoverFunc)IconHover;
    StrLvlUpIcon->Texture = "HLISTUP";
    //StrLvlUpIcon->Alpha = 0.25;
    
    StrLvlMaxButton->Control.X = 248;
    StrLvlMaxButton->Control.Y = 66;
    StrLvlMaxButton->Control.Width = 0;
    StrLvlMaxButton->Control.Height = 0;
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
    DefGenLabel->Control.Y = 138;
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
    
    //Vitality
    GUIIcon *VitalityIcon = GUIAddIcon(StatsPanel, "Vitality Icon");
    GUILabel *VitalityLabel = GUIAddLabel(StatsPanel, "Vitality Label");
    GUILabel *VitGenLabel = GUIAddLabel(StatsPanel, "Vitality General Label");
    //GUILabel *VitXPLabel = GUIAddLabel(StatsPanel, "Vitality XP Label");
    GUIBar *VitXPBar = GUIAddBar(StatsPanel, "Vitality XP Bar");
    GUIBar *VitXPBGBar = GUIAddBar(StatsPanel, "Vitality XP BG Bar");
    
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
    VitGenLabel->Text = "+ max HP\n+ amount of HP regenerated\n+ resistance to status effects";
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
    
    //Energy
    GUIIcon *EnergyIcon = GUIAddIcon(StatsPanel, "Energy Icon");
    GUILabel *EnergyLabel = GUIAddLabel(StatsPanel, "Energy Label");
    GUILabel *EngGenLabel = GUIAddLabel(StatsPanel, "Energy General Label");
    //GUILabel *EngXPLabel = GUIAddLabel(StatsPanel, "Energy XP Label");
    GUIBar *EngXPBar = GUIAddBar(StatsPanel, "Energy XP Bar");
    GUIBar *EngXPBGBar = GUIAddBar(StatsPanel, "Energy XP BG Bar");
    
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
    EngGenLabel->Text = "+ max EP\n+ amount of EP regenerated\n+ aura duration\n+ aura effect range";
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
   
    //Regen
    GUIIcon *RegenIcon = GUIAddIcon(StatsPanel, "Regen Icon");
    GUILabel *RegenLabel = GUIAddLabel(StatsPanel, "Regen Label");
    GUILabel *RgnGenLabel = GUIAddLabel(StatsPanel, "Regen General Label");
    //GUILabel *RgnXPLabel = GUIAddLabel(StatsPanel, "Regen XP Label");
    GUIBar *RgnXPBar = GUIAddBar(StatsPanel, "Regen XP Bar");
    GUIBar *RgnXPBGBar = GUIAddBar(StatsPanel, "Regen XP BG Bar");
    
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
    RgnGenLabel->Text = "+ regeneration frequency";
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
    
    //Agility
    GUIIcon *AgilityIcon = GUIAddIcon(StatsPanel, "Agility Icon");
    GUILabel *AgilityLabel = GUIAddLabel(StatsPanel, "Agility Label");
    GUILabel *AglGenLabel = GUIAddLabel(StatsPanel, "Agility General Label");
    //GUILabel *AglXPLabel = GUIAddLabel(StatsPanel, "Agility XP Label");
    GUIBar *AglXPBar = GUIAddBar(StatsPanel, "Agility XP Bar");
    GUIBar *AglXPBGBar = GUIAddBar(StatsPanel, "Agility XP BG Bar");
    
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
    AglGenLabel->Text = "+ movement speed\n+ jump height\n+ weapon fire rate\n+ survival bonus chance";
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
    
    //Capacity
    GUIIcon *CapacityIcon = GUIAddIcon(StatsPanel, "Capacity Icon");
    GUILabel *CapacityLabel = GUIAddLabel(StatsPanel, "Capacity Label");
    GUILabel *CapGenLabel = GUIAddLabel(StatsPanel, "Capacity General Label");
    //GUILabel *CapXPLabel = GUIAddLabel(StatsPanel, "Capacity XP Label");
    GUIBar *CapXPBar = GUIAddBar(StatsPanel, "Capacity XP Bar");
    GUIBar *CapXPBGBar = GUIAddBar(StatsPanel, "Capacity XP BG Bar");

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
    CapGenLabel->Text = "+ inventory capacity\n+ ammo capacity\n+ aug battery size\n+ stim compounds capacity\n+ medkit capacity";
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
    
    //Luck
    GUIIcon *LuckIcon = GUIAddIcon(StatsPanel, "Luck Icon");
    GUILabel *LuckLabel = GUIAddLabel(StatsPanel, "Luck Label");
    GUILabel *LckGenLabel = GUIAddLabel(StatsPanel, "Luck General Label");
    //GUILabel *LckXPLabel = GUIAddLabel(StatsPanel, "Luck XP Label");
    GUIBar *LckXPBar = GUIAddBar(StatsPanel, "Luck XP Bar");
    GUIBar *LckXPBGBar = GUIAddBar(StatsPanel, "Luck XP BG Bar");
    
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
    LckGenLabel->Text = "+ loot drop types and amounts";
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
    
    GUIUpdatePanelControls(StatsPanel);
}

NamedScript void ButtonClicked(GUIButton *GUIObj)
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
    
    /* if (GUIObj->Alpha == 0)
    {
        
    } */
    return;
}

int CostOfStatUpgrade(int *Stat)
{
    int Cost = (int)((((fixed)*Stat + 1) * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));
    if (Cost < 0)
        Cost = -Cost;
    else if (Cost == 0)
        Cost = (int)((1 * (fixed)MODULE_STAT_MULT) * GetCVarFixed("drpg_module_statfactor"));
    
    return Cost;
}