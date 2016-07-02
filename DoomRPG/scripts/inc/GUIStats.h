#ifndef DOOMRPG_GUISTATS_H
#define DOOMRPG_GUISTATS_H

#include "Defs.h"

// Panel functions
NamedScript void CreateStatsPanel();
NamedScript void UpdateStatsPanel(GUIPanel *);
//NamedScript void CloseStatsPanel(GUIPanel *);

//Buttons Event handling
NamedScript void ButtonClicked(GUIControl *);

//Icons Event handling
NamedScript void IconHover(GUIControl *);
NamedScript void IconUpClick(GUIControl *);
NamedScript void IconDownClick(GUIControl *);

void BuildOrderFormString(int);
int CostOfStatUpgrade(int);
#endif
