#include <stdlib.h>
#include "heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts the two least frequent nodes and
 * inserts a new merged node back into the priority queue
 * @priority_queue: pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_nested;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t sum;

	if (!priority_queue)
		return (0);

	node1 = (binary_tree_node_t *)heap_extract(priority_queue);
	node2 = (binary_tree_node_t *)heap_extract(priority_queue);
	if (!node1 || !node2)
		return (0);

	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;
	sum = symbol1->freq + symbol2->freq;

	new_symbol = symbol_create(-1, sum);
	if (!new_symbol)
		return (0);

	new_nested = binary_tree_node(NULL, new_symbol);
	if (!new_nested)
	{
		free(new_symbol);
		return (0);
	}

	new_nested->left = node1;
	new_nested->right = node2;
	node1->parent = new_nested;
	node2->parent = new_nested;

	if (!heap_insert(priority_queue, new_nested))
		return (0);
	return (1);
}

