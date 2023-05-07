#include<stdio.h>
char s[1000000],ans[100000];
int main(){
    scanf("%s",s);
    int j=0,cnt=0,flag=0;
    if(s[0]=='0'){
        cnt=1;
        for(int i=2;s[i]!='\0';i++){
            if(!flag&&s[i]=='0') cnt++;
            else{
                if(!flag) ans[j++]=s[i],ans[j++]='.',flag=1;
                else ans[j++]=s[i];
            }
        }
        if(j==2) j--;
        ans[j]='\0';
        printf("%se-%d",ans,cnt);
    }
    else{
        ans[j++]=s[0],ans[j++]='.';
        for(int i=1;s[i]!='\0';i++){
            if(s[i]=='.') flag=1;
            else{
                if(!flag) cnt++;
                ans[j++]=s[i];
            }
        }
        if(j==2) j--;
        ans[j]='\0';
        printf("%se%d",ans,cnt);
    }
}