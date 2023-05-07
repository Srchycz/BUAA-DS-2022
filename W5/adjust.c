#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int son[3];
}Node;
typedef struct{
    int id;
    int sum;
}Trans;
Node t[2000];
Trans a[200];
int rt;
int vis[2000];
int val[200],cnt;
void BFS(){
    int q[2000],l=1,r=1;
    q[r++]=rt,vis[0]=1;
    while (r-l){
        int now=q[l++];
        vis[now]=1;
        for(int i=0;i<3;++i){
            if(!vis[t[now].son[i]])
                q[r++]=t[now].son[i];
        }
        if(now<100) val[++cnt]=now;
    }
}
int cmp(const void *a,const void *b){
    Trans A=*(Trans*)a,B=*(Trans*)b;
    if(A.sum==B.sum) return A.id-B.id;
    return B.sum-A.sum;
}
int main(){
    scanf("%d",&rt);
    int now=rt;
    while (now!=-1){
        t[now].son[0]=0;
        t[now].son[1]=0;
        t[now].son[2]=0;
        int x,u=0;
        scanf("%d",&x);
        while (x!=-1){
            t[now].son[u++]=x;
            scanf("%d",&x);
        }
        scanf("%d",&now);
    }
    BFS();
    for(int i=1;i<=cnt;++i)
        scanf("%d %d",&a[i].id,&a[i].sum);
    qsort(a+1,cnt,sizeof(Trans),cmp);
    for(int i=1;i<=cnt;++i){
        printf("%d->%d\n",a[i].id,val[i]);
    }
    return 0;
}