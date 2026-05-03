#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char word[100];
    char meaning[256];
    struct Node *left, *right;
    int height;
} Node;

int max(int a,int b){ return a>b?a:b; }
int height(Node *n){ return n? n->height : 0; }

Node* newNode(char *w,char *m){
    Node *n = malloc(sizeof(Node));
    strcpy(n->word,w);
    strcpy(n->meaning,m);
    n->left=n->right=NULL;
    n->height=1;
    return n;
}

Node* rotateRight(Node *y){
    Node *x=y->left;
    Node *T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(height(y->left),height(y->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    return x;
}

Node* rotateLeft(Node *x){
    Node *y=x->right;
    Node *T2=y->left;
    y->left=x;
    x->right=T2;
    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;
    return y;
}

int getBalance(Node *n){
    return n? height(n->left)-height(n->right) : 0;
}

Node* insert(Node* node,char *word,char *meaning){
    if(!node) return newNode(word,meaning);

    if(strcmp(word,node->word)<0)
        node->left=insert(node->left,word,meaning);
    else if(strcmp(word,node->word)>0)
        node->right=insert(node->right,word,meaning);
    else return node;

    node->height=1+max(height(node->left),height(node->right));
    int balance=getBalance(node);

    if(balance>1 && strcmp(word,node->left->word)<0)
        return rotateRight(node);
    if(balance<-1 && strcmp(word,node->right->word)>0)
        return rotateLeft(node);
    if(balance>1 && strcmp(word,node->left->word)>0){
        node->left=rotateLeft(node->left);
        return rotateRight(node);
    }
    if(balance<-1 && strcmp(word,node->right->word)<0){
        node->right=rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* search(Node* root,char *word){
    if(!root || strcmp(root->word,word)==0) return root;
    if(strcmp(word,root->word)<0) return search(root->left,word);
    return search(root->right,word);
}

void inorder(Node *root){
    if(root){
        inorder(root->left);
        printf("%s -> %s\n",root->word,root->meaning);
        inorder(root->right);
    }
}

int countNodes(Node *root){
    if(!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main(){
    Node *root=NULL;
    root=insert(root,"CPU","Processador");
    root=insert(root,"RAM","Memoria");
    root=insert(root,"GPU","Placa grafica");

    printf("Dicionario:\n");
    inorder(root);

    Node *r=search(root,"RAM");
    if(r) printf("\nBusca RAM: %s\n",r->meaning);

    printf("Altura: %d\n",height(root));
    printf("Itens: %d\n",countNodes(root));
}