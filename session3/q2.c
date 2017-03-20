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
  printf("%d", 5 / 2);
  sqslink newStack = (sqslink)malloc(sizeof(sqstack));
  int DATA[maxsize], n;
  printf("Please input arr length\n");
  scanf("%d", &n);
  printf("Please input int arr\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", (DATA + i));
  }
  for (int j = 0; j < n; j++) {
    if ((n % 2 == 0 && j <= n / 2) || (n % 2 != 0 && j <= n / 2)) {
      Push(newStack, *(DATA + j));
    } else if ((n % 2 == 0 && j > n / 2) || (n % 2 != 0 && j > ((n/2)+1))) {
      if (DATA[j] != Getstop(newStack)) {
        printf("Nope!!");
      }
    }
  }
  printf("Yepe!!");
}