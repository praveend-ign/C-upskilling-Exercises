#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
 
struct node 
{
    int  data;
    struct node *next;
};
 
/* ********************************************************************/
/*  Function to insert a node at the front of the linked list.        */
/*  front: front pointer, val: integer value                          */
/*  Returns the new front pointer.                                    */
/* ********************************************************************/
struct node *insertBegin(struct node *front, int val)
{
    struct node *newnode;
 
    newnode = (struct node *)malloc(sizeof(struct node));
 
    if (newnode == NULL)
    {
        printf("\n Allocation failed \n");
        exit(2);
    }
    newnode->data = val;
    newnode->next = front;
    front = newnode;
    return(front);
}

/**********************************************************************/
/*  Function to insert a node at the end of the linked list.          */
/*  front: front pointer, val: integer value                          */
/*  Returns the new node pointer.                                     */
/*********************************************************************/
struct node *insertEnd(struct node *front, int val)
{
    struct node *newnode;
 
    newnode = (struct node *)malloc(sizeof(struct node));
 
    if (newnode == NULL)
    {
        printf("\n Allocation failed \n");
        exit(2);
    }
    if(front == NULL) {
        front = newnode;
	newnode->data = val;
	newnode->next = NULL;
    } else {
    	while(front->next != NULL) {
		front = front->next;
    	}
    	newnode->data = val;
    	newnode->next = NULL;
    }
    return(newnode);
}
 
/*  Function to display a node in a linked list */
void printNode(struct node *p)
{
    printf("\n data       : %d", p->data);
}
 
/***********************************************************/
/*  Function to deleteNode a node based on employee number */
/*  front: front pointer, id: data value                   */
/*  Returns: the modified list.                            */
/*  ********************************************************/
struct node* deleteNode(struct node *front, int val)
{
    struct node *ptr;
    struct node *bptr;

    if (front == NULL) {
        printf(" list is empty \n");
        return NULL;
    } 
    if (front->data == val)
    {
        ptr = front;
        printf("\n Node deleted:");
        printNode(front);
        front = front->next;
        free(ptr);
        return(front);
    }
    for (ptr = front->next, bptr = front; ptr != NULL; ptr = ptr->next,
bptr = bptr->next)
    {
        if (ptr->data == val)
        {
            printf("\n Node deleted:");
            printNode(ptr);
            bptr->next = ptr->next;
            free(ptr);
            return(front);
        }
    }
    printf("\n data of value %d not found ", val);
    return(front);
}
 
/*  Function to display the linked list */
void display(struct node  *front)
{
    struct node *ptr;
 
    for (ptr = front; ptr != NULL; ptr = ptr->next)
    {
        printNode(ptr);
    }
}
 
/*  Function to display the menu of operations on a linked list */
void menu()
{
    printf("-----------------------------------------------------------\n");
    printf("Press 1 to INSERT a node in the beginning into the list    \n");
    printf("Press 2 to DELETE a node from the list       \n");
    printf("Press 3 to DISPLAY the list                 \n");
    printf("Press 4 to INSERT a node at the end into the list          \n");
    printf("Press 5 to EXIT                              \n");
    printf("-----------------------------------------------------------\n");
}
 
int main()
{
    struct node *linkList;
    struct node *newnode;
    char choice;
    int elemval;
 
    linkList = NULL;
    printf("\n Welcome to demonstration of singly linked list \n");
    menu();
    do
    {
        /*  choose operation to be performed */
	printf("\nEnter your choice: \n");
        choice = getch();
        switch(choice)
        {
        case '1':
            printf("\n Enter the list element value      : ");
            scanf("%d", &elemval);
            linkList = insertBegin(linkList, elemval);
            break;
        case '2':
            printf("\n\n Enter the list element value to be deleted: ");
            scanf("%d", &elemval);
            linkList = deleteNode(linkList, elemval);
            break;
        case '3':
            if (linkList == NULL)
            {
                printf("\n List empty.");
            } else {
                display(linkList);
	    }
            break;
        case '4':
            printf("\n\n Enter the list element value to be inserted: ");
            scanf("%d", &elemval);
            newnode = insertEnd(linkList, elemval);
	    if(linkList == NULL)
		    linkList = newnode;
            break;
        case '5': break;
        default:
		  printf("\nInvalid choice\n");
		  break;
        }
    } while (choice != '5');

    return 0;
}
