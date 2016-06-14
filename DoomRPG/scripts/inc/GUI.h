#ifndef DOOMRPG_GUI_H
#define DOOMRPG_GUI_H

#include "Defs.h"

NamedScript Console void ToggleGUI();

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
NamedScript void UpdateLabel(GUILabel *);
NamedScript void UpdateIcon(GUIIcon *);
NamedScript void UpdateButton(GUIButton *);
NamedScript void UpdateBar(GUIBar *);
NamedScript void UpdateList(GUIList *);
NamedScript void UpdateGrid(GUIGrid *);

// Utility
bool InRegion(int, int, int, int);

GUITooltip *GUICreateTooltip();
GUIContextMenu *GUICreateContextMenu();

//Debugging
NamedScript Console void GUITest(int, int, int, int);

#endif
