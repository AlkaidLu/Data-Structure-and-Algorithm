#include"binarytree.h"
//前序遍历算法
void Nlr(BinaryTreeNode *t){
    BinaryTreeNode* stack[100];
    unsigned top=0;
    stack[0]=t;
    do{
        while(stack[top]!=nullptr){
            printf("%c",stack[top]->Getdata());
            stack[++top]=stack[top]->GetL();
        }
        if(top>0){
            stack[top]=stack[--top]->GetR();
        }
    }while(top>0||stack[top]!=nullptr);
}
//中序遍历
void lNr(BinaryTreeNode *t){
    BinaryTreeNode* stack[100];
    unsigned top=0;
    stack[0]=t;
    do{
        while(stack[top]!=nullptr){
            stack[++top]=stack[top]->GetL();
        }
        if(top>0){
            printf("%c",stack[--top]->Getdata());
            stack[top]=stack[top]->GetR();
        }
    }while(top>0||stack[top]!=nullptr);
}
//后序遍历
void lrN(BinaryTreeNode * t){
    BinaryTreeNode* stack[100];
    unsigned tag[100];
    unsigned top=0;//tag==1，说明当前结点的子结点都访问过了

    stack[0]=t;
    tag[0]=0;
    do{
        while(stack[top]!=NULL){
            stack[++top]=stack[top]->GetL();
            tag[top]=0;//注意设当前top的tag为0
        }
        while(tag[top-1]==1){
            printf("%c",stack[--top]->Getdata());
        }
        if(top>0){
            stack[top]=stack[top-1]->GetR();
            tag[top-1]=1;//注意设置为1的是当前top的上一个
            tag[top]=0;//注意设当前top的tag为0
        }
    }while(top!=0);
}

int main(){
    BinaryTree*bt=new BinaryTree;
    BinaryTreeNode* d=new BinaryTreeNode('d',NULL,NULL);
    BinaryTreeNode* e=new BinaryTreeNode('e',NULL,NULL);
    BinaryTreeNode* b=new BinaryTreeNode('b', d, e);
    BinaryTreeNode* c=new BinaryTreeNode('c',NULL,NULL);
    BinaryTreeNode* a=new BinaryTreeNode('a',b,c);
    bt->root=a;

    printf("PREOrder:\n");
    Nlr(bt->root);
    printf("\n");
    
    printf("INOrder:\n");
    lNr(bt->root);
    printf("\n");

    printf("AFTEROrder:\n");
    lrN(bt->root);
    printf("\n");

    return 0;
}