#include<stdio.h>

int board[20][20];

int Try_h(int x,int y,int k){
    if(y+3>19) return 0;
    if(board[x][y+1]!=k||board[x][y+2]!=k||board[x][y+3]!=k)
        return 0;
    if((y>1&&board[x][y-1]==0)||(y+4<=19&&board[x][y+4]==0)) return 1;
    return 0;
}
int Try_l(int x,int y,int k){
    if(x+3>19) return 0;
    if(board[x+1][y]!=k||board[x+2][y]!=k||board[x+3][y]!=k)
        return 0;
    if((x>1&&board[x-1][y]==0)||(x+4<=19&&board[x+4][y]==0)) return 1;
    return 0;
}
int Try_x(int x,int y,int k){
    if(x+3>19||y+3>19) return 0;
    if(board[x+1][y+1]!=k||board[x+2][y+2]!=k||board[x+3][y+3]!=k)
        return 0;
    if((x>1&&y>1&&board[x-1][y-1]==0)||(x+4<=19&&y+4<=19&&board[x+4][y+4]==0)) 
        return 1;
    return 0;
}
int Try_rx(int x,int y,int k){
    if(x+3>19||y-3<1) return 0;
    if(board[x+1][y-1]!=k||board[x+2][y-2]!=k||board[x+3][y-3]!=k)
        return 0;
    if((x>1&&y<19&&board[x-1][y+1]==0)||(x+4<=19&&y+4>=1&&board[x+4][y-4]==0)) 
        return 1;
    return 0;
}
int main(){
    for(int i=1;i<=19;++i){
        for(int j=1;j<=19;++j){
            scanf("%d",&board[i][j]);
        }
    }
    for(int i=1;i<=19;++i){
        for(int j=1;j<=19;++j){
            if(!board[i][j]) continue;
            if(Try_h(i,j,board[i][j])||Try_l(i,j,board[i][j])||Try_x(i,j,board[i][j])||Try_rx(i,j,board[i][j])){
                printf("%d:%d,%d\n",board[i][j],i,j);
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}