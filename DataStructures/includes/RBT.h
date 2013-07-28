#ifndef RBT_H
#define RBT_H

#include <iostream>

#define RED true
#define BLACK false

template <class Key, class Val>
struct Node {
	Node():color(RED), left(NULL),
		right(NULL) {};
	bool color;
	Node* parent;
	Node* left;
	Node* right;
	Key* key;
	Val* value;
};

// Red black tree for ordered symbol 
// table - implementation from CLRS
template <class Key, class Val>
class RBT {
private:
	Node<Key, Val>* mRoot;
	void leftRotate(Node<Key, Val>*);
	void rightRotate(Node<Key, Val>*);
	void insertFixup(Node<Key, Val>*);
	void deleteFixup(Node<Key, Val>*);
public:
	RBT():mRoot(NULL) {};
	Val* get(Key);
	void put(Key, Val);
	void remove(Key);
	void print(Node<Key, Val>*);
};

#endif