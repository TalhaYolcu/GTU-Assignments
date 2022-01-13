#include<stdio.h>
#include<math.h>

int number_length(int number) {		//finding the length of the number
	int length;
	double log1;
	log1=log10(number);		//using logarithm to calculate length
	length=log1+1;			//length is logarithm of number + 1
	return length;
}
int find_digit(int number,int index) {
	int length,mod,v1,v2,v3,v4,v5,v6,v7;  
	double log1;
	log1=log10(number);		//finding length of given number
	length=log1+1;
	mod=index%length;

	v1=pow(10,length-mod+1);	//finding digit value of number that will be needed
	v2=pow(10,length-mod);		//finding digit value of number that will be needed
	v3=pow(10,1);			//if (index%length==0) then the result will be the last digit
	v4=number%v1;
	v5=v4/v2;
	v6=number%v3;

	if(mod==0) {			//result will be last digit
		if(index>length*100) {
			printf("\nYour index is exceeded\n");
			return 0;
		}
		else {
			v7=number%10;
		}
	}
	else {
		if(index>length*100) {
			printf("\nYour index is exceeded\n");
			return 0;
		}
		else {
			v7=v5;
		}
	}
	return v7;
}
int main() {
	int u,r1,index,r2;			//defining  variables for number,return values and index
	printf("Enter a number maximum 6 digits\n");
	scanf("%d",&u);
	r1=number_length(u);	//finding length
	printf("\nYour number has %d digits\n\n",r1);
	printf("When your number is written 100 times next to each other, which digit of this number would you like to see? :\n");
	scanf("%d",&index);
	r2=find_digit(u,index);		//finding digit
	printf("\n\n%dth digit of the big number sequence : %d\n\n",index,r2);
}
