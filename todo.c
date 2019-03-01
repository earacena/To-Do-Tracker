/*
	todo.c 
	
	Author: 	Emanuel Aracena
	Description:	A simple to-do list tracker command-line utility.
	
*/
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<string.h>

#define MAX_TASKS 50
#define MAX_TASK_LENGTH 80
#define MAX_FILENAME_LENGTH 20
#define BUFFER_SIZE 60

typedef struct List List;

struct List {
	char task_desc[MAX_TASK_LENGTH];
	uint8_t completed;		// '0' for not completed, '1' for completed
	List *next;

};

void print_menu()
{
	printf("\nTo-do Tracker v0.10\n___________________\n");
	printf("1. Add task\n");
	printf("2. Display list\n");
	printf("3. Remove task\n");
	printf("4. Mark task complete\n");
	printf("5. Save list\n");
	printf("6. Load list\n");
	printf("7. Clear list\n");
	printf("0. Quit\n");
	printf("\n\nChoice?: ");
}

void add_task(List **list_ref)
{
	List *current = *list_ref;
	List *new_task = malloc(sizeof(List));

	printf("\n\nNEW TASK: ");
	fgets(new_task->task_desc, MAX_TASK_LENGTH, stdin);

	uint8_t counter = 0;

	while(counter < MAX_FILENAME_LENGTH) {
		if (new_task->task_desc[counter] == '\n')
			new_task->task_desc[counter] = '\0';
		++counter;
	}

	new_task->completed = 0;
	new_task->next = NULL;

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
			while (remove_pos > position+1) {
				current = current->next;
				list_ref = &current->next;
				++position;
			}
				current = current->next;
				*list_ref = current->next;

				free(current);
		}
	}

}

void mark_task_complete(List **list_ref)
{
	List *current = *list_ref;
	if (current == NULL)
		printf("\nERR: No items added to the list!\n");
	else {
		printf("MARK COMPLETE (#): ");
		uint8_t mark_pos;
		scanf("%" SCNd8 "%*c", &mark_pos);
		uint8_t position = 1;
		while(mark_pos > position) {
			current = current->next;
			++position;
		}
		current->completed = 1;
	}
}

void save_list(List **list_ref)
{
	printf("SAVE FILE (max length ~ 20 chars): ");
	char filename[MAX_FILENAME_LENGTH];
	fgets(filename, MAX_FILENAME_LENGTH, stdin);

	// fgets adds a '\n' making file i/o difficult as the program
	// cannot write into proper file
	uint8_t counter = 0;

	while(counter < MAX_FILENAME_LENGTH) {
		if (filename[counter] == '\n')
			filename[counter] = '\0';
		++counter;
	}


	FILE *fptr_out = fopen(filename, "w+");
	if (fptr_out == NULL) {
		printf("ERR: Cant open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	List* current = *list_ref;

	if (current == NULL) {
		printf("ERR: Cannot save an empty list!\n");
		exit(EXIT_FAILURE);
	}

	while (current != NULL) {
		fprintf(fptr_out, "%" PRId8 " ", current->completed);
		fprintf(fptr_out, "%s\n", current->task_desc);
		// For debug
		//printf("SAVED: '%s'\n", current->task_desc);
		current = current->next;
	}

	printf("\n\nSave file '%s' successfully created!\n\n", filename);

	fclose(fptr_out);
}

void load_list(List **list_ref)
{
	printf("LOAD FILE (case sensative): ");
	char filename[MAX_FILENAME_LENGTH];
	fgets(filename, MAX_FILENAME_LENGTH, stdin);

	uint8_t counter = 0;

	while(counter < MAX_FILENAME_LENGTH) {
		if (filename[counter] == '\n')
			filename[counter] = '\0';
		++counter;
	}

	FILE *fptr_in = fopen(filename, "r+");

	uint8_t file_value;
	char file_task[MAX_TASK_LENGTH];

	List *current = *list_ref;

	while (fscanf(fptr_in, "%" PRId8 " %s", &file_value, file_task) != EOF) {
		
		List *new_task = malloc(sizeof(List));
		strcpy(new_task->task_desc, file_task);
		new_task->completed = file_value;
		if (current == NULL ) {
			*list_ref = new_task;
			current = new_task;
		}
		else if (current->next == NULL) {
			current->next = new_task;
			current = current->next;
		}

		
	}
	
	fclose(fptr_in);
}

void clear_list(List **list_ref)
{
	List *current = *list_ref;
	List *temp_ref;

	while (current != NULL) {
		temp_ref = current->next;
		free(current);
		current = temp_ref;
	}

	*list_ref = NULL;
}

void display_list(List **list_ref)
{
	List *current = *list_ref;
	if (current == NULL) 
		printf("\nERR: No items added to the list!\n");
	else {
		printf("\n\nCURRENT LIST\n____________\n\n");
		uint8_t position = 1;
		while(current != NULL) {
			if (current->completed == 1)
				printf("[COMPLETED] ");
			printf("%" PRId8 ". %s\n", position, current->task_desc);
			
			current = current->next;
			++position;
		}
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
		case 4:
			mark_task_complete(&list);
			break;
		case 5:
			save_list(&list);
			break;
		case 6:
			clear_list(&list);
			load_list(&list);
			break;
		case 7:
			clear_list(&list);
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
