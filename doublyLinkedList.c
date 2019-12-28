/*
 ============================================================================
 Name        : dll.c
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
	char name[50];
	long int mobileno;
	float billamt;
}MobileUser;

typedef struct
{
	MobileUser info;
	struct Node *nxt;
	struct Node *prev;
}Node;

void insertatend(Node** head, int n)
{
	for(int i  = 0;i < n;i++)
	{
		printf("\nNew Node #%d",i + 1);
		Node *new = (Node*)malloc(sizeof(Node));
		printf("\nEnter Name of User: ");
		scanf("\n");
		gets(new -> info.name);
		printf("\nMobile Number: ");
		scanf("%ld",&new -> info.mobileno);
		printf("\nBill Amount: ");
		scanf("%f",&new -> info.billamt);
		new -> nxt = NULL;
		if(*head == NULL)
		{
			new -> prev = NULL;
			*head = new;
		}
		else
		{
			Node *temp = *head;
			while(temp -> nxt != NULL)
				temp = temp -> nxt;
			temp -> nxt = new;
			new -> prev = temp;
		}
	}
}

void insertatfront(Node** head)
{
	Node *new = (Node*)malloc(sizeof(Node));
	printf("\nEnter Name of User: ");
	scanf("\n");
	gets(new -> info.name);
	printf("\nMobile Number: ");
	scanf("%ld",&new -> info.mobileno);
	printf("\nBill Amount: ");
	scanf("%f",&new -> info.billamt);
	new -> prev = NULL;
	if(*head == NULL)
	{
			new -> nxt = NULL;
			*head = new;
	}
	else
	{
		new -> nxt = *head;
		*head = new;
	}
}

void insertinmiddle(Node** head)
{
	int pos,count = 0;
	Node *new = (Node*)malloc(sizeof(Node));
	printf("\nEnter Name of User: ");
	scanf("\n");
	gets(new -> info.name);
	printf("\nMobile Number: ");
	scanf("%ld",&new -> info.mobileno);
	printf("\nBill Amount: ");
	scanf("%f",&new -> info.billamt);
x:	printf("Enter Position to Insert: ");
	scanf("%d",&pos);
	if(pos == 1)
		insertatfront(&head);
	else
	{
		Node *temp = *head;
		while((temp -> nxt != NULL)&&(count < pos - 1))
		{
			temp = temp -> nxt;
			count += 1;
		}
		Node *temp2 = temp -> prev;
		if(count == pos - 1)
		{
			new -> prev = temp2;
			new -> nxt = temp2 -> nxt;
			temp2 -> nxt = new;
			temp -> prev = new;
		}
		else
		{
			printf("\nCannot Insert at given position. Please try another position for same entry.\n");
			goto x;
		}
	}
}

void display(Node* head)
{
	Node *temp = head;
	printf("\n");
	printf("Name\tContact\t\tBill Amount\n");
	while(temp != NULL)
	{
		printf("%s\t%ld\t%.2f\n",temp -> info.name,temp -> info.mobileno,temp -> info.billamt);
		temp = temp -> nxt;
	}
	printf("\n");
}

void disp_rev(Node* head)
{
	Node *temp = head;
	while(temp -> nxt != NULL)
		temp = temp -> nxt;
	printf("\n");
	printf("Name\tContact\t\tBill Amount\n");
	while(temp != NULL)
	{
		printf("%s\t%ld\t%.2f\n",temp -> info.name,temp -> info.mobileno,temp -> info.billamt);
		temp = temp -> prev;
	}
}

void revert(Node** head)
{
    Node *temp = NULL;
    Node *current = *head;
    while (current != NULL)
    {
        temp = current -> prev;
        current -> prev = current -> nxt;
        current -> nxt = temp;
        current = current -> prev;
    }
    if(temp != NULL )
        *head = temp -> prev;
    printf("\nDLL Reverted Successfully!\n");
}
void delete(Node** head)
{
	long int key;
	printf("Enter Mobile No. of Record to Delete: ");
	scanf("%ld",&key);
	Node *temp = *head;
	while(temp != NULL)
	{
		if(temp -> info.mobileno == key)
			break;
		temp = temp -> nxt;
	}
	if(temp != NULL)
	{
		if(temp == *head)
				*head = (*head) -> nxt;
		else if(temp -> nxt == NULL)
		{
			Node *temp2 = temp -> prev;
			temp2 -> nxt = NULL;
			temp -> prev = NULL;
		}
		else
		{
			Node *temp2 = temp -> prev;
			Node *temp3 = temp -> nxt;
			temp2 -> nxt = temp -> nxt;
			temp3 -> prev = temp2;
		}
		free(temp);
		printf("\nDeleted Successfully!\n");
	}
	else
		printf("\nDelete Failed.\nNo Record Corresponding to given Mobile Number.\n");
}

int main(void) {
	Node *head = NULL;
	int resp,n,resp2,resp3;
	printf("\n\nDOUBLY LINKED LIST\n\n1. Create Linked List\n2. Exit\nYour Choice: ");
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
					case 2: delete(&head);
							break;
					case 3: display(head);
							break;
					case 4: disp_rev(head);
							break;
					case 5: revert(&head);
							break;
					case 6: return 1;
					default: printf("\nPlease enter a valid response.\n");
		}
	}while(resp != 6);
	return EXIT_SUCCESS;
}
