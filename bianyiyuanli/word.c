#include <stdio.h>
#include <string.h>

// tests
// begin x:=9; if x>9 then x:=2*x+1/3; end #

char *rwtab[6] = {"begin", "if", "then", "while", "do", "end"};
char prog[80], token[8], ch;
int syn, p = 0, m, n, sum;

// parse words in prog list
void parser();
void cleanToken();
void switchSyn();

// main func for word parser
int main(int argc, char const *argv[]) {
  printf("\n Please input a string(end with '#'):\n");
  do {
    p += 1;
    scanf("%c", &prog[p]);
  } while (prog[p] != '#');

  // restore index
  p = 0;
  printf("\n");

  do {
    parser();
    switch (syn) {
      case 11:
        printf("(%6d, %-3d)\n", sum, syn);
        break;
      case -1:
        printf("You have input a wrong string\n");
        // _Exit(0);
        break;
      default:
        printf("(%6s, %-3d)\n", token, syn);
        break;
    }
  } while (syn != 0);
  return 0;
}

void parser() {
  cleanToken();
  sum = 0;
  m = 0;
  ch = prog[p++];
  while ((ch == ' ') || (ch == '\n') || (ch == '\0')) ch = prog[p++];
  if (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A'))) {
    while (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A')) ||
           ((ch >= '0') && (ch <= '9'))) {
      token[m++] = ch;
      ch = prog[p++];
    }
    p--;
    syn = 10;
    for (n = 0; n < 6; n++) {
      if (strcmp(token, rwtab[n]) == 0) {
        syn = n + 1;
        break;
      }
    }
  } else if ((ch >= '0') && (ch <= '9')) {
    while ((ch >= '0') && (ch <= '9')) {
      sum = sum * 10 + ch - '0';
      ch = prog[p++];
    }
    p--;
    syn = 11;
  } else {
    switchSyn(ch);
  }
  token[m++] = '\0';
}

void cleanToken() {
  for (m = 0; m < 8; m++) token[m++] = '\0';
}

void switchSyn() {
  switch (ch) {
    case '<':
      token[m++] = ch;
      ch = prog[p++];
      if (ch == '=') {
        syn = 22;
        token[m++] = ch;
      } else {
        syn = 20;

        p--;
      }
      break;
    case '>':
      token[m++] = ch;
      ch = prog[p++];
      if (ch == '=') {
        syn = 24;
        token[m++] = ch;
      } else {
        syn = 23;
        p--;
      }
      break;
    case '+':
      token[m++] = ch;
      ch = prog[p++];
      if (ch == '+') {
        syn = 17;
        token[m++] = ch;
      } else {
        syn = 13;
        p--;
      }
      break;
    case '-':
      token[m++] = ch;
      ch = prog[p++];
      if (ch == '-') {
        syn = 29;
        token[m++] = ch;
      } else {
        syn = 14;
        p--;
      }
      break;
    case '!':
      ch = prog[p++];
      if (ch == '=') {
        syn = 21;
        token[m++] = ch;
      } else

      {
        syn = 31;
        p--;
      }
      break;
    case '=':
      token[m++] = ch;
      ch = prog[p++];
      if (ch == '=') {
        syn = 25;
        token[m++] = ch;
      } else {
        syn = 18;
        p--;
      }
      break;
    case '*':
      syn = 15;
      token[m++] = ch;
      break;
    case '/':
      syn = 16;
      token[m++] = ch;
      break;
    case '(':
      syn = 27;
      token[m++] = ch;
      break;
    case ')':
      syn = 28;
      token[m++] = ch;
      break;
    case '{':
      syn = 5;
      token[m++] = ch;
      break;
    case '}':
      syn = 6;
      token[m++] = ch;
      break;
    case ';':
      syn = 26;
      token[m++] = ch;
      break;
    case '\"':
      syn = 30;
      token[m++] = ch;
      break;
    case '#':
      syn = 0;
      token[m++] = ch;
      break;
    case ':':
      syn = 17;
      token[m++] = ch;
      break;
    default:
      syn = -1;
      break;
  }
}
