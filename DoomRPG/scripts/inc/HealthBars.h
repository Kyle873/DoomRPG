#ifndef DOOMRPG_HEALTHBARS_H
#define DOOMRPG_HEALTHBARS_H

#include "Defs.h"

int RPGMap HealthBarID;
fixed RPGMap HealthBarX;
fixed RPGMap HealthBarY;

bool RPGMap HealthBarClipEnabled;
fixed RPGMap HealthBarAlpha;
int RPGMap HealthBarClipX;
int RPGMap HealthBarClipY;
int RPGMap HealthBarClipWidth;
int RPGMap HealthBarClipHeight;

NamedScript void HealthBars();

void DrawBarBase(HUDBarInfo *);
void DrawBarEmblems(HUDBarInfo *);
void DrawBarFill(HUDBarInfo *);
void DrawBarStats(HUDBarInfo *);
void DrawBarAuras(HUDBarInfo *);

#endif
