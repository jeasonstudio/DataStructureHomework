#include "../front/jeason.h"

int Push(sqslink s, int tag) {
  if (s->top >= maxsize - 1)
    return 0;
  else {
    s->top++;
    s->num[s->top] = tag;
    return 1;
  }
}

int Pop(sqslink s) {
  if (s->top < 0)
    return 0;
  else {
    s->top--;
    return s->num[s->top + 1];
  }
}

int Getstop(sqslink s) {
  if (s->top < 0)
    return 0;
  else {
    return s->num[s->top];
  }
}

void PrintStack(sqslink s) {
  for (int i = 0; i < maxsize; i++) {
      printf("%d ", Getstop(s));
  }
}

int main(void) {
  sqslink newStack = (sqslink)malloc(sizeof(sqstack));
  for (int i = 1; i <= 5; i++) {
    Push(newStack, i);
  }
  PrintStack(newStack);
}