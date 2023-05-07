#include<stdio.h>
#define P 13331
#define N 100000
typedef unsigned long long int64;
FILE *IN;
int head[N],ver[N],edge[N],nxt[N],tot;
int64 key[N];
char STA[400][400];
int rhash[N],vis[N],back[N],via[N];
int ans[N],ansvia[N],p,cnt;
void add(int x,int y,int z){
    ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
    edge[tot]=z;
}
int64 hash(char *s){
    int64 res=0;
    for(int i=0;s[i]!='\0';++i){
        res*=P;
        res+=s[i];
    }
    return res;
}
int f(int64 a){
    const int64 temp=1e10;
    return a%1000*100+a/temp%100;
}
void bfs(int start,int aim){
    int q[N],l=1,r=1;
    q[r++]=start;
    vis[start]=1;
    while (r-l){
        int now=q[l++];
        vis[now]=1;
        for(int i=head[now];i;i=nxt[i]){
            int y=ver[i];
            if(vis[y]) continue;
            q[r++]=y;
            back[y]=now;
            via[y]=edge[i];
            if(y==aim){
                int u=now;
                while (back[u]!=start){
                    ans[++p]=back[u];
                    ansvia[p]=via[u];
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
    char s[200],t[200];
    fscanf(IN,"%d",&n);
    for(int i=1;i<=n;++i){
        int k,m;
        int last=0;
        fscanf(IN,"%d%d",&k,&m);
        for(int j=1;j<=m;++j){
            int u;
            fscanf(IN,"%s%d",STA[cnt],&u);
            // printf("%s\n",STA[cnt]);
            int64 h=hash(STA[cnt]);
            int hlow5=f(h);//(h+1)%N-1;
            if(last==0){
                last=hlow5;
                continue;
            }
            if(!key[hlow5]){
                key[hlow5]=h;
                rhash[hlow5]=cnt;
                ++cnt;
            }
            if(key[hlow5]!=h){
                printf("conflict:%llu %llu\n",key[hlow5],h);
                printf("%s %s\n",STA[rhash[hlow5]],STA[cnt]);
            }
            add(last,hlow5,k);
            add(hlow5,last,k);
            last=hlow5;
        }
    }
    scanf("%s%s",s,t);
    int64 hs=hash(s),ts=hash(t);
    int hslow5=f(hs),tslow5=f(ts);
    bfs(hslow5,tslow5);
    printf("%d\n",p);
    printf("%s-",s);
    for(int i=p;i>=1;--i){
        printf("%s(%d)-",STA[rhash[ans[i]]],ansvia[i]);
    }
    printf("%s\n",t);
    for(int i=head[hslow5];i;i=nxt[i]){
        printf("%d %s\n",edge[i],STA[rhash[ver[i]]]);
    }
    // for(int i=1;i<=cnt;++i){
    //     printf("%s\n",STA[i]);
    // }
    return 0;
}