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
    else if (Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Close)
        Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Close(Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel);
    
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
        
        DrawBackgroundWindow();
        UpdateTabs();
        UpdateGUICursor();
        
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
    if(GetCVar("drpg_debug"))
    {
        SetFont("SMALLFONT");
        HudMessage("%d, %d", (Player.GUI.Mouse.X - WINDOW_X), (Player.GUI.Mouse.Y - WINDOW_Y - 48));
        EndHudMessage(HUDMSG_PLAIN, GUI_CURSOR_ID + 25, "Untranslated", Player.GUI.Mouse.X, Player.GUI.Mouse.Y + 25, 0.03);
    }
    
    if (Player.GUI.Mouse.ActiveTooltip != NULL && Player.GUI.Mouse.ActiveTooltip->Visible == true)
        DrawTooltip(Player.GUI.Mouse.ActiveTooltip);
    
    if (!GetCVar("drpg_debug_gui") || (Player.GUI.Mouse.LeftButton && Player.GUI.Mouse.EditItem))
        Player.GUI.Mouse.EditItem = NULL;
    
    if (Player.GUI.Mouse.EditItem)
    {
        Player.GUI.Mouse.EditItem->X = Player.GUI.Mouse.X - WINDOW_X;
        Player.GUI.Mouse.EditItem->Y = Player.GUI.Mouse.Y - WINDOW_Y - 48;
        LogMessage(StrParam("X: %d Y: %d", Player.GUI.Mouse.EditItem->X, Player.GUI.Mouse.EditItem->Y));
    }
}

void DrawTooltip(GUITooltip *Tooltip)
{
    int Type = Tooltip->Type;
    str Title = Tooltip->Title;
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
        
        Longest = Round(StrLen(Title) * 1.5);
        
        for (int i = 0; i < StrLen(Text); i++)
        {
            Index++;
            
            if (Text[i] == '\n' || i == (StrLen(Text) - 1))
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
        Width = Longest * 8;
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
            //Width += 96;
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
        if (Type == TT_BIG)
        {
            Width *= 1.5;
            Height *= 1.5;
            
            // Bounding
            if (X > ScreenWidth - Width)
                X = ScreenWidth - Width;
            if (Y > ScreenHeight - Height)
                Y = ScreenHeight - Height;
            
            // Text
            SetFont("BIGFONT");
            HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, GUI_CURSOR_ID + 5, Color, X + (NoBack ? 0.1 : 5.1), Y + (NoBack ? 0.1 : 5.1), 0.03);
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
    if (Player.GUI.Mouse.X >= X && Player.GUI.Mouse.X < X + Width &&
        Player.GUI.Mouse.Y >= Y && Player.GUI.Mouse.Y < Y + Height)
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
            if (Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Close)
                Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Close(Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel);
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
        {
            Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel->Update(Player.GUI.TabStrip.Tabs[Player.GUI.TabStrip.ActiveTab].Panel);
        }
    }
}

GUITooltip *GUICreateTooltip()
{
    GUITooltip *Tooltip = calloc(sizeof(GUITooltip), 1);
    
    Tooltip->Type = TT_BASIC;
    Tooltip->Color = "White";
    Tooltip->Visible = true;
    
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
    PrintSprite(StrParam("%STL", Prefix), (StartID == 0 ? 0 : StartID++), X + 0.1, Y + 0.1, 0.03);
    PrintSprite(StrParam("%STR", Prefix), (StartID == 0 ? 0 : StartID++), X + Width + 0.2, Y + 0.1, 0.03);
    PrintSprite(StrParam("%SBL", Prefix), (StartID == 0 ? 0 : StartID++), X + 0.1, Y + Height + 0.2, 0.03);
    PrintSprite(StrParam("%SBR", Prefix), (StartID == 0 ? 0 : StartID++), X + Width + 0.2, Y + Height + 0.2, 0.03);
    
    // Border sides
    SetHudClipRect(X, Y + BorderSize, BorderSize, Height - (BorderSize * 2));
    PrintSprite(StrParam("%SL", Prefix), (StartID == 0 ? 0 : StartID++), X + 0.1, Y + 0.1, 0.03);
    SetHudClipRect(X + Width - BorderSize, Y + BorderSize, BorderSize, Height - (BorderSize * 2));
    PrintSprite(StrParam("%SR", Prefix), (StartID == 0 ? 0 : StartID++), X + Width + 0.2, Y + 0.1, 0.03);
    SetHudClipRect(X + BorderSize, Y, Width - (BorderSize * 2), BorderSize);
    PrintSprite(StrParam("%ST", Prefix), (StartID == 0 ? 0 : StartID++), X + BorderSize + 0.1, Y + 0.1, 0.03);
    SetHudClipRect(X + BorderSize, Y + Height - BorderSize, Width - (BorderSize * 2), BorderSize);
    PrintSprite(StrParam("%SB", Prefix), (StartID == 0 ? 0 : StartID), X + BorderSize + 0.1, Y + Height + 0.2, 0.03);
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
        if (!Kind || Kind == Panel->Controls[i]->Kind)
            if (!StrCmp(Name, Panel->Controls[i]->Name))
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
    Label->Control.id = 0;
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
    Icon->Control.id = 0;
    Icon->Control.Visible = true;
    
    Icon->Control.Update = (ControlUpdateFunc)UpdateIcon;
    
    Icon->CalculateSize = true;
    Icon->Pulse = 0;
    Icon->Alpha = 0;
    Icon->Radius = 1;
    
    Icon->Enabled = true;
    
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
    Bar->Control.Width = 0;
    Bar->Control.Height = 0;
    Bar->Control.Visible = true;
    
    Bar->Type = GUI_BAR_PIXEL;
    
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

NamedScript GUIBorder *GUIAddBorder(GUIPanel *Panel, str Name)
{
    GUIBorder *Border = calloc(sizeof(GUIBorder), 1);
    
    if(!GUIAddExistingControl(Panel, (GUIControl *)Border))
    {
        free(Border);
        return NULL;
    }
    
    Border->Control.Name = Name;
    Border->Control.Kind = CTL_BORDER;
    Border->Control.Owner = Panel;
    
    Border->Control.X = 0;
    Border->Control.Y = 0;
    Border->Control.Width = 32;
    Border->Control.Height = 32;
    Border->Control.id = 0;
    Border->Control.Visible = true;
    
    Border->Texture = "Bor";
    Border->BorderSize = 8;
    
    Border->Control.Update = (ControlUpdateFunc)UpdateBorder;
    
    return Border;
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
    EndHudMessage(HUDMSG_PLAIN, Label->Control.id, Color, X, Y, 0.05);
    
    // Debugging - Draw a border to show the Label's width/height
    if (GetCVar("drpg_debug_gui"))
        DrawBorder("Bor", 0, 8, X, (Y + (Big ? -6 : 0)), Width, Height);
    

    if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height))
    {
        if (Label->Control.Hover)
            Label->Control.Hover((GUIControl *)Label);
        // Tooltip
        if (Label->Control.Tooltip != NULL)
            Player.GUI.Mouse.ActiveTooltip = Label->Control.Tooltip;
    }
    
    // Context Menu
    if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height) && Player.GUI.Mouse.RightButton && Label->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Label->Control.ContextMenu;
    
    // OnClick Event
    if (GetCVar("drpg_debug_gui"))
        if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.LeftButton && Player.GUI.Mouse.ActiveContextMenu == NULL)
            GUIEditPosition(&Label->Control);
}

NamedScript void UpdateIcon(GUIIcon *Icon)
{
    int X = WINDOW_X + Icon->Control.X;
    int Y = WINDOW_Y + Icon->Control.Y + 48;
    int Width = Icon->Control.Width;
    int Height = Icon->Control.Height;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    // Debugging - Draw a border to show the Icon's width/height
    if (GetCVar("drpg_debug_gui"))
        DrawBorder("Bor", 0, 8, X, Y, Width, Height);
    
    if (InRegion(X, Y, Width, Height))
    {
        //OnHover Event
        if (Icon->Control.Hover)
            Icon->Control.Hover((GUIControl *)Icon);
        // Tooltip
        if (Icon->Control.Tooltip != NULL)
            Player.GUI.Mouse.ActiveTooltip = Icon->Control.Tooltip;
    }
    
    // Context Menu
    if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Icon->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Icon->Control.ContextMenu;
    
    // OnClick Event
    if (GetCVar("drpg_debug_gui"))
    {
        if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.LeftButton && Player.GUI.Mouse.ActiveContextMenu == NULL)
            GUIEditPosition(&Icon->Control);
    }
    else if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.LeftButton && Icon->Control.Click && Player.GUI.Mouse.ActiveContextMenu == NULL)
        Icon->Control.Click((GUIControl *)Icon);

    //recheck in case these values were modified by events
    X = WINDOW_X + Icon->Control.X;
    Y = WINDOW_Y + Icon->Control.Y + 48;
    Width = Icon->Control.Width;
    Height = Icon->Control.Height;    
    
    str Texture = Icon->Texture;
    int XOff = Icon->XOff;
    int YOff = Icon->YOff;
    bool CalculateSize = Icon->CalculateSize;
    fixed Pulse = Icon->Pulse;
    fixed Alpha = Icon->Alpha;
    fixed Radius = Icon->Radius;
    bool Enabled = Icon->Enabled;
    
    // Automatically detect X/Y Offset if none are specified
    if (XOff == 0 && YOff == 0 && CalculateSize)
    {
        XOff = Width / 2;
        YOff = Height;
    }
    
    // Drawing
    if (Enabled && Pulse > 0)
    {
        PrintSpritePulse(Texture, Icon->Control.id, X + XOff + 0.1, Y + YOff + 0.1, Alpha, Pulse, Radius, false);
    }
    else if (!Enabled || (Pulse == 0 && Alpha > 0))
    {
        PrintSpriteAlpha(Texture, Icon->Control.id, X + XOff + 0.1, Y + YOff + 0.1, 0.05, (Alpha ? Alpha : 0.33));
    }
    else
    {
        PrintSprite(Texture, Icon->Control.id, X + XOff + 0.1, Y + YOff + 0.1, 0.05);
    }
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
    if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height))
    {
        HudMessage("%S", Text);
        EndHudMessage(HUDMSG_PLAIN, Button->Control.id, HoverColor, X + 0.1, Y, 0.05);
    }
    else
    {
        HudMessage("%S", Text);
        EndHudMessage(HUDMSG_PLAIN, Button->Control.id, Color, X + 0.1, Y, 0.05);
    }

    // Debugging - Draw a border to show the Button's width/height
    if (GetCVar("drpg_debug_gui"))
        DrawBorder("Bor", 0, 8, X, (Y + (Big ? -6 : 0)), Width, Height);
    

    if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height)) 
    {
        //OnHover
        if (Button->Control.Hover)
            Button->Control.Hover((GUIControl *)Button);
        // Tooltip
        if (Button->Control.Tooltip != NULL)
            Player.GUI.Mouse.ActiveTooltip = Button->Control.Tooltip;
    }
    
    // Context Menu
    if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height) && Player.GUI.Mouse.RightButton && Button->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Button->Control.ContextMenu;
    
    // OnClick event
    if (GetCVar("drpg_debug_gui"))
    {
        if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height) && Player.GUI.Mouse.LeftButton && Player.GUI.Mouse.ActiveContextMenu == NULL)
            GUIEditPosition(&Button->Control);
    }
    else if (InRegion(X, (Y + (Big ? -6 : 0)), Width, Height) && Player.GUI.Mouse.LeftButton && Button->Control.Click && Player.GUI.Mouse.ActiveContextMenu == NULL)
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
    int id = Bar->Control.id;
    int Type = Bar->Type;
    bool FadePrint = Bar->FadePrint;
    fixed FadeLength = Bar->FadeLength;
    
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
    
    // Auto-calculate width and height based on Value
    if (Width == 0 && Height == 0)
    {
        Width = Value;
        Height = 6;
    }
    
    // Drawing
    if (Type != GUI_BAR_CLIP)
    {
        for (int i = 0; i < Value; i++)
        {
            if (Type == GUI_BAR_PIXEL)
                PrintSprite(Texture, (id == 0 ? 0 : (id + i)), X + 0.1 + i, Y + 2, 0.05);
            else if (Type == GUI_BAR_FADE && FadePrint)
            {
                PrintSpriteFade(Texture, (id == 0 ? 0 : (id + i)), X + 0.1 + i, Y + 2, 0.05, FadeLength);
                Bar->FadePrint = false;
            }
        }
    }
    else
    {
        SetHudClipRect(X, (Y - Height / 2), Value, Height);
        PrintSprite(Texture, id == 0 ? 0 : id, X + 0.1, Y, 0.05);
        SetHudClipRect(0, 0, 0, 0); //Reset
    }
        
    bool MouseOver = InRegion(X, Y, Width, Height);
//Hover
    if (MouseOver)
    {
        //OnHover
        if (Bar->Control.Hover)
            Bar->Control.Hover((GUIControl *)Bar);
        // Tooltip
        if (Bar->Control.Tooltip != NULL)
            Player.GUI.Mouse.ActiveTooltip = Bar->Control.Tooltip;
    }
    
    // Context Menu
    if (MouseOver && Player.GUI.Mouse.RightButton && Bar->Control.ContextMenu != NULL)
        Player.GUI.Mouse.ActiveContextMenu = Bar->Control.ContextMenu;
    
    // OnClick Event
    if (GetCVar("drpg_debug_gui"))
        if (MouseOver && Player.GUI.Mouse.LeftButton && Player.GUI.Mouse.ActiveContextMenu == NULL)
            GUIEditPosition(&Bar->Control);
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
    int id = List->Control.id;
    
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
            EndHudMessage(HUDMSG_PLAIN, id, HoverColors[i], X + 0.1, Y + ((i - Offset) * 10.0), 0.05);
            List->Selected = i;
            id++;
            
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
            EndHudMessage(HUDMSG_PLAIN, id, Colors[i], X + 0.1, Y + ((i - Offset) * 10.0), 0.05);
            id++;
        }
    }
    
    // Scroll Arrows
    if (List->Offset > 0)
    {
        PrintSprite("ListUp", id, X + Longest + 16.0, Y + 8.0, 0.05);
        id++;
    }
    if (List->Offset < MaxEntries - Shown)
    {
        PrintSprite("ListDn", id, X + Longest + 16.0, Y + (Shown * 10.0) - 20.0, 0.05);
        id++;
    }
    if (InRegion(X + Longest + 16.0, Y + 4.0, 24, 24) && Player.GUI.Mouse.LeftButton && List->Offset > 0)
        List->Offset--;
    if (InRegion(X + Longest + 16.0, Y + (Shown * 10.0) - 24.0, 24, 24) && Player.GUI.Mouse.LeftButton && List->Offset < MaxEntries - Shown)
        List->Offset++;
    
    /* if (GetCVar("drpg_debug_gui"))
        if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.LeftButton && Player.GUI.Mouse.ActiveContextMenu == NULL)
            GUIEditPosition((GUIControl *)List); */
}

NamedScript void UpdateGrid(GUIGrid *Grid)
{
    // TODO
}

NamedScript void UpdateBorder(GUIBorder *Border)
{
    str Texture = Border->Texture;
    int BorderSize = Border->BorderSize;
    fixed X = WINDOW_X + Border->Control.X;
    fixed Y = WINDOW_Y + Border->Control.Y + 48;
    int Width = Border->Control.Width;
    int Height = Border->Control.Height;
    int id = Border->Control.id;
    
    // Set the Resolution/HUD Size
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    //Draw Border
    DrawBorder(Texture, id, BorderSize, X, Y, Width, Height);
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


void GUIEditPosition(GUIControl *Obj)
{
    if (!Player.GUI.Mouse.EditItem)
        Player.GUI.Mouse.EditItem = Obj;
    else
        Player.GUI.Mouse.EditItem = NULL;
}

// Temporary, for testing coordinates
NamedScript Console void GUITest(int X, int Y, int X2, int Y2)
{
    GUITestX = X + (X2 / 100);
    GUITestY = Y + (Y2 / 100);
}
