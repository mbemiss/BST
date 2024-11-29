/*

*/

#include <iostream> // This is a header file library that lets us work with input and output objects, such as cout.
#include <algorithm> // This is a header file library that lets us work with arrays.
#include <chrono> // This is a header file library that lets us work with time.
#include <random> // This is a header file library that lets us work with random numbers.
#include <vector> // This is a header file library that lets us work with arrays that can change in size.

using namespace std; // using standard namespace to avoid writing std:: before standard library functions
using namespace chrono; // using chrono namespace to avoid writing chrono:: before time measurement functions

class Node { // This class represents a node in a binary search tree
public: // This means that the members of the class that follow are accessible from outside the class
	int data; // This is the data stored in the node
	Node* left; // This is a pointer to the left child of the node
	Node* right; // This is a pointer to the right child of the node

	Node(int value) : data(value), left(nullptr), right(nullptr) {} // This is a constructor that initializes the node with a value
};

class BinarySearchTree { // This class represents a binary search tree
private: // This means that the members of the class that follow are not accessible from outside the class
	Node* root; // This is a pointer to the root node of the tree

	Node* insertRecursive(Node* node, int value) { // This is a private member function that inserts a value into the tree recursively
		if (node == nullptr) { // If the node is null
			return new Node(value); // Create a new node with the value
        }

		if (value < node->data) { // If the value is less than the data in the node
			node->left = insertRecursive(node->left, value); // Insert the value into the left subtree
        }
		else if (value > node->data) { // If the value is greater than the data in the node
			node->right = insertRecursive(node->right, value); // Insert the value into the right subtree
        }

		return node; // Return the node
    }

	Node* findMinNode(Node* node) { // This is a private member function that finds the node with the minimum value in the tree
		while (node->left != nullptr) { // While the left child of the node is not null
			node = node->left; // Move to the left child
        }
		return node; // Return the node
    }

	Node* removeRecursive(Node* node, int value) { // This is a private member function that removes a value from the tree recursively
		if (node == nullptr) { // If the node is null
			return nullptr; // Return null
        }

		if (value < node->data) { // If the value is less than the data in the node
			node->left = removeRecursive(node->left, value); // Remove the value from the left subtree
        }
		else if (value > node->data) { // If the value is greater than the data in the node
			node->right = removeRecursive(node->right, value); // Remove the value from the right subtree
        }
		else { // If the value is equal to the data in the node
			if (node->left == nullptr) { // If the left child of the node is null
				Node* temp = node->right; // Store the right child of the node in a temporary variable
				delete node; // Delete the node
				return temp; // Return the right child
            }
			else if (node->right == nullptr) { // If the right child of the node is null
				Node* temp = node->left; // Store the left child of the node in a temporary variable
				delete node; // Delete the node
				return temp; // Return the left child
            }

			Node* temp = findMinNode(node->right); // Find the node with the minimum value in the right subtree
			node->data = temp->data; // Copy the data of the minimum node to the current node
			node->right = removeRecursive(node->right, temp->data); // Remove the minimum node from the right subtree
        }

		return node; // Return the node
    }

	void inorderTraverseRecursive(Node* node) { // This is a private member function that traverses the tree in inorder recursively
		if (node != nullptr) { // If the node is not null
			inorderTraverseRecursive(node->left); // Traverse the left subtree
			cout << node->data << " "; // Print the data in the node
			inorderTraverseRecursive(node->right); // Traverse the right subtree
        }
    }

	Node* findRecursive(Node* node, int value) { // This is a private member function that finds a value in the tree recursively
		if (node == nullptr || node->data == value) { // If the node is null or the data in the node is equal to the value
			return node; // Return the node
        }

		if (value < node->data) { // If the value is less than the data in the node
			return findRecursive(node->left, value); // Find the value in the left subtree
        }

		return findRecursive(node->right, value); // Find the value in the right subtree
    }

public: // This means that the members of the class that follow are accessible from outside the class
	BinarySearchTree() : root(nullptr) {} // This is a constructor that initializes the tree with a null root

	void add(int value) { // This is a public member function that adds a value to the tree
		root = insertRecursive(root, value); // Insert the value into the tree recursively
    }

	void remove(int value) { // This is a public member function that removes a value from the tree
		root = removeRecursive(root, value); // Remove the value from the tree recursively
    }

	int maximum() { // This is a public member function that returns the maximum value in the tree
		if (root == nullptr) { // If the root is null
			throw runtime_error("BST is empty"); // Throw a runtime error
        }

		Node* current = root; // Create a pointer to the root node
		while (current->right != nullptr) { // While the right child of the current node is not null
			current = current->right; // Move to the right child
        } 
		return current->data; // Return the data in the current node
    }

	void inorderTraverse() { // This is a public member function that traverses the tree in inorder
		inorderTraverseRecursive(root); // Traverse the tree in inorder recursively
		cout << endl; // Print a new line
    }

	bool find(int value) { // This is a public member function that finds a value in the tree
		return findRecursive(root, value) != nullptr; // Return true if the value is found, false otherwise
    }
};

double measureAddPerformance(int numNodes) { // This is a function that measures the performance of adding nodes to a binary search tree
	BinarySearchTree bst; // Create a binary search tree
	random_device rd; // Create a random device
	mt19937 gen(rd()); // Create a Mersenne Twister pseudo-random number generator
	uniform_int_distribution<> dis(1, 1000000); // Create a uniform distribution from 1 to 1000000

	auto start = high_resolution_clock::now(); // Start the timer

	for (int i = 0; i < numNodes; ++i) { // For each node to add
		bst.add(dis(gen)); // Add a random number to the tree
    }

	auto end = high_resolution_clock::now(); // End the timer
	duration<double> diff = end - start; // Calculate the duration
	return diff.count(); // Return the duration in seconds
}

int main() { // This is the main function
	vector<int> nodeCounts = { 100, 1000, 10000, 100000 }; // This is a vector of node counts to measure performance for

	for (int count : nodeCounts) { // For each node count
		double time = measureAddPerformance(count); // Measure the performance of adding nodes
		cout << "Time to add " << count << " nodes: " << time << " seconds" << endl; // Print the time to add nodes
    }

	return 0; // Return 0 to indicate successful completion
}