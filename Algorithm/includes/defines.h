#ifndef __DEFINES__H
#define __DEFINES__H

// in bytes 
#define BUFFER_SIZE	8
#define BYTE_SIZE 8

#define CURRENT_BYTE(index) \
	(index/BYTE_SIZE)
#define CURRENT_BIT(index) \
	(index%BYTE_SIZE)

#endif
