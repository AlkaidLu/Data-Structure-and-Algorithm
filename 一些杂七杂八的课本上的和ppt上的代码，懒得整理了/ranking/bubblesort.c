#include<sort.h>
#define FALSE 0
#define TRUE 1
void BubbleSort(ForSort A[],int n){
    int i,j;
    bool flag;
    ForSort temp;
    for(i=n-1,flag=1;i>0&&flag;i--){
        flag=FALSE;
        for(j=0;j<i;j++){
            if(A[j+1].key<A[j].key){
                flag=TRUE;
                temp=A[j+1];
                A[j+1]=A[j];
                A[j]=temp;
            }
        }
    }
}