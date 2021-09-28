#include <stdio.h>

struct struct_test{
    int x;
    int arr[2][1];
} typedef struct_test;


void update(struct_test s){
    s.x += 10;
    s.arr[0][0] = 10;
}

void p_update(struct_test* s){
    s->x += 10;
    s->arr[0][0] = 10;
}

struct_test* p_call_by_value(struct_test t1){
    return &t1;
}

void value_vs_pointer(struct_test t1){
    printf("%d at %p\n",t1.x,&t1);
}

void arrays_in_struct(struct_test t1){
    printf("[%d,%d] at %p\n",t1.arr[0][0],t1.arr[1][0],t1.arr);
}

void test_pointer(int* p){
    //printf("%d\n",*p); --> seg fault sometimes
    *p = 5;
    printf("%d\n",*p);
}

int main(){/*
    struct_test test = {0,{{1},{2}}};
    printf("%d, [%d, %d]\n",test.x,test.arr[0][0],test.arr[1][0]); 

    update(test);

    printf("%d, [%d, %d]\n",test.x,test.arr[0][0],test.arr[1][0]);

    p_update(&test);

    printf("%d, [%d, %d]\n",test.x,test.arr[0][0],test.arr[1][0]);*/
    struct_test t1 = {1};

    printf("%d\n",(&t1 == p_call_by_value(t1)));

    printf("%d at %p\n",t1.x,&t1);
    value_vs_pointer(t1);

    printf("Proves the call_by_value for struct.\nBut what for arrays in struct ?\n");

    printf("[%d,%d] at %p\n",t1.arr[0][0],t1.arr[1][0],t1.arr);

    arrays_in_struct(t1);

    int p = -1;

    test_pointer(&p);
    return 0;
}

