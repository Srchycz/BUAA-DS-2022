#include<stdio.h>
#include<stdlib.h>
#define N 10000
int key[N],name[N][20],idx[N],cnt=1;
int ans[N],p;
int vis[N];
int Find(int aim){
    for(int i=1;i<cnt;++i){
        if(key[aim]==key[i])
        return i;
    }
    return 0;
}
int cmp(const void *A,const void *B){
    int a=*(int*)A,b=*(int*)B;
    if(key[a]>key[b]) return 1;
    else return -1;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int temp;
        scanf("%d%s%d%d",&key[cnt],name[cnt],&idx[cnt],&temp);
        int k=Find(cnt);
        if(k==0) ++cnt;
        else{
            if(vis[k]==0&&idx[cnt]!=idx[k]) ans[++p]=k,vis[k]=1;
        }
    }
    qsort(ans+1,p,sizeof(int),cmp);
    for(int i=1;i<=p;++i){
        printf("%d %s\n",key[ans[i]],name[ans[i]]);
    }
    return 0;
}
/*
21
191028 wangdi 15 093000
192387 litong 39 093000
190877 liugang 37 093001
197583 huangqinian 196 093004
195211 liuhao 201 093005
193098 zhaogang 377 093006
190001 zhousheng 1 093007
190009 wuhong 12 093007
197583 huangqinian 197 093008
195877 lisisi 202 093008
192387 litong 309 093009
191000 tonghao 201 093402
197583 huangqinian 196 093500
191028 wangdi 15 093507
190010 wangzhuang 85 093558
195333 zhangye 63 093600
197583 huangqinian 195 094100
195211 liuhao 200 095103
190010 wangzhuang 287 095509
193098 zhaogang 377 095606
191028 wangdi 15 095709
*/