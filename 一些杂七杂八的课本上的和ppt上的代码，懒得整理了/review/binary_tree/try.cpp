#include<iostream>
using namespace std;
int main(){
    int a[2];
    a[0]=0;
    int top=0;
    a[++top]=a[top];
    cout<<a[0]<<","<<a[1]<<endl;
    cout<<top<<endl;
}