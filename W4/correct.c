#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
struct stack
{
    int Top;
    char Symbol[1000];
    int Line[1000];
};
struct stack Stack1,Stack2;
char s0[1000],mistake;
int flag=0,flag1=0;//flag marks if mistake has been found; flag1 marks if any "/*"before;
int cnt=0,misline;//标记行数
void Examine(char *s)
{
    int l=strlen(s);
    cnt++;
    for(int i=0;i<l;i++)
    {
        if(s[i]!='*')
        {
            if(flag1==1)
            continue;
            else
            {
                if(s[i]=='/')
                {
                   if(s[i+1]=='/')
                   break;
                   else if(s[i+1]=='*')
                   {
                       flag1=1;
                       for(int j=i+2;j<l;j++)
                       {
                           if(s[j]=='*'&&s[j+1]=='/')
                           {
                               i=j+1;
                               flag1=0;
                               break;
                           }
                       }
                       if(flag1==0)
                       continue;
                   }
                }
                if(s[i]==39)
                {
                   if(s[i+2]==39)
                   i++;
                }
                if(s[i]==34)
                {
                    for(int j=i+1;j<l;j++)
                    {
                        if(s[j]==34)
                        {
                            i=j;break;
                        }
                    }
                }
                if(s[i]=='{')
                {
                    if(Stack1.Top>=1&&Stack1.Symbol[Stack1.Top]=='(')
                    {
                        flag=1;
                        mistake=Stack1.Symbol[Stack1.Top];
                        misline=Stack1.Line[Stack1.Top];
                        break;
                    }
                    else
                    {
                        Stack1.Top++;
                        Stack1.Symbol[Stack1.Top]=s[i];
                        Stack1.Line[Stack1.Top]=cnt;
                        Stack2.Top++;
                        Stack2.Symbol[Stack2.Top]=s[i];
                    } 
                }
                if(s[i]=='(')
                {
                    Stack1.Top++;
                    Stack1.Symbol[Stack1.Top]=s[i];
                    Stack1.Line[Stack1.Top]=cnt;
                    Stack2.Top++;
                    Stack2.Symbol[Stack2.Top]=s[i];
                }
                if(s[i]==')')
                {
                    if(Stack1.Top>=1&&Stack1.Symbol[Stack1.Top]=='(')
                    {
                        Stack2.Top++;
                        Stack2.Symbol[Stack2.Top]=s[i];
                        Stack1.Top--;
                    }
                    else
                    {
                        flag=1;
                        mistake=s[i];
                        misline=cnt;
                        break;
                    }
                }
                if(s[i]=='}')
                {
                    if(Stack1.Top>=1&&Stack1.Symbol[Stack1.Top]=='{')
                    {
                        Stack2.Top++;
                        Stack2.Symbol[Stack2.Top]=s[i];
                        Stack1.Top--;
                    }
                    else
                    {
                        flag=1;
                        mistake=s[i];
                        misline=cnt;
                        break;
                    }
                }
            }
        }
        else if(s[i]=='*')
        {
            if(s[i+1]=='/'&&flag1==1)
            {
                i++;
                flag1=0;
            }
            else
            continue;
        }
    }  
}
int main()
{
    Stack1.Top=0;
    Stack2.Top=0;
    FILE *in;
    in=fopen("example.c", "r");
    while(fgets(s0,1000,in)!=NULL)
    {
        Examine(s0);
        if(flag==1)
        {
            printf("without maching '%c' at line %d",mistake,misline);
            return 0;
        }
    }
    if(Stack1.Top!=0)
    {
        printf("without maching '%c' at line %d",Stack1.Symbol[Stack1.Top],Stack1.Line[Stack1.Top]);
        return 0;
    }
    for(int i=1;i<=Stack2.Top;i++)
    {
        printf("%c",Stack2.Symbol[i]);
    }
}