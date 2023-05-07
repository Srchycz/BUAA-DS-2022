#include<stdio.h>
#include<string.h>
char f[100];
char s[200];
int main(){
    scanf("%s",f);
    getchar();
    gets(s);
    int k=strlen(s);
    int p=1,flag=0;
    if(f[p]=='-') flag=1,++p;
    int m=0;
    while (f[p]!=':'){
        m*=10;
        m+=f[p]-'0';
        ++p;
    }
    if(m>k) m=k;
    int n=0;
    ++p;
    while (f[p]!='S'){
        n*=10;
        n+=f[p]-'0';
        ++p;
    }
    f[p]='s';
    if(n<m) n=m;
    int u=n-m;
    if(flag){
        for(int i=1;i<=u;++i) putchar('#');
        for(int i=0;i<m;++i) putchar(s[i]);
    }
    else{
        for(int i=0;i<m;++i) putchar(s[i]);
        for(int i=1;i<=u;++i) putchar('#');
    }
    // printf("%d %d %d %d\n",u,n,m,k);
    return 0;
}
/*
%-20:30S
Hello, word!
*/