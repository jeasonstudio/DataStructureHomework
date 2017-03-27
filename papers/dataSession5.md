## 数据结构第五章作业
#### 赵吉彤 41524122 计1501

### 题目一

```cpp
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
  // 十字链表见图
}
```

### 十字链表

![alt](file:///Users/Jeason/Documents/ToDos/DataStructureHomework/session5/shizi.png)

### 题目二

> 广义表表示： H=(A,B,b2)=((a1,D,a3),(b1,b2,b3),b2)=((a1,(d1,d2,d3),a3),(b1,b2,b3),b2)

#### 单链结构

![alt](file:///Users/Jeason/Documents/ToDos/DataStructureHomework/session5/dan.png)

#### 双链结构

![alt](file:///Users/Jeason/Documents/ToDos/DataStructureHomework/session5/shuang.png)
