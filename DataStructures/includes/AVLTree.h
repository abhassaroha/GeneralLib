#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

template <class Key, class Val>
struct AVLNode {
	AVLNode():left(NULL), right(NULL), 
	height(1), size(1) {};
	int height;
	Key* key;
	Val* value;
	AVLNode* left;
	AVLNode* right;
	AVLNode* parent;
	int size;
};

template <class Key, class Val>
class AVLTree {
	private:
		AVLNode<Key, Val>* mRoot;
		AVLNode<Key, Val>* getAVLNodeWithRank(int);
	public:
		AVLTree() {};
		Val* get(Key*);
		void put(Key*, Val*);
		void remove(Key*);
		Key* min();
		Key* max();
		Key* successor(Key*);
		Key* predecessor(Key*);
		Key* getKeyWithRank(int);
		Val* getValWithRank(int);
		int getRank(Key*);
		int size();
		void print();
};

#endif
