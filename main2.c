/*
COMP20003 Assignment Two (main2.c)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020

This is the main program which executes all required processes from the Stage 2,
it is supported by read.h (read.c), kdtree.h (kdtree.c), search.h (search.c) and
output.h (output.c).
*/

#include "read.h"
#include "kdtree.h"
#include "search.h"
#include "output.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
/******************************************************************************/

int main( int argc, char **argv) {

	struct KDNode *parent = NULL;
	struct KDNode **radiusNodes = NULL;
	struct listNode *item = NULL;
	size_t lineBufferLength = 0;
	FILE *dataFile = NULL;
	FILE *outputFile = NULL;
	char *fileName = NULL;
	char *fields[NUMBERFIELDS];
	char *line = NULL;
	double **query = NULL;
	int queryCount = 0;
	int radiusNodesCount = 0;
	int keys = 0;
	int i = 0;
	int j = 0;

	/* Reads query */
	query = readQueryTwo(stdin, &queryCount);

	/* Opens data file & output file */
	fileName = readDataFileName(argv);
	dataFile = openDataFile(fileName);
	fileName = readOutputFileName(argv);
	outputFile = openOutputFile(fileName);

	/* Reads fields */
	getline(&line, &lineBufferLength, dataFile);
	createField(line, fields);

	/* Creates KD-tree */
	while(getline(&line, &lineBufferLength, dataFile) != EOF) {
		item = createListNode(line);
		parent = createKDTree(parent, item);
	};

	/* Searches the nodes in the range of radius, writes outputs and
	number of comparison keys */
	for (i = 0; i < queryCount; i++) {

		/* Mallocs an array of saving KD-node's address */
		radiusNodes = (struct KDNode**) malloc(sizeof(struct KDNode*) * 0);
		assert(radiusNodes);

		radiusNodesCount = 0;
		keys = 0;

		radiusNodes = searchRadius(parent, query[i], radiusNodes,
			&radiusNodesCount, &keys);

		if (radiusNodesCount == 0) {
			writeRadiusNotFound(outputFile, query[i]);
		} else {
			for (j = 0; j < radiusNodesCount; j++) {
				writeAllRadius(outputFile, radiusNodes[j], query[i], fields);
			}
		}

		free(radiusNodes);

		/* Prints out comparison keys */
		printf("%f %f %f --> %d%c", query[i][0], query[i][1], query[i][2],
			keys, NEXTLINE);
	};

	/* Closes files */
	fclose(dataFile);
	fclose(outputFile);

	/* Frees allocated memories */
	freeQuery(query, queryCount);
	freeFields(fields);
	freeKDTree(parent);
	free(line);

	return 0;
}
