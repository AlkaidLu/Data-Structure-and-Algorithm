#include<IOSTREAM>
using namespace std;
#include"listnode.h"

ListNode* reverseList(ListNode* head){
    //递归法
    if (head == NULL || head ->next == NULL)
    {
        return head;
    }
    else
    {
        ListNode * newHead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
}

int main(){
    ListNode*a[10];
    for(int i=0;i<10;i++){
        a[i]=new ListNode;
        Initialize(a[i],i,NULL);
    }
    for(int i=0;i<9;i++){
        InsertAfter(a[i],a[i+1]);
    }
    ListNode*head=a[0];
    ListNode*tail=a[9];
    a[9]=NULL;
    PrintList(head);
    ListNode *newnode=reverseList(head);
    cout<<endl;
    PrintList(newnode);
    return 0;
}
