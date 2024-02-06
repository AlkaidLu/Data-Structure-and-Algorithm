#define NULL nullptr
#include<IOSTREAM>
using namespace std;
struct ListNode
{
    int data;
    ListNode * next;
};
void Initialize(ListNode*N, int data,ListNode*ptr){
    N->data=data;
    N->next=ptr;
}
void InsertAfter(ListNode*N, ListNode*p){
    p->next=N->next;
    N->next=p;
}
void PrintList(ListNode*head){
    ListNode*a=head;
    while(a!=NULL){
        cout<<a->data<<"\t";
        a=a->next;
    }
    //cout<<"\n";
}