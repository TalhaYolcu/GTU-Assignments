#include<stdio.h>
#include <math.h>
int q=50;
void add1(float a,float b,float c) {
	c=a+b;
	printf("Your result is = %f\n",c);	
	}
void subtract1(float a,float b,float c) {
	c=a-b;
	printf("Your result is = %f\n",c);
}
void multiply1(float a,float b,float c) {
	c=a*b;
	printf("Your result is = %f\n",c);
}
void divide1(float a,float b,float c) {
		c=a/b;
	printf("Your result is= %f\n",c);
	}
void nthpower(float a,float b) {
	int i=0,j=0;
	float temp=0,temp2=0,temp3=0,c;
	temp=a;
    if (b>=0) {
		for (i=1;i<b;i++) {
			temp2=temp*a;
			temp=temp2;
		}
	    printf("Your result is %f\n",temp2);
	}

	else {
		c=b*(-2)+b;
		for (i=1;i<c;i++) {
			temp2=temp*a;
			temp=temp2;
			}
	    temp3=1/temp2;
	    printf("Your result is %f\n",temp3);
	}
}
float average(float num,float sayac) {
	float i=0,j=0,temp=0,temp2=0;
	temp2=num/sayac;
	printf("\n Your result is: %f",temp2);
}
int maximum(){
	float arr[2347]={};
	float max;
	int c=0;
	int t;
	float b=1;
	float a;
	int z;
	while(b==1){
		printf("Enter a Number (to see maximum enter '0' 2 times):");
		scanf("%f",&a);
		if(a==0){
			printf("Enter '0' to see maximum,Enter '1' to add 0 to numbers:");
			scanf("%d",&z);
			if(z==0){
				max=arr[0];
				for(t=1;t<c;t++){
					if(max<arr[t]){
						max=arr[t];			
					}
				}
				printf("Maximum of numbers:%f\n",max);
				break;
			}
			if(z!=0){
				arr[c]=a;
				t++;
			}
		}
		else{
		arr[c]=a;
		c++;
		}
	}
}


int main() {
	
	int i=0,x=0,exit=0,j=0,z=0;
	float add=0,num1=0,num2=0,subtract=0,multiply=0,divisor=0,result;
	float num6=1,num61=0;
	float sayac6=0,sayac61=0,zeros=0,toplam=0,zero2=1;
	char exit6[1];
	int arr[1243],zeros2=0,num7=1;
	int sayac7=0,sayac71=0;

	i=1;
	start_point:
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n%% WELCOME TO GTU CALCULATOR MACHINE %%\n");
	printf("%% STUDENT NAME: YAKUP TALHA YOLCU %%\n");
	printf("%% PLEASE SELECT FROM THE FOLLOWING MENU : %%\n");
	
	printf("(1) ADD TWO NUMBERS\n");
	printf("(2) SUBTRACT TWO NUMBERS\n");
	printf("(3) MULTIPLY TWO NUMBERS\n");
	printf("(4) DIVIDE TWO NUMBERS\n");
	printf("(5) TAKE THE NTH POWER OF A NUMBER\n");
	printf("(6) FIND AVERAGE OF NUMBERS INPUTTED\n");
	printf("(7) FIND THE MAXIMUM OF NUMBERS INPUTTED\n");
	printf("(0) EXIT\n");
	printf("PLEASE SELECT:");
	scanf("%d",&x);
	
	switch(x) {
		case 1 :
			printf("Please enter first number");
			scanf("%f",&num1);
			printf("\nPlease enter second number");
			scanf("%f",&num2);
			add1(num1,num2,add);
			printf("\nfor reset press 0");
			scanf("%d",&exit);
			if (exit==0) {
				goto start_point;
			}
			break;
			
		case 2:
			printf("Please enter first number");
			scanf("%f",&num1);
			printf("\nPlease enter second number");
			scanf("%f",&num2);
			subtract1(num1,num2,subtract);
			printf("\nfor reset press 0");
			scanf("%d",&exit);
			if (exit==0) {
				goto start_point;
			}
			break;
		case 3:
			printf("Please enter first number");
			scanf("%f",&num1);
			printf("\nPlease enter second number");
			scanf("%f",&num2);
			multiply1(num1,num2,multiply);
			printf("\nfor reset press 0");
			scanf("%d",&exit);
			if (exit==0) {
				goto start_point;
			}
			break;
		case 4:	
		    printf("Please enter first number");
			scanf("%f",&num1);
			dividepoint:
			printf("\nPlease enter second number");
			scanf("%f",&num2);
			if (num2==0) {
				printf("Please enter a number that not 0");
				goto dividepoint;
			}
			
			divisor = num1/num2;
			divide1(num1,num2,divisor);
			printf("\nfor reset press 0");
		    scanf("%d",&exit);
			
			if (exit==0) {
				goto start_point;
			break;
			}
		case 5:
			printf("Please enter the bottom number");
			scanf("%f",&num1);
			printf("Please enter the power");
			scanf("%f",&num2);
			nthpower(num1,num2);	
			
		    printf("\nfor reset press 0");
		    scanf("%d",&exit);
		    if (exit==0) {
		        goto start_point;
		        break;
				}
	    case 6:
	    	while(x=x) {
	    		cs:
	    		sayac6++;
	    		while(num6!=0) {
	    			for(i=0;i<sayac6;i++) {
	    		    	printf("enter a number,for exiting or adding 0, press 0");
	    			    scanf("%f",&num6);
	    				toplam=toplam+num6;
	    				sayac61++;
	    			}
				}
				printf("IF YOU WANT TO FINISH, press 1;IF YOU WANT TO CONTINUE ENTER YOUR NEXT NUMBER");
				scanf("%f",&zeros);
				if(zeros==1) {
					
					 sayac61=sayac61-1;
			         average(toplam,sayac61);
					 break;
				}
				else {
					goto cs;
				}
				
			}
			toplam=0;
			num6=1;
			sayac6=0;
			sayac61=0;
			printf("\nfor reset press 0");
		    scanf("%d",&exit);
		    if (exit==0) {
		        goto start_point;
		        break;
			}
			case 7:
				
			maximum();
			            
			printf("\nfor reset press 0");
		    scanf("%d",&exit);
		    if (exit==0) {
		        goto start_point;
		        break;
			}
		default :
			printf("Please enter number that between 1 and 7");
			goto start_point;
			break;
	}
}
			
	    	
		
			
			
	    	
	    	
	    	
	    	
	    	
	    
	    	
	    
	     
	    
	    	
	    	
	    
			
	    	 


	
	

