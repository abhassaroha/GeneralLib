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
	int fieldLength; // length of the huffman code
	bool bitField[NUMCHARS]; // the bit field to represent huffman code
	unsigned int inBytes; // field for read, write stats
	unsigned int outBytes;
	FileBufferReader* mFileReader;
	FileBufferWriter* mFileWriter;
	FreqInfo* mRoot;
	FreqInfo** freqTable;
	void threeWayQuickSort(FreqInfo**, int, int);
	unsigned int buildFrequencyTable();
	void buildPrefixFreeTree();
	void writePrefixFreeTree(FreqInfo*);
	void writeCompressedText();
	void readPrefixFreeTree();
	void parsePrefixFreeTree(FreqInfo*);
	void decodeCompressedText(int);
public:
	Huffman(char* inFile, char* outFile) {
		fieldLength = 0;
		inBytes = 0;
		outBytes = 0;
		mFileReader = new FileBufferReader(inFile);
		mFileWriter = new FileBufferWriter(outFile);
	}
	void encode();
	void decode();
};
#endif
