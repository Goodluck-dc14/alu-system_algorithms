#include "heap.h"

/**
 * find_insertion_parent - Finds parent for next insert via level-order scan
 * @heap: pointer to the heap
 *
 * Return: pointer to the node that will be the parent of the new node
 */
static binary_tree_node_t *find_insertion_parent(heap_t *heap)
{
	binary_tree_node_t **queue, *node, *parent = NULL;
	size_t front = 0, back = 0;

	queue = malloc(sizeof(*queue) * (heap->size + 1));
	if (!queue)
		return (NULL);

	queue[back++] = heap->root;
	while (front < back)
	{
		node = queue[front++];
		if (!node->left || !node->right)
		{
			parent = node;
			break;
		}
		queue[back++] = node->left;
		queue[back++] = node->right;
	}
	free(queue);
	return (parent);
}

/**
 * swap_up - Swaps data up while child is smaller than or equal to parent
 * @heap: pointer to the heap
 * @node: node to sift up
 *
 * Return: final node holding the inserted data
 */
static binary_tree_node_t *swap_up(heap_t *heap, binary_tree_node_t *node)
{
	void *tmp;

	while (node->parent &&
	       heap->data_cmp(node->parent->data, node->data) >= 0)
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

	parent = find_insertion_parent(heap);
	if (!parent)
		return (NULL);

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

