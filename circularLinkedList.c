#include <stdio.h>
#include <stdlib.h>

struct node
{
	int exp;
	int coef;
	struct node* nxt;
};

struct node* create(struct node *, int*);
void display(struct node*);
struct node* add_poly(struct node*, struct node*, struct node*);
struct node* mul_poly(struct node*, struct node *, struct node *);
int eval_poly(struct node*);
struct node* add_terms(struct node*);
int power(int, int);

int main()
{
	int resp,n,*p = &n,val;
	struct node *head1,*head2,*result;
	do
	{
		printf("\nPolynomial Operations\n\n1.Addition\n2.Multiplication\n3.Evaluation\n4.Exit\nYour Choice:");
		scanf("%d",&resp);
		head1 = NULL;
		head2 = NULL;
		result = NULL;
		switch(resp)
		{
			case 1: printf("Number of Terms in Polynomial 1:");
					scanf("%d",&n);
					head1 = create(head1,p);
					display(head1);
					printf("Number of Terms in Polynomial 2:");
					scanf("%d",&n);
					head2 = create(head2,p);
					display(head2);
					result = add_poly(head1,head2,result);
					printf("\nAddition: ");
					display(result);
					break;
			case 2: printf("Number of Terms in Polynomial 1:");
					scanf("%d",&n);
					head1 = create(head1,p);
					display(head1);
					printf("Number of Terms in Polynomial 2:");
					scanf("%d",&n);
					head2 = create(head2,p);
					display(head2);
					result = mul_poly(head1,head2,result);
					printf("\nMultiplication: ");
					display(result);
					break;
			case 3: printf("Number of Terms in the Polynomial:");
					scanf("%d",&n);
					head1 = create(head1,p);
					display(head1);
					val = eval_poly(head1);
					printf("\nValue of the polynomial is: %d\n",val);
					break;
			case 4: break;
			default: printf("Please enter a valid response.\n");
		}
	}while(resp != 4);
	return 0;
}
struct node* create(struct node *head, int* n)
{
	struct node *new,*temp;
	int i;
	for(i = 0;i < *n;i++)
	{
		new = (struct node*)malloc(sizeof(struct node));
		printf("Power of Term %d:",i+1);
		scanf("%d",&(new -> exp));
		printf("Coefficient of Term %d:",i+1);
		scanf("%d",&(new -> coef));
		new -> nxt = NULL;
		if(head == NULL)
		{
			head = new;
			temp = head;
		}
		else
		{
			temp -> nxt = new;
			temp = new;
		}
	}
	temp -> nxt = head;
	return head;
}
void display(struct node* head)
{
	struct node* temp;
	temp = head;
	if(head == NULL)
		printf("List is Empty\n");
	else
	{
		printf("\n");
		do
		{
			if(temp -> nxt == head)
				printf("%dx^%d\n",temp -> coef,temp -> exp);
			else
			{
				if(temp->nxt->coef>0)
					printf("%dx^%d + ",temp -> coef,temp -> exp);
				else
					printf("%dx^%d ",temp -> coef,temp -> exp);
			}
			temp = temp -> nxt;
		}while(temp != head);
		printf("\n");
	}
}
struct node* add_poly(struct node* head1, struct node* head2, struct node* result)
{
	struct node* poly1, *poly2, *temp, *head;
	head = NULL;
	temp = NULL;
	poly1 = head1;
	poly2 = head2;
	do
	{
		result = (struct node*)malloc(sizeof(struct node));
		if(poly1 -> exp > poly2 -> exp)
		{
			result -> exp = poly2 -> exp;
			result -> coef = poly2 -> coef;
			poly2 = poly2 -> nxt;
		}
		else if(poly1 -> exp < poly2 -> exp)
		{
			result -> exp = poly1 -> exp;
			result -> coef = poly1 -> coef;
			poly1 = poly1 -> nxt;
		}
		else
		{
			result -> exp = poly1 -> exp;
			result -> coef = poly1 -> coef + poly2 -> coef;
			poly1 = poly1 -> nxt;
			poly2 = poly2 -> nxt;
		}
		if(head == NULL)
		{
			head = result;
			temp = head;
		}
		else
		{
			temp -> nxt = result;
			temp = result;
		}
	}while(poly1 != head1 && poly2 != head2);
	while(poly1 != head1)
	{
		result = (struct node*)malloc(sizeof(struct node));
		result -> exp = poly1 -> exp;
		result -> coef = poly1 -> coef;
		poly1 = poly1 -> nxt;
		temp -> nxt = result;
		temp = result;
	}
	while(poly2 != head2)
	{
		result = (struct node*)malloc(sizeof(struct node));
		result -> exp = poly2 -> exp;
		result -> coef = poly2 -> coef;
		poly2 = poly2 -> nxt;
		temp -> nxt = result;
		temp = result;
	}
	result -> nxt = head;
	result = result -> nxt;
	return result;
}
struct node* add_terms(struct node* head)
{
	struct node *temp,*temp1,*dupli;
	temp = head;
	do
	{
		temp1 = temp;
		do
		{
			if(temp -> exp == temp1 -> nxt -> exp)
			{
				temp -> coef += temp1 -> nxt -> coef;
				dupli = temp1 -> nxt;
				temp1 -> nxt = temp1 -> nxt -> nxt;
				free(dupli);
			}
			else
				temp1 = temp1 -> nxt;
		}while(temp1 -> nxt != head);
		temp = temp -> nxt;
	}while(temp -> nxt != head);
	return head;
}
struct node* mul_poly(struct node* head1, struct node *head2, struct node *result)
{
	struct node *poly1,*poly2,*head,*temp;
	head = temp = NULL;
	poly1 = head1;
	poly2 = head2;
	do
	{
		do
		{
			result = (struct node*)malloc(sizeof(struct node));
			result -> exp = poly1 -> exp + poly2 -> exp;
			result -> coef = poly1 -> coef * poly2 -> coef;
			poly1 = poly1 -> nxt;
			if(head == NULL)
			{
				head = result;
				temp = head;
			}
			else
			{
				temp -> nxt = result;
				temp = result;
			}
		}while(poly1 != head1);
		poly2 = poly2 -> nxt;
	}while(poly2 != head2);
	result -> nxt = head;
	result = result -> nxt;
	result = add_terms(result);
	return result;
}
int eval_poly(struct node* head)
{
	int result = 0, x;
	struct node *temp;
	temp = head;
	printf("Value of Variable:");
	scanf("%d",&x);
	do
	{
		result += temp -> coef * power(x,temp -> exp);
		temp = temp -> nxt;
	}while(temp != head);
	return result;
}
int power(int x, int y)
{
	int n = 1;
	for(int i = 0;i < y;i++)
		n *= x;
	return n;
}
