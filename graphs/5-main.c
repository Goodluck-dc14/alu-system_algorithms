#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

void traverse_action(const vertex_t *v, size_t depth)
{
	printf("%*s[%lu] %s\n", (int)depth * 4, "", v->index, v->content);
}

int main(void)
{
	graph_t *graph;
	size_t depth;

	graph = graph_create();
	if (!graph)
		return (EXIT_FAILURE);
	if (!graph_add_vertex(graph, "San Francisco") ||
	    !graph_add_vertex(graph, "Seattle") ||
	    !graph_add_vertex(graph, "New York") ||
	    !graph_add_vertex(graph, "Miami") ||
	    !graph_add_vertex(graph, "Chicago") ||
	    !graph_add_vertex(graph, "Houston") ||
	    !graph_add_vertex(graph, "Las Vegas") ||
	    !graph_add_vertex(graph, "Boston"))
		return (EXIT_FAILURE);
	if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
	    !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
	    !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
	    !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
		return (EXIT_FAILURE);
	graph_display(graph);
	printf("\nBreadth First Traversal:\n");
	depth = breadth_first_traverse(graph, &traverse_action);
	printf("\nDepth: %lu\n", depth);
	graph_delete(graph);
	return (EXIT_SUCCESS);
}

