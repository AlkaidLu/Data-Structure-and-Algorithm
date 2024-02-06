#define ElementType char 
#include<iostream>
class BinaryTreeNode{
    private:
    ElementType data;
    BinaryTreeNode* LeftChild, *RightChild;
    public:
    BinaryTreeNode(){}
    BinaryTreeNode(ElementType e,BinaryTreeNode *l, BinaryTreeNode*r);
    ElementType Getdata();
    BinaryTreeNode* GetL();
    BinaryTreeNode* GetR();
};
BinaryTreeNode::BinaryTreeNode(ElementType e,BinaryTreeNode *l, BinaryTreeNode*r)
{
    data=e;
    LeftChild=l;
    RightChild=r;
}
ElementType BinaryTreeNode::Getdata(){
    return data;
}
BinaryTreeNode* BinaryTreeNode::GetL(){
    return LeftChild;
}
BinaryTreeNode* BinaryTreeNode::GetR(){
    return RightChild;
}

class BinaryTree{
    public:
    BinaryTreeNode *root;
    public:
    BinaryTree(){};
    BinaryTree(BinaryTree* bt);
    bool isEmpty(BinaryTree *bt);
    bool getRoot(BinaryTree *bt, ElementType *x);
};

BinaryTree::BinaryTree(BinaryTree* bt)
{
    bt=new BinaryTree;
    bt->root=nullptr;
}

bool BinaryTree::isEmpty(BinaryTree *bt){
    return ((bt->root)? false:true);
}

bool BinaryTree::getRoot(BinaryTree*bt, ElementType *x){
    if(bt->root){
        * x= bt->root->Getdata();
        return true;
    }
    else return false;
}

