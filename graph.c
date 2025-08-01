#include<stdlib.h>

#define INITIAL_CAPACITY 2

struct graph{
    unsigned long long n;
    unsigned long long** adj;
    unsigned long long* capacity;
    unsigned long long* degree;
};

struct graph newGraph(const unsigned long long n){
    struct graph g;
    g.n = n;
    g.adj = (unsigned long long**)malloc((n + 1) * sizeof(unsigned long long *));
    g.capacity = (unsigned long long*)malloc((n + 1) * sizeof(unsigned long long));
    for(unsigned long long i = 1; i < n + 1; i++){
        g.adj[i] = (unsigned long long*)malloc(INITIAL_CAPACITY * sizeof(unsigned long long));
        g.capacity[i] = INITIAL_CAPACITY;
    }
    g.degree = (unsigned long long*)calloc(n + 1, sizeof(unsigned long long));
    return g;
}

void freeGraph(struct graph* g){
    for(unsigned long long i = 1; i < g->n + 1; i++){
        free(g->adj[i]);
    }
    free(g->adj);
    free(g->capacity);
    free(g->degree);
}

void addEdge(struct graph* const g, const unsigned long long u, const unsigned long long v){
    if(g->degree[u] == g->capacity[u]){
        g->capacity[u] *= 2;
        g->adj[u] = (unsigned long long*)realloc(g->adj[u], g->capacity[u] * sizeof(unsigned long long));
    }
    if(g->degree[v] == g->capacity[v]){
        g->capacity[v] *= 2;
        g->adj[v] = (unsigned long long*)realloc(g->adj[v], g->capacity[v] * sizeof(unsigned long long));
    }
    g->adj[u][g->degree[u]] = v;
    g->degree[u]++;
    g->adj[v][g->degree[v]] = u;
    g->degree[v]++;
}

unsigned long long findBridges(const struct graph* const g){
    unsigned long long* height = (unsigned long long*)calloc(g->n + 1, sizeof(unsigned long long));
    unsigned long long count = 0;

    unsigned long long dfs(const unsigned long long u, const unsigned long long p, const unsigned long long assigned_height){
        if(height[u] > 0) return height[u];
        height[u] = assigned_height;
        unsigned long long minheight = assigned_height;
        for(unsigned long long i = 0; i < g->degree[u]; i++){
            unsigned long long v = g->adj[u][i];
            if(v == p) continue;
            unsigned long long childLow = dfs(v, u, assigned_height + 1);
            if(childLow == assigned_height + 1){
                count++;
                continue;
            }
            if(childLow < minheight) minheight = childLow;
        }
        return minheight;
    }

    for(unsigned long long i = 1; i < g->n; i++) dfs(i, 0, 1);
    free(height);
    return count;
}