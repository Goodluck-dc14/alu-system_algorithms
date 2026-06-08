# C - Huffman coding

This project implements Huffman coding in C, building from a min binary heap up
to generating Huffman codes for a set of characters and their frequencies.

## Description

Huffman coding is a compression technique that assigns shorter binary codes to
more frequent characters and longer codes to less frequent ones. This project
builds the supporting data structures (a min binary heap used as a priority
queue) and then uses them to construct a Huffman tree and extract the codes.

## Requirements

* Compiled on Ubuntu 14.04 LTS with gcc 4.8.4
* Flags: `-Wall -Werror -Wextra -pedantic`
* Betty style
* No global variables
* No more than 5 functions per file (heap insert and extract allow up to 7)
* Header files: `huffman.h` and `heap/heap.h`

## Files

| File | Description |
| ---- | ----------- |
| `heap/heap.h` | Header with heap and binary tree node structures |
| `heap/heap_create.c` | Creates a heap data structure |
| `heap/binary_tree_node.c` | Creates a generic binary tree node |
| `heap/heap_insert.c` | Inserts a value into a min binary heap |
| `heap/heap_extract.c` | Extracts the root value of a min binary heap |
| `heap/heap_delete.c` | Deallocates a heap |
| `huffman.h` | Header with the symbol structure |
| `symbol.c` | Creates a symbol structure |
| `huffman_priority_queue.c` | Builds the priority queue for Huffman coding |
| `huffman_extract_and_insert.c` | Extracts two nodes and inserts a merged one |
| `huffman_tree.c` | Builds the Huffman tree |
| `huffman_codes.c` | Builds the tree and prints the Huffman codes |

## Data structures

A min binary heap stores nodes so the smallest value is always at the root. Used
as a priority queue, it keeps the least frequent symbol at the top, which is what
the Huffman algorithm needs at each step.

## Author

Goodluck-dc14
