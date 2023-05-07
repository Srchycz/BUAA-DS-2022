#include<stdio.h>
#include<string.h>
int t[200][200];
int vis[200];
int n,m;
void add(int x,int y){
    t[x][y]=t[y][x]=1;
}
void dfs(int now){
    printf("%d ",now-1);
    vis[now]=1;
    for(int i=1;i<=n;++i){
        if(t[now][i]){
            if(!vis[i]) dfs(i);
        }
    }
}
void bfs(){
    int q[200],l=1,r=1;
    q[r++]=1;
    vis[1]=1;
    while (r-l){
        int now=q[l++];
        for(int i=1;i<=n;++i){
            if(t[now][i]){
                if(!vis[i]) q[r++]=i,vis[i]=1;
            }
        }
        printf("%d ",now-1);
    }
}
int main(){
    int k;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        ++x,++y;
        add(x,y);
    }
    scanf("%d",&k);
    ++k;
    memset(vis,0,sizeof vis);
    dfs(1);puts("");
    memset(vis,0,sizeof vis);
    bfs();puts("");
    memset(vis,0,sizeof vis);
    vis[k]=1,dfs(1);puts("");
    memset(vis,0,sizeof vis);
    vis[k]=1,bfs();puts("");
    return 0;
}