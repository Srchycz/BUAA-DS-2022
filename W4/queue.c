#include<stdio.h>
#define N 1000000
struct queue{
    int id;//客户编号
    int tim;//客户是第几轮来的
}q[N];
int l=1,r=1;//前闭后开 队列首尾指针
int a[N],T;
int vis[N];
void Push(int id,int tim){
    q[r].id=id;
    q[r].tim=tim;
    ++r;
}

int main(){
    int t=0,numWindow=3,idx=0;
    scanf("%d",&T);
    for(int i=1;i<=T;++i)
        scanf("%d",&a[i]);
    while ((r-l)||t<=T){//(r-l)即等待队列人数
        ++t;
        if(t<=T){
            for(int i=1;i<=a[t];++i)
                Push(++idx,t);//把该轮新来的客户加入等待队列
            if(r-l>=21){//判断要开几个窗口
                if(r-l>=28) numWindow=5;
                else numWindow=4;
            }
            else numWindow=3;
        }
        for(int i=1;i<=numWindow&&(r-l);++i,++l)
            vis[q[l].id]=t-q[l].tim;
        if(r-l<35) numWindow=4;//判断是否要减少窗口
        if(r-l<28) numWindow=3;
    }
    for(int i=1;i<r;++i)
        printf("%d : %d\n",i,vis[i]);
    
    return 0;
}