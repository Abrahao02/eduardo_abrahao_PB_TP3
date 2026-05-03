#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct Trie{
    struct Trie *zero,*one;
    int route;
}Trie;

Trie* newNode(){
    Trie *n=malloc(sizeof(Trie));
    n->zero=n->one=NULL;
    n->route=-1;
    return n;
}

void insert(Trie *root,unsigned int ip,int prefix,int route){
    Trie *cur=root;
    for(int i=31;i>31-prefix;i--){
        int bit=(ip>>i)&1;
        if(bit==0){
            if(!cur->zero) cur->zero=newNode();
            cur=cur->zero;
        } else{
            if(!cur->one) cur->one=newNode();
            cur=cur->one;
        }
    }
    cur->route=route;
}

int lookup(Trie *root,unsigned int ip){
    Trie *cur=root;
    int last=-1;
    for(int i=31;i>=0;i--){
        if(cur->route!=-1) last=cur->route;
        int bit=(ip>>i)&1;
        cur=(bit==0)?cur->zero:cur->one;
        if(!cur) break;
    }
    return last;
}

int main(){
    Trie *root=newNode();
    insert(root,inet_addr("192.168.0.0"),16,1);
    insert(root,inet_addr("192.168.1.0"),24,2);

    int r=lookup(root,inet_addr("192.168.1.5"));
    printf("Rota encontrada: %d\n",r);
}