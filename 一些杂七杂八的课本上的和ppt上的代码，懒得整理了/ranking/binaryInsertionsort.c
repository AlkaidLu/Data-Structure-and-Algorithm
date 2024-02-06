#include<sort.h>

void BinaryInsertionSort(ForSort A[],int n){
    int i,k,r;
    ForSort temp;
    for(int i=1;i<n;i++){
        temp=A[i];
        k=0;r=i-1;
        while(k<=r){
            int m;
            m=(k+r)/2;
            if(temp.key<A[m].key)
                r=m-1;
            else
            k=m+1;
         
        }
        for(r=i;r>k;r--){
            A[r]=A[r-1];
        }
        A[k]=temp;
    }
}