#include<stdio.h>
int v[10],ans[10];    
int n;
void P(){
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    puts("");
}
void Solve(int idx){
    if(idx==n+1){
        P();
        return;
    }
    for(int i=1;i<=n;i++){
        if(v[i]) continue;
        v[i]=1;
        ans[idx]=i;
        Solve(idx+1);
        v[i]=0;
    }
}
int main(){
    scanf("%d",&n);
    Solve(1);
    return 0;
}