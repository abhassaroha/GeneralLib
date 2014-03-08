#include "Huffman.h"

#ifdef DEBUG
void printFreqTable(FreqInfo** freqTable) {
	for (int i = 0; i < NUMCHARS; i++) {
		cout<<freqTable[i]->codePoint<<"\t"<<freqTable[i]->freq<<endl;
	}
}
#endif

namespace algorithms {
	void Huffman::swap(FreqInfo** source, int a, int b) {
		FreqInfo* temp = source[a];
		source[a] = source[b];
		source[b] = temp;
	}

	void Huffman::checkStreamIsGood() {
		if (!mFileReader->good()) {
			if(mFileReader->eof()) {
				cout<<"EOF reached"<<endl;
				exit(EXIT_FAILURE);
			}
			else if (mFileReader->bad()) {
				cout<<"Bad bit set"<<endl;
				exit(EXIT_FAILURE);
			}
			else if (mFileReader->fail()) {
				cout<<"Fail bit set"<<endl;
				exit(EXIT_FAILURE);
			}		
		}
	}
	void Huffman::threeWayQuickSort(FreqInfo** inArray, int left, int right) {
		if (left >= right) return;
		int i = left, j = left, k = right;
		int pivot = inArray[left + rand()%(right - left + 1)]->freq;
		while (i <= k) {
			if (inArray[i]->freq < pivot) 
				swap(inArray, i++, j++);
			else if (inArray[i]->freq > pivot)
				swap(inArray, i, k--);
			else i++;
		}
		threeWayQuickSort(inArray, left, j - 1);
		threeWayQuickSort(inArray, k + 1, right);
	}

	/*************************/
	/** Compression methods **/
	/*************************/

	void Huffman::buildFrequencyTable() {
		unsigned int charCount = 0;
		mFileReader->open();
		checkStreamIsGood();
		char current;
		freqTable = new FreqInfo*[NUMCHARS]; 
		for (int i = 0; i < NUMCHARS; i++) {
			freqTable[i] = new FreqInfo;
			freqTable[i]->codePoint = (unsigned char) i;
		} 
		mFileReader->readByte(current);
		while (mFileReader->good()) {
			freqTable[(int)current]->freq++;
			charCount++;
			mFileReader->readByte(current);
		}
		mFileReader->close();
		// open the compressed data target and write char count
		mFileWriter->open();
		// cout<<"Char count "<<charCount<<endl;
		mFileWriter->writeInt(charCount);
	}

#define CREATE_ROOT() \
	mRoot = new FreqInfo();	\
	mRoot->left = first;		\
	mRoot->right = second;	\
	mRoot->freq = first->freq + second->freq;	\
	queueTwo->push(mRoot)

	void Huffman::buildPrefixFreeTree() {
		int q1Left = 0, iter;
		FreqInfo *first, *second;
		FreqInfo** copy = new FreqInfo*[NUMCHARS];
		for (int i = 0; i < NUMCHARS; i++)
			copy[i] = freqTable[i];
		threeWayQuickSort(copy, 0, NUMCHARS - 1);
		while(copy[q1Left]->freq == 0) q1Left++; 
		Queue* queueOne = new Queue(copy, q1Left, NUMCHARS - 1);
		// we decrease number of elems by one each iteration and we stop
		// after length - 1 iterations of original array, hence second queue's
		// size is bounded as below.
		Queue* queueTwo = new Queue(new FreqInfo*[NUMCHARS - q1Left - 1], 0);
		if (queueOne->size() == 1) {
			// handle size one queues, nothing more to do
			mRoot = queueOne->pop();
		}
		else {
			// initially queueTwo is empty
			// handle that case first
			first = queueOne->pop();
			second = queueOne->pop();
			// number of iterations is length - 1, first iteration ran above
			iter = NUMCHARS - q1Left - 2;
			CREATE_ROOT();
			while (iter-- > 0) {
				if (!queueOne->good()) {
					// when queuOne has nothing, choose both from queueTwo
					first = queueTwo->pop();
					second = queueTwo->pop();
				}
				else { // when both queues have elements
					// first comes from second queue
					if (queueTwo->peek()->freq < queueOne->peek()->freq) { 
						first = queueTwo->pop();
						if (queueTwo->good()) { //queueTwo could be empty
							if (queueTwo->peek()->freq <  queueOne->peek()->freq)
								second = queueTwo->pop();
							else second = queueOne->pop();
						}
						else {
							second = queueOne->pop();
						}
					}
					else { // first comes from first queue
						first = queueOne->pop();
						if (queueOne->good()) { // frist queue could be empty
							if (queueTwo->peek()->freq <  queueOne->peek()->freq)
								second = queueTwo->pop();
							else second = queueOne->pop();
						}
						else {
							second = queueTwo->pop();
						}
					}
				}
				CREATE_ROOT();
			}
		}
	}

	// Post order traversal of the prefix tree
	void Huffman::writePrefixFreeTree(FreqInfo* root) {
		if (!root->left) {
			// leaf node
			mFileWriter->writeBit(true);
			// write length of huffman code
			mFileWriter->writeByte(root->codePoint);
			root->fieldLength = mFieldLength; 
			root->bitField = new bool[mFieldLength];
			// write the huffman code
			for (int i = 0; i < mFieldLength; i++) {
				root->bitField[i] = mBitField[i];
			}
		}
		else {
			// non-leaf node
			mFileWriter->writeBit(false);	
			// mFieldLength++ - push stack
			mBitField[mFieldLength++] = false;
			writePrefixFreeTree(root->left);
			// mFieldLength++ - push stack
			mBitField[mFieldLength++] = true;
			writePrefixFreeTree(root->right);
		}
		// pop stack
		mFieldLength--;
	}

	void Huffman::writeCompressedText() {
		mFileReader->open();
		char current;
		FreqInfo* node;
		mFileReader->readByte(current);
		while (mFileReader->good()) {
			node = freqTable[(int)current];
			for (int i = 0; i < node->fieldLength; i++) {
				mFileWriter->writeBit(node->bitField[i]);
			}
			mFileReader->readByte(current);
		}
		mFileWriter->close();
		mFileReader->close();
	}

	/***************************/
	/** Decompression methods **/
	/***************************/
	// TODO: handle case of corrupt compressed input files.

	// read in the prefix free tree from file to be decoded
	unsigned int Huffman::readPrefixFreeTree() {
		mRoot = new FreqInfo;
		unsigned int charCount;
		mFileReader->open(); 
		checkStreamIsGood();
		mFileReader->readInt(charCount);
		parsePrefixFreeTree(mRoot);
		return charCount;
	}

	// do a post order traversal and regenerate the prefix free tree
	void Huffman::parsePrefixFreeTree(FreqInfo* root) {
		bool current; 
		if (mFieldLength == NUMCHARS)  {
			cout<<"Corrupt compression header detected!"<<endl;
			exit(EXIT_FAILURE);
		}
		mFileReader->readBit(current);
		// leaf node
		if (current) {
			mFileReader->readByte((char&)root->codePoint);
			root->fieldLength = mFieldLength; 
			root->bitField = new bool[mFieldLength];
			// write the huffman code
			for (int i = 0; i < mFieldLength; i++) {
				root->bitField[i] = mBitField[i];
			}
		}
		else { // non leaf
			root->left = new FreqInfo;
			root->right = new FreqInfo;
			mBitField[mFieldLength++] = false;
			parsePrefixFreeTree(root->left);
			mBitField[mFieldLength++] = true;
			parsePrefixFreeTree(root->right);
		}
		mFieldLength--;
	}

	// Go through the remaining file and regenerate the original
	// characters.
	void Huffman::decodeCompressedText(unsigned int charCount) {
		FreqInfo* current = mRoot;
		bool bit;
		mFileWriter->open();
		while(charCount > 0) {
			if (!current->left) {
				mFileWriter->writeByte(current->codePoint);
				charCount--;
				current = mRoot;
			}
			else {
				mFileReader->readBit(bit);
				if (bit) {
					current = current->right;
				}
				else {
					current = current->left;
				}
			}
		}
		mFileReader->close();
		mFileWriter->close();
	}

	/*******************/
	/** Public methods */
	/*******************/

	void Huffman::encode() {
		buildFrequencyTable();
		buildPrefixFreeTree();
		writePrefixFreeTree(mRoot);
		writeCompressedText();
		int readBytes = mFileReader->readBytes();
		int wroteBytes = mFileWriter->wroteBytes();
		cout<<"Read bytes "<<readBytes<<"\tWrote bytes "<<wroteBytes<<endl;
		cout<<"Compression ratio "<<100.0f*wroteBytes/readBytes<<endl;
	}

	void Huffman::decode() {
		unsigned int charCount = readPrefixFreeTree();
		// cout<<"Char count "<<charCount<<endl;
		decodeCompressedText(charCount);
		int readBytes = mFileReader->readBytes();
		int wroteBytes = mFileWriter->wroteBytes();
		cout<<"Read bytes "<<readBytes<<"\tWrote bytes "<<wroteBytes<<endl;
		cout<<"Compression ratio "<<100.0f*readBytes/wroteBytes<<endl;
	}
}

int main(int argc, char** argv) {
	using namespace algorithms;
	Huffman* instance;
	if (argc < 4) {
		cout<<"Insufficient arguments"<<endl;
		cout<<"\tUsage: huffman -/+ inFile outFile"<<endl;
		cout<<"\t-\tEncode file"<<endl;
		cout<<"\t+\tDecode file"<<endl;
		exit(EXIT_FAILURE);
	}
	instance = new Huffman(argv[2], argv[3]);

	if (argv[1][0] == '-') {
		instance->encode();
	}
	else if (argv[1][0] == '+') {
		instance->decode();
	}
	else {
		cout<<"Incorrect argument: "<<argv[1][0]<<endl;
		cout<<"\tUsage: huffman -/+ inFile outFile"<<endl;
		cout<<"\t-\tEncode file"<<endl;
		cout<<"\t+\tDecode file"<<endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
