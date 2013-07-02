#include "FileBufferReader.h"

#define CURRENT_BYTE(index) \
	(index/BYTE_SIZE)
#define CURRENT_BIT(index) \
	(index%BYTE_SIZE)

bool FileBufferReader::isGood() {
	return mStream.good() || mBufferIndex < readBytes*BYTE_SIZE;
}

bool FileBufferReader::readBit() {
	char byte;
	if (mBufferIndex == readBytes*BYTE_SIZE) {
		if (mStream.good()) {
			mStream.read(mBuffer, BUFFER_SIZE);
			readBytes = mStream.gcount();
			mBufferIndex = 0;
		}
		else  {
			readBytes = 0;
			mBufferIndex = 0;
			return 0;
		}
	}
	int mask = 1<<CURRENT_BIT(mBufferIndex);
	byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
	mBufferIndex++;
	return byte&mask;
}

char FileBufferReader::readByte() {
	unsigned char byte = 0;
	// buffer has not reached end
	if (mBufferIndex != readBytes*BYTE_SIZE) {
		byte = (unsigned char) mBuffer[CURRENT_BYTE(mBufferIndex)];
		byte = byte>>CURRENT_BIT(mBufferIndex);
		mBufferIndex += BYTE_SIZE - CURRENT_BIT(mBufferIndex);
		if (mBufferIndex == readBytes*BYTE_SIZE) {
			if (mStream.good()) {
				mStream.read(mBuffer, BUFFER_SIZE);
				mBufferIndex = 0;
				readBytes = mStream.gcount();
				byte = byte|mBuffer[mBufferIndex/BYTE_SIZE]<<BYTE_SIZE - mBufferIndex%BYTE_SIZE;
			}
			else {
				readBytes = 0;
				mBufferIndex = 0;
			}
		}
		else {
		}
	} 
	else { // buffer reached end, read more from file
		if (mStream.good()) {
			mStream.read(mBuffer, BUFFER_SIZE);
			mBufferIndex = 0;
			readBytes = mStream.gcount();
			if (readBytes != 0) byte = mBuffer[0];
		}
		else {
			readBytes = 0;
			mBufferIndex = 0;
		}
	}
	return byte;
}
