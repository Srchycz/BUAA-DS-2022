#include<stdio.h>
#include<string.h>
char a[100],b[100],c[100];
int tag_a,tag_b;
void rev(char *s){
    int k=strlen(s);
    for(int i=0;i<=((k-1)>>1);i++){
        char temp;
        temp=s[i];
        s[i]=s[k-i-1];
        s[k-i-1]=temp;
    }
}
int cmp(char *p_a,char *p_b){
    while (*p_a=='0') p_a++;
    while (*p_b=='0') p_b++;
    tag_a=p_a-a,tag_b=p_b-b;
    int k1=strlen(a),k2=strlen(b);
    if(k1-tag_a>k2-tag_b) return 1;
    if(k1-tag_a<k2-tag_b) return -1;
    while (p_a<a+k1&&p_b<b+k2){
        if(*p_a==*p_b){
            p_a++,p_b++;
            continue;
        }
        if(*p_a>*p_b) return 1;
        else return -1;
    }
    if(p_a==a+k1&&p_b==b+k2) return 0;
    if(p_a==a+k1) return -1;
    else return 1;
}
int main(){
    scanf("%s",a);
    scanf("%s",b);
    int u=cmp(a,b),flag=0;
    char *pvt,*sub;
    if(u==0){puts("0");return 0;}
    if(u==1) {
        pvt=a,sub=b;
    }
    else{
        pvt=b,sub=a,flag=1;
        tag_a^=tag_b;
        tag_b^=tag_a;
        tag_a^=tag_b;
    }
    rev(a),rev(b);
    tag_a=strlen(pvt)-tag_a-1,tag_b=strlen(sub)-tag_b-1;
    for(int i=0;i<=tag_b;i++){
        if(*(pvt+i)>=*(sub+i)) c[i]='0'+*(pvt+i)-*(sub+i);
        else{
            c[i]=*(pvt+i)-*(sub+i)+'0'+10;
            int j=i+1;
            while(*(pvt+j)=='0') *(pvt+j)='9',j++;
            (*(pvt+j))--;
        }
    }
    for(int i=tag_b+1;i<=tag_a;i++) c[i]=*(pvt+i);
    rev(c);
    int f=0;
    while (c[f]=='0') f++;
    if(flag) printf("-");
    printf("%s",c+f);
}