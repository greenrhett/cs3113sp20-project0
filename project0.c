#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{

	int data; //occurences
	struct Node *next; // next node
	unsigned char array[5]; // array for the four bytes and the endline char
};

//structs for mergeSort
struct Node* SortedMerge(struct Node* a, struct Node* b);
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef);
/*Insert to the end of linked list and increment occurnece accordingly */
void insert(struct Node** head_ref, char *new_data)
{
	// create and allocate new node
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	//create last node and set to head reference node passed in as parameter
	struct Node *last = *head_ref;
	// fill the array with the passed in char data
	strcpy(new_node->array, new_data);
	//intialize new node
	new_node->data = 1;
	// set next to null
	new_node->next = NULL;

	/*  If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)

	{
		//set head to new node
		*head_ref = new_node;
		return;
	}
	// if the nodes are the same
	if(strcmp(last->array, new_data) == 0)
	{
		//increment occurence
		last->data++;
		return;
	}
	else
	{
		//traverse till last node
		while(last->next != NULL)
		{
			// if nodes are the same
			if(strcmp(last->array, new_data) == 0)
			{
				//increment occurneces
				last->data++;
				return;
			}
			// set last to the next node
			last = last->next;
			//if the nodes are the same
			if(strcmp(last->array, new_data) == 0)
			{
				//increment occurences
				last->data++;
				return;
			}
		}
	}
	//set next node to new node
	last->next = new_node;
	return;
}
/*Print Linked List*/
void printList(struct Node *node)
{
	//while there is a node to print
	while (node != NULL)
	{
		//print statement
		printf("%s->%d\n", node->array, node->data);
		//node is set to next node
		node = node->next;
	}
}
/*split the list for sorting */
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef)
{
	//declare nodes for sorting
    struct Node* fast;
    struct Node* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
/*Sorted Merge Method*/
struct Node* SortedMerge(struct Node* a, struct Node* b)
{
// create node and intialize to null    
struct Node* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->data >= b->data) 
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else 
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}
/*Merge Sort Method*/
void mergeSort(struct Node** headRef)
{
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) 
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    mergeSort(&a);
    mergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

/*Main Method*/
int main()
{
	struct Node* list = NULL;
	int byte = 0;
	int counter;

	//while there is still data
	while ((byte = fgetc(stdin)) != EOF)
	{

		if(byte  >= 0xf0) //if byte is 1111 0000
		{
			
			int byte2 = fgetc(stdin);
			int byte3 = fgetc(stdin);
			int byte4 = fgetc(stdin);
			unsigned char array[5] = {byte, byte2, byte3, byte4, '\0'};
			insert(&list,array);

		}
		if((byte  >= 0xE0) && (byte < 0xF0)) //if byte is 1110 0000
		{

			int byte2 = fgetc(stdin);
			int byte3 = fgetc(stdin);
			unsigned char array[4] = {byte, byte2, byte3, '\0'};
			insert(&list,array);

		}
		if((byte  >= 0xC0) && (byte < 0xE0)) //if byte is 1100 0000
		{

			int byte2 = fgetc(stdin);
			unsigned char array[3] = {byte, byte2, '\0'};
			insert(&list,array);

		}
		if(byte <= 0x80) //if byte is 1100 0000
		{

			unsigned char array[2] = {byte, '\0'};
			insert(&list,array);

		}
	}
	mergeSort(&list);
	printList(list);
}
