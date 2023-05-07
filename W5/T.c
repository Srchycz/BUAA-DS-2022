#include<stdio.h>//简单BST
#define N 100000

typedef struct node{
    int ls,rs,fa;
    int v;
    int cnt;
} Node;

Node t[N];
int tot, rt;
void Insert(int k){//插入操作
    if(tot==0){
        t[++tot].v=k;
        rt=tot;//rt保存bst的根的下标
        return;
    }
    int p=rt,u=rt;
    while (u){
        p=u;
        if(k==t[u].v){
            ++ t[u].cnt;
            return;
        }
        else if(k<t[u].v) u=t[u].ls;
        else u=t[u].rs;
    }

    t[++tot].v=k;
    t[tot].fa=p;
    t[tot].cnt=1;
    t[tot].ls=0;
    t[tot].rs=0;
    if(k<t[p].v) t[p].ls=tot;
    else t[p].rs=tot;
}
int Find(int k) {//存在返回1 反之返回0
    if(tot==0){
        Printf("Empty!\n");
        return 0;
    }
    int u=rt;
    while (u) {
        if(k==t[u].v) return 1;
        if(k>t[u].v)
            u=t[u].rs;
        else
            u=t[u].ls;
    }
    return 0;
}
void dfs(int idx,int dep){
    int flag=((t[idx].ls)||(t[idx].rs));
    if(t[idx].ls) dfs(t[idx].ls,dep+1);
    if(t[idx].rs) dfs(t[idx].rs,dep+1);
    if(flag==0){
        printf("%d %d\n",t[idx].v,dep);
    }
}
int main(){
    return 0;
}