#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

// Binary search tree node
struct Node {
	int data;	
	Node* left;
	Node* right;
};

// Input: A Node pointer to the root of the BST and the data for the
// 		new node to be inserted.
// Iteratively scans through the BST to find the position for the new
// 		node, the creates a node with the data and attached it to the BST 
//		at that position.
Node* IterativeInsert(Node* root_ptr, int data) {
	if (!root_ptr) {
		root_ptr = new Node{data, nullptr, nullptr};
	}

	Node* node = root_ptr;

	while (true) {
		if (data <= node->data) {
			if (node->left) {
				node = node->left;
			} else {
				node->left = new Node{data, nullptr, nullptr};
				break;
			}
		} else {
			if (node->right) {
				node = node->right;
			} else {
				node->right = new Node{data, nullptr, nullptr};
				break;
			}
		}
	}
	
	return root_ptr;
}

// Input: The root node of a BST.
// Prompts the user to enter a space-separated list of integers
// 		to be used as initialization for a binary search tree.
// Returns: The root node of the newly created BST.
Node* InitializeBST() {
	string input_from_user;
	getline(cin, input_from_user);

	istringstream ss(input_from_user);

	int new_node_value;
	Node* root_ptr = nullptr;
	Node* temp_node = nullptr;
	while (ss >> new_node_value) {
		root_ptr = IterativeInsert(root_ptr, new_node_value);
	}

	return root_ptr;
}

// Input: Node pointer to the root of the BST
// Iteratively traverses the BST in-order and prints the
// 		value at each node.
void IterativeInorderPrint(Node* node) {
	stack<Node*> node_stack;

	while (true) {
		if (node) {
			node_stack.push(node);
			node = node->left;
		} else {
			if (node_stack.size() != 0) {
				cout << node_stack.top()->data << ' ';
				node = node_stack.top()->right;
				node_stack.pop();
			} else {
				break;
			}
		}
	}
}

// Input: The Node pointer to the root node of the BST.
// Iteratively traverses the BST to find the minimum value.
// 		i.e., traverses as far left as possible.
// Returns: A Node* pointer to the node with the minimum key.
Node* IterativeMinSearch(Node* node) {
	if (!node) {
		return nullptr;
	}

	while (node->left) {
		node = node->left;
	}

	return node;
}

// Input: The Node pointer to the root node of the BST.
// Iteratively traverses the BST to find the maximum value.
// 		i.e., traverses as far right as possible.
// Returns: A Node* pointer to the node with the maximum key.
Node* IterativeMaxSearch(Node* node) {
	if (!node) {
		return nullptr;
	}

	while (node->right) {
		node = node->right;
	}

	return node;
}

int main() {
	cout << "Input a space-separated list of integers as initializers for the BST (enter to submit): ";
	Node* root_ptr = InitializeBST();
	cout << endl;

	cout << "Iterative in-order print of the BST: ";
	IterativeInorderPrint(root_ptr);
	cout << endl;

	Node* node_with_min_key = IterativeMinSearch(root_ptr);
	cout << "Iterative min result: (value: " << node_with_min_key->data << ", address: " << node_with_min_key << ")" << endl;

	Node* node_with_max_key = IterativeMaxSearch(root_ptr);
	cout << "Iterative max result: (value: " << node_with_max_key->data << ", address: " << node_with_max_key << ")" << endl;
}
