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

// function A - B
link ASubB(link A, link B)
{
    link fromA, fromB, r;
    fromA = A;
    r = A;
    fromB = B->next;

    // Search the same part between A & B
    while (fromA)
    {
        while (fromB)
        {
            // Delete from A
            if (fromA->next->num == fromB->num)
            {
                r = fromA->next;
                fromA->next = r->next;
                free(r);
                break;
            }
            else
            {
                fromB = fromB->next;
            }
        }
        fromB = B->next;
        if (fromA->next)
            fromA = fromA->next;
        else
        {
            fromA->next = NULL;
            break;
        }
    }

    return fromA;
}

// 函数：A交B
link LA_Intersection_LB(link A, link B)
{
    link C, p, q, r, s;
    p = A->next;
    q = B->next;

    // 新建链表C
    C = (link)malloc(sizeof(linkNode));
    C->next = NULL;
    r = C;

    // 寻找AB相同的部分
    while (p)
    {
        while (q)
        {
            // 找到相同部分添加到C中
            if (p->num == q->num)
            {
                // 检查是否以及添加
                link temp;
                temp = C->next;
                while (temp && temp->num != p->num)
                {
                    temp = temp->next;
                }
                if (temp != NULL)
                {
                    break;
                }
                else
                {
                    // 添加到C中
                    s = (link)malloc(sizeof(linkNode));
                    r->next = s;
                    s->num = p->num;
                    s->next = NULL;
                    r = s;
                    break;
                }
            }
            else
            {
                q = q->next;
            }
        }
        q = B->next;
        p = p->next;
    }
    r->next = NULL;
    return C;
}

