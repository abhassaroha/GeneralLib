#ifndef __HUFFMAN__H
#define __HUFFMAN__H

#include <fstream>
#include <iostream>
#include <stdlib.h>

#define NUMCHARS 256 

class Huffman {
private:
	char* mInFile;
	char* mOutFile;
	int* freqTable;
	void threeWayQuickSort(int*, int, int);
	void buildFrequencyTable();
	void buildPrefixFreeTree();
	void writePrefixFreeTree();
	void writeCompressedText();
	void binaryToPrefixFreeTree();
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
