/*
COMP20003 Assignment Two (search.h)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020

The following functions would read the query from stdin and search the required
results.
*/

#ifndef SEARCHH
#define SEARCHH

#define QUERYONESIZE 2
#define QUERYTWOSIZE 3
#define STRWHITESPACE " "

#include "kdtree.h"
#include <stdio.h>
/******************************************************************************/

/* Reads query in Stage1 */
double** readQueryOne(FILE *stdin, int *queryCount);

/* Reads query in Stage2 */
double** readQueryTwo(FILE *stdin, int *queryCount);

/* Frees querys' memory */
void freeQuery(double **query, int queryCount);

/* Calculates the distance between the query point and the node */
double distCal(struct coordinates* coords, double *query);

/* Searches the closest node and return the node's address */
struct KDNode* searchClose(struct KDNode *parent, double *query,
	struct KDNode* closeNode, double *minDist, int *keys);

/* Searches the nodes in the range of radius and return an array of containing
nodes' address */
struct KDNode** searchRadius(struct KDNode *parent, double *query,
	struct KDNode **radiusNodes, int *radiusNodesCount, int *keys);

#endif
