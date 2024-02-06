typedef int ElementType;
struct forsort{
    ElementType key;
};
typedef struct forsort ForSort;
void InitForSort(ForSort * FS,int a){
    FS->key=a;
}
