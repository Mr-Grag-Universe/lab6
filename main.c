#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "KGetLine.h"
#include "list.h"

int main() {
	List * line;// = init_list();
    char * C = malloc(1);
	do {
        free(C);
		printf("-> ");
        line = get_list_line();
        delete_spaces(line);
        delete_words(line);
        delete_spaces(line);
        printf("\n");
        print_list(line);
        if (line->begin == NULL) {
            delete_list(line);
            continue;
        }
        printf("do you wanna continue?\nEnter \"y\" here:\n");
        C = get_line();
        if (!(line->begin && line->begin->a != '\n')) {
            delete_list(line);
        	break;
        }
        delete_list(line);
    } while (strcmp(C, "y") == 0);
    free(C);
    printf("\nGoodbye!\n");
    sleep(2);
	return 0;
}