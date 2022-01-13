#include<stdio.h>

int checklength(int i) {
	int c=0;
	if(i<=1) {	//if numbers are 1 and 0,their lengths are should be 1
		c=1;
	}
	else {
		while(i!=0) {	// if number will be 0,loop will stop 
		i=i/10;			//we divide number by 10 because each step, we get it's length
		c++;			//increment by 1
		}
	}
	return c;	//returning length
}
int checkbin(int a,int l) {		
	int c=0,r1=0,i=0;		//defining return and flag values
	while(i<2) {
		i=a%10;		//taking mod by 10 because :if mod is greater than 1,number are not binary
		a=a/10;		//another step
		c++;
		if(c==l) {	//if we reach the length of number we can make the loop end
			r1=1;
			break;
		}
	}
	if(r1==1) {		//if number is binary
		return 1;
	}
	else {		// if it is not binary
		return 0;
	}
}
int andop(int a,int b) {
	int i=1,c,x=0,y=10,z=0;		//defining multiply,return values
	while(a>0) {	//if number is 0,we should end the loop
		
		if(a%10<1 || b%10<1) {	//and operation (if one of the them is 0,result should be 0)
			c=0;
			
		}
		else {		//numbers are both 1,result is 1
			c=1;
		}
		a=a/10;		//decrementing the numbers
		b=b/10;
	
		i=i*10;		//each step multiply the multiply value by 10 because number digits are incrementing
		x=x+c*i;	//to get a result,we should add
	}
	if(c==0) {
			
	}
	else { 			//if first digit 1,we should divide it,becaues of true result
		x=x/10;
	}
	return x;
}
int main() {
	int a,b,c,r1,r2,r3,r4,r5;	//defining integers,return values
	c=-1;
	while(c<0) {	//if c is smaller than 0
		printf("\nFirst Integer:");
		scanf("%d",&a);
		printf("\nSecond Integer:");
		scanf("%d",&b);
		r1=checklength(a);	//checking length
		r4=checklength(b);
		
		if(r1==r4) {				//if lengths are the same
			c=1;
			r2=checkbin(a,r1);	//checking numbers are binary or not
			r5=checkbin(b,r4);
			if(r2>0 && r5>0) {			//if numbers are both binary
				r3=andop(a,b);	//and operation function
				printf("%d AND %d = %d\n",a,b,r3);
			}
			else {
				printf("Integers should be binary, please enter 2 new integers.");		//if they are not binary
				c=-1;	//start loop again
			}
		}
		else {
			printf("Integers should have the same length, please enter 2 new integers.");	//if they don't have the same length
			c=-1;	//start loop again
		}
	}
}