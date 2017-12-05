#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>

using namespace std;

// Bidirectional graph implementation using an adjacency list.
// List is implemented using a vector of shared pointers to Nodes.
class AdjacencyList {
	struct Node {
		char data;
		bool visited;
		vector<shared_ptr<Node>> neighbors;
	};

	vector<shared_ptr<Node>> all_nodes_;

	public: 
	AdjacencyList() {}

	shared_ptr<Node> add_node(char data) {
		shared_ptr<Node> new_node_ptr = make_shared<Node>(new Node{data});
		all_nodes_.push_back(new_node_ptr);

		return new_node_ptr;
	}

	void connect(const shared_ptr<Node>& node, const shared_ptr<Node>& node_to_connect) {
		node->neighbors.push_back(node_to_connect);
		node_to_connect->neighbors.push_back(node);
	}

	shared_ptr<Node> get_node_at(int index) {
		return all_nodes_[index];
	}

	void print() {
		for (auto& node : all_nodes_) {
			print_node(node);
			cout << endl;
		}
	}

	friend void depth_first_traversal(shared_ptr<Node>& root) {
		if (!root) return;
		print_node(root);
		cout << endl;
		root->visited = true;
		for (auto& neighbor : root->neighbors) {
			if (!neighbor->visited) {
				depth_first_traversal(neighbor);
			}
		}
	}

	private:
	static void print_node(const shared_ptr<Node>& node) {
		cout << "Node " << node->data << " is connected to: ";

		ostringstream ss;
		for (auto& neighbor : node->neighbors) {
			ss << neighbor->data << ' ';
		}
		cout << setw(10) << left << ss.str();
	}
};

int main() {
	AdjacencyList adjacency_list;

	// Create vertices
	auto A = adjacency_list.add_node('A');
	auto B = adjacency_list.add_node('B');
	auto C = adjacency_list.add_node('C');
	auto D = adjacency_list.add_node('D');

	// Connect vertices
	adjacency_list.connect(A, B);

	adjacency_list.connect(A, C);
	adjacency_list.connect(C, B);

	adjacency_list.connect(C, D);

	// Print graph
	adjacency_list.print();

	// Print graph using depth-first traversal
	cout << "\nDepth-first print: \n";
	depth_first_traversal(A);
}
