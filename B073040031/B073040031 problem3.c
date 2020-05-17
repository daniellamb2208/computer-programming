#include<stdio.h>

int main(void)
{
	int a[3], i;
	printf("Exercise 1\n");
	a[0] = a[1] = 1;
	printf("a0 = %d\na1 = %d\n",a[0], a[1]);
	for(i=2;i<=45;i++)
	{
		a[2] = a[1] + a[0];
		a[0] = a[1];
		a[1] = a[2];
		printf("a%d = %d\n", i, a[2]);
	}
}
