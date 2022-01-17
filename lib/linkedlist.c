#include "./task-manager.c"

#define MAX 50

// A linked list node
typedef struct Node {
	TASK * task;
	struct Node* next;
} NODE;

//LinkedList
typedef struct LLNode {
	NODE * head;
	NODE * rear;
} LLNODE;

LLNODE * createLinkedList(){
	LLNODE * newLL;
	newLL = (LLNODE *)malloc(sizeof(LLNODE *));
	newLL -> head = NULL;
	newLL -> rear = NULL;
	return newLL;
}

/* Given a reference (pointer to pointer) to the head of a
list and an int inserts a new node on the front of the
list. */
void push(LLNODE * LL)
{
	NODE *new_node;
    new_node = (NODE *)malloc(sizeof(NODE));
	new_node -> task = readTask();
	new_node -> next = NULL;

	if(LL->head == NULL){
		LL->head = new_node;
		LL->rear = new_node;
		LL->head->next = NULL;
		LL->rear->next = NULL;
	}else {
		new_node->next = LL->head;
		LL->head = new_node;
	}
}


/* Given a reference (pointer to pointer) to the head of a
list and a position, deletes the node at the given
position */
void deleteNode(LLNODE * LL)
{
	// If linked list is empty
	if (LL->head == NULL)
		return;

	// Store head node
	struct Node* temp = LL->head;
	LL->head = temp->next; // Change head
	free(temp); // free old head
	return;
}

void getTask(LLNODE * LL){
	printf("\n================= TODO TASK =================\n");
	displayTask(LL->head->task);
	deleteNode(LL);
}

// This function prints contents of linked list starting
// from the given node
void printList(LLNODE* LL)
{
	NODE * temp;

	temp = LL -> head;
	while (temp != NULL) {
		displayTask(temp->task);
		temp = temp->next;
	}
}

/* Driver program to test above functions*/
// int main()
// {
// 	LLNODE * newLL = createLinkedList();

// 	push(newLL);
// 	push(newLL);
// 	push(newLL);
// 	printList(newLL);
// 	deleteNode(newLL);
// 	printList(newLL);
// }
