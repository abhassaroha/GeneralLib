#include "RBT.h"

/** Private methods **/
template <class Key, class Val>
void 
RBT<Key, Val>::leftRotate(Node<Key, Val>* node) {
	Node<Key, Val>* parent = node->parent;
	Node<Key, Val>* left = node->left;
	// update left node
	if (left) left->parent = parent;
	// update node
	node->left = parent;
	node->parent = parent->parent;
	// update parent
	parent->right = left;
	parent->parent = node;
}

template <class Key, class Val>
void
RBT<Key, Val>::rightRotate(Node<Key, Val>* node) {
	Node<Key, Val>* parent = node->parent;
	Node<Key, Val>* right = node->right;
	// update left node
	if (right) right->parent = parent;
	// update node
	node->right = parent;
	node->parent = parent->parent;
	// update parent
	parent->left = right;
	parent->parent = node;
}

template <class Key, class Val>
void
RBT<Key, Val>::insertFixup(Node<Key, Val>* node) {
	
}

template <class Key, class Val>
void
RBT<Key, Val>::deleteFixup(Node<Key, Val>* node) {
	
}

/** Public methods **/

// same as a BST
template <class Key, class Val>
Val*
RBT<Key, Val>::get(Key key) {
	Node<Key, Val>* current = mRoot;
	Val* result = NULL;
	while (current) {
		if (current->key == key)
			result = current->value;
		else if (current->key > key) 
			current = current->right;
		else current = current->left;
	}
	return result;
}

// If key not found, create new node with
// that key, else update value.
template <class Key, class Val>
void
RBT<Key, Val>::put(Key key, Val value) {
	Node<Key, Val> *current = mRoot;
	Node<Key, Val> *previous = NULL;
	while(current) {
		previous = current;
		if (current->key == key) {
			current->value = value;
			break;
		}
		else if (key > current->key) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	if (!current) {
		current = new Node<Key, Val>();
		current->key = key;
		current->value = value;
		if (previous) {
			current->parent = previous;
			if (previous->key > key) 
				previous->left = current;
			else previous->right = current;
			insertFixup(current);
		}
		else {
			mRoot = current;
			current->color = BLACK;
		}
	}
}

template <class Key, class Val>
void
RBT<Key, Val>::remove(Key key) {
	
}

template <class Key, class Val>
void
RBT<Key, Val>::print(Node<Key, Val>* node) {
	if (node) {
		print(node->left);
		cout<<node->value<<" ";
		print(node->right);
		if (node == mRoot) cout<<endl;
	}
}

int 
main(int argc, char** argv) {
	RBT<int, int> testInstance;
	return 0;
}