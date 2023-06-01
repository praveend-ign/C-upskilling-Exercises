/*! sample C source code for
 * demonstration to build with 
 * Makefile
 */
#include "search.h"

static int array[100];

/*! function for searching an
 *  element using linear search
 */
void linear_search(void)
{
	int c;
	int search;

	for(c=0;c<100;c++)
		array[c] = (c * 23) + c;

	/*! value to be searched */
	search = 2376;

	for (c = 0; c < 100; c++)
  	{
		/*! If required element is found */
    		if (array[c] == search)    
    		{
      			printf("%d is present at location %d.\n", search, c+1);
     		 	break;
    		}
  	}
  	if (c == 100)
    		printf("%d isn't present in the array.\n", search);
}

/*! function for searching an
 *  element using binary search
 */
void binary_search(void)
{
	int i, low, high, mid, key;

	for(i = 0; i < 100; i++)
		array[i] = (i * 10) + i;

	/*! value to searched */
	key = 1089;
	low = 0;
	high = 100 - 1;
	mid = (low+high)/2;
	while (low <= high) {
		if(array[mid] < key)
			low = mid + 1;
		else if (array[mid] == key) {
			printf("%d found at location %d.\n", key, mid+1);
			break;
		}
		else
			high = mid - 1;
		mid = (low + high)/2;
	}
	if(low > high)
		printf("Not found! %d isn't present in the list.\n", key);
}

