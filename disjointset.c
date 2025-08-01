#include<stdlib.h>

struct disjointSet{
    unsigned long long n;
    unsigned long long* parent;
    unsigned char* rank;
};

struct disjointSet newDisjointSet(const unsigned long long n){
    struct disjointSet ds;
    ds.n = n;
    ds.parent = (unsigned long long*)malloc((n + 1) * sizeof(unsigned long long));
    for(unsigned long long i = 1; i <= n; i++){
        ds.parent[i] = i;
    }
    ds.rank = (unsigned char*)calloc(n + 1, sizeof(unsigned char));
    return ds;
}

void freeDisjointSet(struct disjointSet* const ds){
    free(ds->parent);
    free(ds->rank);
}

unsigned long long find(struct disjointSet* const ds, const unsigned long long u){
    if(ds->parent[u] != u){
        ds->parent[u] = find(ds, ds->parent[u]);
    }
    return ds->parent[u];
}

void unionSet(struct disjointSet* const ds, const unsigned long long u, const unsigned long long v){
    unsigned long long rootU = find(ds, u);
    unsigned long long rootV = find(ds, v);
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