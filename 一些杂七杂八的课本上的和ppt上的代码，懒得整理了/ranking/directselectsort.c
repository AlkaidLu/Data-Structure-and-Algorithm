#include<sort.h>

void DirectSelectSort(ForSort A[],int n){
    int i,j,k;
    ForSort temp;
    for(i=0;i<n-1;i++){
        k=i;
        for(j=i+1;j<n;j++){
            if(A[j].key<A[k].key)
            k=j;
        }
        if(i!=k){
            temp=A[k];
            A[k]=A[i];
            A[i]=temp;
        }
    }
}