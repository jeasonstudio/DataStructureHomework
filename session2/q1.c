/**
 * auther: Jeason
 * time: 3.7
 */

#include "../front/jeason.h"

// build & run :
// clang q1.c && ./a.out

typedef int Item;
typedef struct node *PNode;

// definded node
typedef struct node
{
    Item num;
    PNode next;
} Node, *SList;

// create a linked list
int createLinkList(SList *p_list, int size)
{
    PNode p = NULL;
    int i;

    *p_list = (SList)malloc(sizeof(Node));
    if (*p_list == NULL)
        return -1;
    (*p_list)->next = NULL;
    for (i = size; i > 0; i--)
    {
        p = (PNode)malloc(sizeof(Node));
        if (p == NULL)
            return -1;
        p->num = 0;
        p->next = (*p_list)->next;
        (*p_list)->next = p;
    }
    return 1;
}

int main(void)
{
    printf("Started ...\n");
    printf("Hello World.\n");
}