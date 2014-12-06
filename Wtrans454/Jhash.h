/* 
Jon Martin


Hash Table of Binary trees: Provides a very fast way to implement
chain style hashing.
*/

#include <string.h>
#include <iostream>
#include <fstream>
#include "JBSTree.h"
#include <cctype>  // for checking CAPS

#ifndef JHASH_H
#define JHASH_H

using namespace std;

struct HashNode;

class Jhash  
{
public:	
	
	Jhash();
	Jhash(int n);
	virtual ~Jhash();	
	int Hash1(char s[100]);  // adds int val of all chars in string%Max_Size
	int Hash2(char *s);		 // first four chars (one byte each) % MAX_SIZE
	int BootheHash(char *s); // XOR Style hash provides hash values from 0 to MAXSIZE-1

	TREENODE* GetNode(char key[100]); // returns pointer to TREENODE in hTable
	void Get(char a[50], bool& found);  // returns string from node (less useful)
	void Add(char STR[50]);				// adds TREENODE to hTable
	void LoadFromFile(char filename[100]);
	void GetSearchCounts(int& , int& ); // Bucket searches counts from trees	
private:	
	int LENGTH;
	int MAX_ITEMS;
	HashNode *items;
};	

#endif 

