#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    int id;
    int x,y;
    int weight;
}Edge;
Edge a[1000];
int fa[1000];
int n,m;
int heap[1000],tot;
int ans[1000],p;
int Get(int x){
    if(fa[x]==x) return x;
    return fa[x]=Get(fa[x]);
}
void Merge(int x,int y){
    fa[Get(x)]=Get(y);
}
int cmp(int x,int y){
    if(a[x].weight==a[y].weight) return a[x].id<a[y].id;
    return a[x].weight<a[y].weight;
}
void Insert(int d){
	int now=++tot;
	while (now>1)
	{
		if(!cmp(heap[now>>1],d))
		heap[now]=heap[now>>1],now>>=1;
		else break;
	}
	heap[now]=d;
}
void Extract(){
	int now=1,nxt=2;
	int k=heap[tot--];
	while(nxt<=tot)
	{
		if(nxt<tot&&cmp(heap[nxt|1],heap[nxt])) nxt|=1;
		if(cmp(heap[nxt],k)) heap[now]=heap[nxt],now=nxt,nxt=now<<1;
		else break;
	}
	heap[now]=k;
}
int cmp2(const void* a,const void* b){
    int A=*(int*)a,B=*(int*)b;
    return A-B;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i) fa[i]=i;
    for(int i=1;i<=m;++i){
        scanf("%d%d%d%d",&a[i].id,&a[i].x,&a[i].y,&a[i].weight);
        Insert(i);
    }
    int cnt=n-1;
    while (cnt){
        int x=a[heap[1]].x,y=a[heap[1]].y;
        if(Get(x)!=Get(y)){
            --cnt;
            ans[++p]=a[heap[1]].id;
            ans[0]+=a[heap[1]].weight;
            Merge(x,y);
        }
        Extract();
    }
    qsort(ans+1,p,sizeof(int),cmp2);
    printf("%d\n",ans[0]);
    for(int i=1;i<=p;++i)
        printf("%d ",ans[i]);
    puts("");
    return 0;
}
/*
6 10
1 0 1 600
2 0 2 100
3 0 3 500
4 1 2 500
5 2 3 500
6 1 4 300
7 2 4 600
8 2 5 400
9 3 5 200
10 4 5 600
*/