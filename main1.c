/*
COMP20003 Assignment Two (main1.c)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020

This is the main program which executes all required processes from the Stage 1,
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
	struct KDNode *closeNode = NULL;
	struct listNode *item = NULL;
	size_t lineBufferLength = 0;
	FILE *dataFile = NULL;
	FILE *outputFile = NULL;
	char *fileName = NULL;
	char *fields[NUMBERFIELDS];
	char *line = NULL;
	double minDist = 0.0;
	double **query = NULL;
	int queryCount = 0;
	int keys = 0;
	int i = 0;

	/* Reads query */
	query = readQueryOne(stdin, &queryCount);

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

	/* Searches the closest node, writes outputs & number of comparison keys */
	for (i = 0; i < queryCount; i++) {
		closeNode = parent;
		minDist = distCal(parent->coords, query[i]);
		keys = 0;

		closeNode = searchClose(parent, query[i], closeNode, &minDist, &keys);
		writeAllClose(outputFile, closeNode, query[i], fields);

		/* Prints out comparison keys */
		printf("%f %f --> %d%c", query[i][0], query[i][1], keys, NEXTLINE);
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
