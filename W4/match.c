#include<stdio.h>
#include<string.h>
FILE *IN;
int braces[2200],parentheses[2200],cnt_1,cnt_2;
int flag1,flag2,flag3,flag4;
char s[5100],ans[2200];
int tot;
void Perr(char c,int i){
    printf("without maching '%c' at line %d",c,i);
    fclose(IN);
}
int main(){
    int h=0;
    IN=fopen("example.c","r");
    while (fgets(s,1000,IN)!=NULL){
        ++h,flag3=0;
        int q=strlen(s);
        for(int i=0;i<q;++i){
            switch(s[i]){
                case '(':{
                    if(flag1==0&&flag2==0&&flag3==0&&flag4==0){
                        parentheses[++cnt_2]=h;
                        ans[++tot]='(';
                    }
                    break;
                }
                case ')':{
                    if(flag1==0&&flag2==0&&flag3==0&&flag4==0){
                        --cnt_2;
                        ans[++tot]=')';
                        if(cnt_2<0){
                            Perr(')',h);
                            return 0;
                        }
                    }
                    break;
                }
                case '{':{
                    if(flag1==0&&flag2==0&&flag3==0&&flag4==0){
                        ans[++tot]='{';
                        if(cnt_2>0){
                            Perr('(',parentheses[cnt_2]);
                            return 0;
                        }
                        braces[++cnt_1]=h;
                    }
                    break;
                }
                case '}':{
                    if(flag1==0&&flag2==0&&flag3==0&&flag4==0){
                        ans[++tot]='}';
                        if(cnt_2>0){
                            Perr('}',h);
                            return 0;
                        }
                        --cnt_1;
                        if(cnt_1<0){
                            Perr('}',h);
                            return 0;
                        }
                    }
                    break;
                }
                case '*':{
                    if(flag1){
                        if(s[i+1]=='/'){
                            flag1=0;
                            ++i;
                        }
                    }
                    break;
                }
                case '/':{
                    if(flag1==0&&flag2==0&&flag3==0&&flag4==0){
                        if(s[i+1]=='/'){
                            flag3=1;
                            ++i;
                        }
                        else{
                            if(s[i+1]=='*'){
                                flag1=1;
                                ++i;
                            }
                        }
                    }
                    break;
                }
                case '\"':{
                    if(flag1==0&&flag3==0&&flag2==0){
                        flag4^=1;
                    }
                    break;
                }
                case '\'':{
                    if(flag1==0&&flag3==0&&flag4==0){
                        flag2^=1;
                    }
                    break;
                }
                default:{}
            }
        }
    }
    if(cnt_1>0||cnt_2>0){
        if(cnt_2) Perr('(',parentheses[cnt_2]);
        else Perr('{',braces[cnt_1]);
        return 0;
    }
    else{
        for(int i=1;i<=tot;++i)
            printf("%c",ans[i]);
        // puts("");
        fclose(IN);
    }
    return 0;
}