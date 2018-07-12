/*
	License goes here
*/

/*
	Program description
*/
#include<stdio.h>
#include<inttypes.h>

#define MAX_TASKS 50
#define MAX_TASK_LENGTH 80

struct List {
	uint8_t task[MAX_TASKS][MAX_TASK_LENGTH];
	uint8_t completed[MAX_TASKS];
}list;

void print_menu()
{
	printf("\nTo-do Tracker v0.01\n___________________\n");
	printf("1. Add task\n");
	printf("2. Remove task\n");
	printf("3. Mark task as completed\n");
	printf("4. Save list\n");
	printf("5. Load list\n");
	printf("6. Reset list\n");
	printf("7. View current list\n");
	printf("0. Quit");
	printf("\n\nChoice?: ");
}

void add_task()
{
	printf("Feature not added yet.");
}

void remove_task()
{
	printf("Feature not added yet.");
}

void mark_task_complete()
{
	printf("Feature not added yet.");
}

void save_list()
{

	printf("Feature not added yet.");
}

void load_list()
{
	printf("Feature not added yet.");
}

void reset_list()
{	
	printf("Feature not added yet.");
}

void display_list()
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
	print_menu();
	uint8_t choice = read_input();

	while(choice > 0) {
		switch(choice) {
			case 1:
				add_task();
				break;
			case 2:
				remove_task();
				break;
			case 3:
				mark_task_complete();
				break;
			case 4:
				save_list();
				break;
			case 5:
				load_list();
				break;
			case 6:
				reset_list();
				break;
			default:
				printf("ERROR: Invalid input, please try again.\n");
				break;
		}

		print_menu();
		choice = read_input();
	}

	return 0;
}
