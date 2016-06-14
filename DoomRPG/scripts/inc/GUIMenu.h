#ifndef DOOMRPG_GUIMENU_H
#define DOOMRPG_GUIMENU_H

#include "Defs.h"

// Menu Creation
NamedScript void CreateGUIMenu();
NamedScript void CreateTabs();
NamedScript void CreatePanels();

// Panel functions
NamedScript void CreateOverviewPanel();
NamedScript void UpdateOverviewPanel(GUIPanel *);

#endif
