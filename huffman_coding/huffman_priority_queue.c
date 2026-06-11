#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * symbol_cmp - Compares two nested nodes by their symbol frequency
 * @p1: first nested node (binary_tree_node_t *)
 * @p2: second nested node (binary_tree_node_t *)
 *
 * Return: negative, zero, or positive based on frequency comparison
 */
static int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1, *node2;
	symbol_t *symbol1, *symbol2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;
	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;

	if (symbol1->freq < symbol2->freq)
		return (-1);
	if (symbol1->freq > symbol2->freq)
		return (1);
	return (0);
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 * @data: array of characters
 * @freq: array of associated frequencies
 * @size: size of the arrays
 *
 * Return: pointer to the created min heap, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *nested;
	symbol_t *symbol;
	size_t i;

	if (!data || !freq || !size)
		return (NULL);

	heap = heap_create(symbol_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
			return (NULL);
		nested = binary_tree_node(NULL, symbol);
		if (!nested)
			return (NULL);
		if (!heap_insert(heap, nested))
			return (NULL);
	}
	return (heap);
}

