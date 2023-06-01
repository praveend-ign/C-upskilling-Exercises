#ifndef _SORT_H
#define _SORT_H

#define item_less(A,B)       (A < B)

typedef int item;

typedef struct node *link;
struct node {
        item key;
        link next;
};

link list_init(int);
void list_show(link);
link list_sort(link);

void list_delete(link h);

item item_rand(void);
item item_dummy(void);
void item_show(item);

link insertsort_NEW(item key, link next);
link insertsort_list_max(link h);
link insertsort_list_init(int N);
void insertsort_list_show(link h);
link insertsort_list_sort(link h);

#endif
