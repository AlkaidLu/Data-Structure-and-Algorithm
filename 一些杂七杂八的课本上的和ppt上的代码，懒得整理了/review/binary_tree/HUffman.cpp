struct huffmannode{
    int weight;
    int tag,LeftChild,RightChild;
};
typedef struct huffmannode Huffmannode;

void InitHuffmannode(Huffmannode * h, int t, int l, int r){
    h->tag=t;
    h->LeftChild=l;
    h->RightChild=r;
}

struct huffmantree{
    int root;
};

typedef struct huffmantree Huffmantree;

void InitHuffmantree(Huffmantree* ht, int r){
    ht->root=r;
}

void makeHuffmantree(Huffmantree * ht, int a[], Huffmannode b[], int n){
    int i,j,m1,m2,x1,x2;
    for(i=0;i<n;i++){
        b[i].weight=a[i];
    }
    for(i=1;i<=n-1;i++){
        m1=m2=32767;
        x1=x2=-1;
        for(j=0;j<n+i-1;j++){
        if(b[j].weight<m1&&b[j].tag==0){
            m2=m1;
            x2=x1;
            m1=b[j].weight;
            x1=j;
        }
        else if(b[j].weight<m2&&b[j].tag==0){
            m2=b[j].weight;
            x2=j;
        }
    }
    b[x1].tag=1;
    b[x2].tag=1;

    b[n-1+i].weight=b[x1].weight+b[x2].weight;
    b[n-1+i].LeftChild=x1;
    b[n-1+i].RightChild=x2;
    b[n-1+i].tag=0;
    }
    ht->root=2*n-2;
}
//在构造哈夫曼树的过程中，通常会使用一个数组来表示哈夫曼树的结构。在这个数组中，前n个元素用来存储叶子节点的权值，接下来的n-1个元素用来存储内部节点的权值和构造子树的过程。

//在构造子树的过程中，b[n-1+i]表示数组b中从第n-1+i个元素开始的位置，这些元素用来构造当前子树。i表示当前子树的索引，从0开始递增。

//而ht->root=2*n-2表示哈夫曼树的根节点在数组中的位置。在一棵哈夫曼树中，总共有2*n-1个节点，其中叶子节点有n个，内部节点有n-1个。因此，根节点的索引为2*n-2，即数组中的倒数第二个位置。这个值是根据哈夫曼树的特性计算得出的，用来表示根节点在数组中的位置。

