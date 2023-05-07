#include<stdio.h>//time ： 1.033s
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
int trie[5000000][26],ed[5000000],tot=0,cnt=0;
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
int main(int argc,char *argv[]){
    Init();
    NUM=atoi(*(argv+1));
    for(int i=2;i<argc;++i){
        int k=Find(*(argv+i));
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
            int k=Find(temp);
            if(!k) continue;
            int hk=Search(k);
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
        int k=Find(temp);
        if(k){
            int hk=Search(k);
            if(hk){
                dn[hk]+=(tnk[txt_cnt][hk]==0);
                ++tnk[txt_cnt][hk];
            }
            ++sum[txt_cnt];
        }
    }
    for(int i=1;i<=txt_cnt;++i){
        al[i].id=i;
        for(int j=1;j<=k_p;++j){
            if(!tnk[i][j]||!dn[j]) continue;
            double tf=(double)(tnk[i][j])/(double)(sum[i])*100;
            double idf=log10((double)(txt_cnt)/(double)(dn[j]));
            // printf("%d %d:%.6lf\n",txt_cnt,dn[j],idf);
            al[i].sim+=tf*idf;
        }
    }
    for(int i=1;i<=k_p;++i){
        printf("%d\n",dn[i]);
    }
    qsort(al+1,txt_cnt,sizeof(Text),cmp2);
    for(int i=1;i<=5;++i){
        printf("%.6lf %d %s\n",al[i].sim,al[i].id,tit[al[i].id]);
    }
    OUT=fopen("results.txt","w");
    for(int i=1;i<=NUM;++i){
        if(al[i].sim>0)
            fprintf(OUT,"%.6lf %d %s\n",al[i].sim,al[i].id,tit[al[i].id]);
    }
    fclose(IN),fclose(OUT);
    return 0;
}
inline void Insert(char *s){
    int p=0;
    for(int i=0;s[i]!='\0';++i){
        int ch=s[i]-'a';
        if(trie[p][ch]==0) trie[p][ch]=++tot;
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