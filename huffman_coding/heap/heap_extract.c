#include "heap.h"

/**
 * get_last_node - Finds the last node in level order of the heap
 * @heap: pointer to the heap
 *
 * Return: pointer to the last node, or NULL on failure
 */
static binary_tree_node_t *get_last_node(heap_t *heap)
{
	binary_tree_node_t **queue, *node = NULL;
	size_t front = 0, back = 0;

	queue = malloc(sizeof(*queue) * heap->size);
	if (!queue)
		return (NULL);

	queue[back++] = heap->root;
	while (front < back)
	{
		node = queue[front++];
		if (node->left)
			queue[back++] = node->left;
		if (node->right)
			queue[back++] = node->right;
	}
	free(queue);
	return (node);
}

/**
 * sift_down - Restores the min-heap property, keeping earlier nodes on ties
 * @heap: pointer to the heap
 * @node: node to sift down
 */
static void sift_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *child;
	void *tmp;

	while (node->left)
	{
		child = node->left;
		if (node->right &&
		    heap->data_cmp(node->right->data, child->data) < 0)
			child = node->right;
		if (heap->data_cmp(child->data, node->data) > 0)
			break;
		tmp = node->data;
		node->data = child->data;
		child->data = tmp;
		node = child;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: pointer to the heap
 *
 * Return: pointer to the data stored in the root node, or NULL
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last = get_last_node(heap);
	if (!last)
		return (NULL);

	heap->root->data = last->data;
	if (last->parent->right == last)
		last->parent->right = NULL;
	else
		last->parent->left = NULL;
	free(last);
	heap->size--;
	sift_down(heap, heap->root);
	return (data);
}

