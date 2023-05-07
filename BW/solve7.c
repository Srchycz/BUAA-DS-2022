//手动内联
#pragma GCC optimize ("O3")
#pragma once
#pragma pack (16)
#include<stdio.h>
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
char dic[5000000];
char stw[50000];
double idf[N];
int sum[N],tnk[N][M],dn[M];
int key[500000],k_p;
int cmp(int,int);
int main(int argc,char *argv[]){
    for(int i='a';i<='z';++i){
        alpha[i]=i;
        alpha[i-32]=i;
    }
    char *str;
    IN=fopen("dictionary.txt","r");
    int m=fread(dic+1,sizeof(char),5000000,IN);
    register char *s=dic+1;
    int str_flag=0;
    while  (s<=dic+m){
        if (alpha[*s]){
            if(str_flag==0) str=s,str_flag=1;
            ++s;
            continue;
        }
        if(str_flag){
            *s='\0',str_flag=0;
            register int p=0;
            while(*str){
                int ch=*str-'a';
                if(trie[p][ch]==0) trie[p][ch]=++tot;
                p=trie[p][ch];
                ++str;
            }
            ed[p]=++cnt;
        }
        ++s;
    }
    fclose(IN);
    IN=fopen("stopwords.txt","r");
    int n=fread(stw+1,sizeof(char),50000,IN);
    s=stw+1,str_flag=0;
    while (s<=stw+n){
        if (alpha[*s]){
            if(str_flag==0) str=s,str_flag=1;
            ++s;
            continue;
        }
        if(str_flag){
            *s='\0',str_flag=0;
            register int p=0;
            while (*str){
                int ch=*str-'a';
                if(trie[p][ch]==0) break;
                p=trie[p][ch];
                ++str;
            }
            ed[p]=0;
        }
        ++s;
    }
    fclose(IN);
    NUM=0;
    s=*(argv+1);
    while (*s){
        NUM*=10;
        NUM+=*s-'0';
        ++s;
    }
    for(int i=2;i<argc;++i){
        int k;
        int p=0;
        char *argv_s=*(argv+i);
        while(*argv_s){
            int ch=*argv_s-'a';
            if(trie[p][ch]==0){p=0;break;}
            p=trie[p][ch];
            ++argv_s;
        }
        k=ed[p];
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
            int k,p=0;
            char *temp_p=temp;
            while(*temp_p){
            int ch=*temp_p-'a';
            if(trie[p][ch]==0){p=0;break;}
            p=trie[p][ch];
            ++temp_p;
            }
            k=ed[p];
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
        int now=++heaptot;
        while (now>1){
            if(sim[heap[now>>1]]>=sim[i])
                heap[now]=heap[now>>1],now>>=1;
            else break;
        }
        heap[now]=i;
        if(heaptot>NUM){
            int now=1,nxt=2;
            int k=heap[heaptot--];
            while (nxt<=heaptot){
                if(nxt<heaptot&&!cmp(heap[nxt],heap[nxt|1])) nxt|=1;
                if(!cmp(k,heap[nxt])) heap[now]=heap[nxt],now=nxt,nxt<<=1;
                else break;
            }
            heap[now]=k;
        }
    }
    while (heaptot){
        rk[heaptot]=heap[1];
        int now=1,nxt=2;
        int k=heap[heaptot--];
        while (nxt<=heaptot){
            if(nxt<heaptot&&!cmp(heap[nxt],heap[nxt|1])) nxt|=1;
            if(!cmp(k,heap[nxt])) heap[now]=heap[nxt],now=nxt,nxt<<=1;
            else break;
        }
        heap[now]=k;
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
inline int cmp(int a,int b){
    if(sim[a] == sim[b])
        return a > b;
    return sim[a] < sim[b];
}//a<b返回1   a>b返回0