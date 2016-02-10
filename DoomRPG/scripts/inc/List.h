#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#include "Defs.h"

typedef struct ListNode_S ListNode;

struct ListNode_S
{
    void *Data;
    
    struct ListNode_S *Next;
    struct ListNode_S *Prev;
};

ListNode *ListCreateNode();

void ListInsert(ListNode *, void *);
void ListRemove(ListNode *, int);

int ListGetSize(ListNode *);

#endif
