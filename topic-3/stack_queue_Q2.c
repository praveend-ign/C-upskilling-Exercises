#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE          64
#define EXP_SIZE      32

struct stack {
    int s_elems[SIZE];
    int top;
};

struct queue {
    int q_elems[SIZE];
/* dequeue from front */
    int front;
/*enqueue from rear */
    int rear;
};

struct stack slist;
struct queue qlist;
int customer_num=100;

void push(int x)
{
    if (slist.top == (SIZE-1)) {
	printf("stack is full\n");
	exit(1);
    } else {
	slist.top = slist.top + 1;
	slist.s_elems[slist.top] = x;
    }
}

int pop(void)
{
    int del_elem;

    if(slist.top == -1) {
	    printf(" stack is empty\n");
	    exit(1);
    } else {
	    del_elem = slist.s_elems[slist.top];
	    slist.top = slist.top - 1;
    }
    return del_elem;
}

void display_stack(void)
{
    int i;

   if(slist.top == -1) {
	 printf("stack is empty\n");
	 return;
   }
   printf("elements in stack:\n");
   for(i=0;i<(slist.top);i++) {
	printf(" %d\n", slist.s_elems[i]);
   }
   printf("\n");
}

void enqueue(int y)
{
    int front, rear;

    front = qlist.front;
    rear = qlist.rear;

    if(rear == (SIZE-1)) {
	    printf("queue overflow\n");
	    exit(1);
    } else {
	if(front == -1)
		front = 0;

	rear = rear+1;
	qlist.q_elems[rear] = y;
    }
    qlist.front = front;
    qlist.rear = rear;
}

int dequeue(void)
{
    int elem;

    if ((qlist.front == -1) || (qlist.front > qlist.rear)) {
	   printf("queue underflow\n");
	   exit(1);
    } else {
	   elem = qlist.q_elems[qlist.front];
	   qlist.front = qlist.front + 1;
	   return elem;
    }
}

void display_queue(void)
{
    int i;

    if(qlist.front == -1)
	    printf("Empty queue\n");
    else {
	printf("queue:\n");
	for(i=qlist.front;i<=qlist.rear;i++)
		printf(" %d", qlist.q_elems[i]);
    }
    printf("\n");
}

void simple_calculator(void)
{
    char exp[EXP_SIZE];
    char *e;
    int n1,n2,n3,num;
    printf("Enter the expression :: ");
    scanf("%s",exp);
    e = exp;
    while(*e != '\0')
    {
        if(isdigit(*e))
        {
            num = *e - 48;
            push(num);
        }
        else
        {
            n1 = pop();
            n2 = pop();
            switch(*e)
            {
            case '+':
                n3 = n1 + n2;
            	break;
            case '-':
                n3 = n2 - n1;
                break;
            case '*':
                n3 = n1 * n2;
                break;
            case '/':
                n3 = n2 / n1;
                break;
	    default:
		printf("invalid operator\n");
		break;
            }
            push(n3);
        }
        e++;
    }
    printf("\nThe result of expression %s  =  %d\n\n",exp,pop());
}

void generate_customer_num() //generate a number and add to queue
{
	customer_num = customer_num+1;
	printf("\nYou are customer number: %i",customer_num);
	printf("\n");
	enqueue(customer_num);
}

void banking_simulation(void)
{
     /*! the 'customer' is just to generate a number that will be enqueued
	 the 'admin' is for the user to view and remove elements from the queue */
	int choice_admin, choice_customer, start;
	int elem;
start:
	printf("*****welcome to the bank*****\n\n");
	printf("Are you a Customer (1) or an Admin (0)? : ");
	scanf("%i",&start);
 	
	 /*! customer */
	 if (start==1)
 	{
 		printf("\n****Good day, Customer!*****");
		
		/*! generate a number and automatically adds it to the queue */
		generate_customer_num();
		printf("\n\n");
		
		goto start;	
	}
	
	/*! admin account */
	else if (start==0)	
	{
		printf("\n****Good day, Admin!*****\n");
		while(1)
		{
			printf("1.View Waiting Line\n2.Update 'Now Serving' number\n3.Quit\n\n");
			printf("what would you like to do? : ");	scanf("%i",&choice_admin);
		
			switch(choice_admin)
			{
				case 1:
				{
					/*! view the elements on the queue */
					display_queue();
					break;
				}
				case 2:
				{
					/*! remove the topmost element on the queue */
					elem = dequeue();
					printf("serving customer number = %d\n", elem);
					break;
				}
				case 3:
				{
					/*! to exit the 'admin' account */
					printf("\n");
					goto start;
				}
				default:
				{
					printf("Invalid input.");
					printf("\n\n");
				}
			}
		}
	}
	else
	{
		printf("Invalid input. Plese Try again.");
		printf("\n\n");
		goto start;
	}
}

int main(void)
{
    slist.top = -1;
    simple_calculator();
    qlist.front = qlist.rear = -1;
    banking_simulation();
    return 0;
}
