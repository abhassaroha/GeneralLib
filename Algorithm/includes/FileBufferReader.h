#ifndef __FILE_BUFFER_READER_H
#define __FILE_BUFFER_READER_H

#include <fstream>
#include "defines.h"

using namespace std;
// Data read by this class is assumed to have been encoded
// in little endian format. Earlier bits of buffer encoded data
// which came earlier.
class FileBufferReader {
	private:
		char* mFileName;
		ifstream mStream;
		char* mBuffer;
		int mBufferIndex;
		int mReadBytes;
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
		void readInt(int&);
};

#endif
