#include <stdio.h>
#include <stdlib.h>

//定义链表中每个节点的 结构体
 typedef struct node{
     int val;
     struct node* next;
 }LinkList_t;


//创建一个链表
LinkList_t * LinkList_Creat(){
    LinkList_t * head = (LinkList_t *)malloc(sizeof(LinkList_t));
    head->next = NULL;

    return head; 
}

//头插法
int LinkList_InsertHead(LinkList_t * head, int val){
    LinkList_t * node = (LinkList_t *)malloc(sizeof(LinkList_t));
    node->val = val;
    node->next = head->next;
    head->next = node;
    return 0;
}

//尾插法
int LinkList_InsertEnd(LinkList_t * head, int val){
    LinkList_t * node = (LinkList_t *)malloc(sizeof(LinkList_t));
    node->val = val;

    while(head->next != NULL){
        head = head->next;
    }
    node->next = head->next;
    head->next = node;
    return 0;
}
 
//判断链表是否为空。 空返回1，非空返回0
int  LinkList_is_empty(LinkList_t * head){
    
    return head->next == NULL?1:0;
}

//头删除法  （删除一个节点）
int  LinkList_DelHead(LinkList_t * head){
    //判断链表是否为空
    if(LinkList_is_empty(head)){
        printf("link list is empty\n");
        return -1;
    }

    //临时节点存放 head->next
    LinkList_t * temp;
    temp = head->next;

    head->next = head->next->next;
    free(temp);
    
    return 0;
}

//修改数据(将链表中某一旧数据修改成新的)
int LinkList_change(LinkList_t *head, int oldval, int newval){
    //判断链表不为空
    if(LinkList_is_empty(head)){
        printf("link link is empty\n");
        return -1;
    }
    while (head->next != NULL) {
        head = head->next;
        if(head->val == oldval){
            head->val = newval;
        }
    }
    return 0;
}

//按照顺序插入（当链表是递增时）
int LinkList_Insert_Sort(LinkList_t *head, int val){
  //判断链表不为空
    if(LinkList_is_empty(head)){
        printf("link link is empty\n");
        return -1;
    }
    
    LinkList_t * node = (LinkList_t *)malloc(sizeof(LinkList_t));
    node->val = val;
    while (head->next != NULL) {
        head = head->next;
        if(head->val <= val && val <= head->next->val){
            node->next = head->next;
            head->next = node;
            break;
        }
    }

    return 0;
}
//按照位置插入
int LinkList_Insert_pos(LinkList_t * head, int pos, int val){
    int i = 0;
    for(i = 0; i < pos - 1 ; i++){
        if(head->next == NULL){
            printf("LInk list has no pos:%d, i = %d\n", pos, i);
            return -1;
        }
        head = head->next;
    }

    LinkList_t * node = (LinkList_t *)malloc(sizeof(LinkList_t));
    node->val = val;

    node->next = head->next;

    head->next = node;
    return 0;
}

//数据反转
LinkList_t * LinkList_revert(LinkList_t * head){
    if(LinkList_is_empty(head)){
        printf("LInk list is empty\n");
        return NULL;
    }
    LinkList_t * newlist = (LinkList_t *)malloc(sizeof(LinkList_t));
    LinkList_t * tmp;
    while (head->next != NULL) {
        tmp = head->next;
        head->next = tmp->next;

        //采用头插法
        tmp->next = newlist->next;
        newlist->next = tmp;
    }

    return newlist;
}

//数据遍历
int LinkList_foreach_print(LinkList_t * head){
    while(head->next != NULL){
        head = head->next;
        printf("val=%d\n", head->val);
    }
    return 0;
}

int main(){
    //创建一个链表
    LinkList_t * head = LinkList_Creat();
    //插入数据
    LinkList_InsertHead(head, 8);
    LinkList_InsertHead(head, 6);
    LinkList_InsertHead(head, 3);
    LinkList_InsertHead(head, 2);
    LinkList_InsertHead(head, 1);

    //遍历输出链表
    LinkList_foreach_print(head);
    
    
    #if 0
    //头删除
    LinkList_DelHead(head);
    printf("头删除之后的结果：\n");
    LinkList_foreach_print(head);
    #endif

    #if 0
    //修改数据
    LinkList_change(head, 3, 33);
    printf("将3 修改成33后的结果：\n");
    LinkList_foreach_print(head);
    #endif

    #if 0
    //原来的联表示按照顺序排列，插入一个顺序数据
    LinkList_Insert_Sort(head, 5);
    printf("插入5后的结果：\n");
    LinkList_foreach_print(head);
    #endif

    #if 0
    //按照位置插入
    LinkList_Insert_pos(head, 3, 30);
    printf("在第三个节点插入数据30后的结果：\n");
    LinkList_foreach_print(head);
    #endif

     #if 1
    //数据反转
    LinkList_t * list =  LinkList_revert(head);
    printf("数据反转后的结果后的结果：\n");
    LinkList_foreach_print(list);
    #endif

    return 0;
}