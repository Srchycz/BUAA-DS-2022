// #define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#define EPS 1e-9
#define PI 3.14159265358979323846
#define maximum(x, y) ((x) > (y) ? (x) : (y))
#define minimum(x, y) ((x) < (y) ? (x) : (y))
typedef long long LL;
typedef unsigned long long ULL;
int gcd(int x, int y)
{
	return (y == 0) ? (x) : (gcd(y, x % y));
}
//以上是缺省源

//===========================macro==========================

#define WORD_LEN_MAX 250					//单词最长长度
#define HASH_TABLE_SIZE 100003				//hash表的长度
#define NMAX 10000							//N的最大值
#define MMAX 128							//M的最大值
#define FINGERPRINT_NUM	4		 			//fingerprint中unsigned int的个数


//===========================struct==========================

//字典树结构
typedef struct TRIE
{
	int flag;
	struct TRIE *son[26];
} trie;
trie *trie_root = NULL;

//hash表结构
typedef struct HASHNODE
{
	char word[WORD_LEN_MAX];
	int count;
	int sub;					//sub表示在特征向量中的下标，默认-1
	struct HASHNODE *next;
} hashnode;
hashnode *hash_table[HASH_TABLE_SIZE] = { 0 };
hashnode *feature_table[NMAX + 1];

//网页结构
typedef struct WEB
{
	char ID[WORD_LEN_MAX];
	unsigned int fingerprint[FINGERPRINT_NUM];
	struct WEB *next;
} web;
web *first_article = NULL, * first_sample = NULL;

//答案缓存结构
typedef struct ANS_BUFF
{
	char *ID;
	struct ANS_BUFF *next;
} ans_buff;
ans_buff *ans_first[4] = { 0 }, * ans_last[4] = { 0 };


//===========================global==========================

int M, N;
FILE *in_stopwords, * in_hashvalue, * in_article, * in_sample, * out_result;
char *hashvalue_table;
int word_count;					//统计hash表中一共有多少单词


//===========================state==========================

void stopword_read();
void hash_table_create();
void feature_creat();
web *fingerprint_creat(FILE *in);
void ans_print();
void hashvalue_read();


int main(int argc, char **argv)
{
	N = atoi(argv[1]);
	M = atoi(argv[2]);

	in_stopwords = fopen("stopwords.txt", "r");
	in_hashvalue = fopen("hashvalue.txt", "r");
	in_article = fopen("article.txt", "r");
	in_sample = fopen("sample.txt", "r");
	out_result = fopen("result.txt", "w");

	stopword_read();
	hashvalue_read();
	hash_table_create();
	feature_creat();

	first_article = fingerprint_creat(in_article);
	first_sample = fingerprint_creat(in_sample);
	ans_print();

	fclose(in_stopwords);
	fclose(in_hashvalue);
	fclose(in_article);
	fclose(in_sample);
	fclose(out_result);

	return 0;
}

//===========================proto==========================

trie *trie_add(trie *root, char *p)
{
	if(root == NULL)
	{
		root = (trie *)calloc(1, sizeof(trie));
	}
	if(*p == '\0')
	{
		root->flag = 1;
		return root;
	}
	root->son[*p - 'a'] = trie_add(root->son[*p - 'a'], p + 1);
	return root;
}

//读取stopword并且存于字典树trie_root中
void stopword_read()
{
	char stopword[WORD_LEN_MAX] = { 0 };
	while(fgets(stopword, WORD_LEN_MAX, in_stopwords) != NULL)
	{
		stopword[strlen(stopword) - 1] = '\0';
		trie_root = trie_add(trie_root, stopword);
	}
}

//读取hash的前N行前M列
void hashvalue_read()
{
	char laji[MMAX];
	hashvalue_table = calloc(N * M + 1, sizeof(char));
	for(int i = 0; i < N; i++)
	{
		fgets(hashvalue_table + i * M, M + 1, in_hashvalue);
		fgets(laji, MMAX, in_hashvalue);
	}
}

//从指定文件中读取一个单词
//单词存放于word中
//返回值为1说明未到网页尾
int fgetword(FILE *in, char *word)
{
	char *p = word;
	char ch = 0;
	while(!isalpha(ch = fgetc(in)))
	{
		if(ch == '\f')
		{
			return 0;
		}
		if(ch == EOF)
		{
			return -1;
		}
	}
	ungetc(ch, in);
	while(1)
	{
		ch = fgetc(in);
		if(islower(ch))
		{
			*p = ch;
			p++;
		}
		else if(isupper(ch))
		{
			*p = tolower(ch);
			p++;
		}
		else
		{
			*p = '\0';
			if(ch == '\f')
			{
				return 0;
			}
			else if(ch == EOF)
			{
				return EOF;
			}
			else
			{
				return 1;
			}
		}
	}
}

//判断word是否在停用词表中
int isstopword(char *word)
{
	int sub = 0;
	trie *root = trie_root;
	while(root != NULL)
	{
		if(word[sub] == '\0')
		{
			return root->flag;
		}
		root = root->son[word[sub] - 'a'];
		sub++;
	}
	return 0;
}

//hash函数
unsigned int hash(char *key)
{
	unsigned int hash_val = 0;
	while(*key != '\0')
	{
		hash_val = hash_val * 31 + *key - 'a' + 1;
		key++;
	}
	return hash_val % HASH_TABLE_SIZE;
}

//将word添加到hash表中
void hash_table_add(char *word)
{
	unsigned int hash_val = hash(word);
	hashnode *pnode = hash_table[hash_val], * prepnode = NULL;
	while(pnode != NULL)
	{
		if(strcmp(pnode->word, word) == 0)
		{
			pnode->count++;
			return;
		}
		prepnode = pnode;
		pnode = pnode->next;
	}
	hashnode *q = (hashnode *)malloc(sizeof(hashnode));
	strcpy(q->word, word);
	q->count = 1;
	q->sub = -1;
	q->next = NULL;
	if(prepnode == NULL)
	{
		hash_table[hash_val] = q;
	}
	else
	{
		prepnode->next = q;
	}
	word_count++;
}

//建造hash_table
//in_article文件指针会返回文件首
void hash_table_create()
{
	char ch = 0;
	char ID[WORD_LEN_MAX] = { 0 };

	while((ch = fgetc(in_article)) != EOF)
	{
		ungetc(ch, in_article);

		fscanf(in_article, "%s", ID);

		int flag = 0;
		while(1)
		{
			char word[WORD_LEN_MAX] = { 0 };
			flag = fgetword(in_article, word);
			if(flag != 1)
			{
				break;
			}
			if(strlen(word) != 0)
			{
				if(!isstopword(word))
				{
					hash_table_add(word);
				}
			}
		}
		if(flag == -1)
		{
			break;
		}
	}

	fseek(in_article, 0, SEEK_SET);
}

//特征向量重排
void feature_resort()
{
	int sub = N;
	while(sub != 0 && (feature_table[sub - 1] == NULL || feature_table[sub - 1]->count < feature_table[sub]->count || (feature_table[sub - 1]->count == feature_table[sub]->count && strcmp(feature_table[sub]->word, feature_table[sub - 1]->word) < 0)))
	{
		hashnode *temp = feature_table[sub];
		feature_table[sub] = feature_table[sub - 1];
		feature_table[sub - 1] = temp;
		sub--;
	}
}

//生成网页特征向量
void feature_creat()
{
	for(int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		hashnode *q = hash_table[i];
		while(q != NULL)
		{
			feature_table[N] = q;
			feature_resort();
			q = q->next;
		}
	}

	for(int i = 0; i < N; i++)
	{
		feature_table[i]->sub = i;
	}
}

//为一串网页生成指纹
web *fingerprint_creat(FILE *in)
{
	web *first = NULL, * p = NULL, * q = NULL;
	char ch = 0;

	while((ch = fgetc(in)) != EOF)
	{
		ungetc(ch, in);

		q = (web *)calloc(1, sizeof(web));
		fscanf(in, "%s", q->ID);
		if(first == NULL)
		{
			first = p = q;
		}
		else
		{
			p->next = q;
			p = q;
		}

		int count[NMAX] = { 0 };
		int flag = 0;
		while(1)
		{
			char word[WORD_LEN_MAX] = { 0 };
			flag = fgetword(in, word);
			if(flag != 1)
			{
				break;
			}
			if(strlen(word) != 0)
			{
				hashnode *pnode = hash_table[hash(word)];
				while(pnode != NULL)
				{
					if(strcmp(pnode->word, word) == 0)
					{
						int sub = pnode->sub;
						if(sub != -1)
						{
							count[sub]++;
							break;
						}
					}
					pnode = pnode->next;
				}

			}
		}

		int sum[MMAX] = { 0 };
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < M; j++)
			{
				(hashvalue_table[i * M + j] - '0') ? (sum[j] += count[i]) : (sum[j] -= count[i]);
			}
		}
		for(int i = 0; i < M; i++)
		{
			q->fingerprint[i / 32] = q->fingerprint[i / 32] << 1;
			if(sum[i] > 0)
			{
				q->fingerprint[i / 32] ++;
			}
		}

		if(flag == -1)
		{
			break;
		}
	}

	return first;
}

//计算距离
int distance_cal(unsigned int x, unsigned int y)
{
	int distance = 0;
	unsigned int z = x ^ y;
	while(z != 0)
	{
		z &= (z - 1);
		distance += 1;
	}
	return distance;
}

//缓存结果
void ans_buff_add(char *ID, int distance)
{
	ans_buff *q = (ans_buff *)malloc(sizeof(ans_buff));
	q->ID = ID;
	q->next = NULL;
	if(ans_first[distance] == NULL)
	{
		ans_first[distance] = ans_last[distance] = q;
	}
	else
	{
		ans_last[distance]->next = q;
		ans_last[distance] = q;
	}
}

//输出一个sample网页的结果
// flag为1表示需要输出到stdout
//同时释放缓冲区空间
void ans_web_print(char sample_ID[WORD_LEN_MAX], int flag)
{
	fprintf(out_result, "%s\n", sample_ID);
	if(flag)
	{
		fprintf(stdout, "%s\n", sample_ID);
	}
	for(int i = 0; i <= 3; i++)
	{
		ans_buff *p = ans_first[i];
		if(p != NULL)
		{
			fprintf(out_result, "%d:", i);
			if(flag)
			{
				fprintf(stdout, "%d:", i);
			}
			while(p != NULL)
			{
				fprintf(out_result, "%s ", p->ID);
				if(flag)
				{
					fprintf(stdout, "%s ", p->ID);
				}
				ans_buff *prep = p;
				p = p->next;
				free(prep);
			}
			fputc('\n', out_result);
			if(flag)
			{
				fputc('\n', stdout);
			}
			ans_first[i] = ans_last[i] = NULL;
		}
	}
}

//输出结果
void ans_print()
{
	web *psample = first_sample;
	while(psample != NULL)
	{
		web *particle = first_article;
		while(particle != NULL)
		{
			int distance = 0;
			for(int i = 0; i < FINGERPRINT_NUM; i++)
			{
				distance += distance_cal(particle->fingerprint[i], psample->fingerprint[i]);
			}
			if(distance <= 3)
			{
				ans_buff_add(particle->ID, distance);
			}
			particle = particle->next;
		}

		ans_web_print(psample->ID, psample == first_sample);
		psample = psample->next;
	}
}