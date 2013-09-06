#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

template <class Key, class Val>
struct AVLNode {
	AVLNode(AVLNode<Key, Val>* sentinel):left(sentinel), right(sentinel), 
		height(1), size(1) {};
	// sentinel
	AVLNode():left(NULL), right(NULL),
		height(0), size(0) {};
	Key* key;
	Val* value;
	AVLNode* left;
	AVLNode* right;
	AVLNode* parent;
	int height;
	int size;
};

template <class Key, class Val>
class AVLTree {
	private:
		AVLNode<Key, Val>* mSentinel;
		AVLNode<Key, Val>* mRoot;
		AVLNode<Key, Val>* getAVLNodeWithRank(int);
		void leftRotate(AVLNode<Key, Val>*);
		void rightRotate(AVLNode<Key, Val>*);
		void insertFixup(AVLNode<Key, Val>*);
	public:
		AVLTree():mSentinel(new AVLNode<Key, Val>()), mRoot(mSentinel) {};
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
