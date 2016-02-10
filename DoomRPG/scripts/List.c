#include "List.h"

ListNode *ListCreateNode()
{
    ListNode *NewNode = (ListNode *)malloc(sizeof(ListNode));
    
    NewNode->Data = NULL;
    
    NewNode->Next = NULL;
    NewNode->Prev = NULL;
    
    return NewNode;
}

void ListInsert(ListNode *Node, void *Data)
{
    while (Node->Next != NULL)
        Node = Node->Next;
    
    Node->Next = ListCreateNode();
    (Node->Next)->Prev = Node;
    
    Node = Node->Next;
    Node->Data = Data;
    Node->Next = NULL;
}

void ListRemove(ListNode *Node, int Index)
{
    for (int i = 0; i < Index; i++)
        Node = Node->Next;
    
    if (Node == NULL)
        return;
    
    ListNode *TempNode = Node->Next;
    Node->Next = TempNode->Next;
    TempNode->Prev = Node;
    
    free(TempNode);
}

int ListGetSize(ListNode *Node)
{
    int Size = 0;
    
    while (Node->Next != NULL)
        Size++;
    
    return Size;
}
