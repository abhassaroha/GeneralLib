#include "AVLTree.h"

/*********************/
/** Private methods **/
/*********************/
#define MAX(a, b) \
(a > b ? a : b)

template <class Key, class Val>
void 
AVLTree<Key, Val>::leftRotate(AVLNode<Key, Val>* node)
{
	AVLNode<Key, Val>* parent = node->parent;
	AVLNode<Key, Val>* right = node->right;
	// update node's right child
	node->right = right->left;
	node->size -= right->size;
	node->size += right->left->size;
	node->height = 	MAX(node->left->height, node->right->height) + 1;
	right->left->parent = node;
	// update right
	right->size -= right->left->size;
	right->left = node;
	right->size += node->size;
	right->height = MAX(right->left->height, right->right->height) + 1;
	right->parent = parent;
	// update parent
	if (node == parent->left)
		parent->left = right;
	else
		parent->right = right;
	parent->height = MAX(parent->left->height, parent->right->height) + 1;
	// update node's parent
	node->parent = right;
	if (mRoot == node) mRoot = right;
}

template <class Key, class Val>
void 
AVLTree<Key, Val>::rightRotate(AVLNode<Key, Val>* node)
{
	AVLNode<Key, Val>* parent = node->parent;
	AVLNode<Key, Val>* left = node->left;
	// update node's left child
	node->left = left->right;
	node->size -= left->size;
	node->size += left->right->size;
	node->height = 	MAX(node->left->height, node->right->height) + 1;		
	left->right->parent = node;
	// update left
	left->size -= left->right->size;
	left->right = node;
	left->size += node->size;
	left->height = MAX(left->left->height, left->right->height) + 1;	
	left->parent = parent;
	// update parent
	if (node == parent->left)
		parent->left = left;
	else
		parent->right = left;
	parent->height = MAX(parent->left->height, parent->right->height) + 1;
	// update node's parent
	node->parent = left;
	if (mRoot == node) mRoot = left;
}

template <class Key, class Val>
AVLNode<Key,Val>*
AVLTree<Key, Val>::getAVLNodeWithRank(int rank) {
	AVLNode<Key, Val>* current = mRoot;
	AVLNode<Key, Val>* result = NULL;
	while (current != mSentinel) {
		if (rank == current->left->size + 1) {
			result = current;
			break;
		}
		else if (rank > current->left->size + 1) {
			rank -= (current->left->size + 1);
			current = current->right;
		}
		else { current = current->left; }
	}
	return result;
}

template <class Key, class Val>
void 
AVLTree<Key, Val>::insertFixup(AVLNode<Key, Val>* node)
{
	AVLNode<Key, Val>* parent;
	while (node != mSentinel)
	{
		if (node->left->height > node->right->height + 1) {
			if (node->left->right->height > node->left->left->height) {
				leftRotate(node->left);
			}
			rightRotate(node);
		}
		else if (node->right->height > node->left->height + 1) {
			if (node->right->left->height > node->right->right->height) {
				rightRotate(node->right);
			}
			leftRotate(node);
		}
		node = node->parent;
	}
}

/********************/
/** Public methods **/
/********************/

template <class Key, class Val>
Val*
AVLTree<Key, Val>::get(Key* key) {
	return NULL;
}

template <class Key, class Val>
void
AVLTree<Key, Val>::put(Key* key, Val* val) {
	AVLNode<Key,Val>* current = mRoot;
	AVLNode<Key, Val>* previous = mSentinel;
	while (current != mSentinel)
	{
		if (*key == *current->key)
		{
			current->val = val;
			break;
		}
		else if (*key > *current->key) {
			previous = current;
			current = current->right;

		}
		else {
			previous = current;
			current = current->left;
		}
	}
	
	if (current != mSentinel) {
		current = new AVLNode<Key, Val>(mSentinel);
		current->key = key;
		current->val = val;
		current->parent = previous;
		if (previous != mSentinel) {
			if (*previous->key > *current->key)
				previous->left = current;
			else previous->right = current;
			insertFixup(previous);
		}
		else {
			mRoot = current;
			mRoot->parent = mSentinel;
		}
	}
}
/**
* Find the minimum element.
* Does that by following the left child till the
* left child is sentinel.
*/
template <class Key, class Val>
Key*
AVLTree<Key, Val>::min() {
	AVLNode<Key, Val>* current = mRoot;
	while (current->left != mSentinel)
		current = current->left;
	return current->key;	
}

/**
* Find the maximum element.
* Does that by following right child till
* the right child is sentinel.
*/
template <class Key, class Val>
Key*
AVLTree<Key, Val>::max() {
	AVLNode<Key, Val>* current = mRoot;
	while (current->right != mSentinel)
		current = current->right;
	return current->key;
}

/**
* Find the successor for a given key.
* If the found key has right sub-tree, 
* then find min in that tree.
* Else find the first right ancestor.
*/
template <class Key, class Val>
Key*
AVLTree<Key, Val>::successor(Key* key) {
	Key* result = NULL;
	AVLNode<Key, Val>* current = mRoot;
	while (current != mSentinel) {
		if (*current->key == *key) {
					// if right sub-tree.
			if (current->right != mSentinel) {
				current = current->right;
				while (current->left != mSentinel)
					current = current->left;
				result = current->key;
			}
			else {
				while (current->parent != mSentinel && current == current->parent->right)
					current = current->parent;
				if (current->parent != mSentinel) result = current->parent->key;
			}
			break;
		}
		else if (*current->key > *key)
			current = current->left;
		else current = current->right;
	}
	return result;
}

template <class Key, class Val>
Key*
AVLTree<Key, Val>::predecessor(Key* key) {
	Key* result = NULL;
	AVLNode<Key, Val>* current = mRoot;
	while (current != mSentinel) {
		if (*current->key == *key) {
					// if left sub-tree.
			if (current->left != mSentinel) {
				current = current->left;
				while (current->right != mSentinel)
					current = current->right;
				result = current->key;
			}
			else {
				while (current->parent != mSentinel && current == current->parent->left)
					current = current->parent;
				if (current->parent != mSentinel) result = current->parent->key;
			}
			break;
		}
		else if (*current->key > *key)
			current = current->left;
		else current = current->right;
	}
	return result;
}

// TODO: add size info and logic to update it 
// with insert and delete as well as rotate.
// then implement rank methods below.
template <class Key, class Val>
Key*
AVLTree<Key, Val>::getKeyWithRank(int rank) {
	AVLNode<Key, Val>* node = getAVLNodeWithRank(rank);
	return node ? node->key : NULL;
}

template <class Key, class Val>
Val*
AVLTree<Key, Val>::getValWithRank(int rank) {
	AVLNode<Key, Val>* node = getAVLNodeWithRank(rank);
	return node ? node->value : NULL;
}

template <class Key, class Val>
int
AVLTree<Key, Val>::getRank(Key* key) {
	int rank = 0;
	AVLNode<Key, Val>* current = mRoot;
	while (current != mSentinel) {
		if (*key == *current->key) {
			rank += current->left->size + 1;
			break;
		}
		else if (*key > *current->key) {
			rank += current->left->size + 1;
			current = current->right;
		}
		else {
			current = current->left;
		}		
	}
	return rank;
}

template <class Key, class Val>
int
AVLTree<Key, Val>::size() {
	return mRoot->size;	
}

int main(int argc, char** argv) {
	AVLTree<int*, int*> instance;
	return 0;
}
