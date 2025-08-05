#include<stdlib.h>

struct disjointSet{
    unsigned int n;
    unsigned int* parent;
    unsigned char* rank;
};

struct disjointSet newDisjointSet(const unsigned int n){
    struct disjointSet ds;
    ds.n = n;
    ds.parent = (unsigned int*)malloc((n + 1) * sizeof(unsigned int));
    for(unsigned int i = 1; i <= n; i++){
        ds.parent[i] = i;
    }
    ds.rank = (unsigned char*)calloc(n + 1, sizeof(unsigned char));
    return ds;
}

void freeDisjointSet(struct disjointSet* const ds){
    free(ds->parent);
    free(ds->rank);
}

unsigned int find(struct disjointSet* const ds, const unsigned int u){
    if(ds->parent[u] != u){
        ds->parent[u] = find(ds, ds->parent[u]);
    }
    return ds->parent[u];
}

void unionSet(struct disjointSet* const ds, const unsigned int u, const unsigned int v){
    unsigned int rootU = find(ds, u);
    unsigned int rootV = find(ds, v);
    if(rootU == rootV) return;
    if(ds->rank[rootU] < ds->rank[rootV]){
        ds->parent[rootU] = rootV;
        return;
    }
    if(ds->rank[rootU] > ds->rank[rootV]){
        ds->parent[rootV] = rootU;
        return;
    }
    ds->parent[rootV] = rootU;
    ds->rank[rootU]++;
}