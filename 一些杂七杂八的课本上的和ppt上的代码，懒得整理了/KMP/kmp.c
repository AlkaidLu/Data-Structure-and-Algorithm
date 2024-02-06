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
    int i = 0, j = -1;
    next[0] = -1;
    while (i < s->length - 1) {
        while (j >= 0 && s->str[i] != s->str[j]) {
            j = next[j];
        }
        i++;
        j++;
        if (s->str[i] == s->str[j]) {
            next[i] = next[j];
        }
        else next[i] = j;
    }
}
int Find(CMyString* CS, CMyString* s) {
    int i, j, * next = (int*)malloc(sizeof(int) * s->length);

    GenKMPNext(next, s);
    for (i = 0, j = 0; i < s->length && j < CS->length;) {
        if (s->str[i] == CS->str[i]) {
            i++;
            j++;
        }
        else if (next[i] >= 0)
            i = next[i];
        else {
            i = 0;
            j++;
        }
    }
    
    if (i >= s->length) {
        return j - s->length;
    }
    else {
        return -1;
    }
    
}
int main() {
    int* next=(int* )malloc(sizeof(int));
    char s[] = "aabaabbbab";
    CMyString* CS = (CMyString*)malloc(sizeof(CMyString));
    init( CS, s);
    char s1[] = "aabb";
    CMyString* CS1 = (CMyString*)malloc(sizeof(CMyString));
    init( CS1, s1);
    Find(CS, CS1);
    system("pause");
    return 0;
}
/*    GenKMPNext(next, CS);
    for (int i = 0; i < CS->length; i++) {
        printf("%d", next[i]);
    }
    */