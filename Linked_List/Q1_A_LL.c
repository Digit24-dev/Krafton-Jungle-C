//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL_CZ1007(LinkedList *ll, int item)
{
	int i =0;
	ListNode *cur = NULL, *temp;

	if (ll->head == NULL)
	{
		ll->head = malloc(sizeof(ListNode));
		ll->head->next = NULL;
		ll->head->item = item;
		ll->size++;
		return 0;
	}
	
	ListNode *LN = ll->head;

	while (LN != NULL)
	{
		if (LN->item == item)
			return -1;
		else if (LN->item > item) {
			temp = malloc(sizeof(ListNode));

			temp->next = LN;
			temp->item = item;

			if (cur != NULL)
				cur->next = temp;
			else
				ll->head = temp;

			return i;
		}

		cur = LN;
		LN = LN->next;
		++i;
	}
}

int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *temp = ll->head;
	ListNode *newNode = malloc(sizeof(ListNode));
	newNode->item = item;
	newNode->next = NULL;

	unsigned int idx = 0;

	if (temp == NULL) {
		ll->head = newNode;
		ll->size++;
		return 0;
	}
	else {
		while (temp->item <= item)
		{
			++idx;
			if (temp->item == item) return -1;

			if (temp->next == NULL) {
				temp->next = newNode;
				ll->size++;
				return idx;
			}

			if (temp->next->item > item) {
				newNode->next = temp->next;
				temp->next = newNode;
				ll->size++;
				return idx;
			}
			temp = temp->next;
		}
		if (idx == 0) {
			newNode->next = ll->head;
			ll->head = newNode;
			ll->size++;
			return 0;
		}
	}
}

int insertSortedLL_2(LinkedList *ll, int item)
{
	/* add your code here */
	ListNode *temp = ll->head;
	unsigned int idx = 0;

	if (temp == NULL) {
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = item;
		ll->size++;
		return 0;
	}
	else {
		while(temp->item <= item) {
			++idx;
			if (temp->item == item) return -1;

			if (temp->next == NULL) {
				temp->next = malloc(sizeof(ListNode));
				temp->next->item = item;
				ll->size++;
				return idx;
			}

			if (temp->next->item > item) {
				ListNode *p = temp->next;
				temp->next = malloc(sizeof(ListNode));
				temp->next->item = item;
				temp->next->next = p;
				ll->size++;
				return idx;
			}

			temp = temp->next;
		}

		if (idx == 0) {
			ListNode *p = ll->head;
			ll->head = malloc(sizeof(ListNode));
			ll->head->item = item;
			ll->head->next = p;
			ll->size++;
			return 0;
		}

		ListNode *p = temp->next;
		temp->next = malloc(sizeof(ListNode));
		temp->next->item = item;
		temp->next->next = p;
		ll->size++;
		return idx;
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
