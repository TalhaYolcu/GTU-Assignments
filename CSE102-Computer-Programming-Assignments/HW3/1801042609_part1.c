#include<stdio.h>

int sum(int n,int flag) {
	int i,sum=0;	//defining count and sum variable
	switch(flag) {

		case 0:			//user chose sum even numbers
		if(n<2) {		//if value is smaller than 2,then sum should be 1
			sum=1;
			
		}
		else {
			for(i=2;i<=n;i=i+2) {
				sum=sum+i;
				printf("%d",i);
				if(i+2<=n) {		//if operation will be continued
					printf(" + ");
				}
			}
			printf(" = ");
		} 
		break;

		case 1:		//user chose sum odd numbers
		if(n==0) {	//if value is 0,then sum should be 1 because [1,N]
			sum=1;
		}
		else {
			for(i=1;i<=n;i=i+2) {
				sum=sum+i;
				printf("%d",i);
				if(i+2<=n) {		//if operation will be continued
					printf(" + ");
				}
			}
			printf(" = ");
		}			
		break;
	}
	return sum;
}
int mult(int n,int flag) {
	int i,mult=1;		//defining count and sum variable
	switch(flag) {

		case 0:		//user chose multiply even numbers
		if(n<2) {	//if value is smaller than 2,result should be 1 because [1,N]
			mult=1;
		}
		else {
			for(i=2;i<=n;i=i+2) {
				mult=mult*i;
				printf("%d",i);
				if(i+2<=n) {
					printf(" * ");	//if operation will be continued
				}
			}
			printf(" = ");
		}
		break;

		case 1:					//user chose multiply odd numbers
		if(n<=2) {			//if values is smaller than or equal to 2 ,result should be 1
			mult=1;
		}
		else {
			for(i=1;i<=n;i=i+2) {
				mult=mult*i;
				printf("%d",i);
				if(i+2<=n) {		//if operation will be continued
					printf(" * ");
				}
			}
			printf(" = ");
		}
		break;
	}
	return mult;
}
int main() {
	int n,flag1,flag2,r1,r2;	//defining integer,flags,return values
	printf("\nEnter an integer:\n");
	scanf("%d",&n);

	printf("\nPlease enter '0' for sum, '1' for multiplication\n");
	scanf("%d",&flag1);

	printf("\nPlease enter '0' to work on even numbers,'1' to work on odd numbers\n");
	scanf("%d",&flag2);
	
	if( flag1<0 || flag1>1 || flag2>1 || flag2<0) {		//if flags are not like expected
		printf("\nUnsupported operation\n");
	}
	else {
		switch(flag1) {
		case 0:		//user chose sum operation
		r1=sum(n,flag2);	
		break;

		case 1:		//user chose multiply operation
		r1=mult(n,flag2);	
		break;

		default:
			printf("\nUnsupported operation\n");	
		}
		printf("%d\n",r1);		//printing the return value
	}
}