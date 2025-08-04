#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class DisjointSet {
public:
    DisjointSet(unsigned int n) : n(n), parent(n + 1), rank(n + 1, 0) {
        for (unsigned int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    unsigned int find(unsigned int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSet(unsigned int u, unsigned int v) {
        unsigned int rootU = find(u);
        unsigned int rootV = find(v);
        if (rootU == rootV) return;
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            ++rank[rootU];
        }
    }

private:
    unsigned int n;
    std::vector<unsigned int> parent;
    std::vector<unsigned char> rank;
};

class Graph {
public:
    Graph(unsigned int n) : n(n), adj(n + 1), degree(n + 1, 0) {}

    void addEdge(unsigned int u, unsigned int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++degree[u];
        ++degree[v];
    }

    unsigned int findBridges() const {
        std::vector<unsigned int> height(n + 1, 0);
        unsigned int count = 0;

        for (unsigned int i = 1; i <= n; ++i) {
            if (height[i] == 0) {
                dfs(i, 0, 1, height, count);
            }
        }
        return count;
    }

private:
    unsigned int n;
    std::vector<std::vector<unsigned int>> adj;
    std::vector<unsigned int> degree;

    unsigned int dfs(unsigned int u, unsigned int p, unsigned int assigned_height, std::vector<unsigned int>& height, unsigned int& count) const {
        if (height[u] > 0) return height[u];
        height[u] = assigned_height;
        unsigned int minheight = assigned_height;
        for (unsigned int v : adj[u]) {
            if (v == p) continue;
            unsigned int childLow = dfs(v, u, assigned_height + 1, height, count);
            if (childLow == assigned_height + 1) {
                ++count;
                continue;
            }
            minheight = std::min(minheight, childLow);
        }
        return minheight;
    }
};

int main() {
    unsigned int n, m;
    if (!(std::cin >> n >> m)) return 1;

    DisjointSet ds1(n), ds2(n);
    Graph g(n);

    for (unsigned int u, v; std::cin >> u >> v;) {
        if (u < 1 || u > n || v < 1 || v > n || u == v) return 1;
        if (ds2.find(u) == ds2.find(v)) continue;
        if (ds1.find(u) != ds1.find(v)) {
            ds1.unionSet(u, v);
            g.addEdge(u, v);
            continue;
        }
        ds2.unionSet(u, v);
        g.addEdge(u, v);
    }

    std::cout << g.findBridges() << std::endl;
    return 0;
}
