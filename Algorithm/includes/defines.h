#ifndef DEFINES_H
#define DEFINES_H

// in bytes 
#define BUFFER_SIZE 4012	
#define BYTE_SIZE 8

#define CURRENT_BYTE(index) \
(index/BYTE_SIZE)
#define CURRENT_BIT(index) \
	(index%BYTE_SIZE)

#endif
