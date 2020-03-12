//This script will find the consensus sequence (at 60% threshold) given a multiple sequence alignment
//input: multiple sequence alignment file
//output: consensus sequence
//To run just provide the input (aligned file) file.
#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
using namespace std; 
  
// function to calculate modified Hamming distance i.e., exact match score
double hammingDist(char *str1, char *str2) 
{ 
   double count = 0.0;double percent=0.0;double countsim=0.0;double weighted_score=0.0;
   for (int i=0;i<strlen(str1);i++){
	if(str1[i]==str2[i]){
		if (str1[i]!='-' | str1[i]!='X'){
			 count++; 
		}
   	 } 
	}
   countsim=strlen(str1)-count;
//   cout<<countsim<<" countsim "<<strlen(str1)<<endl;
   weighted_score=((countsim/double(strlen(str1)))*double(countsim));
   percent= round((countsim/double(strlen(str1)))*100); 
   return weighted_score; 
//   return countsim;
}

//this will check if the positions has been already enountered
int dupcheck(vector<int>tvec, int name){
      int present=0;
      for (int a=0;a<tvec.size();a++){
      		if (tvec[a]==name){
			present=1;
		}
      }
      return present;
}
vector < vector<char> >seq1;
vector<string>seq2;
int main(int argc, char* argv[]) 
{ 
	string line;
	ifstream myReadFile;
	myReadFile.open(argv[1]);
	map<string,int>freq;
	vector<int>index;
	int count=0,gcount=0;
	if (myReadFile.is_open()){
	  string tpair;
	  while (!myReadFile.eof()) {
		getline(myReadFile,line);
		char A[line.length()];
		strcpy(A,line.c_str());
		if (!line.empty()){
			if(line[0]!='>'){
				for (int j=0;j<line.size();j++){
					tpair=A[j];
					tpair.append("#"+to_string(count));
					freq[tpair]+=1;
					if (dupcheck(index,count)==0){
						index.push_back(count);
					}
					count+=1;
				}
			}else if (line[0]=='>') {
				count=0;
				gcount+=1;
			}		
		}

	   }
	}/*
	map<string,int>::iterator itr1;
	for (itr1=freq.begin();itr1!=freq.end();itr1++){
		cout<<itr1->first<<" and value "<< itr1->second<<endl;
	}*/
//	vector<int>index;
	map<string,int>::iterator itr;
	cout<<">Consensus_sequence"<<endl; 
	for (int b=0;b<index.size();b++){
		double tempval=0.0,temppercent=0.0;
		string tempkey;
		int resindex;
		for (itr=freq.begin();itr!=freq.end();itr++){
			resindex=stoi(itr->first.substr(itr->first.find('#')+1));
			if (index[b]==resindex){
				//the if statement below checks for 60% threshold. Change it if needed different percent threshold
				if ((itr->second/double(gcount))>0.6 && (itr->second/double(gcount))>temppercent){
					tempval=itr->second;
					temppercent=itr->second/double(gcount);
					tempkey=itr->first.substr(0,itr->first.find('#'));
				}
			}
		}
		if (tempval==0.0){
			tempkey='X';
		}
		cout<<tempkey;
	}
	cout<<endl;	
}
