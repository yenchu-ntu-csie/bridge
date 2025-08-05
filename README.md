# Bridge Finder (Streaming Data Model)

This project is a C/C++ implementation to find bridges in a graph. A bridge in a graph is an edge that, if removed, increases the number of connected components.

## Project Structure

- **main.c**: The main entry point of the program.
- **graph.c**: Contains graph-related data structures and functions.
- **disjointset.c**: Implements the disjoint set (union-find) data structure.
- **main.cpp**: The same algorithm implemented in C++.
- **compile.sh**: Shell script to compile the program.
- **execute.sh**: Shell script to execute the program.

## How to Use

1. **Compile the Program**:
   ```bash
   ./compile.sh
   ```

2. **Run the Program**:
    ```bash
    ./execute.sh
    ```

## Dependencies

- GCC

## Algorithm Complexity

The algorithm implemented in this project has the following complexities:

- **Space Complexity**: $O(N)$, where N is the number of nodes in the graph. This is due to the storage requirements of the disjoint set and graph data structures. The algorithm works under the streaming data model, so most of the edges in the graph are not stored. Instead, only $O(N)$ edges are stored, significantly reducing the space complexity.
- **Time Complexity**: $O(N\alpha(N))$ in the worst case, where $\alpha$ is the inverse Ackermann function. This arises from the union-find operations with path compression and union by rank.
