#include<stdio.h>
#include<string.h>
char a[1000],b[1000];
char c[1020];
FILE *IN,*OUT;
char Cvt(char c){return ('A'<=c&&c<='Z')?c+32:c;}
int Match(int idx){
    for(int i=0;a[i]!='\0';++i)
        if(Cvt(a[i])!=Cvt(c[idx+i])) return 0;
    fprintf(OUT,"%s",b);
    return 1;
}
int main(){
    IN=fopen("filein.txt","r");
    OUT=fopen("fileout.txt","w");
    // IN=stdin,OUT=stdout;
    scanf("%s",a);scanf("%s",b);
    int k=strlen(a);
    while (fgets(c,1000,IN)!=NULL){
        int len=strlen(c);
        while (c[len-1]=='\r'||c[len-1]=='\n') c[--len]='\0';
        int p=0;
        while (c[p]!='\0'){
            if(Cvt(c[p])!=Cvt(a[0])){
                fputc(c[p],OUT);
                ++p;
                continue;
            }
            if(Match(p)) p+=k;
            else{
                fputc(c[p],OUT);
                ++p;
            }
        }
        fputc('\n',OUT);
    }
    fclose(IN);fclose(OUT);
    return 0;
}