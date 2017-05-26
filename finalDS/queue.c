#include <stdio.h>
#include <stdlib.h>

char c;
typedef struct node {
  char data;
  struct node *next;
} Qnode, *Qlink;
typedef struct { Qnode *front, *rear; } linkqueue;

void Createqueue(linkqueue *q) {
  q->front = (Qlink)malloc(sizeof(Qnode));
  q->front->next = NULL;
  q->rear = q->front;
}
int Emptyqueue(linkqueue *q) {
  if (q->front == q->rear)
    return 1;
  else
    return 0;
}
void Enqueue(linkqueue *q, char e) {
  Qlink p;
  p = (Qlink)malloc(sizeof(Qnode));
  p->data = e;
  p->next = NULL;
  q->rear->next = p;
  q->rear = p;
}
char Dequeue(linkqueue *q) {
  Qlink p;
  if (Emptyqueue(q))
    return (NULL);
  else {
    p = q->front;
    q->front = p->next;
    free(p);
    return (q->front->data);
  }
}
int main() {
  linkqueue q;
  Createqueue(&q);
  while (c = getchar(), c - '#') {
    switch (c) {
      case '0': {
        if (Emptyqueue(&q)) {
          printf("Empty queue!\n");
          break;
        }
        printf("The char deQueued is : %c\n", Dequeue(&q));
        break;
      }
      case '@': {
        if (Emptyqueue(&q)) {
          printf("Empty queue!\n");
          break;
        }
        printf("The Queue is :");
        while (!Emptyqueue(&q)) {
          printf("%c", Dequeue(&q));
        }
        printf("\n");
        break;
      }
      case '\n': {
        break;
      }
      default: { Enqueue(&q, c); }
    }
  }
  return 0;
}