#include <stdio.h>
#include <stdlib.h>
//定义链表中的节点结构体
typedef  struct node{
    int val;
    struct node  * next;
}LinkList_t;

//创建空的链表
LinkList_t * LinkList_creat(){
    LinkList_t  * head = (LinkList_t *)malloc(sizeof(LinkList_t));
    head->next = head;

    return head;
}
//尾插入法
int linkList_loop_insert_end(LinkList_t * head, int val){
    //记录临时节点：
    LinkList_t * tmp = head;
    LinkList_t * node = (LinkList_t *)malloc(sizeof(LinkList_t));
    node->val = val;
    node->next = head;
    
    printf("func=%s, line=%d\n", __FUNCTION__, __LINE__);
    while(head->next != tmp){
        head = head->next;
    }
    printf("func=%s, line=%d\n", __FUNCTION__, __LINE__);

    head->next = node;


    printf("func=%s, line=%d\n", __FUNCTION__, __LINE__);

    return 0;
}

//有头遍历
int LinkList_loop_head_foreach(LinkList_t *head){
    LinkList_t *tmp = head;
    while(head->next != tmp){
        head = head->next;
        printf("val:%d\n",head->val); 
    }
    return 0;
}

//砍头函数
LinkList_t * LinkList_loop_nohead(LinkList_t * head){
    LinkList_t * tmp = head;

    while(head->next != tmp ){
        head = head->next;
    }

    head->next = tmp->next;

    free(tmp);
    tmp = NULL;
    return head->next;
}

//无头遍历
int LinkList_loop_nohead_foreach(LinkList_t * head){
    LinkList_t *tmp = head;
    while(head->next != tmp){
        printf("val:%d\n", head->val);
        head = head->next;
    }
    printf("val:%d\n", head->val);
    return 0;
}

int main(){
    LinkList_t * head = LinkList_creat();
    linkList_loop_insert_end(head, 5);
    linkList_loop_insert_end(head, 4);
    linkList_loop_insert_end(head, 3);
    linkList_loop_insert_end(head, 2);

    LinkList_loop_head_foreach(head);
    head = LinkList_loop_nohead(head);
    printf("砍头之后结果：\n");
  LinkList_loop_nohead_foreach(head);
    return 0;
}