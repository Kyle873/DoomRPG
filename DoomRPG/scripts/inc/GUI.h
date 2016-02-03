#ifndef DOOMRPG_GUI_H
#define DOOMRPG_GUI_H

#include "Defs.h"

NamedScript Console void ToggleGUI();

NamedScript void CreateGUIMenu();
void CreateTabs();

NamedScript void UpdateGUIMenu();
NamedScript void UpdateGUICursor();
void UpdateTabs();

// Drawing
NamedScript void DrawBackgroundWindow();
NamedScript void DrawGlowLine();

// Utility
bool InRegion(int, int, int, int);

// Window/Control Handling
void HandleTabStrip(GUITabStrip *);
void HandleLabel(GUILabel *);
void HandleIcon(GUIIcon *);
void HandleButton(GUIButton *);
void HandleBar(GUIBar *);
void HandleList(GUIList *);
void HandleGrid(GUIGrid *);
void DrawTooltip(GUITooltip *);
void HandleContextMenu(GUIContextMenu *);

// Window/Control Creation
GUITabStrip *GUICreateTabStrip();
GUILabel *GUICreateLabel();
GUIIcon *GUICreateIcon();
GUIButton *GUICreateButton();
GUIBar *GUICreateBar();
GUIList *GUICreateList();
GUIGrid *GUICreateGrid();
GUITooltip *GUICreateTooltip();
GUIContextMenu *GUICreateContextMenu();

// Utility
void DrawBorder(str, int, int, int, int, int);

// Creation
void CreateTabs();
//NamedScript void UpdateMainWindow();

#endif
