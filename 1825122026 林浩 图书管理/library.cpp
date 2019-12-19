#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
typedef struct AVLNode* Tree;
typedef int ElementType;
struct AVLNode
{
    int depth; //深度，这里计算每个结点的深度，通过深度的比较可得出是否平衡
    Tree parent; //该结点的父节点，方便操作
    ElementType val; //结点值   书号
    string bookname;
    string aditor;
    int xian;    //现存量
    int  total;   //总库存量
    Tree lchild;
    Tree rchild;
    AVLNode(int val = 0) //默认构造函数
    {
        parent = NULL;
        depth = 0;
        lchild = rchild = NULL;
        this->val = val;
    }
};
typedef struct bookborrow {
    int shuhao;
    string booknames;
    struct bookborrow* next;
    long int data;
}bookborrow,*zhixiang;
typedef struct borrower {
    long int borrowNumber;
    bookborrow* xia;
}borrower,*bookjie;
Tree insert_val(Tree&, Tree, Tree);
Tree remove(Tree&, ElementType);
Tree remove_val(Tree&, Tree&);
void update_depth(Tree);
Tree AVLTree(Tree&, Tree);
Tree LL_rotate(Tree);
Tree RL_rotate(Tree);
Tree RR_rotate(Tree);
Tree LR_rotate(Tree);
int  get_balance(Tree);
int  is_balance(Tree);
Tree* Find_Min(Tree&);
//向AVL树中插入val
//参数：根，插入数据value
//返回:新根结点
Tree Insert(Tree& root, ElementType val,string a,string b, int c,int d)
{
    Tree temp = NULL;
    Tree node = new AVLNode(val);
    node->bookname = a;
    node->aditor = b;
    node->xian = c;
    node->total = d;
    //插入结点
    temp = insert_val(root, node, NULL); //调用真正的插入函数  16  ，3
    if (temp)
    {
        update_depth(temp);
        root = AVLTree(root, temp);  //检查树是否该调整
    }
    else //无需插入，释放结点
        delete temp;
    return root;
}
//插入函数
//参数：根节点，待插结点，待插结点的父节点
//返回：插入结点
Tree insert_val(Tree& root, Tree node, Tree parent)   //16做爹
{
    if (root == NULL)
    {
        root = node;        //如果根节点为空，则插入的节点就为根
        node->parent = parent;    //设置当前结点的父结点，，第一个插入的双亲为空   16为3的爹
        return root;              //返回插入结点   返回3
    }
    if (node->val < root->val) //插左子树
        return insert_val(root->lchild, node, root);
    else if (node->val > root->val) //插右子树
        return insert_val(root->rchild, node, root);
    else //已存在该结点，停止插入操作，返回NULL
        return NULL;
}
//AVL树调整函数
//参数：根结点，插入结点
//返回：调整后的根结点
Tree AVLTree(Tree& root, Tree node)
{
    int balance = 0; //平衡因子
    while (node != NULL) //检查其祖先是否需要调整，更新
    {
        update_depth(node);     //更新当前结点的高度信息
        balance = is_balance(node);    //获取当前结点的平衡因子情况
        if (balance > 1 || balance < -1) //平衡因子超标
        {
            if (balance > 1) //左子树高
            {
                if (is_balance(node->lchild) > 0) //LL型
                    node = LL_rotate(node);
                else  //LR型
                    node = LR_rotate(node);
            }
            else //右子树高
            {
                if (is_balance(node->rchild) < 0) //RR型
                    node = RR_rotate(node);
                else //RL型
                    node = RL_rotate(node);
            }
            if (node->parent == NULL) //到达根结点
            {
                root = node; //设置新的根结点
                break; //退出
            }
        }
        node = node->parent; //依次找到其父节点
    }
    return root; //返回新根
}
//查找最小结点
Tree* Find_Min(Tree& root)
{
    if (root->lchild)
    {
        return Find_Min(root->lchild);
    }
    return &root;
}
//删除操作
//参数：根，需要删除的结点
//返回值: 返回删除结点的父节点
Tree remove_val(Tree& root, Tree& node)
{
    Tree parent = node->parent;
    Tree temp = NULL;
    //只有左孩子
    if (node->rchild == NULL && node->lchild != NULL)
    {
        temp = node;
        node = node->lchild; //指向左孩子
        node->parent = temp->parent;
        delete temp;       //释放结点
        update_depth(node); //更新当前结点信息
    }
    else if (node->lchild == NULL && node->rchild != NULL) //只有右孩子
    {
        temp = node;
        node = node->rchild; //指向右结点
        node->parent = temp->parent;
        delete temp;       //释放结点
        update_depth(node); //更新当前结点信息
    }
    else if (node->rchild == NULL && node->lchild == NULL) //叶子结点
    {
        parent = node->parent; //找到其父节点
        if (parent) //如果父节点存在
        {
            delete node;
            node = NULL;
            update_depth(parent); //更新父节点高度信息
        }
        else //删除的是根
        {
            delete root;
            root = NULL;
        }
    }
    else //既有左孩子也有右孩子，化繁为简
    {
        Tree* tmp = Find_Min(node->rchild); //找到替代元素，temp为叶子结点
        node->val = (*tmp)->val;         //更新值
        //判断当前叶子结点是左孩子还是右孩子。
        parent = (*tmp)->parent;
        /*
        if (parent->lchild==temp)
        {
            parent->lchild=0;
            delete temp;
        }
        else
        {
            parent->rchild=0;
            delete temp;
        }
         */
        delete* tmp;
        *tmp = NULL;
        update_depth(parent);
    }
    return parent;
}
//找到删除的结点，执行删除操作，并根据情况调整AVL树
//参数：根，需要删除的val
//返回：找到删除结点的情况则返回新根，否则返回NULL
Tree remove(Tree& root, ElementType val)
{
    static Tree* temp = NULL;
    if (root == NULL)
    {
        temp = NULL;
        return NULL;
    }
    else if (root->val < val) //在右子树查找
        remove(root->rchild, val);
    else if (root->val > val) //在左子树查找
        remove(root->lchild, val);
    else   //找到了，标记一下
        temp = &root;
    if (temp)
    {
        if (!root->parent) //如果已经返回到最后一次（也就是root是真正的树根）
        {
            Tree tmp = NULL;
            tmp = remove_val(root, *temp);  //执行删除操作
            return AVLTree(root, tmp); //更新AVL树
        }
        return *temp;
    }
    return NULL;
}
//获取当前结点的深度
int get_balance(Tree node)
{
    if (node == NULL)
        return 0;
    return node->depth;
}
//返回当前平衡因子
int is_balance(Tree node)
{
    if (node == NULL)
        return 0;
    else
        return get_balance(node->lchild) - get_balance(node->rchild);
}
//RR型调整函数
//返回新父节点
Tree RR_rotate(Tree node)
{
    //node为离操作结点最近的失衡的结点
    Tree parent = NULL, son;
    //获取失衡结点的父节点
    parent = node->parent;
    //获取失衡结点的右孩子
    son = node->rchild;
    //设置son结点左孩子的父指针
    if (son->lchild != NULL)
        son->lchild->parent = node;
    //失衡结点的右孩子变更为son的左孩子
    node->rchild = son->lchild;
    //更新失衡结点的高度信息
    update_depth(node);
    //失衡结点变成son的左孩子
    son->lchild = node;
    //设置son的父结点为原失衡结点的父结点
    son->parent = parent;
    //如果失衡结点不是根结点，则开始更新父节点
    if (parent != NULL)
    {
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if (parent->lchild == node)
            parent->lchild = son;
        else //父节点的右孩子是失衡结点
            parent->rchild = son;
    }
    //设置失衡结点的父亲
    node->parent = son;
    //更新son结点的高度信息
    update_depth(son);
    return son;
}
//LL型调整函数
//返回:新父节点
Tree LL_rotate(Tree node)
{
    //node为离操作结点最近的失衡的结点
    Tree parent = NULL, son;
    //获取失衡结点的父节点
    parent = node->parent;
    //获取失衡结点的左孩子
    son = node->lchild;
    //设置son结点右孩子的父指针
    if (son->rchild != NULL)
        son->rchild->parent = node;
    //失衡结点的左孩子变更为son的右孩子
    node->lchild = son->rchild;
    //更新失衡结点的高度信息
    update_depth(node);
    //失衡结点变成son的右孩子
    son->rchild = node;
    //设置son的父结点为原失衡结点的父结点
    son->parent = parent;
    //如果失衡结点不是根结点，则开始更新父节点
    if (parent != NULL)
    {
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if (parent->lchild == node)
            parent->lchild = son;
        else //父节点的右孩子是失衡结点
            parent->rchild = son;
    }
    //设置失衡结点的父亲
    node->parent = son;
    //更新son结点的高度信息
    update_depth(son);
    return son;
}
//LR型，先左旋转，再右旋转
//返回：新父节点
Tree LR_rotate(Tree node)
{
    RR_rotate(node->lchild);
    return LL_rotate(node);
}
//RL型，先右旋转，再左旋转
//返回:新父节点
Tree RL_rotate(Tree node)
{
    LL_rotate(node->rchild);
    return RR_rotate(node);
}
int max(int a, int b) {
    if (a >= b)  return a;
    else    return b;
}
//更新当前深度
void update_depth(Tree node)
{
    if (node == NULL)
        return;
    else
    {
        int depth_Lchild = get_balance(node->lchild); //左孩子深度
        int depth_Rchild = get_balance(node->rchild); //右孩子深度
        node->depth = max(depth_Lchild, depth_Rchild) + 1;
    }
}

//中序遍历  用于测试平衡二叉排序树的正确
void InOrder(Tree root)
{
    if (root == NULL)
        return;
    InOrder(root->lchild);
   cout<<root->val<<"  "<<root->bookname<<endl;
    InOrder(root->rchild);
}
Tree find(Tree& root, int xx) {         //二叉排序树的查找
    if (root->val = xx)
        return root;
    if (root->val < xx)
         find(root->lchild, xx);
    if (root->val > xx)
         find(root->rchild, xx);
}
void aoutput(Tree& root,string kg) {      //凹入表打印，在每个插入后验证
    if (root != NULL) {
        cout <<root->val << endl;
       
            if (root->lchild) {
                kg = kg + "  ";
                cout << kg<<"左:";
                aoutput(root->lchild, kg);
                if (root->rchild) {
                    cout << kg << "右:";
                    aoutput(root->rchild, kg);
                }
            }
            if (root->lchild==NULL&&root->rchild) {
                kg = kg + "  ";
                cout <<kg<< "右:";
                aoutput(root->rchild, kg);
            }
           
    }
   
}

bookjie findbro(long int temp,bookjie chaxun) {  //根据图书证号查找借书者的信息
    for (int j = 0; j <= 10; j++) {
       
        if (chaxun->borrowNumber != temp) {
            ++chaxun;
        }
        if (chaxun->borrowNumber == temp) {
            return chaxun;
            break;
        }
    }
    return NULL;
}
void outputbrorrowbook(bookjie dfd) {         //查找该借书者的借书信息，打印出来
    zhixiang sdsa;
    if(dfd->xia!= NULL) {
        cout << dfd->xia->shuhao << endl;
    }
    sdsa = dfd->xia->next;
    if (sdsa != NULL) {
        cout << sdsa->shuhao;
        sdsa = sdsa->next;
    }
}
void  reback(int xx, bookjie cv) {      //还书
    zhixiang  vfvf,lll=NULL;
    vfvf = cv->xia;
    while (vfvf->shuhao != xx) {
        lll = vfvf;
        vfvf = vfvf->next;

    }
    lll->next = vfvf->next;
    free(vfvf);
}
int main()
{   
    cout << "图书信息如下,依次插入平衡二叉排序树中" << endl;
    cout << "书号   " << "书名       " << "作者     " << "现库存   " << "总库存   "<<endl;
    cout << "16     " << "JAVA基础   " << "Nocdfv   " << "10       " << "10   " << endl;
    cout << "3      " << "Linux      " << "balala   " << "20       " << "20   " << endl;
    cout << "7      " << "语文       " << "小天     " << "5        " << "5   " << endl;
    cout << "11     " << "数学       " << "小明     " << "6        " << "6   " << endl;
    cout << "9      " << "英语       " << "小红     " << "2        " << "2   " << endl;
    cout << "26     " << "政治       " << "小刚     " << "1        " << "1   " << endl;
    cout << "18     " << "历史       " << "小酷     " << "3        " << "3   " << endl;
    cout << "14     " << "地理       " << "小金     " << "4        " << "4   " << endl;
    cout << "15     " << "物理       " << "koolas   " << "8        " << "8   " << endl;
    string kongge = " ";
    cout <<"下面每插入一个，凹入表打印"<< endl;
    Tree chazhao = NULL;
    Tree root = NULL;
    //采编入库
    root = Insert(root, 16,"JAVA基础","Nocdfv",10,10);
    aoutput(root,kongge);
    cout << endl;
    root = Insert(root, 3,"Linux操作系统","balala",20,20);
    aoutput(root, kongge);
    cout << endl;
    //插入7后LR调整
    root = Insert(root, 7, "语文", "小天", 5, 5);
    aoutput(root, kongge);
    cout << endl;
    root = Insert(root, 11, "数学", "小明", 6, 6);
    aoutput(root, kongge);
    cout << endl;
    //插入9后LL调整
    root = Insert(root, 9, "英语", "小红", 2, 2);
    aoutput(root, kongge);
    cout << endl;
    //插入26后RR调整
    root = Insert(root, 26, "政治", "小刚", 1, 1);
    aoutput(root, kongge);
    cout << endl;
    //插入28后RL调整
    root = Insert(root, 18, "历史", "小酷", 3, 3);
    aoutput(root, kongge);
    cout << endl;
    root = Insert(root, 14, "地理", "小金", 4, 4);
    aoutput(root, kongge);
    cout << endl;
    //插入15后LR调整
    root = Insert(root, 15, "物理", "koolas", 8, 8);
    aoutput(root, kongge);
    cout << endl;
    InOrder(root);
    //借阅功能
   
    bookjie  yi = (bookjie)malloc(10 * sizeof(borrower));     //创建10个借书者的顺序表
   
        cout << "请输入您的借阅证号" << endl;
        cin >> yi[0].borrowNumber;
        zhixiang sd = NULL;
        zhixiang sdaaa = NULL;
    for (int u = 0; u <= 10; u++) {
        
        cout << "请输入想借的书的书号" << endl;
        int xx;
        cin >> xx;
        chazhao = find(root, xx);
        if (chazhao->xian >= 0) {
            cout << "有库存，可借阅" << endl;
            zhixiang fg;
           
            fg = new bookborrow;
            fg->shuhao=chazhao->val;
            yi[0].xia = fg;
            

            yi[0].xia->next = sdaaa;             //顺序表后接的链表形式存储书籍信息
            sdaaa = yi[0].xia;
            
            //  cout << yi[0].xia->booknames << " " << yi[0].xia->shuhao;
            cout << "请输入还书日期 以20120101 类形式" << endl;
            cin >> yi[0].xia->data;
            cout << "借书成功！" << endl;
            chazhao->xian = chazhao->xian - 1;//借阅成功，现存量减1
        }
        else
            cout << "抱歉，现无库存" << endl;

        cout << "是否继续借书?继续借请输入 1 ，不借输入 0 " << endl;
        int vc;
        cin >> vc;
        if (vc == 0)  
            break;
    }
    cout << "归还图书测试" << endl;
    cout << "请输入你的借书证号" << endl;
    long int mm;
    cin >> mm;
    bookjie zhongzhuang;
    zhongzhuang = findbro(mm, yi);
    cout << "查询到你现在持有的书有 "<< endl;
    outputbrorrowbook(zhongzhuang);
    cout << endl;
    cout << "请选择要还的书,输入书号" << endl;
    int  xx;
    cin >> xx;
    cout << "已还成功！" << endl;
    reback(xx, yi);
    cout << "查询到你现在持有的书有 " << endl;
    outputbrorrowbook(zhongzhuang);
    cout << "清除库存测试" << endl;
    cout << "请选择要删除的书的书号" << endl;
    int mop;
    cin >> mop;
    remove(root, mop);
    aoutput(root, kongge);
    cout << endl;
    cout << "请选择要删除的书的书号" << endl;
    cin >> mop;
    remove(root, mop);
    aoutput(root, kongge);
    

    return 0;
}
