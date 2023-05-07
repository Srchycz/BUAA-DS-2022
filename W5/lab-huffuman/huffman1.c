//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

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
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step==1) ? print1():(void)1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root):(void)2; 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3():(void)3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4():(void)4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 
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

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ
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

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ
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

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ
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

//��ʵ�鲽��4������

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
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
