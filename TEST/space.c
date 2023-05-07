#include<stdio.h>
int vis[120000];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int l,r;
        scanf("%d%d",&l,&r);
        vis[l]=1,vis[r]=1;
    }
    int flag=0;
    for(int i=0;i<=100000;++i){
        if(vis[i]){
            if(flag){
                if(vis[i+1]==0){
                    printf(" %d\n",i);
                    flag=0;
                }
                else ++i;
            }
            else{
                printf("%d",i);
                flag=1;
            }
        }
    }
    return 0;
}