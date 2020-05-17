#include<stdio.h>
#include<math.h>
#define TOL 0.00000000001
int prime(int);

int main()
{
	int a[100], i, j, k, tmp, index, b, c, d, f, count;	//i,j,k for for-loop counting
	printf("Exercise 1\n");
	a[0] = a[1] = 1;
	printf("a0 = %d\na1 = %d\n",a[0], a[1]);		//start from a0
	for(i=2;i<=20;i++)
	{
		a[2] = a[1] + a[0];
		a[0] = a[1];
		a[1] = a[2];
		printf("a%d = %d\n", i, a[2]);
	}
	
	printf("\nExercise 2\n");
	printf("Input the first integer: ");
	scanf("%d",&a[0]);
	printf("Input the second integer: ");
	scanf("%d",&a[1]);
	printf("Input the third integer: ");
	scanf("%d",&a[2]);
	
	int max = a[0], min = a[0];
	for(i=1;i<3;i++)
		if(a[i] > max)
			max = a[i];
	printf(" Max number is %d\n",max);
	for(i=1;i<3;i++)
		if(a[i] < min)
			min = a[i];
	printf(" Min number is %d\n",min);
	
	for(i=0;i<3;i++)		//tmp, index for sorting
	{
		index = i;
		min = a[i];
		for(j=i+1;j<3;j++)
		{	
			if(a[j] < min)
			{
				min = a[j];
				index = j;
			}
		}
		tmp = a[index];
		a[index] = a[i];
		a[i] = tmp;
	}
	printf("After sorting ");
	for(i=0;i<3;i++)
		printf("%d ",a[i]);
	printf("\n Mid number is %d\n",a[1]);
	
	printf("\nExercise 3\n");
	printf("Input the decimal number: ");
	scanf("%d",&d);			//b is base, d is input decimal number
	int r = d;
	b = 9; i =0;			//can change 'b' for any base
	while(d)
	{
		a[i] = d % b;
		d /= b;
		i++;
	}
	for(j=i-1;j>=0;j--)
			printf("%d",a[j]);
	printf("\n");
	d = r; b = 2; i =0;		//regive d the origin value, base = 2
	while(d)
	{
		a[i] = d % b;
		d /= b;
		i++;
	}
	for(j=i-1;j>=0;j--)
		if(a[j] < 10)
			printf("%d",a[j]);
	printf("\n");
	d = r; b = 8; i =0;		//base = 8
	while(d)
	{
		a[i] = d % b;
		d /= b;
		i++;
	}
	for(j=i-1;j>=0;j--)
		if(a[j] < 10)
			printf("%d",a[j]);
	printf("\n");
	d = r;	b = 16; i =0;	//base = 16
	while(d)
	{
		a[i] = d % b;
		d /= b;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		if(a[j] < 10)
			printf("%d",a[j]);
		else
		{
			char h = a[j]-10+65;		//65 is capital A
			printf("%c",h);
		}
	}printf("\n");
	
	printf("\nExercise 4\n");
	count = 0; 
	for(i=10001;i<=20000;i++)
		if(prime(i))
			count ++;
	printf("The number of prime number between 10001 and 20000 is %d\n", count);
	count = 0;
	for(i=20001;i<=30001;i++)
		if(prime(i))
			count ++;
	printf("The number of prime number between 20001 and 30001 is %d\n", count);
	
	printf("Input a number: ");
	scanf("%d",&f);
	printf("%d = ",f);
	if(f == 1)
		printf("1");
	for(i=2;i<=f;i++)
	{
/*		count = 0;
		if(prime(i) && !(f%i))
			printf(" %d", i);*/
		while(prime(i) && !(f % i))
		{
			f /= i;
			printf("%d x ", i);
//			count ++;
		}
/*		if(count >= 2)
			printf("^%d", count);*/
	}
	printf("\b\b ");			//backspace in order to remove the last x 
	printf("\n");

	printf("\nExercise 5\n");
	double s1=1,s2;				//s1=sin(pi/2)*2
	int n=1;
	s2 = s1/(2+2*sqrt(1-s1));
	while(fabs(sqrt(s2))*pow(2,n+1)-sqrt(s1)*pow(2,n) > TOL)
	{
		n++;
		s1 = s2;
		s2 = s1 / (2+2*sqrt(1-s1));
		printf("%15.14f\n",sqrt(s2)*pow(2,n+1));
	}
	return 0;	
} 

int prime(int p)
{
	int i;
	if(p==1)
		return 0; 
	for(i=2;i<p/2;i++)
		if(!(p%i))
			return 0;
	return 1;
}
