#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"

int main(void)
{
	char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	size_t freq[] = {6, 11, 12, 13, 16, 36};
	size_t size = sizeof(data) / sizeof(data[0]);

	if (!huffman_codes(data, freq, size))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

