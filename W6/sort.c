#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 500
int a[N],ans,n;
int b[N];
void Swap(int*,int*);
int Adjust(int,int);
int Merge(int,int);
int Qsort(int,int);
void SelectionSort();
void BubbleSort();
void HeapSort();
void MergeSort();
void QuickSort();
int main(){
    int k;
    void (*f[])()={SelectionSort,BubbleSort,HeapSort,MergeSort,QuickSort};
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    f[k-1]();
    for(int i=1;i<=n;++i)
        printf("%d ",a[i]);
    puts("");
    printf("%d\n",ans);
    return 0;
}
void Swap(int *a,int *b){
    int temp=(*a);
    *a=*b;
    *b=temp;
}
void SelectionSort(){
    int res=0;
    for(int i=1;i<n;++i){
        int aim=i;
        for(int j=i+1;j<=n;++j){
            ++res;
            if(a[j]<a[aim]) aim=j;
        }
        Swap(&a[i],&a[aim]);
    }
    ans=res;
}
void BubbleSort(){
    int res=0;
    for(int i=1;i<=n;++i){
        int flag=0;
        for(int j=2;j<=n-i+1;++j){
            ++res;
            if(a[j]<a[j-1]){
                Swap(&a[j],&a[j-1]);
                flag=1;
            }
        }
        if(flag==0) break;
    }
    ans=res;
}
int Adjust(int i,int n){
    int res=0;
    int k=a[i];
    int now=i;
    int nxt=now<<1;
    while(nxt<=n){
        if(nxt<n && a[nxt]<a[nxt+1]) ++nxt;
        ++res;
        if(k>=a[nxt]) break;
        a[now]=a[nxt],now=nxt,nxt<<=1;
    }
    a[now]=k;
    return res;
}
void HeapSort(){
    int i;
    for(i=n>>1;i>=1;--i)
        ans+=Adjust(i,n);
    for(i=n;i>=2;--i){
        Swap(&a[i],&a[1]);
        ans+=Adjust(1,i-1);
    }
}
int Merge(int l,int r){
    int res=0;
    if(l==r) return 0;
    int mid=(l+r)>>1;
    res+=Merge(l,mid);
    res+=Merge(mid+1,r);
    int i=l,j=mid+1,k=l;
    while (i<=mid&&j<=r){
        ++res;
        if(b[i]<b[j]) a[k++]=b[i++];
        else a[k++]=b[j++];
    }
    while (i<=mid) a[k++]=b[i++];
    while (j<=r) a[k++]=b[j++];
    memcpy(b+1,a+1,4*n);
    return res;
}
void MergeSort(){
    memcpy(b+1,a+1,4*n);
    ans=Merge(1,n);
}
int Qsort(int l,int r){
    int res=0;
    if(l>=r) return 0;
    int u=l;
    for(int i=l+1;i<=r;++i){
        ++res;
        if(a[i]<a[l]) Swap(&a[++u],&a[i]);
    }
    Swap(&a[l],&a[u]);
    res+=Qsort(l,u-1);
    res+=Qsort(u+1,r);
    return res;
}
void QuickSort(){
    ans=Qsort(1,n);
}
/*
20 1
38 356 98 -102 126 46 65 -9 100 0 21 2 90 8 18 12 78 16 189 23
4 4 
4 3 2 1
*/