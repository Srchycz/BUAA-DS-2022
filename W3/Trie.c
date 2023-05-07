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
int main(){
    IN=fopen("article.txt","r");
    while (fgets(s,1500,IN)!=NULL){
        int k=strlen(s);
        for(int i=0;i<k;++i)
            s[i]=tolower(s[i]);
        for(int i=0;i<k;++i){
            if(s[i]<'a'||s[i]>'z') continue;
            int j=i,p=1;
            while(s[j]<='z'&&s[j]>='a'){
                int ch=s[j]-'a';
                if(trie[p][ch]==0) trie[p][ch]=++tot;
                p=trie[p][ch];
                ++j;
            }
            ++ed[p];
            i=j;
        }
    }
    dfs(1);
    fclose(IN);
    return 0;
}