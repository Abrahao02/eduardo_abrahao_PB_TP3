#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define CAPACITY 50
#define MAX_POINTS 100000

typedef struct Point{
    float x,y;
}Point;

typedef struct Node{
    float xmin,xmax,ymin,ymax;
    Point *points;
    int count;
    struct Node *nw,*ne,*sw,*se;
}Node;

Node* createNode(float xmin,float xmax,float ymin,float ymax){
    Node* n=malloc(sizeof(Node));
    n->xmin=xmin; n->xmax=xmax; n->ymin=ymin; n->ymax=ymax;
    n->points=malloc(CAPACITY*sizeof(Point));
    n->count=0;
    n->nw=n->ne=n->sw=n->se=NULL;
    return n;
}

void subdivide(Node *n){
    float midx=(n->xmin+n->xmax)/2;
    float midy=(n->ymin+n->ymax)/2;
    n->nw=createNode(n->xmin,midx,midy,n->ymax);
    n->ne=createNode(midx,n->xmax,midy,n->ymax);
    n->sw=createNode(n->xmin,midx,n->ymin,midy);
    n->se=createNode(midx,n->xmax,n->ymin,midy);
}

void insert(Node *n,Point p){
    if(n->count<CAPACITY){
        n->points[n->count++]=p;
        return;
    }
    if(!n->nw) subdivide(n);

    if(p.x<(n->xmin+n->xmax)/2){
        if(p.y<(n->ymin+n->ymax)/2) insert(n->sw,p);
        else insert(n->nw,p);
    } else {
        if(p.y<(n->ymin+n->ymax)/2) insert(n->se,p);
        else insert(n->ne,p);
    }
}

int main(){
    Node *root=createNode(0,1000,0,1000);

    #pragma omp parallel for
    for(int i=0;i<MAX_POINTS;i++){
        Point p={rand()%1000,rand()%1000};
        #pragma omp critical
        insert(root,p);
    }

    printf("Quadtree criada com 100k pontos\n");
}