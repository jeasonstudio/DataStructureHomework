#include "../front/jeason.h"

struct threeNumNode {
  int num;
  int x;
  int y;
};
typedef struct threeNumNode tnNode;

typedef struct OLNode {
  int x, y;
  int num;
  struct OLNode *right, *down;
} OLNode, *OList;



int main(void) {
  int JZ[5][5] = {{1, 0, 0, 0, 2},
                  {0, 3, 0, 0, 4},
                  {0, 0, 0, 5, 0},
                  {0, 0, 0, 6, 0},
                  {0, 0, 0, 0, 7}};
  int result[15], k = 0;

  for (int i = 0; i < 5; i++) {
    for (int j = i; j < 5; j++) {
      result[k] = JZ[i][j];
      k++;
    }
  }

  // The result is {1,0,0,0,2,3,0,0,4,0,5,0,6,0,7}
  // k = 0 + j (i == 0)
  // k = 5 + j - i (i == 1)
  // k = 9 + j - i (i == 2)
  // k = 12 + j - i (i == 3)
  // k = 14 + j - i (i == 4)
  // 此处 i,j,k 为数组下标，都+1为结果
  printf("Finished");

  tnNode table[15];
  int po = 0, zeroNum = 0, notZeroNum = 0;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (JZ[i][j] != 0) {
        table[po].num = JZ[i][j];
        table[po].x = i;
        table[po].y = j;
        po++;
        notZeroNum++;
      } else {
        zeroNum++;
      }
    }
  }
  printf("Finished threeNumNode");

  OList result = (OList)malloc(sizeof(OLNode));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
			if (JZ[i][j] != 0) {
        result->num = JZ[i][j];
        result->x = i;
        result->y = j;
      }
    }
  }
}