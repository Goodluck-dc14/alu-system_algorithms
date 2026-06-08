#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

/**
 * backtrack - Recursive helper to find a path via backtracking
 * @map: read-only 2D map
 * @visited: 2D array marking visited cells
 * @rows: number of rows
 * @cols: number of columns
 * @x: current x coordinate
 * @y: current y coordinate
 * @target: target point
 * @path: queue building the path
 *
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(char **map, char **visited, int rows, int cols,
		     int x, int y, point_t const *target, queue_t *path)
{
	point_t *point;

	if (x < 0 || y < 0 || x >= cols || y >= rows)
		return (0);
	if (map[y][x] == '1' || visited[y][x])
		return (0);

	visited[y][x] = 1;
	printf("Checking coordinates [%d, %d]\n", x, y);

	if (x == target->x && y == target->y)
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}

	if (backtrack(map, visited, rows, cols, x + 1, y, target, path) ||
	    backtrack(map, visited, rows, cols, x, y + 1, target, path) ||
	    backtrack(map, visited, rows, cols, x - 1, y, target, path) ||
	    backtrack(map, visited, rows, cols, x, y - 1, target, path))
	{
		point = malloc(sizeof(*point));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}
	return (0);
}

/**
 * backtracking_array - Searches for first path from start to target
 * @map: read-only 2D array
 * @rows: number of rows
 * @cols: number of columns
 * @start: starting point
 * @target: target point
 *
 * Return: queue of points forming the path, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path;
	char **visited;
	int i;

	if (!map || !start || !target || rows < 1 || cols < 1)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = malloc(sizeof(char *) * rows);
	if (!visited)
		return (NULL);
	for (i = 0; i < rows; i++)
		visited[i] = calloc(cols, sizeof(char));

	if (!backtrack(map, visited, rows, cols, start->x, start->y,
		       target, path))
	{
		queue_delete(path);
		path = NULL;
	}

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}

