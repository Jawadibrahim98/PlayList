#include "playlist.h"
#include <string.h>


node* allocItem(int id, char *artistName, char *albumName, int trackNo, char *trackName)
{
	node* item = (node*)malloc(sizeof(node));
	item->id = id;
	item->trackNo = trackNo;
	strcpy(item->artistName, artistName);
	strcpy(item->albumName, albumName);
	strcpy(item->trackName, trackName);
	return item;
}

int insertFirst(list *lst, node *item)
{
	if (item != NULL)
	{
		//reset item pointers
		item->next = item->prev = NULL;
	
		if(lst->head == NULL)
		{
			//make head & tail pointing to item
			lst->head = lst->tail = item;	
		}
		else 
		{
			//update first prev link
			lst->head->prev = item;
			//point item to old first link
			item->next = lst->head;
			//point head to new first node
			lst->head = item;
		}
		return 1;
	}
	return 0;
}

void printData(node *p){
	printf("%5d %30s %30s %10d %30s \n", p->id, p->artistName, p->albumName, p->trackNo, p->trackName);
}

void refreshFile(list *lst, char *path){
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	FILE *fp = fopen("playlist.txt", "r");
	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	fclose(fp);

	fp = fopen("playlist.txt", "w");
	node *p = lst->head;
	fprintf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	while (p != lst->tail)
		fprintf("%5d %30s %30s %10d %30s \n", p->id, p->artistName, p->albumName, p->trackNo, p->trackName);
	fprintf("%5d %30s %30s %10d %30s \n", p->id, p->artistName, p->albumName, p->trackNo, p->trackName);
	fclose(fp);
}

void menu(list *lst, char *path){
	while(1){
		int action = 0;
		int searchAction = 0;
		char searchValue[31];
		node *p = lst->head;
		node *item = (node*)malloc(sizeof(node));
		lst->playing = lst->head;
		printf("Choose an action:\n");
		printf("Play song ------ 1:\n");
		printf("Next Song ------ 2:\n");
		printf("Preveius Song -- 3:\n");
		printf("Search Song ---- 4:\n");
		printf("Delete Song ---- 5:\n");
		printf("Add Song ------- 6:\n");
		printf("Sort Playlist -- 7:\n");
		printf("Exit ----------- 0:\n");

		scanf("%d", &action);
		switch(action){
			case 0:
				return 1;
			break;
			case 1: //Play song
				printf("Playing: %s", lst->playing->trackName);
			break;

			case 2: //Next song
				lst->playing = lst->playing->next;
			break;

			case 3: //Prev song
				lst->playing = lst->playing->prev;
			break;

			case 4: //Search song
				printf("Choose a search option:\n");
				printf("By song name ---- 1:\n");
				printf("By artist name -- 2:\n");
				printf("By album name --- 3:\n");
				scanf("%d",&searchAction);
				printf("Enter search value:\n");
				scanf("%s", &searchValue);
				switch(searchAction){
					case 1:
						while(p != lst->tail){
							if(p->trackName == searchValue)
								printData(p);
							p = p->next;
						}
						if(p->trackName == searchValue)
							printData(p);
					break;

					case 2:
						while(p != lst->tail){
							if(p->artistName == searchValue)
									printData(p);
							p = p->next;
						}
						if(p->trackName == searchValue)
							printData(p);
					break;

					case 3:
						while(p != lst->tail){
							if(p->albumName == searchValue)
								printData(p);
							p = p->next;
						}
						if(p->albumName == searchValue)
							printData(p);
					break;
				}
			break;

			case 5:
				printf("Enter name of the song to be deleted:\n");
				scanf("%s", &searchValue);
				while(p != lst->tail){
					if(p->trackName == searchValue){
						p->prev->next = p->next;
						p->next->prev = p->prev;
					}
					p = p->next;
				}
			break;

			case 6:
				printf("You requested to add a song\n");
				printf("Enter song ID:\n");
				scanf("%s", &item->id);
				printf("Enter artist name:\n");
				scanf("%s", &item->artistName);
				printf("Enter album name:\n");
				scanf("%s", &item->albumName);
				printf("Enter track name:\n");
				scanf("%s", &item->trackName);
				printf("Enter track number:\n");
				scanf("%s", &item->trackNo);
				item->next = lst->head;
				item->prev = lst->tail;
			break;

			case 7:

			break;

		}
	}
}

int importData(char *path ,int sortindx, list *lst){
	lst->head = lst->tail = lst->playing =  NULL;//Init list
	int id, trackNo;
	char artistName[31], albumName[31], trackName[31];	//note +1 for '\0'
	char h1[6], h2[31], h3[31], h4[10], h5[10];
	
	FILE *fp = fopen(path, "r");
	if (!fp)
	{
		printf("File not found!\n");
		return 0;
	}

	fscanf(fp, "%5s%30s%30s%10s%30s", h1, h2, h3, h4, h5);
	printf("%-5s %-30s %-30s %-10s %-30s \n", h1, h2, h3, h4, h5);
	while (fscanf(fp, "%5d%30[^\n]%30[^\n]%5d%30[^\n]", &id, artistName, albumName, &trackNo, trackName)>0)
	{
		insertFirst(lst, allocItem(id, artistName, albumName, trackNo, trackName));
		printf("%5d %30s %30s %10d %30s \n", id, artistName, albumName, trackNo, trackName);
	}
	fclose(fp);
	return 1;
}
