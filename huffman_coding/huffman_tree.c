#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_tree - Builds the Huffman tree
 * @data: array of characters
 * @freq: array of associated frequencies
 * @size: size of the arrays
 *
 * Return: pointer to the root node of the Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *root;

	priority_queue = huffman_priority_queue(data, freq, size);
	if (!priority_queue)
		return (NULL);

	while (priority_queue->size > 1)
	{
		if (!huffman_extract_and_insert(priority_queue))
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	root = (binary_tree_node_t *)heap_extract(priority_queue);
	heap_delete(priority_queue, NULL);
	return (root);
}

