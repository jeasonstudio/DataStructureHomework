
#include <malloc/malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// q1 & q3
typedef int Item;
// definded node & link pointer
typedef struct node {
  Item num;
  struct node *next;
} linkNode, *link;

// student Node shunxu q2
struct studentNode {
  int No;
  char Sno[20];
  char Name[20];
  int sex;
  char Class[20];
};

typedef struct studentNode StuDentNode;