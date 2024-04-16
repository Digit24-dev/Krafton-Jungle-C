//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

void postOrderIterativeS1(BSTNode *root)
{
	/* add your code here */
	if (root == NULL) return;

	postOrderIterativeS1(root->left);
	postOrderIterativeS1(root->right);
	printf("%d ", root->item);
}

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("3: Remove a node from the binary search tree;\n");
	printf("4: Print the tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/4/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("A node that you want to remove: ");
			scanf("%d", &i);
			root = removeNodeFromTree(root, i);
			break;
		case 4:
			printf("Printing your BST: ");
			postOrderIterativeS1(root);
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
Write  an  iterative  C  function  postOrderIterativeS2()  that 
prints the  post-order traversal of a  binary search tree  using  **two** stacks.
Note  that you should only  use  push()  or  pop()  operations 
when  you  add  or  remove  integers  from  the  stacks. 
Remember to empty the stacks at the beginning, if the stacks are not empty.

result : 10 18 15 25 80 50 20

**KEY TO SOLVE**
you have to use **TWO** stacks. one is for searching, one is for the answer.

think about how the preOrder, inOrder, postOrder search work.

preOrder : root / left / right
inOrder	 : left / root / right
postOrder: left / right / root

STACK stacks data from bottom, postOrder needs left/right/root.
so you have to stacks data ***root/right/left***.
*/

void postOrderIterativeS2(BSTNode *root)
{
	/* add your code here */
	if (root == NULL) return;

	BSTNode *p = root;
	int flag = 0;

	Stack stack1; 
	Stack stack2;

	stack1.top = NULL;
	stack2.top = NULL;

	// after preOrder Search and push to stack1 & 2, 
	while (!flag)
	{
		if (p != NULL) {
			push(&stack1, p);
			push(&stack2, p);
			p = p->right;
		}
		else {
			if (!isEmpty(&stack1)) {
				p = pop(&stack1);
				p = p->left;
			}
			else
				flag = 1;
		}
	}

	// while stack2, pop and print.
	while (!isEmpty(&stack2))
	{
		printf("%d ", pop(&stack2)->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	/* add your code here */
	// pre first
	if (root == NULL) return NULL;

	if (root->item == value) {
		// if root has left node
		BSTNode *p = root;
		if (root->left != NULL) {
			p = root->left;
			// find highest node
			while (p->right != NULL) p = p->right;
			
			root->item = p->item;
			free(p);
			return root;
		}

		// if root has right node
		if (root->right != NULL) {
			p = root->right;
			// find lowest node
			while (p->left != NULL) p = p->left;
			
			root->item = p->item;
			free(p);
			return root;
		}

		// both NULL
		free(p);
		return NULL;
	}
	
	root->left  = removeNodeFromTree(root->left,  value);
	root->right = removeNodeFromTree(root->right, value);

	return root;
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
