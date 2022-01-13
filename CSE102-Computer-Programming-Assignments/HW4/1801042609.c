#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

char decrypt_numbers(int number) {		//part1 and part2 functions
	
	char ch;
	
	switch (number) {
					//finding counterparts of numbers 
		case 0:
		ch=' ';
		break;

		case 1:
		ch='-';
		break;

		case 2:
		ch='_';
		break;

		case 3:
		ch='|';
		break;

		case 4:
		ch='/';
		break;

		case 5:
		ch='\\';
		break;

		case 6:
		ch='O';
		break;
		
		case 7:
		ch='\n';
		break;
	}
	return ch;
}						//function of part1 and part2
int dee(char a) {		//helper function for part1 because file couldn't read file inside as an integer,then we got them as a character and turn into number
	
	int inps;
	
	switch(a) {
		
		case'0':
		inps=0;
		break;

		case'1':
		inps=1;
		break;

		case'2':
		inps=2;
		break;

		case'3':
		inps=3;
		break;

		case'4':
		inps=4;
		break;

		case'5':
		inps=5;
		break;

		case'6':
		inps= 6;
		break;

		case'\n':	//if the character that we read is '\n',return 7 and 7's counter will be '\n' in the other function
		inps=7;
		break;
	}
	return inps;
}
void decrypt_and_print(char*file_path) {	//function of part 1
	
	FILE *fp1;					//filepointer
	fp1=fopen(file_path,"r");	//opening the file read mode
	int inps=1;			//integer value for operations
	char c,a;			//char values for operations
		
	while(!feof(fp1)) {		//while file pointer is not at the end of file
		
		fscanf(fp1,"%c",&a);	//reading as a character
		inps=dee(a);		//switcing it into number(helper function)
		c=decrypt_numbers(inps);	//find symbols as counterpart of numbers
		printf("%c",c);				//printing
	}
	fclose(fp1);	//closing the file
}
void deep_decrypt_and_print(char*file_path) {	//function of part2
	
	FILE *fp2;					//filepointer
	fp2=fopen(file_path,"r");	//opening the file read mode
	int inps2=1;				//integer value for operation
	char a2,a3,a4,b2,b3,b6,ch;	//characters for reading
	
	while(!feof(fp2)) {			//while file pointer is not the end of the file

		fscanf(fp2,"%c",&a2);	//read
		if(a2=='\n') {
			inps2=7;			//if the character that we read is '\n',then we will sen 7 value to the function
		}
		else {					//send char and get number value
			inps2=dee(a2);		//else send char and get as a number
			fscanf(fp2,"%c",&a3);	//read second thing
			if(a3=='\n') {			

			}
			else {	//if second thing is not '\n',send it and sum previous
				
				inps2=inps2+dee(a3);	//send char and get number value
				fscanf(fp2,"%c",&a4);	//read third thing
				if(a4=='\n') {			//if third thing is new line ,decrement filepointer's cursor by 1 because we could get 2 values for operation
					fseek(fp2,-1,SEEK_CUR);
				}
				else {				
					inps2=inps2+dee(a4);	//send char and get number value
					fseek(fp2,-2,SEEK_CUR);		//if it is not the new line,then decrement filepointer's cursor by 2 because we could get 3 values for operation
				}	
			}
			inps2=inps2%7;	//take them mod by 7
		}
		ch=decrypt_numbers(inps2);	//send them into decrypt numbers function get character as counterpart
		printf("%c",ch);
	} 
}
void refresh_position(int*x,int*y,double*d,double*r) {	//function of part3
	
	*x=1+rand()%11;					//refreshing the x and y coordinats
	*y=1+rand()%11;
	*d=sqrt(abs((*x)-6)*abs((*x)-6+abs((*y)-6)*abs((*y)-6)));	//finding distance between enemy camp and our camp
	*r=sqrt((*x)*(*x)+(*y)*(*y));			//finding displacement of enemy camp
		
}
void track_machine() {		//part3 function

	int i,j,count=0;		//variables for count and for loop operations
	int x1=0,y1=0,dis1,dis2,k,l,a,b;		//integer values for coordinats,displacement,distance
	double disp,dist;	//double values for displacement and distance
	int *x,*y;			//pointers for coordinats
	double *d,*r;		//pointers for displacement and distance
	char cd;			//we will take input for refresh or Enemy 
	
	x=&x1;			//pointing
	y=&y1;
	r=&disp;
	d=&dist;
	k=x1;			//we will use x1's first value
	l=y1;			//we will use y1'S first value

	x1=1+rand()%11;
	y1=1+rand()%11;

	while(count==0) {
		for(i=1;i<12;i++) {
			for(j=1;j<12;j++) {
				if(x1==i && y1==j) {
					printf("E\t");		//camp of enemy
					
				}
				else if(i==6 && j==6) {
					printf("O\t");		//our camp
				}
				else {
					printf("*\t");		//fields
				}
			}
			printf("\n");
		}
		a=abs(x1-k);	//absolute value of x displacement of enemy
		b=abs(y1-l);	//absolute value of y displacement of enemy
		k=x1;			//we will use it later on 
		l=y1;			//we will use it later on

		disp=sqrt(a*a+b*b);	//displacement of enemy camp
		dis1=abs(x1-6);		//absolute value of x distance
		dis2=abs(y1-6);		//absolute value of y distance
		dist=sqrt(dis1*dis1+dis2*dis2);		//distance to our camp

		printf("\nEnemies X position: %d, Y postion: %d,Displacement: %.2lf, Distance to our camp: %.2lf",x1,y1,disp,dist);
		printf("\nCommand waiting...\n");
		
		scanf("%s",&cd);
		printf("\n");
		if(cd=='R') {
			refresh_position(x,y,d,r);		//refresh the enemy camp
		}
		else {
			count=1;		//get out of the loop
		}
	}
}
int dee2(char ch) {		//part4 function
	
	int a;
	
	switch(ch) {
		
		case ' ':
		a=0;
		break;

		case '-':
		a=1;
		break;

		case '_':
		a=2;
		break;

		case '|':
		a=3;
		break;

		case '/':
		a=4;
		break;

		case '\\':
		a=5;
		break;

		case 'O':
		a=6;
		break;
		
	}
	return a;
}
void encrypt_messages(char*file_path) {		//part4 function
	
	FILE *fp;				
	fp=fopen(file_path,"r");
	FILE *fp2;					//file that we will write on it
	fp2=fopen("encrypted_p4.img","w");
	
	char ch1,ch2,ch3;			//character that we will read later on
	int a=0,b=0,c=0,d=0,e=0,f=0,g=0,k=0,j=0,sum=0;		//integers that will be needed
	
	while(!feof(fp)) {		//while filepointer is not at the end of the file
						//we will need a's previous value
		fscanf(fp,"%c",&ch1);	//read it
		j++;
		
		if(ch1=='\n') {
			fprintf(fp2,"\n");	//if it is new line,print new file new line
			j=0;
		}
		else {
			if(j==1) {		//if that's first reading
				a=dee2(ch1);	//send it to function and get number counterpart of symbol
				sum=a;			//it is the first value then,we will use just it
				b=a;			//we will need it's value
				fprintf(fp2,"%d",sum%7);	//take mod number by 7 and print into file
			}
			else {
				if(j==2) {		//if that's is second reading
					a=dee2(ch1);	//send symbol,find number
					sum=b+a;		//sum with the previous(first) value
					c=a;			//we will use it(not sum,we will use second value)
					fprintf(fp2,"%d",sum%7);	//take mod sum by 7 and print into file
				}
				else {
					if(j==3) {		//if that is third reading
						a=dee2(ch1);	//send it to function and get number counter part of symbol
						d=a;			//we will use it
						sum=c+a;		//sum with the previous(second value)
						fprintf(fp2,"%d",sum%7);	//take mod by 7 and print
					}
					else {
						//if that is fourth or more reading increment cursor by 3	
						fseek(fp,-3,SEEK_CUR);
						fscanf(fp,"%c",&ch1);	//read 3 times and send into function
						d=dee2(ch1);
						fscanf(fp,"%c",&ch1);
						e=dee2(ch1);
						fscanf(fp,"%c",&ch1);
						f=dee2(ch1);
						sum=d+e+f;		//sum them
						fprintf(fp2,"%d",sum%7);	//take mod by 7 and print into file
					}
				}
			}
		}
	}
	fclose(fp);		//closing files
	fclose(fp2);
}
void menu() {			//part5 function
	
	int a=0;	//variable for switch case
	int p=0;	//variable for quitting
	char*e1="encrypted_p1.img";		//file path variables
	char*e2="encrypted_p2.img";
	char*d4="decrypted_p4.img";

	while(p<1) {
		printf("\n1-) Decrypt and print encrypted_p1.img");
		printf("\n2-) Decrypt and print encrypted_p2.img");
		printf("\n3-) Switch on the tracking machine");
		printf("\n4-) Encrypt the message");
		printf("\n5-) Switch off\n");
		printf("\nPlease make your choice:\n");
		scanf("%d",&a);
		
		switch(a) {

			case 1:
			decrypt_and_print(e1);	//user chose decrypt and print(part1)
			break;

			case 2:
			deep_decrypt_and_print(e2);	//user chose deep decrypt and print(part2)
			break;

			case 3:
			track_machine();	//user chose track machine(part3)
			break;

			case 4:
			encrypt_messages(d4);	//user chose encrypt messages(part4)
			break;

			case 5:
			printf("\nQuitting\n");	//user chose switching off
			p=1;	//get out of the menu
			break;

			default:
			printf("\nWrong option.\n");	//user chose wrong option
			break;
		}
	}
}
int main() {
	menu(); //menu function
}
