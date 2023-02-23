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

	if (num_items > 0){
		if (find_item_num(itemnum) != 0 && find_item_num(itemnum) != NULL){
			item *u = find_item_num(itemnum);
			u = update_item(itemnum, str_to_category(category), name, size, quantity, cost, onsale);
			return u;
		}
	}

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

item *update_item(int itemnum, category category, char *name, char size, int quantity, double cost, int onsale){

	item *u = malloc(sizeof(item));
       	u = find_item_num(itemnum);
	u->itemnum = itemnum;
	u->category = category;
	strcpy(u->name, name);
	u->size = size;
	u->quantity = quantity;
	u->cost = cost;
	u->onsale = onsale;
	
	return u;
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

item *purchase_item(int itemnum){
	if (find_item_num(itemnum) == NULL)
		return 0;
	item *p = find_item_num(itemnum);
	p->quantity = p->quantity - 1;

	purchased[purchased_items] = p;
	purchased_items++;
	return p;
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

	for (int i = 0; i < num_items; i++){
		if (db[i]->itemnum == itemnum){
			return db[i];
		}
	}
	return 0;
}
//fills the *item[] with items where each element is category c
//returns number of elements in items[]
int get_category(item **items, category c){
	int in = 0;
	for (int i = 0; i < num_items; i++){
        	if(db[i]->category == c){
           		items[in] = db[i];
	    		in++;		
        	}
    	}
        return in;

}
//fills items with items where each element is category c and size
int get_category_size(item **items,category c, char size){
   int in = 0;
   for (int i = 0; i < num_items; i++){
        if(db[i]->category == c && db[i]->size == size){
           items[in] = db[i];
           in++;            
        }
    }

    
    return in;

}
int get_category_cost(item **items, category c, double cost){
    int in = 0;
    for (int i = 0; i < num_items; i++){
        if(db[i]->category == c && db[i]->cost <  cost){
           items[in] = db[i];
           in++;            
        }
    }
    return in;
}
//prints the value of item *c to string *s
//returns number of chars in s
int sprint_item(char *s, item *c){
     
     sprintf(s,"%d %s %s %c %d %lf %d \n", c->itemnum, category_to_str(c->category), c->name, c->size, c->quantity, c->cost, c->onsale);

    return strlen(s);
}


