#ifndef MEM_H
#define MEM_H

#include "details.h"

#include <stddef.h>

RCEXTERN 
void *rcmalloc(size_t sz);

RCEXTERN
void rcfree(void* v);

#endif // MEM_H
