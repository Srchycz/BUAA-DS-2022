#include<stdio.h>
int S[120],p=0;
int main(){
    int opt,k;
    while (1){
        scanf("%d",&opt);
        if(opt==-1) break;
        switch(opt){
            case 1:{
                scanf("%d",&k);
                if(p==100) printf("error ");
                else S[++p]=k;
                break;
            }
            case 0:{
                if(p==0) printf("error ");
                else printf("%d ",S[p--]);
                break;
            }
        }
    }
    return 0;
}