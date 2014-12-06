/*
Jon Martin

This is a queue of pointers to TREENODE.
This is a basic circular queue structure which acts as a helper 
to the main() function of the program in order to solve
for the shortest path. 

I wrote this one last year and modified it for this
program by changing the node structure to hold TREENODES
*/
 


#ifndef JCSQUE_H
#define JCSQUE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "JBSTree.h"

typedef TREENODE *QUENODE;

class JCSQue
{
public:	
	
    JCSQue();    
	JCSQue(int n);
	JCSQue(const JCSQue& anotherQue);	// Copy constructor	
	~JCSQue();
    void MakeEmpty();    
    bool IsFull() const;    
    bool IsEmpty() const;
	void enqueue(QUENODE a);
	void dequeue(QUENODE& a);
	void operator =(const JCSQue& originalQue);

private:	
	int MAX_ITEMS;
    int front, rear;    
	QUENODE *items;  // array of pointers to TREENODE 
};

#endif







