#ifndef __HUFFMAN__H
#define __HUFFMAN__H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "FreqInfo.h"
#include "Queue.h"
#include "FileBufferReader.h"
#include "FileBufferWriter.h"

using namespace std;

#define NUMCHARS 256 
class Huffman {
private:
	int mFieldLength; // length of the huffman code
	bool mBitField[NUMCHARS]; // the bit field to represent huffman code
	FileBufferReader* mFileReader;
	FileBufferWriter* mFileWriter;
	FreqInfo* mRoot;
	FreqInfo** freqTable;
	void swap(FreqInfo**, int, int);
	void threeWayQuickSort(FreqInfo**, int, int);
	void checkStreamIsGood();
	void buildFrequencyTable();
	void buildPrefixFreeTree();
	void writePrefixFreeTree(FreqInfo*);
	void writeCompressedText();
	unsigned int readPrefixFreeTree();
	void parsePrefixFreeTree(FreqInfo*);
	void decodeCompressedText(unsigned int);
public:
	Huffman(char* inFile, char* outFile) {
		mFieldLength = 0;
		mFileReader = new FileBufferReader(inFile);
		mFileWriter = new FileBufferWriter(outFile);
	}
	void encode();
	void decode();
};
#endif
