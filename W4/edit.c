#include<stdio.h>
#include<string.h>
char text[1000];
typedef struct operation{
    int opt;
    int pos;
    char str[1000];
    int k;
}OPT;
OPT a[5000];
void Insert(int pos,char *s,int n){
    int k=strlen(text);
    for(int i=k;i>=pos;--i)
        text[i+n]=text[i];
    for(int i=0;i<n;++i)
        text[pos+i]=s[i];
}
void Delete(int pos,int n){
    int k=strlen(text);
    if(n>k-pos) text[pos]='\0';
    for(int i=pos+n;i<=k;++i)
        text[i-n]=text[i];
}
void Reduct(int m){
    for(int i=m;i>=1;--i){
        if(a[i].opt==1)
            Delete(a[i].pos,a[i].k);
        else
            Insert(a[i].pos,a[i].str,a[i].k);
    }
}
int main(){
    int n;
    gets(text);
    int cnt=strlen(text);
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d%d%s",&a[i].opt,&a[i].pos,a[i].str);
        a[i].k=strlen(a[i].str);
    }
    Reduct(n);
    int f;
    while (1){
        scanf("%d",&f);
        if(f==-1) break;
        switch(f){
            case 1:{
                a[++n].opt=f;
                scanf("%d%s",&a[n].pos,a[n].str);
                a[n].k=strlen(a[n].str);
                cnt+=a[n].k;
                break;
            }
            case 2:{
                a[++n].opt=f;
                scanf("%d%d",&a[n].pos,&a[n].k);
                if(cnt-a[n].pos<a[n].k)
                    a[n].k=cnt-a[n].pos;
                cnt-=a[n].k;
                break;
            }
            case 3:{
                if(n>0){
                    if(a[n].opt==1) cnt-=a[n].k;
                    else cnt+=a[n].k;
                    --n;
                }
                break;
            }
        }
    }
    for(int i=1;i<=n;++i){
        if(a[i].opt==1)
            Insert(a[i].pos,a[i].str,a[i].k);
        else
            Delete(a[i].pos,a[i].k);
    }
    puts(text);
    return 0;
}