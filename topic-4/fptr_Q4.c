#include <stdio.h>

typedef int bool;

#define TRUE     1
#define FALSE    0

struct student {
	char name[20];
	int score;
	bool (*compare)(struct student, struct student);
};

bool greater_score(struct student ab, struct student cd)
{
     if(ab.score > cd.score)
	  return TRUE;
     
     return FALSE;
}

struct student group[] = {
	"hari", 68, greater_score,
	"karthik", 72, greater_score,
	"parvathi", 53, greater_score
};

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void ascend_sort(struct student *arr, int size)
{
    int i, j;
    for(i=0;i<(size-1);i++) {
	for(j=0;j<(size-i-1);j++) {
		if(greater_score(arr[j], arr[j+1]))
			swap(&arr[j].score, &arr[j+1].score);
	}
    }
}

void descend_sort(struct student *arr, int size)
{
    int i, j;
    for(i=0;i<(size-1);i++) {
	for(j=0;j<(size-i-1);j++) {
		if(greater_score(arr[j], arr[j+1]) == FALSE)
			swap(&arr[j].score, &arr[j+1].score);
	}
    }
}

void printArray(struct student arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i].score);
    printf("\n");
}

void sort_students(struct student gh[], int size, void (*sort_order)(struct student[], int))
{
     (*sort_order)(gh, size);
}

int main(void)
{
	int size;
	
	size = sizeof(group)/sizeof(group[0]);
	printf(" size = %d\n", size);

        sort_students(group, size, ascend_sort);
	printf("students score in ascending order =\n");
	printArray(group, size);
        sort_students(group, size, descend_sort);
	printf("students score in descending order =\n");
	printArray(group, size);
	return 0;
}

