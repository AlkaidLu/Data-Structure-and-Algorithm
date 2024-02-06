#define ElementType char
struct threadedBTNode
{
    bool ltag, rtag;
    ElementType data;
    struct threadedBTNode *LeftChild, *RightChild;
    
};

void InorderThreaded(threadedBTNode *p, threadedBTNode **pre){
    //设置标记值的同时将二叉树线索化
    if(p !=nullptr){
        InorderThreaded(p->LeftChild, pre);
        if(* pre!=nullptr&&(*pre)->rtag==1){
            (*pre)->RightChild=p;
        }
        if(p->LeftChild==nullptr){
            p->ltag=1;
            p->LeftChild=*pre;
        }
        if(p->RightChild==nullptr){
            p->rtag=1;
        }
        *pre = p;
        InorderThreaded(p->RightChild, pre);
    }
}
