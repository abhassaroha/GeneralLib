#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

using namespace std;

namespace datastructures {
	template <typename Key, typename Val>
    class AVLTree {
    private:
		template <typename _Key, typename _Val>
	    struct AVLNode {
	        AVLNode(AVLNode<_Key, _Val>* sentinel) : left(sentinel),
			right(sentinel),
	        height(1), size(1) {};
	        // sentinel
	        AVLNode():left(NULL), right(NULL),
	        height(0), size(0) {};
	        _Key* key;
	        _Val* value;
	        AVLNode* left;
	        AVLNode* right;
	        AVLNode* parent;
	        int height;
	        int size;
	    };
	
        AVLNode<Key, Val>* mSentinel;
        AVLNode<Key, Val>* mRoot;
        AVLNode<Key, Val>* getAVLNodeWithRank(int);
        void leftRotate(AVLNode<Key, Val>*);
        void rightRotate(AVLNode<Key, Val>*);
        void insertFixup(AVLNode<Key, Val>*);
        void printTree(AVLNode<Key, Val>*);
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
}

#endif
