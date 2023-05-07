#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 1000
int q[N],sum;
char name[N][30];
int cnt=1;
int t[N][N];
int head[N],ver[N],nxt[N],tot;
void add(int x,int y){
    if(t[x][y]) return;
    t[x][y]=1;
    ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
}
int Find(int aim){
    for(int i=1;i<cnt;++i){
        if(strcmp(name[aim],name[i])==0)
        return i;
    }
    return 0;
}
int main(){
    int opt;
    while (scanf("%d",&opt)!=EOF){
        if(opt==8){
            scanf("%s",name[cnt]);
            int k=Find(cnt);
            if(k==0) k=cnt++;
            if(sum==0) q[++sum]=k;
            else q[++sum]=k,add(q[sum-1],k);
        }
        else --sum;
    }
    for(int i=1;i<cnt;++i){
        int a[N],temp=0;
        for(int j=head[i];j;j=nxt[j]){
            a[++temp]=ver[j];
        }
        if(temp){
            printf("%s:%s",name[i],name[a[temp]]);
            for(int j=temp-1;j>0;--j){
                printf(",%s",name[a[j]]);
            }
            puts("");
        }
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