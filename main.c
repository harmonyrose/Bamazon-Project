#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bamazon.h"

char **split(char str[], char tok[], int *num_elements){
	char count_str[255];
	strcpy(count_str, str);
	char *tokens[100];
	int strings_in_str = 0;
	char *pch = strtok(count_str, tok);
	while (pch != NULL){
		tokens[strings_in_str] = pch;
		pch = strtok(NULL, tok);
		strings_in_str++;
	}
	char **array = malloc(sizeof(char*)*strings_in_str);
	if (!array)
		return NULL;
	for (int i = 0; i < strings_in_str; i++){
		array[i] = malloc(strlen(tokens[i])+1);
		if (!array[i])
			return NULL;
		strcpy(array[i], tokens[i]);
	}
	*num_elements = strings_in_str;
	return array;
}

int main(int argc, char **argv){

	// read the file from the command line
	if (argc < 2){
		printf("File not found!\n");
		return -1;
	}
	else
		read_db(argv[1]);

	// allow the user to enter as a shopper or bamazon
	char user[15];
	printf("Enter user name: ");
	scanf("%s%*c", user);
	if (strcmp(user, "shopper") == 0)
		printf("Welcome shopper!\n");
	else if (strcmp(user, "bamazon") == 0)
		printf("Welcome bamazon user!\n");
	else {
		printf("Invalid user!\n");
		exit(1);
	}

	// reads commands from the terminal
	char command[255];
	while (strcmp(command, "quit") != 0 && strcmp(command, "exit") != 0){
		printf("Enter a command: ");
		fgets(command, 255, stdin);
		char *ptr = strchr(command, '\n');
		if (ptr) {
			*ptr = '\0';
		}

		int num_strs;
		char **input = split(command, " ", &num_strs);
	
		
		if (strcmp(user, "bamazon") == 0){

			if (strcmp(input[0], "add") == 0) {

					int itemnum = atoi(input[1]);
					char *category = input[2];
					char *name = input[3];
					char size = *input[4];
					int quantity = atoi(input[5]);
					double cost = atof(input[6]);
					int onsale = atoi(input[7]);
					add_item(itemnum, category, name, size, quantity, cost, onsale);
				
			}

			else if (strcmp(input[0], "delete") == 0) {
				int itemnum = atoi(input[1]);
				if (find_item_num(itemnum) == NULL){
					printf("Invalid itemnum!\n");
				}
				else {
					delete_item(itemnum);
				}

			}

			else if (strcmp(input[0], "updatecost") == 0) {
				int itemnum = atoi(input[1]);
				if (find_item_num(itemnum) == NULL){
					printf("Invalid itemnum!\n");
				}
				else {
					double cost = atof(input[2]);
					item *u = find_item_num(itemnum);
					update_item(itemnum, u->category, u->name, u->size, u->quantity, cost, u->onsale);
				}
			}
		
			else if (strcmp(input[0], "updatequantity") == 0) {
				int itemnum = atoi(input[1]);
				if (find_item_num(itemnum) == NULL){
					printf("Invalid itemnum!\n");
				}
				else {
					int quantity = atoi(input[2]);
					item *u = find_item_num(itemnum);
					update_item(itemnum, u->category, u->name, u->size, quantity, u->cost, u->onsale);
			
				}
			}
		
			else if (strcmp(input[0], "save") == 0) {
				// FUNCTION CALL
               			if (argc < 2){
	            			printf("File not found!\n");
		            		return -1;
	            		}
	            		else
		        		write_db(argv[1]);

			}
		
			else if (strcmp(input[0], "showitems") == 0) {
				show_items();
			}
		
			else if (strcmp(input[0], "showcategory") == 0) {
				// FUNCTION CALL
                if(argc < 2){
                    printf("Invalid category.\n");
                    return -1;
                }
                else{
                    category c = str_to_category(argv[1]);
                    item **items; //needs to be defined but unsure how
                    get_category(items,c);
                    //item *item[]= //needs to be defined but unsure how
                    //get_category(items, c);
                }
			}	

			else if (strcmp(input[0], "showcategorycost") == 0) {
				// FUNCTION CALL
			}

			else if (strcmp(input[0], "showcategorysize") == 0) {
				// FUNCTION CALL
			}

			else if (strcmp(input[0], "purchase") == 0) {
				int itemnum = atoi(input[1]);
				if (find_item_num(itemnum) == NULL) {
					printf("Invalid itemnum!\n");
				}
				else {
					purchase_item(itemnum);
				}
			}

			else {
				if(strcmp(input[0], "exit") != 0 && strcmp(input[0], "quit") != 0)
					printf("Invalid command!\n");

			}
		}	
	}
}
