#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int numPathsHome(int street,int avenue);		

typedef struct Hospital {			//PART 2 STRUCT
	char* name;
	char citiesServed[3];
}Hosp;

int canOfferCovidCoverage(char _cities[7],char _locations[4][3],int _numHospitals,struct Hospital results[4]);

typedef struct card {		//PART 3 STRUCT
	const char *face;
	const char *suit;
}cards;

void fill(cards cardss[52],int i);		//FILLING ARRAY FOR PART 3 
void check(int random[52],int*i,int k);		//CHECKING ELEMENTS OF THE ARRAY IF THEY ARE THE SAME

int numPathsHome(int street, int avenue) {
	int r;
	int p;
	int temp;
	int m;
	if((street>2)&&(avenue>2)) {		//IF BOTH OF THEM ARE LARGER THAN TWO RESULT WILL BE SUM OF THE UPPER OPERATION AND LEFT OPERATION LIKE THAT:
										//ASSUME THAT WE ARE TRYING TO FIND STREET->5 AVENUE ->5 WE CAN FIND AS :STREET 4 AVENUE 5   +  AVENUE 5 STREET 4
										//SUM OF THESE TWO THINGS ARE 35 , THEN 35*2=70 WE OBTAINED 5 5 NOW.
		r=numPathsHome(street-1,avenue);
		m=numPathsHome(street,avenue-1);
		p=m+r;
	}
	if(street==2) {				//IF ONE OF THEM IS 2 ,RESULT WILL BE OTHER ONE
		p=avenue;
	}
	if(avenue==2){				//IF ONE OF THEM IS 2,RESULT WILL BE OTHER ONE
		p=street;
	}
	if((street<2)||(avenue<2)) {		//IF BOTH OF THEM SMALLER THAN 2,RESULT WILL BE 1
		p=1;
	}
	return p;
}
int canOfferCovidCoverage(char _cities[7],char _locations[4][3],int _numHospitals,Hosp results[4]) {
	int h=0;
	if(_numHospitals==1) {				//FIRST HOSPITAL
		if(results[_numHospitals].citiesServed[0]=='B') {		//CHECK IF WE REPLACE THE 2ND HOSPITAL BEFORE

			results[_numHospitals-1].citiesServed[0]=_cities[0];			//REPLACE CITIES
			_locations[0][0]=results[_numHospitals-1].citiesServed[0];
			
			results[_numHospitals-1].citiesServed[1]=_cities[2];
			_locations[0][1]=results[_numHospitals-1].citiesServed[1];

			results[_numHospitals-1].citiesServed[2]=_cities[3];
			_locations[0][2]=results[_numHospitals-1].citiesServed[2];
			
			h=1;					//WE CAME TO THE BOTTOM,NOW WE SHOULD GO TO THE TOP OF THE FUNCTION
		}				
	}
	else if(_numHospitals==2) {					//2ND HOSPITAL
		if(results[_numHospitals].citiesServed[0]=='C') {			//CHECK IF WE REPLACE THE 3RD HOSPITAL BEFORE
			
			results[_numHospitals-1].citiesServed[0]=_cities[1];			//REPLACE CITIES
			_locations[1][0]=results[_numHospitals-1].citiesServed[0];

			results[_numHospitals-1].citiesServed[1]=_cities[5];
			_locations[1][1]=results[_numHospitals-1].citiesServed[1];
			
			h=canOfferCovidCoverage(_cities,_locations,_numHospitals-1,results);		//DECREMENT NUMHOSPITALS AND REPLACE 1ST HOSP
		}
		else {

		}
	}
	else if(_numHospitals==3) {								//3RD HOSPITAL
		results[_numHospitals-1].citiesServed[0]=_cities[2];				//REPLACE CITIES
		_locations[2][0]=results[_numHospitals-1].citiesServed[0];

		results[_numHospitals-1].citiesServed[1]=_cities[4];
		_locations[2][1]=results[_numHospitals-1].citiesServed[1];

		results[_numHospitals-1].citiesServed[2]=_cities[5];
		_locations[2][2]=results[_numHospitals-1].citiesServed[2];

		h=canOfferCovidCoverage(_cities,_locations,_numHospitals-1,results);		//DECREMENT NUMHOSPITALS AND REPLACE 2ND HOSP
	}	
	else if(_numHospitals==4) {							//4TH HOSPITAL
		results[_numHospitals-1].citiesServed[0]=_cities[0];				//REPLACE CITITES
		_locations[3][0]=results[_numHospitals-1].citiesServed[0];
		
		results[_numHospitals-1].citiesServed[1]=_cities[1];
		_locations[3][1]=results[_numHospitals-1].citiesServed[1];

		results[_numHospitals-1].citiesServed[2]=_cities[2];
		_locations[3][2]=results[_numHospitals-1].citiesServed[2];

		h=canOfferCovidCoverage(_cities,_locations,_numHospitals-1,results);		//DECREMENT NUMHOSPITALS AND REPLACE 3RD HOSP
	}
	return h;
}
void fill(cards cardss[52],int i) {				//PART 3 FILLING CARDS
	if(i%13==0) {
		cardss[i].face="Ace";
	}
	else if(i%13==1) {
		cardss[i].face="Deuce";
	}
	else if(i%13==2) {
		cardss[i].face="Three";
	}
	else if(i%13==3) {
		cardss[i].face="Four";
	}
	else if(i%13==4) {
		cardss[i].face="Five";
	}
	else if(i%13==5) {
		cardss[i].face="Six";
	}
	else if(i%13==6) {
		cardss[i].face="Seven";
	}
	else if(i%13==7) {
		cardss[i].face="Eight";
	}
	else if(i%13==8) {
		cardss[i].face="Nine";
	}
	else if(i%13==9) {
		cardss[i].face="Ten";
	}
	else if(i%13==10) {
		cardss[i].face="Jack";
	}
	else if(i%13==11) {
		cardss[i].face="Queen";
	}
	else if(i%13==12) {
		cardss[i].face="King";
	}			
}
void check(int random[52],int*i,int k) {		//CHECKING ELEMENT OF THE ARRAY IF WE GOT THE SAME ELEMENT AGAIN
	int j=0;
	while(j<=k) {
		if(*i==random[j]) {			//IF WE GOT THE SAME VALUE,REFRESH AGAIN
			*i=rand()%52;
			j=0;			
		}
		else {
			j++;
		}
	}
}
int main() {
	int s;
	int a;
	int temp;
	int r=0;
	int i;
	int k;
	int h;
	int m;
	int _numHospitals;		
	int random[52];			//ARRAY THAT HOLDS RANDOM NUMBERS FOR CARDS
	
	cards cardss[52];		//CARDS ARRAY
	cards cardss2[52];		//WE ARE GOING TO NEED THAT ARRAY BECAUSE WE MUST SHUFFLE THE ACTUAL ARRAY	
	Hosp results[4];		//RESULT ARRAY THAT HOLDS INFORMATION ABOUT HOSPITAL AND CITIES
	
	char _cities[7]="ABCDEF";	//NAME OF THE CITIES
	char _locations[4][3];

	const char*face;
	const char*suit;

	printf("\nThis is menu\n");			//MENU 
	while(1) {
		printf("\n(1)Part 1 Street-Avenue\n(2)Part 2 Covid Coverage\n(3)Part 3 Shuffle Cards\n(4)Exit\n\nYour Choice:");
		scanf(" %d",&m);
		if(m==4) {			//EXIT
			break;
		}
		else {
			switch(m) {
				case 1:
					printf("\nEnter the street number:");
					scanf("%d",&s);
					printf("street:%d\n",s);
					printf("Enter the avenue number:");
					scanf("%d",&a);
					printf("avenue:%d\n",a);
					if(s>a) {					//ORDER SMALLER TO LARGER
						temp=s;
						s=a;
						a=temp;
					}
					r=numPathsHome(s,a);
					printf("Number of optimal paths to take back home:%d\n\n",r);

					break;

				case 2:
					printf("Enter the maximum number of hospitals that can be constructed:");
					scanf("%d",&_numHospitals);	
					h=canOfferCovidCoverage(_cities,_locations,_numHospitals,results);
					if(h>0) {
						printf("\n\nYes, can offer health care to all!\n\n");
						for(i=0;i<_numHospitals;i++) {
							printf("Hospital - %d\nHospital locations: %c %c %c\n",i+1,_locations[i][0],_locations[i][1],_locations[i][2]);
						}
						printf("\n");
					}
					else {
						printf("\nNo,some cities are not covered.\n\n");						
					}
					break;

				case 3:
					for(i=0;i<4;i++) {
						if(i==0) {				//HEARTS
							for(k=0;k<13;k++) {
								cardss[k].suit="Hearts";				
								fill(cardss,k);					
							}						
						}
						else if(i==1) {			//DIAMONDS
							for(k=0;k<13;k++) {
								cardss[k+13].suit="Diamonds";
								fill(cardss,k+13);					
							}			
						}
						else if(i==2) {			//CLUBS
							for(k=0;k<13;k++) {
								cardss[k+26].suit="Clubs";
								fill(cardss,k+26);					
							}			
						}	
						else if(i==3) {			//SPADES
							for(k=0;k<13;k++) {
								cardss[k+39].suit="Spades";
								fill(cardss,k+39);					
							}			
						}								
					}
					printf("\n\nSHUFFLED:\n\n");
					srand(time(NULL));
					for(k=0;k<52;k++) {				//SHUFFLE AND CHECK IF WE GOT THE SAME VALUE
						i=rand()%52;
						check(random,&i,k);
						random[k]=i;					//COPY INTO INTEGER ARRAY
						cardss2[k].face=cardss[k].face;			//COPY ACTUAL ARRAY TO TEMP ARRAY		
						cardss2[k].suit=cardss[k].suit;
					}
					for(i=0;i<52;i++) {
						cardss[i].face=cardss2[random[i]].face;			//COPY TEMP ARRAY TO ACTUAL ARRAY
						cardss[i].suit=cardss2[random[i]].suit;
					}
					for(i=0;i<52;i+=2) {
						if(cardss[i].suit=="Diamonds") {			//DIAMONDS SLIDES COUPLE OF BLANKS WE WANT TO PRINT PROPERLY
							printf("%5s of %s\t %s of %s\n",cardss[i].face,cardss[i].suit,cardss[i+1].face,cardss[i+1].suit);
						}
						else {
							printf("%5s of %s\t\t %5s of %5s\n",cardss[i].face,cardss[i].suit,cardss[i+1].face,cardss[i+1].suit);			
						}
					}				
			}			
		}
	}
}