/**
 * auther: Jeason
 * time: 3.7
 */

#include "../front/jeason.h"

// build & run :
// clang q1.c -o q1.o && ./q1.o

typedef int elemType;

/************************************************************************/
/*             以下是关于线性表链接存储（单链表）操作的18种算法        */

/* 1.初始化线性表，即置单链表的表头指针为空 */
/* 2.创建线性表，此函数输入负数终止读取数据*/
/* 3.打印链表，链表的遍历*/
/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
/* 5.返回单链表的长度 */
/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
/* 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行 */
/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
/* 9.把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０ */
/* 10.向单链表的表头插入一个元素 */
/* 11.向单链表的末尾添加一个元素 */
/* 12.向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０ */
/* 13.向有序单链表中插入元素x结点，使得插入后仍然有序 */
/* 14.从单链表中删除表头结点，并把该结点的值返回，若删除失败则停止程序运行 */
/* 15.从单链表中删除表尾结点并返回它的值，若删除失败则停止程序运行 */
/* 16.从单链表中删除第pos个结点并返回它的值，若删除失败则停止程序运行 */
/* 17.从单链表中删除值为x的第一个结点，若删除成功则返回1,否则返回0 */
/* 18.交换2个元素的位置 */
/* 19.将线性表进行快速排序 */

/************************************************************************/
typedef struct Node
{ /* 定义单链表结点类型 */
    elemType element;
    struct Node *next;
} Node;

/* 1.初始化线性表，即置单链表的表头指针为空 */
void initList(Node **pNode)
{
    *pNode = NULL;
    printf("initList函数执行，初始化成功\n");
}

/* 2.创建线性表，此函数输入负数终止读取数据*/
Node *creatList(Node *pHead)
{
    Node *p1;
    Node *p2;

    p1 = p2 = (Node *)malloc(sizeof(Node)); //申请新节点
    if (p1 == NULL || p2 == NULL)
    {
        printf("内存分配失败\n");
        exit(0);
    }
    memset(p1, 0, sizeof(Node));

    scanf("%d", &p1->element); //输入新节点
    p1->next = NULL;           //新节点的指针置为空
    while (p1->element > 0)    //输入的值大于0则继续，直到输入的值为负
    {
        if (pHead == NULL) //空表，接入表头
        {
            pHead = p1;
        }
        else
        {
            p2->next = p1; //非空表，接入表尾
        }
        p2 = p1;
        p1 = (Node *)malloc(sizeof(Node)); //再重申请一个节点
        if (p1 == NULL || p2 == NULL)
        {
            printf("内存分配失败\n");
            exit(0);
        }
        memset(p1, 0, sizeof(Node));
        scanf("%d", &p1->element);
        p1->next = NULL;
    }
    printf("creatList函数执行，链表创建成功\n");
    return pHead; //返回链表的头指针
}

/* 3.打印链表，链表的遍历*/
void printList(Node *pHead)
{
    if (NULL == pHead) //链表为空
    {
        printf("PrintList函数执行，链表为空\n");
    }
    else
    {
        while (NULL != pHead)
        {
            printf("%d ", pHead->element);
            pHead = pHead->next;
        }
        printf("\n");
    }
}

/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
void clearList(Node *pHead)
{
    Node *pNext; //定义一个与pHead相邻节点

    if (pHead == NULL)
    {
        printf("clearList函数执行，链表为空\n");
        return;
    }
    while (pHead->next != NULL)
    {
        pNext = pHead->next; //保存下一结点的指针
        free(pHead);
        pHead = pNext; //表头下移
    }
    printf("clearList函数执行，链表已经清除\n");
}

/* 5.返回单链表的长度 */
int sizeList(Node *pHead)
{
    int size = 0;

    while (pHead != NULL)
    {
        size++; //遍历链表size大小比链表的实际长度小1
        pHead = pHead->next;
    }
    printf("sizeList函数执行，链表长度 %d \n", size);
    return size; //链表的实际长度
}

/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
int isEmptyList(Node *pHead)
{
    if (pHead == NULL)
    {
        printf("isEmptyList函数执行，链表为空\n");
        return 1;
    }
    printf("isEmptyList函数执行，链表非空\n");

    return 0;
}

/* 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行 */
elemType getElement(Node *pHead, int pos)
{
    int i = 0;

    if (pos < 1)
    {
        printf("getElement函数执行，pos值非法\n");
        return 0;
    }
    if (pHead == NULL)
    {
        printf("getElement函数执行，链表为空\n");
        return 0;
        //exit(1);
    }
    while (pHead != NULL)
    {
        ++i;
        if (i == pos)
        {
            break;
        }
        pHead = pHead->next; //移到下一结点
    }
    if (i < pos) //链表长度不足则退出
    {
        printf("getElement函数执行，pos值超出链表长度\n");
        return 0;
    }

    return pHead->element;
}

/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
elemType *getElemAddr(Node *pHead, elemType x)
{
    if (NULL == pHead)
    {
        printf("getElemAddr函数执行，链表为空\n");
        return NULL;
    }
    if (x < 0)
    {
        printf("getElemAddr函数执行，给定值X不合法\n");
        return NULL;
    }
    while ((pHead->element != x) && (NULL != pHead->next)) //判断是否到链表末尾，以及是否存在所要找的元素
    {
        pHead = pHead->next;
    }
    if ((pHead->element != x) && (pHead != NULL))
    {
        printf("getElemAddr函数执行，在链表中未找到x值\n");
        return NULL;
    }
    if (pHead->element == x)
    {
        printf("getElemAddr函数执行，元素 %d 的地址为 0x%x\n", x, &(pHead->element));
    }

    return &(pHead->element); //返回元素的地址
}

/* 9.把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０ */
int modifyElem(Node *pNode, int pos, elemType x)
{
    Node *pHead;
    pHead = pNode;
    int i = 0;

    if (NULL == pHead)
    {
        printf("modifyElem函数执行，链表为空\n");
    }
    if (pos < 1)
    {
        printf("modifyElem函数执行，pos值非法\n");
        return 0;
    }
    while (pHead != NULL)
    {
        ++i;
        if (i == pos)
        {
            break;
        }
        pHead = pHead->next; //移到下一结点
    }
    if (i < pos) //链表长度不足则退出
    {
        printf("modifyElem函数执行，pos值超出链表长度\n");
        return 0;
    }
    pNode = pHead;
    pNode->element = x;
    printf("modifyElem函数执行\n");

    return 1;
}

/* 10.向单链表的表头插入一个元素 */
int insertHeadList(Node **pNode, elemType insertElem)
{
    Node *pInsert;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0, sizeof(Node));
    pInsert->element = insertElem;
    pInsert->next = *pNode;
    *pNode = pInsert;
    printf("insertHeadList函数执行，向表头插入元素成功\n");

    return 1;
}

/* 11.向单链表的末尾添加一个元素 */
int insertLastList(Node **pNode, elemType insertElem)
{
    Node *pInsert;
    Node *pHead;
    Node *pTmp; //定义一个临时链表用来存放第一个节点

    pHead = *pNode;
    pTmp = pHead;
    pInsert = (Node *)malloc(sizeof(Node)); //申请一个新节点
    memset(pInsert, 0, sizeof(Node));
    pInsert->element = insertElem;

    while (pHead->next != NULL)
    {
        pHead = pHead->next;
    }
    pHead->next = pInsert; //将链表末尾节点的下一结点指向新添加的节点
    *pNode = pTmp;
    printf("insertLastList函数执行，向表尾插入元素成功\n");

    return 1;
}

/* 12.向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０ */

/* 13.向有序单链表中插入元素x结点，使得插入后仍然有序 */
/* 14.从单链表中删除表头结点，并把该结点的值返回，若删除失败则停止程序运行 */
/* 15.从单链表中删除表尾结点并返回它的值，若删除失败则停止程序运行 */
/* 16.从单链表中删除第pos个结点并返回它的值，若删除失败则停止程序运行 */
/* 17.从单链表中删除值为x的第一个结点，若删除成功则返回1,否则返回0 */
/* 18.交换2个元素的位置 */
/* 19.将线性表进行快速排序 */

/******************************************************************/
int main()
{
    Node *pList = NULL;
    int length = 0;

    elemType posElem;

    initList(&pList); //链表初始化
    printList(pList); //遍历链表，打印链表

    pList = creatList(pList); //创建链表
    printList(pList);

    sizeList(pList); //链表的长度
    printList(pList);

    isEmptyList(pList); //判断链表是否为空链表

    posElem = getElement(pList, 3); //获取第三个元素，如果元素不足3个，则返回0
    printf("getElement函数执行，位置 3 中的元素为 %d\n", posElem);
    printList(pList);

    getElemAddr(pList, 5); //获得元素5的地址

    modifyElem(pList, 4, 1); //将链表中位置4上的元素修改为1
    printList(pList);

    insertHeadList(&pList, 5); //表头插入元素12
    printList(pList);

    insertLastList(&pList, 10); //表尾插入元素10
    printList(pList);

    clearList(pList); //清空链表
    system("pause");
}