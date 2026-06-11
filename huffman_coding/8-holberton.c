#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));

int symbol_print(char *buffer, void *data)
{
	symbol_t *symbol;
	char c;
	int length;

	symbol = (symbol_t *)data;
	c = symbol->data;
	if (c == -1)
		c = '$';
	length = sprintf(buffer, "(%c/%lu)", c, symbol->freq);
	return (length);
}

int main(void)
{
	binary_tree_node_t *root;
	char data[] = {'H', 'o', 'l', 'b', 'e', 'r', 't', 'o', 'n'};
	size_t freq[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	size_t size = sizeof(data) / sizeof(data[0]);

	root = huffman_tree(data, freq, size);
	if (!root)
		return (EXIT_FAILURE);
	binary_tree_print(root, symbol_print);
	return (EXIT_SUCCESS);
}

