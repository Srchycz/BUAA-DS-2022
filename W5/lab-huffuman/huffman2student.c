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
	(Step==1) ? print1(): 1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root): 2; 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3(): 3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4(): 4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

void statCount()
{


	
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

void createHTree()
{


	
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

void makeHCode()
{

	
	
} 

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

void atoHZIP()
{


	
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
