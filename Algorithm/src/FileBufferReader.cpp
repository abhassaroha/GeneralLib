#include "FileBufferReader.h"

void FileBufferReader::fillBuffer() {
	mStream.read(mBuffer, BUFFER_SIZE);
	mReadBytes = mStream.gcount();
	mInBytes += mReadBytes;
	mBufferIndex = 0;
}

void FileBufferReader::open() {
	mStream.open(mFileName, ios::binary|ios::in);
	mBufferIndex = 0;
	mReadBytes = 0;
	mInBytes = 0;
}

void FileBufferReader::close() {
	mStream.close();	
}

bool FileBufferReader::good() {
	return mStream.good() || mBufferIndex < mReadBytes*BYTE_SIZE;
}

bool FileBufferReader::fail() {
	return mStream.fail();
}

bool FileBufferReader::bad() {
	return mStream.bad();
}

bool FileBufferReader::eof() {
	return mStream.eof();
}

void FileBufferReader::readBit(bool& bit) {
	char byte;
	// Full buffer, read more
	if (mBufferIndex == mReadBytes*BYTE_SIZE) {
		if (mStream.good()) {
			fillBuffer();
		}
		else  { // buffer is not good anymore
			mReadBytes = 0;
			mBufferIndex = 0;
			return;
		}
	}
	// return the current unread bit
	int mask = 1<<CURRENT_BIT(mBufferIndex);
	byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
	mBufferIndex++;
	bit = byte&mask;
}

void FileBufferReader::readByte(char& byte) {
	byte = 0;
	int currentBit;
	// buffer reached end, read more from file
	if (mBufferIndex == mReadBytes*BYTE_SIZE) {
		if (mStream.good()) {
			fillBuffer();
			byte = mBuffer[0];
			mBufferIndex += BYTE_SIZE;
		}
		else { // buffer is no longer good
			mReadBytes = 0;
			mBufferIndex = 0;
		}
	} 
	else { // buffer has not reached end 
		byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
		currentBit = CURRENT_BIT(mBufferIndex);
		// if not reached byte boundary, make up byte from two adjacent
		// bytes in buffer
		if (currentBit == 0) {
			mBufferIndex += BYTE_SIZE;
		}
		else {
			// remove lower read bits
			byte = ((unsigned char)byte)>>currentBit;
			mBufferIndex += BYTE_SIZE - currentBit;
			if (mBufferIndex == mReadBytes*BYTE_SIZE) {
				if (mStream.good()) {
					fillBuffer();
					// remove higher unexplored bits
					// not casting as left shift of signed and unsigned 
					// are equivalent
					byte = byte|mBuffer[0]<<(BYTE_SIZE - currentBit);
					mBufferIndex += currentBit;
				}
				else {
					mReadBytes = 0;
					mBufferIndex = 0;
				}
			}
			else {
				// remove higher unexplored bits
				// not casting as left shift of signed and unsigned 
				// are equivalent
				byte = 
				byte|mBuffer[CURRENT_BYTE(mBufferIndex)]<<(BYTE_SIZE - currentBit);
				mBufferIndex += currentBit;
			}
		}
	}
}

void FileBufferReader::readInt(unsigned int& result) {
	char byte; 
	readByte(byte);
	result = (unsigned char) byte;
	readByte(byte);
	result = (unsigned char)byte<<BYTE_SIZE|result;
	readByte(byte);
	result = (unsigned char)byte<<2*BYTE_SIZE|result;
	readByte(byte);
	result = (unsigned char)byte<<3*BYTE_SIZE|result;
}
