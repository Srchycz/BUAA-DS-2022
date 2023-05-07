#include<stdio.h>
typedef struct node{
    int ls,rs,fa;
    int v,cnt;
} Node;
Node t[100000];
int tot;
int ans=0;
int temp[1000],w[1000],maxx=0,m=0;
void Insert(int k){
    if(tot==0){
        t[++tot].v=k;
        t[tot].cnt=1;
        return;
    }
    int p=1,u=1;
    while (u){
        p=u;
        ++ans;
        if(k<t[u].v) u=t[u].ls;
        else if(k>t[u].v) u=t[u].rs;
        else if(k==t[u].v) break;
    }
    if(u==0){
        t[++tot].v=k;
        t[tot].fa=p,t[tot].cnt=1;
        if(k<t[p].v) t[p].ls=tot;
        else t[p].rs=tot;
    }
    else t[u].cnt++;
}
void dfs(int now,int dep){
    temp[dep]=t[now].v;
    if(t[now].cnt>maxx){
        for(int i=1;i<=dep;++i)
            w[i]=temp[i];
        maxx=t[now].cnt;
        m=dep;
    }
    if(t[now].ls) dfs(t[now].ls,dep+1);
    if(t[now].rs) dfs(t[now].rs,dep+1);
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int x;
        scanf("%d",&x);
        Insert(x);
    }
    printf("%d\n",ans);
    dfs(1,1);
    for(int i=1;i<=m;++i){
        printf("%d ",w[i]);
    }
    puts("");
    return 0;
}