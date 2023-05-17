#ifndef __DATA_TYPE_H
#define __DATA_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif


#if !(defined uint8_t || defined uint16_t || defined uint32_t || defined uint64_t) 
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned long uint32_t;
	typedef unsigned long long uint64_t;
	typedef char int8_t;
	typedef short int16_t;
	typedef long int32_t;
	typedef long long int64_t;
#endif


#ifdef __cplusplus
}
#endif
#endif

