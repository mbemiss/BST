/*
This implementation file provides the concrete implementations for the Binary Search Tree (BST) class methods declared in the header file. It defines 
the functionality for core BST operations such as insertion, removal, searching, and various tree traversals (inorder, preorder, postorder). The file 
also includes implementations for constructors, destructor, and overloaded operators, completing the full functionality of the Binary Search Tree data 
structure.
*/

#include "BinarySearchTree.h" // This is a header file that contains the implementation of a binary search tree.

BinarySearchTree::BinarySearchTree() : root(nullptr) {} // This is the default constructor for the binary search tree.

void BinarySearchTree::insert(string word) { // This function inserts a node with the given word into the binary search tree.
	root = insertRecursive(root, word); // Call the recursive insert function to insert the node.
}

Node* BinarySearchTree::insertRecursive(Node* node, string word) { // This function inserts a node with the given word into the binary search tree.
	if (node == nullptr) { // If the current node is null, create a new node with the given word.
		return new Node{ word }; // Return the new node.
    }

	if (word < node->data) { // If the given word is less than the current node's data, insert the word into the left subtree.
		node->left = insertRecursive(node->left, word); // Recursively insert the word into the left subtree.
    }
	else if (word > node->data) { // If the given word is greater than the current node's data, insert the word into the right subtree.
		node->right = insertRecursive(node->right, word); // Recursively insert the word into the right subtree.
    }

	return node; // Return the current node.
}

bool BinarySearchTree::remove(string word) { // This function removes a node with the given word from the binary search tree.
	Node* result = removeRecursive(root, word); // Call the recursive remove function to remove the node.
	if (result == nullptr) { // If the result is null, the node was not found.
		return false; // Return false to indicate that the node was not removed.
    }
	root = result; // Update the root node.
	return true; // Return true to indicate that the node was removed.
}

Node* BinarySearchTree::removeRecursive(Node* node, string word) { // This function removes a node with the given word from the binary search tree.
	if (node == nullptr) { // If the current node is null, return null.
		return nullptr; // Return null.
    }

	if (word < node->data) { // If the given word is less than the current node's data, remove the word from the left subtree.
		node->left = removeRecursive(node->left, word); // Recursively remove the word from the left subtree.
    }
	else if (word > node->data) { // If the given word is greater than the current node's data, remove the word from the right subtree.
		node->right = removeRecursive(node->right, word); // Recursively remove the word from the right subtree.
    }
	else { // If the given word is equal to the current node's data, remove the current node.
		if (node->left == nullptr) { // If the left child is null, replace the current node with the right child.
			Node* temp = node->right; // Store the right child in a temporary variable.
			delete node; // Delete the current node.
			return temp; // Return the right child.
        }
		else if (node->right == nullptr) { // If the right child is null, replace the current node with the left child.
			Node* temp = node->left; // Store the left child in a temporary variable.
			delete node; // Delete the current node.
			return temp; // Return the left child.
        }

		Node* temp = findMinNode(node->right); // Find the node with the minimum value in the right subtree.
		node->data = temp->data; // Replace the current node's data with the minimum value.
		node->right = removeRecursive(node->right, temp->data); // Recursively remove the minimum value from the right subtree.
    }
	return node; // Return the current node.
}

Node* BinarySearchTree::findMinNode(Node* node) { // This function finds the node with the minimum value in the binary search tree.
	while (node->left != nullptr) { // Traverse the left subtree until the left child is null.
		node = node->left; // Move to the left child.
    }
	return node; // Return the node with the minimum value.
}

bool BinarySearchTree::exists(string word) const { // This function checks if a node with the given word exists in the binary search tree.
	return findRecursive(root, word) != nullptr; // Call the recursive find function and return true if the node is found, false otherwise.
}

Node* BinarySearchTree::findRecursive(Node* node, string word) const { // This function finds a node with the given word in the binary search tree.
	if (node == nullptr || node->data == word) { // If the current node is null or the data matches the given word, return the current node.
		return node; // Return the current node.
    }

	if (word < node->data) { // If the given word is less than the current node's data, search the left subtree.
		return findRecursive(node->left, word); // Recursively search the left subtree.
    }
	return findRecursive(node->right, word); // Otherwise, search the right subtree.
}

string BinarySearchTree::inorder() const { // This function returns the inorder traversal of the binary search tree as a string.
	string result; // Create an empty string to store the traversal result.
	inorderTraverseRecursive(root, result); // Call the recursive inorder traversal function to populate the result.
	return result; // Return the traversal result.
}

void BinarySearchTree::inorderTraverseRecursive(Node* node, string& result) const { // This function traverses the binary search tree in inorder and stores the result in a string.
	if (node != nullptr) { // If the current node is not null, traverse the left subtree, visit the current node, and traverse the right subtree.
		inorderTraverseRecursive(node->left, result); // Recursively traverse the left subtree.
		result += node->data + " "; // Append the current node's data to the result string.
		inorderTraverseRecursive(node->right, result); // Recursively traverse the right subtree.
    }
}

string BinarySearchTree::preorder() const { // This function returns the preorder traversal of the binary search tree as a string.
	string result; // Create an empty string to store the traversal result.
	preorderTraverseRecursive(root, result); // Call the recursive preorder traversal function to populate the result.
	return result; // Return the traversal result.
}

void BinarySearchTree::preorderTraverseRecursive(Node* node, string& result) const { // This function traverses the binary search tree in preorder and stores the result in a string.
	if (node != nullptr) { // If the current node is not null, visit the current node, traverse the left subtree, and traverse the right subtree.
		result += node->data + " "; // Append the current node's data to the result string.
		preorderTraverseRecursive(node->left, result); // Recursively traverse the left subtree.
		preorderTraverseRecursive(node->right, result); // Recursively traverse the right subtree.
    }
}

string BinarySearchTree::postorder() const { // This function returns the postorder traversal of the binary search tree as a string.
	string result; // Create an empty string to store the traversal result.
	postorderTraverseRecursive(root, result); // Call the recursive postorder traversal function to populate the result.
	return result; // Return the traversal result.
}

void BinarySearchTree::postorderTraverseRecursive(Node* node, string& result) const { // This function traverses the binary search tree in postorder and stores the result in a string.
	if (node != nullptr) { // If the current node is not null, traverse the left subtree, traverse the right subtree, and visit the current node.
		postorderTraverseRecursive(node->left, result); // Recursively traverse the left subtree.
		postorderTraverseRecursive(node->right, result); // Recursively traverse the right subtree.
		result += node->data + " "; // Append the current node's data to the result string.
    }
}

BinarySearchTree::~BinarySearchTree() { // This is the destructor for the binary search tree.
	deleteTree(root); // Call the deleteTree function to delete the binary search tree.
}

void BinarySearchTree::deleteTree(Node* node) { // This function deletes the binary search tree.
	if (node != nullptr) { // If the current node is not null, recursively delete the left and right subtrees, and delete the current node.
		deleteTree(node->left); // Recursively delete the left subtree.
		deleteTree(node->right); // Recursively delete the right subtree.
		delete node; // Delete the current node.
    }
}