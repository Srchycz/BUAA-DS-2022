#include<stdio.h>
#include<stdlib.h>
typedef struct line{
    int x1,y1,x2,y2;
} line;
line num[10000];
int v[10000],ans=0,X,Y;
int cmp(const void *a,const void *b){
    line *x=(line*)a;
    line *y=(line*)b;
    if(x->x1<y->x1) return -1;
    if(x->x2<y->x2) return -1;
    return 1;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d%d%d%d",&num[i].x1,&num[i].y1,&num[i].x2,&num[i].y2);
    }
    qsort(num+1,n,sizeof(line),cmp);
    for(int i=1;i<=n;++i){
        if(v[i]) continue;
        v[i]=1;
        int cnt=1,now_x=num[i].x2,now_y=num[i].y2,flag=1;
        while(flag){
            flag=0;
            for(int j=1;j<=n;++j){
                if(v[j]) continue;
                if(num[j].x1==now_x&&num[j].y1==now_y){
                    now_x=num[j].x2,now_y=num[j].y2;
                    flag=1;v[j]=1;
                    ++cnt;
                    break;
                }
                if(num[j].x2==now_x&&num[j].y2==now_y){
                    now_x=num[j].x1,now_y=num[j].y1;
                    flag=1;v[j]=1;
                    ++cnt;
                    break;
                }
            }
        }
        if(cnt>ans){
            ans=cnt;
            X=num[i].x1;
            Y=num[i].y1;
        }
    }
    printf("%d %d %d\n",ans,X,Y);
    return 0;
}