#include<sort.h>

void ShellSort(ForSort A[],int n,int s){
    int i,j,k;
    ForSort temp;
    for(k=s;k>0;k>>=1){
        for(i=k;i<n;i++){
            temp=A[i];
            j=i-k;
            while(j>=0&&temp.key<A[j].key){
                A[j+k]=A[j];
                j-=k;
            }
            A[j+k]=temp;
        }
        
    }
}