#include "AVLTree.h"

#include <cstdlib>

namespace datastructures {
    
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
        if (parent != mSentinel) {
            if (node == parent->left)
                parent->left = right;
            else
                parent->right = right;
            parent->height =
            MAX(parent->left->height, parent->right->height) + 1;
        }
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
        if (parent != mSentinel)
        {
            if (node == parent->left)
                parent->left = left;
            else
                parent->right = left;
            parent->height =
            MAX(parent->left->height, parent->right->height) + 1;
        }
        // update node's parent
        node->parent = left;
        if (mRoot == node) mRoot = left;
    }
    
	template <class Key, class Val>
    AVLTree<Key, Val>::AVLNode<Key,Val>*
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
            parent = node->parent;
            if (node->left->height > node->right->height + 1) {
                if (node->left->right->height > node->left->left->height) {
                    leftRotate(node->left);
                }
                rightRotate(node);
            }
            else if (node->right->height > node->left->height + 1) {
                if (node->right->left->height >
                    node->right->right->height) {
                    rightRotate(node->right);
                }
                leftRotate(node);
            }
            // make sure height is consistent after previous rotations
            else node->height =
                MAX(node->left->height, node->right->height) + 1;
            node = parent;
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
    AVLTree<Key, Val>::put(Key* key, Val* value) {
        AVLNode<Key,Val>* current = mRoot;
        AVLNode<Key, Val>* previous = mSentinel;
        while (current != mSentinel)
        {
            if (*key == *current->key)
            {
                current->value = value;
                break;
            }
            else if (*key > *current->key) {
                previous = current;
                current->size++;
                current = current->right;
            }
            else {
                previous = current;
                current->size++;
                current = current->left;
            }
        }
        
        int newVal;
        if (current == mSentinel) {
            current = new AVLNode<Key, Val>(mSentinel);
            current->key = key;
            current->value = value;
            current->parent = previous;
            if (previous != mSentinel) {
                if (*previous->key > *current->key)
                    previous->left = current;
                else previous->right = current;
                while (previous != mSentinel) {
                    newVal =
                    MAX(previous->left->height, previous->right->height) + 1;
                    if (newVal > previous->height) previous->height = newVal;
                    else break;
                    previous = previous->parent;
                }
                insertFixup(current->parent);
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
                    while (current->parent != mSentinel
                           && current == current->parent->right)
                        current = current->parent;
                    if (current->parent != mSentinel)
                        result = current->parent->key;
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
                    while (current->parent != mSentinel
                           && current == current->parent->left)
                        current = current->parent;
                    if (current->parent != mSentinel)
                        result = current->parent->key;
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
    
	template <class Key, class Val>
    void
    AVLTree<Key, Val>::printTree(AVLNode<Key,Val>* root) {
        if (root != mSentinel) {
            // Assert invariant
            if (root->left->height > root->right->height + 1 ||
                root->left->height + 1 < root->right->height)
            {
                cout<<"Imbalanced tree at node "<<*root->key
                <<" -> "<<*root->value<<" "<<endl;
                exit(EXIT_FAILURE);
            }
            if (root->height !=
                MAX(root->left->height, root->right->height) + 1) {
                cout<<"Height invariant violated at "<<*root->key<<" -> "
                <<*root->value<<" H "<<root->height<<" ";
                cout<<"LH "<<root->left->height<<" RH "
                <<root->right->height<<endl;
                exit(EXIT_FAILURE);
            }
            printTree(root->left);
            cout<<*root->key<<" -> "<<*root->value<<" ";
            printTree(root->right);
        }
    }
    
	template <class Key, class Val>
    void
    AVLTree<Key, Val>::print() {
        printTree(mRoot);
        cout<<endl;
    }
    
}

//////////////////////////////////////
//            Test Client			//
//////////////////////////////////////

void swap(int* source, int a, int b) {
    int temp = source[a];
    source[a] = source[b];
    source[b] = temp;
}

void knuthShuffle(int* inArray, int length) {
    int i;
    int current;
    srand(time(NULL));
    for (i = length; i > 0;) {
        current = rand()%i;
        swap(inArray, current, --i);
    }
}

using namespace datastructures;

int main(int argc, char** argv) {
	AVLTree<int, int> testInstance;
	int* array = new int[10];
	for (int i = 0; i < 10; i++)
		array[i] = i + 1;
	knuthShuffle(array, 10);
	// Test insertion
	for (int i = 0; i < 10; i++) {
		testInstance.put(&array[i], &array[i]);
	}
	testInstance.print();
    
    // Test min
	int* min = testInstance.min();
	cout<<"Min "<<*min<<endl;
    // Test successor of min
	int* successor = testInstance.successor(min);
	cout<<"Successor of Min "<<*successor<<endl;
    // Test predecessor of min
	int *predecessor = testInstance.predecessor(min);
	cout<<"Predecessor of Min is NULL "
    <<(predecessor==NULL ? "true" : "false")<<endl;
    
    // Test max	
	int* max = testInstance.max();
	cout<<"Max "<<*max<<endl;
    // Test successor of max
	successor = testInstance.successor(max);
	cout<<"Successor of Max is NULL "
    <<(successor == NULL ? "true" : "false")<<endl;
    // Test predecessor of max
	predecessor = testInstance.predecessor(max);
	cout<<"Predecessor of Max "<<*predecessor<<endl;
    // Rank tests
	cout<<"Test Rank for "<<array[2]<<endl;
	int rank = testInstance.getRank(&array[2]);
	cout<<"Key with rank "<<rank<<" "<<*testInstance.getKeyWithRank(rank)<<endl;
	cout<<"Val with rank "<<rank<<" "<<*testInstance.getValWithRank(rank)<<endl;
	return 0;
}
