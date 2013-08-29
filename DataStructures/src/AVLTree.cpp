#include "AVLTree.h"

/*********************/
/** Private methods **/
/*********************/

template <class Key, class Val>
AVLNode<Key,Val>*
AVLTree<Key, Val>::getAVLNodeWithRank(int rank) {
	AVLNode<Key, Val>* current = mRoot;
	AVLNode<Key, Val>* result = NULL;
	while (current != NULL) {
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


/********************/
/** Public methods **/
/********************/

/**
* Find the minimum element.
* Does that by following the left child till the
* left child is sentinel.
*/
template <class Key, class Val>
Key*
AVLTree<Key, Val>::min() {
	AVLNode<Key, Val>* current = mRoot;
	while (current->left != NULL)
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
	while (current->right != NULL)
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
	while (current != NULL) {
		if (*current->key == *key) {
					// if right sub-tree.
			if (current->right != NULL) {
				current = current->right;
				while (current->left != NULL)
					current = current->left;
				result = current->key;
			}
			else {
				while (current->parent != NULL && current == current->parent->right)
					current = current->parent;
				if (current->parent != NULL) result = current->parent->key;
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
	while (current != NULL) {
		if (*current->key == *key) {
					// if left sub-tree.
			if (current->left != NULL) {
				current = current->left;
				while (current->right != NULL)
					current = current->right;
				result = current->key;
			}
			else {
				while (current->parent != NULL && current == current->parent->left)
					current = current->parent;
				if (current->parent != NULL) result = current->parent->key;
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
	while (current != NULL) {
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
