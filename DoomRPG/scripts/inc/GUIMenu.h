#ifndef DOOMRPG_GUIMENU_H
#define DOOMRPG_GUIMENU_H

#include "Defs.h"

// Menu Creation
void CreateMenus();

// Menu Updating
void MenuUpdate();
NamedScript void UpdateMainMenu();
NamedScript void UpdateStatsMenu();
NamedScript void UpdateAugsMenu();
NamedScript void UpdateSkillsMenu();

#endif
