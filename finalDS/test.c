#include "./jeason.h"

int len = 0;

// print the linked line
link CreatList() {
  int DATA, nodeID = 1, mt;
  link thisNode = (link)malloc(sizeof(linkNode));
  link resNode = thisNode;
  scanf("%d", &DATA);
  while (DATA != 0 && DATA == mt) {
    link nextNode = (link)malloc(sizeof(linkNode));
    thisNode->id = nodeID;
    thisNode->num = DATA;
    mt = DATA;
    thisNode->next = nextNode;

    nodeID++;

    thisNode = nextNode;
    scanf("%d", &DATA);
  }
  thisNode->next = NULL;
  len = nodeID;
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
  printf("Please input linked line A,type ZERO to end:\n");
  link A = CreatList();

  printf("Linked line A Your input is:\n");
  printLinkedLine(A);

  printf("Please input k (0 < k < %d):\n", len);

  int k;
  scanf("%d", &k);

  while (k > len || k <= 0) {
    printf("Please input the right k (0 < k < %d):\n", len);
    scanf("%d", &k);
  }

  link res = AdjMax(A, k);
  printf("The Reasult ID is: %d \nThe Result Data is: %d \n", res->id,
         res->num);
}