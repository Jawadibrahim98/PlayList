#ifndef playlist
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* programm menu - options to choose what to do with the playlist
* e.g.: play song, next song, prev song, etc.
*/

typedef struct node 
{
   int id;
   int trackNo;
   char artistName[31];
   char albumName[31];
   char trackName[31];	
   struct node *next;
   struct node *prev;
}node;

typedef struct list
{
	node *head;
	node *tail;
	node *playing;
}list;
	

void menu();

/*
* importing data from a text file (path) into doubli linked list
* sorted by sortindx (0:non sorted, 1:sorted by song title, 2:sorted by song performer)
* returning 1 if import succeeded, 0 on fail.
*/

int importData(char *path ,int sortindx, list *lst);

node* allocItem(int id, char *artistName, char *albumName, int trackNo, char *trackName);

int insertFirst(list *lst, node *item);

void printData(node *p);

void refreshFile(list *lst, char *path);









#endif
