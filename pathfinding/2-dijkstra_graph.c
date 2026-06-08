#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "pathfinding.h"

/**
 * get_next - Finds the unvisited vertex with the smallest distance
 * @nb: number of vertices
 * @dist: array of distances
 * @visited: array marking visited vertices
 *
 * Return: index of the closest unvisited vertex, or -1 if none
 */
static int get_next(size_t nb, size_t *dist, char *visited)
{
	size_t i, best = ULONG_MAX;
	int idx = -1;

	for (i = 0; i < nb; i++)
	{
		if (!visited[i] && dist[i] < best)
		{
			best = dist[i];
			idx = (int)i;
		}
	}
	return (idx);
}

/**
 * build_path - Builds the path queue by walking back through via array
 * @graph: pointer to the graph
 * @target: target vertex
 * @via: array of predecessor indices
 * @path: queue to fill
 */
static void build_path(graph_t *graph, vertex_t const *target,
		       long *via, queue_t *path)
{
	vertex_t *v;
	size_t cur = target->index;

	while (1)
	{
		for (v = graph->vertices; v && v->index != cur; v = v->next)
			;
		queue_push_front(path, strdup(v->content));
		if (via[cur] == -1)
			break;
		cur = (size_t)via[cur];
	}
}

/**
 * run_dijkstra - Runs the main Dijkstra loop over the graph
 * @graph: pointer to the graph
 * @start: starting vertex
 * @target: target vertex
 * @dist: array of distances
 * @via: array of predecessor indices
 * @visited: array marking visited vertices
 */
static void run_dijkstra(graph_t *graph, vertex_t const *start,
			 vertex_t const *target, size_t *dist,
			 long *via, char *visited)
{
	int cur;
	vertex_t *v;
	edge_t *e;

	while ((cur = get_next(graph->nb_vertices, dist, visited)) != -1)
	{
		for (v = graph->vertices; v && v->index != (size_t)cur;
		     v = v->next)
			;
		visited[cur] = 1;
		printf("Checking %s, distance from %s is %lu\n",
		       v->content, start->content, dist[cur]);
		if (v == target)
			break;
		for (e = v->edges; e; e = e->next)
			if (dist[cur] + e->weight < dist[e->dest->index])
			{
				dist[e->dest->index] = dist[cur] + e->weight;
				via[e->dest->index] = cur;
			}
	}
}

/**
 * dijkstra_graph - Searches for the shortest path from start to target
 * @graph: pointer to the graph
 * @start: starting vertex
 * @target: target vertex
 *
 * Return: queue of vertex names forming the shortest path, or NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	queue_t *path;
	size_t *dist, i;
	long *via;
	char *visited;

	if (!graph || !start || !target)
		return (NULL);
	dist = malloc(sizeof(size_t) * graph->nb_vertices);
	via = malloc(sizeof(long) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!dist || !via || !visited)
		return (free(dist), free(via), free(visited), NULL);
	for (i = 0; i < graph->nb_vertices; i++)
		dist[i] = ULONG_MAX, via[i] = -1;
	dist[start->index] = 0;
	run_dijkstra(graph, start, target, dist, via, visited);
	path = queue_create();
	if (dist[target->index] != ULONG_MAX)
		build_path(graph, target, via, path);
	else
		queue_delete(path), path = NULL;
	free(dist), free(via), free(visited);
	return (path);
}

