#include<stdio.h>

int test(int * a){
    *a = *a + 3;
}

int main(){
    int * b;
    *b = 0;
    test(b);
    printf("%d", *b);
}