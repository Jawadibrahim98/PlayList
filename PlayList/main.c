
#include "playlist.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Assigned by:
jawad
*/

int main (int argc, char *argv[])
{
	list *lst = (list*)malloc(sizeof(list));
    char *path;
    int srtidx;
	if (argc < 2)
		{
			printf("Valid Arguments\n"); 
			printf("---------------\n");
			printf("To insert a new playlist: program.exe filePath.txt [-sortindex]\n");
			return;
		}

/* 
* if the sort order wasn't selected choose default 0
*/
    srtidx=(argc>=3) ? (int)argv[2]:0;
    
/* 
* if data import wasn't successful exit the programm
*/
    if(!importData(argv[1],srtidx, lst)) 
    	exit(0);

    menu(lst, argv[1]);

    return 0;
}

