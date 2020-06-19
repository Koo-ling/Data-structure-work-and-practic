# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# define max 100
typedef struct
{
    int key;
    char data;
}ElemType;     //定义结点类型

typedef struct
{
    ElemType elems[max];
    int len;
}HashTable;      //定义散列表类型

int stored[max];  //标志数组

typedef struct ElemNode {
    int key;
    ElemType data;
    struct ElemNode* next;
}ElemNode;

typedef struct {
    ElemNode* first;
    int len;
}ElemHeader, hashtable[max];


HashTable initHashTable(int n)     //ht:散列表   n:散列表长度
{
    int i; HashTable ht;
    ht.len = n;
    for (i = 0; i < n; i++)
        stored[i] = 0;
    return ht;
}

int Hash(HashTable ht, int k)
{
    return k % ht.len;
}

HashTable insert(HashTable ht, int x)   //ht:散列表   ele:插入结点
{
    int i, add;
    i = Hash(ht, x);
    if (stored[i] == 0)
    {
        ht.elems[i].key = x;
        stored[i] = 1;
    }
    else {
        add = i; i = (i + 1) % ht.len;
        while (i != add && stored[i] == 1)  i = (i + 1) % ht.len;
        if (stored[i] == 0)
        {
            ht.elems[i].key = x; stored[i] = 1;
        }
        else printf("error occurred!");
    }
    return ht;
}

int search(HashTable ht, int x)  //ht:散列表  ele:待查找结点
{
    int i, add;
    i = Hash(ht, x);
    if (stored[i] == 1 && ht.elems[i].key == x)  return i;
    else
    {
        add = i; i = (i + 1) % ht.len;
        while (i != add && stored[i] == 1 && ht.elems[i].key != x)
            i = (i + 1) % ht.len;
        if (ht.elems[i].key == x) return i;
        else { printf("can not find!"); return -1; }
    }
}

void delet(HashTable ht, int x)   //ht:散列表  ele:待删除结点
{
    int i;
    i = search(ht, x);
    if (i != -1) stored[i] = 0;
    else printf("error occurred!");
}

void InitHashTable(hashtable ht2, int n) {
    int i;
    ht2->len = n;
    for (i = 0; i < max; i++)
        ht2[i].first = NULL;
}

int hash(hashtable ht2, int x) {
    return x % ht2->len;
}

void Insert(hashtable ht2, int x) {
    int i; ElemNode* p;
    i = hash(ht2, x);
    p = (ElemNode*)malloc(sizeof(ElemNode));
    p->key = x;
    p->next = ht2[i].first;
    ht2[i].first = p;
}

int Search(hashtable ht2, int x) {
    int i; ElemNode* p;
    i = hash(ht2, x);
    p = ht2[i].first;
    while (p != NULL && p->key != x)
        p = p->next;
    if (p != NULL) return 1;
    else return 0;
}

void display1(HashTable ht) {
    int i;
    for (i = 0; i < ht.len; i++)
        printf("%3d", i);
    printf("\n");
    for (i = 0; i < ht.len; i++)
        if (stored[i] == 1)
            printf("%3d", ht.elems[i].key);
        else printf("   ");
    printf("\n");
}

void display2(hashtable ht2) {
    int i; ElemNode* p;
    for (i = 0; i < ht2->len; i++) {
        p = ht2[i].first;
        if (p != NULL) {
            printf("%3d.", i);
            while (p != NULL)
            {
                printf("%3d", p->key); p = p->next;
            }printf("\n");
        }
        else printf("%3d.\n", i);
    }
}


void main()
{
    HashTable ht; hashtable ht2; ElemNode* p;
    int i, j, n, x, t;
    p = (ElemNode*)malloc(sizeof(ElemNode));
    printf("请输入散列表的长度：");
    scanf("%d", &n);
    InitHashTable(ht2, n);
    ht = initHashTable(n);
    printf("请输入数据，不超过%d个，以负数结束：", n);
    scanf("%d", &x);
    while (x >= 0)
    {
        ht = insert(ht, x); Insert(ht2, x); scanf("%d", &x);
    }
    printf("   ====================散列表==================\n");
    printf("   --------------------------------------------\n");
    printf("       1:线性探测法                            \n");
    printf("       2:拉链法                                \n");
    printf("       3:退出                                  \n");
    printf("   --------------------------------------------\n");

    while (1) {
        printf("请选择:");
        scanf("%d", &t);
        switch (t)
        {
        case 1:printf("散列表中的结点如下：\n");
            display1(ht);
            printf("请输入要查找的节点：");
            scanf("%d", &x);
            i = search(ht, x);
            if (i != -1)  printf("该节点存放在地址为%d的散列表中.", i);
            else printf("该散列表中没有该值！\n");
            printf("\n");
            printf("输入要删除的结点：");
            scanf("%d", &x);
            printf("删除key为%d的结点…\n", x); delet(ht, x);
            printf("删除后，散列表中的结点如下：\n");
            display1(ht);
            printf("请输入要插入的结点：");
            scanf("%d", &x);
            printf("插入key为%d的结点…\n", x);
            ht = insert(ht, x);
            printf("插入后，散列表中的结点如下：\n");
            display1(ht);
            break;
        case 2:printf("散列表中的结点如下：\n");
            display2(ht2);
            printf("请输入要查找的节点：");
            scanf("%d", &x);
            j = Search(ht2, x);
            if (j == 1) printf("结点找到！\n");
            else printf("结点没找到！\n");
            printf("请输入要插入的结点：");
            scanf("%d", &x);
            printf("插入key为%d的结点…\n", x);
            ht = insert(ht, x); Insert(ht2, x);
            printf("插入后，散列表中的结点如下：\n");
            display2(ht2);
            break;

        case 3:exit(0);
        }
    }
}

