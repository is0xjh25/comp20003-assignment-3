/*
COMP20003 Assignment Two (kdtree.c)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020
*/

#include "kdtree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
/******************************************************************************/

struct listNode* createListNode(char *line) {

	int i = 0;
	int quote = 0;
	int charIndex = 0;
	int field = 0;
	char *string = (char*) malloc(sizeof(char) * STRINGMAXCHAR);

	struct listNode *item = (struct listNode*) malloc(sizeof(struct listNode));
	assert(item);

	item->next = NULL;

	for (i = 0;i < strlen(line);i++){

		if (line[i] == QUOTE){
			quote++;
		}

		if (line[i] == COMMA && quote%2 == 0){
			string[charIndex] = TERMINATE;
			string = createTerm(string);

		switch(field){
			case 0:
				item->censusYear =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->censusYear);
				strcpy(item->censusYear, string);
				break;
			case 1:
				item->blockID =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->blockID);
				strcpy(item->blockID, string);
				break;
			case 2:
				item->propertyID =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->propertyID);
				strcpy(item->propertyID, string);
				break;
			case 3:
				item->basePropertyID =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->basePropertyID);
				strcpy(item->basePropertyID, string);
				break;
			case 4:
				item->clueSmallArea =
					(char*) malloc (sizeof(char) * (strlen(string) + 1));
				assert(item->clueSmallArea);
				strcpy(item->clueSmallArea,string);
				break;
			case 5:
				item->tradingName =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->tradingName);
				strcpy(item->tradingName, string);
				break;
			case 6:
				item->industryCode =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->industryCode);
				strcpy(item->industryCode, string);
				break;
			case 7:
				item->industryDescription =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->industryDescription);
				strcpy(item->industryDescription, string);
				break;
			case 8:
				item->xCoordinate =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->xCoordinate);
				strcpy(item->xCoordinate, string);
				break;
			case 9:
				item->yCoordinate =
					(char*) malloc(sizeof(char) * (strlen(string) + 1));
				assert(item->yCoordinate);
				strcpy(item->yCoordinate, string);
				break;
			}

			field++;
			charIndex = 0;
		}

		/* The situation of last field (location) */
		else if (line[i] == NEXTLINE || i == strlen(line) - 1){
			if (line[i] == NEXTLINE){
				string[charIndex] = TERMINATE;
			} else {
				string[charIndex++] = line[i];
				string[charIndex] = TERMINATE;
			}
			string = createTerm(string);
			item->location = (char*) malloc(sizeof(char) *
				(strlen(string) + 1));
			assert(item->location);
			strcpy(item->location, string);
		}
		/* Do nothing with carrage return ('\r') */
		else if (line[i] == CARRIAGERETURN){
		} else {
			string[charIndex++] = line[i];
		}
	}

	free(string);
	return item;
}

char *createTerm(char *string){

	int stringSize = strlen(string);
    char previousChar = ' ';
    char *term = (char *)malloc(sizeof(char) * (stringSize + 1));
    assert(term);
    int charIndex = 0;

	int i = 0;

	for (i = 0; i < stringSize; i++){

        if (string[i] == QUOTE){
            if (i != 0 && i != (stringSize - 1) && previousChar != QUOTE){
                term[charIndex++] = string[i];
                previousChar = string[i];
			}
        }
        else{
            term[charIndex++] = string[i];
            previousChar = string[i];
        }
    }
	/* lets the string be terminated ('\0') */
	term[charIndex] = TERMINATE;
    strcpy(string, term);
    free(term);
    return string;
}

struct KDNode* createKDTree(struct KDNode *parent, struct listNode *item) {

	struct KDNode **insertLocation = &parent;
	struct KDNode *currentParent = NULL;

	while(*insertLocation){
		/* There is a existing KD node having same location */
		if (atof(item->xCoordinate) == (*insertLocation)->coords->x &&
			atof(item->yCoordinate) == (*insertLocation)->coords->y) {
				break;
		}
		/* Keeps proceeding down either left or right branch */
		else if ((*insertLocation)->dimension == XDIMENSION) {
	 		if(atof(item->xCoordinate) < (*insertLocation)->coords->x){
		 		currentParent = *insertLocation;
		 		insertLocation = &((*insertLocation)->left);
	 		} else {
		 		currentParent = *insertLocation;
		 		insertLocation = &((*insertLocation)->right);
	 		}
		}
		else if ((*insertLocation)->dimension == YDIMENSION) {
			if(atof(item->yCoordinate) < (*insertLocation)->coords->y){
				currentParent = *insertLocation;
				insertLocation = &((*insertLocation)->left);
			} else {
				currentParent = *insertLocation;
				insertLocation = &((*insertLocation)->right);
			}
		}
 	}

	/* Creates a KD node if there is no existing KD node */
	if (!*insertLocation) {

		*insertLocation = (struct KDNode*) malloc(sizeof(struct KDNode));
	 	assert(*insertLocation);
		(*insertLocation)->coords =
		(struct coordinates*) malloc(sizeof(struct coordinates));
		assert((*insertLocation)->coords);

	 	(*insertLocation)->left = NULL;
	 	(*insertLocation)->right = NULL;
	 	(*insertLocation)->parent = currentParent;
		(*insertLocation)->item = item;

		(*insertLocation)->coords->x =
			atof((*insertLocation)->item->xCoordinate);
		(*insertLocation)->coords->y =
			atof((*insertLocation)->item->yCoordinate);

		if (!(*insertLocation)->parent){
			(*insertLocation)->dimension = XDIMENSION;
		}
		else if ((*insertLocation)->parent->dimension == XDIMENSION) {
			(*insertLocation)->dimension = YDIMENSION;
		}
		else if ((*insertLocation)->parent->dimension == YDIMENSION) {
			(*insertLocation)->dimension = XDIMENSION;
		}
	}
	/* Inserts into the linked-list hold by the existing KD-node */
	else if (*insertLocation) {
		(*insertLocation)->item = creatLinkList((*insertLocation)->item, item);
	}
	return parent;
}

struct listNode* creatLinkList(struct listNode *list, struct listNode *item) {

	item->next = list;
	list = item;
	return list;
}

void freeLinkList(struct listNode *list) {

	struct listNode *temp = list;

	while (temp){
		list = temp->next;
		free(temp->tradingName);
		free(temp->censusYear);
		free(temp->blockID);
		free(temp->propertyID);
		free(temp->basePropertyID);
		free(temp->clueSmallArea);
		free(temp->industryCode);
		free(temp->industryDescription);
		free(temp->xCoordinate);
		free(temp->yCoordinate);
		free(temp->location);
		free(temp);
		temp = list;
	}
}

void freeKDTree(struct KDNode *parent) {

	if (!parent) {
		return;
	} else {

		if(parent->item) {
			freeLinkList(parent->item);
		}
		freeKDTree(parent->right);
		freeKDTree(parent->left);
		free(parent->coords);
		free(parent);
	}
}
