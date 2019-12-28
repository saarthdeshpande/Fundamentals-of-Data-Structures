/*
 ============================================================================
 Name        : sparse_matrix.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MaxCol 50

void input(int a[][MaxCol],int b[][3])
{
	int i,j,r,c;
	printf("No. of Rows: ");
	scanf("%d",&r);
	printf("No. of Columns: ");
	scanf("%d",&c);
	for(i = 0;i < r;i++)
	{
		printf("Enter elements of Row #%d: ",i + 1);
		for(j = 0;j < c;j++)
			scanf("%d",&a[i][j]);
	}
	matrixToTable(a,r,c,b);
}

void matrixToTable(int a[][MaxCol],int r,int c,int b[][3])
{
	int i,j,cnt = 0,k = 1;
	b[0][0] = r;
	b[0][1] = c;
	for(i = 0;i < r;i++)
	{
		for(j = 0;j < c;j++)
		{
			if(a[i][j] != 0)
			{
				cnt += 1;
				b[k][0] = i;
				b[k][1] = j;
				b[k][2] = a[i][j];
				k += 1;
			}
		}
	}
	b[0][2] = cnt;
}

void fastTranspose()
{
	int a[MaxCol][MaxCol],b[MaxCol][3],c[MaxCol][3];
	input(a,b);
	int i,j;
	int row_terms[MaxCol],starting_pos[MaxCol];
	int num_cols = b[0][1],num_terms = b[0][2];
	c[0][0] = num_cols,c[0][1] = b[0][0],c[0][2] = num_terms;
	if(num_terms > 0)
	{
		for(i = 0;i < num_cols;i++)
			row_terms[i] = 0;
		for(i = 0;i <= num_terms;i++)
			row_terms[b[i][1]] += 1;
		starting_pos[0] = 1;
		for(i = 1;i < num_cols;i++)
			starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
		for(i = 1;i <= num_terms;i++)
		{
			j = starting_pos[b[i][1]];
			c[j][0] = b[i][1];
			c[j][1] = b[i][0];
			c[j][2] = b[i][2];
			starting_pos[b[i][1]] += 1;
		}
	}
	display(c);
}

void simpleTranspose()
{
	int a[MaxCol][MaxCol],b[MaxCol][3],c[MaxCol][3];
	input(a,b);
	int i,j,k = 1;
	for(i = 0;i < b[0][1];i++)
	{
		for(j = 1;j <= b[0][2];j++)
		{
			if(b[j][1] == i)
			{
				c[k][0] = b[j][1];
				c[k][1] = b[j][0];
				c[k][2] = b[j][2];
				k += 1;
			}
		}
	}
	c[0][0] = b[0][1];
	c[0][1] = b[0][0];
	c[0][2] = b[0][2];
	display(c);
}

void display(int a[][3])
{
	int i,j;
	printf("\nResultant Table\n\n");
	for(i = 0;i <= a[0][2];i++)
	{
			printf("a[%d]\t%d\t%d\t%d\n",i,a[i][0],a[i][1],a[i][2]);
	}
}

void add()
{
	int a[MaxCol][MaxCol],A[MaxCol][3],b[MaxCol][MaxCol],B[MaxCol][3],C[MaxCol][3];
	int i = 1,j = 1,k = 1;
	printf("\nMatrix A:\n");
	input(a,A);
	printf("\nMatrix B:\n");
	input(b,B);
	if((A[0][0] != B[0][0])||(A[0][1] != B[0][1]))
	{
		printf("\Addition Not Possible!\n");
		return;
	}
	if((A[0][2] <= 0)&&(B[0][2] <= 0))
	{
		printf("\Addition Not Possible!\n");
		return;
	}
	while((i <= A[0][2])&&(j <= B[0][2]))
	{
		if(A[i][0] < B[j][0])
		{
			C[k][0] = A[i][0];
			C[k][1] = A[i][1];
			C[k][2] = A[i][2];
			i += 1;
			k += 1;
		}
		else if(A[i][0] > B[j][0])
		{
			C[k][0] = B[j][0];
			C[k][1] = B[j][1];
			C[k][2] = B[j][2];
			j += 1;
			k += 1;
		}
		else if(A[i][1] < B[j][1])
		{
			C[k][0] = A[i][0];
			C[k][1] = A[i][1];
			C[k][2] = A[i][2];
			i += 1;
			k += 1;
		}
		else if(A[i][1] > B[j][1])
		{
			C[k][0] = B[j][0];
			C[k][1] = B[j][1];
			C[k][2] = B[j][2];
			j += 1;
			k += 1;
		}
		else
		{
			C[k][0] = B[j][0];
			C[k][1] = B[j][1];
			C[k][2] = A[i][2] + B[j][2];
			j += 1;
			k += 1;
			i += 1;
		}
	}
	while(i <= A[0][2])
	{
		C[k][0] = A[i][0];
		C[k][1] = A[i][1];
		C[k][2] = A[i][2];
		i += 1;
		k += 1;
	}
	while(j <= B[0][2])
	{
		C[k][0] = B[j][0];
		C[k][1] = B[j][1];
		C[k][2] = B[j][2];
		j += 1;
		k += 1;
	}
	C[0][0] = A[0][0];
	C[0][1] = A[0][1];
	C[0][2] = k - 1;
	display(C);
}

int main(void) {
	int resp;
	do
	{
		printf("\nSPARSE MATRIX\n\n1. Add 2 Matrices\n2. Simple Transpose\n3. Fast Transpose\n4. Exit\nYour Choice: ");
		scanf("%d",&resp);
		switch(resp)
		{
			case 1: add();
					break;
			case 2: simpleTranspose();
					break;
			case 3: fastTranspose();
					break;
			case 4: break;
			default: printf("\nPlease enter a valid response.\n");

		}
	}while(resp != 4);
	return EXIT_SUCCESS;
}
