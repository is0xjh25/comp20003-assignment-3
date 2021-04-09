/*
COMP20003 Assignment Two (output.c)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020
*/

#include "output.h"
#include <stdlib.h>
#include <stdio.h>
/******************************************************************************/

void writeAllClose(FILE *outputFile, struct KDNode *parent, double *query,
	char **fields) {

	struct listNode *temp = parent->item;

	writeSingleClose(outputFile, temp, query, fields);

	/* Finds all data in the linked-list (can be null) */
	temp = temp->next;

	while (temp) {
		writeSingleClose(outputFile, temp, query, fields);
		temp = temp->next;
	}
}

void writeSingleClose(FILE *outputFile, struct listNode *item, double *query,
	char **fields) {

	fprintf(outputFile, "%f %f --> %s: %s || %s: %s || %s: %s || %s: %s || "
		"%s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s ||"
		"%c", query[0], query[1], fields[0], item->censusYear,
		fields[1], item->blockID, fields[2], item->propertyID,
		fields[3], item->basePropertyID, fields[4], item->clueSmallArea,
		fields[5], item->tradingName, fields[6], item->industryCode,
		fields[7], item->industryDescription, fields[8], item->xCoordinate,
		fields[9], item->yCoordinate, fields[10], item->location, NEXTLINE);
}

void writeAllRadius(FILE *outputFile, struct KDNode *parent, double *query,
	char **fields) {

	struct listNode *temp = parent->item;

	writeSingleRadius(outputFile, temp, query, fields);

	/* Finds all data in the linked-list (can be null) */
	temp = temp->next;

	while (temp) {
		writeSingleRadius(outputFile, temp, query, fields);
		temp = temp->next;
	}
}

void writeSingleRadius(FILE *outputFile, struct listNode *item, double *query,
	char **fields) {

	fprintf(outputFile, "%f %f %f --> %s: %s || %s: %s || %s: %s || %s: %s || "
		"%s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s ||"
		"%c%c", query[0], query[1], query[2], fields[0], item->censusYear,
		fields[1], item->blockID, fields[2], item->propertyID,
		fields[3], item->basePropertyID, fields[4], item->clueSmallArea,
		fields[5], item->tradingName, fields[6], item->industryCode,
		fields[7], item->industryDescription, fields[8], item->xCoordinate,
		fields[9], item->yCoordinate, fields[10], item->location,
		NEXTLINE, NEXTLINE);
}

void writeRadiusNotFound(FILE *outputFile, double *query) {

	fprintf(outputFile, "%f %f %f --> NOTFOUND %c%c",
	query[0], query[1], query[2], NEXTLINE, NEXTLINE);
}
