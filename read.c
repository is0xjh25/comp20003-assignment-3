/*
COMP20003 Assignment Two (read.c)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020
*/

#include "read.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
/******************************************************************************/

char* readDataFileName(char **argv) {

	char *dataFileName = argv[1];

	if (!dataFileName) {
		printf("DataFile Name Error!");
		exit(1);
	}

	return dataFileName;
}

char* readOutputFileName(char **argv) {

	char *outputFileName = argv[2];

	if (!outputFileName) {
		printf("OutputFile Name Error!");
		exit(1);
	}

	return outputFileName;
}

FILE* openDataFile(char *dataFileName) {

	FILE *dataFile = fopen(dataFileName, "r");;

	if (!dataFile) {
		printf("OPEN DataFile Error!");
	 	exit(1);
	}

	return dataFile;
}

FILE* openOutputFile(char *outputFileName) {

	FILE *outputFile = fopen(outputFileName, "w");

	if (!outputFile) {
		printf("OPEN OutputFile Error!");
	 	exit(1);
	}

	return outputFile;
}

void createField(char *line, char *fields[]) {

	int n = 0;
	char *token = strtok(line, STRCOMMA);

	while (token) {
		fields[n] = (char*)malloc(sizeof(char*)*strlen(token));
		assert(fields[n]);
		strcpy(fields[n], token);
		token = strtok(NULL, STRCOMMA);
		n++;
	}

	/* Replaces the last two characters in location ("\r\n") to termination */
	fields[NUMBERFIELDS - 1][strlen(fields[NUMBERFIELDS - 1]) - 1] = TERMINATE;
	fields[NUMBERFIELDS - 1][strlen(fields[NUMBERFIELDS - 1]) - 2] = TERMINATE;
}

void freeFields(char *fields[]) {

	int i = 0;

	for (i = 0; i < NUMBERFIELDS; i++) {
		free(fields[i]);
	}
}
