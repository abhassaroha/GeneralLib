#ifndef __HUFFMAN__H
#define __HUFFMAN__H
class Huffman {
private:
	char* inFile;
	char* outFile;
	int* freqTable;
	void buildFrequenceTable();
	void buildPrefixFreeTree();
	void writePrefixFreeTree();
	void writeCompressedText();
	void binaryToPrefixFreeTree();
	void decodeCompressedText();
	void writeUncompressedText();
public:
	Huffman(char*, char*);
	void encode();
	void decode();
};
#endif
