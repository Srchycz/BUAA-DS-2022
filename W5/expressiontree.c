#include<stdio.h>
#include<string.h>
#include<ctype.h>
typedef struct node{
    int ls,rs;
    char c;
    int x;
} Node;
Node t[10000];
int cnt;
char epr[2000],rpn[4000];
int tot,p,q;
int n;
char a[2000];//stack1
int b[2000];//stack2
int h[120];
void Filter(){
    n=strlen(epr);
    int j=0;
    for(int i=0;i<n;++i){
        if(epr[i]==' '||epr[i]=='=') continue;
        epr[j++]=epr[i];
    }
    epr[j]='\0';
    n=j;
}
int Numfy(int pos,char *s,int *res){
    *res=0;
    while (isdigit(s[pos])){
        *res=(*res)*10+s[pos]-'0';
        ++pos;
    }
    return pos-1;
}
int opt_cmp(char a,char b){
    if(a=='(') return -1;
    else return h[a]-h[b];
}
void Transform(){
    h[37]=h[42]=h[47]=2;
    h[43]=h[45]=1;
    for(int i=0;i<n;++i){
        if(isdigit(epr[i]))
            rpn[tot++]=epr[i];
        else{
            rpn[tot++]=' ';
            if(p==0) a[++p]=epr[i];
            else{
                switch(epr[i]){
                    case '(':{
                        a[++p]=epr[i];
                        break;
                    }
                    case ')':{
                        while(a[p]!='(')
                            rpn[tot++]=a[p--];
                        --p;
                        break;
                    }
                    default:{
                        while (p&&opt_cmp(a[p],epr[i])>=0){
                            rpn[tot++]=a[p--];
                            if(p<0) break;
                        }
                        a[++p]=epr[i];
                        break;
                    }
                }
            }
        }
    }
    while (p) rpn[tot++]=a[p--];
    rpn[tot]='\0';
}
void Build(){
    for(int i=0;i<tot;++i){
        if(rpn[i]==' ') continue;
        if(isdigit(rpn[i])){
            int k=0;
            i=Numfy(i,rpn,&k);
            t[++cnt].x=k;
            t[cnt].c='!';
            b[++q]=cnt;
        }
        else{
            int y=b[q--],x=b[q--];
            t[++cnt].ls=x,t[cnt].rs=y;
            t[cnt].c=rpn[i];
            b[++q]=cnt;
        }
    }
}
int Calc(int idx){
    if(t[idx].c=='!') return t[idx].x;
    int a=Calc(t[idx].ls),b=Calc(t[idx].rs);
    switch(t[idx].c){
        case '+':{
            return a+b;
            break;
        }
        case '-':{
            return a-b;
            break;
        }
        case '*':{
            return a*b;
            break;
        }
        case '/':{
            return a/b;
            break;
        }
        case '%':{
            return a%b;
            break;
        }
        default:{};
    }
}
int main(){
    gets(epr);
    Filter();
    Transform();
    Build();
    int rt=b[1];
    printf("%c ",t[rt].c);
    if(t[rt].ls){
        if(t[t[rt].ls].c=='!')
            printf("%d ",t[t[rt].ls].x);
        else
            printf("%c ",t[t[rt].ls].c);
    }
    if(t[rt].rs){
        if(t[t[rt].rs].c=='!')
            printf("%d",t[t[rt].rs].x);
        else
            printf("%c",t[t[rt].rs].c);
    }
    puts("");
    printf("%d\n",Calc(rt));
    return 0;
}