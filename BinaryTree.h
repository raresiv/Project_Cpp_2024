#pragma once
#include <iostream>
#include <vector>
using namespace std;
//We created all our functions in the .h file because the template class will not function otherwise
//The compiler will not have access to them otherwise
//The template is used so that the nodes of our tree can take values of any type T
template <typename T>
class BinaryTree
{
public:
	BinaryTree() : _depth(0) { //constructor initializing an empty tree

	}

	BinaryTree(int d) : _depth(d) { //constructor initializing a tree of depth d
		resizeTree(); // we rezise the tree at the good size
	}
	void setDepth(int n) {	//function that changes the size of the tree to the size n
		_depth = n;
		resizeTree();
	}

	void setNode(int x, int y, T t) { // x is the depht and y the level
		if (_tree.size() != 0) { // if the tree is non null (exists)
			if (x >= 0 && x <= _tree.size()) { // and if x is in the interval
				if (y >= 0 && y < _tree[x].size()) {
					_tree[x][y] = t;
				}
			}
		}
	}

	T getNode(int a, int b) { // a is the level and b the depth
		T t{};
		if (_depth != 0) {
			if (a >= 0 && a <= _depth) {	// if the tree is non null (exists)
				if (b >= 0 && b < _tree[a].size()) { // and if a is in the interval
					t = _tree[a][b];	// we get the value of the node
				}
			}
		}

		return t;
	}

	void display() {//display the tree on the console
		if (_tree.size() != 0) { //if the tree exists
			for (int i = 0; i < _depth; i++) { //we visit each depth
				for (int j = 0; j < _tree[i].size(); j++) {	// and each 'level'
					std::cout << _tree[i][j] << " ";
				}
				std::cout << "\n";	// next row at the end of a depht
			}
		}
	}

protected:
	int _depth;
	std::vector<std::vector<T>> _tree;

	void resizeTree() { //function that resize the tree
		_tree.resize(_depth+1);
		for (int i = 0; i < _depth+1; ++i) {
			_tree[i].resize(i + 1);
		}
	}

};

