#include<stdio.h>
#include<string.h>
int n;
char h[30],z[30];
void Solve(int l,int r){
    if(r<l) return;
    for(int i=n-1;i>=0;--i){
        for(int j=l;j<=r;++j){
            if(h[i]==z[j]){
                printf("%c",h[i]);
                Solve(l,j-1),Solve(j+1,r);
                return;
            }
        }
    }
}
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    scanf("%s",h);
    scanf("%s",z);
    n=strlen(h);
    Solve(0,n-1);
    fclose(stdin),fclose(stdout);
    return 0;
}