#include<stdio.h>
int n,m;
int vis[1000];
int temp[1000];
int path[500][500],cnt;
int head[1000],ver[1000],tot,nxt[1000],edge[1000];
void add(int x,int y,int k){
    ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
    edge[tot]=k;
}
void Find(int now,int dep){
    if(now==n){
        ++cnt;
        for(int i=0;i<dep;++i)
            path[cnt][i]=temp[i];
        return;
    }
    vis[now]=1;
    for(int i=head[now];i;i=nxt[i]){
        int y=ver[i];
        if(!vis[y]){
            temp[dep]=edge[i];
            Find(y,dep+1);
        }
    }
    vis[now]=0;
}
int cmp(int a,int b){
    int i=0;
    while (path[a][i]&&path[b][i]) {
        if(path[a][i]<path[b][i]) return 0;
        if(path[a][i]>path[b][i]) return 1;
        ++i;
    }
    if(path[a][i]) return 1;
    return 0;
}
int main(){
    int rk[1000];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int x,y,id;
        scanf("%d%d%d",&id,&x,&y);
        ++x,++y,++id;
        add(x,y,id),add(y,x,id);
    }
    Find(1,0);
    for(int i=1;i<=cnt;++i) rk[i]=i;
    for(int i=1;i<=cnt;++i){
        int flag=1;
        for(int j=2;j<=cnt;++j){
            if(cmp(rk[j-1],rk[j])){
                rk[j-1]^=rk[j];
                rk[j]^=rk[j-1];
                rk[j-1]^=rk[j];
                flag=0;
            }
        }
        if(flag) break;
    }
    for(int i=1;i<=cnt;++i){
        int j=0;
        while (path[rk[i]][j]){
            printf("%d ",path[rk[i]][j]-1);
            ++j;
        }
        puts("");
    }
    return 0;
}
/*
6 8
1 0 1
2 1 2
3 2 3
4 2 4
5 3 5
6 4 5
7 0 5
8 0 1
*/