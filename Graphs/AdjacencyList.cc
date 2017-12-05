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
		vector<weak_ptr<Node>> neighbors;

		Node(const char data) : data{data}, visited{}, neighbors{} {}
	};

	vector<shared_ptr<Node>> all_nodes_;

	public: 
	AdjacencyList() {}

	weak_ptr<Node> add_node(const char data) {
		auto new_node_ptr = make_shared<Node>(data);
		all_nodes_.push_back(new_node_ptr);

		return new_node_ptr;
	}

	void connect(const weak_ptr<Node>& node, const weak_ptr<Node>& node_to_connect) {
		node.lock()->neighbors.push_back(node_to_connect);
		node_to_connect.lock()->neighbors.push_back(node);
	}

	shared_ptr<Node> get_node_at(const int index) {
		return all_nodes_[index];
	}

	void print() {
		for (const auto& node : all_nodes_) {
			print_node(node);
			cout << endl;
		}
	}

	friend void depth_first_traversal(weak_ptr<Node> root);

	private:
	static void print_node(const weak_ptr<Node> node);
};

void AdjacencyList::print_node(const weak_ptr<Node> node) {
		auto locked_node = node.lock();

		if (locked_node) {
			cout << "Node " << locked_node->data << " is connected to: ";

			ostringstream ss;
			for (auto& neighbor : locked_node->neighbors) {
				auto locked_neighbor = neighbor.lock();
				ss << locked_neighbor->data << ' ';
			}
			cout << setw(10) << left << ss.str();
		}
}

void depth_first_traversal(weak_ptr<AdjacencyList::Node> root) {
		auto node = root.lock();

		if (!node) return;
		AdjacencyList::print_node(node);
		cout << endl;
		node->visited = true;
		for (auto& neighbor : node->neighbors) {
			auto locked_neighbor = neighbor.lock();
			if (locked_neighbor && !locked_neighbor->visited) {
				depth_first_traversal(locked_neighbor);
			}
		}
}

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
