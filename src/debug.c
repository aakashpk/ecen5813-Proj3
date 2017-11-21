#include "debug.h"

void print_memory(uint8_t * start, uint32_t length) {
	#ifdef VERBOSE
	int i=0;
	if(start!=NULL) {
		for(i=0;i<length;i++){
		printf("\n Value at Address:%p is %d\n",(start+i),*(start+i));
	 }
	}
#else
;
#endif
}
