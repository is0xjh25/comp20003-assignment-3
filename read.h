/*
COMP20003 Assignment Two (read.h)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020

The following functions woud read the data file, open the output file and
read the fileds from the datafile's header line.
If any of these process fails, the program would be terminated.
*/

#ifndef READH
#define READH

#define STRCOMMA ","
#define TERMINATE '\0'
#define NUMBERFIELDS 11

#include <stdio.h>
/******************************************************************************/

/* Reads data File's name from argv */
char* readDataFileName(char **argv);

/* Reads output File's name from argv */
char* readOutputFileName(char **argv);

/* Opens data File */
FILE* openDataFile(char *dataFileName);

/* Opens output File */
FILE* openOutputFile(char *outputFileName);

/* Creates a field array from the header line of the data file */
void createField(char *line, char *fields[]);

/* Frees fileds' memory */
void freeFields(char *fields[]);

#endif
