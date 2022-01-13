#include<stdio.h>

void read_news(char buffer[500], char file_path[10], int is_Only_Title) {
	
	int i=0;
	FILE *fp;
	fp=fopen(file_path,"r");

	if(is_Only_Title==0) {			//if user want to read entire new
		while(!feof(fp)) {
			fscanf(fp,"%c",&buffer[i]);
			i++;				
		}
		i=0;
		while(buffer[i]!='\0') {
			printf("%c",buffer[i]);
			i++;
		}
	}							//if user want to read just head of news
	else {
		while(1) {
			fscanf(fp,"%c",&buffer[i]);
			printf("%c",buffer[i]);
			if(buffer[i]=='\n') {
				break;
			}
			i++;
		}
	}
	for(i=0;i<500;i++) {
		buffer[i]='\0';
	}
	fclose(fp);
}
void append_file(char* file_path,char c) {			//appending name of new's file to news_id.txt
	
	FILE *fp;
	fp=fopen(file_path,"a");
	fprintf(fp,"\n%c",c);
	fclose(fp);
}
char check_readed(char* file_path,char n) {			//helper function to check if it is readed or not
	
	char c;
	char r='0';
	FILE *fp;
	fp=fopen(file_path,"r");

	if ((fp=fopen(file_path,"r")) == NULL) {		//if it is not readed 
		r='0';
  	}
  	else {					// if any new readed before
  		while(!feof(fp)) {
			fscanf(fp,"%c",&c);		//if given new readed before
			if(c==n) {
				r=n;
				break;
			}
		}
		fclose(fp);
	}
  	return r;
}
void check_readedb(char*file_path) {				//for part p we have to check if it is readed or not
	
	int c[5];
	FILE *fp;
	fp=fopen(file_path,"r");
	int i=0;
	while(!feof(fp)) {
		fscanf(fp,"%d",&c[i]);
		printf("\n%d.new is readed",c[i]);
	}
	fclose(fp);
}
double f_func(int x) {			//for part c f function
	
	double r=x*x*x-x*x+2;
	return r;
}
double g_func(double f(int x),int a) {		//for part c g function
	
	double g=f(a)*f(a);
	return g;
}
void read_magic_numbers(char buffer_magic[10],char buffer_news[500]) {			//reading magic number
	
	int num;
	int p;
	
	double f,g,sum=0;
	
	char s;

	FILE *fp;
	fp=fopen(buffer_magic,"r");

	while(!feof(fp)) {
		fscanf(fp,"%c",&s);
		printf("%c",s);
		if(s=='#') {				// if there is a magic number
			fscanf(fp,"%d",&num);		//scan integer
			printf("%d",num);			//also print the number
			g=g_func(f_func,num);	//send into g function in the f funciton
			sum=sum+g;				//sum them
		}
		else {

		}
	}
	fclose(fp);
	if(buffer_magic[5]=='1') {			//if user chose 1st new
			p=1;
	}
	else if(buffer_magic[5]=='2') {  // if user chose 2nd new
			p=2;
	}
	else if(buffer_magic[5]=='3') {		//3rd new
			p=3;
	}
	else if(buffer_magic[5]=='4') {		//4th new
			p=4;
	}
		
	printf("\n");

	switch(p) {			//depend on the new name print the results
		case 1:
		printf("\nNumber of test performed:%.2lf",sum);
		break;

		case 2:
		printf("\nNumber of sick people:%.2lf",sum);
		break;

		case 3:
		printf("\nNumber of deaths:%.2lf",sum);
		break;

		case 4:
		printf("\nExpected number of sick people:%.2lf",sum);
		break;
	}
	printf("\n");
}

int allnews(int b,char allnews[20]) {	//printing all news helper func
	int a;

	int i=0;
	
	FILE *fp;
	fp=fopen(allnews,"r");
	while(i!=b) {
		fscanf(fp,"%d",&a);
		i++;
	}
	fclose(fp);
	return a;
}

void menu() {
	
	char o;				//variable for case a-b-c
	char con='y',con3;	//variables for continue
	char buffer[500];	//buffer for news
	char buffer2[500];	//another buffer for news
	char fp1[11]="news/1.txt";	//filepaths
	char fp2[11]="news/2.txt";
	char fp3[11]="news/3.txt";
	char fp4[11]="news/4.txt";
	char*app="readed_news_id.txt";
	char allnew[20]="all_news_id.txt";

	int is_Only_title;	//variable for is only title
	int n;				//variable for number of new that will be read
	int con2;			//if new is readed before,it will determine
	int r1,r2,r3,r4;	//checking if it is readed or not
	int d;				//variable in the part c for the which new will be encrypted

	printf("\n\n**********Daily Press**********\n\n");

	printf("Today's news are listed for you:\n\n");
	printf("Title of %d.news:",allnews(1,allnew));
	read_news(buffer,fp1,1);
	printf("Title of %d.news:",allnews(2,allnew));
	read_news(buffer,fp2,1);
	printf("Title of %d.news:",allnews(3,allnew));
	read_news(buffer,fp3,1);
	printf("Title of %d.news:",allnews(4,allnew));
	read_news(buffer,fp4,1);
	
	
	while(con=='y') {

		if(con3=='n') {
			break;
		}
		printf("\nWhat do you want to do?\n");
		printf("a.Read a new\nb.List the readed news\nc.Get decrypted indormation from the news\n");
		scanf("\n%c",&o);

		switch(o) {

			case 'a':
			
			printf("\nWhich news do you want to read?:\n");
			scanf("%d",&n);
			
			printf("\n");
			switch(n) {

				case 1: //1st new
				r1=check_readed(app,'1');		//checking if it is readed or not 
				if(r1!='0') {
					printf("\nThis new is readed,do you want to read again? Yes(1)/No(0)\n");
					scanf("%d",&con2);
					if(con2==1) {
						printf("\n(0)To read entire news  (1)To read only title of news\n");
						scanf("%d",&is_Only_title);						
						read_news(buffer,fp1,is_Only_title);	//reading news
					}
					else {
				
					}
				}
				else {
					printf("\n(0)To read entire news  (1)To read only title of news\n");	//if it is not readed before, program will be here
					scanf("%d",&is_Only_title);
					read_news(buffer,fp1,is_Only_title);
					append_file(app,'1');	//it will append readed news name
				}
				break;

				case 2:		//2nd new
				r2=check_readed(app,'2');				//same operations
				if(r2!='0') {	
					printf("\nThis new is readed,do you want to read again? Yes(1)/No(0)\n");
					scanf("%d",&con2);
					if(con2==1) {
						printf("\n(0)To read entire news  (1)To read only title of news\n");
						scanf("%d",&is_Only_title);	
						read_news(buffer,fp2,is_Only_title);
					}
					else {
				
					}
				}
				else {
					printf("\n(0)To read entire news  (1)To read only title of news\n");
					scanf("%d",&is_Only_title);
					read_news(buffer,fp2,is_Only_title);
					append_file(app,'2');
				}
				break;

				case 3:			//same operations
				r3=check_readed(app,'3');
				if(r3!='0') {
					printf("\nThis new is readed,do you want to read again? Yes(1)/No(0)\n");
					scanf("%d",&con2);
					if(con2==1) {
						printf("\n(0)To read entire news  (1)To read only title of news\n");
						scanf("%d",&is_Only_title);						
						read_news(buffer,fp3,is_Only_title);
					}
					else {
				
					}
				}
				else {
					printf("\n(0)To read entire news  (1)To read only title of news\n");
					scanf("%d",&is_Only_title);
					read_news(buffer,fp3,is_Only_title);
					append_file(app,'3');
				}
				break;

				case 4:				//same operaions
				r4=check_readed(app,'4');
				if(r4!='0') {
					printf("\nThis new is readed,do you want to read again? Yes(1)/No(0)\n");
					scanf("%d",&con2);
					if(con2==1) {
						printf("\n(0)To read entire news  (1)To read only title of news\n");
						scanf("%d",&is_Only_title);						
						read_news(buffer,fp4,is_Only_title);
					}
					else {
				
					}
				}
				else {
					printf("\n(0)To read entire news  (1)To read only title of news\n");
					scanf("%d",&is_Only_title);
					read_news(buffer,fp4,is_Only_title);
					append_file(app,'4');
				}
				break;

			}
			printf("\n");
			break;

			case 'b':					//when user chooses case b
			check_readedb(app);
			printf("\n");
			break;

			case 'c':				//case c
			printf("\nWhich news would you like to decrypt?:\n");
			scanf("%d",&d);

			switch(d) {

				case 1:					//sending file path and buffer
				read_magic_numbers(fp1,buffer2);
				break;

				case 2:
				read_magic_numbers(fp2,buffer2);
				break;

				case 3:
				read_magic_numbers(fp3,buffer2);
				break;

				case 4:
				read_magic_numbers(fp4,buffer2);
				break;
			}
			break;
		}
		printf("\n");
		printf("Do you want to continue? Yes(y)/No(n)\n");			//asking continue
		scanf("\n%c",&con);
	}
	printf("\nGood Bye!\n");
}
int main() {

	menu();
}