/*
 ============================================================================
 Name        : sll.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int info;
	struct Node *nxt;
}Node;

void insertatend(Node** head,int n)
{
	for(int i = 0;i < n;i++)
	{
		Node *new = (Node*)malloc(sizeof(Node));
		printf("\nEnter value of New Node: ");
		scanf("%d",&new -> info);
		new -> nxt = NULL;
		if(*head == NULL)
			*head = new;
		else
		{
			Node *temp = *head;
			while(temp -> nxt != NULL)
				temp = temp -> nxt;
			temp -> nxt = new;
		}
	}
}

void insertatfront(Node** head)
{
	Node *new = (Node*)malloc(sizeof(Node));
	printf("\nEnter value of New Node: ");
	scanf("%d",&new -> info);
	new -> nxt = NULL;
	if(*head == NULL)
		*head = new;
	else
	{
		new -> nxt = *head;
		*head = new;
	}
}

void insertinmiddle(Node** head)
{
	int count,pos;
	Node *temp = *head;
x:	count = 0;
	printf("\nPosition to Insert: ");
	scanf("%d",&pos);
	if(pos == 1)
		insertatend(head,1);
	else
	{
		while((count < pos - 1)&&(temp -> nxt != NULL))
		{
			temp = temp -> nxt;
			count += 1;
		}
		if(count == pos - 1)
		{
			Node *new = (Node*)malloc(sizeof(Node));
			printf("\nEnter value of New Node: ");
			scanf("%d",&new -> info);
			new -> nxt = temp -> nxt;
			temp -> nxt = new;
		}
		else
		{
			printf("\nCannot insert at given position. Please try inserting same element again.\n");
			goto x;
		}
	}
}
/*
void deleteatend(Node** head)
{
	if(*head == NULL)
	{
		printf("\nNothing to Delete.\n");
		return;
	}
	Node *temp = *head;
	Node *temp2 = *head;
	while(temp -> nxt != NULL)
		temp = temp -> nxt;
	while(temp2 -> nxt != temp)
		temp2 = temp2 -> nxt;
	temp2 -> nxt = temp -> nxt;
	free(temp);
	printf("\nDeleted At End Successfully!\n");
}

void deleteatfront(Node** head)
{
	Node *temp = *head;
	if(*head == NULL)
	{
		printf("\nNothing to Delete.\n");
		return;
	}
	temp = temp -> nxt;
	free(*head);
	*head = temp;
	printf("\nDeleted At Front Successfully!\n");
}

void deleteinmiddle(Node** head)
{
	int pos,count = 0;
	if(*head == NULL)
	{
		printf("\nNothing to Delete.\n");
		return;
	}
	printf("\nPosition to Delete: ");
	scanf("%d",&pos);
	if(pos == 1)
		deleteatend(head);
	else
	{
		Node *temp = *head;
		Node *temp2 = *head;
		while((count < pos - 1)&&(temp -> nxt != NULL))
		{
			temp = temp -> nxt;
			count += 1;
		}
		if(count == pos - 1)
		{
			while(temp2 -> nxt != temp)
				temp2 = temp2 -> nxt;
			temp2 -> nxt = temp -> nxt;
			free(temp);
			printf("\nDeleted Successfully!");
		}
		else
		{
			printf("\nCannot delete at given position. Please try deleting again.\n");
		}
	}
}
*/

void delete(Node** head,int val)
{
	Node *temp = *head;
	while(temp != NULL)
	{
		if(temp -> info == val)
			break;
		temp = temp -> nxt;
	}
	if(temp != NULL)
	{
		Node *temp2 = *head;
		if(temp == *head)
			*head = (*head) -> nxt;
		else
		{
			while(temp2 -> nxt != temp)
				temp2 = temp2 -> nxt;
			temp2 -> nxt = temp -> nxt;
		}
		free(temp);
		printf("\n'%d' Deleted Successfully!\n",val);
	}
	else
		printf("\n'%d' Not in List!",val);
}

void display(Node* head)
{
	Node *temp = head;
	printf("\n");
	while(temp != NULL)
	{
		if(temp -> nxt == NULL)
			printf("|%d / %u|",temp -> info,temp -> nxt);
		else
			printf("|%d / %u| -> ",temp -> info,temp -> nxt);
		temp = temp -> nxt;
	}
	printf("\n");
}

void disp_rev(Node* head)
{
	Node *temp = head;
	if(temp -> nxt == NULL)
	{
		printf("\n");
		printf("%d\t",temp -> info);
		return;
	}
	disp_rev(temp -> nxt);
	printf("%d\t",temp -> info);
}

void rev(Node** head)
{
	Node* prev = NULL;
	Node* current = *head;
	Node* next = NULL;
	while (current != NULL)
	{
		next = current -> nxt;
		current -> nxt = prev;
		prev = current;
		current = next;
	}
	*head = prev;
	printf("\nSLL Reverted Successfully!\n");
}

int main(void) {
	Node *head = NULL;
	int resp,n,resp2,resp3;
	printf("\n\nSINGLY LINKED LIST\n\n1. Create Linked List\n2. Exit\nYour Choice: ");
	scanf("%d",&resp3);
	switch(resp3)
	{
		case 1: printf("No. of elements to insert: ");
				scanf("%d",&n);
				insertatend(&head,n);
				break;
		case 2: return 1;printf("\nPlease enter a valid response.\n");
		default: printf("\nPlease enter a valid response.\n");
	}
	do
	{
		printf("\n\n1. Insert\n2. Delete\n3. Display\n4. Display Reverse\n5. Revert\n6. Exit\nYour Choice: ");
		scanf("%d",&resp);
		switch(resp)
		{
			case 1: printf("\n1. At End\n2. At Front\n3. In the Middle\nYour Choice: ");
					scanf("%d",&resp2);

					switch(resp2)
					{
						case 1: insertatend(&head,1);
								break;
						case 2: insertatfront(&head);
								break;
						case 3: insertinmiddle(&head);
								break;
						default: printf("\nPlease enter a valid response.\n");
					}
					break;
			case 2: printf("\nValue to Delete: ");
					scanf("%d",&resp2);
					delete(&head,resp2);
					break;
			case 3: display(head);
					break;
			case 4: disp_rev(head);
					break;
			case 5: rev(&head);
					break;
			case 6: break;
			default: printf("\nPlease enter a valid response.\n");
		}
	}while(resp != 6);
	return EXIT_SUCCESS;
}
