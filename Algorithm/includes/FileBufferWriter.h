#ifndef __FILE_BUFFER_WRITER_H
#define __FILE_BUFFER_WRITER_H

#include <fstream>

class FileBufferWriter {
	private: 
		char* mFileName;
		ofstream mStream;
public:
		flushBuffer();
		writeBit(bool);
		writeByte(unsigned char);
}

#endif
