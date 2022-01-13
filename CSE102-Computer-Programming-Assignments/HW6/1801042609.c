#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void game();							//taking words from file,creating board
int num();								//take which number of word
int len(char str[15]);					//finding length
int fx(int l,int d);					//retake x co-ordinat
int fy(int l,int d);					//retake y co-ordinat
void copyint(int*a,int*b);				//copy integers
void check(int newxy[2],char t[20][20],int x,int y,int d,int l);	//checking if there is another word 
char fill();			//fill table with random letters
int strcomp(char a[15],char b[15],int l1,int l2);			//string compare function
int play(char t[20][20],char w[15],char ch,int o,char entered[15]);	//playing game

int num() {		//taking words
	int r;
	r=1+rand()%95;
	return r;
}
int len(char str[15]) {		//finding length of word
	int i=0;
	while(str[i]!='\0') {
		i++;
	}
	return i;
}
int fx(int l,int d) { // x
	int i;
	int l2=19-l;			//depend on the direction we set the x and y coordinats
	int r;
	if(d==1) {
		i=rand()%19;
	}
	else if(d==2) {
		i=rand()%l2;	
	}
	else if(d==3) {
		i=rand()%l2;		
	}
	else if(d==4) {
		i=rand()%l2;		
	}
	else if(d==5) {
		i=rand()%19;
	}
	else if(d==6) {
		r=rand()%l2;
		i=r+l-1;
	}
	else if(d==7) {
		r=rand()%l2;
		i=r+l-1;		
	}
	else if(d==8) {
		r=rand()%l2;
		i=r+l-1;		
	}
	return i;
}
int fy(int l,int d) {	// y
	int i;
	int l2;
	int r;
	l2=19-l;	//depend on the direction we set the x and y coordinats
	if(d==1) {
		r=rand()%(l2);
		i=r+l-1;		
	}
	else if(d==2) {
		r=rand()%(l2);
		i=r+l-1;			
	}
	else if(d==3) {
		i=rand()%19;
	}
	else if(d==4) {
		i=rand()%l2;
	}
	else if(d==5) {
		i=rand()%l2;
	}
	else if(d==6) {
		i=rand()%l2;
	}
	else if(d==7) {
		i=rand()%19;
	}
	else if(d==8) {
		r=rand()%(l2);
		i=r+l-1;			
	}
	return i;
}
void copyint(int*a,int*b) {
		*a=*b;
}
void check(int newxy[2],char t[20][20],int x,int y,int d,int l) {
	int i;
	int x2;
	int y2;
	int r;
	int l2;
	l2=19-l;
	x2=x;
	y2=y;
	switch(d) {
		case 1:				//direction case 
		for(i=0;i<l;) {
			if(t[y][x]=='\t') {
				y--;
				i++;
			}
			else {
				x=fx(l,d);		//retake x and y
				y=fy(l,d);
				i=0;
				x2=x;
				y2=y;				
			}
		}
		break;

		case 2:
		for(i=0;i<l;) {			//do same operations
			if(t[y][x]=='\t') {
				y--;
				x++;
				i++;
			}
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);
				x2=x;
				y2=y;				
			}			
		}
		break;

		case 3:
		for(i=0;i<l;) {		//do same operations
			if(t[y][x]=='\t') {
				x++;
				i++;
			}
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);				
				x2=x;
				y2=y;				
			}			
		}
		break;

		case 4:
		for(i=0;i<l;) {		//do same operations
			if(t[y][x]=='\t') {
				y++;
				x++;
				i++;
			}
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);				
				x2=x;
				y2=y;				
			}			
		}
		break;

		case 5:
		for(i=0;i<l;) {		//do same operations
			if(t[y][x]=='\t') {
				y++;
				i++;
			}			
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);
				x2=x;
				y2=y;
				i=0;
			}
		}
		break;

		case 6:
		for(i=0;i<l;) {		//do same operations
			if(t[y][x]=='\t') {
				y++;
				x--;
				i++;
			}	
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);
				
				x2=x;
				y2=y;
			}		
		}
		break;

		case 7:
		for(i=0;i<l;) {		//do same operations
			if(t[y][x]=='\t') {
				x--;
				i++;
			}
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);				

				x2=x;
				y2=y;				
			}			
		}
		break;

		case 8:
		for(i=0;i<l;) {		//do same operations
			if(t[y][x]=='\t') {
				y--;
				x--;
				i++;
			}
			else {
				i=0;
				x=fx(l,d);
				y=fy(l,d);
				
				x2=x;
				y2=y;				
			}			
		}
	}
	newxy[0]=x2;	//assign x and y
	newxy[1]=y2;
}
char fill() {
	int a=97;
	int c;
	char ch;
	c=rand()%25;
	c=c+a;
	ch=(char)c;
	return ch; 
}
int strcomp(char a[15],char b[15],int l1,int l2) {
	int i;
	int r=1;
	if(l1==l2) {
		for(i=0;i<l1-1;i++) {
			if(a[i]==b[i]) {

			}
			else {
				r=0;
				break;
			}
		}
	}
	else {
		r=0;
	}
	return r;
}
int play(char t[20][20],char w[15],char ch,int o,char entered[15]) {
	int i;
	int l;
	int l2;
	int cnt=0;	
	int re;
	l=len(entered);			//length of entered string
	l2=len(w);				//length of word
	re=strcomp(w,entered,l,l2);					//ehecking if words are the same
	if(re==1) {
		if(t[ch-97][o]==entered[0]) {		//check if the first letter same with the table
			if(t[ch-98][o]==entered[1]) {		// direction 1
				for(i=2;i<l;i++) {
					if(t[ch-97-i][o]==entered[i]) {			// check if remained letters same with table
						cnt++;
					}
					else {			//if not break the loop
						cnt=0;
						break;
					}
				}
				if(cnt==l-2) {				//if entred word and coordinats true,make letters capital
					for(i=0;i<l;i++) {
						t[ch-97-i][o]=t[ch-97-i][o]-32;
					}
				}
			}
			else {
				if(t[ch-98][o+1]==entered[1]) {	// direction 2
					for(i=2;i<l;i++) {
						if(t[ch-97-i][o+i]==entered[i]) {// check if remained letters same with table
							cnt++;
						}
						else {			//if not break the loop
							cnt=0;
							break;
						}
					}
					if(cnt==l-2) {				//if entred word and coordinats true,make letters capital
						for(i=0;i<l;i++) {
							t[ch-97-i][o+i]=t[ch-97-i][o+i]-32;
						}
					}
				}
				else {
					if(t[ch-97][o+1]==entered[1]) {	// direction 3
						for(i=2;i<l;i++) {
							if(t[ch-97][o+i]==entered[i]) {// check if remained letters same with table
								cnt++;
							}
							else {			//if not break the loop
								cnt=0;
								break;
							}
						}
						if(cnt==l-2) {			//if entred word and coordinats true,make letters capital
							for(i=0;i<l;i++) {
								t[ch-97][o+i]=t[ch-97][o+i]-32;						
							}
						}
					}
					else {
						if(t[ch-96][o+1]==entered[1]) {	// direction 4
							for(i=2;i<l;i++) {
								if(t[ch-97+i][o+i]==entered[i]) {// check if remained letters same with table
									cnt++;
								}
								else {		//if not break the loop
									cnt=0;
									break;
								}
							}
							if(cnt==l-2) {		//if entred word and coordinats true,make letters capital
								for(i=0;i<l;i++) {
									t[ch-97+i][o+i]=t[ch-97+i][o+i]-32;					
								}
							}
						}
						else {
							if(t[ch-96][o]==entered[1]) {	// direction 5
								for(i=2;i<l;i++) {
									if(t[ch-97+i][o]==entered[i]) {// check if remained letters same with table
										cnt++;
									}
									else {		//if not break the loop
										cnt=0;
										break;
									}
								}
								if(cnt==l-2) {	//if entred word and coordinats true,make letters capital
									for(i=0;i<l;i++) {
										t[ch-97+i][o]=t[ch-97+i][o]-32;						
									}
								}
							}
							else {
								if(t[ch-96][o-1]==entered[1]) { // direction 6
									for(i=2;i<l;i++) {
										if(t[ch-97+i][o-i]==entered[i]) {// check if remained letters same with table
											cnt++;
										}
										else {		//if not break the loop
											cnt=0;
											break;
										}
									}
									if(cnt==l-2) {	//if entred word and coordinats true,make letters capital
										for(i=0;i<l;i++) {
											t[ch-97+i][o-i]=t[ch-97+i][o-i]-32;						
										}
									}
								}
								else {
									if(t[ch-97][o-1]==entered[1]) { // direction 7	
										for(i=2;i<l;i++) {
											if(t[ch-97][o-i]==entered[i]) {// check if remained letters same with table
												cnt++;
											}
											else {		//if not break the loop
												cnt=0;
												break;
											}
										}
										if(cnt==l-2) {	//if entred word and coordinats true,make letters capital
											for(i=0;i<l;i++) {
												t[ch-97][o-i]=t[ch-97][o-i]-32;
											}
										}
									}
									else {
										if(t[ch-98][o-1]==entered[1]) { // direction 8
											for(i=2;i<l;i++) {
												if(t[ch-97-i][o-i]==entered[i]) {// check if remained letters same with table
													cnt++;
												}
												else {		//if not break the loop
													cnt=0;
													break;
												}
											}
											if(cnt==l-2) { //if entred word and coordinats true,make letters capital
												for(i=0;i<l;i++) {
													t[ch-97-i][o-i]=t[ch-97-i][o-i]-32;
												}
											}
										}
										else {
											cnt=0;
										}				
									}				
								}			
							}						
						}
					}						
				}				
			}
		}
		if(cnt==l-2) {	//if coordinats and word true ,return 1
			return 1;
		}
		else {
			return 0;
		}	
	}
	else {
		return 0;
	}

}
void game() {
	char w2[100][15];		//whole words
	char w[10][15];			//words that will be selected
	char t[20][20];			//board
	char*file_path="words.txt";		//filepath of wordsfile
	char ch;		//char that will be taken from user and it will be used for coordinat
	char entered[15];	//entered string by user

	int i=0;	//counter
	int k;	//counterr
	int j;	//counter
	int m;	//counter
	int o;	//coordinat of letter that will be entered by user
	int arr[10];			//word number
	int arr2[10];			//word x
	int arr3[10];			//word y
	int arr4[10];			//word direction
	int arrx[10];			//word x again because we will need these values
	int arry[10];			//word y again because we will need these values
	int leng[10];			//leng array of words
	int newxy[2];			//we will need that array because x and y coordinats may change
	int number=0;			//counter
	int l;					//length of some string
	int r1;					//return value for playing game function

	FILE *fp;
	fp=fopen(file_path,"r");

	while(!feof(fp)) {				//reading words from file
		fscanf(fp,"%s",w2[i]);
		i++;
	}
	fclose(fp);
	for(i=0;i<100;i++) {			//if readed strings have other characters ,we need to clear them
		for(k=0;k<15;k++) {
			if(w2[i][k]=='\0') {
				for(j=14;j>k;j--) {
					w2[i][j]='\0';
				}
				break;
			}
			else {
			
			}
		}
	}
	for(i=0;i<20;i++) {		// making table more readable and we are gonna fill the full of table with letters	
		for(k=0;k<20;k++) {
			t[i][k]='\t';
		}
	}	
	srand(time(NULL));
	for(i=0;i<10;i++) {	//check if we got the same word again,take new word
		arr[i]=num();
		for(m=0;m<i;m++) {				
			if(arr[m]==arr[i]) {
				arr[i]=num();
			}
		}
	}
	for(i=0;i<10;i++) {				//copying words
		for(k=0;k<15;k++) {
			w[i][k]=w2[arr[i]][k];			
		}
	}
	for(i=0;i<10;i++) {   //determinig the direction 1 up, 2 uprigth, 3 right, 4 rightdown, 5 down,6 left down, 7 left, 8 upleft 
		arr4[i]=1+rand()%8;
	}
	for(i=0;i<10;i++) {	// determining x coordinats
		l=len(w[i]);
		arr2[i]=fx(l,arr4[i]);
		for(k=0;k<i;k++) {
			if(arr2[i]==arr2[k]) {				//if we got the same x value again,then retake x again to prevent intersect
				arr2[i]=fx(l,arr4[i]);
			}
		}
	}
	for(i=0;i<10;i++) {  //determining y coordinats
		l=len(w[i]);
		arr3[i]=fy(l,arr4[i]);
		for(k=0;k<i;k++) {
			if(arr3[i]==arr3[k]) {			//if we got the same y value again,then retake y again to prevent intersect
				arr3[i]=fy(l,arr4[i]);
			}
		}
	}
	printf("\n");
	printf("WORDS:");
	for(i=0;i<10;i++) {		//printing words
		printf(" %s ",w[i]);
	}
	printf("\n");
	for(i=0;i<10;i++) {		//copy x and y values
		copyint(&arrx[i],&arr2[i]);
		copyint(&arry[i],&arr3[i]);		
	}
	for(i=0;i<10;i++) {
		leng[i]=len(w[i]);			//take lengths of words
	}
	for(i=0;i<10;i++) {
		newxy[0]=0;			//make zero
		newxy[1]=0;
		switch(arr4[i]) {
			case 1:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);			//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arry[i]--;
			}
			break;
			case 2:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arry[i]--;
				arrx[i]++;
			}
			break;
			case 3:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arrx[i]++;
			}
			break;
			case 4:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arry[i]++;
				arrx[i]++;
			}
			break;
			case 5:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arry[i]++;
			}
			break;
			case 6:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arry[i]++;
				arrx[i]--;
			}
			break;
			case 7:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arrx[i]--;
			}
			break;
			case 8:
			check(newxy,t,arrx[i],arry[i],arr4[i],leng[i]);		//check if there is any word here
			copyint(&arrx[i],&newxy[0]);
			copyint(&arry[i],&newxy[1]);		
			copyint(&arr2[i],&arrx[i]);			
			copyint(&arr3[i],&arry[i]);
			for(k=0;k<leng[i];k++) {
				t[arry[i]][arrx[i]]=w[i][k];
				arry[i]--;
				arrx[i]--;
			}
			break;																								
		}
	}
	for(i=0;i<20;i++) {
		for(k=0;k<20;k++) {
			if(t[i][k]!='\t') {

			}
			else {
				t[i][k]=fill();				
			}
		}
	}
	printf("\n  ");
	for(i=0;i<20;i++) {			//prining horizontal line
		if(i<10) {
			printf(" %d ",i);			
		}
		else {
			printf("%d ",i);			
		}
	}
	printf("\n");
	for(i=0;i<20;i++) {
		printf("%c ",i+97);			//printing vertical line
		for(k=0;k<20;k++) {
			printf(" %c ",t[i][k]);
		}
		printf("\n");
	}
	for(i=0;i<10;i++) {
		printf("x:%d y:%d\t",arr2[i],arr3[i]);
	}
	printf("\n");
	while(1) {
		o=-1;
		printf("Please enter the coordinate and (space) the word ex:(e7 parched) or to exit,print EXIT:");
		scanf("\n%c%d %s",&ch,&o,entered);			//take info from user
		for(i=0;i<10;i++) {
			if((arr2[i]==o)&&(arr3[i]==(ch-97))) {		//find x and y coordinats of word that entered  by user
				break;
			}
		}
		if(o==-1) {		//EXIT 
			break;
		}
		else {
			r1=play(t,w[i],ch,o,entered);			//send to functions
			if(r1==1) {							//if coordinat and word is true
				for(k=0;k<len(entered);k++) {
					entered[k]=entered[k]-32;		//make capital letter
					for(i=0;i<10;i++) {
						if((arr2[i]==o)&&(arr3[i]==(ch-97))) {
							break;
						}
					}
					w[i][k]=entered[k];			//update word list
				}
				printf("\n");
				printf("WORDS:");		//updated list
				for(i=0;i<10;i++) {
					for(k=0;k<leng[i];k++) {
						printf("%c",w[i][k]);				
					}
					printf("  ");
				}
				printf("\n  ");
				for(i=0;i<20;i++) {			//updated table
					if(i<10) {
						printf(" %d ",i);			
					}
					else {
						printf("%d ",i);			
					}
				}
				printf("\n");			
				for(i=0;i<20;i++) {		//update table (cont)
					printf("%c ",i+97);
					for(k=0;k<20;k++) {
						printf(" %c ",t[i][k]);
					}
					printf("\n");
				}
				printf("\n");
				number++;		//increment counter
				if(number==10) {
					printf("\n\nYOU ARE DONE WELL NOW");			//user have found all words
					break;
				}			
			}
			else {
				printf("\nWrong answer,pls try again");
			}		
		}
	}
}
int main() {
 	printf("\nWELCOME TO WORD HUNTER GAME\n");
	game();
	printf("\n");
}
