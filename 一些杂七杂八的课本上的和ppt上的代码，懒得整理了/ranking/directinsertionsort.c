 #include<sort.h>
 void DirectInsertionSort(ForSort A[],int n){
    int i,j;
    ForSort temp;
    for(i=1;i<n;i++){
        j=i;
        temp=A[i];
        while(j>0&&temp.key<A[j-1].key){
            A[j]=A[j-1];
            j--;
        }
        A[j]=temp;
    }
 }