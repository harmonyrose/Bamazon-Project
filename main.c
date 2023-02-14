#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bamazon.h"

int main(int argc, char **argv){

	// read the file from the command line
	if (argc < 2){
		printf("File not found!\n");
		return -1;
	}

	else
		read_db(argv[1]);
		show_items();


}
