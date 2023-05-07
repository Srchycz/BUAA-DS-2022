#include<stdio.h>
#include<string.h>
FILE *IN,*OUT;
char a[1020],sk[60];
int v[200],p=0;
int main(){
    IN=fopen("encrypt.txt","r");
    OUT=fopen("output.txt","w");
    scanf("%s",a);
    int k=strlen(a);
    for(int i=0;i<k;i++){
        if(v[a[i]]) continue;
        sk[p++]=a[i];
        v[a[i]]=1;
    }
    for(int i='z';i>='a';--i){
        if(v[i]) continue;
        sk[p++]=i;
        v[a[i]]=1;
    }
    while (fgets(a,1000,IN)!=NULL){
        int len=strlen(a);
        while (a[len-1]=='\r'||a[len-1]=='\n') a[--len]='\0';
        for(int i=0;a[i]!='\0';++i){
            if('a'<=a[i]&&a[i]<='z')
                a[i]=sk[a[i]-'a'];
        }
        fprintf(OUT,"%s\n",a);
    }
    fclose(IN),fclose(OUT);
    return 0;
}