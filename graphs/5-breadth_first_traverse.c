#include <stdlib.h>
#include "graphs.h"

/**
 * bfs_loop - Runs the breadth-first loop over a pre-seeded queue
 * @queue: BFS queue, already seeded with the starting vertex
 * @visited: Array marking visited vertices by index
 * @back: Number of vertices currently in the queue
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest depth reached
 */
static size_t bfs_loop(const vertex_t **queue, char *visited, size_t back,
		       void (*action)(const vertex_t *v, size_t depth))
{
	size_t front = 0, depth = 0, level_end, i;
	edge_t *edge;

	while (front < back)
	{
		level_end = back;
		for (i = front; i < level_end; i++)
		{
			action(queue[i], depth);
			for (edge = queue[i]->edges; edge; edge = edge->next)
				if (!visited[edge->dest->index])
				{
					visited[edge->dest->index] = 1;
					queue[back++] = edge->dest;
				}
		}
		front = level_end;
		if (front < back)
			depth++;
	}
	return (depth);
}

/**
 * breadth_first_traverse - Traverses a graph using breadth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	const vertex_t **queue;
	char *visited;
	size_t depth;

	if (!graph || !graph->vertices || !action)
		return (0);

	queue = malloc(sizeof(*queue) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!queue || !visited)
	{
		free(queue);
		free(visited);
		return (0);
	}

	queue[0] = graph->vertices;
	visited[graph->vertices->index] = 1;
	depth = bfs_loop(queue, visited, 1, action);

	free(queue);
	free(visited);
	return (depth);
}
