/*
COMP20003 Assignment Two (kdtree.h)
Created by Yun-Chi Hsiao (student ID: 1074004) Sep 15th, 2020

The providing functions help the user to create KD-tree based on the data file,
and create linked-list for the nodes which have same location.
*/

#ifndef KDTREEH
#define KDTREEH

#define COMMA ','
#define QUOTE '"'
#define ENDPARENTHESIS ')'
#define TERMINATE '\0'
#define NEXTLINE '\n'
#define CARRIAGERETURN '\r'
#define XDIMENSION 0
#define YDIMENSION 1
#define LINEMAXCHAR 512
#define STRINGMAXCHAR 128

#include <stdio.h>
/******************************************************************************/

struct KDNode {
	struct KDNode *left;
	struct KDNode *right;
	struct KDNode *parent;
	struct listNode *item;
	struct coordinates *coords;
	int dimension;
};

struct coordinates {
	double x;
	double y;
};

struct listNode {
	char *censusYear;
	char *blockID;
	char *propertyID;
	char *basePropertyID;
	char *clueSmallArea;
	char *tradingName;
	char *industryCode;
	char *industryDescription;
	char *xCoordinate;
	char *yCoordinate;
	char *location;
	struct listNode *next;
};

/* Creates a node from a read-in line */
struct listNode* createListNode(char *line);

/* Creates a KD-tree*/
struct KDNode* createKDTree(struct KDNode *parent, struct listNode *item);

/* Creates a linked list for the listNode (same location) */
struct listNode* creatLinkList(struct listNode *list, struct listNode *item);

/* Returns a string for saving the store's specific information */
char* createTerm(char *string);

/* Frees linked-lists' memory */
void freeLinkList(struct listNode *list);

/* Frees KD-tree's memory */
void freeKDTree(struct KDNode *parent);

#endif
