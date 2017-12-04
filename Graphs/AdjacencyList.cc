#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>

using namespace std;

class AdjacencyList {
	struct Node {
		char data;
		bool visited;
		vector<shared_ptr<Node>> neighbors;
	};

	vector<shared_ptr<Node>> all_nodes_;

	public: 
	AdjacencyList() {}

	shared_ptr<Node> add_node(const char& data) {
		shared_ptr<Node> new_node_ptr(new Node{data});
		all_nodes_.push_back(new_node_ptr);

		return new_node_ptr;
	}

	void connect(const shared_ptr<Node>& node, const shared_ptr<Node>& node_to_connect) {
		node->neighbors.push_back(node_to_connect);
		node_to_connect->neighbors.push_back(node);
	}

	void print() {
		for (auto& node : all_nodes_) {
			print_node(node);
			cout << endl;
		}
	}

	private:
	void print_node(const shared_ptr<Node>& node) const {
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

	adjacency_list.connect(A, D);
	adjacency_list.connect(C, D);

	// Print Adjacency List
	adjacency_list.print();
}
