#ifndef __HUFFMAN__H
#define __HUFFMAN__H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "FreqInfo.h"
#include "Queue.h"

using namespace std;

#define NUMCHARS 256 
class Huffman {
private:
	int fieldLength = 0; // length of the huffman code
	bool bitField[NUMCHARS]; // the bit field to represent huffman code
	unsigned int inBytes = 0; // field for read, write stats
	unsigned int outBytes = 0;
	FileBufferReader* mFileReader;
	FileBufferWriter* mFileWriter;
	FreqInfo* mRoot;
	FreqInfo** freqTable;
	void threeWayQuickSort(FreqInfo**, int, int);
	unsigned int buildFrequencyTable();
	void buildPrefixFreeTree();
	void writePrefixFreeTree(FreqInfo*, ofstream&);
	void writeCompressedText(ofstream&);
	void readPrefixFreeTree(ifstream&);
	void parsePrefixFreeTree(FreqInfo*, ifstream&);
	void decodeCompressedText(ifstream&, unsigned int);
public:
	Huffman(char* inFile, char* outFile) {
		mFileReader = new FileReader(inFile);
		mFileWriter = new FileWriter(outFile);
	}
	void encode();
	void decode();
};
#endif
