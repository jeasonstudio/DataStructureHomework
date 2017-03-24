/**
 * Auther: Fengyi Wang
 */


#include "stdio.h"

int main(void) {
  int tag[17];
  printf("请输入身份证前17位(空格隔开，回车结束)：\n");

  for (int i = 0; i < 17; i++) {
    scanf("%d", &tag[i]);
  }
  int xs[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
  int sum = 0;

  for (int i = 0; i < 17; i++) {
    sum = sum + (xs[i] * tag[i]);
  }
  char resArr[10] = {'1','0','X','9','8','7','6','5','4','3','2'};
  int x = sum % 11;
  printf("The Result is %c\n", resArr[x]);
  printf("Your ID NUM is: ");
  for (int i = 0; i < 17; i++) {
    printf("%d", tag[i]);
  }
    printf("%c\n", resArr[x]);    
}