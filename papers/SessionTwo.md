### 第二章作业：

> Front: jeason.h

```c
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
```

> Question1: Question1.c

```c
/**
  * Auther: Jeason
  * CreateTime: 3.7
  * FileName: Question1.c
  * Description: La - Lb & La ∩ Lb
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

// function A - B
link ASubB(link A, link B) {
  link fromA, fromB, r;
  fromA = A;
  r = A;
  fromB = B->next;

  // Search the same part between A & B
  while (fromA) {
    while (fromB) {
      // Delete from A
      if (fromA->next->num == fromB->num) {
        r = fromA->next;
        fromA->next = r->next;
        free(r);
        break;
      } else {
        fromB = fromB->next;
      }
    }
    fromB = B->next;
    if (fromA->next)
      fromA = fromA->next;
    else {
      fromA->next = NULL;
      break;
    }
  }

  return fromA;
}

// 函数：A交B
link LA_Intersection_LB(link A, link B) {
  link C, p, q, r, s;
  p = A->next;
  q = B->next;

  // 新建链表C
  C = (link)malloc(sizeof(linkNode));
  C->next = NULL;
  r = C;

  // 寻找AB相同的部分
  while (p) {
    while (q) {
      // 找到相同部分添加到C中
      if (p->num == q->num) {
        // 检查是否以及添加
        link temp;
        temp = C->next;
        while (temp && temp->num != p->num) {
          temp = temp->next;
        }
        if (temp != NULL) {
          break;
        } else {
          // 添加到C中
          s = (link)malloc(sizeof(linkNode));
          r->next = s;
          s->num = p->num;
          s->next = NULL;
          r = s;
          break;
        }
      } else {
        q = q->next;
      }
    }
    q = B->next;
    p = p->next;
  }
  r->next = NULL;
  return C;
}

// function main
int main(void) {
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
```

> Question2: Question2.c

```c
/**
  * Auther: Jeason
  * CreateTime: 3.8
  * FileName: Question2.c
  * Description: Sequence table of Student
  */

#include "../front/jeason.h"

// 根据学号删除节点
StuDentNode *deleteTable(StuDentNode *stutab, char *theSno, int len) {
  for (int i = 0; i < len; i++) {
    if (strcmp(stutab[i].Sno, theSno) == 0) {
      for (int j = i; j < len - i; j++) {
        stutab[j] = stutab[j + 1];
      }
      break;
    }
  }
  return stutab;
}

// 合适的位置插入数据
StuDentNode *insertTable(StuDentNode *stutab, StuDentNode x, int len) {
  for (int i = 0; i < len; i++) {
    // StuDentNode thisNode = stutab[i];
    if (stutab[i].No > x.No) {
      for (int j = i; j < len - i; j++) {
        StuDentNode item = stutab[j];
        stutab[j] = x;
        x = item;
      }
      break;
    }
  }
  return stutab;
}

// function main
int main(void) {
  StuDentNode stuTable[20] = {{1, "J0001", "Jeason1", 1, "J1501"},
                              {2, "J0002", "Jeason2", 1, "J1501"},
                              {3, "J0003", "Jeason3", 1, "J1501"},
                              {4, "J0004", "Jeason4", 1, "J1501"},
                              // {5, "J0005", "Jeason5", 1, "J1501"},
                              {6, "J0006", "Jeason6", 1, "J1501"},
                              {7, "J0007", "Jeason7", 1, "J1501"},
                              {8, "J0008", "Jeason8", 1, "J1501"},
                              {9, "J0009", "Jeason9", 1, "J1501"}};

  StuDentNode newGuy = {5, "J0005", "Jeason5", 1, "J1501"};

  insertTable(stuTable, newGuy, 20);

  printf("Finished!\n");

  deleteTable(stuTable, "J0006", 20);

  printf("Finished!\n");
}
```

> Question3: Question3.c

```c
/**
  * Auther: Jeason
  * CreateTime: 3.10
  * FileName: Question3.c
  * Description: Search node
  */

#include "../front/jeason.h"

// print the linked line
link createLinkedLineNum(int len) {
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
  link resNode = createLinkedLineNum(10);
  search(resNode, resNode, 5);

  printf("Search End!");
}
```

> Question4: Question4.c

```c
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
```