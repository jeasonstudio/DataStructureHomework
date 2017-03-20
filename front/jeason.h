
#include <malloc/malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxsize 10

// q1 & q3
typedef int Item;
// definded node & link pointer
typedef struct node {
  Item num;
  struct node *next;
} linkNode, *link;

// 定义一个栈结构
typedef struct stack {
  int num[maxsize];
  int top;
} sqstack, *sqslink;

// student Node shunxu q2
struct studentNode {
  int No;
  char Sno[20];
  char Name[20];
  int sex;
  char Class[20];
};
typedef struct studentNode StuDentNode;