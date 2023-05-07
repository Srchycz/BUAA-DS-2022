#include<stdio.h>//Trie
#include<ctype.h>
#include<string.h>
FILE *IN;
char s[2000];
int trie[6000][26],tot=1,ed[6000];
char temp[1000];
int cnt=0;
void dfs(int idx){
    if(ed[idx]){
        temp[++cnt]='\0';
        printf("%s %d\n",temp+1,ed[idx]);
        --cnt;
    }
    for(int i=0;i<26;++i){
        if(trie[idx][i]==0) continue;
        temp[++cnt]=i+'a';
        dfs(trie[idx][i]);
        --cnt;
    }
}
void Insert(char *s){
    int p=1;
    while(*s){
        int ch=*s-'a';
        if(trie[p][ch]==0) trie[p][ch]=++tot;
        p=trie[p][ch];
        ++s;
    }
    ++ed[p];
}
int main(){
    char temp[50],q=0;
    char f[50],flag=0;
    IN=fopen("article.txt","r");
    while (fgets(s,1500,IN)!=NULL){
        int k=strlen(s);
        for(int i=0;i<k;++i)
            s[i]=tolower(s[i]);
        for(int i=0;i<k;++i){
            if(s[i]<='z'&&s[i]>='a')
                temp[q++]=s[i];
            else if(q){
                temp[q]='\0';
                Insert(temp);
                switch(flag){
                    case 0:{
                        flag=1;printf("%s ",temp);
                        strcpy(f,temp);
                        break;
                    }
                    case 1:{
                        if(strcmp(temp,f)>0){
                            flag=2;
                            printf("%s ",temp);
                            strcpy(f,temp);
                        }
                        break;
                    }
                    case 2:{
                        if(strcmp(temp,f)>0){
                            flag=3;
                            printf("%s ",temp);
                        }
                        break;                        
                    }
                    default:{}
                }
                q=0;
            }
        }
    }
    puts("");
    dfs(1);
    fclose(IN);
    return 0;
}