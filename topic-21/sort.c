/*! sample C source code for
 * demonstration to build with 
 * Makefile
 */
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/*! functions defined below are for
 *  bubble sort algorithm
 */ 

/*! function for inserting new element */
link NEW(item key, link next) {
        link x = malloc(sizeof(*x));
        x->key = key;
        x->next = next;
        return x;
}

/*! function for comparing and exchange
 *  value if first argument is less than
 *  the second argument
 */ 
void list_compexch(link a, link b) {
        link t;
        if (item_less(b->next->key, a->next->key)) {
                t = b->next;
                b->next = b->next->next;
                t->next = b;
                a->next = t;
        }
}

/*! function for initializing the list with
 *  new elements
 */
link list_init(int N) {
        int i;
        link x;

        x = NEW(item_rand(), NULL);

        for (i = 1; i < N; ++i) {
                x = NEW(item_rand(), x);
        }

        x = NEW(item_dummy(), x);

        return x;
}

/*! function to display the values
 */
void list_show(link h) {

        for (; h->next != NULL; h = h->next) {
                item_show(h->next->key);
        }

        printf("\n");
}

/*! function for sorting the elements
 *  in the linked list using
 *  bubble sort
 */
link list_sort(link h) {
        link x, t, out = NULL;

        while (h->next != NULL) {
                for (x = h; x->next != NULL; x = x->next) {
                        if (x->next->next == NULL) {
                                t = x->next;
                                x->next = NULL;
                                t->next = out;
                                out = t;
                                break;
                        } else {
                                list_compexch(x, x->next);
                        }
                }
        }

        h->next = out;

        return h;
}

/*! function to delete all elements in
 *  the linked list
 */
void list_delete(link h)
{
	link temp;

	while(h != NULL) {
		temp = h;
		h = h->next;
		free(temp);
	}
}

item item_rand(void) {
        return rand() % 100;
}

item item_dummy(void) {
        return 0;
}

void item_show(item x) {
        printf("%i ", x);
}

/*! below functions are defined for 
 *  insertion sort algorithm
 */

link insertsort_NEW(item key, link next) {
        link x = malloc(sizeof(*x));
        x->key = key;
        x->next = next;
        return x;
}

link insertsort_list_max(link h) {
        link r;

        for (r = h; h->next != NULL; h = h->next) {
                if (item_less(r->next->key, h->next->key)) {
                        r = h;
                }
        }

        return r;
}

link insertsort_list_init(int N) {
        int i;
        link x;

        x = insertsort_NEW(item_rand(), NULL);

        for (i = 1; i < N; ++i) {
                x = insertsort_NEW(item_rand(), x);
        }

        x = insertsort_NEW(item_dummy(), x);

        return x;
}

void insertsort_list_show(link h) {

        for (; h->next != NULL; h = h->next) {
                item_show(h->next->key);
        }

        printf("\n");
}

link insertsort_list_sort(link h) {
        link x, u, t, out;

        out = insertsort_NEW(item_dummy(), NULL);

        for (t = h->next; t != NULL; t = u) {
                u = t->next;
                for (x = out; x->next != NULL; x = x->next) {
                        if (item_less(t->key, x->next->key)) {
                                break;
                        }
                }
                t->next = x->next;
                x->next = t;

        }

        return out;
}

