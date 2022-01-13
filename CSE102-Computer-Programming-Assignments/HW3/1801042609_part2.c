#include<stdio.h>
#include<math.h>

int isprime(int a) {
	int i,flag=1;
	for(i=2;i<=sqrt(a);i++) {	//check if it is prime by using given formula
		if(a%i==0) {	//if it is divisible by any number, it is not prime and return its least divisor
			flag=i;
			break;
		}
		else {	//if it is prime it will enter here

		}
	}	
	return flag;		//returning flag value (if it is prime it will return 1)
}
int main() {
	int n,i,r1;
	printf("Please enter an integer:\n");
	scanf("%d",&n);
	for(i=2;i<n;i++) {	//from 2 to number that is given by user
		r1=isprime(i);	//check if it is prime
		if(r1<2) {		//if number is prime	//if number is prime r1 will be 1
			printf("\n%d is a prime number\n",i);
		}
		else {		//if it is not prime
			printf("\n%d is not a prime number,it is divisible by %d\n",i,r1);
		}
	}
}
