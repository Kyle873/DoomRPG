// ----------------------------------------------------------------------------
//
//  List.h
//
//  In-place linked list structure.
//
// ---

#ifndef DOOMRPG_LIST_H
#define DOOMRPG_LIST_H

#include <stdlib.h>

typedef struct LinkList_S LinkList;

struct LinkList_S
{
    LinkList  *Next;
    LinkList **Prev;
    void      *Owner;
};

static void Link_Insert(LinkList *this, void *object, LinkList **head)
{
    LinkList *next = *head;

    if((this->Next = next))
        next->Prev = &this->Next;

    this->Prev = head;
    *head = this;

    this->Owner = object;
}

static void Link_Remove(LinkList *this)
{
    LinkList **prev = this->Prev;
    LinkList  *next = this->Next;

    if(prev && (*prev = next))
        next->Prev = prev;

    this->Next = NULL;
    this->Prev = NULL;
}

#endif // DOOMRPG_LIST_H
