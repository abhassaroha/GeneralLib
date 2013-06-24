#ifndef __HUFFMAN__H
#define __HUFFMAN__H

#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define NUMCHARS 256 
struct FreqInfo {
	unsigned char codePoint;
	bool* bitField;
	int fieldLength;
	int freq;
	FreqInfo* left;
	FreqInfo* right;
	FreqInfo() {
		freq = 0;
		left = NULL;
		right = NULL;
		bitField = NULL;
	}
};

// Queue with assumption that we will never
// overflow and underflow.
class Queue {
private:
	FreqInfo** mArray;
	int mLeft;
	int mRight;
public:
	Queue(FreqInfo** array, int left, int right = -1):
		mArray(array), mLeft(left), mRight(right) {};

	FreqInfo* pop() {
		FreqInfo* result = NULL;
		if (this->good()) {
			result = mArray[mLeft];
			mLeft++;
		}
		return result;
	};

	void push(FreqInfo* elem) {
		mArray[++mRight] = elem;
	};

	FreqInfo* peek() {
		FreqInfo* result = NULL;
		result = mArray[mLeft];
		return result;
	};

	bool good() {
		return (mLeft <= mRight);
	};

	int size() {
		int result = mRight - mLeft + 1;
		if (result < 0) result = 0;
		return result;
	}
};

class Huffman {
private:
	char* mInFile;
	char* mOutFile;
	FreqInfo* mRoot;
	FreqInfo** freqTable;
	void threeWayQuickSort(FreqInfo**, int, int);
	void buildFrequencyTable();
	void buildPrefixFreeTree();
	void writePrefixFreeTree(FreqInfo*, ofstream&);
	void writeCompressedText(ofstream&);
	void readPrefixFreeTree(ifstream&);
	void parsePrefixFreeTree(FreqInfo*, ifstream&);
	void decodeCompressedText();
	void writeUncompressedText();
public:
	Huffman(char* inFile, char* outFile) {
		mInFile = inFile;
		mOutFile = outFile;
	}
	void encode();
	void decode();
};
#endif
