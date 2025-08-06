#include<stdio.h>
#include"graph.c"
#include"disjointset.c"

int main(){
    unsigned int n, m;
    if(scanf("%u%u", &n, &m) != 2) return 1;
    struct disjointSet ds1 = newDisjointSet(n);
    struct disjointSet ds2 = newDisjointSet(n);
    struct graph g = newGraph(n);
    for(unsigned int u, v; scanf("%u%u", &u, &v) == 2;){
        if(u < 1 || u > n || v < 1 || v > n || u == v) return 1;
        if(find(&ds2, u) == find(&ds2, v)) continue;
        if(find(&ds1, u) != find(&ds1, v)){
            unionSet(&ds1, u, v);
            addEdge(&g, u, v);
            continue;
        }
        unionSet(&ds2, u, v);
        addEdge(&g, u, v);
    }
    freeDisjointSet(&ds1);
    freeDisjointSet(&ds2);
    printf("%u\n", numBridges(&g));
    freeGraph(&g);
    return 0;
}