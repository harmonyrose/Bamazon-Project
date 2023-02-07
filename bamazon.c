#include <stdio.h>


struct item {
	int itemnum;
	enum category category;
	char *name;
	char size;
	int quantity;
	double cost;
	int onsale;
};

int read_db(char *filename) {

}

item *add_item(int itemnum, char *category, char *name, char size, int quantity, double cost, int onsale) {
	struct item *i = malloc(sizeof(struct item));
	s->itemnum = itemnum;
	s->category = c;
	s->size = size;
	s->quantity = quantity;
	s->cost = cost;
	s->onsale = onsale;

}
