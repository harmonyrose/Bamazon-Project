#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bamazon.h"

int main(int argc, char **argv){

	if (argc < 2)
	{
		printf("File not found!\n");
		return(1);
	}

	else
	{
		read_db(argv[1]);
		printf("yay!\n");
	}

}
