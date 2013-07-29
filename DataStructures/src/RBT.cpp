#include "RBT.h"

using namespace std;

static int maxHeight = 0;
static int totalHeight = 0;
static int lastBlackHeight = -1;
static int blackHeight = 0;

/** Private methods **/
template <class Key, class Val>
void 
RBT<Key, Val>::leftRotate(Node<Key, Val>* node) {
	Node<Key, Val>* parent = node->parent;
	Node<Key, Val>* right = node->right;
	// update node's right child
	node->right = right->left;
	if (right->left) right->left->parent = node;
	// update right
	right->left = node;
	right->parent = parent;
	// update parent
	if (node == parent->left)
		parent->left = right;
	else
		parent->right = right;
	// update node's parent
	node->parent = right;
	if (mRoot == node) mRoot = right;
}

template <class Key, class Val>
void
RBT<Key, Val>::rightRotate(Node<Key, Val>* node) {
	Node<Key, Val>* parent = node->parent;
	Node<Key, Val>* left = node->left;
	// update node's left child
	node->left = left->right;
	if (left->right) left->right->parent = node;
	// update left
	left->parent = parent;
	left->right = node;
	// update parent
	if (node == parent->left)
		parent->left = left;
	else
		parent->right = left;
	// update node's parent
	node->parent = left;
	if (mRoot == node) mRoot = left;
}

template <class Key, class Val>
void
RBT<Key, Val>::insertFixup(Node<Key, Val>* node) {
	Node<Key,Val>* parent;
	Node<Key, Val>* uncle;
	Node<Key, Val>* current = node;
	while(current->parent->color == RED) {
		parent = current->parent;
		// when parent is left-child
		if (parent == parent->parent->left) {
			uncle = parent->parent->right;
			// pull down the black grand parent
			// and make parent and uncle black.
			if (uncle->color == RED) {
				uncle->color = BLACK;
				parent->color = BLACK;
				parent->parent->color = RED;
				current = parent->parent;
			}
			else {
				// if i am right, convert to case that follows
				if (current == parent->right) {
					leftRotate(parent);
					current = parent;
				}
				// right rotate to pull parent one level
				// nearer to root.
				current->parent->color = BLACK;
				current->parent->parent->color = RED;
				rightRotate(current->parent->parent);
			}
		}
		// when parent is right-child
		else {
			uncle = parent->parent->left;
			if (uncle->color == RED) {
				uncle->color = BLACK;
				parent->color = BLACK;
				parent->parent->color = RED;
				current = parent->parent;
			}
			else {
				// if i am left, convert to case that follows
				if (current == parent->left) {
					rightRotate(parent);
					current = parent;
				}
				// left rotate to pull parent one level
				// nearer to root.
				current->parent->color = BLACK;
				current->parent->parent->color = RED;
				leftRotate(current->parent->parent);
			}
		}
	}
	mRoot->color = BLACK;
}

template <class Key, class Val>
void
RBT<Key, Val>::deleteFixup(Node<Key, Val>* node) {
	
}

template <class Key, class Val>
void
RBT<Key, Val>::printTree(Node<Key, Val>* node) {
	if (node != mSentinel) {
		totalHeight++;
		if (node->color == BLACK) blackHeight++;
		printTree(node->left);
		if (node->color == BLACK) blackHeight--;
		cout<<*node->key<<"->"<<*node->value<<" ";
		totalHeight++;
		if (node->color == BLACK) blackHeight++;
		printTree(node->right);
		if (node->color == BLACK) blackHeight--;
		if (node == mRoot) {
			cout<<endl;
			// Max total height - Red + Black max 
			// across all paths from root to leaf
			// Black Height - Black height of each path from
			// root to leaves in RBT.
			cout<<"Black Height "<<lastBlackHeight<<endl;
			cout<<"Total Max Height "<<maxHeight<<endl;
		}
	}
	else {
		if (totalHeight > maxHeight)
			maxHeight = totalHeight;
		// ASSERTION
		// Black height should be same across
		// all paths from root to leaf.
		if (lastBlackHeight == -1)
			lastBlackHeight = blackHeight;
		else {
			if (lastBlackHeight != blackHeight) {
				cout<<"Black Height mismatch current "<<
					blackHeight<<" last "<<lastBlackHeight<<endl;
				cout<<"max height "<<maxHeight<<endl;
				exit(EXIT_FAILURE);	
			}
		}
	}
	totalHeight--;
}

/** Public methods **/

// same as a BST
template <class Key, class Val>
Val*
RBT<Key, Val>::get(Key* key) {
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
RBT<Key, Val>::put(Key* key, Val* value) {
	Node<Key, Val> *current = mRoot;
	Node<Key, Val> *previous = NULL;
	while(current != mSentinel) {
		previous = current;
		if (*current->key == *key) {
			current->value = value;
			break;
		}
		else if (*key > *current->key) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	if (current == mSentinel) {
		current = new Node<Key, Val>(mSentinel);
		current->key = key;
		current->value = value;
		if (previous) {
			current->parent = previous;
			if (*previous->key > *key) 
				previous->left = current;
			else previous->right = current;
			insertFixup(current);
		}
		else {
			mRoot = current;
			current->parent = mSentinel;
			current->color = BLACK;
		}
	}
}

template <class Key, class Val>
void
RBT<Key, Val>::remove(Key* key) {
	
}

template <class Key, class Val>
void
RBT<Key, Val>::print() {
	printTree(mRoot);
}

void swap(int* source, int a, int b) {
	int temp = source[a];
	source[a] = source[b];
	source[b] = temp;
}

void knuthShuffle(int* inArray, int length) {
	int i;
	int current;
	for (i = length; i > 0;) {
		current = rand()%i;
		swap(inArray, current, --i);
	}
}

// Test client for RBT.
int 
main(int argc, char** argv) {
	RBT<int, int> testInstance;
	int* array = new int[10];
	for (int i = 0; i < 10; i++)
		array[i] = i + 1;
	knuthShuffle(array, 10);
	for (int i = 0; i < 10; i++) {
		testInstance.put(&array[i], &array[i]);
	}
	testInstance.print();
	return 0;
}