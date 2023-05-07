#include<stdio.h>
#include<string.h>
#include<ctype.h>
double num[200];
char epr[2000];
double rpn[4000];
int vis[4000];
char a[2000];
int p,tot;
double b[2000];
int q;
int h[160];
int Numfy(char *s,double *res){
    *res=0;
    int flag=1,u=0;
    if(isalpha(*s)) {*res=num[*s];return 0;}
    if(*s=='-') flag=-1,++s,++u;
    while (isdigit(*s)){
        *res=(*res)*10+*s-'0';
        ++s,++u;
    }
    *res=(*res)*flag;
    return u-1;
}
int opt_cmp(char a,char b){
    if(a=='(') return -1;
    else return h[a]-h[b];
}
void Transform(){
    int f=0;
    for(int i=0;epr[i]!='\0';++i){
        if(isdigit(epr[i])||isalpha(epr[i])||(f==0&&epr[i]=='-')){
            i+=Numfy(epr+i,&rpn[tot++]);
            f=1;
            continue;
        }
        if(p==0) a[++p]=epr[i];
        else{
            switch(epr[i]){
                case '(':{
                    a[++p]=epr[i];
                    f=0;
                    break;
                }
                case ')':{
                    while(a[p]!='(')
                        rpn[tot++]=a[p--],vis[tot-1]=1;
                    --p;
                    break;
                }
                default:{
                    while (p&&opt_cmp(a[p],epr[i])>=0){
                        rpn[tot++]=a[p--],vis[tot-1]=1;
                    }
                    a[++p]=epr[i];
                    break;
                }
            }
        }
    }
    while (p) rpn[tot++]=a[p--],vis[tot-1]=1;
    rpn[tot]='\0';
}
void Calc(){
    for(int i=0;i<tot;++i){
        if(!vis[i]){
            b[++q]=rpn[i];
        }
        else{
            double y=b[q--],x=b[q--];
            switch((char)rpn[i]){
                case '+':{
                    b[++q]=x+y;
                    break;
                }
                case '-':{
                    b[++q]=x-y;
                    break;
                }
                case '*':{
                    b[++q]=x*y;
                    break;
                }
                case '/':{
                    b[++q]=x/y;
                    break;
                }
            }
            vis[i]=0;
        }
    }
}
int main(){
    h[37]=h[42]=h[47]=2;
    h[43]=h[45]=1;
    h[40]=h[41]=3;
    char temp[300];
    while (1){
        gets(temp);
        if(temp[1]=='x') break;
        if(temp[1]=='r'){
            int flag=0;
            for(int i=5;temp[i]!='\0';++i){
                if(temp[i]==' ') continue;
                if(flag) printf(" ");
                printf("%.2lf",num[temp[i]]);
                flag=1;
            }
            puts("");
        }
        if(temp[1]=='='){
            int v=0;
            for(int i=2;temp[i]!='\0';++i){
                epr[i-2]=temp[i];
                v=i-2;
            }
            epr[++v]='\0';
            Transform();
            Calc();
            num[temp[0]]=b[1];
            for(int i=0;i<tot;++i){
                printf("%.0lf ",rpn[i]);
            }
            puts("");
            q=0,p=0,tot=0;
        }
    }
    return 0;
}
/*
a=10
b=20
c=(a+b)/4
print a b c
d=a*(b-c)
print d
exit
*/