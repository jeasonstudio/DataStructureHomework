#include "../front/jeason.h"

// print the linked line
link createLinkedLine(int len) {
  int DATA;
  link firstNode = (link)malloc(sizeof(linkNode));
  link thisNode = (link)malloc(sizeof(linkNode));
  scanf("%d", &DATA);
  firstNode->num = DATA;
  firstNode->next = thisNode;

  for (int i = 1; i < len; i++) {
    link nextNode = (link)malloc(sizeof(linkNode));
    scanf("%d", &DATA);
    thisNode->num = DATA;
    thisNode->next = nextNode;

    thisNode = nextNode;
  }

  thisNode->next = firstNode;
  return firstNode;
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

void search(link TABLE, link start, int tag) {
  int i = 0;
  link thisNode = (link)malloc(sizeof(linkNode));
  thisNode = start;
  while (thisNode->num != tag) {
    thisNode = thisNode->next;
    i++;
  }

  printf("Search %d From Location : %d\n", tag, i);
}

int main(void) {
  link resNode = createLinkedLine(10);
  search(resNode, resNode, 5);

  printf("Search End!");
}