#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

class Relation;
class Set;
class Relation {
	public:
		friend class Set;								//friend classes Set and Relation
		string p1;										//pairs for Relation
		string p2;
		friend void read(fstream &fp,Set s[50]);		//FILE READ function
};
class Set {
	public:
		friend class Relation;
		string elm[50];									//holds the elements of the set
		bool ref;										//bool val for reflexive,symmetric,antisymmetric,transitive
		bool sym;
		bool ansym;
		bool tran;
		Relation r[50];									//holds the relations of the set
		int numofr;										//holds the number of relations of sets
		int numofe;										//holds the number of elements of the set										
		int whr;										//no situation for reflexive
		string whs1;									//gives info about symmetry-non symmetry
		string whs2;									
		int antysym1;									//give info about antisymmetry
		int antysym2;
		string wht1;									//give info about transitivity
		string wht2;
		string wht3;									
		friend void read(fstream &fp,Set s[50],int &numofsets);			//FILE READ FUNCTION
		bool is_element(string &element);								//CHECK IF IT IS THE ELEMENT OF THE SET
		bool reflexivity();												//RELATED FUNCTIONS OF PROPERTIES OF RELATION
		bool symmetry();
		bool antysymmetry();
		bool transitivity(string p1,string p2,int x,string p1_1);		
		friend void determine(Set s[50],int &numofsets);				//DETERMINE THE PROPERTY OF RELATION AND WRITE TO THE FILE
};
int main() {
	fstream fp;							
	fp.open("input.txt");
	Set s[50];								//ARRAY FOR SET
	int numofsets=0; 						
	read(fp,s,numofsets);					//READ THE FILE
	determine(s,numofsets);					//DETERMINE THE PROPERTIES
	fp.close();								
}
bool Set::reflexivity() {
	bool x=true;
	int i=0;
	int j=0;
	bool array[numofe];
	for(i=0;i<numofe;i++) {
		for(j=0;j<numofr;j++) {
			if(elm[i]==r[j].p1 && elm[i]==r[j].p2) {				//IF PAIRS ARE THE SAME
				array[i]=true;
				break;
			}
		}
	}
	for(i=0;i<numofe;i++) {
		if(array[i]==false) {
			x=false;
			this->whr=i;							//FOR PRINT
			break;			
		}
	}
	return x;
}
bool Set::symmetry() {											//IF (A,B) AND (B,A) ARE FOUND BOTH
	bool x=false;
	int cnt=0;
	int k=0;
	int i=0;
	bool array[numofr];
	for(i=0;i<numofr;i++) {
		for(k=0;k<numofr;k++) {
			if(r[i].p1==r[i].p2) {
				cnt+=1;
				break;
			}
			else if(r[i].p1==r[k].p2 && r[i].p2==r[k].p1) {
				antysym1=i;
				antysym2=k;
				cnt+=1;
				break;
			}
			else {
				whs1=r[i].p1;								//FOR PRINT
				whs2=r[i].p2;
			}
		}
	}
	if(cnt==numofr) {
		x=true;
	}
	return x;
}
bool Set::antysymmetry() {										//IF (A,B) AND (B,A) IS NOT FOUND
	bool x=true;
	int cnt=0;
	int k=0;
	int i=0;
	if((this->symmetry())) {
		for(i=0;i<numofr;i++) {
			if(r[i].p1!=r[i].p2) {
				x=false;
				break;
			}
			else {

			}
		}
	}
	else {
		for(i=0;i<numofr;i++) {
			for(k=0;k<numofr;k++) {
				if(r[i].p1==r[k].p2 && r[i].p2==r[k].p1 && r[i].p1!=r[i].p2) {
					x=false;
					break;
				}
				else {
					whs1=r[i].p1;
					whs2=r[i].p2;
				} 
			}
		}
	}
	return x;
}
bool Set::transitivity(string p1,string p2,int x,string p1_1) {				//RECURSIVELY (A,B) (B,C) FOUND WITH (A,C)
	int i=0;
	int k=0;
	int j=0;
	int cnt=0;
	bool ret=false;
	bool arr[50];
	for(i=0;i<50;i++) {
		arr[i]=false;
	}
	if(x==2) {
		for(i=0;i<numofr;i++) {
			if(r[i].p1==p1_1 && r[i].p2==p2) {
				ret=true;
				break;
			}
		}
		if(ret==false) {
			wht1=p1_1;
			wht2=p1;
			wht3=p2;
		}
		if(ret==true) {
			wht1=p1_1;
			wht2=p1;
			wht3=p2;			
		}				
	}
	else {
		for(i=0;i<numofr;i++) {
			if(r[i].p1==p2) {
				ret=transitivity(r[i].p1,r[i].p2,x+1,p1_1);
				arr[cnt]=ret;
				cnt+=1;
			}
		}
		if(cnt==0) {
			ret=true;
		}
		else {
			for(i=0;i<cnt;i++) {
				if(arr[i]==false) {
					ret=false;
					break;
				}
				else {
					ret=true;
				}
			}					
		}

	}
	return ret;
}
void determine(Set s[50],int &numofsets) {
	int i=0;
	int k=0;
	int j=0;
	int cnt=0;
	bool flag=true;
	bool x[50][50];
	for(i=0;i<50;i++) {						//FILL THE ARRAY WITH FALSES
		for(k=0;k<50;k++) {
			x[i][j]=false;
		}
	}
	for(i=0;i<numofsets;i++) {				//ASSIGNS THE BOOL VALUES OF PROPERTIES(REFLEXIVE,SYMMETRY,ANTİSYMMETRY,TRANSITIVE)
		if(s[i].reflexivity()) {
			s[i].ref=true;
		}
		if(s[i].symmetry()) {
			s[i].sym=true;
		}
		if(s[i].antysymmetry()) {
			s[i].ansym=true;
		}
		for(j=0;j<s[i].numofr;j++) {
			if(s[i].transitivity(s[i].r[j].p1,s[i].r[j].p2,1,s[i].r[j].p1)) {
				x[i][j]=true;			//HOLD FOR EVERY TRANSITIVE POSSIBILITY
			}				
		}
		for(j=0;j<s[i].numofr;j++) {		//IF THERE IS A NOT TRANSITIVE POSSIBILITY
			if(x[i][j]==false) {
				flag=false;
				break;
			}
		}
		if(flag==true) {			//THIS RELATION IS TRANSITIVE
			s[i].tran=true;
		}
		else if(flag==false){
			s[i].tran=false;
		}
		flag=true;			
	}
	fstream fp2;
	fp2.open("output.txt",fstream::out);												//WRITE TO THE FILE
	for(i=0;i<numofsets;i++) {
		fp2<<'n'<<endl;
		for(k=0;k<s[i].numofr;k++) {
			fp2<<'('<<s[i].r[k].p1<<','<<s[i].r[k].p2<<')';
		}	
		fp2<<endl;
		fp2<<"Reflexive: ";
		if(s[i].ref) {
			fp2<<"Yes , all elements are presented"<<endl;
		}
		else {
			fp2<<"No , ("<<s[i].elm[s[i].whr]<<","<<s[i].elm[s[i].whr]<<") is not found"<<endl;
		}
		fp2<<"Symmetric: ";
		if(s[i].sym) {
			fp2<<"Yes , ("<<s[i].r[1].p1<<","<<s[i].r[1].p2<<")"<<" is found whereas "<<"("<<s[i].r[1].p2<<","<<s[i].r[1].p1<<")"<<" and every elements obeys the rule" <<endl;
		}
		else {
			fp2<<"No , ("<<s[i].whs1<<","<<s[i].whs2<<")"<<" is found whereas "<<"("<<s[i].whs2<<","<<s[i].whs1<<")"<<" is not found"<<endl;
		}
		fp2<<"Antisymmetric: ";
		if(s[i].ansym) {
			fp2<<"Yes ," <<endl;
		}
		else {
			fp2<<"No , ("<<s[i].r[s[i].antysym1].p1<<","<<s[i].r[s[i].antysym1].p2<<")"<<" is found with ("<<s[i].r[s[i].antysym1].p2<<","<<s[i].r[s[i].antysym1].p1<<")"<<endl;
		}
		fp2<<"Transitive: ";
		if(s[i].tran) {
			fp2<<"Yes , ("<<s[i].wht1<<","<<s[i].wht2<<")"<<" and ("<<s[i].wht2<<","<<s[i].wht3<<") is found with ("<<s[i].wht1<<","<<s[i].wht3<<")"<<endl;
		}
		else {
			fp2<<"No , ("<<s[i].wht1<<","<<s[i].wht2<<")"<<" and ("<<s[i].wht2<<","<<s[i].wht3<<") is found but ("<<s[i].wht1<<","<<s[i].wht3<<") is not found"<< endl;
		}
	}
	fp2.close();
}
bool Set::is_element(string &element) {			//CHECKS THE ELEMENTS IF ITS IN THE SET
	int i;
	bool x=false;
	for(i=0;i<this->numofe;i++) {
		if(element.compare(this->elm[i])==0) {
			x=true;
			break;
		}
	}
	return x;
}
void read(fstream &fp,Set s[50],int &numofsets) {
	int i=0;
	int k=0;
	int cnt=0;
	int mycnt=0;
	int j=0;
	string temp;
	stringstream mys;
	string empty="";
	while(!fp.eof()) {								
		fp>>s[i].numofr;								//GETS THE NUMBER OF RELATIONS
		if(s[i].numofr<=0) {							//IF IT IS NEWLINE
			break;
		}
		mys<<empty;										//STRING STREAM ISSUES
		mys>>temp;
		getline(fp,temp);								//GET THE NEW LINE '\n'
		getline(fp,temp);								//GET THE ELEMENTS LINE
		for(k=0;k<temp.size();) {			
			s[i].elm[j]=temp[k];						//GET THE ELEMENTS OF THE SET
			j+=1;	
			k+=2;	
		}
		s[i].numofe=j;									//RECORD THE NUMBER OF ELEMENTS
		for(cnt=0;cnt<s[i].numofr;cnt++) {				//GETS THE EVERY RELATION
			mys<<empty;
			mys>>temp;
			getline(fp,temp);
			s[i].r[cnt].p1=temp[0];			//GET THE PAIRS
			s[i].r[cnt].p2=temp[2];						
			if(s[i].is_element(s[i].r[cnt].p1) && s[i].is_element(s[i].r[cnt].p2)) {	

			}
			else {
				cout<<"PROBLEM!!! THIS IS NOT A RELATION"<<endl;			//NO MATCHING ELEMENT
				break;
				i--;				
			}			
		}
		i++;
		j=0;
		k=0;
		mys.str("");
	}
	numofsets=i;//RECORD HOW MANY SET IN THE FILE
}