#ifndef __TREESET_HPP__
#define __TREESET_HPP__
#include <time.h>
#include <cmath>
#include <iostream>
#include "avltree.hpp"


class NMTreeSet{
	AVLTree<int> *tree;
public:
	NMTreeSet(){
		tree = new AVLTree<int>();
	}
	~NMTreeSet(){
		delete tree;
	}
	bool insert(int val){
		return this->tree->insert(val);
	}

	void remove(int val){
		this->tree->deleteKey(val);
	}
	void print(){
		this->tree->printTree(PrintType::inOrderPrint);
	}

	int getRandomElement(){
		// Choose random depth
		// Go down until depth
		// At each choice, choose random direction
		return tree->getRandomElement();
	}
};

#endif // __TREESET_HPP__
