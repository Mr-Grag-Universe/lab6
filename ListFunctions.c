#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List* init_list() {
	List * l = malloc(sizeof(List));
	l->begin = NULL;
	l->end = NULL;
	l->len = 0;
	return l;
}

void delete_list(List * l) {
	Item *el = l->begin, *p_el;
	while (el) {
		p_el = el;
		el = el->next;
		free(p_el);
	}
	free(l);
}

int push_back(List * l, char a) {
	if (l->begin == NULL) {
		l->begin = malloc(sizeof(Item));
		if (!l->begin)
			return -1;
		l->begin->next = NULL;
		l->begin->a = a;
		l->begin->previos = NULL;
		l->end = l->begin;
        l->len++;
		return 0;
	}

	l->end->next = malloc(sizeof(Item));
	Item * el = l->end->next;
	if (!el)
		return -1;
	el->previos = l->end;
	el->next = NULL;
	el->a = a;
	l->end = el;
	l->len++;
	return 1;
}

char get_c(List * l, int i) {
    if (!l->end)
        return '\0';
    if (i == -1)
        return l->end->a;

    Item * el = l->begin;
    int j = 0;
    while (j != i && el->next) {
        el = el->next;
        j++;
    }
    if (j == i)
        return el->a;
    else
        return '\0';
}

Item * get_el(List * l, int i) {
    if (!l->end)
        return NULL;
    Item * el = l->begin;
    int j = 0;
    while (j != i && el->next) {
        el = el->next;
        j++;
    }
    if (j == i)
        return el;
    else
        return NULL;
}

void copy_list(List * l1, int ind1, List * l2,  int ind2, int len) {
    int from = ind2;
    int to = ind1;
    while (from-ind2 < len && get_el(l2, from)) {
        Item * el = get_el(l1, to);
        if (el)
            el->a = get_el(l2, from)->a;
        else
            push_back(l1, get_el(l2, from)->a);
    }
}

List * join_list(List * l1, List * l2) {
    List * res = init_list();
    if (!l1->end && l2->end) {
        copy_list(res, 0, l2, 0, l2->len);
        return res;
    }
    else if (!l2->end && l1->end) {
        copy_list(res, 0, l1, 0, l1->len);
        return res;
    }
    else if (!l2->end && !l1->end)
        return res;
    else {
        copy_list(res, 0, l1, 0, l1->len);
        copy_list(res, res->len-1, l2, 0, l2->len);
        return res;
    }
}

List * get_list_line() {
    char buf = '\0';
    List * s = init_list();
    while (buf != EOF) {
        buf = getchar();
        if (buf != EOF && push_back(s, buf) < 0) {
            printf("NOT ENOUGH MEMORY.\n");
            return NULL;
        }
    }
    return s;
}

List * get_list_lines() {
    List *buf = init_list();
    List *res = init_list();

    return res;
}

void delete_spaces(List * line) {
    Item * el = line->begin;
    while (el) {
        if (el->a == '\t')
            el->a = ' ';
        el = el->next;
    }

    if (line->len == 1) {
        if (line->begin->a == ' ') {
            line->len = 0;
            free(line->begin);
            line->begin = NULL;
            line->end = NULL;
        }
        return;
    }
    el = line->begin->next;
    Item * el_p = line->begin;
    char flag = 0;
    while (el) {
        if (el->a == ' ' || el->a == '\n') {
            if (flag) {
                if (el->a == ' ') {
                    el_p->next = el->next;
                    if (el->next)
                        el->next->previos = el_p;
                    free(el);
                    el = el_p->next;
                    line->len--;
                }
                else {
                    flag = 1;
                    el_p->previos->next = el;
                    el->previos = el_p->previos;
                    free(el_p);
                    el_p = el;
                    el = el->next;
                    line->len--;
                }
            }
            else {
                flag = 1;
                el_p = el;
                el = el->next;
            }
        }
        else {
            flag = 0;
            el_p = el;
            el = el->next;
        }
    }
    if (line->begin && line->begin->a == ' ') {
        if (line->len == 1) {
            if (line->begin->a == ' ') {
                line->len = 0;
                free(line->begin);
                line->begin = NULL;
                line->end = NULL;
            }
            return;
        }
        line->begin = line->begin->next;
        free(line->begin->previos);
    }
}

void print_list(List * l) {
    Item * el = l->begin;
    printf("\n");
    while (el) {
        printf("%c", el->a);
        el = el->next;
    }
    printf("\n");
}

void delete_words(List * line) {
    if (line->begin == NULL) {
        return;
    }
    int GL = 0;
    char flag = 0;
    Item * last = line->begin;
    Item * el = line->begin;
    while (el && last && line->begin) {
        // если слово закончилось
        if (el->a == ' ' || el->a == '\n' || el->next == NULL) {
            if (GL%2 == 0 && GL) {
                if (last) {
                    if (last->previos) {
                        last->previos->next = el;
                    }
                    if (last->previos)
                        last->previos->next = el;
                    else
                        line->begin = el;
                    if (el) {
                        el->previos = last->previos;
                    }
                    //getchar();
                    // удалить слово
                    while (last != el) {
                        Item * t = last;
                        last = last->next;
                        free(t);
                        line->len--;
                    }
                    //print_list(line);
                }
                else {
                	if (el->next)
	                    while (last != NULL) {
	                        Item * t = last;
	                        last = last->next;
	                        free(t);
	                        line->len--;
	                    }
                    else {
                    	while (last != el) {
	                        Item * t = last;
	                        last = last->next;
	                        free(t);
	                        line->len--;
	                    }
                    }
                    printf("LAST IS NULL!!!\n");
                    break;
                }

            }
            if (!el)
            	break;
            last = el;
            el = el->next;
            GL = 0;
        }
        // если буква в слове
        else {
            if (el->a == 'A' || el->a == 'E' || el->a == 'I' || el->a == 'O' || el->a == 'U' || el->a == 'Y')
                GL++;
            else if (el->a == 'a' || el->a == 'e' || el->a == 'i' || el->a == 'o' || el->a == 'u' || el->a == 'y')
                GL++;
            el = el->next;
        }
    }
}