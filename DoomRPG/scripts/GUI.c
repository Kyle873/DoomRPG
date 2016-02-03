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
    
    Player.GUI.Created = true;
}

void CreateTabs()
{
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Icon = "TMain";
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Title = "Overview";
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_MAIN].Tooltip->Text = "Overview";
    
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Icon = "TStats";
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Title = "\CgStats";
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_STATS].Tooltip->Text = "\CgStats";
    
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Icon = "TAugs";
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Title = "\CkAugmentations";
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_AUGS].Tooltip->Text = "\CkAugmentations";
    
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Icon = "TSkills";
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Title = "\CnSkills";
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_SKILLS].Tooltip->Text = "\CnSkills";
    
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Icon = "TShield";
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Title = "\CvShield";
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_SHIELD].Tooltip->Text = "\CvShield";
    
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Icon = "TStims";
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Title = "\CcStims";
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_STIMS].Tooltip->Text = "\CcStims";
    
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Icon = "TTurret";
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Title = "\CdTurret";
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TURRET].Tooltip->Text = "\CdTurret";
    
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Icon = "TShop";
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Title = "\CfShop";
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_SHOP].Tooltip->Text = "\CfShop";
    
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Icon = "TPayout";
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Title = "\CfPayout";
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_PAYOUT].Tooltip->Text = "\CfPayout";
    
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Icon = "TMission";
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Title = "\CaMissions";
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_MISSION].Tooltip->Text = "\CaMissions";
    
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Icon = "TTrans";
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Title = "\ChTransport";
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TRANSPORT].Tooltip->Text = "\ChTransport";
    
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Icon = "TTeam";
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Title = "\CqTeam";
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TEAM].Tooltip->Text = "\CqTeam";
    
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Icon = "TTips";
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Title = "\CuTips";
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Enabled = true;
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Tooltip = GUICreateTooltip();
    Player.GUI.TabStrip.Tabs[PANEL_TIPS].Tooltip->Text = "\CuTips";
    
    Player.GUI.TabStrip.Tabs[PANEL_MAX].Icon = "";
    Player.GUI.TabStrip.Tabs[PANEL_MAX].Title = "";
    Player.GUI.TabStrip.Tabs[PANEL_MAX].Enabled = false;
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
        UpdateGUICursor();
        UpdateTabs();
        DrawBackgroundWindow();
        
        Delay(1);
    }
    
    ActivatorSound("gui/close", 127);
    SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
}

NamedScript void DrawBackgroundWindow()
{
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    DrawBorder("Bor", 8, WINDOW_X, WINDOW_Y, GUI_WIDTH, GUI_HEIGHT);
    
    SetHudClipRect(0, 0, 0, 0);
    
    if (Player.GUI.GlowLine.Delay < 1)
        DrawGlowLine();
    else
        Player.GUI.GlowLine.Delay--;
    
    PrintSpriteAddAlpha("GStatic1", 0, WINDOW_X + 0.1, WINDOW_Y + 0.1, 0.03, 0.5);
    PrintSpriteAlpha("GUIBack", 0, WINDOW_X + 0.1, WINDOW_Y + 0.1, 0.03, 0.75);
}

NamedScript void DrawGlowLine()
{
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    SetHudClipRect(WINDOW_X, WINDOW_Y, GUI_WIDTH, GUI_HEIGHT);
    PrintSpriteAdd("ScanLine", 0, 0.1, (fixed)Player.GUI.GlowLine.Position + 0.1, 0.03);
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
    PrintSprite("Cursor", 0, (fixed)Player.GUI.Mouse.X + 0.1, (fixed)Player.GUI.Mouse.Y + 0.1, 0.05);
    
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
    str Icon = Tooltip->Icon;
    int IconXOff = Tooltip->IconXOff;
    int IconYOff = Tooltip->IconYOff;
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
        Width = Longest * 7;
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
            
            // Border
            //if (!NoBack)
            //    DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
            
            // Text
            SetFont("SMALLFONT");
            HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, X + (NoBack ? 0.1 : 4.1), Y + (NoBack ? 0.1 : 4.1), 0.05);
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
            
            // Border
            //if (!NoBack)
            //    DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
            
            // Title
            SetFont("BIGFONT");
            HudMessage("%S", Tooltip->Title);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 8.1, Y + 16.0, 0.05);
            
            // Text
            SetFont("SMALLFONT");
            HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, X + 8.1, Y + 32.1, 0.05);
        }
        
        // Draw Background
        if (!NoBack)
        {
            SetHudClipRect(X, Y, Width, Height);
            PrintSprite("GUIBack", 0, X + (Width / 2), Y + (Height / 2), 0.05);
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

void UpdateTabs()
{
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    for (int i = 0; StrLen(Player.GUI.TabStrip.Tabs[i].Icon) != 0; i++)
    {
        int X = 22 + i * 38;
        int Y = 22;
        
        if (InRegion(X - 17, Y - 19, 34, 38) && Player.GUI.Mouse.LeftButton && Player.GUI.TabStrip.Tabs[i].Enabled && Player.GUI.TabStrip.ActiveTab != i)
        {
            Player.GUI.TabStrip.ActiveTab = i;
            ActivatorSound("gui/open", 127);
        }
        
        if (InRegion(X - 17, Y - 19, 34, 38) && Player.GUI.TabStrip.Tabs[i].Enabled)
        {
            Player.GUI.Mouse.ActiveTooltip = Player.GUI.TabStrip.Tabs[i].Tooltip;
            
            PrintSpritePulse(Player.GUI.TabStrip.Tabs[i].Icon, 0, X, Y, 0.75, 32.0, 0.25, false);
        }
        else if (!Player.GUI.TabStrip.Tabs[i].Enabled)
            PrintSpritePulse(Player.GUI.TabStrip.Tabs[i].Icon, 0, X, Y, 0.25, 256.0, 0.25, true);
        else
            PrintSprite(Player.GUI.TabStrip.Tabs[i].Icon, 0, X, Y, 0.05);
    }
}

void HandleLabel(GUILabel *Label)
{
    // Don't handle the control if it's invisible
    if (!Label->Visible) return;
    
    str Text = Label->Text;
    int Alignment = Label->Alignment;
    fixed X = WINDOW_X + Label->X;
    fixed Y = WINDOW_Y + Label->Y + 32;
    int Width = Label->Width;
    int Height = Label->Height;
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
    if (InRegion(X, Y, Width, Height) && Label->Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Label->Tooltip;
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Label->ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Label->ContextMenu;
}

void HandleIcon(GUIIcon *Icon)
{
    // Don't handle the control if it's invisible
    if (!Icon->Visible) return;
    
    str Texture = Icon->Texture;
    int X = WINDOW_X + Icon->X;
    int Y = WINDOW_Y + Icon->Y + 32;
    int XOff = Icon->XOff;
    int YOff = Icon->YOff;
    int Width = Icon->Width;
    int Height = Icon->Height;
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
    //if (GetCVar("drpg_debug_gui"))
    //    DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
    
    // Tooltip
    if (InRegion(X + 4, Y + 8, Width, Height) && Icon->Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Icon->Tooltip;
    
    // Context Menu
    if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.RightButton && Icon->ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Icon->ContextMenu;
    
    // OnClick Event
    if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.LeftButton && Icon->OnClick && Player.GUI.Mouse.ActiveContextMenu == NULL)
        Icon->OnClick(Icon);
}

void HandleButton(GUIButton *Button)
{
    // Don't handle the control if it's invisible
    if (!Button->Visible) return;

    str Text = Button->Text;
    int X = WINDOW_X + Button->X;
    int Y = WINDOW_Y + Button->Y + 32;
    int Width = Button->Width;
    int Height = Button->Height;
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
    if (InRegion(X, Y, Width, Height) && Button->Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Button->Tooltip;
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Button->ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Button->ContextMenu;
    
    // OnClick event
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.LeftButton && Button->OnClick && Player.GUI.Mouse.ActiveContextMenu == NULL)
        Button->OnClick(Button);
}

void HandleBar(GUIBar *Bar)
{
    // Don't handle the control if it's invisible
    if (!Bar->Visible) return;

    int X = WINDOW_X + Bar->X;
    int Y = WINDOW_Y + Bar->Y + 32;
    int Width = Bar->Width;
    int Height = Bar->Height;
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
    if (InRegion(X, Y, Width, Height) && Bar->Tooltip != NULL)
        Player.GUI.Mouse.ActiveTooltip = Bar->Tooltip;
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Bar->ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Bar->ContextMenu;
}

void HandleList(GUIList *List)
{
    // Don't handle the control if it's invisible
    if (!List->Visible) return;
    
    // Reset the selected entry
    List->Selected = -1;
    
    int X = WINDOW_X + List->X;
    int Y = WINDOW_Y + List->Y + 32;
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
            if (List->Tooltip != NULL)
                Player.GUI.Mouse.ActiveTooltip = List->Tooltip;
            
            // Context Menu
            if (Player.GUI.Mouse.RightButton && List->ContextMenu != NULL)
                Player.GUI.Mouse.ActiveContextMenu = List->ContextMenu;
            
            // OnClick event
            if (Player.GUI.Mouse.LeftButton && List->OnClick)
                List->OnClick(List);
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

void HandleGrid(GUIGrid *Grid)
{
    // TODO
}

void HandleContextMenu(GUIContextMenu *Menu)
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

GUILabel *GUICreateLabel()
{
    GUILabel *Label = calloc(sizeof(GUILabel), 1);
    
    Label->Alignment = LA_LEFT;
    Label->Visible = true;
    
    return Label;
}

GUIIcon *GUICreateIcon()
{
    GUIIcon *Icon = calloc(sizeof(GUIIcon), 1);
    
    Icon->CalculateSize = true;
    Icon->Visible = true;
    
    return Icon;
}

GUIButton *GUICreateButton()
{
    GUIButton *Button = calloc(sizeof(GUIButton), 1);
    
    Button->Visible = true;
    
    return Button;
}

GUIBar *GUICreateBar()
{
    GUIBar *Bar = calloc(sizeof(GUIBar), 1);
    
    Bar->Visible = true;
    
    return Bar;
}

GUIList *GUICreateList()
{
    GUIList *List = calloc(sizeof(GUIList), 1);
    
    List->Visible = true;
    
    return List;
}

// TODO
GUIGrid *GUICreateGrid()
{
    GUIGrid *Grid = calloc(sizeof(GUIGrid), 1);
    
    return Grid;
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

void DrawBorder(str Prefix, int BorderSize, int X, int Y, int Width, int Height)
{
    // Border corners
    
    PrintSprite(StrParam("%STL", Prefix), 0, X + 0.1, Y + 0.1, 0.03);
    PrintSprite(StrParam("%STR", Prefix), 0, X + Width + 0.2, Y + 0.1, 0.03);
    PrintSprite(StrParam("%SBL", Prefix), 0, X + 0.1, Height + 0.2, 0.03);
    PrintSprite(StrParam("%SBR", Prefix), 0, X + Width + 0.2, Height + 0.2, 0.03);
    
    // Border sides
    SetHudClipRect(X, Y, BorderSize, Height - Y - BorderSize);
    PrintSprite(StrParam("%SL", Prefix), 0, X + 0.1, Y + 0.1, 0.03);
    SetHudClipRect(X + Width - BorderSize, Y, BorderSize, Height - Y - BorderSize);
    PrintSprite(StrParam("%SR", Prefix), 0, X + Width + 0.2, Y + 0.1, 0.03);
    SetHudClipRect(X + BorderSize, Y, Width - BorderSize, BorderSize);
    PrintSprite(StrParam("%ST", Prefix), 0, X + BorderSize + 0.1, Y + 0.1, 0.03);
    SetHudClipRect(X + BorderSize, Height - BorderSize, Width - BorderSize, BorderSize);
    PrintSprite(StrParam("%SB", Prefix), 0, X + BorderSize + 0.1, Height + 0.2, 0.03);
}

// --------------------------------------------------
// GUI Creation
//
/*
NamedScript void UpdateMainWindow()
{
    GUIWindow *Window = GUICreateWindow();
    Player.GUI.Window[WINDOW_MAIN] = Window;
    
    // --------------------------------------------------
    // Player Sprite
    //
    
    str PlayerSprite = "PLAYA1";
    
    GUIIcon *PlayerSpriteIcon = GUICreateIcon(Window);
    
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
    PlayerSpriteIcon->X = 32;
    PlayerSpriteIcon->Y = 64;
    
    // --------------------------------------------------
    // Player Info
    //
    
    GUILabel *NameLabel = GUICreateLabel(Window);
    GUILabel *LevelLabel = GUICreateLabel(Window);
    GUILabel *XPLabel = GUICreateLabel(Window);
    GUILabel *TitleLabel = GUICreateLabel(Window);
    GUILabel *RankLabel = GUICreateLabel(Window);
    GUILabel *PPLabel = GUICreateLabel(Window);
    
    NameLabel->X = 64;
    NameLabel->Y = 16;
    NameLabel->Color = "White";
    NameLabel->Big = true;
    
    LevelLabel->X = 64;
    LevelLabel->Y = 28;
    LevelLabel->Color = "White";
    LevelLabel->Big = true;
    
    XPLabel->X = 64;
    XPLabel->Y = 40;
    XPLabel->Color = "White";
    XPLabel->Big = true;
    
    TitleLabel->X = 64;
    TitleLabel->Y = 52;
    TitleLabel->Color = "Yellow";
    TitleLabel->Big = true;
    
    RankLabel->X = 64;
    RankLabel->Y = 64;
    RankLabel->Color = "Yellow";
    RankLabel->Big = true;
    
    PPLabel->X = 64;
    PPLabel->Y = 76;
    PPLabel->Color = "Gold";
    PPLabel->Big = true;
    
    // --------------------------------------------------
    // Totals
    //
    
    // TODO: Put DRLA stuff below the inventory/ammo totals
    
    GUIIcon *ModuleIcon = GUICreateIcon(Window);
    GUIIcon *TurretPartsIcon = GUICreateIcon(Window);
    GUIIcon *AugChargeIcon = GUICreateIcon(Window);
    GUIIcon *AugSlotsIcon = GUICreateIcon(Window);
    GUIIcon *AugCanistersIcon = GUICreateIcon(Window);
    GUIIcon *AugUpgradesIcon = GUICreateIcon(Window);
    GUIIcon *StimsIcon = GUICreateIcon(Window);
    GUIIcon *ChipsGoldIcon = GUICreateIcon(Window);
    GUIIcon *ChipsPlatIcon = GUICreateIcon(Window);
    GUIIcon *InventoryIcon = GUICreateIcon(Window);
    
    GUILabel *ModuleLabel = GUICreateLabel(Window);
    GUILabel *TurretPartsLabel = GUICreateLabel(Window);
    GUILabel *AugChargeLabel = GUICreateLabel(Window);
    GUILabel *AugSlotsLabel = GUICreateLabel(Window);
    GUILabel *AugUpgradesLabel = GUICreateLabel(Window);
    GUILabel *StimsLabel = GUICreateLabel(Window);
    GUILabel *ChipsGoldLabel = GUICreateLabel(Window);
    GUILabel *ChipsPlatLabel = GUICreateLabel(Window);
    GUILabel *InventoryLabel = GUICreateLabel(Window);
    
    ModuleIcon->Texture = "UMODA0";
    ModuleIcon->X = 40;
    ModuleIcon->Y = 128;
    
    TurretPartsIcon->Texture = "TPRTA0";
    TurretPartsIcon->X = 40;
    TurretPartsIcon->Y = 160;
    
    AugChargeIcon->Texture = "AUGBATT";
    AugChargeIcon->X = 40;
    AugChargeIcon->Y = 180;
    
    AugSlotsIcon->Texture = "AUGUB0";
    AugSlotsIcon->X = 40;
    AugSlotsIcon->Y = 210;
    
    AugCanistersIcon->Texture = "AUGCA0";
    AugCanistersIcon->X = 32;
    AugCanistersIcon->Y = 236;
    
    AugUpgradesIcon->Texture = "AUGUA0";
    AugUpgradesIcon->X = 48;
    AugUpgradesIcon->Y = 230;
    
    StimsIcon->Texture = "STIMB0";
    StimsIcon->X = 40;
    StimsIcon->Y = 280;
    
    ChipsGoldIcon->Texture = "CHIPGOLD";
    ChipsGoldIcon->X = 24;
    ChipsGoldIcon->Y = 300;
    
    ChipsPlatIcon->Texture = "CHIPPLAT";
    ChipsPlatIcon->X = 24;
    ChipsPlatIcon->Y = 336;
    
    InventoryIcon->Texture = "GPAKA0";
    InventoryIcon->X = 40;
    InventoryIcon->Y = 428;
    
    ModuleLabel->X = 84;
    ModuleLabel->Y = 116;
    ModuleLabel->Color = "Green";
    ModuleLabel->Big = true;
    
    TurretPartsLabel->X = 84;
    TurretPartsLabel->Y = 148;
    TurretPartsLabel->Color = "White";
    TurretPartsLabel->Big = true;
    
    AugChargeLabel->X = 84;
    AugChargeLabel->Y = 180;
    AugChargeLabel->Color = "Yellow";
    AugChargeLabel->Big = true;
    
    AugSlotsLabel->X = 84;
    AugSlotsLabel->Y = 200;
    AugSlotsLabel->Color = "Green";
    AugSlotsLabel->Big = true;
    
    AugUpgradesLabel->X = 84;
    AugUpgradesLabel->Y = 224;
    AugUpgradesLabel->Color = "Green";
    AugUpgradesLabel->Big = true;
    
    StimsLabel->X = 84;
    StimsLabel->Y = 264;
    StimsLabel->Color = "White";
    StimsLabel->Big = true;
    
    ChipsGoldLabel->X = 84;
    ChipsGoldLabel->Y = 314;
    ChipsGoldLabel->Color = "Gold";
    ChipsGoldLabel->Big = true;
    
    ChipsPlatLabel->X = 84;
    ChipsPlatLabel->Y = 350;
    ChipsPlatLabel->Color = "White";
    ChipsPlatLabel->Big = true;
    
    InventoryLabel->X = 84;
    InventoryLabel->Y = 412;
    InventoryLabel->Color = "White";
    InventoryLabel->Big = true;
    
    // --------------------------------------------------
    // Map Stats
    //
    
    str MapType = "Standard Map";
    
    GUIIcon *MapIcon = GUICreateIcon(Window);
    
    GUILabel *MapNameLabel = GUICreateLabel(Window);
    GUILabel *MapInfoLabel = GUICreateLabel(Window);
    GUILabel *MapTimeLabel = GUICreateLabel(Window);;
    GUILabel *MapKillsLabel = GUICreateLabel(Window);
    GUILabel *MapItemsLabel = GUICreateLabel(Window);
    GUILabel *MapSecretsLabel = GUICreateLabel(Window);
    
    if (CurrentLevel->SecretMap)
        MapType = "Secret Map";
    if (CurrentLevel->UACBase)
        MapType = "UAC Base";
    if (CurrentLevel->UACArena)
        MapType = "UAC Arena";
    
    MapIcon->Texture = "PMAPA0";
    MapIcon->X = 300;
    MapIcon->Y = 128;
    
    MapNameLabel->X = 328;
    MapNameLabel->Y = 110;
    MapNameLabel->Color = "White";
    MapNameLabel->Big = true;
    
    MapInfoLabel->X = 328;
    MapInfoLabel->Y = 122;
    MapInfoLabel->Color = "Green";
    MapInfoLabel->Big = true;
    
    MapTimeLabel->X = 328;
    MapTimeLabel->Y = 134;
    MapTimeLabel->Color = "Orange";
    MapTimeLabel->Big = true;
    
    MapKillsLabel->X = 328;
    MapKillsLabel->Y = 146;
    MapKillsLabel->Big = true;
    
    MapItemsLabel->X = 328;
    MapItemsLabel->Y = 158;
    MapItemsLabel->Big = true;
    
    MapSecretsLabel->X = 328;
    MapSecretsLabel->Y = 170;
    MapSecretsLabel->Big = true;
    
    // --------------------------------------------------
    // Shield
    //
    
    // --------------------------------------------------
    // Current Stim / Toxicity
    //
    
    // --------------------------------------------------
    // Update Loop
    //
    
    while (true)
    {
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
            MapIcon->Visible = true;
            MapNameLabel->Visible = true;
            MapInfoLabel->Visible = true;
            MapTimeLabel->Visible = true;
            MapKillsLabel->Visible = true;
            MapItemsLabel->Visible = true;
            MapSecretsLabel->Visible = true;
        }
        else
        {
            MapIcon->Visible = false;
            MapNameLabel->Visible = false;
            MapInfoLabel->Visible = false;
            MapTimeLabel->Visible = false;
            MapKillsLabel->Visible = false;
            MapItemsLabel->Visible = false;
            MapSecretsLabel->Visible = false;
        }
        
        Delay(1);
    }
}
*/

// Temporary, for testing coordinates
NamedScript Console void GUITest(int X, int Y, int X2, int Y2)
{
    GUITestX = X + (X2 / 100);
    GUITestY = Y + (Y2 / 100);
}
