#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

/**
 * print_codes - Recursively traverses the tree printing each leaf's code
 * @node: current node
 * @code: buffer holding the current path
 * @depth: current depth / index in code buffer
 */
static void print_codes(binary_tree_node_t *node, char *code, int depth)
{
	symbol_t *symbol;

	if (!node)
		return;

	if (!node->left && !node->right)
	{
		symbol = (symbol_t *)node->data;
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
		return;
	}

	code[depth] = '0';
	print_codes(node->left, code, depth + 1);
	code[depth] = '1';
	print_codes(node->right, code, depth + 1);
}

/**
 * free_tree - Recursively frees the Huffman tree and its symbols
 * @node: current node
 */
static void free_tree(binary_tree_node_t *node)
{
	if (!node)
		return;
	free_tree(node->left);
	free_tree(node->right);
	free(node->data);
	free(node);
}

/**
 * huffman_codes - Builds the Huffman tree and prints the Huffman codes
 * @data: array of characters
 * @freq: array of associated frequencies
 * @size: size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[1024];

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_codes(root, code, 0);
	free_tree(root);
	return (1);
}

