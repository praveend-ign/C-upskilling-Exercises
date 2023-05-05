#include <stdio.h>
#include <stdlib.h>

struct tree_node {
     int data;
     struct tree_node *lchild;
     struct tree_node *rchild;
};

struct tree_node *insert_node(struct tree_node *root, int elem)
{
     struct tree_node *tmp, *par, *ptr;

     ptr = root;
     par = NULL;

     while(ptr != NULL) {
	par = ptr;
	if(elem < ptr->data)
	       ptr = ptr->lchild;
	else if(elem > ptr->data)
		ptr = ptr->rchild;
	else {
		printf("duplicate Key");
		return root;
	}
     }
     tmp = (struct tree_node *)malloc(sizeof(struct tree_node));
     if(tmp == NULL) {
	printf("unable to alloc memory\n");
	return NULL;
     }
     tmp->data = elem;
     tmp->lchild = NULL;
     tmp->rchild = NULL;
     if(par == NULL)
	     root = tmp;
     else if(elem < par->data)
	     par->lchild = tmp;
     else
	     par->rchild = tmp;
     return root;
}

int count_nodes(struct tree_node *root)
{
     int lchild, rchild;

     if(root == NULL)
	     return 0;
     lchild = count_nodes(root->lchild);
     rchild = count_nodes(root->rchild);

     return (1 + lchild + rchild);
}

struct tree_node* newNode(int data)
{
    struct tree_node* Node;
    
    Node = (struct tree_node *)malloc(sizeof(*Node));
    if(Node == NULL) {
	printf("unable to alloc memory\n");
	return NULL;
    }
    Node->data = data;
    Node->lchild = NULL;
    Node->rchild = NULL;
    return (Node);
}

int main(void)
{
    struct tree_node* root;

    root = newNode(1);
    root->lchild = newNode(2);
    root->rchild = newNode(3);
    root->lchild->lchild = newNode(4);
    root->lchild->rchild = newNode(5);
    root->rchild->lchild = newNode(9);
    root->rchild->rchild = newNode(8);
    root->lchild->lchild->lchild = newNode(6);
    root->lchild->lchild->rchild = newNode(7);

    printf("total number of nodes in the tree = %d\n", count_nodes(root));
    return 0;
}
