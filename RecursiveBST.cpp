//Recursive Binary Search Tree 

#include "stdafx.h"
#include <iostream>

struct Node
{
	int data;
	Node *left;
	Node *right;
};

Node *getNewNode(int data);
Node *insert(Node*, int);
void inOrderTraversal(Node*);
bool find(Node*, int);
Node *findMax(Node*);
Node *deleteNumber(Node*, int);


int main()
{
	Node* root = NULL;
	root = insert(root, 15);
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 3);
	root = insert(root, 50);
	root = insert(root, 29);

  //print numberss from tree in order
	inOrderTraversal(root);
	std::cout << std::endl;

  //check to see if number is in tree
	if (find(root, 100))
		std::cout << "The number was found" << std::endl;
	else
		std::cout << "The number was not found" << std::endl;
  
  //Print minimum number in tree
	Node *minNumber;
	minNumber = findMin(root);
	std::cout << "Minimum Number is: " << minNumber->data << std::endl;

  //Delete number from tree
	deleteNumber(root, 29);
	inOrderTraversal(root);
	std::cout << std::endl;

    return 0;
}

//Create new node throught built in pointer and dynamically allocating memory
Node *getNewNode(int data)
{
	Node *newNode = new Node();
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

//Insert number in tree; calls getNewNode function to dynamically allocate memory
Node *insert(Node *root, int data)
{
	if (root == NULL)
		root = getNewNode(data);
	else if (data <= root->data)
		root->left = insert(root->left, data);   
	else
		root->right = insert(root->right, data);

	return root;
}

//Traverse through tree and print in order
void inOrderTraversal(Node *root)
{
	if (root)
	{
		inOrderTraversal(root->left);
		std::cout << root->data << " ";
		inOrderTraversal(root->right);
	}
}

//Check to see if number is in tree
bool find(Node *root, int data)
{
	if (root == NULL)
		return false;
	else if (root->data == data)
		return true;
	else if (data <= root->data)
		return find(root->left, data);
	else
		return find(root->right, data);
}

//Find max number; will be used in deleteNumber function
Node *findMax(Node *root) 
{
	if (root == NULL)
		return NULL;
	else if (root->right == NULL)
		return root;
	else
		return findMax(root->right);
}

//Delete a number from tree; calls findMax 
Node *deleteNumber(Node *root, int data)
{
	Node *temp;
	if (root == NULL)
		std::cout << "Element is not in the tree." << std::endl;
	else if (data < root->data)
		root->left = deleteNumber(root->left, data);
	else if (data > root->data)
		root->right = deleteNumber(root->right, data);
    //We have found the element
	else 
	{
    //2 children; replace number that is going to be deleted with largest from left subtree
		if (root->left && root->right) 
		{
			temp = findMax(root->left);
			root->data = temp->data;		
			root->left = deleteNumber(root->left, root->data);
		}
    //1 child or no child
		else
		{
			temp = root;
			if (root->left == NULL && root->right == NULL)
			{
				delete root;
				return NULL;
			}
			if (root->left == NULL)
				root = root->right;
			if (root->right == NULL)
				root = root->left;
			delete temp;
			temp = NULL; 
		}

	}
	return root;
}
