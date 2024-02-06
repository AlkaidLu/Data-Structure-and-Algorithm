#include"listnode.h"
ListNode *CreateQueue();
void DeleteQueue(ListNode*rear);
void In(ListNode*&rear, int item);
int Out(ListNode*&rear);
int Length(ListNode*rear);

ListNode *CreateQueue(){
    ListNode* rear = new ListNode;
    rear->next=rear;
    rear->data=0;
    return rear;
}

void DeleteQueue(ListNode* rear){
    ListNode*p=rear->next;
    while(p!=rear){
        ListNode*tmp=p;
        delete tmp;
        p=p->next;
    }
    
}

void In(ListNode*&rear, int item){
    ListNode* newnode=new ListNode;
    newnode->data=item;
    newnode->next=rear->next;
    rear->next=newnode;
    rear=newnode;
}

int Out(ListNode*&rear){
    ListNode*del=rear->next;
    rear->next=rear->next->next;
    return del->data;
}

int Length(ListNode*rear){
    int cnt=0;
    ListNode*p=rear->next;
    while(p!=rear){
        cnt++;
        p=p->next;
    }
    return cnt;
}