#include "heap.h"

/**
 * free_tree - Recursively frees the binary tree nodes
 * @node: current node
 * @free_data: function to free node data, or NULL
 */
static void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;
	free_tree(node->left, free_data);
	free_tree(node->right, free_data);
	if (free_data)
		free_data(node->data);
	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: pointer to the heap to delete
 * @free_data: pointer to a function used to free the content of a node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;
	free_tree(heap->root, free_data);
	free(heap);
}

