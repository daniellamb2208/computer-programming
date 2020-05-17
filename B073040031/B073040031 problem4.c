#include<stdio.h>
#include<math.h>

int square(double,double);
int triangle(double,double);
int t(double,double);
int t2(double,double);

int main(void)
{
	double x, y;
	printf("Input the cordinate(x,y): ");
	scanf("%lf%lf", &x, &y);
	
	if(square(x,y))
		printf("(%.1lf, %.1lf) is in (a).\n", x, y);
	else
		printf("(%.1lf, %.1lf) is not in (a).\n", x, y);
	if(triangle(x,y))
		printf("(%.1lf, %.1lf) is in (b).\n", x, y);
	else
		printf("(%.1lf, %.1lf) is not in (b).\n", x, y);
	if(square(x,y) && !t(x,y) && !t2(x,y))	
		printf("(%.1lf, %.1lf) is in (c).\n", x, y);
	else
		printf("(%.1lf, %.1lf) is not in (c).\n", x, y);
	
	return 0;	
}

int square(double x, double y)
{
	if(x>=0 && x<=2 && y>=0 && y<=1)
		return 1;
	return 0;
}

int triangle(double x, double y)
{
	if((7*x - 2*y >= 0) && (5*x + 4*y <= 3.8) && (x - 3*y <= 0))
		return 1;
	return 0;
}

int t(double x, double y)
{
	if((7*x - 2*y > 0) && (5*x + 4*y < 3.8) && (x - 3*y < 0))
		return 1;
	return 0;
}

int t2(double x, double y)
{
	if((7*x - 2*y > 2.8) && (5*x + 4*y < 5.8) && (x - 3*y < 0.4))
		return 1;
	return 0;
}
