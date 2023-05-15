#include <stdio.h>
#include <string.h>

struct student {
/* C doesnot support bit-fields in arrays */
	char name[20];
	unsigned int age : 6;
	unsigned char grade : 4;
};

struct student iot_trainees[3];

int main(void)
{
    int size;
    int i;

    printf("values of iot_trainees members are:\n");
    strcpy(iot_trainees[0].name, "Ganesh");
    strcpy(iot_trainees[1].name, "Shani");
    strcpy(iot_trainees[2].name, "Rahu");
    iot_trainees[0].age = 48;
    iot_trainees[1].age = 52;
    iot_trainees[2].age = 27;
    iot_trainees[0].grade = 9;
    iot_trainees[1].grade = 8;
    iot_trainees[2].grade = 6;

    for(i=0;i<3;i++) {
    	printf("%s\n", (char *)iot_trainees[i].name);
    	printf("%d\n", iot_trainees[i].age);
    	printf("%d\n", iot_trainees[i].grade);
    }

    size = sizeof(struct student);
    printf("size of struct student = %d\n", size);
    size = sizeof(int);
    printf("in this machine: size of integer = %d\n", size);
    return 0;
}
