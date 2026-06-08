#include "heap.h"

/**
 * get_parent - Finds the parent node for the next insertion
 * @root: root of the heap
 * @size: current size of the heap
 *
 * Return: pointer to the parent node where insertion happens
 */
static binary_tree_node_t *get_parent(binary_tree_node_t *root, size_t size)
{
	size_t path, bit;
	binary_tree_node_t *node = root;

	path = (size + 1) / 2;
	for (bit = 1; bit <= path; bit <<= 1)
		;
	bit >>= 2;
	while (bit > 1)
	{
		if (path & bit)
			node = node->right;
		else
			node = node->left;
		bit >>= 1;
	}
	return (node);
}

/**
 * swap_up - Swaps data up while child is smaller than parent
 * @heap: pointer to the heap
 * @node: node to sift up
 *
 * Return: final node holding the inserted data
 */
static binary_tree_node_t *swap_up(heap_t *heap, binary_tree_node_t *node)
{
	void *tmp;

	while (node->parent &&
	       heap->data_cmp(node->parent->data, node->data) > 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;
		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: pointer to the heap
 * @data: data to store in the new node
 *
 * Return: pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node, *parent;

	if (!heap || !data)
		return (NULL);

	if (!heap->root)
	{
		heap->root = binary_tree_node(NULL, data);
		if (!heap->root)
			return (NULL);
		heap->size++;
		return (heap->root);
	}

	parent = get_parent(heap->root, heap->size);
	node = binary_tree_node(parent, data);
	if (!node)
		return (NULL);

	if (!parent->left)
		parent->left = node;
	else
		parent->right = node;

	heap->size++;
	return (swap_up(heap, node));
}

