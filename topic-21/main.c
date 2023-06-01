/*! sample C source code for
 * demonstration to build with 
 * Makefile
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "math.h"
#include "util.h"
#include "sort.h"
#include "search.h"

/*! function for bubble sort
 *  algorithm
 */
void bubble_sort(void)
{
	int N = 10;
	link h;

        srand(time(NULL));

        h = list_init(N);

        list_show(h);

        h = list_sort(h);

        list_show(h);

	list_delete(h);
}

/*! function for insertion sort
 *  algorithm
 */
void insertion_sort(void)
{
	int N = 10;
	
	link h;

        srand(time(NULL));

        h = insertsort_list_init(N);

        insertsort_list_show(h);

        h = insertsort_list_sort(h);

        insertsort_list_show(h);

	list_delete(h);
}

int main(void)
{
	bubble_sort();
	insertion_sort();
	linear_search();
	binary_search();
	return 0;
}


