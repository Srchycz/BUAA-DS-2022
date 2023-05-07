#include<stdio.h>
#include<string.h>
#include<math.h>
typedef unsigned int UIT;
typedef struct {
    int val,tim;
}Heap;
typedef struct{
    int w,id;
    int son[2];
}Huffuman;
Huffuman t[4000];
Heap heap[2020];
int tot,T=0,p=0;
char text[2020],k;
int cnt[128];
char key[128][20];
char temp[20];
char res[10000];
void Total(char *s){
    for(int i=0;i<k;++i)
        ++cnt[s[i]];
}
int cmp(Heap a,Heap b){
    if(a.val==b.val)
        return a.tim<b.tim;
    return a.val<b.val;
}//a<b返回1   a>b返回0
void Insert(Heap d){
    int now=++tot;
    while (now>1){
        if(!cmp(heap[now>>1],d))
            heap[now]=heap[now>>1],now>>=1;
        else break;
    }
    heap[now]=d;
}
Heap Top(){return heap[1];}
void Extract(){
    int now=1,nxt=2;
    Heap k=heap[tot--];
    while (nxt<=tot){
        if(nxt<tot&&!cmp(heap[nxt],heap[nxt|1])) nxt|=1;
        if(!cmp(k,heap[nxt])) heap[now]=heap[nxt],now=nxt,nxt<<=1;
        else break;
    }
    heap[now]=k;
}
void dfs(int idx,int dep){
    if(t[idx].son[0]==0&&t[idx].son[1]==0){
        temp[dep]='\0';
        strcpy(key[t[idx].id],temp);
        return;
    }
    if(t[idx].son[0]){
        temp[dep]='0';
        dfs(t[idx].son[0],dep+1);
    }
    if(t[idx].son[1]){
        temp[dep]='1';
        dfs(t[idx].son[1],dep+1);
    }
}
int main(){
    FILE *IN=fopen("input.txt","r"),*OUT=fopen("output.txt","w");
    fgets(text,2000,stdin);
    k=strlen(text);
    text[k-1]='\0';
    Total(text);
    for(int i=0;i<128;++i){
        if(cnt[i]){
            ++p;
            t[p].w=cnt[i],t[p].id=i;
            Insert((Heap){cnt[i],p});
        }
    }
    while (tot>1){
        Heap a=Top();Extract();
        Heap b=Top();Extract();
        ++p;
        t[p].son[0]=a.tim,t[p].son[1]=b.tim;
        t[p].w=a.val+b.val;
        Insert((Heap){t[p].w,p});
    }
    dfs(p,0);
    char *v=res;
    for(int i=0;i<k;++i)
        strcat(v,key[text[i]]);
    int res_len=strlen(res);
    int d=ceil((double)(res_len+1)/(double)16);
    for(int i=0;i<d;++i){
        UIT Q=0;
        for(int j=0;j<16&&j<=res_len;++j){
            int num=text[i*16+j]-'0';
            Q+=(num<<(15-j));
        }
        printf("%x",Q);
    }
    return 0;
}