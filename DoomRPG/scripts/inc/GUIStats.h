#ifndef DOOMRPG_GUISTATS_H
#define DOOMRPG_GUISTATS_H

#include "Defs.h"

// Panel functions
NamedScript void CreateStatsPanel();
NamedScript void UpdateStatsPanel(GUIPanel *);
//NamedScript void CloseStatsPanel(GUIPanel *);

//OnClick handling
NamedScript void ButtonClicked(GUIControl *);

//OnHover handling
NamedScript void IconHover(GUIControl *);

int CostOfStatUpgrade(int *);
#endif
