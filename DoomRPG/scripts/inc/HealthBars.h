#ifndef DOOMRPG_HEALTHBARS_H
#define DOOMRPG_HEALTHBARS_H

#include "Defs.h"

extern int RPGMap HealthBarID;
extern fixed RPGMap HealthBarX;
extern fixed RPGMap HealthBarY;

extern bool RPGMap HealthBarClipEnabled;
extern fixed RPGMap HealthBarAlpha;
extern int RPGMap HealthBarClipX;
extern int RPGMap HealthBarClipY;
extern int RPGMap HealthBarClipWidth;
extern int RPGMap HealthBarClipHeight;

NamedScript void HealthBars();

void DrawBarBase(HUDBarInfo *);
void DrawBarEmblems(HUDBarInfo *);
void DrawBarFill(HUDBarInfo *);
void DrawBarStats(HUDBarInfo *);
void DrawBarAuras(HUDBarInfo *);

#endif
