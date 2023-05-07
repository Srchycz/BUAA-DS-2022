#pragma GCC optimize("O3")//尝试读入trie而非建立trie
#include<stdio.h>
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
Text al[N],heap[N];
Text rk[N];
int NUM,heaptot=0;
int trie[1200000][26],ed[1200000],tot=0,cnt=0;
char tit[N][30];
int sum[N],tnk[N][M],dn[M];
int key[500000],k_p;
int alpha[500];
int Find(char*);
void Init();
int cmp(Text*,Text*);
void Insert_Heap(Text* d);
void Extract();
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
        if(alpha[c]){
            if(c<='Z') c+=32;
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
        Insert_Heap(&al[i]);
        if(heaptot>NUM) Extract();
    }
    while (heaptot){
        rk[heaptot]=heap[1];
        Extract();
    }
    for(register int i=1;i<=5;++i)
        printf("%.6lf %d %s\n",rk[i].sim,rk[i].id,tit[rk[i].id]);
    OUT=fopen("results.txt","w");
    for(register int i=1;i<=NUM;++i){
        if(rk[i].sim<=0) break;
        fprintf(OUT,"%.6lf %d %s\n",rk[i].sim,rk[i].id,tit[rk[i].id]);
    }
    fclose(IN),fclose(OUT);
    system("pause");
    return 0;
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
inline void Init(){
    for(int i='A';i<='Z';++i)
        alpha[i]=1;
    for(int i='a';i<='z';++i)
        alpha[i]=1;
    IN=fopen("tries.c","r");
    char temp[10];
    fscanf(IN,"%s",temp);
    fscanf(IN,"%d",&tot);
    for(register int i=0;i<=tot;++i){
        int t;
        fscanf(IN,"%d",&t);
        for(register int j=0;j<t;++j){
            int idx;
            fscanf(IN,"%d",&idx);
            fscanf(IN,"%d",&trie[i][idx]);
        }
    }
    for(register int i=1;i<=tot;++i)
        fscanf(IN,"%d",&ed[i]);
    fclose(IN);
}
inline int cmp(Text* a,Text* b){
    if(a->sim == b->sim)
        return a->id > b->id;
    return a->sim < b->sim;
}//a<b返回1   a>b返回0
inline void Insert_Heap(Text* d){
    int now=++heaptot;
    while (now>1){
        if(!cmp(&heap[now>>1],d))
            heap[now]=heap[now>>1],now>>=1;
        else break;
    }
    heap[now]=*d;
}
inline void Extract(){
    int now=1,nxt=2;
    Text k=heap[heaptot--];
    while (nxt<=heaptot){
        if(nxt<heaptot&&!cmp(&heap[nxt],&heap[nxt|1])) nxt|=1;
        if(!cmp(&k,&heap[nxt])) heap[now]=heap[nxt],now=nxt,nxt<<=1;
        else break;
    }
    heap[now]=k;
}