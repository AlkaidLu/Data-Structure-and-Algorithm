#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STRING_SIZE 1024

struct cMyString {
    int length;
    char str[MAX_STRING_SIZE + 1];
};
typedef struct cMyString CMyString;
void init(CMyString* CS, char* s) {
    char* p1, * p2;
    for (CS->length = 0, p1 = CS->str, p2 = (char*)s; *p2; CS->length++)
        *p1++ = *p2++;
    *p1 = 0;
}

void GenKMPNext(int* next, CMyString* s) {
    int i=0,j=-1;
    next[0]=-1;
    while(i<s->length-1){
        while(j>=0&&s->str[i]!=s->str[j]){
            j=next[j];
        }
        i++;
        j++;
        if(s->str[i]==s->str[j]){
            next[i]=next[j];
        }
        else next[i]=j;
    }
}

int 