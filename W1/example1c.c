#include<stdio.h>
char s[100000];
int calc(int a,int b,char u){
    switch(u){
        case '+':{a+=b;break;}
        case '-':{a-=b;break;}
        case '*':{a*=b;break;}
        case '/':{a/=b;break;}
    }
    return a;
}
int main(){
    gets(s);
    int temp=0,res=1,ans=0;
    char c='+',d='*';
    for(int i=0;s[i]!='\0';i++){
        if(s[i]==' ') continue;
        if(s[i]<='9'&&s[i]>='0'){
            temp=temp*10+s[i]-'0';
        }
        else{
            res=calc(res,temp,d);
            d=s[i];
            if(s[i]=='+'||s[i]=='-'||s[i]=='='){
                ans=calc(ans,res,c);
                c=s[i];
                res=1,d='*';
            }
            temp=0;
        }
    }
    printf("%d\n",ans);
    return 0;
}