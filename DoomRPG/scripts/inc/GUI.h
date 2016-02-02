#ifndef DOOMRPG_GUI_H
#define DOOMRPG_GUI_H

#include "Defs.h"

NamedScript Console void ToggleGUI();

NamedScript void CheckCursor();
NamedScript void CheckGUI();

// Window/Control Handling
void HandleTabStrip(GUITabStrip *);
void HandleWindow(GUIWindow *);
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
GUIWindow *GUICreateWindow();
void GUIDeleteWindow(GUIWindow *);
GUILabel *GUICreateLabel(GUIWindow *);
GUIIcon *GUICreateIcon(GUIWindow *);
GUIButton *GUICreateButton(GUIWindow *);
GUIBar *GUICreateBar(GUIWindow *);
GUIList *GUICreateList(GUIWindow *);
GUIGrid *GUICreateGrid(GUIWindow *);
GUITooltip *GUICreateTooltip();
GUIContextMenu *GUICreateContextMenu();

// Utility
bool InRegion(int, int, int, int);
void DrawBorder(int, int, int, int, str, str);

// Effects
NamedScript void DrawScanLine();

// Creation
void CreateTabs();
NamedScript void UpdateMainWindow();

#endif
