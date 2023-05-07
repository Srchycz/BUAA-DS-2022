#include<stdio.h>
char s[100000];
int judge(char c){
    if(c<='9'&&c>='0') return 1;
    if(c<='Z'&&c>='A') return 2;
    if(c<='z'&&c>='a') return 3;
    return 4;
}
int main(){
    scanf("%s",s);
    for(int i=0;s[i]!='\0';i++){
        if(s[i]=='-'){
            if(judge(s[i-1])==judge(s[i+1])&&s[i+1]>s[i-1])
                for(int j=s[i-1]+1;j<s[i+1];j++) printf("%c",j);
            else printf("-");
        }
        else{
            printf("%c",s[i]);
        }
    }
    return 0;
}