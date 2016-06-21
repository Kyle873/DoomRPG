#include "Defs.h"

#include "GUIMenu.h"

#include "GUIOverview.h"
#include "GUIStats.h"

#include "GUI.h"
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
    CreateStatsPanel();
}
