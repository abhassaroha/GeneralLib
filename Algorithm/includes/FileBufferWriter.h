#ifndef FILE_BUFFER_WRITER_H
#define FILE_BUFFER_WRITER_H

#include <fstream>
#include "defines.h"

using namespace std;

namespace algorithms {
	class FileBufferWriter {
		private: 
			unsigned int mOutBytes;
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
			void writeByte(char);
			void writeInt(unsigned int);
			unsigned int wroteBytes() { return mOutBytes; };
	};
}
#endif
