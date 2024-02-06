#include <iostream>

class BinaryTreeNode {
private:
    char data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
public:
    BinaryTreeNode(char value, BinaryTreeNode* l, BinaryTreeNode* r) : data(value), left(l), right(r) {}
    char GetData() { return data; }
    BinaryTreeNode* GetLeft() { return left; }
    BinaryTreeNode* GetRight() { return right; }
    void SetLeft(BinaryTreeNode* l) { left = l; }
    void SetRight(BinaryTreeNode* r) { right = r; }

};

class BinaryTree {
public:
    BinaryTreeNode* root;
    BinaryTree() : root(nullptr) {}
};

// Pre-order traversal
void Nlr(BinaryTreeNode* t) {
    if (t != nullptr) {
        std::cout << t->GetData() << " ";
        Nlr(t->GetLeft());
        Nlr(t->GetRight());
    }
}

// In-order traversal
void lNr(BinaryTreeNode* t) {
    if (t != nullptr) {
        lNr(t->GetLeft());
        std::cout << t->GetData() << " ";
        lNr(t->GetRight());
    }
}

// Post-order traversal
void lrN(BinaryTreeNode* t) {
    if (t != nullptr) {
        lrN(t->GetLeft());
        lrN(t->GetRight());
        std::cout << t->GetData() << " ";
    }
}

int main() {
    BinaryTree* bt = new BinaryTree;
    BinaryTreeNode* a = new BinaryTreeNode('a', nullptr, nullptr);
    BinaryTreeNode* b = new BinaryTreeNode('b', nullptr, nullptr);
    BinaryTreeNode* c = new BinaryTreeNode('c', nullptr, nullptr);
    BinaryTreeNode* d = new BinaryTreeNode('d', nullptr, nullptr);
    BinaryTreeNode* e = new BinaryTreeNode('e', nullptr, nullptr);

    a->SetLeft(b);
    a->SetRight(c);
    b->SetLeft(d);
    b->SetRight(e);


    bt->root = a;

    std::cout << "Pre-order traversal: ";
    Nlr(bt->root);
    std::cout << std::endl;

    std::cout << "In-order traversal: ";
    lNr(bt->root);
    std::cout << std::endl;

    std::cout << "Post-order traversal: ";
    lrN(bt->root);
    std::cout << std::endl;

    return 0;
}
