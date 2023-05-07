#include<stdio.h>
typedef struct node{
    int s1,s2,s3;
}Node;
Node t[1000];
int q[1000],l=1,r=1,cnt=0,depth=0;
int id[1000],tot;
void dfs(int idx,int dep){
    if(idx==0) return;
    ++tot;
    int k=(t[idx].s1>0)+(t[idx].s2>0)+(t[idx].s3>0);
    if(k>cnt){
        l=r=1;depth=dep;cnt=k;
        id[r]=tot,q[r++]=idx;
    }
    else if(k==cnt){
            if(dep>depth){
                l=r=1;depth=dep;
                id[r]=tot,q[r++]=idx;
            }
            else if(dep==depth)
                id[r]=tot,q[r++]=idx;
    }
    dfs(t[idx].s1,dep+1);
    dfs(t[idx].s2,dep+1);
    dfs(t[idx].s3,dep+1);
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int r,a1,a2,a3;
        scanf("%d%d%d%d",&r,&a1,&a2,&a3);
        t[r]=(Node){a1,a2,a3};
    }
    dfs(1,1);
    while (r-l){
        printf("%d %d\n",q[l],id[l]);
        ++l;
    }
    return 0;
}