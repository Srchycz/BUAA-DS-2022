#include<stdio.h>
int a[100000];
int main(){
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    int j=q;
    for(int i=1;i<=n-1;++i){
        int T=(m-1)%(n+1-i)+1,cnt=0;
        while (cnt<T){
            if(!a[j])   ++cnt;
            ++j;
            if(j>n) j=1;
        }
        --j;
        if(j==0) j=n;
        a[j]=1;
        while (a[j]){
            ++j;
            if(j>n) j=1;
        }  
    }
    for(int i=1;i<=n;++i){
        if(!a[i]){
            printf("%d\n",i);
            break;
        }
    }
    return 0;
}