#ifndef __AVLTREEHPP__
#define __AVLTREEHPP__
#include <memory>
#include <algorithm>
#include <iostream>


enum PrintType {
	inOrderPrint,
	postOrderPrint,
	preOrderPrint
};

/** AVLTree Implementation using Unique Pointers */
template <typename K>
class AVLTree {
private:

	/** Make the AVLNode private so users can only access the tree implementation */
	template <class Key>
	class AVLNode {
	public:
		
		AVLNode *right { nullptr };
		AVLNode *left { nullptr };
		AVLNode *parent { nullptr };
		int balance { 0 };
		Key key;

		bool add(Key k){
			if(this->key == k){
				return false;
			}else if(k < this->value){
				if(this->left == nullptr){
					this->left = AVLNodePtr(new AVLNode(k, this));
					return true;
				}else{
					return this->left->add(k);
				}
			}else{
				if(this->right == nullptr){
					this->right = AVLNodePtr(new AVLNode(k, this));
					return true;
				}else{
					return this->right->add(k);
				}
			}
			return false;
		}

		/** Key Constructor */
		AVLNode(Key k, AVLNode *p) 
			: key(k)
			, parent(p)
		{}

		
		/** Copy Constructor */
		AVLNode(const AVLNode &node) 
			: left(node.left) 
			, right(node.right)
			, parent(node.parent)
			, key(node.key)
		{}

		/** Move constructor */
		AVLNode(AVLNode && node) noexcept 
			: left(node.left)
			, right(node.right)
			, parent(node.parent)
			, key(node.key)
		{}

		/** Copy Assignment Operator */
		AVLNode & operator= (const AVLNode &other){
			AVLNode tmp(other);
			*this = std::move(tmp);
			return *this;
		}

		/** Move assignment operator */
		AVLNode & operator= (AVLNode &&other) noexcept {
			this->left = other.left->clone();
			this->right = other.right->clone();
			this->parent = other.parent->clone();
			this->key = other.key;
			return *this;
		}
		/** Destructor */
		~AVLNode(){}

	};
	/** END AVLNode definition */

	/** AVLTree Definition */
	AVLNode<K> *root { nullptr };

	/** Rotations */
	AVLNode<K> *rotateLeft(AVLNode<K> *a){
		AVLNode<K> *tmp = a->right;
		tmp->parent = a->parent;
		a->right= tmp->left;
		
		if(a->right != nullptr){
			a->right->parent = a;
		}

		tmp->left= a;
		a->parent = tmp;

		if(tmp->parent != nullptr){
			if(tmp->parent->right == a){
				tmp->parent->right = tmp;
			}else{
				tmp->parent->left = tmp;
			}
		}

		this->setBalance(a);
		this->setBalance(tmp);
		return tmp;
	}
	AVLNode<K> *rotateLeftThenRight(AVLNode<K> *a){
		a->left = rotateLeft(a->left);
		return rotateRight(a);
	}

	AVLNode<K> *rotateRight(AVLNode<K> *a){
		AVLNode<K> *tmp = a->left;
		tmp->parent = a->parent;
		a->left = tmp->right;
		
		if(a->left != nullptr){
			a->left->parent = a;
		}

		tmp->right = a;
		a->parent = tmp;

		if(tmp->parent != nullptr){
			if(tmp->parent->right == a){
				tmp->parent->right = tmp;
			}else{
				tmp->parent->left = tmp;
			}
		}

		this->setBalance(a);
		this->setBalance(tmp);
		return tmp;
	}

	AVLNode<K> *rotateRightThenLeft(AVLNode<K> *a){
		a->right = rotateRight(a->right);
		return rotateLeft(a);
	}

	/** Rebalancing */
	void rebalance(AVLNode<K> *a){
		/*
		if(a == nullptr){
			return;
		}
		*/
		this->setBalance(a);

		// 4 rotation possibilities
		if(a->balance == -2){
			// Left side is lower, so we need to do right rotations
			if(this->height(a->left->left) >= this->height(a->left->right)){
				a = rotateRight(a);
			}else{
				a = rotateLeftThenRight(a);
			}
		}else if(a->balance == 2){
			if(this->height(a->right->right) >= this->height(a->right->left)){
				a = rotateLeft(a);
			}else{
				a = rotateRightThenLeft(a);
			}
		}

		if(a->parent != nullptr){
			rebalance(a->parent);
		}else{
			root = a;
		}
		
	}

	int height(AVLNode<K> *a){
		if(a == nullptr){
			return 0;
		}
		return 1 + std::max(height(a->left), height(a->right));
	}

	void setBalance(AVLNode<K> *a){
		if(a == nullptr){
			return;
		}
		// balance is the right height - the left height
		a->balance = height(a->right) - height(a->left);
	}
	void printBalance(AVLNode<K> *a){
		if(a != nullptr){
			printBalance(a->left);
			std::cout << a->balance << " ";
			printBalance(a->right);
		}
	}
	// void clearNode(AVLNode<K> *a);
	AVLNode<K> *getRightMostChild(AVLNode<K> *n){
		if(n == nullptr){
			return nullptr;
		}
		AVLNode<K> *tmp = n;
		while(tmp->right){
			tmp = tmp->right;
		}
		return tmp;
	}

	AVLNode<K> *getLeftMostChild(AVLNode<K> *n){
		if(n == nullptr){
			return nullptr;
		}
		AVLNode<K> *tmp = n;
		while(tmp->left){
			tmp = tmp->left;
		}
		return tmp;
	}

	void inOrderPrint(AVLNode<K> *node){
		if(node != nullptr){
			this->inOrderPrint(node->left);
			std::cout << node->key << ", ";
			this->inOrderPrint(node->right);
		}
	}
	
	void preOrderPrint(AVLNode<K> *node){
		if(node != nullptr){
			std::cout << node->key << ", ";
			this->inOrderPrint(node->left);
			this->inOrderPrint(node->right);
		}
	}

	void postOrderPrint(AVLNode<K> *node){
		if(node != nullptr){
			this->inOrderPrint(node->left);
			this->inOrderPrint(node->right);
			std::cout << node->key << ", ";
		}
	}

	int getRandomElement(AVLNode<K> *node){
		if(node == nullptr){
			std::cout << "No elements to grab" << std::endl;
			return -1;
		}
		AVLNode<K> *tmp = node;
		int depth = std::rand() % this->height(node);
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

public:
	AVLTree(){}
	~AVLTree(){
		delete root;
	}
	bool insert(K key){
		if(root == nullptr){
			root = new AVLNode<K>(key, nullptr);
			return true;
		}else{
			AVLNode<K> *n = root;
			AVLNode<K> *parent;
			while(n){
				if(n->key == key){
					return false;
				}

				parent = n;
				bool goLeft = n->key > key;
				n = goLeft ? n->left : n->right;

				if(n == nullptr){
					if(goLeft){
						parent->left = new AVLNode<K>(key, parent);
					}else{
						parent->right = new AVLNode<K>(key, parent);
					}
					this->rebalance(parent);
					break;
				}
				
			}
		}
		return true;
	}
	
	void deleteKey(const K delKey) {

		if (root == NULL)
			return;

		AVLNode<K>
			*n       = root,
			*parent  = root,
			*delNode = NULL,
			*child   = root;

		while (child != NULL) {
			parent = n;
			n = child;
			child = delKey >= n->key ? n->right : n->left;
			if (delKey == n->key){
				delNode = n;
			}
		}

		if (delNode != NULL) {
			delNode->key = n->key;

			child = n->left != NULL ? n->left : n->right;

			if (root->key == delKey) {
				root = child;
			}else{
				if (parent->left == n) {
					parent->left = child;
				}else{
					parent->right = child;
				}

				rebalance(parent);
			}
		}
	}
	
	void printBalance(){
		this->printBalance(this->root);
		std::cout << std::endl;
	}

	void printTree(PrintType printType){
		std::cout << "{ ";
		switch(printType){
			case PrintType::inOrderPrint:
				this->inOrderPrint(this->root);
				break;
			case PrintType::postOrderPrint:
				this->postOrderPrint(this->root);
				break;
			case PrintType::preOrderPrint:
				this->preOrderPrint(this->root);
				break;
			default:
				this->inOrderPrint(this->root);
				break;
				
		}
		std::cout << "}" << std::endl;
		
	}

	int height(){
		return this->height(this->root);
	}

	int getRandomElement(){
		return this->getRandomElement(this->root);
	}

};

#endif // __AVLTREEHPP__
