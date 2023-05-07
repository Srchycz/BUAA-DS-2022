#pragma GCC optimize("O3")
#include<stdio.h>//采用hash 而非二分+离散化
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 18000
#define M 3000
typedef struct{
    double sim;
    int id;
}Text;
FILE *IN,*OUT;
Text al[N];
int NUM;
int trie[1200000][26],ed[1200000],tot=0,cnt=0;
char tit[N][30];
int sum[N],tnk[N][M],dn[M];
int key[500000],k_p;
void Insert(char*);
int Find(char*);
int lc(int);
void Extract();
void Init();
int cmp2(const void *a,const void *b){
    Text A=*(Text*)a,B=*(Text*)b;
    if(A.sim==B.sim) return A.id-B.id;
    if(A.sim<B.sim) return 1;
    return -1;
}
int main(int argc,char *argv[]){
    Init();
    NUM=atoi(*(argv+1));
    for(int i=2;i<argc;++i){
        int k=Find(*(argv+i));
        key[k]=++k_p;
    }
    char temp[50];
    IN=fopen("article.txt","r");
    int c='\f';
    int txt_cnt=0,t=0;
    while (c!=-1){
        c=lc(c);
        if('a'<=c&&c<='z'){
            temp[t++]=c;
            c=fgetc(IN);
            continue;
        }
        if(t){
            temp[t]='\0';t=0;
            int k=Find(temp);
            if(!k){
                c=fgetc(IN);
                continue;
            }
            int hk=key[k];
            if(hk){
                dn[hk]+=(tnk[txt_cnt][hk]==0);
                ++tnk[txt_cnt][hk];
            }
            ++sum[txt_cnt];
        }
        if(c=='\f')
            fscanf(IN,"%s",tit[++txt_cnt]);
        c=fgetc(IN);
    }
    for(register int i=1;i<=txt_cnt;++i){
        al[i].id=i;
        for(register int j=1;j<=k_p;++j){
            if(!tnk[i][j]||!dn[j]) continue;
            double tf=(double)(tnk[i][j])/(double)(sum[i])*100;
            double idf=log10((double)(txt_cnt)/(double)(dn[j]));
            al[i].sim+=tf*idf;
        }
    }
    qsort(al+1,txt_cnt,sizeof(Text),cmp2);
    for(register int i=1;i<=5;++i){
        printf("%.6lf %d %s\n",al[i].sim,al[i].id,tit[al[i].id]);
    }
    OUT=fopen("results.txt","w");
    for(register int i=1;i<=NUM;++i){
        if(al[i].sim>0)
            fprintf(OUT,"%.6lf %d %s\n",al[i].sim,al[i].id,tit[al[i].id]);
    }
    fclose(IN),fclose(OUT);
    return 0;
}
inline void Insert(char *s){
    int p=0;
    for(register int i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) trie[p][ch]=++tot;
        p=trie[p][ch];
    }
    ed[p]=++cnt;
}
inline int Find(char *s){
    int p=0;
    for(register int i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) return 0;
        p=trie[p][ch];
    }
    return ed[p];
}
inline void Extract(char *s){
    int p=0;
    for(register int i=0;s[i]!='\0';++i){
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
inline int lc(int c){
    if(c>='A'&&c<='Z') return c+32;
    return c;
}