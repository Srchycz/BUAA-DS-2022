#include<stdio.h>
#include<stdlib.h>
typedef struct polynomial{
    int a,c;
}polynomial;
polynomial a[200],b[200],ans[40000];
int cnt_a,cnt_b,cnt;
int cmp(const void* a,const void* b){
    polynomial*x=(polynomial*)a;
    polynomial*y=(polynomial*)b;
    if(x->c>y->c) return 1;
    else return -1;
}
int main(){
    char c='0';
    while (c!='\n'&&c!='\r'){
        ++cnt_a;
        scanf("%d%d",&a[cnt_a].a,&a[cnt_a].c);
        c=getchar();
    }
    c='0';
    while (c!='\n'&&c!='\r'){
        ++cnt_b;
        scanf("%d%d",&b[cnt_b].a,&b[cnt_b].c);
        c=getchar();
    }
    for(int i=1;i<=cnt_b;++i){
        for(int j=1;j<=cnt_a;++j){
            ans[++cnt].a=b[i].a*a[j].a;
            ans[cnt].c=b[i].c+a[j].c;
        }
    }
    qsort(ans+1,cnt,sizeof(polynomial),cmp);
    for(int i=1;i<cnt;++i){
        if(ans[i].c==ans[i+1].c){
            int j=i;
            while (ans[j].a==0&&ans[j-1].c==ans[i+1].c) --j;
            ans[j].a+=ans[i+1].a;
            ans[i+1].a=0;
        }
    }
    for(int i=cnt;i>=1;--i){
        if(ans[i].a==0) continue;
        printf("%d %d ",ans[i].a,ans[i].c);
    }
    return 0;
}