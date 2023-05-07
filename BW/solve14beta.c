//尝试部署循环展开
#pragma GCC optimize ("Ofast")
#pragma pack (16)
#include<stdio.h>
#include <sys/mman.h>
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
char a[34900000];
char dic[4800000];
char stw[4000];
int sum[N],tnk[N][M],dn[M];
int key[500000],k_p;
double idf[N];
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
    char *data = NULL;
    int fd=open("file.txt",O_RDONLY);
    long size = lseek(fd, 0, SEEK_END);
    data = (char *)mmap(NULL,34900000,PROT_READ, MAP_PRIVATE,fd,0);
    register char *c=&a[0];
    register char* maxn=a+u;
    while (c<=maxn){
        switch(alpha[*c]){
            case 0:{
                if(t){
                    temp[t]='\0';t=0;
                    int k=Find(temp);
                    if(!k) break;
                    int hk=key[k];
                    if(hk){
                        dn[hk]+=(tnk[txt_cnt][hk]==0);
                        ++tnk[txt_cnt][hk];
                    }
                    ++sum[txt_cnt];
                }
                break;
            }
            case 1:{
                ++c;
                while (*c=='\n'||*c=='\r') ++c;
                til[++txt_cnt]=c;
                while (*c!='\n'&&*c!='\r') ++c;
                *c='\0';
                break;
            }
            default:{
                temp[t++]=alpha[*c];
                break;
            }
        }
        ++c;
    }
    double log_t=log10((double)txt_cnt);
    for(register int i=1;i<=k_p;++i){
        if(dn[i]==0) continue;
        idf[i]=log_t-log10((double)(dn[i]));
    }
    for(register int i=1;i<=txt_cnt;++i){
        double tf1=0,tf2=0,tf3=0,tf4=0,tf5=0,tf6=0,tf7=0,tf8=0;
        for(register int j=0;j+8<=k_p;j+=8){
            tf1+=(tnk[i][j+1])*idf[j+1];
            tf2+=(tnk[i][j+2])*idf[j+2];
            tf3+=(tnk[i][j+3])*idf[j+3];
            tf4+=(tnk[i][j+4])*idf[j+4];
            tf5+=(tnk[i][j+5])*idf[j+5];
            tf6+=(tnk[i][j+6])*idf[j+6];
            tf7+=(tnk[i][j+7])*idf[j+7];
            tf8+=(tnk[i][j+8])*idf[j+8];
        }
        switch(k_p&7){
            case 7:tf7+=(tnk[i][k_p-6])*idf[k_p-6];
            case 6:tf6+=(tnk[i][k_p-5])*idf[k_p-5];
            case 5:tf5+=(tnk[i][k_p-4])*idf[k_p-4];
            case 4:tf4+=(tnk[i][k_p-3])*idf[k_p-3];
            case 3:tf3+=(tnk[i][k_p-2])*idf[k_p-2];
            case 2:tf2+=(tnk[i][k_p-1])*idf[k_p-1];
            case 1:tf1+=(tnk[i][k_p])*idf[k_p];
        }
        sim[i]+=(tf1+tf2+tf3+tf4+tf5+tf6+tf7+tf8)*100/sum[i];
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
    for(int i='a';i<='z';++i){
        alpha[i]=i;
        alpha[i-32]=i;
    }
    alpha['\f']=1;
    char *temp;
    IN=fopen("dictionary.txt","r");
    int m=fread(dic+1,sizeof(char),4800000,IN);
    register char *s=dic+1;
    register char *lim=dic+m;
    int t=0;
    while  (s<=lim){
        if (alpha[*s]){
            if(t==0) temp=s,t=1;
            ++s;
            continue;
        }
        if(t){
            *s='\0';t=0;
            Insert(temp);
        }
        ++s;
    }
    fclose(IN);
    IN=fopen("stopwords.txt","r");
    int n=fread(stw+1,sizeof(char),4000,IN);
    s=stw+1,t=0;
    lim=stw+n;
    while (s<=lim){
        if (alpha[*s]){
            if(t==0) temp=s,t=1;
            ++s;
            continue;
        }
        if(t){
            *s='\0';t=0;
            Filter(temp);
        }
        ++s;
    }
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
        if(cmp(heap[now>>1],d)) break;
        heap[now]=heap[now>>1],now>>=1;
    }
    heap[now]=d;
}
inline void Extract(){
    int now=1,nxt=2;
    int k=heap[heaptot--];
    while (nxt<=heaptot){
        if(nxt<heaptot&&!cmp(heap[nxt],heap[nxt|1])) nxt|=1;
        if(cmp(k,heap[nxt])) break;
        heap[now]=heap[nxt],now=nxt,nxt<<=1;
    }
    heap[now]=k;
}
