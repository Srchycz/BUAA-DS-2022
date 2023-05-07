#include<stdio.h>
#include<stdlib.h>
int main(){
    if(system("fc results.txt results(example).txt"))
        puts("Wrong");
    else
        puts("AC");
    return 0;
}