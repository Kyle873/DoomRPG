#include "Defs.h"

#include "GUI.h"
#include "Map.h"
#include "Menu.h"
#include "RPG.h"
#include "Utils.h"

NamedScript Console void ToggleGUI()
{
	Player.GUI.Open = !Player.GUI.Open;
	
	if (Player.GUI.Open)
    {
        ActivatorSound("gui/open", 127);
		SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
    }
	else
    {
        ActivatorSound("gui/close", 127);
		SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
    }
}

NamedScript void CheckCursor()
{
	Start:
	
	while (Player.GUI.Open)
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
		PrintSprite("Cursor", 0, Player.GUI.Mouse.X, Player.GUI.Mouse.Y, 0.05);
		
        Delay(1);
	}
	
	Delay(1);
	goto Start;
}

NamedScript void CheckGUI()
{
    int Current = Player.GUI.CurrentWindow;
	
	// Center Mouse
	Player.GUI.Mouse.X = GUI_WIDTH / 2;
	Player.GUI.Mouse.Y = GUI_HEIGHT / 2;
	
    // Create GUI
    if (!Player.GUI.Created)
    {
        CreateTabs();
        CreateMainWindow();
        
        Player.GUI.Created = true;
    }
    
	while (true)
	{
        // Tab Enabling/Disabling
        Player.GUI.TabStrip->Enabled[WINDOW_MISSION] = CurrentLevel->UACBase;
        Player.GUI.TabStrip->Enabled[WINDOW_TRANSPORT] = CurrentLevel->UACBase;
        Player.GUI.TabStrip->Enabled[WINDOW_TEAM] = InMultiplayer;
        
		if (Player.GUI.Open)
		{
			// Draw Context Menu
			if (Player.GUI.ContextMenu != NULL)
				HandleContextMenu(Player.GUI.ContextMenu);
			
			// Draw Tooltip
			if (Player.GUI.Tooltip != NULL && Player.GUI.ContextMenu == NULL)
			{
				DrawTooltip(Player.GUI.Tooltip);
				Player.GUI.Tooltip = NULL;
			}
			
            // Handle Labels
            for (int i = 0; Player.GUI.Window[Current]->Labels[i] != NULL; i++)
                HandleLabel(Player.GUI.Window[Current]->Labels[i]);
            
            // Handle Icons
            for (int i = 0; Player.GUI.Window[Current]->Icons[i] != NULL; i++)
                HandleIcon(Player.GUI.Window[Current]->Icons[i]);
            
            // Handle Buttons
            for (int i = 0; Player.GUI.Window[Current]->Buttons[i] != NULL; i++)
                HandleButton(Player.GUI.Window[Current]->Buttons[i]);
            
            // Handle Bars
            for (int i = 0; Player.GUI.Window[Current]->Bars[i] != NULL; i++)
                HandleBar(Player.GUI.Window[Current]->Bars[i]);
            
            // Handle Lists
            for (int i = 0; Player.GUI.Window[Current]->Lists[i] != NULL; i++)
                HandleList(Player.GUI.Window[Current]->Lists[i]);
            
            // Handle Grids
            for (int i = 0; Player.GUI.Window[Current]->Grids[i] != NULL; i++)
                HandleGrid(Player.GUI.Window[Current]->Grids[i]);
            
            // Handle Tab Strip
            HandleTabStrip(Player.GUI.TabStrip);
            
            // Handle Drawing and Input for the Window
            HandleWindow(Player.GUI.Window[Current]);
		}
		
		Delay(1);
	}
}

void HandleTabStrip(GUITabStrip *TabStrip)
{
    for (int i = 0; StrLen(TabStrip->Icon[i]) != 0; i++)
    {
        int X = 18 + i * 38;
        int Y = 18;
        
        if (InRegion(X - 12, Y - 10, 34, 38) && TabStrip->Enabled[i])
        {
            // Tooltip
            SetFont("BIGFONT");
            HudMessage("%S", TabStrip->Title[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", Player.GUI.Mouse.X + 8 + 0.1, Player.GUI.Mouse.Y + 8, 0.05);
            
            PrintSpritePulse(TabStrip->Icon[i], 0, X, Y, 0.75, 32.0, 0.25, false);
        }
        else if (!TabStrip->Enabled[i])
            PrintSpritePulse(TabStrip->Icon[i], 0, X, Y, 0.25, 256.0, 0.25, true);
        else
            PrintSprite(TabStrip->Icon[i], 0, X, Y, 0.05);
    }
    
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
	PrintSpritePulse("TabBack", 0, 0.1, 0.1, 0.85, 512.0, 0.15);
	DrawBorder(0, 0, GUI_WIDTH, 36, "BarHorz", "BarVertT");
}

void HandleWindow(GUIWindow *Window)
{
    if (!Random(0, 100) && !Player.GUI.ScanLine)
        DrawScanLine();
    
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
	PrintSpritePulse("GUIBack", 0, WINDOW_X + 0.1, WINDOW_Y + 0.1, 0.85, 512.0, 0.15);
	DrawBorder(WINDOW_X, WINDOW_Y, GUI_WIDTH - WINDOW_X, GUI_HEIGHT - WINDOW_Y, "BarHorz", "BarVert");
}

void HandleLabel(GUILabel *Label)
{
	// Don't handle the control if it's invisible
	if (!Label->Visible) return;
	
	str Text = Label->Text;
	int Alignment = Label->Alignment;
	fixed X = WINDOW_X + Label->X + 2;
	fixed Y = WINDOW_Y + Label->Y + 16;
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
		Player.GUI.Tooltip = Label->Tooltip;
    
	// Context Menu
	if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Label->ContextMenu != NULL)
		Player.GUI.ContextMenu = Label->ContextMenu;
}

void HandleIcon(GUIIcon *Icon)
{
	// Don't handle the control if it's invisible
	if (!Icon->Visible) return;

	str Texture = Icon->Texture;
	int X = WINDOW_X + Icon->X + 2;
	int Y = WINDOW_Y + Icon->Y + 16;
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
    if (GetCVar("drpg_debug_gui"))
        DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
	
	// Tooltip
	if (InRegion(X + 4, Y + 8, Width, Height) && Icon->Tooltip != NULL)
		Player.GUI.Tooltip = Icon->Tooltip;
	
	// Context Menu
	if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.RightButton && Icon->ContextMenu != NULL)
		Player.GUI.ContextMenu = Icon->ContextMenu;
	
	// OnClick Event
	if (InRegion(X + 4, Y + 8, Width, Height) && Player.GUI.Mouse.LeftButton && Icon->OnClick && Player.GUI.ContextMenu == NULL)
		Icon->OnClick(Icon);
}

void HandleButton(GUIButton *Button)
{
	// Don't handle the control if it's invisible
	if (!Button->Visible) return;

	str Text = Button->Text;
	int X = WINDOW_X + Button->X + 2;
	int Y = WINDOW_Y + Button->Y + 16;
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
		Player.GUI.Tooltip = Button->Tooltip;
	
	// Context Menu
	if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Button->ContextMenu != NULL)
		Player.GUI.ContextMenu = Button->ContextMenu;
	
	// OnClick event
	if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.LeftButton && Button->OnClick && Player.GUI.ContextMenu == NULL)
		Button->OnClick(Button);
}

void HandleBar(GUIBar *Bar)
{
	// Don't handle the control if it's invisible
	if (!Bar->Visible) return;

	int X = WINDOW_X + Bar->X + 2;
	int Y = WINDOW_Y + Bar->Y + 16;
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
		Player.GUI.Tooltip = Bar->Tooltip;
	
	// Context Menu
	if (InRegion(X, Y, Width, Height) && Player.GUI.Mouse.RightButton && Bar->ContextMenu != NULL)
		Player.GUI.ContextMenu = Bar->ContextMenu;
}

void HandleList(GUIList *List)
{
	// Don't handle the control if it's invisible
	if (!List->Visible) return;
	
	// Reset the selected entry
	List->Selected = -1;
	
	int X = WINDOW_X + List->X + 2;
	int Y = WINDOW_Y + List->Y + 16;
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
		
		if (InRegion(X, Y + 3 + ((i - Offset) * 10), Width, 9) && Player.GUI.ContextMenu == NULL)
		{
			HudMessage("%S", Entries[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, HoverColors[i], X + 0.1, Y + ((i - Offset) * 10.0), 0.05);
			List->Selected = i;
			
			// Tooltip
			if (List->Tooltip != NULL)
				Player.GUI.Tooltip = List->Tooltip;
			
			// Context Menu
			if (Player.GUI.Mouse.RightButton && List->ContextMenu != NULL)
				Player.GUI.ContextMenu = List->ContextMenu;
			
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

void DrawTooltip(GUITooltip *Tooltip)
{
	int Type = Tooltip->Type;
	str Title = Tooltip->Text;
	str Text = Tooltip->Text;
	str Color = Tooltip->Color;
	int X = Player.GUI.Mouse.X + 8;
	int Y = Player.GUI.Mouse.Y + 8;
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
			if (!NoBack)
				DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
			
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
			if (!NoBack)
				DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
			
			// Title
			SetFont("BIGFONT");
			HudMessage("%S", Tooltip->Title);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 8.1, Y + 16.0, 0.05);
			
			// Text
			SetFont("SMALLFONT");
			HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, X + 8.1, Y + 32.1, 0.05);
		}
		
		// Complex Tooltip
		if (Type == TT_COMPLEX)
		{
			// Add more Width
			Width += 100;
			Height += 48;
			
			// Bounding
			if (X > ScreenWidth - Width)
				X = ScreenWidth - Width;
			if (Y > ScreenHeight - Height)
				Y = ScreenHeight - Height;
			
			// Border
			if (!NoBack)
				DrawBorder(X, Y, Width, Height, "BarHorz", "BarVert");
			
			// Title
			SetFont("BIGFONT");
			HudMessage("%S", Tooltip->Title);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 64.1, Y + 16.0, 0.05);
			
			// Text
			SetFont("SMALLFONT");
			HudMessage("%S", Tooltip->Text);
            EndHudMessage(HUDMSG_PLAIN, 0, Color, X + 64.1, Y + 32.1, 0.05);
			
			// Icon
			PrintSprite(Tooltip->Icon, 0, X + IconXOff + 16.1, Y + IconYOff + 16.1, 0.05);
		}
		
		// Draw Background
		if (!NoBack)
		{
			SetHudClipRect(X, Y, Width, Height);
			PrintSprite("GUIBack", 0, X, Y, 0.05);
			SetHudClipRect(0, 0, 0, 0);
		}
	}
}

void HandleContextMenu(GUIContextMenu *Menu)
{
	int X = Menu->X;
	int Y = Menu->Y;
	int Width;
	int Height;
	int Longest;
	
	// Calculate the Width and Height
	for (int i = 0; StrLen(Menu->Name[i]) != 0; i++)
		if (StrLen(Menu->Name[i]) > Longest)
			Longest = StrLen(Menu->Name[i]);
	Width = Longest * 9;
	for (int i = 0; StrLen(Menu->Name[i]) != 0; i++)
		Height += 12;
	
	// Draw Border
	DrawBorder(X + 16, Y + 32, Width, Height, "BarHorz", "BarVert");
	
	// Draw/Handle Options
	for (int i = 0; StrLen(Menu->Name[i]) != 0; i++)
	{
		if (InRegion(X + 20, Y + 40 + (i * 10), Width, 11))
		{
			HudMessage("%S", Menu->Name[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, X + 18.1, Y + 40.0 + (i * 10), 0.05);
			
			// OnClick Event
			if (Player.GUI.Mouse.LeftButton && Menu->OnClick[i] != NULL)
				Menu->OnClick[i](Menu->Data);
		}
		else
        {
			HudMessage("%S", Menu->Name[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 18.1, Y + 40.0 + (i * 10), 0.05);
        }
	}
	
	// Draw Background
	SetHudClipRect(X + 16, Y + 32, Width, Height);
	PrintSprite("GUIBack", 0, X, Y, 0.05);
	SetHudClipRect(0, 0, 0, 0);
	
	// Close Menu
	if (Player.GUI.Mouse.LeftButton || Player.GUI.Mouse.RightButton)
		Player.GUI.ContextMenu = NULL;
}

GUITabStrip *GUICreateTabStrip()
{
	GUITabStrip *TabStrip = calloc(sizeof(GUITabStrip), 1);
	
	return TabStrip;
}

GUIWindow *GUICreateWindow()
{
	GUIWindow *Window = calloc(sizeof(GUIWindow), 1);
	
	return Window;
}

void GUIDeleteWindow(GUIWindow *Window)
{
	// Free Controls
	for (int i = 0; i < MAX_CONTROLS; i++)
	{
		if (Window->Labels[i] != NULL) 	free(Window->Labels[i]);
		if (Window->Icons[i] != NULL) 	free(Window->Icons[i]);
		if (Window->Buttons[i] != NULL) free(Window->Buttons[i]);
		if (Window->Bars[i] != NULL) 	free(Window->Bars[i]);
		if (Window->Lists[i] != NULL) 	free(Window->Lists[i]);
		if (Window->Grids[i] != NULL) 	free(Window->Grids[i]);
	}
	
	// Free Window
	free(Window);
}

GUILabel *GUICreateLabel(GUIWindow *Window)
{
	GUILabel *Label = calloc(sizeof(GUILabel), 1);
	
	Label->Alignment = LA_LEFT;
	Label->Visible = true;
	
	for (int i = 0; i < MAX_CONTROLS; i++)
		if (Window->Labels[i] == NULL)
		{
			Window->Labels[i] = Label;
			break;
		}
	
	return Label;
}

GUIIcon *GUICreateIcon(GUIWindow *Window)
{
	GUIIcon *Icon = calloc(sizeof(GUIIcon), 1);
	
	Icon->CalculateSize = true;
	Icon->Visible = true;
	
	for (int i = 0; i < MAX_CONTROLS; i++)
		if (Window->Icons[i] == NULL)
		{
			Window->Icons[i] = Icon;
			break;
		}
	
	return Icon;
}

GUIButton *GUICreateButton(GUIWindow *Window)
{
	GUIButton *Button = calloc(sizeof(GUIButton), 1);
	
	Button->Visible = true;
	
	for (int i = 0; i < MAX_CONTROLS; i++)
		if (Window->Buttons[i] == NULL)
		{
			Window->Buttons[i] = Button;
			break;
		}
	
	return Button;
}

GUIBar *GUICreateBar(GUIWindow *Window)
{
	GUIBar *Bar = calloc(sizeof(GUIBar), 1);
	
	Bar->Visible = true;
	
	for (int i = 0; i < MAX_CONTROLS; i++)
		if (Window->Bars[i] == NULL)
		{
			Window->Bars[i] = Bar;
			break;
		}
	
	return Bar;
}

GUIList *GUICreateList(GUIWindow *Window)
{
	GUIList *List = calloc(sizeof(GUIList), 1);
	
	List->Visible = true;
	
	for (int i = 0; i < MAX_CONTROLS; i++)
		if (Window->Lists[i] == NULL)
		{
			Window->Lists[i] = List;
			break;
		}
	
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

bool InRegion(int X, int Y, int Width, int Height)
{
	if (Player.GUI.Mouse.X > X && Player.GUI.Mouse.X < X + Width &&
		Player.GUI.Mouse.Y > Y && Player.GUI.Mouse.Y < Y + Height)
		return true;
	else
		return false;
}

void DrawBorder(int X, int Y, int Width, int Height, str HorzTexture, str VertTexture)
{
	PrintSprite(HorzTexture, 0, X + 0.1, Y, 0.05);
	PrintSprite(HorzTexture, 0, X + 0.1, Y + Height - 1, 0.05);
	PrintSprite(VertTexture, 0, X, Y + 0.1, 0.05);
	PrintSprite(VertTexture, 0, X + Width - 1, Y + 0.1, 0.05);
}

NamedScript void DrawScanLine()
{
    int Y = WINDOW_Y;
    int ID = SCANLINE_ID;
    
    SetHudSize(GUI_WIDTH, GUI_HEIGHT, true);
    
    Player.GUI.ScanLine = true;
    
    while (Y++ < GUI_HEIGHT + 32)
    {
        if (!Player.GUI.Open)
            break;
        
        SetHudClipRect(0, Y, GUI_WIDTH, 1);
        PrintSpriteFade("ScanLine", ID++, 0.1, Y, 0.05, 0.25);
        SetHudClipRect(0, 0, 0, 0);
        
        Delay(1);
    }
    
    for (int i = SCANLINE_ID; i < SCANLINE_ID + GUI_HEIGHT; i++)
        ClearMessage(i);
    
    Player.GUI.ScanLine = false;
}

// --------------------------------------------------
// GUI Creation
//

void CreateTabs()
{
    GUITabStrip *TabStrip = GUICreateTabStrip();
    
    TabStrip->Icon[WINDOW_MAIN] = "TMain";
    TabStrip->Title[WINDOW_MAIN] = "Overview";
    TabStrip->Enabled[WINDOW_MAIN] = true;
    TabStrip->Icon[WINDOW_STATS] = "TStats";
    TabStrip->Title[WINDOW_STATS] = "\CgStats";
    TabStrip->Enabled[WINDOW_STATS] = true;
    TabStrip->Icon[WINDOW_AUGS] = "TAugs";
    TabStrip->Title[WINDOW_AUGS] = "\CkAugmentations";
    TabStrip->Enabled[WINDOW_AUGS] = true;
    TabStrip->Icon[WINDOW_SKILLS] = "TSkills";
    TabStrip->Title[WINDOW_SKILLS] = "\CnSkills";
    TabStrip->Enabled[WINDOW_SKILLS] = true;
    TabStrip->Icon[WINDOW_SHIELD] = "TShield";
    TabStrip->Title[WINDOW_SHIELD] = "\CvShield";
    TabStrip->Enabled[WINDOW_SHIELD] = true;
    TabStrip->Icon[WINDOW_STIMS] = "TStims";
    TabStrip->Title[WINDOW_STIMS] = "\CcStims";
    TabStrip->Enabled[WINDOW_STIMS] = true;
    TabStrip->Icon[WINDOW_TURRET] = "TTurret";
    TabStrip->Title[WINDOW_TURRET] = "\CdTurret";
    TabStrip->Enabled[WINDOW_TURRET] = true;
    TabStrip->Icon[WINDOW_SHOP] = "TShop";
    TabStrip->Title[WINDOW_SHOP] = "\CfShop";
    TabStrip->Enabled[WINDOW_SHOP] = true;
    TabStrip->Icon[WINDOW_PAYOUT] = "TPayout";
    TabStrip->Title[WINDOW_PAYOUT] = "\CfPayout";
    TabStrip->Enabled[WINDOW_PAYOUT] = true;
    TabStrip->Icon[WINDOW_MISSION] = "TMission";
    TabStrip->Title[WINDOW_MISSION] = "\CaMissions";
    TabStrip->Enabled[WINDOW_MISSION] = true;
    TabStrip->Icon[WINDOW_TRANSPORT] = "TTrans";
    TabStrip->Title[WINDOW_TRANSPORT] = "\ChTransport";
    TabStrip->Enabled[WINDOW_TRANSPORT] = true;
    TabStrip->Icon[WINDOW_TEAM] = "TTeam";
    TabStrip->Title[WINDOW_TEAM] = "\CqTeam";
    TabStrip->Enabled[WINDOW_TEAM] = true;
    
    Player.GUI.TabStrip = TabStrip;
}

void CreateMainWindow()
{
    GUIWindow *Window = GUICreateWindow();
    
    // TODO
    
    Player.GUI.Window[WINDOW_MAIN] = Window;
}
