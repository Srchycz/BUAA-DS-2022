#define _CRT_SECURE_NO_WARNINGS
#pragma GCC optimize ("O3")
#pragma once
#pragma pack (16)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE 1000005
#define Sens 120000
struct sentence {
	int sen[2];
	int frequency;
	int sentenceorder;
}Sen[Sens];
int i, j, m, l = 0, ll, n, flag = 0, temp, N, M;
int SenNum = 0, senbegin[SIZE], VacNum = 0, VacFre[SIZE * 5], * VacFrePtr;
char s[46600], tmp[200], buff[2000], ch; char st[Sens][45], hash[10001][130], na[Sens][40], id[Sens][40], sana[40];//s在这里定义
int Trie[1000010][26];
int Freqc[1000010] = { 0 };
int pos = 1, p = 0, ar[Sens][130], sa[130], ct1 = 0;//ct1是停用词数量
void getSW()//暂且不需要看
{
	freopen("stopwords.txt", "r", stdin);

	while (scanf("%s", st[ct1++]) != EOF);

	fclose(stdin);
}
void clearSW()//暂且不需要看
{
	for (int k = 0; k < ct1; k++)
	{
		p = 0;
		for (int i = 0; st[k][i]; i++) {
			temp = st[k][i] - '0';
			if (!Trie[p][temp])
				Trie[p][temp] = ++pos;//可以再优化
			p = Trie[p][temp];
		}
		Freqc[p] = 0;
	}

}

int cmp(const void* a, const void* b)//暂且不需要看
{
	return *(int*)b - *(int*)a;
}
int main()
{
	auto t1 = clock();
	N = 10000, M = 16;
	FILE* fp = fopen("sample.txt", "r");//问题主要是该读入的东西读入完后又读了些新的
	ll=(int)fread(s, sizeof(char), SIZE * 7, fp);//这里读入sample
	fclose(fp);//断点可以设置在这里，剩下的程序不用看了，原文本中sample以“reply\n\nmathew"结尾，程序已经读入了（在字符数组角标46498处左右读完，数组我开得比较贴合这个数字，调试时滑倒底再倒回去一点就行了）
	FILE *out = fopen("temp.txt","w");
    int i=0;
    while(i<ll){
        fputc(s[i++],out);
    }
    fclose(out);
    /*
	{
	M = atoi(argv[1]);
	N = atoi(argv[2]);
	}
	*/
	// getSW();

	// FILE* gp = fopen("hashvalue.txt", "r");
	// for (int j = 0; j < 10000; j++)
	// {
	// 	fgets(hash[j], 129, gp);//貌似可以优化
	// 	fgetc(gp);
	// }
	// for (int i = 0; i < N; i++)
	// 	for (int j = 0; j < M; j++)
	// 	{
	// 		hash[i][j] -= '0';
	// 	}
	// fclose(gp); 
	// int nu = 0;
	// while (1)
	// {
	// 	if ((s[i] == ' ' || s[i] == '\n'))
	// 	{
	// 		if (flag)
	// 		{
	// 			i++;
	// 			continue;

	// 		}
	// 		else
	// 			break;
	// 	}

	// 	flag = 0;
	// 	id[0][nu++] = s[i];
	// 	i++;
	// }
    
	// while (i<=ll)
	// {
		// if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
		// {
		// 	temp = (s[i] <= 'Z') ? s[i] - 'A' : s[i] - 'a';
		// 	if (!Trie[p][temp])
		// 		Trie[p][temp] = ++pos;
		// 	p = Trie[p][temp];
		// }
		// else
		// {
		// 	Freqc[p]++;
		// 	VacFre[++VacNum] = p;
		// 	p = 0;
		// }
		// if (s[i] == '\f')
		// {

		// 	i++;
		// 	clearSW();//结算
		// 	qsort(Freqc, 1000010, sizeof(Freqc[0]), cmp);
		// 	for (int i = 0; i < N; i++)
		// 	{
		// 		for (int cl = 0; cl < M; cl++)
		// 		{
		// 			if (hash[i][cl])
		// 			{
		// 				ar[j][cl] += Freqc[i];
		// 			}
		// 			else
		// 			{
		// 				ar[j][cl] -= Freqc[i];
		// 			}
		// 		}
		// 	}
		// 	for (int cl = 0; cl < M; cl++)
		// 	{
		// 		if (ar[j][cl] > 0)
		// 			ar[j][cl] = 1;
		// 		else
		// 			ar[j][cl] = 0;
		// 	}
		// 	//			memset(Trie, 0, sizeof(Trie));
		// 	memset(Freqc, 0, sizeof(Freqc));//为下一次做准备
		// 	j++; if (j == 10)
		// 	{
		// 		for (int p = i - 10; p < i + 10; p++)
		// 		{
		// 			putchar(s[p]);
		// 		}
		// 	}
			
		// 	int flag = 1, nu = 0;
		// 	while (s[i])//可以试试修改
		// 	{

		// 		if ((s[i] == ' ' || s[i] == '\n'))
		// 		{
		// 			if (flag)
		// 			{
		// 				i++;
		// 				continue;

		// 			}
		// 			else
		// 				break;
		// 		}

		// 		flag = 0;
		// 		id[j][nu++] = s[i];
		// 		i++;

		// 	}

		// }

		
		// i++;

	// }
	// auto t2 = clock();
	// printf("%d\n", (int)(t2 - t1));
	/*
	for (i = 0; i < 5; i++)
	{
		printf("%d ", Sen[i].frequency);
		int l = Sen[i].sen[1];
		j = Sen[i].sen[0];
		while (s[j] == ' ' && j <= l) j++;
		for (; j <= l; j++)
		{
			putchar(s[j]);
		}
		puts("");
	}
	freopen("results.txt", "w", stdout);
	*/
	

	return 0;
}