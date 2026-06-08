#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

/**
 * print_t - Stores recursively each level in an array of strings
 * @tree: Pointer to the node to print
 * @offset: Offset to print
 * @depth: Depth of the node
 * @s: Buffer
 * @print_data: Function to print node data
 *
 * Return: length of printed tree after process
 */
static int print_t(const binary_tree_node_t *tree, int offset, int depth,
		   char **s, int (*print_data)(char *, void *))
{
	char branch[12];
	int width, left, right, is_left, i;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = print_data(branch, tree->data);
	left = print_t(tree->left, offset, depth + 1, s, print_data);
	right = print_t(tree->right, offset + left + width, depth + 1, s,
			print_data);
	for (i = 0; i < width; i++)
		s[depth][offset + left + i] = branch[i];
	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	return (left + width + right);
}

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 * @print_data: Function to print node data
 */
void binary_tree_print(const binary_tree_node_t *tree,
		       int (*print_data)(char *, void *))
{
	char **s;
	size_t depth, i;
	const binary_tree_node_t *tmp;

	if (!tree)
		return;
	for (depth = 0, tmp = tree; tmp; tmp = tmp->left)
		depth++;
	for (tmp = tree; tmp; tmp = tmp->right)
		depth++;
	s = malloc(sizeof(*s) * (depth + 1));
	if (!s)
		return;
	for (i = 0; i < depth + 1; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 255);
	}
	print_t(tree, 0, 0, s, print_data);
	for (i = 0; i < depth + 1; i++)
	{
		size_t j = 254;

		while (j > 0 && s[i][j] == 32)
			s[i][j--] = '\0';
		if (s[i][j] != 32)
			printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}

