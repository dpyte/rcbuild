
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

inline void *rcmalloc(size_t sz) {	

	void *rval = malloc(sz);
	if (rval == NULL) {
		fprintf(stderr,
				"rcmalloc: failed to allocate memory: %ld\n", sz);
		exit(-1);
	}
	return rval;
}

inline void rcfree(void *v) {
	if (v != NULL) {
		free(v);
		v = NULL;
	}
}
