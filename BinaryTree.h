#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class BinaryTree
{
public:
	BinaryTree(int d) : _depth(d) {
		resizeTree();
	}
	void setDepth(int n) {
		_depth = n;
		resizeTree();
	}

	void setNode(int x, int y, T t) { // a est le niveau et b la 'profondeur'
		if (_tree.size() != 0) {
			if (x >= 0 && x < _tree.size()) {
				if (y >= 0 && y < _tree[x].size()) {
					_tree[x][y] = t;
				}
			}
			//mess d'erreur ?
		}
	}

	T getNode(int a, int b) {//comme le fonction d'avant, a est le niveau et b la profondeur
		T t;
		if (_depth != 0) {
			if (a >= 0 && a < _depth) {
				if (b > 0 && b < _tree[a].size()) {
					t = _tree[a][b];
				}
			}
		}

		return t;
	}

	void display() {
		if (_tree.size() != 0) {
			for (int i = 0; i < _depth; i++) {
				for (int j = 0; j < _tree[i].size(); j++) {
					std::cout << _tree[i][j] << " ";
				}
				std::cout << "\n";
			}
		}
	}

	
	//void display() {
	//	if (_tree.size() != 0) {
	//		for (int i = 0; i < _depth; i++) {
	//			// Imprime l'espacement initial pour centrer les niveaux
	//			for (int j = 0; j < (_depth - i - 1); j++) {
	//				std::cout << "   "; // Espacement à gauche
	//			}

	//			// Imprime les valeurs dans le niveau actuel
	//			for (int j = 0; j < _tree[i].size(); j++) {
	//				std::cout << _tree[i][j] << "    "; // Valeurs avec espacement
	//			}

	//			std::cout << "\n";

	//			// Affiche les branches pour le niveau actuel
	//			if (i < _depth - 1) {
	//				for (int j = 0; j < (_depth - i-1); j++) {
	//					std::cout << "   ";
	//					// Espacement à gauche
	//				}
	//				for (int j = 0; j < _tree[i].size(); j++) {
	//					std::cout << "/ \\  "; // Affiche les branches
	//					
	//				}
	//				std::cout << "\n";
	//			}
	//		}
	//	}
	//}


protected:
	int _depth;
	std::vector<std::vector<T>> _tree;

	void resizeTree() {
		_tree.resize(_depth);
		for (int i = 0; i < _depth; ++i) {
			_tree[i].resize(i + 1);
		}
	}

};

