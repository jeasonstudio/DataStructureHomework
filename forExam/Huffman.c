#include <stdio.h>
#include <stdlib.h>

#define LEN 5

typedef struct node {
  int data;
  struct node *left, *right;
} treeNode, *tree;

treeNode *createTree(treeNode *ns, int len) {
  for (int j = 0; j < len; j++) {
    *(&ns + j) = (tree)malloc(sizeof(treeNode));
    *(&ns + j)->data = j;
    *(&ns + j)->left = NULL;
    *(&ns + j)->right = NULL;

  }
  for (int i = 0; i < len; i++) {
    if ((2 * i + 1) <= len) {
      (&ns + i)->left = *(&ns + 2 * i + 1);
      // printf("s");
    }
    // else {
    //   (&ns + i) -> left = NULL;
    // }
    // if ((2 * i + 2) <= len) {
    //   *(&ns + i)->right = *(&ns + 2 * i + 2);
    // } else {
    //   *(&ns + i)->right = NULL;
    // }
  }

  return ns;
}

int main(int argc, char const *argv[]) {
  int a = 7;
  treeNode nodes[LEN] = {};

  treeNode *head = createTree(nodes, LEN);
  return 0;
}
