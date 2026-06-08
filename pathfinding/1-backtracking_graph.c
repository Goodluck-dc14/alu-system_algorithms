#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

/**
 * backtrack - Recursive helper to find a path in a graph via backtracking
 * @vertex: current vertex
 * @target: target vertex
 * @visited: array marking visited vertices by index
 * @path: queue building the path
 *
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(vertex_t const *vertex, vertex_t const *target,
		     char *visited, queue_t *path)
{
	edge_t *edge;
	char *city;

	if (!vertex || visited[vertex->index])
		return (0);

	visited[vertex->index] = 1;
	printf("Checking %s\n", vertex->content);

	if (vertex == target)
	{
		city = strdup(vertex->content);
		queue_push_front(path, city);
		return (1);
	}

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		if (backtrack(edge->dest, target, visited, path))
		{
			city = strdup(vertex->content);
			queue_push_front(path, city);
			return (1);
		}
	}
	return (0);
}

/**
 * backtracking_graph - Searches for first path from start to target in a graph
 * @graph: pointer to the graph
 * @start: starting vertex
 * @target: target vertex
 *
 * Return: queue of vertex names forming the path, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	queue_t *path;
	char *visited;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}

	if (!backtrack(start, target, visited, path))
	{
		queue_delete(path);
		path = NULL;
	}

	free(visited);
	return (path);
}

