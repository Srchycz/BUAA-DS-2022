#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
    int ratio;
    int pow;
    struct Node *next;
}node,*nodeptr;

nodeptr creatList(){
    nodeptr p,q,list=NULL;
    char x;
    do{
        q=(nodeptr)malloc(sizeof(node));
        scanf("%d%d%c",&q->ratio,&q->pow,&x);
        q->next=NULL;
        if(list==NULL) list=p=q;
        else p->next=q;
        p=q;
    }while(x!='\n');
    return list;
}

int main(){
    nodeptr l1=NULL,l2=NULL;
    bool flag=1;
    l1=creatList();
    l2=creatList();
    // printf("%d ",l2->pow);
    for(nodeptr p1=l1;p1!=NULL;p1=p1->next){
        for(nodeptr p0=NULL,p2=l2;p2!=NULL;p2=p2->next){
            if(flag){
                p1->ratio*=p2->ratio;
                p1->pow+=p2->pow;
                flag=0;
            }
            else{
                p0->ratio=p1->ratio*p2->ratio;
                p0->pow=p1->pow+p2->pow;
                nodeptr p3=NULL,temp=NULL;
                for(p3=l1;p3!=NULL;temp=p3,p3=p3->next){
                    printf("%p ",p0);
                    if((p0->pow) > (p3->pow)){
                        if(p3==l1){p0->next=l1;l1=p0;break;}
                        else{p0->next=p3;temp->next=p0;break;}
                    }
                    else if(p0->pow==p3->pow){
                        p3->ratio+=p0->ratio;
                        break;
                    }
                }
                if(p3==NULL) 
                temp->next=p0;
            }
        }
    }
    for(nodeptr p1=l1;p1!=NULL;p1=p1->next){
        printf("%d %d ",p1->ratio,p1->pow);
    }
    return 0;
}