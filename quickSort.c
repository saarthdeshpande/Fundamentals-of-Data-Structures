/*
 ============================================================================
 Name        : quick_sort.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MaxLen 50

typedef struct
{
	char name[50];
	long int mobileno;
	float billamt;
}MobileUser;

int partitionRecursive(MobileUser *s, int low, int high, int *pass,int count,int* swap,int* comp)
{
	int i,j;
	*pass += 1;
	*swap = 0;
	char pivot[50];
	strcpy(pivot,s[high].name);
    i = (low - 1);

    for (j = low; j <= high- 1; j++)
    {
        *comp += 1;
        if(strcmp(s[j].name,pivot) > 0)
        {
            i++;

            if(i != j)
            {
				MobileUser temp = s[j];
				s[j] = s[i];
				s[i] = temp;
				*swap += 1;
            }
        }
    }
    if(strcmp(s[i+1].name,s[high].name) != 0)
    {
		MobileUser temp = s[i+1];
		s[i+1] = s[high];
		s[high] = temp;
		*swap += 1;
    }
	printf("Pass #%d:\n",*pass);
    display(s,count);
    printf("\n\tNo. of Swaps: %d\n\n",*swap);
    return (i + 1);
}

void quickSortRecursive(MobileUser *s, int low, int high,int count,int *pass, int swap,int *comp)
{
	int pi;
    if(low < high)
    {
        pi = partitionRecursive(s, low, high,pass,count,&swap,comp);
        quickSortRecursive(s, low, pi - 1,count,pass,swap,comp);
        quickSortRecursive(s, pi + 1, high,count,pass,swap,comp);
    }
    return;
}

int partitionNumber(MobileUser *s, int low, int high, int *pass,int count,int* swap,int* comp)
{
	int i,j;
	*pass += 1;
	*swap = 0;
	long int pivot;
	pivot = s[high].mobileno;
    i = (low - 1);
    for (j = low; j <= high- 1; j++)
    {
        *comp += 1;
        if(s[j].mobileno > pivot)
        {
            i++;
            if(i != j)
            {
				MobileUser temp = s[j];
				s[j] = s[i];
				s[i] = temp;
				*swap += 1;
            }
        }
    }
    if(s[i+1].mobileno > s[high].mobileno)
    {
		MobileUser temp = s[i+1];
		s[i+1] = s[high];
		s[high] = temp;
		*swap += 1;
    }
	printf("Pass #%d:\n",*pass);
    display(s,count);
    printf("\n\tNo. of Swaps: %d\n\n",*swap);
    return (i + 1);
}

void quickSortNumber(MobileUser *s, int low, int high,int count,int *pass, int swap,int *comp)
{
	int pi;
    if(low < high)
    {
        pi = partitionNumber(s, low, high,pass,count,&swap,comp);
        quickSortNumber(s, low, pi - 1,count,pass,swap,comp);
        quickSortNumber(s, pi + 1, high,count,pass,swap,comp);
    }
    return;
}

void input(MobileUser *s,int *count)
{
	int n,i;
	printf("No. of Entries: ");
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		printf("\nEntry #%d\n",*count+1);
		printf("Enter Name: ");
		scanf("\n");
		gets(s[*count].name);
		printf("Enter Mobile Number: ");
		scanf("%ld",&s[*count].mobileno);
		printf("Enter Bill Amount: ");
		scanf("%f",&s[*count].billamt);
		*count += 1;
	}
}

void display(MobileUser *s,int count)
{
	int i;
	printf("\tName\t\tMobile No.\tBillAmount\n");
	for(i = 0;i < count;i++)
	{
		printf("\t%s\t\t%ld\t%.2f\n",s[i].name,s[i].mobileno,s[i].billamt);
	}
}

int main(void) {
	int resp,count,pass = 0,comp = 0,swap = 0;
	MobileUser s[MaxLen];
	do
	{
		printf("\nQuick Sort\n\n1. Input Data\n2. Display Data (Desc. Name)\n3. Display Data (Asc. Mob. No.)\n4. Exit\nYour Choice: ");
		scanf("%d",&resp);
		switch(resp)
		{
		case 1: input(s,&count);
				break;
		case 2: comp = 0;
				pass = 0;
				quickSortRecursive(s,0,count-1,count,&pass,swap,&comp);
				if(comp*pass <= (count - 1)*(count - 1))
					printf("\nComplexity: Best Case = O(%d)\n",comp*pass);
				else
					printf("\nComplexity: Worst case = O(%d)\n",comp*pass);
				break;
		case 3: quickSortNumber(s,0,count -1,count,&pass,swap,&comp);
				if(comp*pass <= (count - 1)*(count - 1))
					printf("\nComplexity: Best Case = O(%d)\n",comp*pass);
				else
					printf("\nComplexity: Worst case = O(%d)\n",comp*pass);
				break;
		case 4: break;
		default: printf("\nPlease enter a valid response.\n");
		}
	}while(resp != 4);
	return EXIT_SUCCESS;
}
