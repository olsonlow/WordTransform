/*

Jon Martin
Word Morph: Find the shortest path.

This program will find the shortest path from one word to another
such as comic->flair using a non-recursive morphing function
which is much faster than the recursive method.
The recursive method works fine, may be more elegant and
easy to code, BUT, the speed gained using this 
method demonstrates this algorithm is superior to that of recursion.

AN example of a one-morph is dog->dig.

multiple morphing:

Morph dog to top:
dog->dig->->dip->tip->top

Extra Files Used:

words (dictionary)
JHash.h & .cpp
JBSTree.h & .cpp
JCSQue.h & .cpp




*/


#include <string.h>
#include <iostream>
#include "Jhash.h"
#include "JCSQue.h"
#include <fstream>
#include <stdio.h>
#include <cstdlib>


using namespace std;

void MorphAWord(TREENODE *tn);
bool OneMorph(const char *STRINGONE, const char *STRINGTWO);


JCSQue MorphedWordQue; 
JCSQue SolutionQue;
Jhash MyHash;			
char *ENDWORD;
int GoodFindCount, FailedFindCount; // for calculating actual loading factors

int main(int argc , char *argv[] )
{	
  
	if (argc != 3){ 	// For those who failed to enter commands,		
		cout << "\n\nYou did not enter your arguments correctly.\n\n";
		cout << "You should enter the following separated by spaces:\n\n";
		cout << "\"Start Word...\"End Word\"\n\nStart Over Please.\nExiting Program....\n\n";
		return 1;	
	}
	else if (strlen(argv[argc-2]) != strlen(argv[argc-1])){ // if not same length
		cout << "\n\nPlease enter words of equal length.\n";
		cout << "Exiting Program....\n\n";
		return 2;

	}
	else if(strcmp(argv[argc-1],argv[argc-2])==0){ // if strings the same
		cout << "\n\nNo need to Morph. The words you entered, \"" << argv[argc-1] <<
			"\" and \"" << argv[argc-2] << "\" are the same.\n\n";
		cout << "ending MorphWords.\n\n";
		return 3;
	}


	// load up the dictionary
	char *words = "words";
	MyHash.LoadFromFile(words);
	ENDWORD = argv[argc-1]; // for capturing the solution later
	TREENODE *TN;
	GoodFindCount=0;
	FailedFindCount=0;
	
	TN = MyHash.GetNode(argv[argc-1]);

	if (!TN){
		
		FailedFindCount++;
		cout << "Sorry No End word \"" << argv[argc-1] << "\" in dictionary." << endl
			<< "\nEnding MorphWords." << endl;
		return 3;
	}	
	
	TREENODE *HEADNODE = NULL;
	TN = MyHash.GetNode(argv[argc-2]);
	if (TN){
		GoodFindCount++;
	
		TN->Depth = 0;		
		TN->ParentNode = HEADNODE;		
		TN->UsedUp=true;
	}
	else{
		cout << "Sorry No Start word \"" << argv[argc-2] << "\" in dictionary." << endl
		<< "\nEnding MorphWords" << endl;
		return 4;
	}	
	
	MorphAWord(TN);
	TREENODE *D;

	while(!MorphedWordQue.IsEmpty()){ 
		// pop nodes off of MorphedWordQue and morph them
		// MorphAWord() enques found word onto the backside
		// of this queue. if ENDWORD matched argv[argc-1] in
		// MorfAWord(), TREENODE->Solution would be true here,
		// therefore, we are done.
		
		MorphedWordQue.dequeue(D); 
		if (D->Solution) { // You won
			SolutionQue.enqueue(D);
			break;
		}			
		if (!D->UsedUp)	MorphAWord(D); // don't morph a morphed word
	}

	
	if (SolutionQue.IsEmpty()){		
	  cout <<"\nSORRY, CAN NOT MORPH \"" << argv[argc-2] << "\" to \"" << argv[argc-1]
	  << "\".\n\n";		
	}
	else{
		while(!SolutionQue.IsEmpty()){

			int iDEPTHTRACKER = 0;	
			SolutionQue.dequeue(D);
			
			cout << "\nYou successfully morphed from \"" << argv[argc-2] <<
			        "\" to \"" << argv[argc-1] << "\"." << endl << endl;		
			cout<< "Morphing Depth:   " << D->Depth << endl;
			cout<< "Word List Length: " << D->Depth+1 << endl;
		       

			TREENODE *temp[100];

			while(D){
				// Traversal backward here, so put Nodes in
				// an array				
				temp[iDEPTHTRACKER] = D;
				D = D->ParentNode;
				iDEPTHTRACKER++;
			}			
			cout << endl; // Now print forwards:
			for(int z=iDEPTHTRACKER-1; z>=0; z--)
			  cout << temp[z]->NodeString << endl;
			  cout << endl << endl << "End Morph Program." << endl << endl;
		}		
	}
 return 0;
}


void MorphAWord(TREENODE *tn)
{	
	int len = strlen(tn->NodeString);
	int DEPTH = tn->Depth + 1;
	TREENODE *TempNode = NULL;
	char temp[100];
	tn->UsedUp=true; // assume solved	
	

	/*
		Brute Force approach to morphing words. Change all letters 25 times
		each for all letters in word. Each time a letter is change, look for
		word in dictionary.
	*/
	for (int i=0; i<len; i++){
		strcpy(temp, tn->NodeString); // replace string for fresh start
		
		for (int x= 97; x<123; x++){  // now go through eash letter
		
			if (tn->NodeString[i] == char(x)) continue; // skip if letter is start letter

			temp[i] = char(x); // assign letter to slot			
			
			TempNode = MyHash.GetNode(temp); // look for word

			if(!TempNode) FailedFindCount++;
			
			else/*(TempNode)*/{ // if found
				GoodFindCount++;	
				if (TempNode->UsedUp) continue; // don't use a USED word

				if (TempNode->Depth==tn->Depth && tn->Depth!=0) continue;
				// filter morphing accross equal depths.
				
				TempNode->ParentNode = tn;  // link 'em up
				TempNode->Depth = DEPTH;	// assign depth of morph
				
				if (strcmp(TempNode->NodeString, ENDWORD)==0)
					TempNode->Solution=true; // mark solved			
				
				MorphedWordQue.enqueue(TempNode);  // put onto que being unloaded in main()											
			}			
			TempNode = NULL;			
		}	
	}		
}



bool OneMorph(const char *STRINGONE, const char *STRINGTWO)
{   // helper function that determines if a word is one morph away from
    // another.  I wrote this to post process solved lists that contained
	// unnessesary (lateral) morphs. This function is not used in this program,
	// I left the function here just for fun.

   int iDIFFERENCE = 0;
   if (strlen(STRINGONE) != strlen(STRINGTWO)) return false;

   while(iDIFFERENCE < 2 && *STRINGONE && *STRINGTWO){ //while true or NOT NULL
	   if (*STRINGONE++ != *STRINGTWO++)  // iterate and compare values
			iDIFFERENCE++;				  // count differences      
   }   
   return (iDIFFERENCE == 1); // return true if 1 char different 
}









