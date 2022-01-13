#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define arraysize 500
#define stringsize 500
#define N 10

void menu();

void makearrayempty(int arr[],int arrays,int i);				//part1 functions
void menu2(int arr[arraysize]);
void menu3();
void generate_hoftstadters_sequence (int*arr,int n);
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);			

void install_pipes (int visited[N][N], int x, int y, int orientation,int counter);		//part2 function

char* remove_duplicates (char* str);						//part3 functions
void slide(char *str);

void menu() {
	int i;
	int k;
	int opt1;
	int arr[arraysize];				//hoftstadter array
	int flag=0;
	int visited[N][N];				//field array
	int o;

	char str[stringsize];			//entered string
	char*newstring[1];				//return string

	for(i=0;i<N;i++) {				//preventing the overflow and fill array with 0's
		for(k=0;k<N;k++) {
			if(i==0||i==9) {
				visited[i][k]=1;
			}
			else if(k==0||k==9) {
				visited[i][k]=1;
			}
			else {
				visited[i][k]=0;
			}
		}
	}
	srand(time(NULL));
	while(flag==0) {
		printf("\nWelcome to Homework 8, please choose one of the parts to continue\n------------------------\n");
		for(i=1;i<=3;i++) {
			printf("(%d) Execute Part %d\n",i,i);
		}
		printf("(%d) Exit\n",i);
		printf("Your Choice:\n");
		scanf("%d",&opt1);
		switch(opt1) {	
			case 1:				//PART1
			menu2(arr);
			break;

			case 2:			//PART2
			o=1;		
			printf("\nFirst setup:\n");		
			install_pipes(visited,0,0,o,0);

			break;

			case 3:                 //PART3
			printf("\nEnter the string:\n");
			scanf(" %[^\n]s",str);
			*newstring=remove_duplicates(str);
			printf("The true string is:%s\n",*(newstring));
			break;

			case 4:			//EXIT
			flag=1;
			break;
		}
	}
}
void makearrayempty(int arr[],int arrays,int i) {			//MAKING HOFTSTADTER ARRAY EMPTY
	if(i<arrays) {
		makearrayempty(arr,arrays,i+1);
		arr[i]=arr[arrays-1];
	}
	else {
		arr[arrays-1]=0;
	}
}
void menu2(int arr[arraysize]) {
	int opt2;
	int fa;				//NUMBER THAT USER ENTERED
	int i;
	int max;
	int sum;
	int max_value=-1;
	int flag2=0;
	double std;
	double mean=0;
	while(flag2==0) {
		menu3();
		scanf("%d",&opt2);
		switch(opt2) {
			case 1:			//FILLING ARRAY BY SEQUENCE
			makearrayempty(arr,arraysize,0);
			printf("\nPlease enter a number to fill array\n");
			scanf("%d",&fa);
			generate_hoftstadters_sequence(arr,fa);
			for(i=0;i<fa;i++) {
				printf("%d ",arr[i]);				//PRINTING ARRAY
			}
			printf("\n");
			break;

			case 2:			//FINDNG MAX VALUE OF ARRAY
			max=find_max(arr,fa,max_value);
			printf("\nBiggest number of the array:%d\n\n",max);
			break;

			case 3:			//FINDING SUM
			*(arr+500)=0;							//CHECK IF USER ENTERD 500
			sum=sum_array(arr);
			printf("\nSum of the array:%d\n\n",sum);
			break;

			case 4:						//STANDART DEVIATION AND MEAN
			std=std_array(arr,&mean,fa,0);
			printf("\nStandart Deviation of the array is:%lf\nMean of of the array is:%lf\n",std,mean);
			break;

			case 5:
			printf("\nQuitting\n");
			flag2=1;
		}		
	}
}
void menu3() {							//MENU OF PART1
	printf("\nPlease make your Choice\n-----------------");
	int i;
	for(i=1;i<6;i++) {
		switch(i) {
			case 1:
			printf("\n(%d) Fill Array",i);
			break;

			case 2:
			printf("\n(%d) Find Biggest Number",i);
			break;	
			
			case 3:
			printf("\n(%d) Calclulate Sum",i);
			break;	

			case 4:
			printf("\n(%d) Calculate Standart Deviation",i);
			break;	

			case 5:
			printf("\n(%d) Exit\n",i);
			break;												
		}
	}
}
void generate_hoftstadters_sequence (int*arr,int n) {
	int a;
	int b;
	arr[0]=1;				//FIRST AND SECOND VALUES ARE 1
	arr[1]=1;	
	if(n==1) {				//IF USER ENTERED 1
		arr[n-1]=1;		
	}
	else if(n==2) {			//IF USER ENTERED 2
		arr[n-1]=1;		
	}
	else if(n>=3) {			
		generate_hoftstadters_sequence(arr,n-1);		//FIRSTLY FILL THE ARRAY RECURSIVELY // WE DECREMENING THE N'S VALUE BY 1 SO ;UNTIL AT N=3 FUNCTION WILL GO TOP TO BOTTOM SINCE N=3 ,FUNCTION GO BOTTOM TO TOP
		b=n-arr[n-3];									//SECOND TERM IN THE FORMULA
		a=n-arr[n-2];									//FIRST TERN IN THE FORMULA
		arr[n-1]=arr[a-1]+arr[b-1];						//SUM THEM
	}
}
int find_max (int arr[], int index, int max_value) {
	if(arr[1]==0) {				//IF ARRAY'S SECOND ELEMENT IS 0,THAT MEANS WE HAVE LAST ELEMENT OF THE TRUE ARRAY IN THE ARRAY's FIRST ELEMENT
		if(arr[0]>max_value) {		//IF LAST ELEMENT (FIRST ELEMENT) OF THE ARRAY IS LARGER THAN MAX VALUE THAT FOUND OUT SO FAR,THEN MAX VALUE CHANGED
			max_value=arr[0];
		}
	}
	else {
		if(arr[0]>max_value) {				//IF ELEMENT OF THE ARRAY IS LARGER THAN MAX VALUE THAT FOUND OUT SO FAR, CHANGE MAX VALUE AND INCREMENT ARRAY POINTER BY 1 SEND IT INTO FUNCTION AGAIN
			max_value=find_max(arr+1,index,arr[0]);			
		}
		else {				//IF MAX VALUE DON'T CHANGE INCREMENT POINTER ARRAY BY 1 AND SEND TO FUNCTION AGAIN
			max_value=find_max(arr+1,index,max_value);
		}
	}
	return max_value;
}
int sum_array (int arr[]) {
	int i;
	int sum=0;
	i=*arr;
	if(*(arr+1)>0) {				//IF THE SECOND ELEMENT(ACTUALLY LAST) OF THE ARRAY IS DETERMINED(WE DETERMINED AS THIS:IF NEXT ELEMENT OF THE ARRAY IS 0,THEN THIS ELEMENT IS LAST ELEMENT OF THE ARRAY)
		sum=i+sum_array(arr+1);			//IF THIS IS NOT THE LAST ELEMENT OF THE ARRAY,THEN INCREMENT POINTER BY 1 AND SEND INTO FUNCTION
	}
	else {
		sum=*arr;			//IF THIS ELEMENT OF THE ARRAY IS LAST TAKE IT'S VALUE AND RETURN
	}
	return sum;
}
double std_array (int arr[], double *mean, int n, int index) {
	double a;
	double b;
	double std;
	double std2;
	double c;

	c=(double)arr[index]/n;				//MEAN COULD FIND AS LIKE THIS:DIVIDE EVERY TERM BY NUMBER OF TERMS AND SUM THAT YOU FOUND
	*mean=*mean+c;

	if(n==index+1) {		//FIND IT IS THE LAST ELEMENT
		a=(double)arr[index]-*mean;				//TO FIND STD
		b=a*a;				//TAKE SQUARE
		std=b;	
	}
	else {
		std=std_array(arr,mean,n,index+1);			//IF IT IS NOT THE LAST ELEMENT,INCREMENT INDEX BY 1 SEND INTO FUNCTION AGAIN(ACTUAL INDEX STAYS)
		a=(double)arr[index]-*mean;
		b=a*a;					//TAKE SQUARE
		std=std+b;		//SUM THEM
	}
	if(index==0) {				//FIRSTLY FUNTION GOES TOP TO BOTTOM AND THEN IT COMES BACK,WHEN IT'S BACK N WILL BE AGAIN 0
		std2=sqrt(std/(n-1));
		std=std2;
	}
	return std;
}
void slide(char *str) {					//IF THERE IS DUPLICATES CHAR,THAT MEANS WHOLE CHARS OF THE ARRAY SHOULD BE SLIDED TO LEFT 1 TIME
	if(*str!='\0') {				//IF THE LAST ELEMENT
		*str=*(str+1);
		slide(str+1);
	}
}
char* remove_duplicates (char* str) {
	char*str2;
	str2=str+1;
	if(*(str2)=='\0') {			//IF THE LAST ELEMENT
		return str-1;
	}
	else {
		if(*str2==*(str)) {			//IF THERE IS A DUPLICATED CHAR
			slide(str+1);
			str2=remove_duplicates(str);				//SEND INTO NEW CHAR'S POINTER
		}
		else {
			str2=remove_duplicates(str+1);		//IF THERE IS NO DUPLICATED CHAR INCREMENT POINTER BY 1 AND SEND		
		}		
	}
	return str;
}
void install_pipes (int visited[N][N], int x, int y, int orientation,int counter) {
	int c;
	c=counter;
	x+=1;
	y+=1;

	if(counter==64) {
		printf("\n\nSecond setup:\n");			
	}
	else if(counter==64*2) {
		printf("\n\nThird setup:\n");			
	}
	else if(counter==64*3) {
		printf("\n\nFourth setup:\n");			
	}
	else if(counter==64*4) {
		printf("\n\nFifth setup:\n");			
	}
	else if(counter==64*5) {
		printf("\n\nSixth setup:\n");			
	}
	else if(counter==64*6) {
		printf("\n\nSeventh setup:\n");			
	}
	else if(counter==64*7) {
		printf("\n\nEighth setup:\n");			
	}
	else if(counter==64*8) {
		printf("\n\nNineth setup:\n");			
	}
	else if(counter==64*9) {
		printf("\n\nTenth setup:\n");			
	}	

	if((visited[y+2][x+1]==0)&&(orientation==1)) {				//O1
		visited[y+2][x+1]=1;
		y+=2;
		x+=1;
		counter+=1;					
	}	
	else if((visited[y+1][x-2]>0)&&(orientation==2)) {			//O2
		visited[y+1][x-2]=1;
		y+=1;
		x-=2;
		counter+=1;	
	}
	else if((visited[y-2][x-1]>0)&&(orientation==3)) {			//O3
		visited[y-2][x-1]=1;
		y-=2;
		x-=1;
		counter+=1;		
	}
	else if((visited[y-1][x+2]>0)&&(orientation==4)) {			//O4
		visited[y-1][x+2]=1;
		y-=1;
		x+=2;
		counter+=1;	
	}
	else if((visited[y+1][x+2]>0)&&(orientation==5)) {			//O5
		visited[y+1][x+2]=1;
		y+=1;
		x+=1;
		counter+=1;	
	}	
	else if((visited[y+2][x-1]>0)&&(orientation==6)) {			//O6
		visited[y+2][x-1]=1;
		y+=2;
		x-=1;
		counter+=1;	
	}
	else if((visited[y-1][x-2]>0)&&(orientation==7)) {			//O7
		visited[y-1][x-2]=1;
		y-=1;
		x-=2;
		counter+=1;	
	}	
	else if((visited[y-2][x+1]>0)&&(orientation==8)) {			//O8
		visited[y-2][x+1]=1;
		y-=2;
		x+=1;
		counter+=1;	
	}
	else {	
		if(orientation==1) {
			y-=2;
			x-=1;
		}
		else if(orientation==2) {
			y-=1;
			x+=2;
		}
		else if(orientation==3) {
			y+=2;
			x+=1;
		}
		else if(orientation==4) {
			y+=1;
			x-=2;
		}
		else if(orientation==5) {
			y-=1;
			x-=2;
		}
		else if(orientation==6) {
			y-=2;
			x+=1;
		}
		else if(orientation==7) {
			y+=1;
			x+=2;
		}
		else if(orientation==8) {
			y+=2;
			x-=1;
		}
	}
	if(counter!=640) {
		if(c==counter-1) {
			printf("O%d , ",orientation);			
		}
		orientation=1+rand()%8;
		install_pipes(visited,x,y,orientation,counter);
	}	

	printf("\n");
}
int main() {
	menu();		
}