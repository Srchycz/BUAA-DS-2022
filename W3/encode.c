#include<stdio.h>
#include<string.h>
FILE *IN,*OUT;
char sk[200],a[1000];
char key[200];
int tot=0;
int v[200];
int main(){
    IN=fopen("in.txt","r");
    OUT=fopen("in_crpyt.txt","w");
    gets(a);
    for(int i=0;a[i]!='\0';++i){
        int h=a[i]-32;
        if(v[h]) continue;
        sk[++tot]=a[i];
        v[h]=1;
    }
    for(int i=32;i<=126;++i){
        if(v[i-32]) continue;
        sk[++tot]=i;
    }
    // sk[tot+1] = '\0';
    // printf("%s",sk+1);
    memset(v,0,sizeof v);
    // key[sk[tot]-32]=sk[1];
    int j=2,T=sk[1],last=1;
    v[1]=1;
    for(int i=1;i<tot;++i){
        int cnt=0;
        T=(T-1)%(tot-i)+1;
        while (cnt<T){
            if(!v[j]) ++cnt;
            ++j;
            if(j>tot) j=1;
        }
        --j;
        if(j==0) j=tot;
        v[j]=1;
        T=key[sk[last]-32]=sk[j];
        // printf("%d:%c->%c\n",i,sk[last],sk[j]);
        last=j;
        while(v[j]&&i<tot-1){
            ++j;
            if(j>tot) j=1;
        }
        // printf("%d\n",i);
    }
    key[sk[last]-32]=sk[1];
    for(int i=0;i<=126-32;++i){
        // printf("%c:%c\n",i+' ',key[i])/;
    }
    char c;
    while ((c=fgetc(IN))!=EOF){
        if(c>=32&&c<=126) fputc(key[c-32],OUT);
        else fputc(c,OUT);
    }
    fclose(IN),fclose(OUT);
    return 0;
}