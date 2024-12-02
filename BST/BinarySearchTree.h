/*
This header file defines the structure and interface for a Binary Search Tree (BST) data structure. It declares a Node struct to represent individual 
nodes in the tree and a BinarySearchTree class that encapsulates the tree's functionality. The BinarySearchTree class provides public methods for common 
operations such as insertion, removal, and traversal, while also including private helper functions for recursive implementations and tree management.
*/

#pragma once // This is a header guard. It prevents the header file from being included more than once in the same file.
#include <iostream> // This is a header file library that lets us work with input and output objects, such as cout.
#include <string> // This is a header file library that lets us work with strings.
#include <chrono> // This is a header file library that lets us work with time.

using namespace std; // using standard namespace to avoid writing std:: before standard library functions
using namespace chrono; // using chrono namespace to avoid writing chrono:: before time measurement functions

struct Node { // This struct represents a node in a binary search tree.
	string data; // This string represents the data stored in the node.
	Node* left = nullptr; // This pointer points to the left child of the node.
	Node* right = nullptr; // This pointer points to the right child of the node.
};

class BinarySearchTree { // This class represents a binary search tree.
private: // This section contains private members of the class.
	Node* root; // This pointer points to the root node of the binary search tree.

	Node* insertRecursive(Node* node, string word); // This function inserts a node with the given word into the binary search tree.
	Node* removeRecursive(Node* node, string word); // This function removes a node with the given word from the binary search tree.
	Node* findMinNode(Node* node); // This function finds the node with the minimum value in the binary search tree.
	Node* findRecursive(Node* node, string word) const; // This function finds a node with the given word in the binary search tree.
	void inorderTraverseRecursive(Node* node, string& result) const; // This function traverses the binary search tree in inorder and stores the result in a string.
	void preorderTraverseRecursive(Node* node, string& result) const; // This function traverses the binary search tree in preorder and stores the result in a string.
	void postorderTraverseRecursive(Node* node, string& result) const; // This function traverses the binary search tree in postorder and stores the result in a string.
	void deleteTree(Node* node); // This function deletes the binary search tree.

public: // This section contains public members of the class.
	BinarySearchTree(); // This is the default constructor for the binary search tree.
	BinarySearchTree(string word); // This is a constructor that initializes the binary search tree with a single node containing the given word.
	BinarySearchTree(const BinarySearchTree& rhs); // This is the copy constructor for the binary search tree.
	~BinarySearchTree(); // This is the destructor for the binary search tree.

	void insert(string word); // This function inserts a node with the given word into the binary search tree.
	bool remove(string word); // This function removes a node with the given word from the binary search tree.
	bool exists(string word) const; // This function checks if a node with the given word exists in the binary search tree.
	string inorder() const; // This function returns the inorder traversal of the binary search tree as a string.
	string preorder() const; // This function returns the preorder traversal of the binary search tree as a string.
	string postorder() const; // This function returns the postorder traversal of the binary search tree as a string.

	bool operator==(const BinarySearchTree& other) const; // This function checks if two binary search trees are equal.
	bool operator!=(const BinarySearchTree& other) const; // This function checks if two binary search trees are not equal.

	friend istream& operator>>(istream& in, BinarySearchTree& tree); // This function overloads the input stream operator to read a binary search tree from a stream.
	friend ostream& operator<<(ostream& out, const BinarySearchTree& tree); // This function overloads the output stream operator to write a binary search tree to a stream.
};