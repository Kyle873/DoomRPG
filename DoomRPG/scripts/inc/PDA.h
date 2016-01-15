#ifndef DOOMRPG_PDA_H
#define DOOMRPG_PDA_H

#include "Defs.h"

typedef struct
{
    str Text;
    fixed X;
    fixed Y;
    int ID;
} MessageInfo;

NamedScript void PDARender();
NamedScript KeyBind void PDABoot();

#endif
