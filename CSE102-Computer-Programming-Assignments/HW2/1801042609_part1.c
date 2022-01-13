#include<stdio.h>
#include<math.h>

int draw_triangle(int side1,int side2,int side3) {
	if(side1+side2>side3 && side1+side3>side2 && side2+side3>side1) {	//whether the triangle can be drawn or not
		return 1;   // it can be drawn
	}
	else {
		return 0;	// it cannot be drawn
	}
}
void type_triangle(int side1,int side2,int side3) {
	if(side1==side2 && side2==side3 && side1==side3) {  //Equiliterial
		printf("\nIt is a Equilateral Triangle");
	}
	else if(side1==side2 || side2==side3 || side1==side3) {
		printf("\nIt is a Isosceles Triangle");			//Isosceles
	}
	else {
		printf("\nIt is a Scalene Triangle");			//Scalene
	}	
}
int perimeter_triangle(int side1,int side2,int side3) {		//calculating perimeter
	int p=side1+side2+side3;
	return p;
}
double area_triangle(int side1,int side2,int side3,int perimeter) {		//calculating area
	double area,per2;		//per2 will be the half of the perimeter
	per2=(perimeter)/2.000000;											//I did 2.000000 because per2 has double type
	area=sqrt(per2*(per2-side1)*(per2-side2)*(per2-side3));				//formula for area
	return area;
}
int main() {
	
	int side1,side2,side3,r1=0,r2;		//defining sides of the triangle first and second return values
	double r3;
	printf("\nThe length of first side:\n");
	scanf("%d",&side1);
	printf("The length of second side:\n");
	scanf("%d",&side2);
	printf("The length of third side:\n");
	scanf("%d",&side3);

	r1=draw_triangle(side1,side2,side3);	//whether it can be drawn or not
	
	if(r1==1) {
		printf("\nAccording to the triangle inequality theorem,this triangle can be drawn\n");
		
		type_triangle(side1,side2,side3);		//determining the type of the triangle
	
		r2=perimeter_triangle(side1,side2,side3);	//calculating perimeter of the triangle
		printf("\nThe perimeter of the triangle:%d",r2);
		
		r3=area_triangle(side1,side2,side3,r2);			//calculating the area of the triangle
		printf("\nThe area of the triangle %lf\n",r3);
	}
	else {        //it cannot be drawn
		printf("\nAccording to the triangle inequality theorem,this triangle cannot be drawn\n");
	}
	printf("\n");
}
