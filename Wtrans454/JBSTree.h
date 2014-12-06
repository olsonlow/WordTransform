/*
Jon Martin

Jon's BinaryStringTree:
Recursive and Dynamic Data Stucture for Strings:


I modified this thing to return pointers to tree nodes
which makes it much more useful for the main() program.

Direct access to the nodes is key for the fastest solution

A well shaped short and wide tree will produce great 
insert and retrieve times O(log2N). Worst case O(n) 
for long and thin trees.

*/



#ifndef JBSTREE_H
#define JBSTREE_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct TreeNode{
	char NodeString[100];
	TreeNode* left;
	TreeNode* right;	
	TreeNode *ParentNode;    	// mark when iterating through a solution								
	int Depth;					
	bool Solution;
	bool UsedUp;			// set when no solution found..no words to morph to	
}TREENODE;					 

class JBSTree
{
public:
	
	JBSTree(); 
    JBSTree(const JBSTree& originalTree); // copy constructor
	~JBSTree(); 
	void PrintToScreen();
	void PrintTreeToFile(ofstream& outFile);	
	void DeleteItem(char a[100]);
	void InsertItem(char a[100]);
	void RetrieveItem(char item[100], bool& found);
	TREENODE* RetrieveTreeNode(char key[100]);
	void LoadFromFile(char filename[100], int& stringcounter);
	void operator =(const JBSTree& originalTree);
    int NumberOfNodes();
    int ATTEMPTEDRETREIVES, NODESSEARCHED;
	
private:
	int CountNodes(TreeNode* tree);
	void CopyTree(TreeNode*& copy, const TreeNode* originalTree);	
	void Destroy(TreeNode*& tree);
	void Print2(TreeNode* tree);
	void Print(TreeNode* tree, ofstream& outFile);
	void Delete(TreeNode*& tree, char a[100]);
	void GetPredecessor(TreeNode* tree, char a[100]);
	void DeleteNode(TreeNode*& tree);
	void Insert(TreeNode*& tree, char a[100]);
	void Retrieve(TreeNode* tree, char a[100], bool& found);
	TREENODE* RetrieveNode(TreeNode* tree, char key[100]);
	TreeNode* root;	
};

#endif
