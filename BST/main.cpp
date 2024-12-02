/*
This program implements a Binary Search Tree (BST) data structure in C++, providing functions for adding, removing, finding, and traversing nodes. 
It also includes a performance evaluation component that measures the time taken to add varying numbers of random nodes to the BST, allowing for analysis 
of the data structure's efficiency as it scales. The implementation demonstrates key BST operations and serves as a foundation for comparing its performance 
characteristics with other data structures.
*/

#include <iostream> // This is a header file library that lets us work with input and output objects, such as cout.
#include <cassert> // This is a header file library that lets us use the assert function to test our code.
#include <algorithm> // This is a header file library that lets us work with arrays.
#include <chrono> // This is a header file library that lets us work with time.
#include <random> // This is a header file library that lets us work with random numbers.
#include <vector> // This is a header file library that lets us work with arrays that can change in size.
#include <iomanip> // This is a header file library that lets us work with parametric manipulators.
#include <fstream> // This is a header file library that lets us work with files.
#include <filesystem> // This is a header file library that lets us work with file systems.
#include "BinarySearchTree.h" // This is a header file that contains the implementation of a binary search tree.

using namespace std; // using standard namespace to avoid writing std:: before standard library functions
using namespace chrono; // using chrono namespace to avoid writing chrono:: before time measurement functions

void readFromFile(BinarySearchTree& bst, const string& filename) { // This function reads data from a file and inserts it into the binary search tree.
	ifstream file(filename); // Open the file for reading.
	string line; // Create a string to store each line of the file.

	if (file.is_open()) { // Check if the file is open.
		while (getline(file, line)) { // Read each line from the file.
			bst.insert(line); // Insert the line into the binary search tree.
		}
		file.close(); // Close the file.
		cout << "Data loaded from file successfully.\n"; // Print a message indicating that the data was loaded successfully.
	}
	else { // If the file cannot be opened, print an error message.
		cout << "Unable to open file.\n"; // Print an error message indicating that the file could not be opened.
	}
}


void testRemoveFromEmptyBST() { // This function tests the remove function on an empty binary search tree.
	BinarySearchTree bst; // Create a new binary search tree.
	assert(bst.remove("5") == false); // Check that removing a node from an empty tree returns false.
	cout << "Remove from empty BST test passed.\n"; // Print a message indicating that the test passed.
}

void testInsertDuplicateNode() { // This function tests inserting a duplicate node into the binary search tree.
	BinarySearchTree bst; // Create a new binary search tree.
	bst.insert("5"); // Insert a node with value 5.
	bst.insert("5"); // Insert a duplicate node with value 5.
	assert(bst.exists("5") == true); // Check that the duplicate node was inserted successfully.
	cout << "Insert duplicate node test passed.\n"; // Print a message indicating that the test passed.
}

void testRemoveNodeWithNoChildren() { // This function tests removing a node with no children from the binary search tree.
	BinarySearchTree bst; // Create a new binary search tree.
	bst.insert("5"); // Insert a node with value 5.
	bst.insert("3"); // Insert a node with value 3.
	bst.insert("7"); // Insert a node with value 7.
	assert(bst.remove("3") == true); // Remove the node with value 3.
	assert(bst.exists("3") == false); // Check that the node with value 3 was removed successfully.
	cout << "Remove node with no children test passed.\n"; // Print a message indicating that the test passed.
}

void testRemoveNodeWithOneChild() { // This function tests removing a node with one child from the binary search tree.
	BinarySearchTree bst; // Create a new binary search tree.
	bst.insert("5"); // Insert a node with value 5.
	bst.insert("3"); // Insert a node with value 3.
	bst.insert("7"); // Insert a node with value 7.
	bst.insert("6"); // Insert a node with value 6.
	assert(bst.remove("7") == true); // Remove the node with value 7.
	assert(bst.exists("7") == false); // Check that the node with value 7 was removed successfully.
	assert(bst.exists("6") == true); // Check that the child node with value 6 still exists.
	cout << "Remove node with one child test passed.\n"; // Print a message indicating that the test passed.
}

void testRemoveNodeWithTwoChildren() { // This function tests removing a node with two children from the binary search tree.
	BinarySearchTree bst; // Create a new binary search tree.
	bst.insert("5"); // Insert a node with value 5.
	bst.insert("3"); // Insert a node with value 3.
	bst.insert("7"); // Insert a node with value 7.
	bst.insert("6"); // Insert a node with value 6.
	bst.insert("8"); // Insert a node with value 8.
	assert(bst.remove("7") == true); // Remove the node with value 7.
	assert(bst.exists("7") == false); // Check that the node with value 7 was removed successfully.
	assert(bst.exists("6") == true); // Check that the child node with value 6 still exists.
	assert(bst.exists("8") == true); // Check that the child node with value 8 still exists.
	cout << "Remove node with two children test passed.\n"; // Print a message indicating that the test passed.
}

void testVerifyBSTStructure() { // This function tests the structure of the binary search tree to ensure it is correctly implemented.
	BinarySearchTree bst; // Create a new binary search tree.
	bst.insert("5"); // Insert a node with value 5.
	bst.insert("3"); // Insert a node with value 3.
	bst.insert("7"); // Insert a node with value 7.
	bst.insert("2"); // Insert a node with value 2.
	bst.insert("4"); // Insert a node with value 4.
	bst.insert("6"); // Insert a node with value 6.
	bst.insert("8"); // Insert a node with value 8.

	cout << "Inorder traversal (should be sorted): " << bst.inorder() << endl; // Print the inorder traversal of the tree.
}

double measureAddPerformance(int numNodes) { // This function measures the performance of adding nodes to the binary search tree.
	BinarySearchTree bst; // Create a new binary search tree.
	random_device rd; // Create a random device to generate random numbers.
	mt19937 gen(rd()); // Create a random number generator.
	uniform_int_distribution<> dis(1, 1000000); // Create a uniform distribution for random numbers.

	auto start = high_resolution_clock::now(); // Start measuring time.

	for (int i = 0; i < numNodes; ++i) { // Loop through the specified number of nodes.
		bst.insert(to_string(dis(gen))); // Insert a random node into the tree.
    }

	auto end = high_resolution_clock::now(); // Stop measuring time.
	duration<double> diff = end - start; // Calculate the time taken to add the nodes.
	return diff.count(); // Return the time taken in seconds.
}

int main() { // This is the main function where the program starts.
	BinarySearchTree bst; // Create a new binary search tree.
	readFromFile(bst, "C:/Users/rashe/Downloads/sample_data.txt"); // Read data from a file and insert it into the binary search tree.
	cout << "Current path is " << filesystem::current_path() << endl; // Print the current path of the program.
	cout << "Inorder traversal of BST: " << bst.inorder() << endl; // Print the inorder traversal of the binary search tree.

	// Run all test cases
	testRemoveFromEmptyBST(); // Test removing a node from an empty binary search tree.
	testInsertDuplicateNode(); // Test inserting a duplicate node into the binary search tree.
	testRemoveNodeWithNoChildren(); // Test removing a node with no children from the binary search tree.
	testRemoveNodeWithOneChild(); // Test removing a node with one child from the binary search tree.
	testRemoveNodeWithTwoChildren(); // Test removing a node with two children from the binary search tree.
	testVerifyBSTStructure(); // Test the structure of the binary search tree.

    // Measure performance
	vector<int> nodeCounts = { 100, 1000, 10000, 100000 }; // Define the number of nodes to add for performance measurement.
	vector<double> times; // Create a vector to store the times taken to add nodes.

	for (int count : nodeCounts) { // Loop through the number of nodes to add.
		double time = measureAddPerformance(count); // Measure the time taken to add the specified number of nodes.
		times.push_back(time); // Store the time taken in the vector.
		cout << "Time to add " << count << " nodes: " << time << " seconds" << endl; // Print the time taken to add the nodes.

		if (times.size() > 1) { // Check if there are at least two time measurements.
			double ratio = times.back() / times[times.size() - 2]; // Calculate the ratio of the current time to the previous time.
			cout << "Ratio to previous: " << fixed << setprecision(2) << ratio << "x" << endl; // Print the ratio to the previous time.
        }
    }

	return 0; // Return 0 to indicate successful completion of the program.
}