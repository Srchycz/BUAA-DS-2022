#include<stdio.h>
#include<string.h>
char Word[5000][30];
int ans=0,n=1;
int head[3001],nxt[5000],ver[5000],tot=1;
unsigned int hash(char*);
void add(int,int);
int SequentialSearch(char*);
int BinarySearch(char*);
int IndexSearch(char*);
int HashSearch(char*);
int main(){
    FILE *IN=fopen("dictionary3000.txt","r");
    while (fscanf(IN,"%s",Word[n])!=EOF) ++n;
    --n;
    int (*f[])(char*)={SequentialSearch,BinarySearch,IndexSearch,HashSearch};
    char s[50];
    int k;
    scanf("%s%d",s,&k);
    printf("%d",f[k-1](s));
    printf(" %d\n",ans);//printf的底层执行逻辑决定了这两个printf不可合并
    return 0;
}
int SequentialSearch(char *s){
    int i=1;
    while(strcmp(Word[i],s)<0&&i<n) ++i;
    ans=i;
    if(strcmp(s,Word[i])==0) return 1;
    else return 0;
}
int BinarySearch(char* s){
    int l=1,r=n;
    while (l<=r){
        int mid=(l+r)>>1;
        ++ans;
        if(strcmp(Word[mid],s)==0) return 1;
        else if(strcmp(Word[mid],s)<0) l=mid+1;
        else r=mid-1; 
    }
    return 0;
}
int IndexSearch(char *s){
    int j=1;
    int idx[30];
    idx[0]=0;
    for(int i=1;i<=26;++i){
        while (Word[j][0]==i+'a'-1&&j<=n) ++j;
        idx[i]=j-1;
    }
    int l=idx[s[0]-'a']+1,r=idx[s[0]-'a'+1];
    while (l<=r){
        int mid=(l+r)>>1;
        ++ans;
        if(strcmp(Word[mid],s)==0) return 1;
        else if(strcmp(Word[mid],s)<0) l=mid+1;
        else r=mid-1; 
    }
    return 0;
}
#define NHASH  3001
#define MULT  37
unsigned int hash(char *str){
       unsigned int h=0;
       char *p;
       for(p=str; *p!='\0'; p++)
              h = MULT*h + *p;
       return h % NHASH;
}
void add(int x,int y){
    ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;
}
int HashSearch(char *s){
    for(int i=1;i<=n;++i)
        add(hash(Word[i]),i);
    int u=hash(s);
    for(int i=head[u];i;i=nxt[i]){
        ++ans;
        if(strcmp(s,Word[ver[i]])==0) return 1;
    }
    return 0;
}