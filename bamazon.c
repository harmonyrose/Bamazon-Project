#include <stdio.h>
#include <stdlib.h>
#include "bamazon.h"


static item *db[MAX_ITEMS];
static int num_items = 0;
static item *purchased[MAX_PURCHASE];
static int purchased_items  = 0;


int read_db(char *filename){

	FILE *fp;
	fp = fopen(filename, "r");
	if (fp){
		printf("Success!");
	}
	else {
		printf("File not found!\n");
		return(1);
	}
}
item *add_item(int itemnum, char *category, char *name, char size, int
		quantity, double cost, int onsale) {
	item *i = malloc(sizeof(item));
	i->itemnum = itemnum;
	i->category = *category;
	//i->name = *name;
	i->size = size;
	i->quantity = quantity;
	i->cost = cost;
	i->onsale = onsale;
	return i;
}
