#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"


static item *db[MAX_ITEMS];
static int num_items = 0;
static item *purchased[MAX_PURCHASE];
static int purchased_items  = 0;

static char *categories[] = {"clothes", "electronics", "tools", "toys"};


// reads the database filename into the internal data structure db
int read_db(char *filename){

	FILE *fin = fopen(filename, "r");

	if (fin == NULL)
		return -1;

	int itemnum, quantity, onsale;
	char name[MAX_ITEM_CHARS], category[12];
	char size;
	double cost;

	while(fscanf(fin, "%d %s %s %c %d %lf %d", &itemnum, category, name, &size, &quantity, &cost, &onsale) != EOF){
		add_item(itemnum, category, name, size, quantity, cost, onsale);
	}

	fclose(fin);
	return 0;
}
//writes the database into a file
int write_db(char *filename){
    FILE *fout = fopen(filename,"w");
    if (fout == NULL){
        return -1;
    }
   	for (int i = 0; i < num_items; i++){
        fprintf(fout,"%d %s %s %c %d %lf %d \n", db[i]->itemnum, category_to_str(db[i]->category), db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost           , db[i]->onsale);
        }
    fclose(fout);
    return 0;
}
void show_items(){

	for (int i = 0; i < num_items; i++)
		printf("%d %s %s %c %d %lf %d \n", db[i]->itemnum, category_to_str(db[i]->category), db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);
}

item *add_item(int itemnum, char *category, char *name, char size, int
		quantity, double cost, int onsale) {

	item *i = malloc(sizeof(item));
	i->itemnum = itemnum;
	i->category = str_to_category(category);
	strcpy(i->name, name);
	i->size = size;
	i->quantity = quantity;
	i->cost = cost;
	i->onsale = onsale;
	db[num_items] = i;
	num_items++;
	return i;
}

item *delete_item(int itemnum){

	int i, j;
	item *del = find_item_num(itemnum);
	for(i = 0; i < num_items; i++){
		if (db[i]->itemnum == itemnum){
			j = i;
		}
	}

	for(i = j; i < num_items-1; i++){
		db[i] = db[i+1];
	}
	num_items--;	
	return del;
}

char *category_to_str(category c){

	return categories[c];
}

category str_to_category(char *s){

	if (strcmp(s, "clothes") == 0)
		return clothes;
	else if (strcmp(s, "electronics") == 0)
		return electronics;
	else if (strcmp(s, "tools") == 0)
		return tools;
	else
		return toys;
}

item *find_item_num(int itemnum){

	int len = sizeof(db)/sizeof(db[0]);
	for (int i = 0; i < len; i++){
		if (db[i]->itemnum == itemnum){
			return db[i];
		}
	}
	return 0;
}
//fills the *item[] with items where each element is category c
//returns number of elements in items[]
int get_category(item **items, category c){
   for (int i = 0; i < num_items; i++){
        if(db[i]->category == c){
           items[i] = db[i];            
        }
    }

    //if items emty return 0
    if(sizeof(items) == NULL){
        return 0;
    }
    else{
        return sizeof(items);
    }
}



