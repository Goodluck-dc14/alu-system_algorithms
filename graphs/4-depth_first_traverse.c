#include <stdlib.h>
#include "graphs.h"

/**
 * dfs - Recursive depth-first helper
 * @vertex: Current vertex
 * @visited: Array marking visited vertices by index
 * @depth: Current depth from the starting vertex
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest depth reached from this vertex
 */
static size_t dfs(const vertex_t *vertex, char *visited, size_t depth,
		  void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *edge;
	size_t max = depth, sub;

	visited[vertex->index] = 1;
	action(vertex, depth);

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		if (!visited[edge->dest->index])
		{
			sub = dfs(edge->dest, visited, depth + 1, action);
			if (sub > max)
				max = sub;
		}
	}
	return (max);
}

/**
 * depth_first_traverse - Traverses a graph using depth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	char *visited;
	size_t max;

	if (!graph || !graph->vertices || !action)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
		return (0);

	max = dfs(graph->vertices, visited, 0, action);

	free(visited);
	return (max);
}

