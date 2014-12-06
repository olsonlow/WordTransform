/*
Jon Martin

implemetation's for Jhash.h
*/

#include "Jhash.h"

struct HashNode{	
	JBSTree IndexList;		
};


Jhash::Jhash()	
/*
	This constructor's settings of MAX_ITEMS should produce
	loading factors of about .5 if set properly.
	Loading Factor being NumItems/NumBuckets, One would thing 
	doubling the size of the array compared to items would have that 
	effect.
  */	
{						 
	MAX_ITEMS = 161521; 	 
	//MAX_ITEMS = 40993;	
	items = new HashNode[MAX_ITEMS];	
}

Jhash::Jhash(int n)
{    /*
		Allows user to set size of array if another word list is used	
	*/
	MAX_ITEMS = n;	// hopefully a prime number!
	items = new HashNode[MAX_ITEMS];	
}

Jhash::~Jhash()
{    
	delete [] items;
}

void Jhash::Add(char STR[50])
{
	//int iLoc = Hash1(STR);
	//int iLoc = Hash2(STR);
	int iLoc = BootheHash(STR);
	items[iLoc].IndexList.InsertItem(STR);	
}

void Jhash::Get(char a[50], bool& found)
{
	//int location = Hash1(a);
	//int location = Hash2(a);
	int location = BootheHash(a);
	items[location].IndexList.RetrieveItem(a, found);
}

TREENODE* Jhash::GetNode(char key[])
{	
	//int location = Hash1(key);
	//int location = Hash2(key);
	int location = BootheHash(key);
	return (items[location].IndexList.RetrieveTreeNode(key) );
}


int Jhash::Hash1(char s[100])
{//    standard string hashing routine

/*     This hashing function produces indexes from 
	   0-2344 from a dictionary of 20499 words.
	   on average, that means a linked list of 
	   10 items which produces a search and insert 
	   time of O(10) (not bad).                   */

	int iVALUE = 0;
	int length = strlen(s);
	
	for(int i=0; i < length; i++)
		iVALUE += int(s[i]);	
	
	return iVALUE % MAX_ITEMS;	
}

int Jhash::Hash2(char *s)
{	/*The first four bytes of the string treated
	  as a thirty two bit integer % MAX_SIZE */
	
	int x = 0;
	for(int i=0; i<4 && *s; i++) // LOOK AT FIRST FOUR CHARS
		x=(x<<8) |*s++; // SHIFT OVER EIGHT AND "CONCAT THE BITS"

	x = x % MAX_ITEMS;	
	return x;	
}

int Jhash::BootheHash(char *s)
{	
/*     This hash function produces index values over 
	   the whole range of the array e.g. 0-MAX_ITEMS-1 (very good!)
	   in theory, there should be very minimal collisions, 
	   producing a search and insert
	   times of O(1)...              */

	unsigned int h = 0;

	while(*s)
		h ^= (h<<5) + *s++;

	h %= MAX_ITEMS;

//	if (boothehashlow > h ) boothehashlow = h ;
//  else if (boothehashhigh < h) boothehashhigh = h;

	return h;	
	
}


void Jhash::LoadFromFile(char filename[100])
{
	ifstream SomeInFile;	
	char InString[100];
	bool bUSEWORD = true;
	
	SomeInFile.open(filename);
	if (!SomeInFile)					
	{	
		cout << "\n\nEither your FileName is incorrect, or the file is not \a\n" <<
			"in the same directory as this program.\n\n";	
		return;
	}

	SomeInFile >> InString;	
	int temp = strlen(InString);	
	for(int z=0; z<temp; z++){
		if (isupper(InString[z])){	//Filter words with CAPS
			bUSEWORD = false;			
			break;
		}
	}
	if (bUSEWORD) Add(InString);												 
										
	while (SomeInFile){
		bUSEWORD = true;
		SomeInFile >> InString;
		temp = strlen(InString);

		for(int i=0; i<temp; i++){
			if (isupper(InString[i])){
				bUSEWORD = false;				
				break;
			}
		}
		if (bUSEWORD)Add(InString);         
	} 

	SomeInFile.close();
	SomeInFile.clear();
}

void Jhash::GetSearchCounts(int &ar, int &ns)
{	// returns total node counts for hTable
	ar=0;
	ns=0;

	for (int i=0; i<MAX_ITEMS; i++){
		ar+= items[i].IndexList.ATTEMPTEDRETREIVES;
		ns+=items[i].IndexList. NODESSEARCHED; 

	}		
}
