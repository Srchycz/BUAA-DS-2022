#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
    int opt;
    char name[30];
}OPT;
typedef struct{
    int p;
    int son[25];
}Node;
Node t[600];
OPT a[600];
char h[600][30];
int tot,cnt;
int q[1000],sum;
int od[1000],od_p;
int vis[600];
int uni[600];
void add(int x,int y){
    t[x].son[++t[x].p]=y;
}
void Swap(int idx1,int idx2){
    char temp[30];
    strcpy(temp,h[idx1]);
    strcpy(h[idx1],h[idx2]);
    strcpy(h[idx2],temp);
}
void Bubble_Sort(){
    for(int i=1;i<=cnt;++i){
        int flag=0;
        for(int j=1;j<cnt;++j){
            if(strcmp(h[j],h[j+1])>0){
                Swap(j,j+1);
                flag=1;
            }
        }
        if(!flag) break;
    }
}
int Find(char *s){
    int l=1,r=cnt;
    while (l<r){
        int mid=(l+r+1)>>1;
        if(strcmp(h[mid],s)<=0) l=mid;
        else r=mid-1;
    }
    return l;
}
int main(){
    while (scanf("%d",&a[++tot].opt)!=EOF){
        if(a[tot].opt==8){
            scanf("%s",a[tot].name);
            strcpy(h[++cnt],a[tot].name);
        }
    }
    Bubble_Sort();
    for(int i=1;i<=tot;++i){
        if(a[i].opt==8){
            int k=Find(a[i].name);
            q[++sum]=k;
            od[++od_p]=k;
            if(sum>1) add(q[sum-1],q[sum]);
        }
        else --sum;
    }
    for(int i=1;i<=od_p;++i){
        int now=od[i];
        if(vis[now]) continue;
        vis[now]=1;
        if(t[now].p==0) continue;
        memset(uni,0,sizeof uni);
        printf("%s:%s",h[now],h[t[now].son[1]]);
        uni[t[now].son[1]]=1;
        for(int j=2;j<=t[now].p;++j){
            if(uni[t[now].son[j]]) continue;
            printf(",%s",h[t[now].son[j]]);
        }
        puts("");
    }
    return 0;
}
/*
8 main
8 input
0
8 mysqrt
0
8 findA
0
8 findB
8 area
8 mysin
0
8 mycos
0
8 mysqrt
0
0
0
8 findC
8 area
8 mysin
0
0
8 mysqrt
8 max
0
0
0
8 output
0
0
*/