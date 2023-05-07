//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1():(void)1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root):(void)2; 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3():(void)3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4():(void)4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 
char text[500000];
int textlen;
void statCount()
{
	fgets(text,450000,Src);
	textlen=strlen(text);
	if(text[textlen-1]=='\n') text[textlen-1]='\0';
	for(int i=0;i<textlen;++i)
		++Ccount[text[i]];
	Ccount[0]=1;
}

//【实验步骤1】结束

//【实验步骤2】开始
typedef struct tnode Tnode;
Tnode *heap[2000];
int tot,idx=127;
int cmp(Tnode* a,Tnode* b){
    if(a->weight==b->weight)
        return (unsigned char)a->c<(unsigned char)b->c;
    return a->weight<b->weight;
}
void Insert(Tnode* d){
    int now=++tot;
    while (now>1){
        if(!cmp(heap[now>>1],d))
            heap[now]=heap[now>>1],now>>=1;
        else break;
    }
    heap[now]=d;
}
void Extract(){
    int now=1,nxt=2;
    Tnode* k=heap[tot--];
    while (nxt<=tot){
        if(nxt<tot&&!cmp(heap[nxt],heap[nxt|1])) nxt|=1;
        if(!cmp(k,heap[nxt])) heap[now]=heap[nxt],now=nxt,nxt<<=1;
        else break;
    }
    heap[now]=k;
}
void createHTree()
{
	for(int i=0;i<128;++i){
		if(Ccount[i]){
			Tnode *p=(Tnode*)malloc(sizeof(Tnode));
			p->c=i,p->weight=Ccount[i];
			p->left=NULL,p->right=NULL;
			Insert(p);
		}
	}
	while(tot>1){
		Tnode* a=heap[1];Extract();
		Tnode* b=heap[1];Extract();
		Tnode *p=(Tnode*)malloc(sizeof(Tnode));
		++idx;
		p->c=idx;
		p->weight=a->weight+b->weight;
		p->left=a,p->right=b;
		Insert(p);
	}
	Root=heap[1];
}

//【实验步骤2】结束

//【实验步骤3】开始
char temp[200];
void dfs(Tnode* p,int dep){
	if(p->left==NULL&&p->right==NULL){
		temp[dep]='\0';
		strcpy(HCode[p->c],temp);
	}
	if(p->left!=NULL){
		temp[dep]='0';
		dfs(p->left,dep+1);
	}
	if(p->right!=NULL){
		temp[dep]='1';
		dfs(p->right,dep+1);
	}
}
void makeHCode()
{
	dfs(Root,0);
} 

//【实验步骤3】结束

//【实验步骤4】开始
char v[200000];
void atoHZIP()
{
	textlen=strlen(text);
	for(int i=0;i<=textlen;++i)
		strcat(v,HCode[text[i]]);
	// fputs(v,Obj);
	int u=strlen(v);
	int w=u;
	if(u%8!=0){
		w=u/8*8+8;
		for(int i=u;i<=w;++i)
			v[i]='0';
	}
	char c=0;
	for(int i=0;i<w;++i){
		if(i%8==0&&i!=0){
			fputc(c,Obj);
			printf("%x",(unsigned char)c);
			c=0;
		}
		c|=((v[i]-'0')<<(7-(i%8)));
	}
	fputc(c,Obj);
	printf("%x",c);
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
