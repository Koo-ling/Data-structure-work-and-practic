# include <malloc.h>
# include <stdlib.h>
#include<iostream>
using namespace std;
# define max 80
typedef struct
{
    int key;
    char data;
}ElemType;     //定义结点类型

typedef struct          //线性探测法  数据结构
{
    ElemType elems[max];
    int len;
}HashTable;      //定义散列表类型

int stored[max];  //标志数组

typedef struct ElemNode {   //拉链法时采用的存储结构
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
    int i;
    HashTable ht;
    ht.len = n;
    for (i = 0; i < n; i++)
        stored[i] = 0;
    return ht;
}

int Hash(HashTable ht, int k)
{
    return k % ht.len;
}

HashTable insert(HashTable ht, int x)   //ht:散列表   ele:插入结点   线性探测法解决冲突
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
        else 
            cout<<"error!"<<endl;
    }
    return ht;
}

void InitHashTable(hashtable ht2, int n) {  //拉链法的初始化哈希表
    int i;
    ht2->len = n;
    for (i = 0; i < max; i++)
        ht2[i].first = NULL;
}

int hash2(hashtable ht2, int x) {
    return x % ht2->len;
}

void Insert(hashtable ht2, int x) {
    int i; ElemNode* p;
    i = hash2(ht2, x);
    p = (ElemNode*)malloc(sizeof(ElemNode));
    p->key = x;
    p->next = ht2[i].first;
    ht2[i].first = p;
}


void display1(HashTable ht) {
    int i;
    for (i = 0; i < ht.len; i++)
        cout << i << "   ";
    printf("\n");
    for (i = 0; i < ht.len; i++)
        if (stored[i] == 1)
        
                cout << ht.elems[i].key <<"  ";
        else cout <<  "  ";
    cout << endl;
}

void display2(hashtable ht2) {
    int i; ElemNode* p;
    for (i = 0; i < ht2->len; i++) {
        p = ht2[i].first;
        if (p != NULL) {
           
            cout << i << " ";
            while (p != NULL)
            {
                cout << p->key << " ";
                p = p->next;
            }
            cout << endl;
        }
        else
            cout << i << endl;
    }
}


void main()
{
    HashTable ht; hashtable ht2; ElemNode* p;
    int i, j, n, x, t;
    p = (ElemNode*)malloc(sizeof(ElemNode));
    cout<<"请输入散列表的长度：";
    cin >> n;
    InitHashTable(ht2, n);
    ht = initHashTable(n);
    cout << "请输入数据，不超过"<<n<<"个，以负数结束：";
    cin >> x;
    while (x >= 0)
    {
        ht = insert(ht, x);
        Insert(ht2, x); 
        cin>>x;
    }
        cout << "线性探测法建立：                            \n";
        display1(ht);        
        cout << "拉链法建立：                            \n";
        display2(ht2);
           

        return;
        
    
}

