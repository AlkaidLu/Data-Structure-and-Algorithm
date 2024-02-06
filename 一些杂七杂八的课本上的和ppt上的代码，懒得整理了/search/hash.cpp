int Hash(int key){
    return key%10;
}
void HashSearch(T ht[],int key,int n){
    int k,j;

    k=Hash1(key);
    j=0;
    while(j<n&&ht[k].key!=key&&ht[k]key!=0){
        if(++k>=n)
        k=0;
        j++;
    }
    if(j==n){
        printf("Hash table has been overflowed!\n");
    }
    else if(ht[k].key==key)
        printf("hash:key %d is found,subscript is %d\n",key,k);
    else
    ht[k].key=key;

}