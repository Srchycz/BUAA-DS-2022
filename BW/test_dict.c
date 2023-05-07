#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 18000
#define M 3000
#pragma GCC optimize("Ofast")
typedef struct{
    double sim;
    int id;
}Text;
FILE *IN,*OUT;
Text al[N];
int NUM;
int trie[1200000][26],ed[1200000],tot=0,cnt=0,deg[1200000];
char tit[N][30];
int sum[N],tnk[N][M],dn[M];
int key[M],k_p;
void Insert(char*);
int Find(char*);
int lc(int);
void Extract();
void Init();
int Search(int);
int cmp(const void *a,const void *b){
    return *(int*)a-*(int*)b;
}
int cmp2(const void *a,const void *b){
    Text A=*(Text*)a,B=*(Text*)b;
    if(A.sim==B.sim) return A.id-B.id;
    if(A.sim<B.sim) return 1;
    return -1;
}
int main(){
    Init();
    IN=fopen("article.txt","r");
    OUT=fopen("tries.c","w");
    fprintf(OUT,"%d\n",tot);
    for(int i=0;i<=tot;++i){
        fprintf(OUT,"%d ",deg[i]);
        for(int j=0;j<26;++j){
            if(trie[i][j]) 
                fprintf(OUT,"%d %d ",j,trie[i][j]);
        }
        fputc('\n',OUT);
    }
    int ans=0;
    for(int i=1;i<=tot;++i){
        fprintf(OUT,"%d\n",ed[i]);
    }
    fclose(IN),fclose(OUT);
    return 0;
}
inline void Insert(char *s){
    int p=0;
    for(int i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) trie[p][ch]=++tot,++deg[p];
        p=trie[p][ch];
    }
    ed[p]=++cnt;
}
inline int Find(char *s){
    int p=0;
    for(int i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) return 0;
        p=trie[p][ch];
    }
    return ed[p];
}
inline void Extract(char *s){
    int p=0;
    for(int i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) return;
        p=trie[p][ch];
    }
    ed[p]=0;
}
inline void Init(){
    char temp[50];
    IN=fopen("dictionary.txt","r");
    fscanf(IN,"%s",temp);
    while (fscanf(IN,"%s",temp)!=EOF) Insert(temp);
    fclose(IN);
    IN=fopen("stopwords.txt","r");
    while(fscanf(IN,"%s",temp)!=EOF) Extract(temp);
    fclose(IN);
}
inline int Search(int aim){
    int l=1,r=k_p;
    while (l<r){
        int mid=(l+r+1)>>1;
        if(key[mid]>aim) r=mid-1;
        else l=mid;
    }
    return (key[l]==aim)?l:0;
}
inline int lc(int c){
    if(c>='A'&&c<='Z') return c+32;
    return c;
}