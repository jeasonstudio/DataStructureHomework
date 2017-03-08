/**
 * auther: Jeason
 * time: 3.7
 */

// build & run :
// clang q1.c && ./a.out

#include "../front/jeason.h"

typedef int Item;
// definded node & link pointer
typedef struct node
{
    Item num;
    struct node *next;
} linkNode, *link;

// print the linked line
link createLinkedLine()
{
    int DATA;
    scanf("%d", &DATA);
    link thisNode = (link)malloc(sizeof(linkNode));
    link resNode = thisNode;
    while (DATA > 0)
    {
        link nextNode = (link)malloc(sizeof(linkNode));
        thisNode->num = DATA;
        thisNode->next = nextNode;

        thisNode = nextNode;
        scanf("%d", &DATA);
    }
    thisNode->next = NULL;
    return resNode;
}

// format print linked line
void printLinkedLine(link tag)
{
    link n = tag;
    while (n->next)
    {
        printf("%d ", n->num);
        n = n->next;
    }
    printf("\n");
}

// Linked Line A - B return A
link ASubB(link tagA, link tagB)
{
    link fromB = tagB;
    link fromA = tagA;
    while (fromB)
    {
        while (fromB->num && fromA)
        {
            if (fromB->num == fromA->num)
            {
                if (fromA->next && fromA->next->next)
                    fromA->next = fromA->next->next;
                else
                    fromA->next = NULL;
            }
            else
            {
                fromA = fromA->next;
            }
            fromB = fromB->next;
        }
    }

    return tagA;
}

// function main
int main(void)
{
    printf("Please input linked line A:\n");
    link A = createLinkedLine();
    printf("Please input linked line B:\n");
    link B = createLinkedLine();

    printf("Linked line A:\n");
    printLinkedLine(A);
    printf("Linked line B:\n");
    printLinkedLine(B);

    printf("A - B = ");
    printLinkedLine(ASubB(A, B));
}