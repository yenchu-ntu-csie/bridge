#include<stdlib.h>

#define INITIAL_CAPACITY 2

struct graph{
    unsigned int n;
    unsigned int** adj;
    unsigned int* capacity;
    unsigned int* degree;
};

struct graph newGraph(const unsigned int n){
    struct graph g;
    g.n = n;
    g.adj = (unsigned int**)malloc((n + 1) * sizeof(unsigned int *));
    g.capacity = (unsigned int*)malloc((n + 1) * sizeof(unsigned int));
    for(unsigned int i = 1; i < n + 1; i++){
        g.adj[i] = (unsigned int*)malloc(INITIAL_CAPACITY * sizeof(unsigned int));
        g.capacity[i] = INITIAL_CAPACITY;
    }
    g.degree = (unsigned int*)calloc(n + 1, sizeof(unsigned int));
    return g;
}

void freeGraph(const struct graph* const g){
    for(unsigned int i = 1; i < g->n + 1; i++){
        free(g->adj[i]);
    }
    free(g->adj);
    free(g->capacity);
    free(g->degree);
}

void addEdge(const struct graph* const g, const unsigned int u, const unsigned int v){
    if(g->degree[u] == g->capacity[u]){
        g->capacity[u] *= 2;
        g->adj[u] = (unsigned int*)realloc(g->adj[u], g->capacity[u] * sizeof(unsigned int));
    }
    if(g->degree[v] == g->capacity[v]){
        g->capacity[v] *= 2;
        g->adj[v] = (unsigned int*)realloc(g->adj[v], g->capacity[v] * sizeof(unsigned int));
    }
    g->adj[u][g->degree[u]] = v;
    g->degree[u]++;
    g->adj[v][g->degree[v]] = u;
    g->degree[v]++;
}

unsigned int findBridges(const struct graph* const g){
    unsigned int* const height = (unsigned int*)calloc(g->n + 1, sizeof(unsigned int));
    unsigned int count = 0;

    unsigned int dfs(const unsigned int u, const unsigned int p, const unsigned int assigned_height){
        if(height[u] > 0) return height[u];
        height[u] = assigned_height;
        unsigned int minheight = assigned_height;
        for(unsigned int i = 0; i < g->degree[u]; i++){
            unsigned int v = g->adj[u][i];
            if(v == p) continue;
            unsigned int childLow = dfs(v, u, assigned_height + 1);
            if(childLow == assigned_height + 1){
                count++;
                continue;
            }
            if(childLow < minheight) minheight = childLow;
        }
        return minheight;
    }

    for(unsigned int i = 1; i < g->n; i++) dfs(i, 0, 1);
    free(height);
    return count;
}