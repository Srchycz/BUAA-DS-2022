//指针优化寻址
#pragma GCC optimize("Ofast")
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 18000
#define M 3000
double sim[N];
int rk[N];
int heap[N];
FILE *IN,*OUT;
int NUM,heaptot=0;
int trie[1200000][26],ed[1200000],tot=0,cnt=0;
char *til[N];
int alpha[200];
char a[35000020];
int sum[N],tnk[N][M],dn[M];
int key[500000],k_p;
void Insert(char*);
int Find(char*);
void Filter();
void Init();
int cmp(int,int);
void Insert_Heap(int d);
void Extract();
int main(int argc,char *argv[]){
    Init();
    NUM=atoi(*(argv+1));
    for(int i=2;i<argc;++i){
        int k=Find(*(argv+i));
        key[k]=++k_p;
    }
    char temp[50];
    a[0]='\f';
    IN=fopen("article.txt","rt");
    int txt_cnt=0,t=0;
    int u=fread(a+1,sizeof(char),35000000,IN);
    register char *c=&a[0];
    while (c<=a+u){
        if(alpha[*c]>0){
            temp[t++]=alpha[*c];
            ++c;
            continue;
        }
        if(t){
            temp[t]='\0';t=0;
            int k=Find(temp);
            if(!k){
                ++c;
                continue;
            }
            int hk=key[k];
            if(hk){
                dn[hk]+=(tnk[txt_cnt][hk]==0);
                ++tnk[txt_cnt][hk];
            }
            ++sum[txt_cnt];
        }
        if(*c=='\f'){
            ++c;
            while (*c=='\n'||*c=='\r') ++c;
            til[++txt_cnt]=c;
            while (*c!='\n'&&*c!='\r') ++c;
            *c='\0';
        }
        ++c;
    }
    for(register int i=1;i<=txt_cnt;++i){
        for(register int j=1;j<=k_p;++j){
            if(!tnk[i][j]||!dn[j]) continue;
            double tf=(double)(tnk[i][j])/(double)(sum[i])*100;
            double idf=log10((double)(txt_cnt)/(double)(dn[j]));
            sim[i]+=tf*idf;
        }
        Insert_Heap(i);
        if(heaptot>NUM) Extract();
    }
    while (heaptot){
        rk[heaptot]=heap[1];
        Extract();
    }
    for(register int i=1;i<=5;++i)
        printf("%.6lf %d %s\n",sim[rk[i]],rk[i],til[rk[i]]);
    OUT=fopen("results.txt","w");
    for(register int i=1;i<=NUM;++i){
        if(sim[rk[i]]<=0) break;
        fprintf(OUT,"%.6lf %d %s\n",sim[rk[i]],rk[i],til[rk[i]]);
    }
    fclose(IN),fclose(OUT);
    return 0;
}
inline void Insert(char *s){
    int p=0;
    while(*s){
        int ch=*s-'a';
        if(trie[p][ch]==0) trie[p][ch]=++tot;
        p=trie[p][ch];
        ++s;
    }
    ed[p]=++cnt;
}
inline int Find(char *s){
    int p=0;
    while(*s){
        int ch=*s-'a';
        if(trie[p][ch]==0) return 0;
        p=trie[p][ch];
        ++s;
    }
    return ed[p];
}
inline void Filter(char *s){
    int p=0;
    while (*s){
        int ch=*s-'a';
        if(trie[p][ch]==0) return;
        p=trie[p][ch];
        ++s;
    }
    ed[p]=0;
}
inline void Init(){
    for(int i='a';i<='z';++i)
        alpha[i]=i;
    for(int i='A';i<='Z';++i)
        alpha[i]=i+32;
    char temp[50];
    IN=fopen("dictionary.txt","r");
    fscanf(IN,"%s",temp);
    while (fscanf(IN,"%s",temp)!=EOF) Insert(temp);
    fclose(IN);
    IN=fopen("stopwords.txt","r");
    while(fscanf(IN,"%s",temp)!=EOF) Filter(temp);
    fclose(IN);
}
inline int cmp(int a,int b){
    if(sim[a] == sim[b])
        return a > b;
    return sim[a] < sim[b];
}//a<b返回1   a>b返回0
inline void Insert_Heap(int d){
    int now=++heaptot;
    while (now>1){
        if(!cmp(heap[now>>1],d))
            heap[now]=heap[now>>1],now>>=1;
        else break;
    }
    heap[now]=d;
}
inline void Extract(){
    int now=1,nxt=2;
    int k=heap[heaptot--];
    while (nxt<=heaptot){
        if(nxt<heaptot&&!cmp(heap[nxt],heap[nxt|1])) nxt|=1;
        if(!cmp(k,heap[nxt])) heap[now]=heap[nxt],now=nxt,nxt<<=1;
        else break;
    }
    heap[now]=k;
}