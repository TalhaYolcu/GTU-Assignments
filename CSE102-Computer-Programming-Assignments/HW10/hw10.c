#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define filepath "commands.txt"
#define outfile "output.txt"

#define ddistance "Distance"
#define aangle "Angle"
#define llength "Length"
#define aarea "Area"

#define min2d 1
#define max2d 100
#define maxpolygon 20

typedef struct point {
	char name[3];
	double x;
	double y;
}point;

typedef struct line  {
	char name[3];
	point lpoints;
	point lpointe;
	double length;
}line;

typedef struct polygon {
	char name[3];
	double circumference;
	double area;
	line linepolygon[maxpolygon];
	point linepoint[20];
	int numline;
}polygon;

typedef struct entire {
	struct polygon epolygon[max2d];
	struct line eline[max2d];
	struct point epoint[max2d];
}entire;

//PROTOTİPLER YAZILACAK

void checklinep(struct entire ab[100],int j,int k,int c) {
	int lc;
	int lc2;
	if(c==0) {
		for(lc=0;lc<k;lc++) {
			for(lc2=0;lc2<j;lc2++) {
				if(strcmp(ab[lc].epoint[lc].name,ab[lc2].eline[lc2].lpoints.name)==0) {
					ab[lc2].eline[lc2].lpoints.x=ab[lc].epoint[lc].x;
					ab[lc2].eline[lc2].lpoints.y=ab[lc].epoint[lc].y;							
				}						
			}	
		}		
	}
	else {
		for(lc=0;lc<k;lc++) {
			for(lc2=0;lc2<j;lc2++) {
				if(strcmp(ab[lc].epoint[lc].name,ab[lc2].eline[lc2].lpointe.name)==0) {
					ab[lc2].eline[lc2].lpointe.x=ab[lc].epoint[lc].x;
					ab[lc2].eline[lc2].lpointe.y=ab[lc].epoint[lc].y;							
				}						
			}	
		}		
	}

}
void get(FILE*fp,int*k1,int*j1,int*p1,struct entire ab[100]) {

	int num;
	int i=0;

	int k=0;

	int j=0;

	int p=0;
	int z=0;
	int t=0;


	char fline[50];
	char fline2[20];
	char fline3[20];
	char fline4[20];
	char c;

	fscanf(fp,"%d",&num);

	for(i=0;i<num;i++) {
		fscanf(fp,"%s",fline);
		if(fline[0]=='/') {
			i-=1;
			while(1) {
				fscanf(fp,"%c",&c);
				if(c=='\n') {
					break;
				}
				else {

				}
			}
		}
		else {
			fscanf(fp,"%s",fline2);
			fscanf(fp,"%s",fline3);
			//POLYGON
			if(fline[0]=='L') {
				strcpy(ab[p].epolygon[p].linepolygon[z].name,fline);
				printf("line %d 's name:%s ",z,ab[p].epolygon[p].linepolygon[z].name);
				strcpy(ab[p].epolygon[p].linepolygon[z+1].name,fline2);
				printf("line %d 's name:%s ",z+1,ab[p].epolygon[p].linepolygon[z+1].name);
				strcpy(ab[p].epolygon[p].linepolygon[z+2].name,fline3);
				printf("line %d 's name:%s ",z+2,ab[p].epolygon[p].linepolygon[z+2].name);

				z+=3;					
				while(1) {
					fscanf(fp,"%s",fline);
					if(fline[0]=='P') {
						strcpy(ab[p].epolygon[p].name,fline);
						printf("polygon name:%s\n",ab[p].epolygon[p].name);
						break;
					}	
					else {
						strcpy(ab[p].epolygon[p].linepolygon[z].name,fline);
						printf("line %d 's name:%s ",z,ab[p].epolygon[p].linepolygon[z].name);
						z++;										
					}
					ab[p].epolygon[p].numline=z;
					z=0;
					p++;
				}
			}
			//LINE
			else if(fline3[0]=='L') {	

				strcpy(ab[j].eline[j].lpoints.name,fline);
				checklinep(ab,j,k,0);	//startp

				strcpy(ab[j].eline[j].lpointe.name,fline2);
				checklinep(ab,j,k,1);	//endp

				strcpy(ab[j].eline[j].name,fline3);
				

				printf("spoint:%s epoint:%s name:%s\n",ab[j].eline[j].lpoints.name, ab[j].eline[j].lpointe.name,ab[j].eline[j].name);

				j++;
			}

			//POLYGON
			else if(fline[0]=='P'){		
				strcpy(ab[p].epolygon[p].linepoint[t].name,fline);
				checklinep(ab,t,k);
				printf("point %d's name:%s ",t,ab[p].epolygon[p].linepoint[t].name);
				strcpy(ab[p].epolygon[p].linepoint[t+1].name,fline2);
				printf("point %d's name:%s ",t+1,ab[p].epolygon[p].linepoint[t+1].name);			
				strcpy(ab[p].epolygon[p].linepoint[t+2].name,fline3);
				printf("point %d's name:%s ",t+2,ab[p].epolygon[p].linepoint[t+2].name);			
				t+=3;
				while(1) {
					fscanf(fp,"%s",fline4);
					if(fline4[1]=='G') {
						strcpy(ab[p].epolygon[p].name,fline4);
						printf("polygon's name:%s\n",ab[p].epolygon[p].name);					
						break;
					}
					else {
						strcpy(ab[p].epolygon[p].linepoint[t].name,fline4);
						printf("point %d's name:%s ",t,ab[p].epolygon[p].linepoint[t].name);							
						t++;
					}
				}
				ab[p].epolygon[p].numline=t;
				p++;
				t=0;
			}
			//POINT
			else {
				sscanf(fline,"%lf",&(ab[k].epoint[k].x));
				sscanf(fline2,"%lf",&(ab[k].epoint[k].y));
				strcpy(ab[k].epoint[k].name,fline3);
				printf("x:%lf y:%lf name:%s\n",ab[k].epoint[k].x,ab[k].epoint[k].y,ab[k].epoint[k].name);
				k++;
			}			
		}
	}
	*k1=k;
	*j1=j;
	*p1=p;
}
void action(FILE*fp,int k,int j,int p) {
	char path[20];
	char operation[10];
	char o1[5];
	char o2[5];
	fscanf(fp,"%s",path);
	FILE*fp2;
	fp2=fopen(path,"w");
	while(1) {
		fscanf(fp2,"%s",operation);
		if(strcmp(operation,ddistance)==0) {
			fscanf(fp2,"%s",o1);
			fscanf(fp2,"%s",o2);
			if((o1[0]=='P')&&(o2[0]=='P')) {	//POINT-POINT

			}
			//POINT-LINE
			else {

			}

		}
		else if(strcmp(operation,aangle)==0) {

		}
		else if(strcmp(operation,llength)==0) {

		}
		else if(strcmp(operation,aarea)==0) {

		}
	}









	fclose(fp2);
}
void read_from_file() {

	struct entire ab[100];
	
	int k=0;
	int j=0;
	int p=0;

	int i;
	int f;
	
	char s[10];
	char c;
	FILE *fp;
	fp=fopen(filepath,"r");
	fscanf(fp,"%s",s);
	
	get(fp,&k,&j,&p,ab);

	fscanf(fp,"%s",s);
	if(s[0]=='/') {
		while(1) {
			fscanf(fp,"%c",&c);
			if(c=='\n') {
				break;
			}
			else {

			}
		}		
	}
	fscanf(fp,"%s",s);
	/*action(fp,k,j,p);*/

	fclose(fp);
}
int main() {
	read_from_file();
}
