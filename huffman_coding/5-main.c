#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

int main(void)
{
	symbol_t *symbol;

	symbol = symbol_create('d', 3);
	if (symbol == NULL)
		return (EXIT_FAILURE);
	printf("Symbol: data(%c) frequency(%lu)\n", symbol->data, symbol->freq);
	symbol = symbol_create('H', 98);
	if (symbol == NULL)
		return (EXIT_FAILURE);
	printf("Symbol: data(%c) frequency(%lu)\n", symbol->data, symbol->freq);
	return (EXIT_SUCCESS);
}

