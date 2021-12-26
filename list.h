
#ifndef LIST
#define LIST

typedef struct Item {
	struct Item * next;
	struct Item * previos;
	char a;
} Item;

typedef struct List {
	Item * begin;
	Item * end;
	int len;
} List;

#endif

#ifndef LIST_F
#define LIST_F
List * init_list();
char get_c(List * l, int i);
int push_back(List * l, char a);
void delete_list(List * l);
List * get_list_line();
void delete_spaces(List * line);
void delete_words(List* line);
void print_list(List * l);
#endif