/*
 ============================================================================
 Name        : sorting_searching_operations.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MaxLen 50

struct student
{
	int rno;
	float per;
	char name[50];
};

int check(int x)
{
	int i;
	int US[100];
	for(i = 0;i < 100;i++)
		US[i] = i+1;
	for(i = 0;i < 100;i++)
	{
		if(x == US[i])
			return 1;
	}
	printf("\nInvalid Percentage. Please Try Again.\n");
	return -1;
}

int checkrno(struct student *p,int count,int rno)
{
	int i;
	for(i = 0;i < count;i++)
	{
		if(p[i].rno == rno)
		{
			printf("\nRoll No. Already Exists. Please Try Again.\n");
			return -1;
		}
	}
	return 0;
}

void add(struct student *p,int n,int *count)
{
	int i,c,d;
	for(i = 0;i < n;i++)
	{
		printf("\nStudent #%d\n",*count + 1);
		printf("Enter Name of Student: ");
		scanf("\n");
		gets(p[*count].name);
	y:	printf("Enter Roll Number: ");
		scanf("%d",&p[*count].rno);
		d = checkrno(p,*count,p[*count].rno);
		if(d == -1)
			goto y;
	x:	printf("Enter Percentage:\n");
		scanf("%f",&p[*count].per);
		c = check(p[*count].per);
		if(c == -1)
			goto x;
		*count += 1;
	}
}

void bub_sort(struct student s[],int count,int *comparisons,int *pass)
{
	if(count == 1)
		return;
	int i,j;
	printf("\nBUBBLE SORT\n");
	for(i = 0;i < count;i++)
	{
		for(j = 0;j < count - i - 1;j++)
		{
			*comparisons += 1;
			if(s[j].rno > s[j+1].rno)
			{
				*pass += 1;
				struct student temp;
				temp = s[j+1];
				s[j+1] = s[j];
				s[j] = temp;
			}
		}
		printf("\nArray after Iteration #%d: ",i+1);
		for(j = 0;j < count;j++)
			printf("%d ",s[j].rno);
		printf("\n");
	}
	printf("\nComplexity of this Algorithm is O(%d).\n",((*comparisons)*(*pass)));
	*comparisons = 0;
	*pass = 0;
	return;
}

void selection_sort(struct student s[],int count,int *comparisons,int *pass)
{
	if(count == 1)
		return;
	printf("\nSELECTION SORT\n");
	int i,j,min,x;
	for(i = 0;i < count;i++)
	{
		min = i;
		for(j = i + 1;j < count;j++)
		{
			x = strcmp(s[j].name,s[min].name);
			*comparisons += 1;
			if(x > 0)
			{
				*pass += 1;
				min = j;
			}
		}
		if(min != i)
		{
			struct student temp = s[min];
			s[min] = s[i];
			s[i] = temp;
		}
		printf("\nArray after Iteration #%d: ",i+1);
		for(j = 0;j < count;j++)
			printf("%d ",s[j].rno);
		printf("\n");
	}
	int t = ((*comparisons)*(*pass));
	if(t == 0)
		t = 1;
	printf("\nComplexity of this Algorithm is O(%d).\n",t);
	*comparisons = 0;
	*pass = 0;
}

int bin_search(struct student *s,int count,int key,int *comparisons,int *pass)
{
	int low = 0,high = count - 1,mid,i,cnt = 0;
	printf("\nBINARY SEARCH\n");
	*comparisons = 1;
	while(low <= high)
	{
		cnt += 1;
		*pass += 1;
		mid = (low + high)/2;
		if(s[mid].rno == key)
			return mid;
		else if(s[mid].rno > key)
			high = mid - 1;
		else
			low = mid + 1;
		printf("\nArray after Iteration #%d: ",cnt);
		for(i = low;i <= high;i++)
			printf("%d ",s[i].rno);
		printf("\n");
	}

	return -1;
}

void disp_one(struct student p[],int loc)
{
	printf("   Roll Number\tName of Student\t\tPercentage\n");
	printf("\t      %d\t   %s\t\t   %.2f\n",p[loc].rno,p[loc].name,p[loc].per);
}

void disp(struct student *p,int count)
{
	int i;
	printf("\n\tSr. No.   Roll Number\tName of Student\t\tPercentage\n");
	for(i = 0;i < count;i++)
	{
			printf("\t  %d\t      %d\t   %s\t\t   %.2f\n",(i+1),p[i].rno,p[i].name,p[i].per);
	}
}

int main(void) {
	int resp,count = 0,dummy,n,comparisons,pass;
	struct student s[MaxLen];
	do
	{
		printf("\n1. Input Details\n2. Display Data (Asc. Roll Number)\n3. Display Data (Desc. Name)\n4. Display Specific Data\n5. Exit\nYour Choice? ");
		scanf("%d",&resp);
		switch(resp)
		{
			case 1: printf("Number of students: ");
					scanf("%d",&n);
					add(s,n,&count);
					break;
			case 2:	bub_sort(s,count,&comparisons,&pass);
					disp(s,count);
					printf("\nComplexity of this Algorithm is O(%d).\n",(comparisons*pass));
					break;
			case 3: selection_sort(s,count,&comparisons,&pass);
					disp(s,count);
					break;
			case 4: printf("\nEnter Roll Number to search: ");
					scanf("%d",&n);
					bub_sort(s,count,&comparisons,&pass);
					dummy = bin_search(s,count,n,&comparisons,&pass);
					printf("\nComplexity of this Algorithm is O(%d).\n",(comparisons*pass));
					comparisons = 0;
					pass = 0;
					if(dummy != -1)
						disp_one(s,dummy);
					else
						printf("\nRecord Unavailable.\n");
					break;
			case 5: break;
		}
	}while(resp != 5);
	return EXIT_SUCCESS;
}
