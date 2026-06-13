#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 * @graph: Pointer to the graph to add the vertex to
 * @str: String to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *tmp;

	if (!graph || !str)
		return (NULL);

	for (tmp = graph->vertices; tmp; tmp = tmp->next)
		if (strcmp(tmp->content, str) == 0)
			return (NULL);

	vertex = malloc(sizeof(vertex_t));
	if (!vertex)
		return (NULL);

	vertex->content = strdup(str);
	if (!vertex->content)
	{
		free(vertex);
		return (NULL);
	}
	vertex->index = graph->nb_vertices;
	vertex->nb_edges = 0;
	vertex->edges = NULL;
	vertex->next = NULL;

	if (!graph->vertices)
	{
		graph->vertices = vertex;
	}
	else
	{
		for (tmp = graph->vertices; tmp->next; tmp = tmp->next)
			;
		tmp->next = vertex;
	}
	graph->nb_vertices++;

	return (vertex);
}

