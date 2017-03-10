#include "../front/jeason.h"

// student Node shunxu
struct studentNode {
  int No;
  char Sno[20];
  char Name[20];
  int sex;
  char Class[20];
};

typedef struct studentNode StuDentNode;

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