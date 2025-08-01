#include<stdio.h>
#include"graph.c"

int main(){
    unsigned long long n, m;
    if(scanf("%llu %llu", &n, &m) == EOF) return 1;
    struct graph g = newGraph(n);
    for(unsigned long long u, v; scanf("%llu %llu", &u, &v) == 2;){
        addEdge(&g, u, v);
    }
    printf("%llu\n", findBridges(&g));
    return 0;
}