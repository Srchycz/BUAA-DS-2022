#include<stdio.h>
#include<string.h>
#define N 100000
FILE *IN;
char STA[600][50];
int p=1,cnt;
int head[N],ver[N],edge[N],nxt[N],tot;
int rhash[N],vis[N],back[N],via[N];
int ans[N],ansvia[N];
int Find(char *s){
    for(int i=1;i<p;++i){
        if(strcmp(s,STA[i])==0)
            return i;
    }
    return 0;
}
void add(int x,int y,int z){
    ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
    edge[tot]=z;
}
void bfs(int start,int aim){
    int q[N],l=1,r=1;
    q[r++]=start;
    vis[start]=1;
    while (r-l){
        int now=q[l++];
        for(int i=head[now];i;i=nxt[i]){
            int y=ver[i];
            if(vis[y]) continue;
            q[r++]=y;
            back[y]=now;
            via[y]=edge[i];
            vis[y]=1;
            if(y==aim){
                int u=y;
                while (u!=start){
                    ans[++cnt]=u;
                    ansvia[cnt]=via[u];
                    u=back[u];
                }
                return;
            }
        }
    }
}
int main(){
    IN=fopen("bgstations.txt","r");
    int n;
    fscanf(IN,"%d",&n);
    for(int i=1;i<=n;++i){
        int k,m,last=0;
        fscanf(IN,"%d%d",&k,&m);
        for(int j=1;j<=m;++j){
            int flag;
            fscanf(IN,"%s%d",STA[p],&flag);
            int h=Find(STA[p]);
            if(h==0) h=p++;
            if(j>1){
                add(last,h,k),add(h,last,k);
            }
            last=h;
        }
    }
    char S[20],T[20];
    scanf("%s",S);
    scanf("%s",T);
    int hs=Find(S),ht=Find(T);
    bfs(hs,ht);
    printf("%s",S);
    // for(int i=cnt;i>=1;--i){
    //     printf("-(%d)-%s",ansvia[i],STA[ans[i]]);
    // }
    int d=1;
    for(int i=cnt;i>=1;--i){
        if(ansvia[i-1]==ansvia[i]){
            ++d;continue;
        }
        printf("-%d(%d)-%s",ansvia[i],d,STA[ans[i]]);
        d=1;
    }
    return 0;
}