#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

int main(void)
{
	char data[] = {'H', 'o', 'l', 'b', 'e', 'r', 't', 'o', 'n'};
	size_t freq[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	size_t size = sizeof(data) / sizeof(data[0]);

	if (!huffman_codes(data, freq, size))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

