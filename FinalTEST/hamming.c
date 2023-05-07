#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char s[20][20];
int h[20],idx[20];
int cmp(const void* A,const void* B){
    int pa=*(int*)A,pb=*(int*)B;
    if(h[pa]==h[pb]) return strcmp(s[pa],s[pb]);
    return h[pa]-h[pb];
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%s",s[i]);
    }
    for(int i=1;i<n;++i){
        idx[i]=i;
        for(int j=0;s[0][j]!='\0';++j){
            if(s[0][j]!=s[i][j]) ++h[i];
        }
    }
    qsort(idx+1,n-1,sizeof(int),cmp);
    for(int i=1;i<n;++i){
        printf("%s %s %d\n",s[0],s[idx[i]],h[idx[i]]);
    }
    return 0;
}