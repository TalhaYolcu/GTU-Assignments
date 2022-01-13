#include<stdio.h>

int main() {

	int s1,s2;		//variables for switch case 
	double a,e,d;	//first amount,euro,dollar

	printf("\n***** Welcome to ABC Exchange Office *****\n\n");
	printf("Enter your amount:\n");
	scanf("%lf",&a);
	printf("\nPlease select your currency\n");
	printf("1. Turkish Lira\n2. Euro\n3. Dollar\n\n");
	scanf("%d",&s1);
	switch(s1) {

		case 1:
		printf("You have %lf Turkish Liras",a);
		break;

		case 2:
		printf("You have %lf Euros",a);
		break;

		case 3:
		printf("You have %lf Dollars",a);
		break;

		default:
		printf("Your selection is invalid\n\n");	//invalid selection
		break;
	}
	if(s1<4) {		//if first selection is valid
		printf("\nChoose which currency you want to convert\n");
		scanf("%d",&s2);
		printf("\n");
		switch(s2) {		//switch case for converting

			case 1:
			if(s1==1) {		//TL/TL
				printf("\nYou have %lf Turkish Liras\n",a);
			}
			else if(s1==2) {	//EURO/TL
				e=a*6.69;
				printf("\nYou have %lf Turkish Liras\n",e);
			}
			else {			
				d=a*6.14;		//DOLLAR/TL
				printf("\nYou have %lf Turkish Liras\n",d);
			}
			break;

			case 2:			
			if(s1==1) {		//TL/EURO
				e=a/6.69;
				printf("\nYou have %lf Euros\n",e);
			}
			else if(s1==2) {	//EURO/EURO
				printf("\nYou have %lf Euros\n",a);
			}
			else {
				d=a*6.14/6.69;	//DOLLAR/EURO
				printf("\nYou have %lf Euros\n",d);
			}
			break;

			case 3:
			if(s1==1) {		//TL/DOLLAR
				d=a/6.14;
				printf("\nYou have %lf Dollars\n",d);
			}
			else if(s1==2) {	//EURO/DOLLAR
				e=a*6.69/6.14;	
				printf("\nYou have %lf Dollars\n",e);
			}
			else {	//DOLLAR/DOLLAR
				printf("\nYou have %lf Dollars\n",a);
			}
			break;

			default:	//invalid selection
			printf("Your selection is invalid\n");
			break;
		}
		printf("\n");
	}
	printf("\n");
}
