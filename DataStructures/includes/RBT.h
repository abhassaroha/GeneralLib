#ifndef RBT_H
#define RBT_H

#include <iostream>
#include <ctime>

namespace datastructures {
    
#define RED true
#define BLACK false
    
	template <class Key, class Val>
    struct RBTNode {
        // sentinel
        RBTNode():color(BLACK), left(this),
        right(this), size(0) {};
        RBTNode(RBTNode<Key, Val>* sentinel): color(RED),
        left(sentinel), right(sentinel), size(1) {};
        bool color;
        RBTNode* parent;
        RBTNode* left;
        RBTNode* right;
        Key* key;
        Val* value;
        int size;
    };
    
	// Red black tree for ordered symbol
	// table - implementation from CLRS
	template <class Key, class Val>
    class RBT {
    private:
        RBTNode<Key, Val>* mSentinel;
        RBTNode<Key, Val>* mRoot;
        void leftRotate(RBTNode<Key, Val>*);
        void rightRotate(RBTNode<Key, Val>*);
        void insertFixup(RBTNode<Key, Val>*);
        void removeFixup(RBTNode<Key, Val>*);
        RBTNode<Key, Val>* getRBTNode(Key*);
        void transplant(RBTNode<Key, Val>*,
						RBTNode<Key,Val>*);
        RBTNode<Key, Val>* successor(RBTNode<Key, Val>*);
        RBTNode<Key, Val>* getRBTNodeWithRank(int);
        void printTree(RBTNode<Key, Val>*);
    public:
        RBT(): mSentinel(new RBTNode<Key,Val>()),
        mRoot(mSentinel) {};
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
