#include "Defs.h"

#include "GUI.h"
#include "Map.h"
#include "Menu.h"
#include "Stats.h"
#include "RPG.h"
#include "Utils.h"

static fixed GUITestX = 0.0;
static fixed GUITestY = 0.0;

NamedScript Console void ToggleGUI()
{
    if (!Player.GUI.Created) return;
    
    Player.GUI.Open = !Player.GUI.Open;
    
    if (Player.GUI.Open)
        UpdateGUIMenu();
}

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

NamedScript void UpdateGUIMenu()
{
    // Menu entry point
    ActivatorSound("gui/open", 127);
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    
    // Move the mouse to the center of the menu
    Player.GUI.Mouse.X = GUI_WIDTH / 2;
    Player.GUI.Mouse.Y = GUI_HEIGHT / 2;
    
    // Switch to the Overview panel
    Player.GUI.TabStrip.ActiveTab = PANEL_MAIN;
    
    // Menu stuff
    while (Player.GUI.Open)
    {
        Player.GUI.Mouse.ActiveTooltip = NULL;
        
        UpdateTabs();
        UpdateGUICursor();
        DrawBackgroundWindow();
        
        Delay(1);
    }
    
    ActivatorSound("gui/close", 127);
    SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
}

NamedScript void DrawBackgroundWindow()
{
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    DrawBorder("Bor", GUI_BACK_ID - 10, 8, WINDOW_X, WINDOW_Y, GUI_WIDTH, GUI_HEIGHT);
    
    SetHudClipRect(0, 0, 0, 0);
    
    if (Player.GUI.GlowLine.Delay < 1)
        DrawGlowLine();
    else
        Player.GUI.GlowLine.Delay--;
    
    PrintSpriteAddAlpha("GStatic1", GUI_BACK_ID - 1, WINDOW_X + 0.1, WINDOW_Y + 0.1, 0.03, 0.5);
    PrintSpriteAlpha("GUIBack", GUI_BACK_ID, WINDOW_X + 0.1, WINDOW_Y + 0.1, 0.03, 0.75);
}

NamedScript void DrawGlowLine()
{
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    SetHudClipRect(WINDOW_X, WINDOW_Y, GUI_WIDTH, GUI_HEIGHT);
    PrintSpriteAdd("ScanLine", GUI_BACK_ID - 2, 0.1, (fixed)Player.GUI.GlowLine.Position + 0.1, 0.03);
    SetHudClipRect(0, 0, 0, 0);
    
    Player.GUI.GlowLine.Position += 4;
    
    if (Player.GUI.GlowLine.Position >= GUI_HEIGHT + WINDOW_Y)
    {
        Player.GUI.GlowLine.Position = WINDOW_Y - 140;
        Player.GUI.GlowLine.Delay = 35 * 2;
    }
}

NamedScript void UpdateGUICursor()
{
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Get X/Y input
    Player.GUI.Mouse.XAdd = GetPlayerInput(PlayerNumber(), INPUT_YAW);
    Player.GUI.Mouse.YAdd = GetPlayerInput(PlayerNumber(), INPUT_PITCH);
    
    // Get Buttons
    Player.GUI.Mouse.Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
    Player.GUI.Mouse.OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
    
    // Add X/Y input to current position
    Player.GUI.Mouse.X -= Player.GUI.Mouse.XAdd / GetCVar("drpg_menu_sensitivity_x");
    Player.GUI.Mouse.Y -= Player.GUI.Mouse.YAdd / GetCVar("drpg_menu_sensitivity_y");
    
    // Check resolution boundaries
    if (Player.GUI.Mouse.X < 0)
        Player.GUI.Mouse.X = 0;
    if (Player.GUI.Mouse.Y < 0)
        Player.GUI.Mouse.Y = 0;
    if (Player.GUI.Mouse.X > GUI_WIDTH)
        Player.GUI.Mouse.X = GUI_WIDTH;
    if (Player.GUI.Mouse.Y > GUI_HEIGHT)
        Player.GUI.Mouse.Y = GUI_HEIGHT;
    
    // Mouse Input
    if (Player.GUI.Mouse.Buttons & BT_ATTACK)
        Player.GUI.Mouse.LeftButtonDown = true;
    else
        Player.GUI.Mouse.LeftButtonDown = false;
    if (Player.GUI.Mouse.Buttons & BT_ATTACK && !(Player.GUI.Mouse.OldButtons & BT_ATTACK))
        Player.GUI.Mouse.LeftButton = true;
    else
        Player.GUI.Mouse.LeftButton = false;
    if (Player.GUI.Mouse.Buttons & BT_ALTATTACK)
        Player.GUI.Mouse.RightButtonDown = true;
    else
        Player.GUI.Mouse.RightButtonDown = false;
    if (Player.GUI.Mouse.Buttons & BT_ALTATTACK && !(Player.GUI.Mouse.OldButtons & BT_ALTATTACK))
        Player.GUI.Mouse.RightButton = true;
    else
        Player.GUI.Mouse.RightButton = false;
    
    // Draw Cursor
    PrintSprite("Cursor", GUI_CURSOR_ID, (fixed)Player.GUI.Mouse.X + 0.1, (fixed)Player.GUI.Mouse.Y + 0.1, 0.03);
    
    if (Player.GUI.Mouse.ActiveTooltip != NULL)
        DrawTooltip(Player.GUI.Mouse.ActiveTooltip);
}

void DrawTooltip(GUITooltip *Tooltip)
{
    int Type = Tooltip->Type;
    str Title = Tooltip->Text;
    str Text = Tooltip->Text;
    str Color = Tooltip->Color;
    int X = Player.GUI.Mouse.X + 16;
    int Y = Player.GUI.Mouse.Y + 16;
    int ScreenWidth = GUI_WIDTH;
    int ScreenHeight = GUI_HEIGHT;
    int Width = Tooltip->Width;
    int Height = Tooltip->Height;
    bool NoBack = Tooltip->NoBack;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Auto-calculate width and height based on string length and size
    if (Width == 0)
    {
        int Longest;
        int Index;
        
        Longest = StrLen(Title) / 2;
        
        for (int i = 0; i < StrLen(Text); i++)
        {
            Index++;
            
            if (Text[i] == '\n')
            {
                if (Index > Longest)
                    Longest = Index;
                
                Index = 0;
            }
        }
        if (!Longest)
            Longest = StrLen(Text);
        if (!Longest)
            Longest = 1;
        Width = Longest * 10;
    }
    if (Height == 0)
    {
        for (int i = 0; i < StrLen(Text); i++)
            if (Text[i] == '\n')
                Height += 9;
        if (!Height)
            Height = 15;
    }
    
    // Drawing
    if (StrLen(Text) != 0)
    {
        // Basic Tooltip
        if (Type == TT_BASIC)
        {
            // Bounding
            if (X > ScreenWidth - Width)
                X = ScreenWidth - Width;
            if (Y > ScreenHeight - Height)
                Y = ScreenHeight - Height;
            
            // Text
            SetFont("SMALLFONT");
            HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, GUI_CURSOR_ID + 5, Color, X + (NoBack ? 0.1 : 4.1), Y + (NoBack ? 0.1 : 4.1), 0.03);
        }
        
        // Basic Tooltip with Title
        if (Type == TT_TITLE)
        {
            Width += 96;
            Height += 48;
            
            // Bounding
            if (X > ScreenWidth - Width)
                X = ScreenWidth - Width;
            if (Y > ScreenHeight - Height)
                Y = ScreenHeight - Height;
            
            // Title
            SetFont("BIGFONT");
            HudMessage("%S", Tooltip->Title);
            EndHudMessage(HUDMSG_PLAIN, GUI_CURSOR_ID + 5, "White", X + 8.1, Y + 16.0, 0.03);
            
            // Text
            SetFont("SMALLFONT");
            HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, GUI_CURSOR_ID + 6, Color, X + 8.1, Y + 32.1, 0.03);
        }
        
        // Draw Background
        if (!NoBack)
        {
            DrawBorder("Bor", GUI_CURSOR_ID + 7, 8, X, Y, Width, Height);
            SetHudClipRect(X, Y, Width, Height);
            PrintSprite("GUIBack", GUI_CURSOR_ID + 15, X + (Width / 2), Y + (Height / 2), 0.03);
            SetHudClipRect(0, 0, 0, 0);
        }
    }
}

bool InRegion(int X, int Y, int Width, int Height)
{
    if (Player.GUI.Mouse.X > X && Player.GUI.Mouse.X < X + Width &&
        Player.GUI.Mouse.Y > Y && Player.GUI.Mouse.Y < Y + Height)
        return true;
    else
        return false;
}

NamedScript void UpdateTabs()
{
    for (int i = 0; i < PANEL_MAX; i++)
        Player.GUI.TabStrip.Tabs[i].Enabled = true;
    
    if (!InMultiplayer)
        Player.GUI.TabStrip.Tabs[PANEL_TEAM].Enabled = false;
    
    if (!CurrentLevel || !(CurrentLevel->UACBase))
    {
        Player.GUI.TabStrip.Tabs[PANEL_MISSION].Enabled = false;
        Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Enabled = false;
    }
    
    if (!CurrentLevel || !CurrentLevel->UACBase && !GetCVar("drpg_shoptype"))
        Player.GUI.TabStrip.Tabs[PANEL_SHOP].Enabled = false;
    
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    int CurrentID = GUI_PANEL_ID;
    
    for (int i = 0; i < PANEL_MAX; i++)
    {
        int X = 22 + i * 38;
        int Y = 22;
        
        if (InRegion(X - 17, Y - 19, 34, 38) && Player.GUI.Mouse.LeftButton && Player.GUI.TabStrip.Tabs[i].Enabled && Player.GUI.TabStrip.ActiveTab != i)
        {
            Player.GUI.TabStrip.ActiveTab = i;
            ActivatorSound("gui/open", 127);
        }
        
        if (Player.GUI.TabStrip.ActiveTab != i && InRegion(X - 17, Y - 19, 34, 38) && Player.GUI.TabStrip.Tabs[i].Enabled)
        {
            Player.GUI.Mouse.ActiveTooltip = Player.GUI.TabStrip.Tabs[i].Tooltip;
            
            PrintSpritePulse(Player.GUI.TabStrip.Tabs[i].Icon, CurrentID++, X, Y, 0.75, 32.0, 0.25, false);
        }
        else if (Player.GUI.TabStrip.ActiveTab == i)
        {
            PrintSprite(Player.GUI.TabStrip.Tabs[i].HighlightedIcon, CurrentID++, X, Y, 0.03);

            SetFont("BIGFONT");
            HudMessage("%S", Player.GUI.TabStrip.Tabs[i].Title);
            EndHudMessage(HUDMSG_PLAIN, CurrentID++, "White", X - 17 + 0.1, Y + 21 + 0.1, 0.03);
        }
        else if (!Player.GUI.TabStrip.Tabs[i].Enabled)
            PrintSpritePulse(Player.GUI.TabStrip.Tabs[i].Icon, CurrentID++, X, Y, 0.25, 256.0, 0.25, true);
        else
            PrintSprite(Player.GUI.TabStrip.Tabs[i].Icon, CurrentID++, X, Y, 0.03);
    }
    
    // Update and draw the panel attached to the currently active tab
    if (Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel)
    {
        if (Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Update)
            Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Update(Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel);
        
        //DrawPanel(Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel);
    }
}

GUITooltip *GUICreateTooltip()
{
    GUITooltip *Tooltip = calloc(sizeof(GUITooltip), 1);
    
    Tooltip->Type = TT_BASIC;
    Tooltip->Color = "White";
    
    return Tooltip;
}

GUIContextMenu *GUICreateContextMenu()
{
    GUIContextMenu *ContextMenu = calloc(sizeof(GUIContextMenu), 1);
    
    return ContextMenu;
}

void DrawBorder(str Prefix, int StartID, int BorderSize, int X, int Y, int Width, int Height)
{
    // Border corners
    PrintSprite(StrParam("%STL", Prefix), StartID++, X + 0.1, Y + 0.1, 0.03);
    PrintSprite(StrParam("%STR", Prefix), StartID++, X + Width + 0.2, Y + 0.1, 0.03);
    PrintSprite(StrParam("%SBL", Prefix), StartID++, X + 0.1, Y + Height + 0.2, 0.03);
    PrintSprite(StrParam("%SBR", Prefix), StartID++, X + Width + 0.2, Y + Height + 0.2, 0.03);
    
    // Border sides
    SetHudClipRect(X, Y + BorderSize, BorderSize, Height - (BorderSize * 2));
    PrintSprite(StrParam("%SL", Prefix), StartID++, X + 0.1, Y + 0.1, 0.03);
    SetHudClipRect(X + Width - BorderSize, Y + BorderSize, BorderSize, Height - (BorderSize * 2));
    PrintSprite(StrParam("%SR", Prefix), StartID++, X + Width + 0.2, Y + 0.1, 0.03);
    SetHudClipRect(X + BorderSize, Y, Width - (BorderSize * 2), BorderSize);
    PrintSprite(StrParam("%ST", Prefix), StartID++, X + BorderSize + 0.1, Y + 0.1, 0.03);
    SetHudClipRect(X + BorderSize, Y + Height - BorderSize, Width - (BorderSize * 2), BorderSize);
    PrintSprite(StrParam("%SB", Prefix), StartID, X + BorderSize + 0.1, Y + Height + 0.2, 0.03);
    SetHudClipRect(0, 0, 0, 0);
}

// --------------------------------------------------
// Panel Functions
//

NamedScript GUIPanel *GUICreatePanel()
{
    GUIPanel *Panel = calloc(sizeof(GUIPanel), 1);
    
    if (Panel == NULL) return NULL; // OOM
    
    return Panel;
}

NamedScript OptionalArgs(1) GUIControl *GUIControlByName(GUIPanel *Panel, str Name, EControlTypes Kind)
{
    for (int i = 0; i < Panel->NumControls; i++)
    {
        if (!StrCmp(Name, Panel->Controls[i]->Name) && (!Kind || Kind == Panel->Controls[i]->Kind))
            return Panel->Controls[i];
    }
    
    return NULL;
}

NamedScript bool GUIAddExistingControl(GUIPanel *Panel, GUIControl *Control)
{
    GUIControl **NewCtlArray = realloc(Panel->Controls, sizeof(GUIControl *) * (Panel->NumControls + 1));
    if (!NewCtlArray)
        return false;
    
    Panel->Controls = NewCtlArray;
    Panel->Controls[Panel->NumControls++] = Control;
    
    return true;
}

NamedScript GUILabel *GUIAddLabel(GUIPanel *Panel, str Name)
{
    GUILabel *Label = calloc(sizeof(GUILabel), 1);
    
    if (!GUIAddExistingControl(Panel, (GUIControl *)Label))
    {
        free(Label);
        return NULL;
    }
    
    Label->Control.Name = Name;
    Label->Control.Kind = CTL_LABEL;
    Label->Control.Owner = Panel;
    
    // Defaults
    Label->Control.X = 0;
    Label->Control.Y = 0;
    Label->Control.Width = 32;
    Label->Control.Height = 32;
    Label->Control.Visible = true;
    
    Label->Control.Update = (ControlUpdateFunc)UpdateLabel;
    
    Label->Alignment = LA_LEFT;

    return Label;
}

NamedScript GUIIcon *GUIAddIcon(GUIPanel *Panel, str Name)
{
    GUIIcon *Icon = calloc(sizeof(GUIIcon), 1);
    
    if (!GUIAddExistingControl(Panel, (GUIControl *)Icon))
    {
        free(Icon);
        return NULL;
    }
    
    Icon->Control.Name = Name;
    Icon->Control.Kind = CTL_ICON;
    Icon->Control.Owner = Panel;
    
    // Defaults
    Icon->Control.X = 0;
    Icon->Control.Y = 0;
    Icon->Control.Width = 32;
    Icon->Control.Height = 32;
    Icon->Control.Visible = true;
    
    Icon->Control.Update = (ControlUpdateFunc)UpdateIcon;
    
    Icon->CalculateSize = true;
    
    return Icon;
}

NamedScript GUIButton *GUIAddButton(GUIPanel *Panel, str Name)
{
    GUIButton *Button = calloc(sizeof(GUIButton), 1);
    
    if (!GUIAddExistingControl(Panel, (GUIControl *)Button))
    {
        free(Button);
        return NULL;
    }
    
    Button->Control.Name = Name;
    Button->Control.Kind = CTL_BUTTON;
    Button->Control.Owner = Panel;
    
    // Defaults
    Button->Control.X = 0;
    Button->Control.Y = 0;
    Button->Control.Width = 32;
    Button->Control.Height = 32;
    Button->Control.Visible = true;
    
    Button->Control.Update = (ControlUpdateFunc)UpdateButton;
    
    return Button;
}

NamedScript GUIBar *GUIAddBar(GUIPanel *Panel, str Name)
{
    GUIBar *Bar = calloc(sizeof(GUIBar), 1);
    
    if (!GUIAddExistingControl(Panel, (GUIControl *)Bar))
    {
        free(Bar);
        return NULL;
    }
    
    Bar->Control.Name = Name;
    Bar->Control.Kind = CTL_BAR;
    Bar->Control.Owner = Panel;
    
    // Defaults
    Bar->Control.X = 0;
    Bar->Control.Y = 0;
    Bar->Control.Width = 32;
    Bar->Control.Height = 32;
    Bar->Control.Visible = true;
    
    Bar->Control.Update = (ControlUpdateFunc)UpdateBar;
    
    return Bar;
}

NamedScript GUIList *GUIAddList(GUIPanel *Panel, str Name)
{
    GUIList *List = calloc(sizeof(GUIList), 1);
    
    if (!GUIAddExistingControl(Panel, (GUIControl *)List))
    {
        free(List);
        return NULL;
    }
    
    List->Control.Name = Name;
    List->Control.Kind = CTL_LIST;
    List->Control.Owner = Panel;
    
    // Defaults
    List->Control.X = 0;
    List->Control.Y = 0;
    List->Control.Width = 32;
    List->Control.Height = 32;
    List->Control.Visible = true;
    
    List->Control.Update = (ControlUpdateFunc)UpdateList;
    
    return List;
}

NamedScript GUIGrid *GUIAddGrid(GUIPanel *Panel, str Name)
{
    GUIGrid *Grid = calloc(sizeof(GUIGrid), 1);
    
    if (!GUIAddExistingControl(Panel, (GUIControl *)Grid))
    {
        free(Grid);
        return NULL;
    }
    
    Grid->Control.Name = Name;
    Grid->Control.Kind = CTL_GRID;
    Grid->Control.Owner = Panel;
    
    // Defaults
    Grid->Control.X = 0;
    Grid->Control.Y = 0;
    Grid->Control.Width = 32;
    Grid->Control.Height = 32;
    Grid->Control.Visible = true;
    
    Grid->Control.Update = (ControlUpdateFunc)UpdateGrid;
    
    return Grid;
}

NamedScript void GUIUpdatePanelControls(GUIPanel *Panel)
{
    for (int i = 0; i < Panel->NumControls; i++)
    {
        if (Panel->Controls[i]->Update && Panel->Controls[i]->Visible)
            Panel->Controls[i]->Update(Panel->Controls[i]);
    }
}

// --------------------------------------------------
// Control Functions
//

// [KS] I didn't touch these, Kyle, sorry. I want to separate drawing from update handling, but not today. Maybe tomorrow.

NamedScript void UpdateLabel(GUILabel *Label)
{
    str Text = Label->Text;
    int Alignment = Label->Alignment;
    fixed X = WINDOW_X + Label->Control.X;
    fixed Y = WINDOW_Y + Label->Control.Y + 48;
    int Width = Label->Control.Width;
    int Height = Label->Control.Height;
    str Color = Label->Color;
    bool Big = Label->Big;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Auto-calculate width and height based on string length and size
    if (Width == 0 && Height == 0)
    {
        Width = StrLen(Text) * (Big ? 13 : 8);
        Height = 14;
    }
    
    // Alignment
    if (Alignment == LA_LEFT)
        X += 0.1;
    if (Alignment == LA_RIGHT)
        X += 0.2;
    if (Alignment == LA_CENTERTOP)
        Y += 0.1;
    if (Alignment == LA_LEFTTOP)
    {
        X += 0.1;
        Y += 0.1;
    }
    if (Alignment == LA_RIGHTTOP)
    {
        X += 0.2;
        Y += 0.1;
    }
    
    // Drawing
    SetFont((Big ? "BIGFONT" : "SMALLFONT"));
    HudMessage("%S", Text);
    EndHudMessage(HUDMSG_PLAIN, 0, Color, X, Y, 0.05);
    
    // Tooltip
    if (InRegion(X, Y, Width, Height) && Label->Control.Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Label->Control.Tooltip;
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Label->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Label->Control.ContextMenu;
}

NamedScript void UpdateIcon(GUIIcon *Icon)
{
    str Texture = Icon->Texture;
    int X = WINDOW_X + Icon->Control.X;
    int Y = WINDOW_Y + Icon->Control.Y + 48;
    int XOff = Icon->XOff;
    int YOff = Icon->YOff;
    int Width = Icon->Control.Width;
    int Height = Icon->Control.Height;
    bool CalculateSize = Icon->CalculateSize;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Automatically detect X/Y Offset if none are specified
    if (XOff == 0 && YOff == 0 && CalculateSize)
    {
        XOff = Width / 2;
        YOff = Height;
    }
    
    // Drawing
    PrintSprite(Texture, 0, X + XOff + 0.1, Y + YOff + 0.1, 0.05);
    
    // Debugging - Draw a border to show the Icon's width/height
    if (GetCVar("drpg_debug_gui"))
        DrawBorder("Bor", 0, 8, X, Y, Width, Height);
    
    // Tooltip
    if (InRegion(X + 4, Y + 8, Width, Height) && Icon->Control.Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Icon->Control.Tooltip;
    
    // Context Menu
    if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.RightButton && Icon->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Icon->Control.ContextMenu;
    
    // OnClick Event
    if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.LeftButton && Icon->Control.Click && Player.GUI.Mouse.ActiveContextMenu == NULL)
        Icon->Control.Click((GUIControl *)Icon);
}

NamedScript void UpdateButton(GUIButton *Button)
{
    str Text = Button->Text;
    int X = WINDOW_X + Button->Control.X;
    int Y = WINDOW_Y + Button->Control.Y + 48;
    int Width = Button->Control.Width;
    int Height = Button->Control.Height;
    str Color = Button->Color;
    str HoverColor = Button->HoverColor;
    bool Big = Button->Big;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Default Color
    if (Color == "Brick")
        Color = "White";
    
    // Default Hover Color
    if (HoverColor == 0)
        HoverColor = MenuCursorColor;
    
    // Auto-calculate width and height based on string length and size
    if (Width == 0 && Height == 0)
    {
        Width = StrLen(Text) * (Big ? 13 : 8);
        Height = 14;
    }
    
    // Drawing
    SetFont((Big ? "BIGFONT" : "SMALLFONT"));
    if (InRegion(X, Y, Width, Height))
    {
        HudMessage("%S", Text);
        EndHudMessage(HUDMSG_PLAIN, 0, HoverColor, X + 0.1, Y, 0.05);
    }
    else
    {
        HudMessage("%S", Text);
        EndHudMessage(HUDMSG_PLAIN, 0, Color, X + 0.1, Y, 0.05);
    }
    
    // Tooltip
    if (InRegion(X, Y, Width, Height) && Button->Control.Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Button->Control.Tooltip;
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Button->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Button->Control.ContextMenu;
    
    // OnClick event
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.LeftButton && Button->Control.Click && Player.GUI.Mouse.ActiveContextMenu == NULL)
        Button->Control.Click((GUIControl *)Button);
}

NamedScript void UpdateBar(GUIBar *Bar)
{
    int X = WINDOW_X + Bar->Control.X;
    int Y = WINDOW_Y + Bar->Control.Y + 48;
    int Width = Bar->Control.Width;
    int Height = Bar->Control.Height;
    int Value = Bar->Value;
    int ValueMax = Bar->ValueMax;
    str Texture = Bar->Texture;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Default Max Value
    if (ValueMax == 0)
        ValueMax = 100;
    
    // Prevent Value under/overflow
    if (Value < 0)
        Value = 0;
    if (Value > ValueMax)
        Value = ValueMax;
    
    // Auto-calculate width and height based on ValueMax
    if (Width == 0 && Height == 0)
    {
        Width = ValueMax;
        Height = 6;
    }
    
    // Drawing
    for (int i = 0; i < (int)(((fixed)Value / (fixed)(ValueMax + 1)) * 100.0); i++)
        PrintSprite(Texture, 0, ++X, Y, 0.05);
    
    // Tooltip
    if (InRegion(X, Y, Width, Height) && Bar->Control.Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Bar->Control.Tooltip;
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Bar->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Bar->Control.ContextMenu;
}

NamedScript void UpdateList(GUIList *List)
{
    // Reset the selected entry
    List->Selected = -1;
    
    int X = WINDOW_X + List->Control.X;
    int Y = WINDOW_Y + List->Control.Y + 48;
    int Shown = List->Shown;
    int Offset = List->Offset;
    str *Entries;
    str *Colors;
    str *HoverColors;
    int MaxEntries;
    int Longest;
    
    Entries = List->Entries;
    Colors = List->Colors;
    HoverColors = List->HoverColors;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
        
    // Calculate max amount of entries
    for (int i = 0; StrLen(Entries[i]) != 0; i++)
        MaxEntries++;
    
    // Can't show less than 5 items
    if (Shown < 5)
        Shown = 5;
    
    // Default Color
    for (int i = 0; i < MaxEntries; i++)
        if (Colors[i] == 0)
            Colors[i] = "White";
    
    // Default Hover Color
    for (int i = 0; i < MaxEntries; i++)
        if (HoverColors[i] == 0)
            HoverColors[i] = MenuCursorColor;
    
    // Drawing/Selection
    SetFont("SMALLFONT");
    for (int i = Offset; i < MaxEntries && i < Offset + Shown; i++)
    {
        int Width = StrLen(Entries[i]) * 8;
        
        // Checking for the longest width in the entries
        if (Width > Longest) Longest = Width;
        
        if (InRegion(X, Y + 3 + ((i - Offset) * 10), Width, 9) && Player.GUI.Mouse.ActiveContextMenu == NULL)
        {
            HudMessage("%S", Entries[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, HoverColors[i], X + 0.1, Y + ((i - Offset) * 10.0), 0.05);
            List->Selected = i;
            
            // Tooltip
            if (List->Control.Tooltip != NULL)
                Player.GUI.Mouse.ActiveTooltip = List->Control.Tooltip;
            
            // Context Menu
            if (Player.GUI.Mouse.RightButton && List->Control.ContextMenu != NULL)
                Player.GUI.Mouse.ActiveContextMenu = List->Control.ContextMenu;
            
            // OnClick event
            if (Player.GUI.Mouse.LeftButton && List->Control.Click)
                List->Control.Click((GUIControl *)List);
        }
        else
        {
            HudMessage("%S", Entries[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, Colors[i], X + 0.1, Y + ((i - Offset) * 10.0), 0.05);
        }
    }
    
    // Scroll Arrows
    if (List->Offset > 0)
        PrintSprite("ListUp", 0, X + Longest + 16.0, Y + 8.0, 0.05);
    if (List->Offset < MaxEntries - Shown)
        PrintSprite("ListDn", 0, X + Longest + 16.0, Y + (Shown * 10.0) - 20.0, 0.05);
    if (InRegion(X + Longest + 16.0, Y + 4.0, 24, 24) && Player.GUI.Mouse.LeftButton && List->Offset > 0)
        List->Offset--;
    if (InRegion(X + Longest + 16.0, Y + (Shown * 10.0) - 24.0, 24, 24) && Player.GUI.Mouse.LeftButton && List->Offset < MaxEntries - Shown)
        List->Offset++;
}

NamedScript void UpdateGrid(GUIGrid *Grid)
{
    // TODO
}

/* Kyle halp
NamedScript void HandleContextMenu(GUIContextMenu *Menu)
{
    int X = Menu->X;
    int Y = Menu->Y;
    int Width;
    int Height;
    int Longest;
    
    // Calculate the Width and Height
    for (int i = 0; StrLen(Menu->Options[i].Name) != 0; i++)
        if (StrLen(Menu->Options[i].Name) > Longest)
            Longest = StrLen(Menu->Options[i].Name);
    Width = Longest * 9;
    for (int i = 0; StrLen(Menu->Options[i].Name) != 0; i++)
        Height += 12;
    
    // Draw Border
    //DrawBorder(X + 16, Y + 32, Width, Height, "BarHorz", "BarVert");
    
    // Draw/Handle Options
    for (int i = 0; StrLen(Menu->Options[i].Name) != 0; i++)
    {
        if (InRegion(X + 20, Y + 40 + (i * 10), Width, 11))
        {
            HudMessage("%S", Menu->Options[i].Name);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, X + 18.1, Y + 40.0 + (i * 10), 0.05);
            
            // OnClick Event
            if (Player.GUI.Mouse.LeftButton && Menu->Options[i].OnClick != NULL)
                Menu->Options[i].OnClick();
        }
        else
        {
            HudMessage("%S", Menu->Options[i].Name);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 18.1, Y + 40.0 + (i * 10), 0.05);
        }
    }
    
    // Draw Background
    SetHudClipRect(X + 16, Y + 32, Width, Height);
    PrintSprite("GUIBack", 0, X, Y, 0.05);
    SetHudClipRect(0, 0, 0, 0);
    
    // Close Menu
    if (Player.GUI.Mouse.LeftButton || Player.GUI.Mouse.RightButton)
        Player.GUI.Mouse.ActiveContextMenu = NULL;
}
*/

// --------------------------------------------------
// GUI Panels
//

NamedScript void CreateOverviewPanel()
{
    GUIPanel *OverviewPanel = GUICreatePanel();
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Panel = OverviewPanel;
    
    OverviewPanel->Update = (PanelUpdateFunc)UpdateOverviewPanel;
    
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
    NameLabel->Color = "White";
    NameLabel->Big = true;
    
    LevelLabel->Control.X = 64;
    LevelLabel->Control.Y = 28;
    LevelLabel->Color = "White";
    LevelLabel->Big = true;
    
    XPLabel->Control.X = 64;
    XPLabel->Control.Y = 40;
    XPLabel->Color = "White";
    XPLabel->Big = true;
    
    TitleLabel->Control.X = 64;
    TitleLabel->Control.Y = 52;
    TitleLabel->Color = "Yellow";
    TitleLabel->Big = true;
    
    RankLabel->Control.X = 64;
    RankLabel->Control.Y = 64;
    RankLabel->Color = "Yellow";
    RankLabel->Big = true;
    
    PPLabel->Control.X = 64;
    PPLabel->Control.Y = 76;
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
    
    TurretPartsIcon->Texture = "TPRTA0";
    TurretPartsIcon->Control.X = 24;
    TurretPartsIcon->Control.Y = 128;
    
    AugChargeIcon->Texture = "AUGBATT";
    AugChargeIcon->Control.X = 24;
    AugChargeIcon->Control.Y = 148;
    
    AugSlotsIcon->Texture = "AUGUB0";
    AugSlotsIcon->Control.X = 24;
    AugSlotsIcon->Control.Y = 178;
    
    AugCanistersIcon->Texture = "AUGCA0";
    AugCanistersIcon->Control.X = 16;
    AugCanistersIcon->Control.Y = 204;
    
    AugUpgradesIcon->Texture = "AUGUA0";
    AugUpgradesIcon->Control.X = 32;
    AugUpgradesIcon->Control.Y = 198;
    
    StimsIcon->Texture = "STIMB0";
    StimsIcon->Control.X = 24;
    StimsIcon->Control.Y = 248;
    
    ChipsGoldIcon->Texture = "CHIPGOLD";
    ChipsGoldIcon->Control.X = 8;
    ChipsGoldIcon->Control.Y = 268;
    
    ChipsPlatIcon->Texture = "CHIPPLAT";
    ChipsPlatIcon->Control.X = 8;
    ChipsPlatIcon->Control.Y = 304;
    
    InventoryIcon->Texture = "GPAKA0";
    InventoryIcon->Control.X = 24;
    InventoryIcon->Control.Y = 396;
    
    ModuleLabel->Control.X = 84;
    ModuleLabel->Control.Y = 116;
    ModuleLabel->Color = "Green";
    ModuleLabel->Big = true;
    
    TurretPartsLabel->Control.X = 84;
    TurretPartsLabel->Control.Y = 148;
    TurretPartsLabel->Color = "White";
    TurretPartsLabel->Big = true;
    
    AugChargeLabel->Control.X = 84;
    AugChargeLabel->Control.Y = 180;
    AugChargeLabel->Color = "Yellow";
    AugChargeLabel->Big = true;
    
    AugSlotsLabel->Control.X = 84;
    AugSlotsLabel->Control.Y = 200;
    AugSlotsLabel->Color = "Green";
    AugSlotsLabel->Big = true;
    
    AugUpgradesLabel->Control.X = 84;
    AugUpgradesLabel->Control.Y = 224;
    AugUpgradesLabel->Color = "Green";
    AugUpgradesLabel->Big = true;
    
    StimsLabel->Control.X = 84;
    StimsLabel->Control.Y = 264;
    StimsLabel->Color = "White";
    StimsLabel->Big = true;
    
    ChipsGoldLabel->Control.X = 84;
    ChipsGoldLabel->Control.Y = 314;
    ChipsGoldLabel->Color = "Gold";
    ChipsGoldLabel->Big = true;
    
    ChipsPlatLabel->Control.X = 84;
    ChipsPlatLabel->Control.Y = 350;
    ChipsPlatLabel->Color = "White";
    ChipsPlatLabel->Big = true;
    
    InventoryLabel->Control.X = 84;
    InventoryLabel->Control.Y = 412;
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
    
    MapNameLabel->Control.X = 328;
    MapNameLabel->Control.Y = 110;
    MapNameLabel->Color = "White";
    MapNameLabel->Big = true;
    
    MapInfoLabel->Control.X = 328;
    MapInfoLabel->Control.Y = 122;
    MapInfoLabel->Color = "Green";
    MapInfoLabel->Big = true;
    
    MapTimeLabel->Control.X = 328;
    MapTimeLabel->Control.Y = 134;
    MapTimeLabel->Color = "Orange";
    MapTimeLabel->Big = true;
    
    MapKillsLabel->Control.X = 328;
    MapKillsLabel->Control.Y = 146;
    MapKillsLabel->Big = true;
    
    MapItemsLabel->Control.X = 328;
    MapItemsLabel->Control.Y = 158;
    MapItemsLabel->Big = true;
    
    MapSecretsLabel->Control.X = 328;
    MapSecretsLabel->Control.Y = 170;
    MapSecretsLabel->Big = true;
    
    // --------------------------------------------------
    // Shield
    //
    
    // --------------------------------------------------
    // Current Stim / Toxicity
    //
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
    
    NameLabel->Text = StrParam("%tS", PlayerNumber() + 1);
    LevelLabel->Text = StrParam("Level: %d", Player.Level);
    XPLabel->Text = StrParam("XP: %ld / %ld", Player.XP, Player.XPNext);
    TitleLabel->Text = StrParam("Title: %S (%d/%d)", Ranks[Player.RankLevel], Player.RankLevel, MAX_RANK);
    RankLabel->Text = StrParam("Rank: %ld / %ld", Player.Rank, Player.RankNext);
    if (Player.PayReady && !Player.PayingOut)
        PPLabel->Text = StrParam("PP: %d (%S) [\C[%S]Ready\C-]", Player.PP, FormatTime(Player.PayTimer), PayReadyColor);
    else
        PPLabel->Text = StrParam("PP: %d (%S)", Player.PP, FormatTime(Player.PayTimer));
    
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
    
    GUIUpdatePanelControls(OverviewPanel);
}

// Temporary, for testing coordinates
NamedScript Console void GUITest(int X, int Y, int X2, int Y2)
{
    GUITestX = X + (X2 / 100);
    GUITestY = Y + (Y2 / 100);
}
