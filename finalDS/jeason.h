#include <malloc/malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int nodeType;
// definded node & link pointer
typedef struct node {
  int id;
  nodeType num;
  struct node *next;
} linkNode, *link;