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
		friend void read(fstream &fp,Set s[50],int &numofsets);			//FILE READ FUNCTION
		bool is_element(string &element);								//CHECK IF IT IS THE ELEMENT OF THE SET
		void reflexivity(Set& s);												//RELATED FUNCTIONS OF PROPERTIES OF RELATION
		bool symmetry();								//CHECKS THE RESPECTIVELY
		void antysymmetry();
		void transitivity(Set& s);		
		friend void determine(Set s[50],int &numofsets);				//DETERMINE THE PROPERTY OF RELATION AND WRITE TO THE FILE
		friend void erase_the_relation(Set& s,int cnt);					//ERASE THE GIVEN RELATION(INDEX) AND MOVE ALL RELATIONS TO THE LEFT
		friend void remove_ref_and_transitive(Set& s);					//TO WRITE THE HASSE DIAGRAM, WE NEED TO REMOVE REFLEXIVE AND TRANSITIVE ONES
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
void Set::reflexivity(Set& s) {
	int k;
	int cnt;
	int j=0;
	bool flag=false;
	for(k=0;k<s.numofe;k++) {
		for(cnt=0;cnt<s.numofr;cnt++) {
			if(s.r[cnt].p1==s.r[cnt].p2 && s.r[cnt].p1==s.elm[k]) {			//IF WE HAVE A (a,a) then this could be reflexive
				flag=true;
				break;
			}
		}
		if(flag==false) {													//IF WE DON'T HAVE IT, THEN ADD A RELATION WHICH IS (a,a) or (b,b) ...
			s.r[numofr].p1=s.elm[k];
			s.r[numofr].p2=s.elm[k];
			s.numofr+=1;
		}
		flag=false;
	}
}
bool Set::symmetry() {											//IF (A,B) AND (B,A) ARE FOUND BOTH
	bool x=false;
	int cnt=0;
	int k=0;
	int i=0;
	for(i=0;i<numofr;i++) {
		for(k=0;k<numofr;k++) {
			if(r[i].p1==r[i].p2) {							//IF THERE IS (a,a) (a,a) 's does not affect the symmetry
				cnt+=1;
				break;
			}
			else if(r[i].p1==r[k].p2 && r[i].p2==r[k].p1) {			//IF THERE ARE (a,b) and (b,a) then we have possibility for symmetry
				cnt+=1;
				break;
			}
			else {

			}
		}
	}
	if(cnt==numofr) {						//IF WHOLE PAIRS ARE SYMMETRIC,THEN RELATION IS SYMMETRIC
		x=true;
	}
	return x;
}
void Set::antysymmetry() {										//IF (A,B) AND (B,A) IS NOT FOUND
	int k=0;
	int i=0;
	if((this->symmetry())) {
		for(i=0;i<numofr;i++) {
			if(r[i].p1!=r[i].p2) {							//IF THIS RELATION IS SYMMETRIC, THEN WE HAVE A (a,b), then we need to erase it
				erase_the_relation(*this,i);
			}
			else {

			}
		}
	}
	else {
		for(i=0;i<numofr;i++) {
			for(k=0;k<numofr;k++) {													//IF WE HAVE (a,b) and (b,a) then we need to erase it
				if(r[i].p1==r[k].p2 && r[i].p2==r[k].p1 && r[i].p1!=r[i].p2) {
					erase_the_relation(*this,i);
				}
				else {

				} 
			}
		}
	}
}
void Set::transitivity(Set &s) {
	int j;
	int k;
	int flag=false;
	int z;
	for(k=0;k<s.numofr;k++) {
		for(j=0;j<s.numofr;j++) {
			if(s.r[k].p2==s.r[j].p1) {									//IF WE HAVE (a,b) and (b,c)
				for(z=0;z<s.numofr;z++) {
					if(s.r[k].p1==s.r[z].p1 && s.r[j].p2==s.r[z].p2) {			//IF WE HAVE (a,b) (b,c) and (a,c) it is a transitive
						flag=true;
						break;
					}
				}
				if(flag==false) {												//IF WE DON'T HAVE IT, THEN ADD (a,c)
					s.r[numofr].p1=s.r[k].p1;
					s.r[numofr].p2=s.r[j].p2;
					s.numofr+=1;
				}
				flag=false;
			}
		}
	}				
}
void erase_the_relation(Set& s,int cnt) {				//ERASE THE GIVEN PAIR AS INDEX, AND ALIGN REMAINED TO THE LEFT
	int k=0;
	for(k=cnt;k<s.numofr;k++) {
		s.r[k].p1=s.r[k+1].p1;
		s.r[k].p2=s.r[k+1].p2;
	}
	s.numofr-=1;
}
void remove_ref_and_transitive(Set& s) {
	int i;
	int k;
	int z;
	int j;
	for(i=0;i<s.numofr;i++) {
		if((s.r[i].p1)==(s.r[i].p2)) {			//THIS IS REFLEXIVE,ERASE IT
			erase_the_relation(s,i);
			i--;
		}
	}
	head:
	for(k=0;k<s.numofr;k++) {
		for(j=0;j<s.numofr;j++) {
			if(s.r[k].p2==s.r[j].p1) {
				for(z=0;z<s.numofr;z++) {
					if(s.r[k].p1==s.r[z].p1 && s.r[j].p2==s.r[z].p2) {			//THIS IS TRANSITIVE, ERASE IT
						erase_the_relation(s,z);
						goto head;
					}
				}
			}
		}
	}				
}
void determine(Set s[50],int &numofsets) {
	int i=0;
	int k=0;
	fstream fp2;
	//LOOK FOR IS THIS RELATION IS A POSET
	for(i=0;i<numofsets;i++) {					//CHECK THEM TWICE BECAUSE THERE MIGHT BE A PROBLEM
		s[i].reflexivity(s[i]);
		s[i].antysymmetry();
		s[i].transitivity(s[i]);
		s[i].reflexivity(s[i]);
		s[i].antysymmetry();
		s[i].transitivity(s[i]);					
	}	

	fp2.open("output.txt",fstream::out);												//WRITE TO THE FILE
	for(i=0;i<numofsets;i++) {
		fp2<<"n\nPOSET: ";
		for(k=0;k<s[i].numofr;k++) {
			if(k!=(s[i].numofr-1))
				fp2<<"("<<s[i].r[k].p1<<","<<s[i].r[k].p2<<"), ";
			else {
				fp2<<"("<<s[i].r[k].p1<<","<<s[i].r[k].p2<<") ";		//THE LAST ELEMENT OF THE POSET

			}
		}
		fp2<<endl;
		remove_ref_and_transitive(s[i]);			//REMOVE THE REFLEXIVE AND TRANSITIVE ONES
		for(k=0;k<s[i].numofr;k++) {
			fp2<<s[i].r[k].p1<<","<<s[i].r[k].p2<<endl;
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