void QSort(int A[],int low,int high){
    /*
    int i=low;
    int j=high;
    while(i<j){
        int temp=A[i];
        while(i<j&&A[i]<A[j]) j--;
        if(i<j){A[i]=A[j];i++;}
        while (i<j&&A[i]<A[j]) i++;
        if(i<j){A[j]=A[i];j--;}
    }
    QSort(A,low,j-1);
    Qsort(A,i+1,high);
    */
   if(low>=high) return;
    int i,j;
    i=low;
    j=high;
    int temp=A[i];
    while(i<j){
        while(i<j&&A[j]>temp) j--;
        if(i<j){A[i]=A[j];i++;}
        while(i<j&&A[i]<temp) i++;
        if(i<j){A[j]=A[i];j--;}
    }
    A[i]=temp;
    QSort(A,low,j-1);
    QSort(A,i+1,high);
}