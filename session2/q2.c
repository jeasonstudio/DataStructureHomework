#include "q1.c"

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

    printf("A jiao B = ");
    printLinkedLine(LA_Intersection_LB(A, B));
}