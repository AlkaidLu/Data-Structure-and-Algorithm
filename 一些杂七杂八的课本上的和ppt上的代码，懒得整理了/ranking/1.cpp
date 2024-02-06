#include<CMATH>
#include<iostream>
using namespace std;
int main(){
    bool flag=1;
    for(int i=0;i<100000;i++){
        if(ceil(log(i+1)/log(2))!=floor(log(i))+1){
            flag=0;
        }
    }
    if(flag==0){
        cout<<"error.";
    }
}