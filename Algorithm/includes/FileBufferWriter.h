#ifndef __FILE_BUFFER_WRITER_H
#define __FILE_BUFFER_WRITER_H

#include <fstream>
#include "defines.h"

using namespace std;

class FileBufferWriter {
	private: 
		char* mFileName;
		ofstream mStream;
		char* mBuffer;
		int mBufferIndex;
public:
		FileBufferWriter(char* fileName):mFileName(fileName) {
			mBuffer = new char[BUFFER_SIZE];
			mBufferIndex = 0;
		}
		void open();
		void close();
		void flushBuffer();
		void writeBit(bool);
		void writeByte(unsigned char);
		void writeInt(int);
	};

#endif
