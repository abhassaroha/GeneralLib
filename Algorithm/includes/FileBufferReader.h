#ifndef FILE_BUFFER_READER_H
#define FILE_BUFFER_READER_H

#include <fstream>
#include "defines.h"

using namespace std;
// Data read by this class is assumed to have been encoded
// in little endian format. Earlier bits of buffer encoded data
// which came earlier.
class FileBufferReader {
private:
	unsigned int mInBytes; // field for read, write stats
	char* mFileName;
	ifstream mStream;
	char* mBuffer;
	int mBufferIndex;
	int mReadBytes;
	void fillBuffer();
public:
	FileBufferReader(char* fileName):mFileName(fileName) {
		mBuffer = new char[BUFFER_SIZE];
		mBufferIndex = 0;
	};
	void open();
	void close();
	bool good();
	bool fail();
	bool bad();
	bool eof();
	void readBit(bool&);
	void readByte(char&);
	void readInt(unsigned int&);
	unsigned int readBytes() { return mInBytes; }
};

#endif
