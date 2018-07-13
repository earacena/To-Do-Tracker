/*
	License goes here
*/

/*
	File description
*/
#include<stdio.h>
#include<inttypes.h>

#define MAX_TASKS 50
#define MAX_TASK_LENGTH 80

typedef struct List {
	
};

void print_menu()
{
	printf("\nTo-do Tracker v0.01\n___________________\n");
	printf("0. Quit");
	printf("\n\nChoice?: ");
}

void add_task(uint8_t *task_array)
{

}

void remove_task(uint8_t *task_array[][], uint8_t *position)
{

}

void mark_task_complete(uint8_t *task_array[][], uint8_t *position)
{
	printf("Feature not added yet.");
}

void save_list(List list)
{

	printf("Feature not added yet.");
}

void load_list(List* list)
{
	printf("Feature not added yet.");
}

void reset_list(List* list)
{	
	printf("Feature not added yet.");
}

void display_list(List list)
{
	printf("Feature not added yet.");
}

uint8_t read_input()
{
	uint8_t input;
	scanf("%" SCNd8, &input);
	return input;
}

int main()
{
	List list;

	print_menu();
	uint8_t choice = read_input();

	while(choice > 0) {
		switch(choice) {
			case 1:
				
			default:
				printf("ERROR: Invalid input, please try again.\n");
				break;
		}

		print_menu();
		choice = read_input();
	}

	return 0;
}
