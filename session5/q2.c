#include "../front/jeason.h"

typedef struct node {
  int atom;
  union {
    char *data;
    struct node *link;
  } dtype;
  struct node *next;
} Lsnode, *Lslink;

int main(void) {}

