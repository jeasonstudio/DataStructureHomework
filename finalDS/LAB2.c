#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 20

// 定义栈
typedef struct {
  char data[MAXSIZE];
  int top;
} sqstack, *sqslink;

typedef struct {
  float data[MAXSIZE];
  int top;
} sqstack_float, *sqslink_float;

int EmptyStack(sqslink s) {
  if (s->top < 0)
    return 1;  //栈空返回1
  else
    return 0;  //栈非空返回0
}

int Push(sqslink s, char x) {
  if (s->top >= MAXSIZE - 1) return -1;  //栈满溢出
  s->top++;
  s->data[s->top] = x;
  return 0;  //成功
}

int Pop(sqslink s) {
  if (EmptyStack(s)) return -1;  //栈空，返回-1
  s->top--;
  return s->data[s->top + 1];
}

void ClearStack(sqslink s) { s->top = -1; }

int GetTop(sqslink s) {
  if (EmptyStack(s)) return -1;  //栈空，返回-1
  return s->data[s->top];
}

int EmptyStack_float(sqslink_float s) {
  if (s->top < 0)
    return 1;  //栈空返回1
  else
    return 0;  //栈非空返回0
}

float Push_float(sqslink_float s, float x) {
  if (s->top >= MAXSIZE - 1) return -1;  //栈满溢出
  s->top++;
  s->data[s->top] = x;
  return 0;  //成功
}

float Pop_float(sqslink_float s) {
  if (EmptyStack_float(s)) return -1;  //栈空，返回-1
  s->top--;
  return s->data[s->top + 1];
}

void ClearStack_float(sqslink_float s) { s->top = -1; }

float GetTop_float(sqslink_float s) {
  if (EmptyStack_float(s)) return -1;  //栈空，返回-1
  return s->data[s->top];
}

int Precede(char x, char y) {
  switch (x) {
    case '+':
    case '-':
      x = 1;
      break;
    case '*':
    case '/':
      x = 2;
      break;
  }
  switch (y) {
    case '+':
    case '-':
      y = 1;
      break;
    case '*':
    case '/':
      y = 2;
      break;
  }
  return x - y;
}

void ReadFile(char *E) {
  char path[50];
  int i = 0;
  for (i = 5; E[i] != '#'; i++) {
    if (E[i] == '\n') continue;
    path[i - 5] = E[i];
  }
  path[i - 5] = '\0';
  FILE *fp = fopen(path, "r");
  if (!fp) {
    printf("File Path Error!\n");
    strcpy(E, "error");
    return;
  }
  fscanf(fp, "%s", E);
  printf("Expression:   %s\n", E);
  fclose(fp);
}

void Mid_post(char *E, char *B) {
  // 建栈
  sqslink S = (sqslink)malloc(sizeof(sqstack));
  ClearStack(S);

  int currentE = 0;
  int currentB = 0;
  char x, y;
  int flag = 0;

  while (E[currentE] != '#') {
    switch (E[currentE]) {
      case ' ':
        flag = 1;
        break;
      case '+':
      case '-':
      case '*':
      case '/':
        flag = 1;
        while (1) {
          if (EmptyStack(S)) break;
          y = GetTop(S);
          if (y == '(') break;
          if (Precede(E[currentE], y) >= 0) break;
          B[currentB] = y;
          currentB += 1;
          Pop(S);
        }
        Push(S, E[currentE]);
        break;
      // 进栈
      case '(':
        flag = 1;
        Push(S, '(');
        break;
      case ')':
        flag = 1;
        while (1) {
          if (EmptyStack(S)) break;
          y = GetTop(S);
          if (y == '(') {
            Pop(S);
            break;
          }
          B[currentB] = y;
          currentB += 1;
          Pop(S);
        }
        break;
      // 直接输出
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '.':
        if (flag == 1) {
          B[currentB] = ' ';
          currentB += 1;
        }
        flag = 0;
        B[currentB] = E[currentE];
        currentB += 1;
        break;
      default:
        printf("Illegal Expression!\n");
        strcpy(B, "input");
        return;
    }
    currentE += 1;
  }
  while (1) {
    if (EmptyStack(S)) break;
    y = GetTop(S);
    B[currentB] = y;
    currentB += 1;
    Pop(S);
  }
  B[currentB] = E[currentE];
  B[currentB + 1] = '\0';
  free(S);
}

float Postcount(char *B) {
  // 建栈
  sqslink_float S = (sqslink_float)malloc(sizeof(sqstack_float));
  ClearStack_float(S);

  int currentB = 0;
  float num = 0;
  int flag = 0, i = 0;
  float temp, a, b;

  while (B[currentB] != '#') {
    switch (B[currentB]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
        if (flag == 0) {
          num = num * 10;
          num += B[currentB] - '0';
        } else {
          i++;
          temp = (B[currentB] - '0');
          for (int j = 0; j < i; j++) temp = temp / 10;
          num += temp;
        }
        break;
      case '.':
        flag = 1;
        break;
      case '+':
        if (num != 0) {
          a = num;
          flag = 0;
          num = 0;
          i = 0;
        } else
          a = Pop_float(S);
        b = Pop_float(S);
        Push_float(S, b + a);
        break;
      case '-':
        if (num != 0) {
          a = num;
          flag = 0;
          num = 0;
          i = 0;
        } else
          a = Pop_float(S);
        b = Pop_float(S);
        Push_float(S, b - a);
        break;
      case '*':
        if (num != 0) {
          a = num;
          flag = 0;
          num = 0;
          i = 0;
        } else
          a = Pop_float(S);
        b = Pop_float(S);
        Push_float(S, b * a);
        break;
      case '/':
        if (num != 0) {
          a = num;
          flag = 0;
          num = 0;
          i = 0;
        } else
          a = Pop_float(S);
        b = Pop_float(S);
        Push_float(S, b / a);
        break;
      case ' ':
        if (num != 0) {
          Push_float(S, num);
          flag = 0;
          num = 0;
          i = 0;
        }
        break;
      default:
        break;
    }
    currentB += 1;
  }
  temp = GetTop_float(S);
  free(S);
  return temp;
}

void main() {
  char expression[400], Bexpression[400];
  char c;
  int i = 0, j = 0;

  while (1) {
    i = 0;
    j = 0;

    // 输入
    printf("--> ");
    c = getchar();
    while (c != '#') {
      expression[j] = c;
      j++;
      c = getchar();
    }
    getchar();
    expression[j] = '#';
    expression[j + 1] = '\0';
    if (strcmp(expression, "exit#") == 0) {
      exit(0);
    } else if (expression[0] == 'r' && expression[1] == 'e' &&
               expression[2] == 'a' && expression[3] == 'd') {
      ReadFile(expression);
    } else if (strcmp(expression, "clear#") == 0) {
      system("cls");
      continue;
    }

    // 中序->后序
    Mid_post(expression, Bexpression);

    // 转换失败
    if (strcmp(Bexpression, "input") == 0) {
      continue;
    }

    // 输出表达式
    printf("Expression:   ");
    while (Bexpression[i] != '\0') {
      if (Bexpression[i] != ' ') printf("%c", Bexpression[i]);
      i++;
    }

    // 计算表达式
    printf("\n           =  %-f\n", Postcount(Bexpression));
  }
  system("pause");
}
