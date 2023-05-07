#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct list{
    char title[60];
    char atr[30];
    char press[40];
    char date[20];
    struct list *pre;
    struct list *nxt;
} list;
FILE *IN,*OUT;
list *head,*tail;
int sz=0;
void Build(){
    list *p=NULL,*q=NULL;
    head=(list*)malloc(sizeof(list));head->pre=NULL;
    tail=(list*)malloc(sizeof(list));tail->nxt=NULL;
    q=(list*)malloc(sizeof(list));
    head->nxt=tail,tail->pre=head;
    while (fscanf(IN,"%s%s%s%s",q->title,q->atr,q->press,q->date)!=EOF){
        if(sz==0){
            p=q;
            q->pre=head,head->nxt=q;
            q->nxt=tail,tail->pre=q;
        }
        else{
            q->nxt=p->nxt,p->nxt->pre=q;
            p->nxt=q,q->pre=p;
        }
        ++sz;
        p=q;
        q=(list*)malloc(sizeof(list));
    }
    free(q);
}
void Swap(list *x,list *y){
    x->pre->nxt=y,y->nxt->pre=x;
    x->nxt=y->nxt,y->pre=x->pre;
    x->pre=y,y->nxt=x;
}
void Bubble_Sort(){
    for(int i=1;i<=sz;i++){
        int f=0;
        for(list *p=head->nxt;p->nxt!=tail&&p!=tail;p=p->nxt){
            if(strcmp(p->title,p->nxt->title)>0){
                f=1;
                Swap(p,p->nxt);
            }
        }
        if(!f) break;
    }
}
void P(list *p,FILE *stm){
    fprintf(stm,"%-50s%-20s%-30s%-10s\n",p->title,p->atr,p->press,p->date);
}
void Insert(){
    list *q=(list*)malloc(sizeof(list));
    scanf("%s%s%s%s",q->title,q->atr,q->press,q->date);
    list *i=head->nxt;
    while (i!=tail&&strcmp(i->title,q->title)<0) i=i->nxt;
    list *p=i->pre;
    q->nxt=p->nxt,p->nxt->pre=q;
    p->nxt=q,q->pre=p;
    ++sz;
}
void Find(char *key){
    for(list *i=head->nxt;i!=tail;i=i->nxt){
        if(strstr(i->title,key)!=NULL){
            P(i,stdout);
        }
    }
}
void Extract(char *key){
    for(list *i=head->nxt;i!=tail&&i!=NULL;){
        if(strstr(i->title,key)!=NULL){
            list *p=i->pre,*q=i->nxt;
            p->nxt=q,q->pre=p;
            free(i);
            i=q;
            --sz;
        }
        else i=i->nxt;
    }
}

int main(){
    IN=fopen("books.txt","r");
    OUT=fopen("ordered.txt","w");

    Build();
    Bubble_Sort();
    int flag;
    char temp[100];
    while (1){
        scanf("%d",&flag);
        if(!flag) break;
        switch(flag){
            case 1:{
                Insert();
                break;
            }
            case 2:{
                scanf("%s",temp);
                Find(temp);
                break;
            }
            case 3:{
                scanf("%s",temp);
                Extract(temp);
                break;
            }
        }
    }
    for(list *i=head->nxt;i!=tail;i=i->nxt) P(i,OUT);
    fclose(IN),fclose(OUT);
    return 0;
}