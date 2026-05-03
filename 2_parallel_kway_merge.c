#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int* merge(int *a,int n,int *b,int m){
    int *res=malloc((n+m)*sizeof(int));
    int i=0,j=0,k=0;

    while(i<n && j<m)
        res[k++]= (a[i]<b[j])?a[i++]:b[j++];
    while(i<n) res[k++]=a[i++];
    while(j<m) res[k++]=b[j++];
    return res;
}

int* parallel_merge(int **lists,int *sizes,int k){
    if(k==1) return lists[0];

    int newk=(k+1)/2;
    int **newlists=malloc(newk*sizeof(int*));
    int *newsizes=malloc(newk*sizeof(int));

    #pragma omp parallel for
    for(int i=0;i<k/2;i++){
        newlists[i]=merge(lists[2*i],sizes[2*i],lists[2*i+1],sizes[2*i+1]);
        newsizes[i]=sizes[2*i]+sizes[2*i+1];
    }

    if(k%2){
        newlists[newk-1]=lists[k-1];
        newsizes[newk-1]=sizes[k-1];
    }

    return parallel_merge(newlists,newsizes,newk);
}

int main(){
    int k=4,n=5;
    int **lists=malloc(k*sizeof(int*));
    int sizes[4]={5,5,5,5};

    for(int i=0;i<k;i++){
        lists[i]=malloc(n*sizeof(int));
        for(int j=0;j<n;j++) lists[i][j]=i*10+j;
    }

    int *res=parallel_merge(lists,sizes,k);
    for(int i=0;i<20;i++) printf("%d ",res[i]);
}