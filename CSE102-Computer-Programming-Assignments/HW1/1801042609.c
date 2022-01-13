#include<stdio.h>  //standart input-output
#include<math.h>	//mathematical 

void find_root() {  //part1
	int a,b,c;  //defining coefficients of equation
	double r1,r2,delta,i=0,temp;    //defining roots,delta(discriminant),squareroot of discriminant,temp value(to order)
	printf("Please Enter the first coefficient:");
	scanf("%d",&a);
	printf("Please Enter the second coefficient:");
	scanf("%d",&b);
	printf("Please Enter the third coefficient:");
	scanf("%d",&c);
	
	delta=(b*b)-(4*a*c);  //discriminant=b^2-4*a*c
	
	if(delta>=0) {
		i=sqrt(delta);
		
		r1=((-b)-i)/(2*a);         //defining roots 
		r2=((-b)+i)/(2*a);
		
		if(r1<r2) {       // ordering roots descending
			temp=r1; 
			r1=r2;
			r2=temp;
		}
		if(b<0 && c>0) {
			printf("Your equation: %d x^2  %d x + %d have real roots {%lf,%lf}\n",a,b,c,r1,r2); // b is negative,c is positive
		}
		else if(b<0 && c<0) {
			printf("Your equation: %d x^2  %d x  %d have real roots {%lf,%lf}\n",a,b,c,r1,r2);  //both b and c are negative
		}
		else if(b>0 && c<0) {
			printf("Your equation: %d x^2 + %d x  %d have real roots {%lf,%lf}\n",a,b,c,r1,r2); //b is positive,c is negative
		}
		else {
			printf("Your equation: %d x^2 + %d x + %d have real roots {%lf,%lf}\n",a,b,c,r1,r2); //both b and c are positive
		}
		
	}  //end of if(checking discriminant positive)
	else {
		printf("Your equation: %d x^2 + %d x + %d does not have any real roots.",a,b,c);	
	}
}
void find_newtonian_root() {  //part2
	int a,b,c;  //defining coefficients of equation
	double r1,r2,delta,i=0,temp,x,fx,diff,difference1,difference2,g1,g2,g3,g4,g5; //defining roots,discriminant,squareroot of discriminant,temp value for ordering roots,x value,function,derivative of function,differences between guesses and roots and initial guesses
	
	printf("Please Enter the first coefficient:");
	scanf("%d",&a);
	printf("Please Enter the second coefficient:");
	scanf("%d",&b);
	printf("Please Enter the third coefficient:");
	scanf("%d",&c);
	printf("Please enter the initial:");
	scanf("%lf",&x);
	
	delta=(b*b)-(4*a*c);  //discriminant=b^2-4*a*c
	
	i=sqrt(delta);

	r1=((-b)-i)/(2*a);         //defining roots 
	r2=((-b)+i)/(2*a);

	if(r1<r2) {       // ordering roots descending
			temp=r1; 
			r1=r2;
			r2=temp;
	}
	if(b<0 && c>0) {
			printf("Your equation is %d x^2 %d x + %d  and iterations are\n",a,b,c); // b is negative,c is positive
	}
	else if(b<0 && c<0) {
			printf("Your equation is %d x^2 %d x %d  and iterations are\n",a,b,c);  //both b and c are negative
	}
	else if(b>0 && c<0) {
			printf("Your equation is %d x^2 + %d x  %d  and iterations are\n",a,b,c); //b is positive,c is negative
	}
	else {
			printf("Your equation is %d x^2 + %d x + %d  and iterations are\n",a,b,c); //both b and c are positive
	}
	diff=2*a*x+b;    //derivative of the function
	g1=x-(a*x*x+b*x+c)/diff;	//guess 1
	fx=a*g1*g1+b*g1+c;			//function 1
	
	difference1=fabs(g1-r1);   //calculating differences between roots and guesses
	difference2=fabs(g1-r2);


	if(difference1>difference2) {   //making difference1 is smaller so that we are going to use it
		temp=difference1; 
		difference1=difference2;
		difference2=temp;
	}
	printf("\nStep\tx\t\tf(x)\t\tDifference\n\n");  
	printf("x1\t%lf\t%lf\t%lf\n",g1,fx,difference1);

	x=g1;                           //2nd value for x
	diff=2*a*x+b;					//derivative of the function
	g2=x-(a*x*x+b*x+c)/diff; 		//guess 2
	fx=a*g2*g2+b*g2+c;				//function 2
	
	difference1=fabs(g2-r1);   //calculating differences between roots and guesses
	difference2=fabs(g2-r2);


	if(difference1>difference2) {   //making difference1 is smaller so that we are going to use it
		temp=difference1;
		difference1=difference2;
		difference2=temp;
	}
	printf("x2\t%lf\t%lf\t%lf\n",g2,fx,difference1);

	x=g2;										//DOING SAME OPERATIONS AGAIN
	diff=2*a*x+b;
	g3=x-(a*x*x+b*x+c)/diff;
	fx=a*g3*g3+b*g3+c;
	
	difference1=fabs(g3-r1);
	difference2=fabs(g3-r2);

	if(difference1>difference2) {
		temp=difference1;
		difference1=difference2;
		difference2=temp;
	}
	printf("x3\t%lf\t%lf\t%lf\n",g3,fx,difference1);

	x=g3;										//DOING SAME OPERATIONS AGAIN
	diff=2*a*x+b;
	g4=x-(a*x*x+b*x+c)/diff;
	fx=a*g4*g4+b*g4+c;
	
	difference1=fabs(g4-r1);
	difference2=fabs(g4-r2);

	if(difference1>difference2) {
		temp=difference1;
		difference1=difference2;
		difference2=temp;
	}
	printf("x4\t%lf\t%lf\t%lf\n",g4,fx,difference1);

	x=g4;                                      //DOING SAME OPERATIONS AGAIN
	diff=2*a*x+b;
	g5=x-(a*x*x+b*x+c)/diff;
	fx=a*g5*g5+b*g5+c;
	
	difference1=fabs(g5-r1);
	difference2=fabs(g5-r2);

	if(difference1>difference2) {
		temp=difference1;
		difference1=difference2;
		difference2=temp;
	}
	printf("x5\t%lf\t%lf\t%lf\n",g5,fx,difference1);
}

int find_multiple_closest(int a, int b) {  //part3
	
	int c,d,e,f;   //defining divisor,mod,half of the b,multiple of b
	c=a/b;  // divisor
	d=a%b;	// mod
	e=b/2;	//half of the b
	f=b*c+b;  // the smallest multiple of b that larger than a
	
	if(b==0) {   ///if b is 0 multiple of 0 is should be 0
		return 0;
	}
	else {
		if(d==0) {  // a is multiple of b 
			return a;
		}
		else {
			if(f-a>e) {  //if multiple of b is closer to (a) than (multiple of b)+b
				return b*c;
			}
			else {
				return f;
			}
		}
	}
}

int main() {
	printf("Part 1:\n");
	find_root();
	
	printf("\n\nPart 2:\n");
	find_newtonian_root();
	
	printf("\n\nPart 3:\n");
	int z=0,t=0,y=0; 									//defining variables for numbers that will be taken and variable for return value
	printf("Please enter first number:");
	scanf("%d",&z);
	printf("Please enter second number:");
	scanf("%d",&t);
	
	y=find_multiple_closest(z,t);
	
	if(y==z) {    //if z is multiple of t
		printf("Closest number to %d that is multiple of %d is itself\n.",z,t);
	}
	else {
			printf("Closest number to %d that is multiple of %d is %d\n.",z,t,y);
	}
	return 0;
}