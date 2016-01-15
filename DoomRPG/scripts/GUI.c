#include "Defs.h"

#include <stdlib.h>

#include "GUI.h"
#include "Menu.h"
#include "RPG.h"
#include "Utils.h"

static GUITooltip *Tooltip;
static GUIContextMenu *ContextMenu;

static fixed TestX = 0.0;
static fixed TestY = 0.0;

NamedScript Console void ToggleGUI()
{
	Player.GUIOpen = !Player.GUIOpen;
	
	if (Player.GUIOpen)
		SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
	else
		SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
}

void CreateTestWindow()
{
    GUIWindow *TestWindow = GUICreateWindow();
    TestWindow->X = 100;
    TestWindow->Y = 100;
    TestWindow->Width = 200;
    TestWindow->Height = 200;
    TestWindow->CanClose = false;
    TestWindow->Title = "Doorpeg GUI Test";
    Player.Window[WINDOW_MAIN] = TestWindow;
}

NamedScript void CheckCursor()
{
	Start:
	
	while (Player.GUIOpen)
	{
		int Width = GetCVar("drpg_menu_width");
		int Height = GetCVar("drpg_menu_height");
		
		// Set the Resolution/HUD Size
		SetHudSize(Width, Height, true);
		
		// Get X/Y input
		Player.Mouse.XAdd = GetPlayerInput(PlayerNumber(), INPUT_YAW);
		Player.Mouse.YAdd = GetPlayerInput(PlayerNumber(), INPUT_PITCH);
		
		// Get Buttons
		Player.Mouse.Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
		Player.Mouse.OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
		
		// Add X/Y input to current position
		Player.Mouse.X -= Player.Mouse.XAdd / 32;
		Player.Mouse.Y -= Player.Mouse.YAdd / 24;
		
		// Check resolution boundaries
		if (Player.Mouse.X < 0)
			Player.Mouse.X = 0;
		if (Player.Mouse.Y < 0)
			Player.Mouse.Y = 0;
		if (Player.Mouse.X > Width)
			Player.Mouse.X = Width;
		if (Player.Mouse.Y > Height)
			Player.Mouse.Y = Height;
		
		// Draw Cursor
		PrintSprite("Cursor", 0, Player.Mouse.X, Player.Mouse.Y, 0.05);
		
		// Mouse Input
		if (Player.Mouse.Buttons & BT_ATTACK)
			Player.Mouse.LeftButtonDown = true;
		else
			Player.Mouse.LeftButtonDown = false;
		if (Player.Mouse.Buttons & BT_ATTACK && !(Player.Mouse.OldButtons & BT_ATTACK))
			Player.Mouse.LeftButton = true;
		else
			Player.Mouse.LeftButton = false;
		if (Player.Mouse.Buttons & BT_ALTATTACK)
			Player.Mouse.RightButtonDown = true;
		else
			Player.Mouse.RightButtonDown = false;
		if (Player.Mouse.Buttons & BT_ALTATTACK && !(Player.Mouse.OldButtons & BT_ALTATTACK))
			Player.Mouse.RightButton = true;
		else
			Player.Mouse.RightButton = false;
		
		Delay(1);
	}
	
	Delay(1);
	goto Start;
}

NamedScript void CheckGUI()
{
	int Width = GetCVar("drpg_menu_width");
	int Height = GetCVar("drpg_menu_height");
	
	// Center Mouse
	Player.Mouse.X = Width / 2;
	Player.Mouse.Y = Height / 2;
	
    // Create Test Window
    CreateTestWindow();
    
	while (true)
	{
		if (Player.GUIOpen)
		{
			// Draw Context Menu
			if (ContextMenu != NULL)
				HandleContextMenu(ContextMenu);
			
			// Draw Tooltip
			if (Tooltip != NULL && ContextMenu == NULL)
			{
				DrawTooltip(Tooltip);
				Tooltip = NULL;
			}
			
			// Window Handling
			for (int i = 0; Player.Window[i] != NULL; i++)
			{
				if (Player.Window[i]->Visible)
				{
					if (!Player.Window[i]->RolledUp)
					{
						// Handle Labels
						for (int j = 0; Player.Window[i]->Labels[j] != NULL; j++)
							HandleLabel(Player.Window[i]->Labels[j]);
						
						// Handle Icons
						for (int j = 0; Player.Window[i]->Icons[j] != NULL; j++)
							HandleIcon(Player.Window[i]->Icons[j]);
						
						// Handle Buttons
						for (int j = 0; Player.Window[i]->Buttons[j] != NULL; j++)
							HandleButton(Player.Window[i]->Buttons[j]);
						
						// Handle Bars
						for (int j = 0; Player.Window[i]->Bars[j] != NULL; j++)
							HandleBar(Player.Window[i]->Bars[j]);
						
						// Handle Lists
						for (int j = 0; Player.Window[i]->Lists[j] != NULL; j++)
							HandleList(Player.Window[i]->Lists[j]);
					}
					
					// Handle Drawing and Input for the Window
					HandleWindow(Player.Window[i]);
				}
			}
		}
		
		Delay(1);
	}
}

void HandleWindow(GUIWindow *Window)
{
	// Set the Resolution/HUD Size
	int Width = GetCVar("drpg_menu_width");
	int Height = GetCVar("drpg_menu_height");
	SetHudSize(Width, Height, true);
	
	// Title
	SetFont("SMALLFONT");
	if (Window->Focused)
    {
		HudMessage("%S", Window->Title);
        EndHudMessage(HUDMSG_PLAIN, 0, ((InTitleBar(Window) || Window->Dragging) ? "Green" : "White"), Window->X + 16.1, Window->Y + 8.0, 0.05);
    }
	else
    {
		HudMessage("%S", Window->Title);
        EndHudMessage(HUDMSG_PLAIN, 0, "DarkGray", Window->X + 16.1, Window->Y + 8.0, 0.05);
    }
	
	// X Button
	if (Window->CanClose)
		if (InRegion(Window->X + Window->Width - 14.1, Window->Y + 12.0, 16, 8) && Window->Focused)
		{
			HudMessage("X");
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, Window->X + Window->Width - 14.1, Window->Y + 8.0, 0.05);
			
			if (Player.Mouse.LeftButton)
				Window->Visible = false;
			if (Player.Mouse.RightButton) // For Testing!
				GUIDeleteWindow(Window);
		}
		else
        {
			HudMessage("X");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", Window->X + Window->Width - 14.1, Window->Y + 8.0, 0.05);
        }
	
	// Roll Button
	if (Window->CanRoll)
		if (InRegion(Window->X + Window->Width - 28.1, Window->Y + 12.0, 14, 8) && Window->Focused)
		{
			HudMessage("_");
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, Window->X + Window->Width - 28.1, Window->Y + 8.0, 0.05);
			
			if (Player.Mouse.LeftButton)
				Window->RolledUp = !Window->RolledUp;
		}
		else
        {
			HudMessage("_");
            EndHudMessage(HUDMSG_PLAIN, 0, "White", Window->X + Window->Width - 28.1, Window->Y + 8.0, 0.05);
        }
	
	// Window Background & Border
	if (Window->RolledUp)
		SetHudClipRect(Window->X, Window->Y, Window->Width, 15);
	else
		SetHudClipRect(Window->X, Window->Y, Window->Width, Window->Height);
	PrintSprite("GUIBack", 0, Window->X, Window->Y, 0.05);
	PrintSprite("BarHorz", 0, Window->X, Window->Y + 14.0, 0.05);
	DrawBorder(Window->X, Window->Y, Window->Width, (Window->RolledUp ? 15 : Window->Height));
	SetHudClipRect(0, 0, 0, 0);
	SetFont("");
	
	// Drag Checking
	if (InTitleBar(Window) && Player.Mouse.LeftButtonDown && Window->Focused)
		Window->Dragging = true;
	if (Window->Dragging && !Player.Mouse.LeftButtonDown)
		Window->Dragging = false;
	
	// Dragging
	if (Window->Dragging)
	{
		Window->X -= Player.Mouse.XAdd / 32;
		Window->Y -= Player.Mouse.YAdd / 24;
		
		// Bounding
		if (Window->X < 0)
			Window->X = 0;
		if (Window->X > Width - Window->Width)
			Window->X = Width - Window->Width;
		if (Window->Y < 0)
			Window->Y = 0;
		if (Window->Y > (Window->RolledUp ? Height - 15 : Height - Window->Height))
			Window->Y = (Window->RolledUp ? Height - 15 : Height - Window->Height);
	}
	
	// Put into focus
	if (InRegion(Window->X, Window->Y, Window->Width, (Window->RolledUp ? 15 : Window->Height)) && Player.Mouse.LeftButton)
		FocusWindow(Window);
}

void HandleLabel(GUILabel *Label)
{
	// Don't handle the control if it's invisible
	if (!Label->Visible) return;
	
	str Text = Label->Text;
	int Alignment = Label->Alignment;
	fixed X = Label->Window->X + Label->X + 2;
	fixed Y = Label->Window->Y + Label->Y + 16;
	int Width = Label->Width;
	int Height = Label->Height;
	str Color = Label->Color;
	bool Big = Label->Big;
	
	// Set the Resolution/HUD Size
	SetHudSize(GetCVar("drpg_menu_width"), GetCVar("drpg_menu_height"), true);
	
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
	if (InRegion(X, Y, Width, Height) && Label->Window->Focused && Label->Tooltip != NULL)
		Tooltip = Label->Tooltip;
		
	// Context Menu
	if (InRegion(X, Y, Width, Height) && Player.Mouse.RightButton && Label->Window->Focused && Label->ContextMenu != NULL)
		ContextMenu = Label->ContextMenu;
}

void HandleIcon(GUIIcon *Icon)
{
	// Don't handle the control if it's invisible
	if (!Icon->Visible) return;

	str Texture = Icon->Texture;
	int X = Icon->Window->X + Icon->X + 2;
	int Y = Icon->Window->Y + Icon->Y + 16;
	int XOff = Icon->XOff;
	int YOff = Icon->YOff;
	int Width = Icon->Width;
	int Height = Icon->Height;
	bool CalculateSize = Icon->CalculateSize;
	
	// Set the Resolution/HUD Size
	SetHudSize(GetCVar("drpg_menu_width"), GetCVar("drpg_menu_height"), true);
	
	// Automatically detect X/Y Offset if none are specified
	if (XOff == 0 && YOff == 0 && CalculateSize)
	{
		XOff = Width / 2;
		YOff = Height;
	}
	
	// Drawing
	PrintSprite(Texture, 0, X + XOff + 0.1, Y + YOff + 0.1, 0.05);
	
	// Debugging - Draw a border to show the Icon's width/height
    if (GetCVar("drpg_debug"))
        DrawBorder(X, Y, Width, Height);
	
	// Tooltip
	if (InRegion(X + 4, Y + 8, Width, Height) && Icon->Window->Focused && Icon->Tooltip != NULL)
		Tooltip = Icon->Tooltip;
	
	// Context Menu
	if (InRegion(X + 4, Y + 8, Width, Height) && Player.Mouse.RightButton && Icon->Window->Focused && Icon->ContextMenu != NULL)
		ContextMenu = Icon->ContextMenu;
	
	// OnClick event
	if (InRegion(X + 4, Y + 8, Width, Height) && Player.Mouse.LeftButton && Icon->OnClick && Icon->Window->Focused && ContextMenu == NULL)
		Icon->OnClick(Icon);
}

void HandleButton(GUIButton *Button)
{
	// Don't handle the control if it's invisible
	if (!Button->Visible) return;

	str Text = Button->Text;
	int X = Button->Window->X + Button->X + 2;
	int Y = Button->Window->Y + Button->Y + 16;
	int Width = Button->Width;
	int Height = Button->Height;
	str Color = Button->Color;
	str HoverColor = Button->HoverColor;
	bool Big = Button->Big;
	
	// Set the Resolution/HUD Size
	SetHudSize(GetCVar("drpg_menu_width"), GetCVar("drpg_menu_height"), true);
	
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
	if (InRegion(X, Y, Width, Height) && !Button->Window->Dragging && Button->Window->Focused)
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
	if (InRegion(X, Y, Width, Height) && Button->Window->Focused && Button->Tooltip != NULL)
		Tooltip = Button->Tooltip;
	
	// Context Menu
	if (InRegion(X, Y, Width, Height) && Player.Mouse.RightButton && Button->Window->Focused && Button->ContextMenu != NULL)
		ContextMenu = Button->ContextMenu;
	
	// OnClick event
	if (InRegion(X, Y, Width, Height) && Player.Mouse.LeftButton && Button->OnClick && Button->Window->Focused && ContextMenu == NULL)
		Button->OnClick(Button);
}

void HandleBar(GUIBar *Bar)
{
	// Don't handle the control if it's invisible
	if (!Bar->Visible) return;

	int X = Bar->Window->X + Bar->X + 2;
	int Y = Bar->Window->Y + Bar->Y + 16;
	int Width = Bar->Width;
	int Height = Bar->Height;
	int Value = Bar->Value;
	int ValueMax = Bar->ValueMax;
	str Texture = Bar->Texture;
	
	// Set the Resolution/HUD Size
	SetHudSize(GetCVar("drpg_menu_width"), GetCVar("drpg_menu_height"), true);
	
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
	if (InRegion(X, Y, Width, Height) && Bar->Window->Focused && Bar->Tooltip != NULL)
		Tooltip = Bar->Tooltip;
	
	// Context Menu
	if (InRegion(X, Y, Width, Height) && Player.Mouse.RightButton && Bar->Window->Focused && Bar->ContextMenu != NULL)
		ContextMenu = Bar->ContextMenu;
}

void HandleList(GUIList *List)
{
	// Don't handle the control if it's invisible
	if (!List->Visible) return;
	
	// Reset the selected entry
	List->Selected = -1;
	
	int X = List->Window->X + List->X + 2;
	int Y = List->Window->Y + List->Y + 16;
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
	SetHudSize(GetCVar("drpg_menu_width"), GetCVar("drpg_menu_height"), true);
		
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
		
		if (InRegion(X, Y + 3 + ((i - Offset) * 10), Width, 9) && !List->Window->Dragging && List->Window->Focused && ContextMenu == NULL)
		{
			HudMessage("%S", Entries[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, HoverColors[i], X + 0.1, Y + ((i - Offset) * 10.0), 0.05);
			List->Selected = i;
			
			// Tooltip
			if (List->Window->Focused && List->Tooltip != NULL)
				Tooltip = List->Tooltip;
			
			// Context Menu
			if (Player.Mouse.RightButton && List->Window->Focused && List->ContextMenu != NULL)
				ContextMenu = List->ContextMenu;
			
			// OnClick event
			if (Player.Mouse.LeftButton && List->OnClick)
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
	if (InRegion(X + Longest + 16.0, Y + 4.0, 24, 24) && Player.Mouse.LeftButton && List->Window->Focused && List->Offset > 0)
		List->Offset--;
	if (InRegion(X + Longest + 16.0, Y + (Shown * 10.0) - 24.0, 24, 24) && Player.Mouse.LeftButton && List->Window->Focused && List->Offset < MaxEntries - Shown)
		List->Offset++;
}

void DrawTooltip(GUITooltip *Tooltip)
{
	int Type = Tooltip->Type;
	str Title = Tooltip->Text;
	str Text = Tooltip->Text;
	str Color = Tooltip->Color;
	int X = Player.Mouse.X + 8;
	int Y = Player.Mouse.Y + 8;
	int ScreenWidth = GetCVar("drpg_menu_width");
	int ScreenHeight = GetCVar("drpg_menu_height");
	int Width = Tooltip->Width;
	int Height = Tooltip->Height;
	str Icon = Tooltip->Icon;
	int IconXOff = Tooltip->IconXOff;
	int IconYOff = Tooltip->IconYOff;
	bool NoBack = Tooltip->NoBack;
	
	// Set the Resolution/HUD Size
	SetHudSize(GetCVar("drpg_menu_width"), GetCVar("drpg_menu_height"), true);
	
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
				DrawBorder(X, Y, Width, Height);
			
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
				DrawBorder(X, Y, Width, Height);
			
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
				DrawBorder(X, Y, Width, Height);
			
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
	DrawBorder(X + 16, Y + 32, Width, Height);
	
	// Draw/Handle Options
	for (int i = 0; StrLen(Menu->Name[i]) != 0; i++)
	{
		if (InRegion(X + 20, Y + 40 + (i * 10), Width, 11))
		{
			HudMessage("%S", Menu->Name[i]);
            EndHudMessage(HUDMSG_PLAIN, 0, MenuCursorColor, X + 18.1, Y + 40.0 + (i * 10), 0.05);
			
			// OnClick Event
			if (Player.Mouse.LeftButton && Menu->OnClick[i] != NULL)
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
	if (Player.Mouse.LeftButton || Player.Mouse.RightButton)
		ContextMenu = NULL;
}

GUIWindow *GUICreateWindow()
{
	GUIWindow *Window = calloc(sizeof(GUIWindow), 1);
	
	FocusWindow(Window);
	
	Window->Visible = true;
	Window->CanClose = true;
	Window->CanRoll = true;
	
	return Window;
}

void GUIDeleteWindow(GUIWindow *Window)
{
	// Free Controls
	for (int i = 0; i < MAX_CONTROLS; i++)
	{
		if (Window->Labels[i] != NULL) 	free(Window->Labels[i]);
		if (Window->Icons[i] != NULL) 	free(Window->Icons[i]);
		if (Window->Buttons[i] != NULL) 	free(Window->Buttons[i]);
		if (Window->Bars[i] != NULL) 	free(Window->Bars[i]);
		if (Window->Lists[i] != NULL) 	free(Window->Lists[i]);
	}
	
	// Free Window
	free(Window);
}

GUILabel *GUICreateLabel(GUIWindow *Window)
{
	GUILabel *Label = calloc(sizeof(GUILabel), 1);
	
	Label->Window = Window;
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
	
	Icon->Window = Window;
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
	
	Button->Window = Window;
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
	
	Bar->Window = Window;
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
	
	List->Window = Window;
	List->Visible = true;
	
	for (int i = 0; i < MAX_CONTROLS; i++)
		if (Window->Lists[i] == NULL)
		{
			Window->Lists[i] = List;
			break;
		}
	
	return List;
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

void FocusWindow(GUIWindow *Window)
{
	// Intersect Checking
	for (int i = 0; Player.Window[i] != NULL; i++)
	{
		// Continue if it's the same window
		if (Player.Window[i] == Window) continue;
		
		/* TODO: This check still needs some work
		// It needs to also account for a window not being completely inside another, as it is, a window will be completely unselectable if it's inside another one
		if (Window->X >= Player.Window[i]->X &&
			Window->X <= Player.Window[i]->Width &&
			Window->Y >= Player.Window[i]->Y &&
			Window->Y <= Player.Window[i]->Height)
			return; */
	}
	
	// Unfocus all Windows
	for (int i = 0; Player.Window[i] != NULL; i++)
		Player.Window[i]->Focused = false;
	
	Window->Focused = true;
}

bool InTitleBar(GUIWindow *Window)
{
	if (Player.Mouse.X > Window->X + 4 && Player.Mouse.X < Window->X + Window->Width - 32 &&
		Player.Mouse.Y > Window->Y + 8 && Player.Mouse.Y < Window->Y + 24)
		return true;
	else
		return false;
}

bool InRegion(int X, int Y, int Width, int Height)
{
	if (Player.Mouse.X > X && Player.Mouse.X < X + Width &&
		Player.Mouse.Y > Y && Player.Mouse.Y < Y + Height)
		return true;
	else
		return false;
}

void DrawBorder(int X, int Y, int Width, int Height)
{
	SetHudClipRect(X, Y, Width, Height);
	PrintSprite("BarHorz", 0, X, Y, 0.05);
	PrintSprite("BarHorz", 0, X, Y + Height - 1, 0.05);
	PrintSprite("BarVert", 0, X, Y, 0.05);
	PrintSprite("BarVert", 0, X + Width - 1, Y, 0.05);
	SetHudClipRect(0, 0, 0, 0);
	SetFont("");
}
