#include <stdio.h>
#include <stdlib.h>

struct node {
	int info;
	struct node *lchild;
	struct node *rchild;
};

/*! function to create a node */
struct node* new_node(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->info = x;
    p->lchild = NULL;
    p->rchild = NULL;

    return p;
}

struct node* search(struct node *root, int x)
{
    if(root==NULL || (root->info==x))
        return root;
    else if(x > root->info)
        return search(root->rchild, x);
    else
        return search(root->lchild, x);
}

struct node* insert(struct node *root, int x)
{
    if(root==NULL)
        return new_node(x);
    else if(x > root->info)
        root->rchild = insert(root->rchild, x);
    else
        root->lchild = insert(root->lchild,x);
    return root;
}

struct node *find_minimum(struct node *ptr)
{
    if(ptr == NULL)
	    return NULL;
    else if(ptr->lchild == NULL)
	    return ptr;
    else
	    return find_minimum(ptr->lchild);
}

struct node *find_maximum(struct node *ptr)
{
    if(ptr==NULL)
	    return NULL;
    else if(ptr->rchild == NULL)
	    return ptr;
    else
	   return find_maximum(ptr->rchild); 
}

struct node* delete(struct node *root, int x)
{
    if(root==NULL)
        return NULL;
    if (x > root->info)
        root->rchild = delete(root->rchild, x);
    else if(x < root->info)
        root->lchild = delete(root->lchild, x);
    else
    {
        /*! No Children */
        if(root->lchild==NULL && root->rchild==NULL)
        {
            free(root);
            return NULL;
        }

        /*! One Child */
        else if(root->lchild==NULL || root->rchild==NULL)
        {
            struct node *temp;
            if(root->lchild==NULL)
                temp = root->rchild;
            else
                temp = root->lchild;
            free(root);
            return temp;
        }

        /*! Two Children */
        else
        {
            struct node *temp = find_minimum(root->rchild);
            root->info = temp->info;
            root->rchild = delete(root->rchild, temp->info);
        }
    }
    return root;
}

void inorder(struct node *root)
{
    if(root!=NULL) 
    {
	/*! visiting left child */
        inorder(root->lchild); 
	/*! printing data at root */
        printf(" %d ", root->info);         
	/*! visiting right child */
	inorder(root->rchild);
    }
}

int main(void)
{
    struct node *root;
    
    root = new_node(20);
    insert(root,5);
    insert(root,1);
    insert(root,15);
    insert(root,9);
    insert(root,7);
    insert(root,12);
    insert(root,30);
    insert(root,25);
    insert(root,40);
    insert(root, 45);
    insert(root, 68);

    inorder(root);
    printf("\n");

    root = delete(root, 1);
    root = delete(root, 40);
    root = delete(root, 45);

    inorder(root);
    printf("\n");

    if(search(root, 12)) {
	printf("search element found\n");
    }

    find_minimum(root);
    find_maximum(root);

    return 0;
}
