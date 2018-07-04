/**
 * 一个递归下降分析程序，实现对词法分析程序所提供的单词序列的语法检查和结构分析
 * 
 * Author: Jeason
 * Date: Wed, Jul 4 2018
 */

#include "stdio.h"
#include "string.h"

// clang -g -o cent.c.out cent.c && ./cent.c.out

// tests
// success
// begin a:=9; x:=2*3; b:=a+x end #
// fail
// x:=a+b*c end #

char prog[100], token[8], ch;
char *rwtab[6] = {"begin", "if", "then", "while", "do", "end"};
int syn, p, m, n, sum, kk;

// func list
void factor();
void expression();
void yucu();
void term();
void statement();
void lrparser();
void scaner();

int main(int argc, char const *argv[]) {
  p = kk = 0;
  printf("\nplease input a string (end with '#'): \n");
  do {
    scanf("%c", &ch);
    prog[p++] = ch;
  } while (ch != '#');
  p = 0;
  scaner();
  lrparser();
  // getch();
  return 0;
}

void lrparser() {
  if (syn == 1) {
    scaner();
    yucu();
    if (syn == 6) {
      scaner();
      if ((syn == 0) && (kk == 0)) printf("success!\n");
    } else {
      if (kk != 1) printf("the string haven't got a 'end'!\n");
      kk = 1;
    }
  } else {
    printf("haven't got a 'begin'!\n");
    kk = 1;
  }
}

void yucu() {
  statement();
  while (syn == 26) {
    scaner();
    if (syn != 6) statement();
  }
}

void statement() {
  if (syn == 10) {
    scaner();
    if (syn == 18) {
      scaner();
      expression();
      /*读下一个单词符号*/ /*读下一个单词符号*/
      /*调用函数 statement();*/
    } else {
      printf("the sing ':=' is wrong!\n");
      kk = 1;
    }
  } else {
    printf("wrong sentence!\n");
    kk = 1;
  }
}

void expression() {
  term();
  while ((syn == 13) || (syn == 14)) {
    scaner();
    term();
  }
}

void term() {
  factor();
  /*读下一个单词符号*/ /*调用函数 term();*/
  while ((syn == 15) || (syn == 16)) {
    scaner();
    factor();
  }
}

void factor() {
  if ((syn == 10) || (syn == 11))
    scaner();
  else if (syn == 27) {
    scaner();
    expression();
    if (syn == 28)
      scaner();
    else {
      printf("the error on '('\n");
      kk = 1;
    }
  } else {
    printf("the expression error!\n");
    kk = 1;
  }
}

void scaner() {
  sum = 0;
  for (m = 0; m < 8; m++) token[m++] = '\0';
  m = 0;
  ch = prog[p++];
  while (ch == ' ') ch = prog[p++];
  if (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A'))) {
    while (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A')) ||
           ((ch >= '0') && (ch <= '9'))) {
      token[m++] = ch;
      ch = prog[p++];
    }
    p--;
    syn = 10;
    token[m++] = '\0';
    for (n = 0; n < 6; n++)
      if (strcmp(token, rwtab[n]) == 0) {
        syn = n + 1;
        break;
      }
  } else if ((ch >= '0') && (ch <= '9')) {
    while ((ch >= '0') && (ch <= '9')) {
      sum = sum * 10 + ch - '0';
      ch = prog[p++];
    }
    p--;
    syn = 11;
  } else
    switch (ch) {
      case '<':
        m = 0;
        ch = prog[p++];
        if (ch == '>') {
          syn = 21;
        } else if (ch == '=') {
          syn = 22;
        } else {
          syn = 20;
          p--;
        }
        break;
      case '>':
        m = 0;
        ch = prog[p++];
        if (ch == '=') {
          syn = 24;
        } else {
          syn = 23;
          p--;
        }
        break;
      case ':':
        m = 0;
        ch = prog[p++];
        if (ch == '=') {
          syn = 18;
        } else {
          syn = 17;
          p--;
        }
        break;
      case '+':
        syn = 13;
        break;
      case '-':
        syn = 14;
        break;
      case '*':
        syn = 15;
        break;
      case '/':
        syn = 16;
        break;
      case '(':
        syn = 27;
        break;
      case ')':
        syn = 28;
        break;
      case '=':
        syn = 25;
        break;
      case ';':
        syn = 26;
        break;
      case '#':
        syn = 0;
        break;
      default:
        syn = -1;
        break;
    }
}
