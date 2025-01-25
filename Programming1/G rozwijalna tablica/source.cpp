// Filip Jarzyna
/*

#include <iostream>

typedef unsigned char BYTE;
const BYTE SIZE = 2;

struct OBJECT_TYPE {
    int d123;
};

struct NODE_STRUCT {
    OBJECT_TYPE* object;
    BYTE use;
    NODE_STRUCT* next;
};
*/

NODE_STRUCT* NewNode(void)
{
    NODE_STRUCT* newElement = new NODE_STRUCT;
    newElement->next = NULL;
    newElement->object = new OBJECT_TYPE[SIZE];
    newElement->use = 0;
    return newElement;
}

void DeleteNode(NODE_STRUCT* node)
{
    if (node != NULL) {
        delete[] node->object;
        delete node;
    }
}

void Clear(NODE_STRUCT** head)
{
    if (*head != NULL) {
        while (*head != NULL) {
            NODE_STRUCT* tempNext = (*head)->next;
            DeleteNode(*head);
            *head = tempNext;
        }
    }
}

void AddFirst(NODE_STRUCT** head, OBJECT_TYPE* objectAdd)
{
    if (*head != NULL) {
        // dodaj do pierwszego na poczatek
        if ((*head)->use >= SIZE) {
            NODE_STRUCT* node = NewNode();
            node->next = *head;
            *head = node;
        }
    } else {
        NODE_STRUCT* node = NewNode();
        node->next = NULL;
        *head = node;
    }

    for (BYTE i = (*head)->use; i > 0; i--) {
        *((*head)->object + i) = *((*head)->object + i - 1);
    }
    *((*head)->object) = *objectAdd;
    (*head)->use++;
}

void AddLast(NODE_STRUCT** head, OBJECT_TYPE* objectAdd)
{
    if (*head != NULL) {
        NODE_STRUCT* temp = *head;
        // add node if no room for object
        if (temp->use >= SIZE) {
            // go| to the last node
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = NewNode();
            temp = temp->next;
        }
        // else just add object
        *(temp->object + temp->use) = *objectAdd;
        temp->use++;
    } else {
        // add object
        *head = NewNode();
        *((*head)->object) = *objectAdd;
        (*head)->use++;
    }
}

void GetFirst(NODE_STRUCT* node, NODE_STRUCT** head, BYTE* byte1)
{
}

void GetPrev(NODE_STRUCT* node1, NODE_STRUCT* node2, BYTE, NODE_STRUCT**, BYTE* byte1)
{
}

void GetNext(NODE_STRUCT* node1, NODE_STRUCT* node2, BYTE byte2, NODE_STRUCT**, BYTE* byte1)
{
}

void GetLast(NODE_STRUCT* node2, NODE_STRUCT** node1, BYTE* byte1)
{
}

void InsertPrev(NODE_STRUCT** node1, NODE_STRUCT* node2, BYTE byte1, OBJECT_TYPE*)
{
}

void InsertNext(NODE_STRUCT* node1, NODE_STRUCT* node2, BYTE byte1, OBJECT_TYPE*)
{
}

void RemoveFirst(NODE_STRUCT** node1)
{
}

void RemovePrev(NODE_STRUCT** node1, NODE_STRUCT* node22, BYTE byte1)
{
}

void RemoveCurrent(NODE_STRUCT** node1, NODE_STRUCT* node2, BYTE byte1)
{
}

void RemoveNext(NODE_STRUCT* node1, NODE_STRUCT* node2, BYTE byte1)
{ 
}

void RemoveLast(NODE_STRUCT** node1)
{
}

void Find(NODE_STRUCT* node1, OBJECT_TYPE*, NODE_STRUCT** node2, BYTE* byte1)
{
}

void Compress(NODE_STRUCT* node1)
{
}

void Reverse(NODE_STRUCT* node1)
{
}