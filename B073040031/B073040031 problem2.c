#include<stdio.h>
#include<math.h>

int this_prime(int);
void prime_factorization(int);
int factorize_two_prime(int);

int main(void)
{
	int i, f, count=0;
	printf("Input a number: ");
	scanf("%d", &f);
	
	prime_factorization(f);
	printf("\n");
	prime_factorization(13);	
	prime_factorization(131);	
	prime_factorization(1313);
	prime_factorization(13131);
	printf("\n");
	for(i=1000;i<=2000;i++)
		if(factorize_two_prime(i))
			count ++;
			
	printf("The number of number between 1000 and 2000 factorized by two different prime is %d \n", count);
	
	return 0;
}
	
int this_prime(int p)
{
	int i;
	if(p==1)
		return 0; 
	for(i=2;i<sqrt(p);i++)
		if(!(p%i))
			return 0;
	return 1;
}

void prime_factorization(int pf)
{
	int i;
	
	printf("%d = ", pf);
	if(pf == 1)
		printf("1");
	for(i=2;i<=pf;i++)
	{
		while(this_prime(i) && !(pf % i))
		{
			pf /= i;
			printf("%d * ", i);
		}
	}
	printf("\b\b ");	
	printf("\n");
}

int factorize_two_prime(int ftp)
{
	if(this_prime(ftp))
		return 0;
			
	int i, count=0;

	for(i=2;i<=ftp;i++)
	{
		if(this_prime(i) && !(ftp % i))		//a prime factor
			count++;
		while(this_prime(i) && !(ftp % i))	
			ftp /= i;
	}
	if(count != 2)							//exactly 2 prime factor
		return 0;
	else
		return 1;
}
