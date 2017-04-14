#ifndef __TREESET_HPP__
#define __TREESET_HPP__
#include <time.h>
#include <cmath>
#include <iostream>

class AVLNode{
public:
	AVLNode *left;
	AVLNode *right;
	AVLNode *parent;
	int balance;
	int key;
	AVLNode(int key, AVLNode *parent) :
	left(nullptr), right(nullptr), parent(parent), key(key)
	{}
	~AVLNode(){
		delete left;
		delete right;
	}

};

class AVLTree{
	int height;
	AVLNode *root;
public:
	bool insert(int val){
		return false;
	}
	bool remove(int val){
		return false;
	}
	int getHeight() const { return height; }
	AVLNode *getRoot() const { return root; }

};

class NMTreeSet{
	AVLTree *tree;
public:
	NMTreeSet(){
	}
	bool insert(int val){
		return tree->insert(val);
	}

	bool remove(int val){
		return tree->remove(val);
	}

	int getRandomElement(){
		// Choose random depth
		// Go down until depth
		// At each choice, choose random direction
		int depth = std::rand() % tree->getHeight();
		auto *tmp = tree->getRoot();
		for(int i = 0; i < depth; i++){
			int choice = std::rand() % 1;
			if(choice){
				// right
				tmp = tmp->right;
			}else{
				// left
				tmp = tmp->left;
			}
		}
		if(tmp){
			return tmp->key;
		}
		return -1;
	}

};

#endif // __TREESET_HPP__
