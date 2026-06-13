#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * find_vertex - Finds a vertex by its stored string
 * @graph: Pointer to the graph
 * @str: String to look for
 *
 * Return: Pointer to the matching vertex, or NULL if not found
 */
static vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex;

	for (vertex = graph->vertices; vertex; vertex = vertex->next)
		if (strcmp(vertex->content, str) == 0)
			return (vertex);
	return (NULL);
}

/**
 * add_one_edge - Appends a single edge from src to dest
 * @src: Source vertex
 * @dest: Destination vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int add_one_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *edge, *tmp;

	edge = malloc(sizeof(edge_t));
	if (!edge)
		return (0);
	edge->dest = dest;
	edge->next = NULL;

	if (!src->edges)
	{
		src->edges = edge;
	}
	else
	{
		for (tmp = src->edges; tmp->next; tmp = tmp->next)
			;
		tmp->next = edge;
	}
	src->nb_edges++;
	return (1);
}

/**
 * remove_last_edge - Removes and frees the last edge of a vertex
 * @vertex: Vertex to remove the last edge from
 */
static void remove_last_edge(vertex_t *vertex)
{
	edge_t *edge = vertex->edges, *prev = NULL;

	if (!edge)
		return;
	while (edge->next)
	{
		prev = edge;
		edge = edge->next;
	}
	if (prev)
		prev->next = NULL;
	else
		vertex->edges = NULL;
	free(edge);
	vertex->nb_edges--;
}

/**
 * graph_add_edge - Adds an edge between two vertices in a graph
 * @graph: Pointer to the graph
 * @src: String identifying the source vertex
 * @dest: String identifying the destination vertex
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
	vertex_t *vsrc, *vdest;

	if (!graph || !src || !dest)
		return (0);

	vsrc = find_vertex(graph, src);
	vdest = find_vertex(graph, dest);
	if (!vsrc || !vdest)
		return (0);

	if (!add_one_edge(vsrc, vdest))
		return (0);

	if (type == BIDIRECTIONAL && !add_one_edge(vdest, vsrc))
	{
		remove_last_edge(vsrc);
		return (0);
	}

	return (1);
}

