#include <stdlib.h>
#include "graphs.h"

/**
 * graph_delete - Completely deletes a graph
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *vertex, *vnext;
	edge_t *edge, *enext;

	if (!graph)
		return;

	vertex = graph->vertices;
	while (vertex)
	{
		vnext = vertex->next;
		edge = vertex->edges;
		while (edge)
		{
			enext = edge->next;
			free(edge);
			edge = enext;
		}
		free(vertex->content);
		free(vertex);
		vertex = vnext;
	}
	free(graph);
}

