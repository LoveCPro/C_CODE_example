#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10

//定义结构体
typedef struct{
    int a[N];  //顺序表中的数
    int last; //指定顺序表中最后一位下标
} sqlist_t;

//创建链表
sqlist_t * sq_create(){
    sqlist_t * q = (sqlist_t *) malloc(sizeof(sqlist_t));
    q->last = -1;

    return q;
}
//判断顺序表是否满了， 满了返回1， 不满返回0
int sq_is_full(sqlist_t * q){

    return q->last == N - 1 ?1 : 0;
}
//判断链表是否为空 满：1  不满：0
int sq_is_empty(sqlist_t * sq){
    return sq->last == -1 ?1:0;
}
//插入数据
int sq_insert(sqlist_t * sq, int val){
    if(sq_is_full(sq)){
        printf("sq list is full\n");
        return -1;
    }
    sq->last++;
    sq->a[sq->last] = val;
    printf("last=%d, val=%d\n",sq->last, val);
    return 0;
}

//删除表中最后一位
int sq_del_last(sqlist_t * sq){
    sq->last--;
    return 0;
}

//将指定的位置的旧数据替换成新数据
int sq_old2new(sqlist_t *sq, int pos, int oldval, int newval){
    printf("pos=%d, old va;=%d, new val=%d\n", pos, oldval, newval);
    if(sq->a[pos - 1] != oldval){
        printf("pos %d  val is not %d\n", pos, oldval);
        return -1;
    }

    sq->a[pos - 1] = newval;
    return 0;
}
//获取某个位置的数据
int sq_getval_onpos(sqlist_t *sq, int pos){
    if(pos-1 > sq->last){
        printf("pos is out sq list\n");
        return -1;
    }
    printf("pos %d, val=%d\n", pos, sq->a[pos - 1]);
    return 0;
}

//按位置删除
int sq_del_onpos(sqlist_t * sq, int pos){
    int i= 0;
    if(sq_is_empty(sq)){
        printf("sq list is empty\n");
        return -1;
    }
    //判断如果是最后一位
    if(pos -1 == sq->last){
        sq_del_last(sq);
    }else{
        for(i = pos -1; i <= sq->last - 1; i++){
            printf("i=%d, last=%d\n", i, sq->last);
            sq->a[i] = sq->a[i + 1];
        }
        sq->last--;
    }
    return 0;
}

//删除重复的数据

//在指定的位置插入数据
int sq_insert_onpos(sqlist_t *sq, int pos, int val){
    int i= 0 ;
    if(sq_is_full(sq)){
        printf("sq list is full\n");
        return -1;
    }
    //判断是否为最后一位
    if(pos > N){
        printf("the sq list max num ：%d\n", N);
    }else if(pos - 2 == sq->last){
        sq->last++;
        sq->a[sq->last] = val;
    }else{
        sq->last++;
        for(i = sq->last; i>pos - 1; i--){
            sq->a[i] = sq->a[i - 1];
        }
        sq->a[pos - 1] = val;
    }
    return 0;
}
//遍历表
int sq_foreach_print(sqlist_t * sq){
    int i = 0;
    //判断链表是否为空
    if(sq_is_empty(sq)){
        printf("sq list is empty");
        return -1;
    }

    for(i = 0; i <=sq->last; i++){
        printf("num = %d, val=%d\n", i, sq->a[i]);
    }
    return 0;
}
int main(){
    //创建一个链表
    sqlist_t * q = sq_create();

    //链表中插入数据
    sq_insert(q, 0);
    sq_insert(q, 1);
    sq_insert(q, 2);
    sq_insert(q, 3);
    sq_insert(q, 4);
    sq_insert(q, 5);
    sq_insert(q, 6);
    sq_insert(q, 7);
    sq_insert(q, 8);

    //遍历链表
    // sq_foreach_print(q);
    //删除链表中最后一位
    //sq_del_last(q);
    //sq_foreach_print(q);

    //将指定位置的旧数据替换成新数据
    sq_old2new(q, 2, 2, 22);
    //sq_foreach_print(q);

    //sq_getval_onpos(q, 5);
    //sq_getval_onpos(q, 4);
    //sq_foreach_print(q);

   // sq_del_onpos(q, 5);
    //sq_foreach_print(q);

    //在指定位置插入数据
    //sq_insert_onpos(q, 3, 33);
    sq_insert_onpos(q, 10, 33);
    sq_foreach_print(q);

    free(q);
    return 0;
}   