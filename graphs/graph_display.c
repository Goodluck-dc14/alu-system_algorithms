#include <stdio.h>
#include "graphs.h"

/**
 * graph_display - Displays the content of a graph
 * @graph: Pointer to the graph to display
 */
void graph_display(const graph_t *graph)
{
	vertex_t *vertex;
	edge_t *edge;

	if (!graph)
		return;
	printf("Number of vertices: %lu\n", graph->nb_vertices);
	vertex = graph->vertices;
	while (vertex)
	{
		printf("[%lu] %s", vertex->index, vertex->content);
		edge = vertex->edges;
		while (edge)
		{
			printf("->%lu", edge->dest->index);
			edge = edge->next;
		}
		printf("\n");
		vertex = vertex->next;
	}
}

