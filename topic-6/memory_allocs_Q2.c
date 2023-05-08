#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECTS      6

struct student {
	char *name;
	int age;
	char *courses[SUBJECTS];
};

char *list_of_courses[SUBJECTS] = {
	"Embedded Systems",
	"Internet of Things",
	"Mathematics",
	"General Science",
	"Social Studies",
	"English"
};

struct student *create_student(char *name, char **courses_list)
{
     struct student *new_student;
     int i;

     new_student = (struct student *)malloc(sizeof(*new_student));
     if(new_student == NULL) {
	 printf("unable to alloc memory\n");
	 return NULL;
     }
     printf("student ptr:%p\n", new_student);

     new_student->name = (char *)malloc(32);
     if(new_student->name == NULL) {
	printf("unable to alloc mem\n");
     }
     strcpy(new_student->name, name);
     printf("ptr:%p, student name = %s\n", new_student->name, new_student->name);
     
     printf("student registered courses for:\n");
     for(i=0;i<SUBJECTS;i++) {
     	new_student->courses[i] = (char *)malloc(48);
	if(new_student->courses[i] == NULL) {
		printf("unable to alloc memory\n");
		return NULL;
	}
	strcpy(new_student->courses[i], courses_list[i]);
	printf("\tptr:%p, %s\n",new_student->courses[i],new_student->courses[i]);
     }
     return new_student;
}

void delete_student(struct student *student_info)
{
     int i;

     free(student_info->name);
     for(i=0;i<SUBJECTS;i++)
     	free(student_info->courses[i]);
     free(student_info);
}

struct student *students[12];
char names[20];

int main(void)
{
     char *special_courses[SUBJECTS] = {"Integrated Electronics", "Digital Signal Processing",
	     				"Switching theory and logic design", "analog communications",
				       "digital communications", "EM Waves and Radiation"};

     int i;

     for(i=0;i<12;i++) {
	sprintf(&names[i], "vidya %s %d", "aarthi", i);
	if(i < 3)
		students[i] = create_student(&names[i], list_of_courses);
	else
		students[i] = create_student(&names[i], special_courses);
     }

     for(i=0;i<12;i++) {
	delete_student(students[i]);
     }

     return 0;
}

