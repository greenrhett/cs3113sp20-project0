#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "textFile.txt"

struct Node
{

	int data; //occurences
	struct Node *next;
	unsigned char array[5];
};

struct Node* SortedMerge(struct Node* a, struct Node* b);
void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef);

//Three cases:

//Else if head's character array is the same as to_insert, according to strcmp, just iterate the number of occurrences.
//Else move to the next element and repeat.

void insert(struct Node** head_ref, char *new_data)
{
	/* 1. allocate node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	struct Node *last = *head_ref;

	struct Node *last1 = *head_ref;
	//    int i;
	//    for(i = 0;, i < 5; i++)
	//    {
	//    	*new_data[i] == 0;
	//    }
	printf("Inside Insert\n");
	strcpy(new_node->array, new_data);

	//    new_node->array  = new_data;
	new_node->data = 1;

	// set next to null
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)

	{
		printf("Head Ref is Null\n");
		*head_ref = new_node;
		return;
	}
	//    if(strcmp(last->array, new_data) == 0)
	//    {
	//    	printf("hereelse1");
	//    }

	//traverse till the last node and change occurence accordi
	// if the two values are the same up occurence
	if(strcmp(last->array, new_data) == 0)
	{
		last->data++;
		return;

	}
	else
	{

		//traverse till last node
		while(last->next != NULL)
		{
			if(strcmp(last->array, new_data) == 0)
			{
				last->data++;

				return;
			}
			last = last->next;
			if(strcmp(last->array, new_data) == 0)
			{
				last->data++;
				return;
			}
		}
	}
	last->next = new_node;
	return;
}

void printList(struct Node *node)
{
	while (node != NULL)
	{
		printf("%s->%d\n", node->array, node->data);
		node = node->next;
	}
}


void FrontBackSplit(struct Node* source,
                    struct Node** frontRef, struct Node** backRef)
{
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

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

struct Node* SortedMerge(struct Node* a, struct Node* b)
{
    struct Node* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->data >= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void mergeSort(struct Node** headRef)
{
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
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


int main()
{
	//	//creates space holder for file
	FILE *fp = NULL;
	// opens file for reading
	fp = fopen("textFile.txt" ,"rb");
	struct Node* list = NULL;
	int byte = 0;
	int counter;

	//	printf("%d", decimalToBinary(byte = fgetc(fp)));

	//while there is still data
	while ((byte = fgetc(fp)) != EOF)
	{

		if(byte  >= 0xf0) //if byte is 1111 0000
		{

			int byte2 = fgetc(fp);
			int byte3 = fgetc(fp);
			int byte4 = fgetc(fp);
			unsigned char array[5] = {byte, byte2, byte3, byte4, '\0'};
			insert(&list,array);

		}
		if((byte  >= 0xE0) && (byte < 0xF0)) //if byte is 1110 0000
		{

			int byte2 = fgetc(fp);
			int byte3 = fgetc(fp);
			unsigned char array[4] = {byte, byte2, byte3, '\0'};
			insert(&list,array);

		}
		if((byte  >= 0xC0) && (byte < 0xE0)) //if byte is 1100 0000
		{

			int byte2 = fgetc(fp);
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




	//	append(&head, 6);
	//	append(&head, 4);
	//	printList(head);

}
