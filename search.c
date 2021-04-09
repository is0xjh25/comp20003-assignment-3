/*
COMP20003 Assignment Two (search.c)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020
*/

#include "search.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
/******************************************************************************/

double** readQueryOne(FILE *stdin, int *queryCount) {

	int queryNum = 0;
	size_t lineBufferLength = 0;
	char *line = NULL;

	double **query = (double**) malloc(sizeof(double*));
	assert(query);

	while (getline(&line, &lineBufferLength, stdin) != EOF) {

		queryNum++;

		query = (double**) realloc(query, sizeof(double*) * queryNum);
		assert(query);
		query[queryNum - 1] = (double*) malloc(sizeof(double) * QUERYONESIZE);
		assert(query[queryNum-1]);

		char *token = strtok(line, STRWHITESPACE);
		query[queryNum - 1][0] = atof(token);
		token = strtok(NULL, STRWHITESPACE);
		query[queryNum - 1][1] = atof(token);
	}

	free(line);

	*queryCount = queryNum;

	return query;
}

double** readQueryTwo(FILE *stdin, int *queryCount) {

	int queryNum = 0;
	size_t lineBufferLength = 0;
	char *line = NULL;

	double **query = (double**) malloc(sizeof(double*));
	assert(query);

	while (getline(&line, &lineBufferLength, stdin) != EOF) {

		queryNum++;

		query = (double**) realloc(query, sizeof(double*) * queryNum);
		assert(query);
		query[queryNum - 1] = (double*) malloc(sizeof(double) * QUERYTWOSIZE);
		assert(query[queryNum - 1]);

		char *token = strtok(line, STRWHITESPACE);
		query[queryNum - 1][0] = atof(token);
		token = strtok(NULL, STRWHITESPACE);
		query[queryNum - 1][1] = atof(token);
		token = strtok(NULL, STRWHITESPACE);
		query[queryNum - 1][2] = atof(token);
	}

	free(line);

	*queryCount = queryNum;

	return query;
}

void freeQuery(double **query, int queryCount) {

	int i = 0;

	for (i = 0; i < queryCount; i++){
		free(query[i]);
	}

	free(query);
}

double distCal(struct coordinates* coords, double *query){

	double queryX = query[0];
	double queryY = query[1];

	double distance =
		sqrt(pow(coords->x - queryX, 2) + pow(coords->y - queryY, 2));

	return distance;
}

struct KDNode* searchClose(struct KDNode *parent, double *query,
	struct KDNode *closeNode, double *minDist, int *keys) {

	double queryX = query[0];
	double queryY = query[1];
	double currentDist = 0.0;

	/*Recursive function*/
	if (parent) {

		(*keys)++;
		currentDist = distCal(parent->coords, query);

		/* Updates the closest node and minimum distance*/
		if (currentDist <= *minDist) {
			*minDist = currentDist;
			closeNode = parent;
		}

		/* Decideds proceeding down either left or right branch or boths */
		if (parent->dimension == XDIMENSION) {
			if (fabs(parent->coords->x - queryX) > (*minDist)) {
				if (parent->coords->x > queryX) {
					closeNode = searchClose(parent->left, query,
						closeNode, minDist, keys);
				} else {
					closeNode = searchClose(parent->right, query,
						closeNode, minDist, keys);
				}
			} else {
				closeNode = searchClose(parent->left, query, closeNode,
					minDist, keys);
				closeNode = searchClose(parent->right, query, closeNode,
					minDist, keys);
			}
		}
		else if (parent->dimension == YDIMENSION) {
			if (fabs(parent->coords->y - queryY) > (*minDist)) {
				if (parent->coords->y > queryY){
					closeNode = searchClose(parent->left, query,
						closeNode, minDist, keys);
				} else {
					closeNode = searchClose(parent->right, query,
						closeNode, minDist, keys);
				}
			} else {
				closeNode = searchClose(parent->left, query, closeNode,
					minDist, keys);
				closeNode = searchClose(parent->right, query, closeNode,
					minDist, keys);
			}
		}
	}
	return closeNode;
}

struct KDNode** searchRadius(struct KDNode *parent, double *query,
	struct KDNode **radiusNodes, int *radiusNodesCount, int *keys) {

	double queryX = query[0];
	double queryY = query[1];
	double radiusDist = query[2];
	double currentDist = 0.0;

	/*Recursive function*/
	if (parent) {

		(*keys)++;
		currentDist = distCal(parent->coords, query);

		/* Updates the array of radius nodes*/
		if (currentDist <= radiusDist) {
			(*radiusNodesCount)++;
			/*Reallocs the size of the array */
			radiusNodes = (struct KDNode**) realloc(radiusNodes,
				sizeof(struct KDNode*) * (*radiusNodesCount));
			assert(radiusNodes);
			radiusNodes[(*radiusNodesCount) - 1] = parent;
			radiusNodes = searchRadius(parent->left, query, radiusNodes,
				radiusNodesCount, keys);
			radiusNodes = searchRadius(parent->right, query, radiusNodes,
				radiusNodesCount, keys);
		} else {
			/* Decideds proceeding down either left or right branch or boths */
			if (parent->dimension == XDIMENSION) {
				if (fabs(parent->coords->x - queryX) > radiusDist) {
					if (parent->coords->x > queryX) {
						radiusNodes = searchRadius(parent->left, query,
							radiusNodes, radiusNodesCount, keys);
					} else {
						radiusNodes = searchRadius(parent->right, query,
							radiusNodes, radiusNodesCount, keys);
					}
				} else {
					radiusNodes = searchRadius(parent->left, query,
						radiusNodes,radiusNodesCount, keys);
					radiusNodes = searchRadius(parent->right, query,
						radiusNodes, radiusNodesCount, keys);
				}
			}
			else if (parent->dimension == YDIMENSION) {
				if (fabs(parent->coords->y - queryY) > radiusDist) {
					if (parent->coords->y > queryY){
						radiusNodes = searchRadius(parent->left, query,
							radiusNodes, radiusNodesCount, keys);
					} else {
						radiusNodes = searchRadius(parent->right, query,
							radiusNodes, radiusNodesCount, keys);
					}
				} else {
					radiusNodes = searchRadius(parent->left, query,
						radiusNodes, radiusNodesCount, keys);
					radiusNodes = searchRadius(parent->right, query,
						radiusNodes, radiusNodesCount, keys);
				}
			}
		}
	}
	return radiusNodes;
}
