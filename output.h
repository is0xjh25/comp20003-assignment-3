/*
COMP20003 Assignment Two (output.h)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020

The following functions would write the found results into the output file.
*/

#ifndef OUTPUTH
#define OUTPUTH

#include "kdtree.h"
#include <stdio.h>
/******************************************************************************/

/* Writes all found results (for Stage1) */
void writeAllClose(FILE *outputFile, struct KDNode *parent, double *query,
	char **fields);

/* Writes a single found result (for Stage1) */
void writeSingleClose(FILE *outputFile, struct listNode *item, double *query,
	char **fields);

/* Writes all found results (for Stage2) */
void writeAllRadius(FILE *outputFile, struct KDNode *parent, double *query,
	char **fields);

/* Writes a single found result (for Stage2) */
void writeSingleRadius(FILE *outputFile, struct listNode *parent, double *query,
	char **fields);

/* Writes "NOT FOUND" (for Stage2) */
void writeRadiusNotFound(FILE *outputFile, double *query);

#endif
