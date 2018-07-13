/*
	License goes here
*/

/*
	File description
*/
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<string.h>

#define MAX_TASKS 50
#define MAX_TASK_LENGTH 80

typedef struct List List;

struct List {
	char task_desc[MAX_TASK_LENGTH];
	uint8_t completed;		// '0' for not completed, '1' for completed
	List *next;

};

void print_menu()
{
	printf("\nTo-do Tracker v0.01\n___________________\n");
	printf("1. Add task\n");
	printf("2. Display list\n");
	printf("3. Remove task\n");
	printf("0. Quit\n");
	printf("\n\nChoice?: ");
}

void add_task(List **list_ref)
{
	List *current = *list_ref;
	List *new_task =  malloc(sizeof(List));

	printf("\n\nNEW TASK: ");
	fgets(new_task->task_desc, MAX_TASK_LENGTH, stdin);
	new_task->completed = 0;

	if (current == NULL) 
		*list_ref = new_task;
	else {
		while(current->next != NULL) 
			current = current->next;
		
		current->next = new_task;
	}

}

void remove_task(List **list_ref)
{	

	if (*list_ref == NULL) 
		printf("\nERR: No items on list!\n");
	else {

		printf("\n\nDELETE TASK(#): ");
		uint8_t remove_pos;
		scanf("%" PRId8, &remove_pos);

		List* current = *list_ref;

		if (remove_pos == 1)
			*list_ref = current->next;
		else {
			uint8_t position = 1;
			List* current = *list_ref;
			while (remove_pos > position+1) {
				current = current->next;
				list_ref = &current->next;
				++position;
			}
			*list_ref = current->next;
			free(current);
		}
	}

}

void mark_task_complete()
{
	printf("\n\nFeature not added yet.\n\n");
}

void save_head()
{

	printf("\n\nFeature not added yet.\n\n");
}

void load_head()
{
	printf("\n\nFeature not added yet.\n\n");
}

void reset_head()
{	
	printf("\n\nFeature not added yet.\n\n");
}

void display_list(List **list_ref)
{
	printf("\n\nCURRENT LIST\n____________\n\n");
	uint8_t position = 1;

	List *current = *list_ref;
	if (current == NULL) {
		printf("\nERR: No items added to the list!\n");
		return;
	}
	else
		while(current != NULL) {
			printf("%" PRId8 ". %s\n", position, 
				current->task_desc);
			
			current = current->next;
			++position;
		}
}

uint8_t read_choice()
{
	uint8_t input;
	scanf("%" SCNd8 "%*c", &input);
	return input;
}

int main()
{
	List *list = NULL;

	print_menu();
	uint8_t choice = read_choice();

	while(choice > 0) {
		switch(choice) {
		case 1:
			add_task(&list);
			break;
		case 2:
			display_list(&list);
			break;
		case 3:
			remove_task(&list);
			break;
		default:
			printf("ERROR: Invalid input, please try again.\n");
			break;
		}

		print_menu();
		choice = read_choice();
	}

	return 0;
}
