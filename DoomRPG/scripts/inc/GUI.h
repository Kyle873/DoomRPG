#ifndef DOOMRPG_GUI_H
#define DOOMRPG_GUI_H

#include "Defs.h"

NamedScript Console void ToggleGUI();

NamedScript void CreateGUIMenu();
NamedScript void CreateTabs();
NamedScript void CreatePanels();

NamedScript void UpdateGUIMenu();
NamedScript void UpdateGUICursor();
NamedScript void UpdateTabs();

// Drawing
NamedScript void DrawBackgroundWindow();
NamedScript void DrawGlowLine();
void DrawBorder(str, int, int, int, int, int, int);
void DrawTooltip(GUITooltip *);

// Panel Functions
NamedScript GUIPanel *GUICreatePanel();
NamedScript OptionalArgs(1) GUIControl *GUIControlByName(GUIPanel *, str, EControlTypes);
NamedScript bool GUIAddExistingControl(GUIPanel *, GUIControl *);
NamedScript GUILabel  *GUIAddLabel(GUIPanel *, str);
NamedScript GUIIcon   *GUIAddIcon(GUIPanel *, str);
NamedScript GUIButton *GUIAddButton(GUIPanel *, str);
NamedScript GUIBar    *GUIAddBar(GUIPanel *, str);
NamedScript GUIList   *GUIAddList(GUIPanel *, str);
NamedScript GUIGrid   *GUIAddGrid(GUIPanel *, str);
NamedScript void GUIUpdatePanelControls(GUIPanel *Panel);

// Control Functions
void UpdateLabel(GUILabel *);
void UpdateIcon(GUIIcon *);
void UpdateButton(GUIButton *);
void UpdateBar(GUIBar *);
void UpdateList(GUIList *);
void UpdateGrid(GUIGrid *);

// Utility
bool InRegion(int, int, int, int);

GUITooltip *GUICreateTooltip();
GUIContextMenu *GUICreateContextMenu();

// Panel functions
NamedScript void CreateOverviewPanel();
void UpdateOverviewPanel(GUIPanel *);

#endif
