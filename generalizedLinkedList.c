#include <stdio.h>
#include <stdlib.h>

#define MAX 200

struct GLL
{
	int flag;
	struct GLL *next;
	union
    	{
		char data[200];
		struct GLL *dlink;
	}u;

};

typedef struct GLL Node;

Node* getNode(Node*);
Node* createGLL(Node*, char[]);
void disp(Node*);

int main()
{
	char str[200],choice;
	Node *head = NULL;
	do 
	{
		printf("\nGENERALIZED LINKED LIST FOR BOOK INDEX\n\n");
		printf("Enter the string: ");
		scanf("\n");
		gets(str);
		printf("\n\nBook Index: \n");
		head = createGLL(head, str);         // create the generalised list
		disp(head);
		printf("\n\nDo you wish to continue? If yes, press 'y'.");
		scanf("%c", &choice);
	}while(choice == 'y' || choice == 'Y');
	return 0;
}

Node* getNode(Node *nev)
{
	nev = (Node*)malloc(sizeof(Node));     // dynamic memory allocation
	nev -> next = NULL;
	nev -> u.dlink = 0;
	return nev;
}

Node* createGLL(Node *head, char str[])
{
	int i, j, open, close;
	Node *temp;
	open = 0;
	close = 0;
	for(i = 0; *str != '\0';)
    	{
		if(*str == '(' && i == 0)    // head node
		{
			head = getNode(head);
			temp = head;
		}
       		else
        	{
			temp -> next = getNode(temp -> next);
			temp = temp -> next;
		}
		i++;
		str++;
		j = 0;
		while(*str != ',' && *str != '(' && *str != ')')     // create nodes on same level
        	{
			temp -> u.data[j] = *str;
			i++;
			str++;
			j++;
		}
		temp -> u.data[j] = '\0';    // end the string
		temp -> flag = 0;     // for atomic node
		if(*str == '(')
		{
			open++;
			temp -> next = getNode(temp -> next);
			temp = temp -> next;
			temp -> flag = 1;  // for sublist
			temp -> u.dlink = createGLL(temp -> u.dlink, str);   // recursively calling the same function
			while(open != close)
			{
				str++;
				i++;
				if(*str == '(')
					open++;
				else if(*str == ')')
					close++;
			}
		   	str++;
		    	i++;
	    	}
		if(*str == ')')   // end of a list or sublist
			return head;
	}
}

void disp(Node *temp)
{
    static int depth;   // for recursive calling
    depth++;
    int i;
    if(temp == NULL)
    {
    	if(depth == 1)
    		printf("List is Empty!");
    	else
    		printf("Sublist is Empty!");
    }
    else
    {
    	while(temp != NULL)
        {
    		if(temp -> flag == 0)     // atomic node
            	{
    			printf("\n");
    			for (i = 1; i < depth; i++)
    				printf("  ");
    			printf("%s",temp -> u.data);     // list titles
    		}
            	else
    			disp(temp -> u.dlink);   // move to down link and repeat
    		temp = temp -> next;
    	}
    }
    depth--;
}
