#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define filepath "Video_Games.txt"			//filepath
#define gamename 100						//game name length
#define genrename 20						//genrename length
#define platformname 20						//platformname length
#define rowsize 200							//row length
#define game 2000							//number of game
#define genre 12							//number of genre
#define platform 10							//number of platform

void operation();
void menu();
float seperatestring(char row[rowsize],char gmn[gamename],char gnrn[genrename],char pltfrm[platformname],float*date,float*sale1,float*sale2,float sale3,float*usrscore);
int rowlength(char row[rowsize]);
int gp(char str1[genre][genrename],char str2[genrename]);
void printsth(char array[][genrename],int a);
int throughyear(char gamenames[game][gamename],float info[game][7],int year,int us);
int isthere(char gamenames[game][gamename],char str[gamename]);
float averagescore(float info[game][7]);
void salecompare(int i,float info[game][7]);
int findhowmany(int a,int b,float info[game][7]);

void menu() {			//printing menu 
	int i;
	for(i=0;i<9;i++) {
		printf("\n");
		switch(i) {
			case 0:
			printf("%d: List of the Genres",i);
			break;

			case 1:
			printf("%d: List of the Platforms",i);
			break;

			case 2:
			printf("%d: List of the Games Through the Years",i);
			break;

			case 3:
			printf("%d: All Informations of a Single Game",i);
			break;
			
			case 4:
			printf("%d: Average of the User Scores",i);
			break;

			case 5:
			printf("%d: Geogrophical Informations of a Single Game",i);
			break;
			
			case 6:
			printf("%d: Frequence of the Genres",i);
			break;

			case 7:
			printf("%d: Frequence of the Platforms",i);
			break;

			case 8:
			printf("%d: Exit\n",i);
		}
	}
}
int rowlength(char row[rowsize]) {			//finding length of string like strlen
	int i=0;
	while(row[i]!='\0') {
		i++;
	}
	return i;
}
float seperatestring(char row[rowsize],char gmn[gamename],char gnrn[genrename],char pltfrm[platformname],float*date,float*sale1,float*sale2,float sale3,float*usrscore) {
		//This function allow me to take string from file and other strings that will be used,some variables that will be used.
	int i;
	int rowl;
	char ds[genrename];			//date string
	char ds2[genrename];		//nasale
	char ds3[genrename];		//eusale
	char ds4[genrename];		//globalsale
	char ds5[genrename];		//userscore
	char global[genrename];		//global sale i need that too
	rowl=rowlength(row);
	for(i=0;i<rowl;i++) {
		if(row[i]==',') {
			row[i]=' ';			//clarifying the array from commas
		}		
	}
	sscanf(row,"%s%s%s%s%s%s%s%s",gmn,gnrn,pltfrm,ds,ds2,ds3,global,ds4);		//getting needed strings from main string
	sscanf(ds,"%f",date);
	sscanf(ds2,"%f",sale1);
	sscanf(ds3,"%f",sale2);
	sscanf(ds4,"%f",usrscore);
	if(global[0]=='n') {			//if this is not avaliable
		sale3=-1.1;					
	}
	else {
		sscanf(global,"%f",&sale3);
	}
	return sale3;
}
int gp(char str1[][genrename],char str2[genrename]) {				//checking if we got the same genre or platform
	int i;
	int r=0;
	for(i=0;i<genre;i++) {
		if(strcmp(str1[i],str2)==0) {
			r=i;
			break;
		}
	}
	return r;
}
void printsth(char array[][genrename],int a) {			//printing genres or platforms
	int i;
	printf("\n");
	for(i=0;i<a;i++) {
		printf("%s\n",array[i]);
	}
}
int throughyear(char gamenames[game][gamename],float info[game][7],int year,int us) {			
	int i=0;
	int ch=0;
	printf("\n");
	if(us==0) {						//UNTIL
		for(i=0;i<game;i++) {
			if(info[i][2]<year) {
				printf("%s\n",gamenames[i]);
				ch=1;
			}
		}	
	}		
	else {					//SINCE
		for(i=0;i<game;i++) {
			if(info[i][2]>=year) {
				printf("%s\n",gamenames[i]);
				ch=1;
			}
		}		
	}
	return ch;
}
int isthere(char gamenames[game][gamename],char str[gamename]) {			//CHECKING IS ENTERED GAME NAME VALID
	int i;
	int r=-1;
	for(i=0;i<game;i++) {
		if(strcmp(gamenames[i],str)==0) {
			r=i;
			break;
		}
	}
	return r;
}
float averagescore(float info[game][7]) {		//FINDING AVERAGE
	int i;
	float sum=0;
	float av;
	for(i=0;i<game;i++) {
		sum=sum+info[i][6];
	}
	av=sum/2000;
	return av;
}
void salecompare(int i,float info[game][7]) {					//COMPARING THE NA AND EU SALES
	if(info[i][3]>info[i][4]) {
		printf("\nThis game was more popular in North America\n");
	}
	else if(info[i][3]<info[i][4]) {
		printf("\nThis game was more popular in Europe\n");
	}
}
int findhowmany(int a,int b,float info[game][7]) {			//FINDING NUMBER OF GENRE OR PLATFORM
	int i;
	int cnt=0;
	for(i=0;i<game;i++) {
		if(a==(int)info[i][b]) {
			cnt++;
		}
	}
	return cnt;
}
void operation() {
	char gamenames[game][gamename];						//IT HOLDS NAMES OF GAMES
	char genrenames[genre][genrename];					//IT HOLDS GENRE NAMES OF GAMES
	char platformnames[platform][platformname];			//IT HOLDS PLATFORM NAMES OF GAMES
	char row[rowsize];									//STRING FOR FILE
	char gmn[gamename];									//RETURNED STRING FROM seperatestring FUNCTION
	char gnrn[genrename];								//RETURNED STRING FROM seperatestring FUNCTION
	char pltfrm[platformname];							//RETURNED STRING FROM seperatestring FUNCTION
	char global[genrename]="not_available";
	char n3[gamename];									//IN THE MENU U GOT THE GAME NAME WITH THIS STRING
	char empty[game];									//EMPTY STRING FOR FIRST ROW OF THE FILE

	int i=0;									//COUNTER FOR GAMES			
	int k=0;									//COUNTER FOR GENRE
	int j=0;									//COUNTER FOR PLATFORM
	int gnrcnt;									//COUNTER FOR GENRE
	int pltfrmcnt;								//COUNTER FOR PLATFORM
	int flag1=1;								//FLAGS FOR GENRES AND PLATFORMS
	int flag2=1;
	int p;										//PLATFORM VALUE
	int g;										//GENRE VALUE
	int opt=-1;
	int r1;
	int year;
	int us;										//UNTIL/SINCE
	int ch;
	int fhm;									//FIND HOW MANY
	int len1;
	int len2;
	int done[3];								//I USED THAT ARRAY FOR FIRST GAME,I TRIED TO GET INFOS OF THE FIRST GAME CORRECTLY

	float date;						
	float done2[4];								//I USED THAT ARRAY FOR FIRST GAME,I TRIED TO GET INFOS OF THE FIRST GAME CORRECTLY
	float info[game][7];						//INFO ARRAY FOR HOLDING THE GENRE INDEX,PLATFORM INDEX,DATE,NASALE,EUSALE,GLOBALSALE,USERSCORE
	float sale1;								//NASALE
	float sale2;								//EUSALE
	float sale3;								//GLOBALSALE
	float usrscore;								//USERSCORE
	float av;									//AVERAGE VALUE FOR USERSCORES
	float f=0.0;								//I USED THAT FOR FIRST GAME,I TRIED TO GET INFOS OF THE FIRST GAME CORRECTLY

	FILE *fp;
	fp=fopen(filepath,"r");	
	fscanf(fp,"%s\n",empty);					//FIRST ROW
	if(fp==NULL) {
		printf("Something went wrong");				//IF FILE CANNOT OPENED
	}
	else {
		while(!feof(fp)) {
			fscanf(fp,"%s",row);		
			flag1=flag2=1;
			gnrcnt=0;
			pltfrmcnt=0;
			sale3=seperatestring(row,gmn,gnrn,pltfrm,&date,&sale1,&sale2,sale3,&usrscore);				//GETTING INFOS FROM FUNCTION
			sprintf(gamenames[i],"%s",gmn);						//HOLDING GAME GENRE PLATROM NAMES
			sprintf(genrenames[k],"%s",gnrn);
			sprintf(platformnames[j],"%s",pltfrm);
			
			for(gnrcnt=0;gnrcnt<k;gnrcnt++) {					//CHECK IF WE GOT THE SAME GENRE
				if(strcmp(genrenames[gnrcnt],genrenames[k])==0) {
					flag1=0;
					break;
				}						
			}	
			for(pltfrmcnt=0;pltfrmcnt<j;pltfrmcnt++) {			//CHECK IF WE GOT THE PLATFORM
				if(strcmp(platformnames[pltfrmcnt],platformnames[j])==0) {
					flag2=0;
					break;
				}
			}
			g=gp(genrenames,gnrn);					//(FOR FLOAT INFO ARRAY)GENRE AND PLATFORM :INDEX OF GENRE AND PLATFORM ARRAY 
			p=gp(platformnames,pltfrm);
			if(i==0) {				//FIRST GAME (CORRECTLY)
				done[0]=g;
				done[1]=p;
				done[2]=(int)date;
				info[i][3]=sale1;
				info[i][4]=sale2;
				info[i][5]=sale3;
				info[i][6]=usrscore;
			}
			else {
				info[i][0]=(double)g;
				info[i][1]=(double)p;
				info[i][2]=date;
				info[i][3]=sale1;
				info[i][4]=sale2;
				info[i][5]=sale3;
				info[i][6]=usrscore;	
			}
			i++;
			if(flag1>0) {				//DEPEND ON THE GENRE AND PLATFORM INCREMENT COUNTERS
				k++;
			}
			if(flag2>0) {
				j++;
			}							
		}
		fclose(fp);	
		if(done[0]==f) {				//FIRST GAME(CORRECTLY)
			info[0][0]=f;
		}
		if(done[1]==f) {
			info[0][1]=f;
		}
		if(done[2]==1985) {
			info[0][2]=done[2];
		}
		while(1) {
			k=0;
			menu();
			printf("\nPlease select an operation:\n");
			scanf("%d",&opt);
			if(opt==8) {
				printf("\nTerminated\n\n");				//TERMINATE
				break;
			}
			else {
				while((opt<0)||(opt>8)) {							//IF INPUT IS INVALID
					printf("\nTRY AGAIN(ERROR:INVALID INPUT)\n");
					menu();
					printf("\nPlease select an operation:\n");
					scanf("%d",&opt);
				}
				switch(opt) {
					case 0:					//PRINT GENRE
					printsth(genrenames,genre);				
					break;

					case 1:						//PRINT PLATFORM
					printsth(platformnames,platform);
					break;

					case 2:
					printf("\nEnter a year:\n");			//GAME THROUGH YEAR
					scanf("%d",&year);
					if((year<1984)||(year>2020)) {
						while(1) {
							printf("\nTRY AGAIN(ERROR:INVALID YEAR\n");			//INVALID YEAR
							printf("\nEnter a year:\n");
							scanf("%d",&year);
							if(1984<year<2020) {
								break;
							}								
						}
					}
					printf("\nUntil (0) or Since (1) %d:",year);			//INVALID NUMBER FOR SINCE AND UNTIL
					scanf("%d",&us);
					if((us<0)||(us>1)) {
						while(1) {
							printf("\nTRY AGAIN(ERROR:INVALID NUMBER\n");	//INVALID NUMBER FOR SINCE AND UNTIL
							printf("\nUntil (0) or Since (1) %d:",year);
							scanf("%d",&us);
							if((us==0)||(us==1)) {
								break;
							}						
						}
					}
					ch=throughyear(gamenames,info,year,us);
					while(ch!=1) {
						printf("\nTRY AGAIN\n\n");
						printf("\nEnter a year:\n");
						scanf("%d",&year);
						printf("\nUntil (0) or Since (1) %d:",year);
						scanf("%d",&us);
						ch=throughyear(gamenames,info,year,us);												
					}
					break;

					case 3:
					printf("Please enter the name of the game:\n");				//ALL INFO FOR GAME
					scanf("%s",n3);
					ch=isthere(gamenames,n3);
					if(ch<0) {
						while(1) {
							printf("\nTRY AGIN INVALID WORD\n");			
							scanf("%s",n3);
							ch=isthere(gamenames,n3);
							if(ch>=0) {
								break;
							}							
						}
					}
					len1=strlen(n3);
					len2=strlen(gamenames[ch]);
					while(len1!=len2) {
						printf("\nTRY AGIN INVALID WORD\n");
						scanf("%s",n3);
						ch=isthere(gamenames,n3);
						len1=strlen(n3);
						len2=strlen(gamenames[ch]);
					}
					printf("\nName:\t\t%s\n",gamenames[ch]);
					printf("Genre:\t\t%s\n",genrenames[(int)info[ch][0]]);
					printf("Platform:\t%s\n",platformnames[(int)info[ch][1]]);
					printf("Year:\t\t%d\n",(int)info[ch][2]);
					printf("Sales In NA:\t%f\n",info[ch][3]);
					printf("Sales IN EU:\t%f\n",info[ch][4]);
					if(info[ch][5]<0) {
						printf("Total Sales\t%s\n",global);			//NOT AVAILABLE
					}	
					else {
						printf("Total Sales\t%f\n",info[ch][5]);						
					}
					printf("User Score:\t%f\n",info[ch][6]);
					break;

					case 4:
					av=averagescore(info);			//FINDING AVERAGE SCORE
					printf("\n\nAverage:%f\n\n",av);
					break;

					case 5:
					printf("\n\nPlease enter the name of the game:\n");
					scanf("%s",n3);	
					for(i=0;i<game;i++) {
						if(strcmp(gamenames[i],n3)==0) {
							break;
						}	
					}				
					while(i>(game-1)) {
						printf("\n\nINVALID Please enter the name of the game:\n");
						scanf("%s",n3);	
						for(i=1;i<game;i++) {
							if(strcmp(gamenames[i],n3)==0) {
								break;
							}	
						}				
					}
					salecompare(i,info);			//COMPARING SALE OF GAME
					break;

					case 6:
					for(i=0;i<genre;i++) {
						fhm=findhowmany(i,0,info);
						if(i==6) {
							printf("\n%s: \t\t %d",genrenames[i],fhm);							
						}
						else {
							printf("\n%s: \t %d",genrenames[i],fhm);								
						}
					}
					break;

					case 7:
					for(i=0;i<platform;i++) {
						fhm=findhowmany(i,1,info);
						printf("\n%s: \t\t %d",platformnames[i],fhm);
					}
					break;
				}
				printf("\n");
			}
		}
	}
}
int main() {
	operation();
}