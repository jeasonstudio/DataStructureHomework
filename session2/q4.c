/**
  * Auther: Jeason
  * CreateTime: 3.10
  * FileName: Question4.c
  * Description: equal La & Lb
  */

#include "../front/jeason.h"

// print the linked line
link createLinkedLine() {
  int DATA;
  scanf("%d", &DATA);
  link thisNode = (link)malloc(sizeof(linkNode));
  link resNode = thisNode;
  while (DATA > 0) {
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
void printLinkedLine(link tag) {
  link n = tag;
  while (n->next) {
    printf("%d ", n->num);
    n = n->next;
  }
  printf("\n");
}

int equal(link LA, link LB) {
  while (LA && LB) {
    if (LA->num != LB->num) return 0;
    LA = LA->next;
    LB = LB->next;
  }
  if((LA && !LB) || (LB && !LA)) return 0;
  return 1;
}

int main(void) {
  printf("Please input Linked Line A:\n");
  link LA = createLinkedLine();
  printf("Please input Linked Line B:\n");
  link LB = createLinkedLine();

  printf("The Result is : %d\n", equal(LA,LB));
}