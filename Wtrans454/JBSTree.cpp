/*
Jon Martin

*/
// Jon's binary tree
// implementation for JBSTree, a Recursive Binary Search Tree
#include "JBSTree.h"
#include <string.h>
#include <iostream>
#include <fstream>


JBSTree::JBSTree()
{	
	ATTEMPTEDRETREIVES=0;
	NODESSEARCHED=0;
    root = NULL;	
}

JBSTree::JBSTree(const JBSTree& originalTree) 	
{	// copy constuctor
	// Copy's tree pointed to
	// by originalTree into self
	CopyTree(root, originalTree.root);
}

void JBSTree::CopyTree(TreeNode*& copy, const TreeNode* originalTree)
{	// copy is the root of a tree that is a dup
	// of tree pointed to by originalTree
	if(originalTree == NULL) copy = NULL;
	else{
		copy = new TreeNode;		
		strcpy(copy->NodeString, originalTree->NodeString);
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);		
	}
}

JBSTree::~JBSTree()
{    
	Destroy(root);
}

void JBSTree::Destroy(TreeNode*& tree)
{
	if(tree){
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

void JBSTree::operator =(const JBSTree& originalTree)
{
	if(&originalTree == this) return; // ignore if assigning self to self	
	Destroy(root);					  // Deallocate existing nodes	
	CopyTree(root, originalTree.root);	
}

int JBSTree::NumberOfNodes()
{
	return CountNodes(root);
}

void JBSTree::LoadFromFile(char filename[100], int& stringcounter)
{
	ifstream SomeInFile;
	char InString[100];
	stringcounter = 0;	
	
	SomeInFile.open(filename);
	if (!SomeInFile)					
	{	
		cout << "\n\nEither your FileName is incorrect, or the file is not \a\n" <<
			"in the same directory as this program.\n\n";	
		return;
	}
	while(SomeInFile){
		SomeInFile >> InString;				
		stringcounter++;
		InsertItem(InString);		
	}
	SomeInFile.close();
	SomeInFile.clear();
}

int JBSTree::CountNodes(TreeNode* tree)
{	
	if (tree == NULL)
		return 0;
	else return CountNodes(tree->left) + 
		CountNodes(tree->right) + 1;
}

// If returns NULL, then not found
TREENODE* JBSTree::RetrieveTreeNode(char key[])
{
	//ATTEMPTEDRETREIVES++; // for testing call counts
	return RetrieveNode(root, key);

}

TREENODE* JBSTree::RetrieveNode(TreeNode *tree, char key[])
{
	//NODESSEARCHED++;  // bucket counts 
	if (tree == NULL)
		return NULL;
	else if(strcmp(key, tree->NodeString) < 0)  // 1st lt than 2nd
		return RetrieveNode(tree->left, key);	
	else if (strcmp(key, tree->NodeString) > 0)  // 1st gt than 2nd
		return RetrieveNode(tree->right, key);
	else
		return tree;
}


void JBSTree::RetrieveItem(char item[100], bool& found )
{
	Retrieve(root, item, found);
}


void JBSTree::Retrieve(TreeNode* tree, char a[100], bool& found)
{
	if (tree == NULL)
		found = false;
	else if(strcmp(a, tree->NodeString) < 0)  // 1st less than 2nd)
		Retrieve(tree->left, a, found);	
	else if (strcmp(a, tree->NodeString) > 0)  // 1st less than 2nd)
		Retrieve(tree->right, a, found);
	else {
		strcpy(a, tree->NodeString);  // found it
		found = true;
	}
}

void JBSTree::InsertItem(char a[100])
{
	Insert(root,a);
}

void JBSTree::Insert(TreeNode*& tree, char a[100])
{	
	if (tree == NULL){ // insertion place found
		tree = new TreeNode;
		tree->right=NULL;
		tree->left=NULL;
		strcpy(tree->NodeString, a);
		tree->UsedUp=false;
		tree->ParentNode=NULL;
		tree->Solution=false;
		tree->Depth = 0;		
	}
	else if (strcmp(a, tree->NodeString) < 0) // insert left subtree
		Insert(tree->left, a);
	else
		Insert(tree->right, a); // insert right subtree
}

void JBSTree::DeleteItem(char a[100])
{
	Delete(root,a);
}

void JBSTree::DeleteNode(TreeNode*& tree)
{
	char b[100];
	TreeNode* temp;
	temp = tree;

	if (tree->left == NULL){
		tree = tree->right;
		delete temp;		
	}
	else if (tree->right == NULL){
		tree = tree->left;
		delete temp;	
	}	
	else{
		GetPredecessor(tree->left, b);
		strcpy(tree->NodeString, b);		
		Delete(tree->left, b);   // delete predecessor node
	}
}

void JBSTree::Delete(TreeNode*& tree, char a[100])
{
	if (strcmp(a, tree->NodeString) < 0)		// look left
		Delete(tree->left, a);  
	else if (strcmp(a, tree->NodeString) > 0)	// look right
		Delete(tree->right, a); 
	else
		DeleteNode(tree);						// not found..
}

void JBSTree::GetPredecessor(TreeNode* tree, char a[100])
{	// sets a to the string member of the right most node in tree
	while(tree->right)
		tree = tree->right;
	strcpy(tree->NodeString, a);	
}

void JBSTree::Print(TreeNode* tree, ofstream &outFile)
{	// inorder traversal (ascending key order)
	// preorder
	if(tree){
		Print(tree->left, outFile);
		outFile << tree->NodeString << endl;
		Print(tree->right, outFile);
	}
}

void JBSTree::PrintTreeToFile(ofstream &outFile)
{ 
	Print(root,outFile);
}

void JBSTree::PrintToScreen()
{
	Print2(root);
}

void JBSTree::Print2(TreeNode* tree)
{
	if(tree){
		Print2(tree->left);
		cout << tree->NodeString <<endl;
		Print2(tree->right);
	}
}















