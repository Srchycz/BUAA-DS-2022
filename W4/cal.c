#include<stdio.h>
#include<string.h>
#include<ctype.h>
char epr[2000];
char rpn[4000];
char a[2000];
int p,tot;
double b[2000];
int q;
int n;
int h[160];
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
int Numfy(int pos,char *s,double *res){
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
void Calc(){
    for(int i=0;i<tot;++i){
        if(rpn[i]==' ') continue;
        if(isdigit(rpn[i])){
            double k=0;
            i=Numfy(i,rpn,&k);
            b[++q]=k;
        }
        else{
            double y=b[q--],x=b[q--];
            switch(rpn[i]){
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
        }
    }
}
int main(){
    h[37]=h[42]=h[47]=2;
    h[43]=h[45]=1;
    gets(epr);
    Filter();
    Transform();
    Calc();
    printf("%.2lf\n",b[1]);
    return 0;
}