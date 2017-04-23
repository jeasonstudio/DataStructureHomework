#include "./jeason.h"

// print the linked line
link CreatList() {
  int DATA, nodeID = 1;
  scanf("%d", &DATA);
  link thisNode = (link)malloc(sizeof(linkNode));
  link resNode = thisNode;
  while (DATA != 0) {
    link nextNode = (link)malloc(sizeof(linkNode));
    thisNode->id = nodeID;
    thisNode->num = DATA;
    thisNode->next = nextNode;

    nodeID++;

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
    printf("%d:%d ", n->id, n->num);
    n = n->next;
  }
  printf("\n");
}

// find it
link AdjMax(link tag, int k) {
  link MaxLinkHeadNode = tag, MaxLinkEndNode, myHead = tag;
  int MaxNum = 0;

  while (1) {
    int thisMax = 0;
    for (int m = 0; m < k; m++) {
      if (m == 0)
        MaxLinkEndNode = MaxLinkHeadNode;
      else
        MaxLinkEndNode = MaxLinkEndNode->next;
      thisMax = thisMax + MaxLinkEndNode->num;
    }
    if (MaxLinkEndNode->next == NULL) break;
    if (thisMax > MaxNum) {
      MaxNum = thisMax;
      myHead = MaxLinkHeadNode;
    } else {
      MaxLinkHeadNode = MaxLinkHeadNode->next;
    }
  }

  return myHead;
}

// function main
int main(void) {
  int k;

  printf("Please input linked line A,type ZERO to end:\n");
  link A = CreatList();

  printf("Linked line A Your input is:\n");
  printLinkedLine(A);

  printf("Please input k:\n");
  scanf("%d", &k);

  link res = AdjMax(A, k);
  printf("The Reasult ID is: %d \nThe Result Data is: %d \n", res->id, res->num);
}