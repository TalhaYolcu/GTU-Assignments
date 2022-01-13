#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define maxentry 1000000

typedef struct my_list{
	int data;
	struct my_list *next;
}l_list;

typedef struct differences{
	int n1;
	int n2;
}diff;


//PART1 FUNCTIONS PROTOTYPES
int *read_array(char *filename,int*r,int*r2);
l_list *read_linkedlist(char *filename,l_list*ln,int*lr);
float *findminandmax(int*arr,int e,float*m);
float stdop(int*arr,int e,float mean);
float * stats_array(int*arr,int e);
float *findminmaxlist(l_list*ln,int lr);
float stdoplist(l_list*ln,int lr,float mean);
float * stats_linkedlist(l_list*ln,int lr);


//PART2 FUNCTIONS PROTOTYPES
int *fillarray(int*p2,int*n);
l_list *fillinkedlist(int i);
diff *analayze(int*p2,l_list*l2,int i,int*j);
//------------------------------------------------
//PART 1 FUNCTIONS
int *read_array(char *filename,int*r,int*r2) {
	FILE*fp;
	fp=fopen(filename,"r");
	int i=0;
	int*n;
	n=r;
	char c;							//FOR COMMA
	for(i=0;i<maxentry+1;i++) {			//FOR MAX ENTRY
		if(feof(fp)) {					//IF WE ARE AT THE END OF FILE ARRAY'S LAST ELEMENT SHOULD BE -1
			*(r+i)=-1;
			break;
		}
		r=(int*)realloc(r,sizeof(int)*(i+1));			//DYNAMIC ALLOCATION FOR NEW ENTRY

		fscanf(fp,"%d%c",&(*(r+i)),&c);
	}
	*r2=i;												//CALCULATE HOW MANY ENTRY IS TAKEN
	fclose(fp);
	return r;
}

l_list *read_linkedlist(char *filename,l_list*ln,int*lr) {
	FILE*fp;
	l_list *a=ln;								//RETURN POINTER
	char c;
	int i=0;
	fp=fopen(filename,"r");
	fscanf(fp,"%d%c",&(ln->data),&c);
	for(i=0;i<maxentry;i++) {
		if(feof(fp)) {								//IF WE ARE AT THE END OF THE LINE,THEN THE LAST LINKED LIST POINTER POINTS TO NOTHING
			ln->next=NULL;	
			break;
		}
		ln->next=(l_list*)malloc(sizeof(l_list));			//REALLOCATION FOR NEW ENTRY
		fscanf(fp,"%d",&(ln->next->data));
		ln=ln->next;										//MOVE LINKED LIST POINTER
		fscanf(fp,"%c",&c);;
	}
	fclose(fp);
	*lr=i;													//HOW MANY ENTRY WE GET
	return a;	
}
float *findminandmax(int*arr,int e,float*m) {
	int i;
	int ext=*arr;						//MIN VALUE
	int ext2=*arr;						//MAX VALUE
	float sum=0;
	for(i=0;i<e;i++) {					//TURN NUMBER OF ENTRY THAT ARRAY HAS
		sum=sum+arr[i];					//SUM THEM TO CALCULATE MEAN
		if(ext>arr[i]) {				//FINDING MIN
			ext=arr[i];
		}
		else if(ext2<arr[i]) {			//FINDING MAX
			ext2=arr[i];
		}
	}
	m[0]=ext;
	m[1]=ext2;
	m[2]=sum/e;							//CALCULATE MEAN
	return m;							//RETURN ARRAY
}
float stdop(int*arr,int e,float mean) {
	int i;
	float sum=0;
	float sum2=0;
	float sum3=0;
	for(i=0;i<e;i++) {
		sum2=arr[i]-mean;				//NECESSARY THINGS TO CALCULATE STANDART DEVIATON
		sum3=sum2*sum2;
		sum=sum+sum3;
	}
	sum=sum/(e-1);
	return (float)sqrt(sum);
}
float * stats_array(int*arr,int e) {
	float*stat=(float*)calloc(4,sizeof(float));
	stat=findminandmax(arr,e,stat);				//NOW,STAT ARRAY HAS MIN,MAX AND MEAN VALUES
	stat[3]=stdop(arr,e,stat[2]);				//CALCULATE STANDART DEVIATON
	return stat;								//RETURN ARRAY
}
float *findminmaxlist(l_list*ln,int lr) {
	float*x=(float*)calloc(4,sizeof(float)); 		
	int ext=ln->data;			
	int ext2=ln->data;
	float sum=0;
	while((ln->next)!=NULL) {
		sum+=ln->data;						//SUM THEM TO CALCULATE MEAN
		if(ln->data<ext) {
			ext=ln->data;					//CALCULATE MIN VALUE
		}
		else if(ln->data>ext2) {			//CALCULATE MAX VALUE
			ext2=ln->data;
		}		
		ln=ln->next;						//MOVE LINKED LIST POINTER
	}
	x[0]=ext;					//MIN
	x[1]=ext2;					//MAX
	x[2]=sum/lr;				//MEAN
	return x;					//RETURN ARRAY
}
float stdoplist(l_list*ln,int lr,float mean) {
	float sum=0;
	float sum2=0;
	float sum3=0;
	while((ln->next)!=NULL) {
		sum2=(ln->data)-mean;			//NECESSARY CALCULATIONS TO FIND STANDART DEVIATION
		sum3=sum2*sum2;
		sum=sum+sum3;
		ln=ln->next;					//MOVE LINKED LIST POINTER
	}
	sum=sum/(lr-1);
	return (float)sqrt(sum);
}

float * stats_linkedlist(l_list*ln,int lr) {
	float*h=(float*)calloc(4,sizeof(float));		
	h=findminmaxlist(ln,lr);			//NOW,THIS FLOAT ARRAY HAS LINKED LIST'S MAX,MIN AND MEAN VALUES
	h[3]=stdoplist(ln,lr,h[2]);			//IT HAS STANDART DEVIATON
	return h;							//RETURN FLOAT ARRAY
}
int *fillarray(int*p2,int*n) {
	int i=0;
	char c[100];
	printf("\nEnter numbers for heap array\nIf you want to quit,press q\n");
	printf("Enter numbers:\n");
	scanf("%s",c);										//TAKE AS A CHARACTER AND GET THE INTEGER VALUE,IF USER ENTERS Q FUNCTION WILL BE STOP AND RETURN THE ARRAY
	if(c[0]=='q') {		
		printf("There is no input");
	}
	else {
		sscanf(c,"%d",&p2[i]);
		i++;
		while(1) {
			scanf("%s",c);
			if(c[0]=='q') {
				break;
			}		
			else {
				p2=(int*)realloc(p2,sizeof(int)*(i+1));
				sscanf(c,"%d",&p2[i]);
				i++;			
			}
		}
	}
	*n=i;
	printf("\n");
	return p2;	
}

l_list *fillinkedlist(int i) {
	l_list*h;
	l_list*ln2=(l_list*)malloc(sizeof(l_list));
	h=ln2;
	int cnt=0;
	char c[100];
	printf("\nEnter numbers for linked list\nIf you want to quit,press q\n");
	printf("Enter numbers:\n");

	for(cnt=0;cnt<i;cnt++) {						//TURN THE LOOP SUCH THAT NUMBER OF ELEMENT
		scanf("%d",&(ln2->data));
		ln2->next=(l_list*)malloc(sizeof(l_list));
		ln2=ln2->next;		
	}
	ln2->next=NULL;
	printf("\n");
	return h;			
}

diff *analayze(int*p2,l_list*l2,int i,int*j) {
	int c=0;
	diff*array=(diff*)malloc(sizeof(diff));
	for(c=0;c<i;c++) {				
		if(p2[c]!=l2->data) {										//IF THEY ARE DIFFERENT FROM EACH OTHER, THEN FILL THE STRUCT ARRAY
			array=(diff*)realloc(array,sizeof(diff)*(*j+1));	
			array[*j].n1=p2[c];
			array[*j].n2=l2->data;
			*j+=1;
		}
		l2=l2->next;
	}
	return array;
}




int main() {
	int*r=(int*)malloc(sizeof(int));
	int*p2=(int*)malloc(sizeof(int));
	int r2=0;
	int r3=0;
	int lr=0;
	int i=0;
	int cnt=0; 
	int j=0;
	int cnt2=0;	

	double t=0,t2=0;
	double lt=0,lt2=0;

	float*extremes;
	float*extremes2;
	
	char*filename="list.txt";
	
	l_list*ln=(l_list*)malloc(sizeof(l_list));
	l_list*l2;
	
	diff *array;					//PART 2 ARRAY

	clock_t str,end;					//START AND END VARIABLES
	clock_t str2,end2;
	clock_t lstr,lend;
	clock_t lstr2,lend2;
	

	for(i=0;i<4;i++) {						//CALCULATE TIME AND BYTE FOR READ AND STAT ARRAY
		str=clock();
		r=read_array(filename,r,&r2);
		end=clock();
		
		str2=clock();
		extremes=stats_array(r,r2-1);
		end2=clock();
		
		t=t+(double)((end-str))/CLOCKS_PER_SEC;
		t2=t+(double)((end2-str2))/CLOCKS_PER_SEC;				
	}
	t=t/4;
	t2=t2/4;

	printf("\n\nFor read array\n%ld bytes are used",r2*(sizeof(int)));
	printf("\nminimum value:%.1f",extremes[0]);
	printf("\nmax value:%.1f",extremes[1]);
	printf("\nmean value:%.1f",extremes[2]);
	printf("\nstandart deviation:%.1f",extremes[3]);
	printf("\nAverage time for this read array function:%lf seconds",t);
	printf("\nAverage time for this stats array function:%lf seconds",t2);

	printf("\n--------------------------\n--------------------------\n");

	for(i=0;i<4;i++) {											//CALCULATE START AND END TIME AND BYTES FOR READ AND STAT LINKED LIST
		lstr=clock();
		ln=read_linkedlist(filename,ln,&lr);
		lend=clock();
		
		lstr2=clock();
		extremes2=stats_linkedlist(ln,lr);
		lend2=clock();

		lt=lt+(double)((lend-lstr))/CLOCKS_PER_SEC;
		lt2=lt2+(double)((lend2-lstr2))/CLOCKS_PER_SEC;		
	}
	lt=lt/4;
	lt2=lt2/4;

	printf("\nFor read linked list\n%ld bytes are used",lr*(sizeof(l_list)));
	printf("\nminimum value:%.1f",extremes2[0]);
	printf("\nmax value:%.1f",extremes2[1]);
	printf("\nmean value:%.1f",extremes2[2]);
	printf("\nstandart deviation:%.1f\n",extremes2[3]);
	printf("\nAverage time for this linked list function:%lf seconds",lt);
	printf("\nAverage time for this stats linked list function:%lf seconds",lt2);	
	printf("\n--------------------------\n--------------------------\n");

	free(r);
	free(extremes);
	free(ln);
	free(extremes2);

	//FILL ARRAY
	i=0;
	p2=fillarray(p2,&i);
	printf("\nArray has %d elements\n\n",i);
	
	l2=fillinkedlist(i);
	printf("\nLinked list has %d elements\n\n",i);
	
	array=analayze(p2,l2,i,&j);
	printf("\n\n");
	for(i=0;i<j;i++) {
		printf("(%d).different elements of the array:%d linked list:%d\n",i+1,array[i].n1,array[i].n2);
	}
	free(p2);
	free(l2);
	free(array);

}

