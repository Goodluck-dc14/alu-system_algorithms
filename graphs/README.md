# C - Graphs

Implementation of an undirected/directed graph in C using an adjacency list,
with depth-first and breadth-first traversals.

## Functions

* `graph_create` - Allocates and initializes a graph
* `graph_add_vertex` - Adds a unique vertex storing a copy of a string
* `graph_add_edge` - Adds a unidirectional or bidirectional edge
* `graph_delete` - Frees the whole graph (vertices, edges, contents)
* `depth_first_traverse` - DFS from the first vertex, returns the max depth
* `breadth_first_traverse` - BFS from the first vertex, returns the max depth

## Requirements

* Ubuntu 14.04 LTS, gcc 4.8.4, flags `-Wall -Werror -Wextra -pedantic`
* Betty style, no global variables, max 5 functions per file

## Author

Goodluck-dc14
