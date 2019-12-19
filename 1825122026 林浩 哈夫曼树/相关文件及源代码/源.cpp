#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>;
using namespace std;

#define N 27//带权值的叶子节点数或者是需要编码的字符数
#define M 2*N-1//n个叶子节点构造的哈夫曼树有2n-1个结点
#define MAX 10000
typedef char TElemType;
//静态三叉链表存储结构
typedef struct {

    int weight;
	int parent;
	int lchild;
	int rchild;

}HTNode;//, *HuffmanTree;

typedef struct node {

	int data;
	node* lelem;
	node* relem;

}node, * bnode;
bnode ai = (bnode)malloc((M+1) * sizeof(node));
typedef HTNode HuffmanTree[M + 1];//0号单元不使用
typedef char* HuffmanCode[N + 1];//存储每个字符的哈夫曼编码表，是一个字符指针数组，每个数组元素是指向字符指针的指针

void select(HuffmanTree HT, int k, int& s1, int& s2) {

	//假设s1对应的权值总是<=s2对应的权值

	unsigned int tmp = MAX, tmpi = 0;
	for (int i = 1; i <= k; i++) {
		if (!HT[i].parent) {//parent必须为0
			if (tmp > HT[i].weight) {
				tmp = HT[i].weight;//tmp最后为最小的weight
				tmpi = i;
			}
		}
	}
	s1 = tmpi;
	tmp = MAX;
	tmpi = 0;
	for (int i = 1; i <= k; i++) {
		if ((!HT[i].parent) && i != s1) {//parent为0
			if (tmp > HT[i].weight) {
				tmp = HT[i].weight;
				tmpi = i;
			}
		}
	}
	s2 = tmpi;
}

//构造哈夫曼树

void createHuffmanTree(HuffmanTree& HT, int* w, int n) {
	int i = 1;
	if (n <= 1)
		return;
	//对树赋初值

	for (; i <= n; i++) {//HT前n个分量存储叶子节点，他们均带有权值

		HT[i].weight = w[i];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	for (; i <= M; i++) {//HT后m-n个分量存储中间结点，最后一个分量显然是整棵树的根节点
		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	//开始构建哈夫曼树，即创建HT的后m-n个结点的过程，直至创建出根节点。用哈夫曼算法
	for (i = n + 1; i <= M; i++) {
		int s1, s2;
		select(HT, i - 1, s1, s2);//在HT[1...i-1]里选择parent为0的且权值最小的2结点，其序号分别为s1,s2，parent不为0说明该结点已经参与构造了，故不许再考虑
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
void decodingHuffmanCode(HuffmanTree HT, char* ch, char testDecodingStr[], int len, char* result) {

	int p = M;//HT的最后一个节点是根节点，前n个节点是叶子节点
	int i = 0;//指示测试串中的第i个字符
	//char result[30];//存储解码以后的字符串
	int j = 0;//指示结果串中的第j个字符
	while (i < len) {
		if (testDecodingStr[i] == '0') {
			p = HT[p].lchild;
		}
		if (testDecodingStr[i] == '1') {
			p = HT[p].rchild;
		}
		if (p <= N) {//p<=N则表明p为叶子节点,因为在构造哈夫曼树HT时，HT的m个节点中前n个节点为叶子节点
			result[j] = ch[p];
			j++;
			p = M;//p重新指向根节点
		}
		i++;
	}
	result[j] = '\0';	
}

//为每个字符求解哈夫曼编码，从叶子到根逆向求解每个字符的哈夫曼编码

void encodingHuffmanCode(HuffmanTree HT, HuffmanCode& HC) {

	//char *tmp = (char *)malloc(n * sizeof(char));//将每一个字符对应的编码放在临时工作空间tmp里，每个字符的编码长度不会超过n
	char tmp[N];
	tmp[N - 1] = '\0';//编码的结束符
	int start, c, f;
	for (int i = 1; i <= N; i++) {//对于第i个待编码字符即第i个带权值的叶子节点
		start = N - 1;//编码生成以后，start将指向编码的起始位置
		c = i;
		f = HT[i].parent;
		while (f) {//f!=0,即f不是根节点的父节点
			if (HT[f].lchild == c) {
				tmp[--start] = '0';
			}
			else {//HT[f].rchild == c,注意:由于哈夫曼树中只存在叶子节点和度为2的节点，所以除开叶子节点，节点一定有左右2个分支
				tmp[--start] = '1';
			}
			c = f;
     		f = HT[f].parent;
		}
		HC[i] = (char*)malloc((N - start) * sizeof(char));//每次tmp的后n-start个位置有编码存在
		strcpy(HC[i], &tmp[start]);//将tmp的后n-start个元素分给H[i]指向的的字符串
	}
}

void encode(char dd[],char ch[],HuffmanCode HC,string &aa)  //对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中
{
	int i;
	for (int k = 0; dd[k]!=NULL; k++) {
		i = 1;
		while (dd[k] != ch[i])
		{
			++i;
			
		}
		aa += HC[i];
	}
	
}


//打印哈夫曼满树
void printHuffmanTree(HuffmanTree HT, char ch[]) {
	printf("\n");
	printf("data, weight, parent, lchild, rchild\n");
	for (int i = 1; i <= M; i++) {
		if (i > N)
		{
			printf("  -, %5d, %5d, %5d, %5d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}
		else {

			printf("  %c, %5d, %5d, %5d, %5d\n", ch[i], HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

		}

	}

	printf("\n");

}
/*
void printHelp(HTNode &p, string ss,HTNode * as)
{
	if (p.weight==0)
		return;
	ss += " ";
	int x = p.rchild-1;
	HTNode rr = as[x];
	printHelp(rr, ss, as);	
	cout << ss << p.weight << endl;
	int y = p.lchild-1;
	printHelp(as[y], ss, as);
	
}
void printha(HTNode &root, HTNode* as) {

			string ss = " ";
			printHelp(root, ss, as);
		}
	*/	
/*
void create(bnode q,HTNode *p,HuffmanTree zz){
	if (!p) {
		q = NULL;
		return;
	}
	else
		q = new node;
	cout << &p;
	q->data = p->weight;
	p = &zz[p->lchild];
	create(q->lelem, p, zz);

	p = &zz[p->rchild];
	create(q->relem, p, zz);

 }
 */
void printHelp(bnode p, string ss, ofstream& www)
{
	if (p == NULL)
		return;
	ss += " ";
	printHelp(p->relem, ss,www);
	cout << ss << p->data << endl;
	www<<ss<< p->data << endl;
	printHelp(p->lelem, ss,www);
}
void printa(bnode root,ofstream &www) {
	string ss = " ";
	printHelp(root, ss,www);
}


int main() {
	HuffmanTree HT;
	HTNode e;
	TElemType ch[N + 1];
	int w[N + 1];
	cout << "请输入" << N << "个字符及其对应的权值" << endl;
	
	
	for (int i = 1; i <= N; i++) {
		cin >> ch[i];
		cin >> w[i];
	}
	createHuffmanTree(HT, w, N);

	//将建立好的哈夫曼树存储到文件hfmTree中
	ofstream outFile("hfmTree.dat", ios::out | ios::binary);
	for (int i = 1; i <= M; i++) {
		e = HT[i];
		outFile.write((char*)& e, sizeof(HTNode));

	}
	outFile.close();
	/*   测试是否写入成功
	ifstream inFile("hfmTree.dat", ios::in | ios::binary);
	if (!inFile) {
		cout << "error" << endl;
		return 0;
	}
	while (inFile.read((char*)& s, sizeof(s))) { //一直读到文件结束
			cout <<s.weight<< " " <<s.parent << " " <<s.lchild<<" "<<s.rchild<< endl;
	}
	inFile.close();
	return 0;
	*/
	ifstream ppp;
	ppp.open("ToBeTran.txt");    //对ToBeTran.txt的正文编码
	char kkk[100];
	

	char cha;
	cin.unsetf(ios::skipws);

	int r = 0;
	do
	{   
		ppp.get(cha);
		
		if (cha == ' ') {
			kkk[r] = '^';
		
		}
		else {
			kkk[r] = cha;
			
		}
		++r;
	} while (!ppp.eof());

	ppp.close();
	kkk[r-1] = NULL;
	cout << kkk << endl;
	HuffmanCode HC;
	encodingHuffmanCode(HT, HC);
	string chk;
	encode(kkk, ch, HC, chk);
	cout << chk;
	ofstream  cxk;
	cxk.open("CodeFile.txt");       //将结果存入文件CodeFile中
	cxk << chk;
	cxk.close();
	char www[500];
	ifstream ttt;
	ttt.open("CodeFile.txt");   //将文件CodeFile中的代码进行译码
	ttt >> www;
	ttt.close();
	char* testDecodingStr = www;
	int testDecodingStrLen = chk.length();
	char result[1000];//存储解码以后的字符串
	decodingHuffmanCode(HT, ch, testDecodingStr, testDecodingStrLen, result);//解码（译码），通过一段给定的编码翻译成对应的字符串
	ofstream  sss;
	sss.open("TextFile.txt");   //译码后结果存入文件TextFile中
	sss << result;
	sss.close();

	//将文件CodeFile以紧凑格式显示在终端上，每行50个代码。
	//同时将此字符形式的编码文件写入文件CodePrin中。
	char daying[1000];
	ifstream print;
	print.open("CodeFile.txt");
	ofstream tofile;
	tofile.open("CodePrin.txt");
	print >> daying;
	int p = 0;
	for (int i = 0; ; i++) {
		if (daying[i] == NULL)  break;
		cout << daying[i];
		tofile << daying[i];
		++p;
		if (p % 50 == 0)
		{
			cout << endl;
			tofile << endl;
		}
	}
	//将哈夫曼树直观地打印，并写入文件TreePrint中
	printHuffmanTree(HT, ch);
	/*	bnode jiayou=NULL ;
		for(int i=0;i<=M;i++)
		cout<<&HT[i]<<endl;
		HTNode *chong =&HT[M];
		cout << &chong;
		create(jiayou, chong, HT);
		printa(jiayou);
		*/
	for (int i = 1; i <= M; i++) {
		ai[i].data = HT[i].weight;
		if (HT[i].lchild == 0) {
			ai[i].lelem = NULL;
		}

		if (HT[i].lchild != 0) {
			int t;
			t = HT[i].lchild;
			ai[i].lelem = &ai[t];
		}
		if (HT[i].rchild == 0) {
			ai[i].relem = NULL;
		}
		if (HT[i].rchild != 0) {
			int t;
			t = HT[i].rchild;
			ai[i].relem = &ai[t];
		}

	}
	//for (int i = 1; i <= M; i++) {
	//	cout << &ai[i] << endl;
	
	bnode root = &ai[M];
	ofstream lalala;
	lalala.open("TreePrint.txt");
	printa(root,lalala);
	/*cout << &ai[M] << endl;
	cout << &(*root->relem) << endl;
	cout << root->relem << endl;
	cout << &(root->relem)<<endl;//  通过这一段测试终于发现问题
	bnode kk = root->relem;   // 原来是指针的理解还是不到位

	cout << kk->data;//*/  
	
	return 0;
}
