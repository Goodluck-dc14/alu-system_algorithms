# C - Pathfinding

This project implements pathfinding algorithms in C, finding a route from a
starting point to a target point across both 2D arrays and graphs.

## Description

Pathfinding is the search for a route between two points. This project covers
three approaches, from the naive to the efficient, to show how algorithm choice
affects performance.

## Requirements

* Compiled on Ubuntu 14.04 LTS with gcc 4.8.4
* Flags: `-Wall -Werror -Wextra -pedantic`
* Betty style
* No global variables
* No more than 5 functions per file
* Linked with `-lgraphs` and `-lqueues`

## Files

| File | Description |
| ---- | ----------- |
| `pathfinding.h` | Header file with prototypes and the `point_t` struct |
| `0-backtracking_array.c` | Finds first path in a 2D array using backtracking |
| `1-backtracking_graph.c` | Finds first path in a graph using backtracking |
| `2-dijkstra_graph.c` | Finds shortest path in a graph using Dijkstra's algorithm |

## Tasks

### 0. Backtracking - Array
Searches for the first path from start to target in a 2D array, exploring
neighbours in the order RIGHT, BOTTOM, LEFT, TOP. Uses recursive backtracking.

### 1. Backtracking - Graph
Searches for the first path from start to target in a graph, following edges
between vertices. Uses recursive backtracking.

### 2. Dijkstra's - Graph
Searches for the shortest path from start to target in a weighted graph using
Dijkstra's algorithm.

## Compilation
