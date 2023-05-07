#pragma GCC optimize("Ofast")
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 18000
#define M 3000
typedef unsigned int uint;
typedef struct{
    double sim;
    int id;
}Text;
FILE *IN,*OUT;
Text al[N];
int NUM;
uint trie[5000000][26],ed[5000000],tot=0,cnt=0;
char tit[N][30];
uint sum[N],tnk[N][M],dn[M];
uint key[M],k_p;
double idf[M];
void Insert(char*);
uint Find(char*);
int lc(int);
void Extract();
void Init();
uint Search(uint);
int cmp(const void *a,const void *b){
    return *(int*)a-*(int*)b;
}
int cmp2(const void *a,const void *b){
    Text A=*(Text*)a,B=*(Text*)b;
    if(A.sim==B.sim) return A.id-B.id;
    if(A.sim<B.sim) return 1;
    return -1;
}
int main(int argc,char *argv[]){
    Init();
    NUM=atoi(*(argv+1));
    for(register uint i=2;i<argc;++i){
        uint k=Find(*(argv+i));
        if(k) key[++k_p]=k;
    }
    qsort(key+1,k_p,sizeof(int),cmp);
    char temp[50];
    IN=fopen("article.txt","r");
    int c='\f';
    int txt_cnt=0,t=0;
    do{
        c=lc(c);
        if('a'<=c&&c<='z'){
            temp[t++]=c;
            continue;
        }
        if(t){
            temp[t]='\0';t=0;
            uint k=Find(temp);
            if(!k) continue;
            uint hk=Search(k);
            if(hk){
                dn[hk]+=(tnk[txt_cnt][hk]==0);
                ++tnk[txt_cnt][hk];
            }
            ++sum[txt_cnt];
        }
        if(c=='\f')
            fscanf(IN,"%s",tit[++txt_cnt]);
    }while ((c=fgetc(IN))!=EOF);
    if(t){
        t=0;
        uint k=Find(temp);
        if(k){
            uint hk=Search(k);
            if(hk){
                dn[hk]+=(tnk[txt_cnt][hk]==0);
                ++tnk[txt_cnt][hk];
            }
            ++sum[txt_cnt];
        }
    }
    for(register uint j=1;j<=k_p;++j){
        if(dn[j]) idf[j]=log10((double)(txt_cnt)/(double)(dn[j]));
        else dn[j]=0;
    }
    for(register uint i=1;i<=txt_cnt;++i){
        al[i].id=i;
        for(register uint j=1;j<=k_p;++j){
            if(!tnk[i][j]) continue;
            double tf=(double)(tnk[i][j])/(double)(sum[i])*100;
            al[i].sim+=tf*idf[j];
        }
    }
    qsort(al+1,txt_cnt,sizeof(Text),cmp2);
    for(register uint i=1;i<=5;++i){
        printf("%.6lf %d %s\n",al[i].sim,al[i].id,tit[al[i].id]);
    }
    OUT=fopen("results.txt","w");
    for(register uint i=1;i<=NUM;++i){
        if(al[i].sim<=0) break;
        fprintf(OUT,"%.6lf %d %s\n",al[i].sim,al[i].id,tit[al[i].id]);
    }
    fclose(IN),fclose(OUT);
    return 0;
}
inline void Insert(char *s){
    uint p=0;
    for(register uint i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) trie[p][ch]=++tot;
        p=trie[p][ch];
    }
    ed[p]=++cnt;
}
inline uint Find(char *s){
    uint p=0;
    for(register uint i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) return 0;
        p=trie[p][ch];
    }
    return ed[p];
}
inline void Extract(char *s){
    int p=0;
    for(register uint i=0;s[i]!='\0';++i){
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
inline uint Search(uint aim){
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