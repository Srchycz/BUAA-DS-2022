#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int id;
    char name[30];
    int pos;
}Stu;
Stu a[5000];
FILE *IN,*OUT;
int cmp(const void* a,const void* b){
    Stu* A=(Stu*)a;
    Stu* B=(Stu*)b;
    if(A->pos==B->pos) return A->id-B->id;
    return A->pos-B->pos;
}
int cmp2(const void* a,const void* b){
    Stu* A=(Stu*)a;
    Stu* B=(Stu*)b;
    return A->id-B->id;
}
int main(){
    IN=fopen("in.txt","r");
    OUT=fopen("out.txt","w");
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        fscanf(IN,"%d%s%d",&a[i].id,a[i].name,&a[i].pos);
    qsort(a+1,n,sizeof(Stu),cmp);
    int t=n,last=0;
    for(int i=1;i<=t;++i){
        if(a[i].pos-last>=2){
            a[t].pos=last+1;
            --t;
        }
        last=a[i].pos;
    }
    for(int i=2;i<=t;++i){
        if(a[i].pos==a[i-1].pos)
            a[i].pos=++last;
    }
    qsort(a+1,n,sizeof(Stu),cmp2);
    for(int i=1;i<=n;++i){
        fprintf(OUT,"%d %s %d\n",a[i].id,a[i].name,a[i].pos);
    }
    return 0;
}