
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

// char[] To int[]
void getdigits(int *a, char *s) {
  int i;
  char digit;
  int len = strlen(s);

  // init Arr
  for (i = 0; i < N; ++i) *(a + i) = 0;
  for (i = 0; i < len; ++i) {
    digit = *(s + i);
    // back to first
    *(a + len - 1 - i) = digit - '0';
  }
}

// a mult b to c
void multiply(int *a, int *b, int *c) {
  int i, j;
  for (i = 0; i < 2 * N; ++i) *(c + i) = 0;

  //数组a中的每位逐位与数组b相乘，并把结果存入数组c
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j) *(c + i + j) += *(a + i) * *(b + j);
  //这里是移位、进位
  for (i = 0; i < 2 * N - 1; ++i) {
    *(c + i + 1) +=
        *(c + i) / 10;  //将十位上的数向前进位，并加上原来这个位上的数
    *(c + i) = *(c + i) % 10;  //将剩余的数存原来的位置上
  }
}

int main() {
  int a[N], b[N], c[2 * N];
  char s1[N], s2[N];
  int j = 2 * N - 1;
  int i;

  printf("Input the first number:");
  scanf("%s", s1);
  printf("/nInput the second number:");
  scanf("%s", s2);

  getdigits(a, s1);
  getdigits(b, s2);

  multiply(a, b, c);

  while (c[j] == 0) j--;
  for (i = j; i >= 0; --i) printf("%d", c[i]);
  printf("/n");
  return 0;
}