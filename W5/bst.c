#include<stdio.h>//简单BST
typedef struct node{
    int ls,rs,fa;
    int v;
} Node;
Node t[100000];
int tot;
void Insert(int k){
    if(tot==0){
        t[++tot].v=k;
        return;
    }
    int p=1,u=1;
    while (u){
        p=u;
        if(k<t[u].v) u=t[u].ls;
        else u=t[u].rs;
    }

    t[++tot].v=k;
    t[tot].fa=p;
    if(k<t[p].v) t[p].ls=tot;
    else t[p].rs=tot;
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
    int n;
    scanf("%d",&n);
    while (n--){
        int a;
        scanf("%d",&a);
        Insert(a);
    }
    dfs(1,1);
    return 0;
}