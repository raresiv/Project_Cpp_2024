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
	BinaryTree() : _depth(0) {

	}

	BinaryTree(int d) : _depth(d) {
		resizeTree();
	}
	void setDepth(int n) {
		_depth = n;
		resizeTree();
	}

	void setNode(int x, int y, T t) { // a is the level and b the depth
		if (_tree.size() != 0) {
			if (x >= 0 && x <= _tree.size()) {
				if (y >= 0 && y < _tree[x].size()) {
					_tree[x][y] = t;
				}
			}
		}
	}

	T getNode(int a, int b) { // a is the level and b the depth
		T t{};
		if (_depth != 0) {
			if (a >= 0 && a <= _depth) {
				if (b >= 0 && b < _tree[a].size()) {
					t = _tree[a][b];
				}
			}
		}

		return t;
	}

	void display() {//display the tree
		if (_tree.size() != 0) {
			for (int i = 0; i < _depth; i++) {
				for (int j = 0; j < _tree[i].size(); j++) {
					std::cout << _tree[i][j] << " ";
				}
				std::cout << "\n";
			}
		}
	}

protected:
	int _depth;
	std::vector<std::vector<T>> _tree;

	void resizeTree() {
		_tree.resize(_depth+1);
		for (int i = 0; i < _depth+1; ++i) {
			_tree[i].resize(i + 1);
		}
	}

};

